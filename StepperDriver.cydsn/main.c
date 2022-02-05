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
#include <math.h>
#include <stdlib.h>
#include "main.h"

const int CLOCK_FREQUENCY = 1000000;

const int stepMode = 1; // microstep
double stepSize = 360.0 / 200.0 / 1;//Converts steps to units that we want to use (in this case: 360 degrees of rotation per 200 steps)
double maxAccel = 360.0*10;// deg/s^2
double maxVelocity = 360.0*20;// deg/s
double targetPosition = 0;
double currentVelocity = 0;


double getCurrentPosition()
{
    return Step_Counter_ReadCounter();
}

void StartMove(double target)
{
    int targetPosition = target / stepSize;
    int currentPosition = Step_Counter_ReadCounter();
    // int period = CLOCK_FREQUENCY*stepSize/maxVelocity;
    
    Step_Counter_WriteCompare(targetPosition);
    Direction_Write(targetPosition >= currentPosition);
    Enable_Write(1);
}

CY_ISR(On_Lim_1) {
    Enable_Write(0);
    Step_Counter_WriteCounter(0);
    isr_lim_1_ClearPending();
}

CY_ISR(On_Lim_2) {
    Enable_Write(0);
    isr_lim_2_ClearPending();
}

CY_ISR(On_Fault) {
    Enable_Write(0);
    isr_fault_ClearPending();
}

int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */
    
    isr_lim_1_StartEx(On_Lim_1);
    isr_lim_2_StartEx(On_Lim_2);
    isr_fault_StartEx(On_Fault);
    Step_Counter_Start();
    
    DBG_UART_Start();
    
    StartMove(270);

    for(;;)
    {
        // DBG_UART_UartReadByte();
        
    }
}

/* [] END OF FILE */
