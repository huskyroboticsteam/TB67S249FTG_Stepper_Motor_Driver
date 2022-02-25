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
double vel;
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

void stop() {
    Enable_Write(0);
    targetPosition = getCurrentPosition();
    E = 0;
}

// speed in steps/sec
void setSpeed(double speed) {
    Step_Timer_WritePeriod(CLOCK_FREQUENCY/speed);
}

void AccelToTarget() {
    int pos = getCurrentPosition();
        
    if (E > targetPosition - pos) {
        E -= E > -E_max;
    }
    if (E < targetPosition - pos) {
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
            Println("Arrived at Target™");
        }
    }
}
    
void StartMove(int target)
{
    targetPosition = target;
    PrintInt(targetPosition);
    Println("");
    Enable_Write(1);
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
    stop();
    
    isr_lim_1_ClearPending();
}

CY_ISR(On_Lim_2) {
    Println("Hit limit switch 2");
    stop();
    
    isr_lim_2_ClearPending();
}

CY_ISR(On_Fault) {
    Println("Driver fault");
    Step_Counter_WriteCounter(0);
    stop();
    
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
    double maxVelocity = 6000; // deg/s
    double maxAcceleration = 1000; // deg/s/s
    
    
    
    if (stepMode == 1) {
        stepSize = 360.0/200;
    }
    
    if (maxVelocity > 6000) {
        maxVelocity = 6000;
    }
    vel = maxVelocity/stepSize;
    accel = maxAcceleration/stepSize;
    
    
    E_max = vel*vel/2/accel;
    
    if (E_max == 0) {
        E_max = 1;
        accel = vel*vel;
    }
    
    
    Print("E_max is ");
    PrintInt(E_max);
    Println("");
    
    for(;;)
    {
        int data = DBG_UART_UartGetByte();
        if (data == STATUS) {
            Print("Step period:");
            PrintInt(Step_Timer_ReadPeriod());
            Print(" Timer Count:");
            PrintInt(Step_Timer_ReadCounter());
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
