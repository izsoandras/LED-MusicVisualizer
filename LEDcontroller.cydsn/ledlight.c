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
#include "ledlight.h"
#include <math.h>
#include <stdio.h>

/** Initially the timing signal is false.
*/
bool milsec = false;
/** Initialize the millisecond counter to 0
*/
uint64 millis = 0;

/** This show cycle's through the colors slowly.
*/
void doCycle(){
    //Counter to prescale the milsec signal
    static int counter = 0;
    //The number of the color to be displayed
    static int color = 0;
    //When a milsec has passed
    if(milsec){
        counter++;
        //After 10 milsec has passed
        if(counter == 10){
            counter = 0;
            //Periodically raising a color's saturation, then another's, then lowering the first's, etc.
            if(color < 256)
                PWM_G_WriteCompare(color);
            else if(color < 2*256)
                PWM_B_WriteCompare(color%256);
            else if(color < 3*256)
                PWM_G_WriteCompare(255-color%256);
            else if(color < 4*256)
                PWM_R_WriteCompare(color%256);
            else if(color < 5*256)
                PWM_B_WriteCompare(255-color%256);
            else if(color < 6*256)
                PWM_G_WriteCompare(color%256);
            else if(color < 7*256)
                PWM_R_WriteCompare(255-color%256);
            else
                color = 255;
                
            color++;
        }
        milsec = false;
    }
}
/** Struct to easily store the RGB color
*/
typedef struct RGBColor {
    uint8 red;
    uint8 green;
    uint8 blue;
} RGBColor;
/** Variable to store the currently displayed color
*/
RGBColor currentColor = {0,0,0};

/** Displays the color value passed as the arguments.
  * @param red The red channel of the RGB code
  * @param green The green channel of the RGB code
  * @param blue The blue channel of the RGB code
*/
void setColor(uint8 red, uint8 green, uint8 blue){
    currentColor.red = red;
    currentColor.green = green;
    currentColor.blue = blue;
    
    PWM_R_WriteCompare(red);
    PWM_G_WriteCompare(green);
    PWM_B_WriteCompare(blue);
}

/** Cycles red-green-blue colors, periodically.
  * Displays a color for 3s, then moves on to the other.
*/
void doRedGreenBlue(){
    static long time = 0;
    //When a milsec has passed
    if(milsec){
        //Prescale the milsec with 3000, then get the color from the mod 3 operation
        if((time/3000)%3 == 0){
            setColor(255,0,0);
        } else if((time/3000)%3 == 1){
            setColor(0,255,0);
        } else{
            setColor(0,0,255);
        }
            
        time++;
        milsec = false;
    }
}

/** A show looking like the police lights.
  * Changes color between red and blue every 650ms.
*/
void doPolice(){
    static long time = 0;
    //When a milsec has passed
    if(milsec){
        //Prescale the milsec with 650, then get the color from the mod 2 operation
        if((time/650)%2 == 0){
            setColor(255,0,0);
        } else{
            setColor(0,0,255);
        }
            
        time++;
        milsec = false;
    }
}
/** Initialize the audio sample buffer and the data needed for it
*/
int16 audioBuff[2][WINDOW_SIZE];
uint8 buffIndex = 0;
uint16 elementIndex = 0;
/** We are limiting the frequencies, since we are only looking for the base frequency
*/
int MAX_FREQ = 2000;
int MIN_FREQ = 20;
int sampleRate = 41666;
/** Calculate the dominant frequency of the samples
 * @param buffIndex The index of the buffer that contains the samples
*/
int getDominantFreq(int buffIndex){
        //for (int i = 0; i < buffer; ++i)
        //    samples[i] = rawSamples[i] * NORMALIZE;
        // Autocorrelation of the signal.
        int64 peak = 0;
        int peakIndex = -1;
        int minPeriod = sampleRate / MAX_FREQ;
        int maxPeriod = sampleRate / MIN_FREQ;
    
        for (int i = minPeriod; i < maxPeriod; ++i) {
            int64 sum = 0;
            for (int j = 0; j < WINDOW_SIZE - i; ++j)
                sum += audioBuff[buffIndex][j] * audioBuff[buffIndex][j + i];
            // Find the peak frequency.
            if (sum > peak) {
                peakIndex = i;
                peak = sum;
            }
        }
        return sampleRate / peakIndex;
}
/** Display the color based on the frequency
 * @param freq The frequency of the signal
 * @param rat A fade ratio based on the volume of the musice
*/
void audioSetColor(int freq, float rat){
    
    if(freq > 1600 || freq < 255){
        setColor(255*rat,0,0);
    } else if(freq < 510){
        setColor(255*rat, (freq-255)*rat,0);
    } else if(freq < 765){
        setColor((freq - 510)*rat, 255*rat, 0);
    } else if(freq < 1020){
        
        setColor(0,255*rat,(freq-765)*rat);
    } else if(freq < 1275){
        setColor(0,(freq - 1020)*rat,255*rat);
    } else if(freq < 1530){
        setColor((freq - 1275)*rat,(freq - 1275)*rat,255*rat);
    }
}
/** Calculate the volume (RMS) of the samples
 * @param buffIndex The index of the buffer that contains the samples
*/
int getVol(int buffIndex){
    int sum = 0;
        for(int i = 0; i < WINDOW_SIZE; i++){
            sum += audioBuff[buffIndex][i]*audioBuff[buffIndex][i];
        }
        return (int) sqrtf(sum/2048);
}
/** Colorshow based on the input music
 * The low frequencies are red, middle is green and the high is blue and eventually white
*/
void doAudio(){
    //maximum volume recorded, previous volume, avarage volume bump (threshold to detect beats), "avarage" volume
    static int maxVol = 0, lastVol = 0, avgBump = 0, avgVol = 0;
    //milliseconds elapsed since the max volume changed
    static uint64 lastMaxVol= 0;
    
    //if we gathered enough samples
    if(elementIndex >= WINDOW_SIZE){
        //save the buffer index
        int sampleIndex = buffIndex;
        //change the buffer index and reset counting
        buffIndex = (buffIndex + 1)%2;
        elementIndex = 0;
        
        int volume = getVol(sampleIndex);
        //cut the low volume to zero, else count it into the avarage
        if(volume < avgVol/2 || volume < 20)
            volume = 0;
        else
            avgVol = (avgVol + volume)/2;
        
        //char buff[8];
        //sprintf(buff, "%d\n\r", volume-lastVol);
        //update maximum volume
        if(volume > maxVol){
            maxVol = volume;
            lastMaxVol = millis;
        }
        //if the volume changes significantly, count it as a bump
        if(volume - lastVol > 30)
            avgBump = (avgBump + (volume - lastVol))/2;
          
        //calculate the dominant frequency
        int f = getDominantFreq(sampleIndex);
        //char buff[8];
        //sprintf(buff, "%d\n\r", f);
        
        //if there is a beat (the volume is higher), change the colors, else fade them
        if(volume - lastVol > avgBump * 0.9){
            audioSetColor(f, (float)volume/maxVol);
        } else{
            setColor(currentColor.red*0.7, currentColor.green*0.7, currentColor.blue*0.7);
        }
        
        
        //UART_PutString(buff);
        
        //update the memory
        lastVol = volume;
        //if the music gets quiter adjust the lightshow, so it'll continue blinking
        if(millis - lastMaxVol> 10000){
            avgVol = (avgVol + volume)/2;
        }
    }
}

/* [] END OF FILE */
