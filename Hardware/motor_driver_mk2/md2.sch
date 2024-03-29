EESchema Schematic File Version 2
LIBS:l293d
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
LIBS:md2-cache
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
U 1 1 5C7FE768
P 3750 1950
F 0 "U1" H 3700 3100 60  0000 C CNN
F 1 "L293D" H 3600 3200 60  0000 C CNN
F 2 "Housings_DIP:DIP-16_W7.62mm_LongPads" H 3750 1950 60  0001 C CNN
F 3 "" H 3750 1950 60  0001 C CNN
	1    3750 1950
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR01
U 1 1 5C7FE868
P 4450 1950
F 0 "#PWR01" H 4450 1700 50  0001 C CNN
F 1 "GND" H 4450 1800 50  0000 C CNN
F 2 "" H 4450 1950 50  0001 C CNN
F 3 "" H 4450 1950 50  0001 C CNN
	1    4450 1950
	0    -1   -1   0   
$EndComp
$Comp
L GND #PWR02
U 1 1 5C7FE87E
P 3050 1950
F 0 "#PWR02" H 3050 1700 50  0001 C CNN
F 1 "GND" H 3050 1800 50  0000 C CNN
F 2 "" H 3050 1950 50  0001 C CNN
F 3 "" H 3050 1950 50  0001 C CNN
	1    3050 1950
	0    1    1    0   
$EndComp
$Comp
L Screw_Terminal_01x02 J5
U 1 1 5C7FE896
P 4850 2000
F 0 "J5" H 4850 2100 50  0000 C CNN
F 1 "M2" H 4850 1800 50  0000 C CNN
F 2 "Connectors_Terminal_Blocks:TerminalBlock_Altech_AK300-2_P5.00mm" H 4850 2000 50  0001 C CNN
F 3 "" H 4850 2000 50  0001 C CNN
	1    4850 2000
	-1   0    0    1   
$EndComp
$Comp
L Screw_Terminal_01x02 J2
U 1 1 5C7FE8CB
P 2650 1900
F 0 "J2" H 2650 2000 50  0000 C CNN
F 1 "M1" H 2650 1700 50  0000 C CNN
F 2 "Connectors_Terminal_Blocks:TerminalBlock_Altech_AK300-2_P5.00mm" H 2650 1900 50  0001 C CNN
F 3 "" H 2650 1900 50  0001 C CNN
	1    2650 1900
	1    0    0    -1  
$EndComp
$Comp
L Conn_01x03_Male J1
U 1 1 5C7FE9E3
P 1350 1950
F 0 "J1" H 1350 2150 50  0000 C CNN
F 1 "mode&en M1" H 1350 1750 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x03_Pitch2.54mm" H 1350 1950 50  0001 C CNN
F 3 "" H 1350 1950 50  0001 C CNN
	1    1350 1950
	1    0    0    -1  
$EndComp
$Comp
L Conn_01x03_Male J6
U 1 1 5C7FEA88
P 6100 1950
F 0 "J6" H 6100 2150 50  0000 C CNN
F 1 "mode&en M2" H 6100 1750 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x03_Pitch2.54mm" H 6100 1950 50  0001 C CNN
F 3 "" H 6100 1950 50  0001 C CNN
	1    6100 1950
	-1   0    0    1   
$EndComp
Wire Wire Line
	3050 1800 3050 2100
Connection ~ 3050 1950
Wire Wire Line
	4450 1800 4450 2100
Connection ~ 4450 1950
Wire Wire Line
	4450 2600 5600 2600
Wire Wire Line
	5600 2600 5600 1950
Wire Wire Line
	5600 1950 5900 1950
Wire Wire Line
	5900 2050 5900 2850
Wire Wire Line
	5900 2850 4450 2850
Wire Wire Line
	1550 1850 1550 1050
Wire Wire Line
	1550 1050 3050 1050
Wire Wire Line
	3050 1300 1800 1300
Wire Wire Line
	1800 1300 1800 1950
Wire Wire Line
	1800 1950 1550 1950
Wire Wire Line
	1550 2050 1800 2050
Wire Wire Line
	2450 1550 3050 1550
Wire Wire Line
	2450 2350 3050 2350
Wire Wire Line
	1800 2050 1800 2600
Wire Wire Line
	1800 2600 3050 2600
Wire Wire Line
	4450 1550 5050 1550
Wire Wire Line
	4450 2350 5050 2350
Wire Wire Line
	5900 1850 5600 1850
Wire Wire Line
	5600 1850 5600 1300
Wire Wire Line
	5600 1300 4450 1300
