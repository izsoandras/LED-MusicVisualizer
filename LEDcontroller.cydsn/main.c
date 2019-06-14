/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
#include "project.h"
#include <stdbool.h>
#include "ledlight.h"
#include <stdio.h>

#define STATE_ADDR 0
#define SRC_ADDR 1

/**Char array to store the message we want to send on serial
*/
char buff[40];
/** Stores if the control is set to remote
*/
bool terminalEnabled = false;
/** Stores the current state of the statemachine.
*/
LightStates currentState;
/** Stores the next state of the statemachine.
*/
LightStates nextState = -1;
/** Set the initial state of the mode switching push button.
  * The button is active low.
*/
bool sw_modeStatus = true;
/** Set the initial state of the source switching push button.
  * The button is active low.
*/
bool sw_srcStatus = true;
/** Enumerate to use for the audio input
*/
typedef enum InputChannel{
    Mic = 0,
    Jack = 1
} InputChannel;
/** Currently selected channel
*/
InputChannel srcChannel = -1;
/** Set the audio input channel
 * @param channel The audio channel you want to select
*/
void setInput(InputChannel channel){
    //if the channel is different than the current, change the variable, write to memory, set the multiplexer and change the LED status
    if(channel != srcChannel){
        srcChannel = channel;
        EEPROM_WriteByte((uint8)srcChannel, SRC_ADDR);
        AMux_1_Select(srcChannel);
        
        LED_JACK_Write(srcChannel);
        LED_MIC_Write((srcChannel+1)%2);
    }
}
/** Update the state of the main state machine
*/
void updateState(){
    if(currentState != nextState){
        currentState = nextState;
        EEPROM_WriteByte((uint8)nextState, STATE_ADDR);
        sprintf(buff, "State changed: %d\n\r", nextState);
        UART_PutString(buff);
    }
}

