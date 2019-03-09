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
LIBS:l293d
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
L GND #PWR01
U 1 1 5C72F3AF
P 2150 1800
F 0 "#PWR01" H 2150 1550 50  0001 C CNN
F 1 "GND" H 2150 1650 50  0000 C CNN
F 2 "" H 2150 1800 50  0001 C CNN
F 3 "" H 2150 1800 50  0001 C CNN
	1    2150 1800
	0    1    1    0   
$EndComp
Text GLabel 3550 1050 2    60   Input ~ 0
ardu5V
Text GLabel 2150 2850 0    60   Input ~ 0
supply12V
Text GLabel 2150 1550 0    60   Input ~ 0
m2+
Text GLabel 2150 2350 0    60   Input ~ 0
m2-
Text GLabel 3550 1550 2    60   Input ~ 0
m4-
Text GLabel 3550 2350 2    60   Input ~ 0
m4+
Text GLabel 2150 1050 0    60   Input ~ 0
en
Text GLabel 3550 2850 2    60   Input ~ 0
en
Text GLabel 2150 1300 0    60   Input ~ 0
pwm_m2
Text GLabel 2150 2600 0    60   Input ~ 0
dig_m2
Text GLabel 3550 2600 2    60   Input ~ 0
pwm_m4
Text GLabel 3550 1300 2    60   Input ~ 0
dig_m4
Text GLabel 3550 3300 2    60   Input ~ 0
ardu5V
Text GLabel 2150 5100 0    60   Input ~ 0
supply12V
Text GLabel 2150 3800 0    60   Input ~ 0
m3+
Text GLabel 2150 4600 0    60   Input ~ 0
m3-
Text GLabel 3550 3800 2    60   Input ~ 0
m1-
Text GLabel 3550 4600 2    60   Input ~ 0
m1+
Text GLabel 2150 3300 0    60   Input ~ 0
en
Text GLabel 3550 5100 2    60   Input ~ 0
en
Text GLabel 2150 3550 0    60   Input ~ 0
pwm_m3
Text GLabel 2150 4850 0    60   Input ~ 0
dig_m3
Text GLabel 3550 4850 2    60   Input ~ 0
pwm_m1
Text GLabel 3550 3550 2    60   Input ~ 0
dig_m1
$Comp
L GND #PWR02
U 1 1 5C72FE27
P 2150 6250
F 0 "#PWR02" H 2150 6000 50  0001 C CNN
F 1 "GND" H 2150 6100 50  0000 C CNN
F 2 "" H 2150 6250 50  0001 C CNN
F 3 "" H 2150 6250 50  0001 C CNN
	1    2150 6250
	0    1    1    0   
$EndComp
Text GLabel 3550 5500 2    60   Input ~ 0
ardu5V
Text GLabel 2150 7300 0    60   Input ~ 0
supply12V
Text GLabel 2150 6000 0    60   Input ~ 0
m6+
Text GLabel 2150 6800 0    60   Input ~ 0
m6-
Text GLabel 3550 6000 2    60   Input ~ 0
m5-
Text GLabel 3550 6800 2    60   Input ~ 0
m5+
Text GLabel 2150 5500 0    60   Input ~ 0
en
Text GLabel 3550 7300 2    60   Input ~ 0
en
Text GLabel 2150 5750 0    60   Input ~ 0
pwm_m6
Text GLabel 2150 7050 0    60   Input ~ 0
dig_m6
Text GLabel 3550 7050 2    60   Input ~ 0
pwm_m5
Text GLabel 3550 5750 2    60   Input ~ 0
dig_m5
Text GLabel 5950 1600 0    60   Input ~ 0
m1+
Text GLabel 5950 1700 0    60   Input ~ 0
m1-
Text GLabel 5950 2000 0    60   Input ~ 0
m2+
Text GLabel 5950 2100 0    60   Input ~ 0
m2-
Text GLabel 8150 1600 0    60   Input ~ 0
m3+
Text GLabel 8150 1700 0    60   Input ~ 0
m3-
Text GLabel 8150 2000 0    60   Input ~ 0
m4+
Text GLabel 8150 2100 0    60   Input ~ 0
m4-
Text GLabel 10450 1600 0    60   Input ~ 0
m5+
Text GLabel 10450 1700 0    60   Input ~ 0
m5-
Text GLabel 10450 2000 0    60   Input ~ 0
m6+
Text GLabel 10450 2100 0    60   Input ~ 0
m6-
Text GLabel 6450 3750 0    60   Input ~ 0
supply12V
$Comp
L GND #PWR03
U 1 1 5C73152D
P 6450 3850
F 0 "#PWR03" H 6450 3600 50  0001 C CNN
F 1 "GND" H 6300 3800 50  0000 C CNN
F 2 "" H 6450 3850 50  0001 C CNN
F 3 "" H 6450 3850 50  0001 C CNN
	1    6450 3850
	1    0    0    -1  