Text GLabel 4450 1050 2    60   Input ~ 0
ardu5v
Text GLabel 3050 2850 0    60   Input ~ 0
supply
$Comp
L Conn_01x02_Male J3
U 1 1 5C7FEE1F
P 2500 4100
F 0 "J3" H 2450 4050 50  0000 C CNN
F 1 "Logic supply voltage" H 2750 4250 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x02_Pitch2.54mm" H 2500 4100 50  0001 C CNN
F 3 "" H 2500 4100 50  0001 C CNN
	1    2500 4100
	1    0    0    -1  
$EndComp
Text GLabel 2700 4100 2    60   Input ~ 0
ardu5v
$Comp
L GND #PWR03
U 1 1 5C7FEEA6
P 2700 4200
F 0 "#PWR03" H 2700 3950 50  0001 C CNN
F 1 "GND" H 2700 4050 50  0000 C CNN
F 2 "" H 2700 4200 50  0001 C CNN
F 3 "" H 2700 4200 50  0001 C CNN
	1    2700 4200
	1    0    0    -1  
$EndComp
$Comp
L Screw_Terminal_01x02 J4
U 1 1 5C7FEFEB
P 4100 4100
F 0 "J4" H 4250 4050 50  0000 C CNN
F 1 "Power supply voltage" H 3900 4250 50  0000 C CNN
F 2 "Connectors_Terminal_Blocks:TerminalBlock_Altech_AK300-2_P5.00mm" H 4100 4100 50  0001 C CNN
F 3 "" H 4100 4100 50  0001 C CNN
	1    4100 4100
	1    0    0    -1  
$EndComp
Text GLabel 3900 4100 0    60   Input ~ 0
supply
$Comp
L GND #PWR04
U 1 1 5C7FF184
P 3900 4200
F 0 "#PWR04" H 3900 3950 50  0001 C CNN
F 1 "GND" H 3900 4050 50  0000 C CNN
F 2 "" H 3900 4200 50  0001 C CNN
F 3 "" H 3900 4200 50  0001 C CNN
	1    3900 4200
	1    0    0    -1  
$EndComp
$Comp
L L293D U2
U 1 1 5C7FFAA2
P 3750 6200
F 0 "U2" H 3700 7350 60  0000 C CNN
F 1 "L293D" H 3600 7450 60  0000 C CNN
F 2 "Housings_DIP:DIP-16_W7.62mm_LongPads" H 3750 6200 60  0001 C CNN
F 3 "" H 3750 6200 60  0001 C CNN
	1    3750 6200
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR05
U 1 1 5C7FFAA9
P 4450 6200
F 0 "#PWR05" H 4450 5950 50  0001 C CNN
F 1 "GND" H 4450 6050 50  0000 C CNN
F 2 "" H 4450 6200 50  0001 C CNN
F 3 "" H 4450 6200 50  0001 C CNN
	1    4450 6200
	0    -1   -1   0   
$EndComp
$Comp
L GND #PWR06
U 1 1 5C7FFAAF
P 3050 6200
F 0 "#PWR06" H 3050 5950 50  0001 C CNN
F 1 "GND" H 3050 6050 50  0000 C CNN
F 2 "" H 3050 6200 50  0001 C CNN
F 3 "" H 3050 6200 50  0001 C CNN
	1    3050 6200
	0    1    1    0   
$EndComp
$Comp
L Screw_Terminal_01x02 J9
U 1 1 5C7FFAB5
P 4850 6250
F 0 "J9" H 4850 6350 50  0000 C CNN
F 1 "M2" H 4850 6050 50  0000 C CNN
F 2 "Connectors_Terminal_Blocks:TerminalBlock_Altech_AK300-2_P5.00mm" H 4850 6250 50  0001 C CNN
F 3 "" H 4850 6250 50  0001 C CNN
	1    4850 6250
	-1   0    0    1   
$EndComp
$Comp
L Screw_Terminal_01x02 J8
U 1 1 5C7FFABC
P 2600 6150
F 0 "J8" H 2600 6250 50  0000 C CNN
F 1 "M1" H 2600 5950 50  0000 C CNN
F 2 "Connectors_Terminal_Blocks:TerminalBlock_Altech_AK300-2_P5.00mm" H 2600 6150 50  0001 C CNN
F 3 "" H 2600 6150 50  0001 C CNN
	1    2600 6150
	1    0    0    -1  
$EndComp
$Comp
L Conn_01x03_Male J7
U 1 1 5C7FFAC3
P 1350 6200
F 0 "J7" H 1350 6400 50  0000 C CNN
F 1 "mode&en M1" H 1350 6000 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x03_Pitch2.54mm" H 1350 6200 50  0001 C CNN
F 3 "" H 1350 6200 50  0001 C CNN
	1    1350 6200
	1    0    0    -1  