/** Timer interrupt which is called every 1ms.
  * This function manages the milsec flag for the lightshows.
  * Also handles the button presses.
  * @param TimerIT the name of the interrupt to handle
*/
CY_ISR(TimerIT){
    //Store the currently selected source and the state of the buttons during the last few calls.
    //It's used for the debouncing
    static bool sw_modePrev[] = {true, true, true, true, true}, sw_srcPrev[] = {true, true, true, true, true};
    static uint8 i = 0;
    //Clear the interrupt
    Timer_1_STATUS;
    milsec = true;
    millis++;
   
    if(!terminalEnabled){
        sw_modePrev[i%5] =  SW_mode_Read();
        bool sw_modeNow = false;
        //Checking if any of the last 5 button reads is high.
        for(int i = 0; i < 5; i++){
            sw_modeNow = sw_modeNow || sw_modePrev[i];
        }
        //If none of the last 5 reading was high, that means the button is pressed
        //If the button is pressed and it wasn't before change the state
        if(!sw_modeNow && sw_modeStatus){
            nextState = ((currentState+1)%StateNo);
            sw_modeStatus = false;
        //If there is at least 1 high value that means the button is not pressed or it's bouncing
        } else if(sw_modeNow){
            sw_modeStatus = true;
        }
    
        sw_srcPrev[i%5] = SW_src_Read();
        bool sw_srcNow = false;
        //Checking if any of the last 5 button reads is high.
        for(int i = 0; i < 5; i++){
            sw_srcNow = sw_srcNow || sw_srcPrev[i];
        }
        //If none of the last 5 reading was high, that means the button is pressed
        //If the button is pressed and it wasn't before change the source and the feedback LEDs.
        if(!sw_srcNow && sw_srcStatus){
            setInput(!srcChannel);
            sw_srcStatus = false;
        //If there is at least 1 high value that means the button is not pressed or it's bouncing
        } else if(sw_srcNow){
            sw_srcStatus = true;
        }
    
    
        i++;
    }
}
/** The interrupt called when the ADC has finished a conversion
 * @AdcIT AdcIT The name of the interrupt to handle
*/
CY_ISR(AdcIT){
    //gather samples to the buffer, and update the number of samples until we have enough
    if(elementIndex < WINDOW_SIZE){
        audioBuff[buffIndex][elementIndex] = ADC_GetResult32()-33000;
        elementIndex++;
        //sprintf(buff, "%ld\r\n", ADC_GetResult32()-32768);
        //UART_PutString(buff);
    }
}
/** Initializes every compontent and sets default values.
*/
void init(){
    //serial port
    UART_Start();
    UART_PutString("Setup running\n\r");
    //non volatile memory
    EEPROM_Start();
    //start the interrupts
    isr_Timer_StartEx(TimerIT);
    isr_ADC_StartEx(AdcIT);
    //start the circuit elements
    opamp_1_Start();
    AMux_1_Start();
    ADC_Start();
    isr_ADC_Disable();
    ADC_StartConvert();
    //start PWMs
    PWM_B_Start();
    PWM_B_WriteCompare(0);
    PWM_R_Start();
    PWM_R_WriteCompare(0);
    PWM_G_Start();
    PWM_G_WriteCompare(0);
    //start the main timer
    Timer_1_Start();
    
    //initialize the state machine
    nextState = EEPROM_ReadByte(STATE_ADDR);
    sprintf(buff, "Init state: %d\n\r", nextState);
    UART_PutString(buff);
    //initialize the input
    setInput(EEPROM_ReadByte(SRC_ADDR));
    sprintf(buff, "Init source: %d\n\r", srcChannel);
    UART_PutString(buff);
   
    //repotrt we finished the setup
    UART_PutString("Setup done. Enabling Global IT\n\r");
    //enable global interrupts
    CyGlobalIntEnable;
}
/** The main program running the state machine.
  * After a little "setup ready" lightshow, it starts the loop with the state machine running in it.
*/
int main(void)
{   
    init();
    //Feedback for the user that setup is ready and the LEDs are working
    PWM_B_WriteCompare(255);
    CyDelay(500);
    PWM_B_WriteCompare(0);
    PWM_G_WriteCompare(255);
    CyDelay(500);
    PWM_G_WriteCompare(0);
    PWM_R_WriteCompare(255);
    CyDelay(500);
    PWM_R_WriteCompare(0);
    
    //The state machine. In every state it calls the right lightshows display function.
    //The currentState is updated in the case block, so it is possible to detect in the state if we just entered.
    for(;;)
    {
        //if we changed the state from audio turn off the ADC to prevent unnecessary interrupts and consumption
        if(nextState != Audio && currentState == Audio)
            isr_ADC_Disable();
            
        //run the main state machine
        //call the 'do' method of the currently displayed lightshow
        switch(nextState){
            case Cycle:
                updateState();
                doCycle();
                break;
            case RedGreenBlue:
                updateState();
                doRedGreenBlue();
                break;
             case Police:
                updateState();
                doPolice();
                break;
            case Audio:
                if(currentState != Audio){
                    isr_ADC_Enable();
                    setColor(0,0,0);
                }
                updateState();
                isr_Timer_Disable();
                doAudio();
                isr_Timer_Enable();
                break;
            default:
                nextState = Cycle;
                updateState();
                break;
        }
        
        //after each cycle read the UART input if there's data received
        //change the next state or the input accordingly
        while(UART_GetRxBufferSize()){
            char c = UART_GetChar();
            if(c == 'T'){
                terminalEnabled = true;
                UART_PutString("Terminal control enabled\n\r");
            }else if(c == 'E'){
                terminalEnabled = false;
                UART_PutString("Terminal control disabled\n\r");
            }else if(terminalEnabled){
                switch(c){
                    case 'C': nextState = Cycle;
                              UART_PutString("Change to Cycle\n\r");
                        break;
                    case 'R': nextState = RedGreenBlue;
                              UART_PutString("Change to RedGreenBlue\n\r");
                        break;
                    case 'P': nextState = Police;
                              UART_PutString("Change to Police\n\r");
                        break;
                    case 'A': nextState = Audio;
                              UART_PutString("Change to Audio\n\r");
                        break;
                    case 'N': nextState = (currentState+1)%StateNo;
                              UART_PutString("Change to next lightshow\n\r");
                        break;
                    case 'J': 
                              setInput(Jack);
                              UART_PutString("Switch to jack\n\r");
                        break;
                    case 'M':
                              setInput(Mic);
                              UART_PutString("Switch to mic\n\r");
                        break;
                    case 'S':
                              setInput(!srcChannel);
                              UART_PutString("Switch input\n\r");
                        break;
                    default:
                        UART_PutString("Unknown command\n\r");
                        break;
                }
            }
        }
    }
}

/* [] END OF FILE */