$EndComp
$Comp
L Screw_Terminal_01x02 J7
U 1 1 5C733FF1
P 6150 1600
F 0 "J7" H 6150 1700 50  0000 C CNN
F 1 "m1" H 6150 1400 50  0000 C CNN
F 2 "Connectors_Terminal_Blocks:TerminalBlock_Altech_AK300-2_P5.00mm" H 6150 1600 50  0001 C CNN
F 3 "" H 6150 1600 50  0001 C CNN
	1    6150 1600
	1    0    0    -1  
$EndComp
$Comp
L Screw_Terminal_01x02 J8
U 1 1 5C7344C5
P 6150 2000
F 0 "J8" H 6150 2100 50  0000 C CNN
F 1 "m2" H 6150 1800 50  0000 C CNN
F 2 "Connectors_Terminal_Blocks:TerminalBlock_Altech_AK300-2_P5.00mm" H 6150 2000 50  0001 C CNN
F 3 "" H 6150 2000 50  0001 C CNN
	1    6150 2000
	1    0    0    -1  
$EndComp
$Comp
L Screw_Terminal_01x02 J9
U 1 1 5C73460D
P 8350 1600
F 0 "J9" H 8350 1700 50  0000 C CNN
F 1 "m3" H 8350 1400 50  0000 C CNN
F 2 "Connectors_Terminal_Blocks:TerminalBlock_Altech_AK300-2_P5.00mm" H 8350 1600 50  0001 C CNN
F 3 "" H 8350 1600 50  0001 C CNN
	1    8350 1600
	1    0    0    -1  
$EndComp
$Comp
L Screw_Terminal_01x02 J10
U 1 1 5C7346D5
P 8350 2000
F 0 "J10" H 8350 2100 50  0000 C CNN
F 1 "m4" H 8350 1800 50  0000 C CNN
F 2 "Connectors_Terminal_Blocks:TerminalBlock_Altech_AK300-2_P5.00mm" H 8350 2000 50  0001 C CNN
F 3 "" H 8350 2000 50  0001 C CNN
	1    8350 2000
	1    0    0    -1  
$EndComp
$Comp
L Screw_Terminal_01x02 J11
U 1 1 5C7347B5
P 10650 1600
F 0 "J11" H 10650 1700 50  0000 C CNN
F 1 "m5" H 10650 1400 50  0000 C CNN
F 2 "Connectors_Terminal_Blocks:TerminalBlock_Altech_AK300-2_P5.00mm" H 10650 1600 50  0001 C CNN
F 3 "" H 10650 1600 50  0001 C CNN
	1    10650 1600
	1    0    0    -1  
$EndComp
$Comp
L Screw_Terminal_01x02 J12
U 1 1 5C7348D8
P 10650 2000
F 0 "J12" H 10650 2100 50  0000 C CNN
F 1 "m6" H 10650 1800 50  0000 C CNN
F 2 "Connectors_Terminal_Blocks:TerminalBlock_Altech_AK300-2_P5.00mm" H 10650 2000 50  0001 C CNN
F 3 "" H 10650 2000 50  0001 C CNN
	1    10650 2000
	1    0    0    -1  
$EndComp
$Comp
L Screw_Terminal_01x02 J14
U 1 1 5C7349E2
P 6650 3750
F 0 "J14" H 6650 3850 50  0000 C CNN
F 1 "power12v" H 6650 3550 50  0000 C CNN
F 2 "Connectors_Terminal_Blocks:TerminalBlock_Altech_AK300-2_P5.00mm" H 6650 3750 50  0001 C CNN
F 3 "" H 6650 3750 50  0001 C CNN
	1    6650 3750
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR04
U 1 1 5C73FA55
P 2150 4050
F 0 "#PWR04" H 2150 3800 50  0001 C CNN
F 1 "GND" H 2150 3900 50  0000 C CNN
F 2 "" H 2150 4050 50  0001 C CNN
F 3 "" H 2150 4050 50  0001 C CNN
	1    2150 4050
	0    1    1    0   
