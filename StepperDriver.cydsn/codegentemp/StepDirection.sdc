# THIS FILE IS AUTOMATICALLY GENERATED
# Project: C:\Users\casey\Desktop\Robotics Stuff\TB67S249FTG_Stepper_Motor_Driver\StepDirection.cydsn\StepDirection.cyprj
# Date: Sat, 05 Feb 2022 22:16:06 GMT
#set_units -time ns
create_clock -name {DBG_UART_SCBCLK(FFB)} -period 729.16666666666663 -waveform {0 364.583333333333} [list [get_pins {ClockBlock/ff_div_2}]]
create_clock -name {CyRouted1} -period 20.833333333333332 -waveform {0 10.4166666666667} [list [get_pins {ClockBlock/dsi_in_0}]]
create_clock -name {CyILO} -period 31250 -waveform {0 15625} [list [get_pins {ClockBlock/ilo}]]
create_clock -name {CyLFClk} -period 31250 -waveform {0 15625} [list [get_pins {ClockBlock/lfclk}]]
create_clock -name {CyIMO} -period 20.833333333333332 -waveform {0 10.4166666666667} [list [get_pins {ClockBlock/imo}]]
create_clock -name {CyHFClk} -period 20.833333333333332 -waveform {0 10.4166666666667} [list [get_pins {ClockBlock/hfclk}]]
create_clock -name {CySysClk} -period 20.833333333333332 -waveform {0 10.4166666666667} [list [get_pins {ClockBlock/sysclk}]]
create_generated_clock -name {DBG_UART_SCBCLK} -source [get_pins {ClockBlock/hfclk}] -edges {1 35 71} [list]
create_generated_clock -name {BUS_CLK_1} -source [get_pins {ClockBlock/hfclk}] -edges {1 49 97} [list [get_pins {ClockBlock/udb_div_0}]]

set_false_path -from [get_pins {__ONE__/q}]

# Component constraints for C:\Users\casey\Desktop\Robotics Stuff\TB67S249FTG_Stepper_Motor_Driver\StepDirection.cydsn\TopDesign\TopDesign.cysch
# Project: C:\Users\casey\Desktop\Robotics Stuff\TB67S249FTG_Stepper_Motor_Driver\StepDirection.cydsn\StepDirection.cyprj
# Date: Sat, 05 Feb 2022 22:15:59 GMT