$EndComp
$Comp
L Conn_01x03_Male J11
U 1 1 5C7FFACA
P 6100 6200
F 0 "J11" H 6100 6400 50  0000 C CNN
F 1 "mode&en M2" H 6100 6000 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x03_Pitch2.54mm" H 6100 6200 50  0001 C CNN
F 3 "" H 6100 6200 50  0001 C CNN
	1    6100 6200
	-1   0    0    1   
$EndComp
Wire Wire Line
	3050 6050 3050 6350
Connection ~ 3050 6200
Wire Wire Line
	4450 6050 4450 6350
Connection ~ 4450 6200
Wire Wire Line
	4450 6850 5600 6850
Wire Wire Line
	5600 6850 5600 6200
Wire Wire Line
	5600 6200 5900 6200
Wire Wire Line
	5900 6300 5900 7100
Wire Wire Line
	5900 7100 4450 7100
Wire Wire Line
	1550 6100 1550 5300
Wire Wire Line
	1550 5300 3050 5300
Wire Wire Line
	3050 5550 1800 5550
Wire Wire Line
	1800 5550 1800 6200
Wire Wire Line
	1800 6200 1550 6200
Wire Wire Line
	1550 6300 1800 6300
Wire Wire Line
	2400 5800 3050 5800
Wire Wire Line
	2400 6600 3050 6600
Wire Wire Line
	1800 6300 1800 6850
Wire Wire Line
	1800 6850 3050 6850
Wire Wire Line
	4450 5800 5050 5800
Wire Wire Line
	4450 6600 5050 6600
Wire Wire Line
	5900 6100 5600 6100
Wire Wire Line
	5600 6100 5600 5550
Wire Wire Line
	5600 5550 4450 5550
Text GLabel 4450 5300 2    60   Input ~ 0
ardu5v
Text GLabel 3050 7100 0    60   Input ~ 0
supply
$Comp
L L293D U3
U 1 1 5C7FFDDD
P 7900 4350
F 0 "U3" H 7850 5500 60  0000 C CNN
F 1 "L293D" H 7750 5600 60  0000 C CNN
F 2 "Housings_DIP:DIP-16_W7.62mm_LongPads" H 7900 4350 60  0001 C CNN
F 3 "" H 7900 4350 60  0001 C CNN
	1    7900 4350
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR07
U 1 1 5C7FFDE4
P 8600 4350
F 0 "#PWR07" H 8600 4100 50  0001 C CNN
F 1 "GND" H 8600 4200 50  0000 C CNN
F 2 "" H 8600 4350 50  0001 C CNN
F 3 "" H 8600 4350 50  0001 C CNN
	1    8600 4350
	0    -1   -1   0   
$EndComp
$Comp
L GND #PWR08
U 1 1 5C7FFDEA
P 7200 4350
F 0 "#PWR08" H 7200 4100 50  0001 C CNN
F 1 "GND" H 7200 4200 50  0000 C CNN
F 2 "" H 7200 4350 50  0001 C CNN
F 3 "" H 7200 4350 50  0001 C CNN
	1    7200 4350
	0    1    1    0   
$EndComp
$Comp
L Screw_Terminal_01x02 J13
U 1 1 5C7FFDF0
P 9050 4400
F 0 "J13" H 9050 4500 50  0000 C CNN
F 1 "M2" H 9050 4200 50  0000 C CNN
F 2 "Connectors_Terminal_Blocks:TerminalBlock_Altech_AK300-2_P5.00mm" H 9050 4400 50  0001 C CNN
F 3 "" H 9050 4400 50  0001 C CNN
	1    9050 4400
	-1   0    0    1   
$EndComp
$Comp
L Screw_Terminal_01x02 J12
U 1 1 5C7FFDF7
P 6750 4300
F 0 "J12" H 6750 4400 50  0000 C CNN
F 1 "M1" H 6750 4100 50  0000 C CNN
F 2 "Connectors_Terminal_Blocks:TerminalBlock_Altech_AK300-2_P5.00mm" H 6750 4300 50  0001 C CNN
F 3 "" H 6750 4300 50  0001 C CNN
	1    6750 4300
	1    0    0    -1  
$EndComp
$Comp
L Conn_01x03_Male J10
U 1 1 5C7FFDFE
P 5500 4350
F 0 "J10" H 5500 4550 50  0000 C CNN
F 1 "mode&en M1" H 5500 4150 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x03_Pitch2.54mm" H 5500 4350 50  0001 C CNN
F 3 "" H 5500 4350 50  0001 C CNN
	1    5500 4350
	1    0    0    -1  
