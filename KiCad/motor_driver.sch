EESchema Schematic File Version 2
LIBS:power
LIBS:device
LIBS:switches
LIBS:relays
LIBS:motors
LIBS:transistors
LIBS:conn
LIBS:linear
LIBS:regul
LIBS:74xx
LIBS:cmos4000
LIBS:adc-dac
LIBS:memory
LIBS:xilinx
LIBS:microcontrollers
LIBS:dsp
LIBS:microchip
LIBS:analog_switches
LIBS:motorola
LIBS:texas
LIBS:intel
LIBS:audio
LIBS:interface
LIBS:digital-audio
LIBS:philips
LIBS:display
LIBS:cypress
LIBS:siliconi
LIBS:opto
LIBS:atmel
LIBS:contrib
LIBS:valves
LIBS:L293D
LIBS:motor_driver-cache
EELAYER 25 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L L293D U1
U 1 1 5C72E20E
P -6300 9050
F 0 "U1" H -6250 9100 60  0000 C CNN
F 1 "L293D" H 2700 17050 60  0000 C CNN
F 2 "Housings_DIP:DIP-16_W7.62mm_Socket_LongPads" H -6300 9050 60  0001 C CNN
F 3 "" H -6300 9050 60  0001 C CNN
	1    -6300 9050
	1    0    0    -1  
$EndComp
Wire Wire Line
	2100 1950 2100 1800
Wire Wire Line
	3600 1950 3600 1800
Wire Wire Line
	2100 1800 1800 1800
Wire Wire Line
	3600 1800 3900 1800
$Comp
L GND #PWR01
U 1 1 5C72F3AF
P 1800 1800
F 0 "#PWR01" H 1800 1550 50  0001 C CNN
F 1 "GND" H 1800 1650 50  0000 C CNN
F 2 "" H 1800 1800 50  0001 C CNN
F 3 "" H 1800 1800 50  0001 C CNN
	1    1800 1800
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR02
U 1 1 5C72F3C9
P 3900 1800
F 0 "#PWR02" H 3900 1550 50  0001 C CNN
F 1 "GND" H 3900 1650 50  0000 C CNN
F 2 "" H 3900 1800 50  0001 C CNN
F 3 "" H 3900 1800 50  0001 C CNN
	1    3900 1800
	1    0    0    -1  
$EndComp
Text GLabel 3600 1350 2    60   Input ~ 0
ardu5V
Text GLabel 2100 2400 0    60   Input ~ 0
supply12V
Text GLabel 2100 1650 0    60   Input ~ 0
m1+
Text GLabel 2100 2100 0    60   Input ~ 0
m1-
Text GLabel 3600 1650 2    60   Input ~ 0
m2+
Text GLabel 3600 2100 2    60   Input ~ 0
m2-
Text GLabel 2100 1350 0    60   Input ~ 0
en
Text GLabel 3600 2400 2    60   Input ~ 0
en
Text GLabel 2100 1500 0    60   Input ~ 0
pwm_m1
Text GLabel 2100 2250 0    60   Input ~ 0
dig_m1
Text GLabel 3600 2250 2    60   Input ~ 0
pwm_m2
Text GLabel 3600 1500 2    60   Input ~ 0
dig_m2
$Comp
L L293D U2
U 2 1 5C72FDB9
P -6250 11150
F 0 "U2" V -6200 11200 60  0000 C CNN
F 1 "L293D" H 2750 19150 60  0000 C CNN
F 2 "Housings_DIP:DIP-16_W7.62mm_Socket_LongPads" H -6250 11150 60  0001 C CNN
F 3 "" H -6250 11150 60  0001 C CNN
	2    -6250 11150
	1    0    0    -1  
$EndComp
Wire Wire Line
	2150 4050 2150 3900
Wire Wire Line
	3650 4050 3650 3900
Wire Wire Line
	2150 3900 1850 3900
Wire Wire Line
	3650 3900 3950 3900
$Comp
L GND #PWR03
U 1 1 5C72FDC4
P 1850 3900
F 0 "#PWR03" H 1850 3650 50  0001 C CNN
F 1 "GND" H 1850 3750 50  0000 C CNN
F 2 "" H 1850 3900 50  0001 C CNN
F 3 "" H 1850 3900 50  0001 C CNN
	1    1850 3900
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR04
U 1 1 5C72FDCA
P 3950 3900
F 0 "#PWR04" H 3950 3650 50  0001 C CNN
F 1 "GND" H 3950 3750 50  0000 C CNN
F 2 "" H 3950 3900 50  0001 C CNN
F 3 "" H 3950 3900 50  0001 C CNN
	1    3950 3900
	1    0    0    -1  