$EndComp
$Comp
L L293D U1
U 1 1 5C73F435
P 2850 1950
F 0 "U1" H 3050 3000 60  0000 C CNN
F 1 "L293D" H 2600 3000 60  0000 C CNN
F 2 "Housings_DIP:DIP-16_W7.62mm_Socket_LongPads" H 2850 1950 60  0001 C CNN
F 3 "" H 2850 1950 60  0001 C CNN
	1    2850 1950
	1    0    0    -1  
$EndComp
Wire Wire Line
	3550 2100 3550 1800
Wire Wire Line
	2150 2100 2150 1800
$Comp
L GND #PWR05
U 1 1 5C73F895
P 3550 1800
F 0 "#PWR05" H 3550 1550 50  0001 C CNN
F 1 "GND" H 3550 1650 50  0000 C CNN
F 2 "" H 3550 1800 50  0001 C CNN
F 3 "" H 3550 1800 50  0001 C CNN
	1    3550 1800
	0    -1   -1   0   
$EndComp
$Comp
L L293D U2
U 1 1 5C73F9A1
P 2850 4200
F 0 "U2" H 3100 5250 60  0000 C CNN
F 1 "L293D" H 2650 5250 60  0000 C CNN
F 2 "Housings_DIP:DIP-16_W7.62mm_Socket_LongPads" H 2850 4200 60  0001 C CNN
F 3 "" H 2850 4200 60  0001 C CNN
	1    2850 4200
	1    0    0    -1  
$EndComp
$Comp
L L293D U3
U 1 1 5C73FA66
P 2850 6400
F 0 "U3" H 3100 7450 60  0000 C CNN
F 1 "L293D" H 2600 7450 60  0000 C CNN
F 2 "Housings_DIP:DIP-16_W7.62mm_Socket_LongPads" H 2850 6400 60  0001 C CNN
F 3 "" H 2850 6400 60  0001 C CNN
	1    2850 6400
	1    0    0    -1  
$EndComp
Wire Wire Line
	3550 4350 3550 4050
Wire Wire Line
	2150 4350 2150 4050
$Comp
L GND #PWR06
U 1 1 5C73FF80
P 3550 4050
F 0 "#PWR06" H 3550 3800 50  0001 C CNN
F 1 "GND" H 3550 3900 50  0000 C CNN
F 2 "" H 3550 4050 50  0001 C CNN
F 3 "" H 3550 4050 50  0001 C CNN
	1    3550 4050
	0    -1   -1   0   
$EndComp
Wire Wire Line
	3550 6550 3550 6250
Wire Wire Line
	2150 6550 2150 6250
$Comp
L GND #PWR07
U 1 1 5C74071F
P 3550 6250
F 0 "#PWR07" H 3550 6000 50  0001 C CNN
F 1 "GND" H 3550 6100 50  0000 C CNN
F 2 "" H 3550 6250 50  0001 C CNN
F 3 "" H 3550 6250 50  0001 C CNN
	1    3550 6250
	0    -1   -1   0   
$EndComp
Text GLabel 4950 1550 0    60   Input ~ 0
pwm_m1
Text GLabel 4950 1650 0    60   Input ~ 0
dig_m1
Text GLabel 4950 2100 0    60   Input ~ 0
pwm_m2
Text GLabel 4950 2200 0    60   Input ~ 0
dig_m2
$Comp
L GND #PWR08
U 1 1 5C741699
P 5300 3900
F 0 "#PWR08" H 5300 3650 50  0001 C CNN
F 1 "GND" V 5300 3700 50  0000 C CNN
F 2 "" H 5300 3900 50  0001 C CNN
F 3 "" H 5300 3900 50  0001 C CNN
	1    5300 3900
	0    1    1    0   
$EndComp
Text GLabel 5300 3700 0    60   Input ~ 0
en
$Comp
L Conn_01x02 J1
U 1 1 5C742255
P 5150 1550
F 0 "J1" H 5150 1650 50  0000 C CNN
F 1 "Conn_01x02" H 5150 1350 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x02_Pitch2.00mm" H 5150 1550 50  0001 C CNN
F 3 "" H 5150 1550 50  0001 C CNN
	1    5150 1550
	1    0    0    -1  
$EndComp
$Comp
L Conn_01x02 J2
U 1 1 5C742362
P 5150 2100
F 0 "J2" H 5150 2200 50  0000 C CNN
F 1 "Conn_01x02" H 5150 1900 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x02_Pitch2.00mm" H 5150 2100 50  0001 C CNN
F 3 "" H 5150 2100 50  0001 C CNN
	1    5150 2100
	1    0    0    -1  