$EndComp
$Comp
L Conn_01x03_Male J14
U 1 1 5C7FFE05
P 10250 4350
F 0 "J14" H 10250 4550 50  0000 C CNN
F 1 "mode&en M2" H 10250 4150 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x03_Pitch2.54mm" H 10250 4350 50  0001 C CNN
F 3 "" H 10250 4350 50  0001 C CNN
	1    10250 4350
	-1   0    0    1   
$EndComp
Wire Wire Line
	7200 4200 7200 4500
Connection ~ 7200 4350
Wire Wire Line
	8600 4200 8600 4500
Connection ~ 8600 4350
Wire Wire Line
	8600 5000 9750 5000
Wire Wire Line
	9750 5000 9750 4350
Wire Wire Line
	9750 4350 10050 4350
Wire Wire Line
	10050 4450 10050 5250
Wire Wire Line
	10050 5250 8600 5250
Wire Wire Line
	5700 4250 5700 3450
Wire Wire Line
	5700 3450 7200 3450
Wire Wire Line
	7200 3700 5950 3700
Wire Wire Line
	5950 3700 5950 4350
Wire Wire Line
	5950 4350 5700 4350
Wire Wire Line
	5700 4450 5950 4450
Wire Wire Line
	6550 3950 7200 3950
Wire Wire Line
	6550 4750 7200 4750
Wire Wire Line
	5950 4450 5950 5000
Wire Wire Line
	5950 5000 7200 5000
Wire Wire Line
	8600 3950 9250 3950
Wire Wire Line
	8600 4750 9250 4750
Wire Wire Line
	10050 4250 9750 4250
Wire Wire Line
	9750 4250 9750 3700
Wire Wire Line
	9750 3700 8600 3700
Text GLabel 8600 3450 2    60   Input ~ 0
ardu5v
Text GLabel 7200 5250 0    60   Input ~ 0
supply
Wire Wire Line
	2400 5800 2400 6150
Wire Wire Line
	2400 6250 2400 6600
Wire Wire Line
	5050 5800 5050 6150
Wire Wire Line
	5050 6600 5050 6250
Wire Wire Line
	6550 4750 6550 4400
Wire Wire Line
	6550 4300 6550 3950
Wire Wire Line
	9250 3950 9250 4300
Wire Wire Line
	9250 4750 9250 4400
Wire Wire Line
	5050 1550 5050 1900
Wire Wire Line
	5050 2350 5050 2000
Wire Wire Line
	2450 2350 2450 2000
Wire Wire Line
	2450 1900 2450 1550
Text Label 2650 1050 0    60   ~ 0
en1
Text Label 2650 1300 0    60   ~ 0
mode1+
Text Label 2650 1550 0    60   ~ 0
m1+
Text Label 2650 2350 0    60   ~ 0
m1-
Text Label 2650 2600 0    60   ~ 0
mode1-
Text Label 4750 2850 0    60   ~ 0
en2
Text Label 4750 2600 0    60   ~ 0
mode2+
Text Label 4750 2350 0    60   ~ 0
m2+
Text Label 4750 1550 0    60   ~ 0
m2-
Text Label 4750 1300 0    60   ~ 0
mode2-
Text Label 8850 3700 0    60   ~ 0
mode2-3
Text Label 8850 3950 0    60   ~ 0
m2-3
Text Label 8850 4750 0    60   ~ 0
m2+3
Text Label 8850 5000 0    60   ~ 0
mode2+3
Text Label 8850 5250 0    60   ~ 0
en2
Text Label 6700 3700 0    60   ~ 0
mode1+3
Text Label 6700 3450 0    60   ~ 0
en13
Text Label 6700 3950 0    60   ~ 0
m1+3
Text Label 6700 4750 0    60   ~ 0
m1-3
Text Label 6700 5000 0    60   ~ 0
mode1-3
Text Label 4700 5550 0    60   ~ 0
mode2-2
Text Label 4700 5800 0    60   ~ 0
m2-2
Text Label 4700 6600 0    60   ~ 0
m2+2
Text Label 4700 6850 0    60   ~ 0
mode2+2
Text Label 4700 7100 0    60   ~ 0
en22
Text Label 2550 5300 0    60   ~ 0
en12
Text Label 2550 5550 0    60   ~ 0
mode1+2
Text Label 2550 5800 0    60   ~ 0
m1+2
Text Label 2550 6850 0    60   ~ 0
mode1-2
Text Label 2550 6600 0    60   ~ 0
m1-2
$EndSCHEMATC