$EndComp
Text GLabel 3650 3450 2    60   Input ~ 0
ardu5V
Text GLabel 2150 4500 0    60   Input ~ 0
supply12V
Text GLabel 2150 3750 0    60   Input ~ 0
m3+
Text GLabel 2150 4200 0    60   Input ~ 0
m3-
Text GLabel 3650 3750 2    60   Input ~ 0
m4+
Text GLabel 3650 4200 2    60   Input ~ 0
m4-
Text GLabel 2150 3450 0    60   Input ~ 0
en
Text GLabel 3650 4500 2    60   Input ~ 0
en
Text GLabel 2150 3600 0    60   Input ~ 0
pwm_m3
Text GLabel 2150 4350 0    60   Input ~ 0
dig_m3
Text GLabel 3650 4350 2    60   Input ~ 0
pwm_m4
Text GLabel 3650 3600 2    60   Input ~ 0
dig_m4
$Comp
L L293D U3
U 3 1 5C72FE1C
P -6200 13450
F 0 "U3" H -6150 13500 60  0000 C CNN
F 1 "L293D" H 2800 21450 60  0000 C CNN
F 2 "Housings_DIP:DIP-16_W7.62mm_Socket_LongPads" H -6200 13450 60  0001 C CNN
F 3 "" H -6200 13450 60  0001 C CNN
	3    -6200 13450
	1    0    0    -1  
$EndComp
Wire Wire Line
	2200 6350 2200 6200
Wire Wire Line
	3700 6350 3700 6200
Wire Wire Line
	2200 6200 1900 6200
Wire Wire Line
	3700 6200 4000 6200
$Comp
L GND #PWR05
U 1 1 5C72FE27
P 1900 6200
F 0 "#PWR05" H 1900 5950 50  0001 C CNN
F 1 "GND" H 1900 6050 50  0000 C CNN
F 2 "" H 1900 6200 50  0001 C CNN
F 3 "" H 1900 6200 50  0001 C CNN
	1    1900 6200
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR06
U 1 1 5C72FE2D
P 4000 6200
F 0 "#PWR06" H 4000 5950 50  0001 C CNN
F 1 "GND" H 4000 6050 50  0000 C CNN
F 2 "" H 4000 6200 50  0001 C CNN
F 3 "" H 4000 6200 50  0001 C CNN
	1    4000 6200
	1    0    0    -1  
$EndComp
Text GLabel 3700 5750 2    60   Input ~ 0
ardu5V
Text GLabel 2200 6800 0    60   Input ~ 0
supply12V
Text GLabel 2200 6050 0    60   Input ~ 0
m5+
Text GLabel 2200 6500 0    60   Input ~ 0
m5-
Text GLabel 3700 6050 2    60   Input ~ 0
m6+
Text GLabel 3700 6500 2    60   Input ~ 0
m6-
Text GLabel 2200 5750 0    60   Input ~ 0
en
Text GLabel 3700 6800 2    60   Input ~ 0
en
Text GLabel 2200 5900 0    60   Input ~ 0
pwm_m5
Text GLabel 2200 6650 0    60   Input ~ 0
dig_m5
Text GLabel 3700 6650 2    60   Input ~ 0
pwm_m6
Text GLabel 3700 5900 2    60   Input ~ 0
dig_m6
$Comp
L Conn_01x02 J1
U 1 1 5C72FEA4
P 6150 1300
F 0 "J1" H 6150 1400 50  0000 C CNN
F 1 "sig_m1" H 6150 1100 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x02_Pitch2.00mm" H 6150 1300 50  0001 C CNN
F 3 "" H 6150 1300 50  0001 C CNN
	1    6150 1300
	1    0    0    -1  
$EndComp
$Comp
L Conn_01x02 J2
U 1 1 5C72FED7
P 6150 1700
F 0 "J2" H 6150 1800 50  0000 C CNN
F 1 "sig_m2" H 6150 1500 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x02_Pitch2.00mm" H 6150 1700 50  0001 C CNN
F 3 "" H 6150 1700 50  0001 C CNN
	1    6150 1700
	1    0    0    -1  
