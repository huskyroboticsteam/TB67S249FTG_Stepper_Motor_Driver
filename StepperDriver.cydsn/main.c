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
#include <stdlib.h>
#include "main.h"

const int CLOCK_FREQUENCY = 1000000;

double maxVelocity = 1440; // deg/s
double maxAcceleration = 360; // deg/s/s
double stepSize;// deg/step
int stepMode = 1; // microstep setting, 0 for full step

int targetPosition = 0;
int dbg_step = 1;
int E = 0;
int E_max;
int dir = 1;

double getCurrentPosition()
{
    return Step_Counter_ReadCounter();
}

void StartMove(int target)
{
    targetPosition = target;
    PrintInt(targetPosition);
    Println("");
    Step_Counter_Enable();
}

void GotoAngle(double angle) {
    StartMove(round(angle / stepSize));
}

void Step(int steps) {
    StartMove(targetPosition + steps);
}

CY_ISR(On_Lim_1) {
    Println("Hit limit switch 1");
    Step_Timer_Stop();
    Step_Counter_WriteCounter(0);
    isr_lim_1_ClearPending();
}

CY_ISR(On_Lim_2) {
    Println("Hit limit switch 2");
    Step_Timer_Stop();
    isr_lim_2_ClearPending();
}

CY_ISR(On_Fault) {
    Println("Driver fault");
    Step_Timer_Stop();
    isr_fault_ClearPending();
}

CY_ISR(On_Step) {
    int pos = Step_Counter_ReadCounter();
    
    if (E == 0) {
        if (pos == targetPosition) {
            Step_Timer_Stop();
        }
        else {
            if (targetPosition >= pos) {   
                Direction_Write(1);
                dir = 1;
            } else {
                Direction_Write(0);
                dir = -1;
            }
        }
    }
    if (E > targetPosition - pos) {
        E -= dir;
    } else if (E < E_max) {
        E += dir;
    }
    
    int new_period = CLOCK_FREQUENCY/sqrt(abs(E)*maxAcceleration/stepSize);
    
    if (CLOCK_FREQUENCY/new_period < 5000) {
        
        Step_Timer_WritePeriod(new_period);
    } else {
        Println("Step frequency capped at 5kHz, you fucked up");
    }
    isr_step_ClearPending();
}


int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */
    
    isr_lim_1_StartEx(On_Lim_1);
    isr_lim_2_StartEx(On_Lim_2);
    isr_fault_StartEx(On_Fault);
    isr_step_StartEx(On_Step);
    Step_Counter_Start();
    Step_Timer_Init(); // Init but don't start the counter
    
    DBG_UART_Start();
    
    Println("Restart");
    
    if (stepMode == 1) {
        stepSize = 360.0/200;
    }
    E_max = (int) maxVelocity*maxVelocity/stepSize/2/maxAcceleration;
    Print("E_max is ");
    PrintInt(E_max);
    Println("");
    
    for(;;)
    {
        
        int currentPosition = Step_Counter_ReadCounter();
        
        int data = DBG_UART_UartGetByte();
        if (data == RIGHT) {
            Step(dbg_step);
        } else if (data == LEFT) {
            Step(-dbg_step);
        } else if (data == UP) {
            if (dbg_step < 200) {
                dbg_step *= 2;
            } else {
                dbg_step = 200;
            }
            Print("Step is ");
            PrintInt(dbg_step);
            Println("");
        } else if (data == DOWN) {
            if (dbg_step > 1) {
                dbg_step /= 2;
            } else {
                dbg_step = 1;
            }
            Print("Step is ");

            PrintInt(dbg_step);
            Println("");
        }
    }
}

/* [] END OF FILE */