$EndComp
Text GLabel 7100 1550 0    60   Input ~ 0
pwm_m3
Text GLabel 7100 1650 0    60   Input ~ 0
dig_m3
Text GLabel 7100 2100 0    60   Input ~ 0
pwm_m4
Text GLabel 7100 2200 0    60   Input ~ 0
dig_m4
$Comp
L Conn_01x02 J3
U 1 1 5C7427DD
P 7300 1550
F 0 "J3" H 7300 1650 50  0000 C CNN
F 1 "Conn_01x02" H 7300 1350 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x02_Pitch2.00mm" H 7300 1550 50  0001 C CNN
F 3 "" H 7300 1550 50  0001 C CNN
	1    7300 1550
	1    0    0    -1  
$EndComp
$Comp
L Conn_01x02 J4
U 1 1 5C7427E4
P 7300 2100
F 0 "J4" H 7300 2200 50  0000 C CNN
F 1 "Conn_01x02" H 7300 1900 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x02_Pitch2.00mm" H 7300 2100 50  0001 C CNN
F 3 "" H 7300 2100 50  0001 C CNN
	1    7300 2100
	1    0    0    -1  
$EndComp
Text GLabel 9400 1600 0    60   Input ~ 0
pwm_m5
Text GLabel 9400 1700 0    60   Input ~ 0
dig_m5
Text GLabel 9400 2150 0    60   Input ~ 0
pwm_m6
Text GLabel 9400 2250 0    60   Input ~ 0
dig_m6
$Comp
L Conn_01x02 J5
U 1 1 5C742D7E
P 9600 1600
F 0 "J5" H 9600 1700 50  0000 C CNN
F 1 "Conn_01x02" H 9600 1400 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x02_Pitch2.00mm" H 9600 1600 50  0001 C CNN
F 3 "" H 9600 1600 50  0001 C CNN
	1    9600 1600
	1    0    0    -1  
$EndComp
$Comp
L Conn_01x02 J6
U 1 1 5C742D85
P 9600 2150
F 0 "J6" H 9600 2250 50  0000 C CNN
F 1 "Conn_01x02" H 9600 1950 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x02_Pitch2.00mm" H 9600 2150 50  0001 C CNN
F 3 "" H 9600 2150 50  0001 C CNN
	1    9600 2150
	1    0    0    -1  
$EndComp
$Comp
L Conn_01x03 J13
U 1 1 5C742ECF
P 5500 3800
F 0 "J13" H 5500 4000 50  0000 C CNN
F 1 "Conn_01x03" H 5500 3600 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x03_Pitch2.00mm" H 5500 3800 50  0001 C CNN
F 3 "" H 5500 3800 50  0001 C CNN
	1    5500 3800
	1    0    0    -1  
$EndComp
Text GLabel 5300 3800 0    60   Input ~ 0
ardu5V
$Comp
L Conn_01x01 J15
U 1 1 5C76A06A
P 7750 5300
F 0 "J15" H 7750 5400 50  0000 C CNN
F 1 "Conn_01x01" H 7750 5200 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x01_Pitch2.00mm" H 7750 5300 50  0001 C CNN
F 3 "" H 7750 5300 50  0001 C CNN
	1    7750 5300
	1    0    0    -1  
$EndComp
Text Notes 6500 5600 0    60   ~ 0
These connectors are used to 'bridge' with wires bc we dont have 2 layers
Text GLabel 7550 5300 0    60   Input ~ 0
ardu5V
$Comp
L Conn_01x01 J16
U 1 1 5C79696D
P 8900 5300
F 0 "J16" H 8900 5400 50  0000 C CNN
F 1 "Conn_01x01" H 8900 5200 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x01_Pitch2.00mm" H 8900 5300 50  0001 C CNN
F 3 "" H 8900 5300 50  0001 C CNN
	1    8900 5300
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR09
U 1 1 5C7978A8
P 8700 5300
F 0 "#PWR09" H 8700 5050 50  0001 C CNN
F 1 "GND" H 8700 5150 50  0000 C CNN
F 2 "" H 8700 5300 50  0001 C CNN
F 3 "" H 8700 5300 50  0001 C CNN
	1    8700 5300
	0    1    1    0   
$EndComp
$EndSCHEMATC