$EndComp
Text GLabel 5950 1300 0    60   Input ~ 0
pwm_m1
Text GLabel 5950 1400 0    60   Input ~ 0
dig_m1
Text GLabel 5950 1700 0    60   Input ~ 0
pwm_m2
Text GLabel 5950 1800 0    60   Input ~ 0
dig_m2
Text GLabel 7000 1300 0    60   Input ~ 0
m1+
Text GLabel 7000 1400 0    60   Input ~ 0
m1-
Text GLabel 7000 1700 0    60   Input ~ 0
m2+
Text GLabel 7000 1800 0    60   Input ~ 0
m2-
$Comp
L Conn_01x02 J3
U 1 1 5C7303DC
P 6250 3400
F 0 "J3" H 6250 3500 50  0000 C CNN
F 1 "sig_m3" H 6250 3200 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x02_Pitch2.00mm" H 6250 3400 50  0001 C CNN
F 3 "" H 6250 3400 50  0001 C CNN
	1    6250 3400
	1    0    0    -1  
$EndComp
$Comp
L Conn_01x02 J4
U 1 1 5C7303E3
P 6250 3800
F 0 "J4" H 6250 3900 50  0000 C CNN
F 1 "sig_m4" H 6250 3600 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x02_Pitch2.00mm" H 6250 3800 50  0001 C CNN
F 3 "" H 6250 3800 50  0001 C CNN
	1    6250 3800
	1    0    0    -1  
$EndComp
Text GLabel 6050 3400 0    60   Input ~ 0
pwm_m3
Text GLabel 6050 3500 0    60   Input ~ 0
dig_m3
Text GLabel 6050 3800 0    60   Input ~ 0
pwm_m4
Text GLabel 6050 3900 0    60   Input ~ 0
dig_m4
Text GLabel 7100 3400 0    60   Input ~ 0
m3+
Text GLabel 7100 3500 0    60   Input ~ 0
m3-
Text GLabel 7100 3800 0    60   Input ~ 0
m4+
Text GLabel 7100 3900 0    60   Input ~ 0
m4-
$Comp
L Conn_01x02 J5
U 1 1 5C7305CB
P 6300 5600
F 0 "J5" H 6300 5700 50  0000 C CNN
F 1 "sig_m5" H 6300 5400 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x02_Pitch2.00mm" H 6300 5600 50  0001 C CNN
F 3 "" H 6300 5600 50  0001 C CNN
	1    6300 5600
	1    0    0    -1  
$EndComp
$Comp
L Conn_01x02 J6
U 1 1 5C7305D2
P 6300 6000
F 0 "J6" H 6300 6100 50  0000 C CNN
F 1 "sig_m6" H 6300 5800 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x02_Pitch2.00mm" H 6300 6000 50  0001 C CNN
F 3 "" H 6300 6000 50  0001 C CNN
	1    6300 6000
	1    0    0    -1  
$EndComp
Text GLabel 6100 5600 0    60   Input ~ 0
pwm_m5
Text GLabel 6100 5700 0    60   Input ~ 0
dig_m5
Text GLabel 6100 6000 0    60   Input ~ 0
pwm_m6
Text GLabel 6100 6100 0    60   Input ~ 0
dig_m6
Text GLabel 7150 5600 0    60   Input ~ 0
m5+
Text GLabel 7150 5700 0    60   Input ~ 0
m5-
Text GLabel 7150 6000 0    60   Input ~ 0
m6+
Text GLabel 7150 6100 0    60   Input ~ 0
m6-
Text GLabel 9250 2550 0    60   Input ~ 0
ardu5V
$Comp
L GND #PWR07
U 1 1 5C730EC2
P 9250 2650
F 0 "#PWR07" H 9250 2400 50  0001 C CNN
F 1 "GND" H 9100 2600 50  0000 C CNN
F 2 "" H 9250 2650 50  0001 C CNN
F 3 "" H 9250 2650 50  0001 C CNN
	1    9250 2650
	1    0    0    -1  
$EndComp
$Comp
L Conn_01x03 J13
U 1 1 5C731181
P 9450 2550
F 0 "J13" H 9450 2750 50  0000 C CNN
F 1 "Conn_01x03" H 9600 2350 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x03_Pitch2.00mm" H 9450 2550 50  0001 C CNN
F 3 "" H 9450 2550 50  0001 C CNN
	1    9450 2550
	1    0    0    -1  
