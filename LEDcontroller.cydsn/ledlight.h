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
#ifndef LEDLIGHT_H
#define LEDLIGHT_H
#include "project.h"
#include <stdbool.h>
#define WINDOW_SIZE 256
    
    /** A signal to show, 1 millisec has passed.
      * The lightshow timing depends on this.
      * It's the user's responsibility to set true.*/
    extern bool milsec;
    /** Variable to count the milliseconds elapsed from start
    */
    extern uint64 millis;
    /** 2 buffers to store audio samples
    */
    extern int16 audioBuff[2][WINDOW_SIZE];
    /** The currently active buffer
    */
    extern uint8 buffIndex;
    /** The number of samples we gathered this cycle
    */
    extern uint16 elementIndex;
    
    /** Enum for easy handling of the different light shows        
    */
    typedef enum LightStates{
        Cycle,
        RedGreenBlue,
        Police,
        Audio,
        StateNo
    } LightStates;
    
    /** The lightshows' display functions.
      * Further explanation in .c file.
    */
    void doCycle();
    void setColor(uint8 red, uint8 green, uint8 blue);
    void doRedGreenBlue();
    void doPolice();
    void doAudio();
#endif
/* [] END OF FILE */
