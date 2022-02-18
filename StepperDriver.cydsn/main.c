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

double accel;
double stepSize;
int E_max;

int targetPosition = 0;
int dbg_step = 1;
int E = 0;

// position in steps
int getCurrentPosition()
{
    return Step_Counter_ReadCounter();
}

// speed in steps/sec
void setSpeed(double speed) {
    Step_Timer_WritePeriod(CLOCK_FREQUENCY/speed);
}

void AccelToTarget() {
    int pos = getCurrentPosition();
        
    if (E > targetPosition - pos) {
        E -= E > -E_max;
    } else {
        E += E < E_max;
    }
    
    Direction_Write(E >= 0);
    
    if (E != 0) {
        double new_freq = sqrt(abs(E)*accel);
        setSpeed(new_freq);
    }
    
    if (pos == targetPosition) {
        if (E == 0) {
            Enable_Write(0);
        }
    } else {
        Enable_Write(1);
    }
}
    
void StartMove(int target)
{
    targetPosition = target;
    int pos = Step_Counter_ReadCounter();
    PrintInt(targetPosition);
    Println("");
    AccelToTarget();
}

void GotoAngle(double angle) {
    StartMove(round(angle / stepSize));
}

void Step(int steps) {
    StartMove(targetPosition + steps);
}

CY_ISR(On_Lim_1) {
    Println("Hit limit switch 1");
    Enable_Write(0);
    Step_Counter_WriteCounter(0);
    isr_lim_1_ClearPending();
}

CY_ISR(On_Lim_2) {
    Println("Hit limit switch 2");
    Enable_Write(0);
    isr_lim_2_ClearPending();
}

CY_ISR(On_Fault) {
    Println("Driver fault");
    Enable_Write(0);
    isr_fault_ClearPending();
}

CY_ISR(On_Step) {
    AccelToTarget();
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
    Step_Timer_Start();
    
    DBG_UART_Start();
    
    Println("Restart");
    
    // TODO get these values from CAN init packet
    int stepMode = 1;
    double maxVelocity = 1440; // deg/s
    double maxAcceleration = 360; // deg/s/s
    
    if (stepMode == 1) {
        stepSize = 360.0/200;
    }
    
    accel = maxAcceleration/stepSize;
    E_max = (int) maxVelocity*maxVelocity/stepSize/2/maxAcceleration;
    
    
    Print("E_max is ");
    PrintInt(E_max);
    Println("");
    
    for(;;)
    {
        int data = DBG_UART_UartGetByte();
        if (data == STATUS) {
            Print(" Step period:");
            PrintInt(Step_Timer_ReadPeriod());
            Print(" Position:");
            PrintInt(Step_Counter_ReadCounter());
            Print(" E:");
            PrintInt(E);
            Println("");
        } else if (data == RIGHT) {
            Step(dbg_step);
        } else if (data == LEFT) {
            Step(-dbg_step);
        } else if (data == UP) {
            dbg_step *= 2;
            Print("Step by ");
            PrintInt(dbg_step);
            Println("");
        } else if (data == DOWN) {
            if (dbg_step > 1) {
                dbg_step /= 2;
            } else {
                dbg_step = 1;
            }
            Print("Step by ");
            PrintInt(dbg_step);
            Println("");
        }
    }
}

/* [] END OF FILE */