$EndComp
Text GLabel 9250 2450 0    60   Input ~ 0
en
Text GLabel 9450 4750 0    60   Input ~ 0
supply12V
$Comp
L GND #PWR08
U 1 1 5C73152D
P 9450 4850
F 0 "#PWR08" H 9450 4600 50  0001 C CNN
F 1 "GND" H 9300 4800 50  0000 C CNN
F 2 "" H 9450 4850 50  0001 C CNN
F 3 "" H 9450 4850 50  0001 C CNN
	1    9450 4850
	1    0    0    -1  
$EndComp
$Comp
L Screw_Terminal_01x02 J7
U 1 1 5C733FF1
P 7200 1300
F 0 "J7" H 7200 1400 50  0000 C CNN
F 1 "m1" H 7200 1100 50  0000 C CNN
F 2 "Connectors_Terminal_Blocks:TerminalBlock_Altech_AK300-2_P5.00mm" H 7200 1300 50  0001 C CNN
F 3 "" H 7200 1300 50  0001 C CNN
	1    7200 1300
	1    0    0    -1  
$EndComp
$Comp
L Screw_Terminal_01x02 J8
U 1 1 5C7344C5
P 7200 1700
F 0 "J8" H 7200 1800 50  0000 C CNN
F 1 "m2" H 7200 1500 50  0000 C CNN
F 2 "Connectors_Terminal_Blocks:TerminalBlock_Altech_AK300-2_P5.00mm" H 7200 1700 50  0001 C CNN
F 3 "" H 7200 1700 50  0001 C CNN
	1    7200 1700
	1    0    0    -1  
$EndComp
$Comp
L Screw_Terminal_01x02 J9
U 1 1 5C73460D
P 7300 3400
F 0 "J9" H 7300 3500 50  0000 C CNN
F 1 "m3" H 7300 3200 50  0000 C CNN
F 2 "Connectors_Terminal_Blocks:TerminalBlock_Altech_AK300-2_P5.00mm" H 7300 3400 50  0001 C CNN
F 3 "" H 7300 3400 50  0001 C CNN
	1    7300 3400
	1    0    0    -1  
$EndComp
$Comp
L Screw_Terminal_01x02 J10
U 1 1 5C7346D5
P 7300 3800
F 0 "J10" H 7300 3900 50  0000 C CNN
F 1 "m4" H 7300 3600 50  0000 C CNN
F 2 "Connectors_Terminal_Blocks:TerminalBlock_Altech_AK300-2_P5.00mm" H 7300 3800 50  0001 C CNN
F 3 "" H 7300 3800 50  0001 C CNN
	1    7300 3800
	1    0    0    -1  
$EndComp
$Comp
L Screw_Terminal_01x02 J11
U 1 1 5C7347B5
P 7350 5600
F 0 "J11" H 7350 5700 50  0000 C CNN
F 1 "m5" H 7350 5400 50  0000 C CNN
F 2 "Connectors_Terminal_Blocks:TerminalBlock_Altech_AK300-2_P5.00mm" H 7350 5600 50  0001 C CNN
F 3 "" H 7350 5600 50  0001 C CNN
	1    7350 5600
	1    0    0    -1  
$EndComp
$Comp
L Screw_Terminal_01x02 J12
U 1 1 5C7348D8
P 7350 6000
F 0 "J12" H 7350 6100 50  0000 C CNN
F 1 "m6" H 7350 5800 50  0000 C CNN
F 2 "Connectors_Terminal_Blocks:TerminalBlock_Altech_AK300-2_P5.00mm" H 7350 6000 50  0001 C CNN
F 3 "" H 7350 6000 50  0001 C CNN
	1    7350 6000
	1    0    0    -1  
$EndComp
$Comp
L Screw_Terminal_01x02 J14
U 1 1 5C7349E2
P 9650 4750
F 0 "J14" H 9650 4850 50  0000 C CNN
F 1 "power12v" H 9650 4550 50  0000 C CNN
F 2 "Connectors_Terminal_Blocks:TerminalBlock_Altech_AK300-2_P5.00mm" H 9650 4750 50  0001 C CNN
F 3 "" H 9650 4750 50  0001 C CNN
	1    9650 4750
	1    0    0    -1  
$EndComp
$EndSCHEMATC
