# THIS FILE IS AUTOMATICALLY GENERATED
# Project: C:\Users\casey\Desktop\Robotics Stuff\TB67S249FTG_Stepper_Motor_Driver\StepperDriver.cydsn\StepperDriver.cyprj
# Date: Fri, 18 Feb 2022 03:32:04 GMT
#set_units -time ns
create_clock -name {DBG_UART_SCBCLK(FFB)} -period 729.16666666666663 -waveform {0 364.583333333333} [list [get_pins {ClockBlock/ff_div_2}]]
create_clock -name {CyRouted1} -period 20.833333333333332 -waveform {0 10.4166666666667} [list [get_pins {ClockBlock/dsi_in_0}]]
create_clock -name {CyILO} -period 31250 -waveform {0 15625} [list [get_pins {ClockBlock/ilo}]]
create_clock -name {CyLFClk} -period 31250 -waveform {0 15625} [list [get_pins {ClockBlock/lfclk}]]
create_clock -name {CyIMO} -period 20.833333333333332 -waveform {0 10.4166666666667} [list [get_pins {ClockBlock/imo}]]
create_clock -name {CyHFClk} -period 20.833333333333332 -waveform {0 10.4166666666667} [list [get_pins {ClockBlock/hfclk}]]
create_clock -name {CySysClk} -period 20.833333333333332 -waveform {0 10.4166666666667} [list [get_pins {ClockBlock/sysclk}]]
create_generated_clock -name {StepClk} -source [get_pins {ClockBlock/hfclk}] -edges {1 25 49} [list [get_pins {ClockBlock/udb_div_0}]]
create_generated_clock -name {DBG_UART_SCBCLK} -source [get_pins {ClockBlock/hfclk}] -edges {1 35 71} [list]

set_false_path -from [get_pins {__ONE__/q}]

# Component constraints for C:\Users\casey\Desktop\Robotics Stuff\TB67S249FTG_Stepper_Motor_Driver\StepperDriver.cydsn\TopDesign\TopDesign.cysch
# Project: C:\Users\casey\Desktop\Robotics Stuff\TB67S249FTG_Stepper_Motor_Driver\StepperDriver.cydsn\StepperDriver.cyprj
# Date: Fri, 18 Feb 2022 03:31:58 GMT
