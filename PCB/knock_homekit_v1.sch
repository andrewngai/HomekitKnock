EESchema Schematic File Version 4
EELAYER 30 0
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
L ESP8266:ESP-12E U2
U 1 1 600D327F
P 5650 4000
F 0 "U2" H 5650 4765 50  0000 C CNN
F 1 "ESP-12E" H 5650 4674 50  0000 C CNN
F 2 "ESP8266:ESP-12E_SMD" H 5650 4000 50  0001 C CNN
F 3 "http://l0l.org.uk/2014/12/esp8266-modules-hardware-guide-gotta-catch-em-all/" H 5650 4000 50  0001 C CNN
	1    5650 4000
	1    0    0    -1  
$EndComp
$Comp
L Regulator_Linear:AMS1117-3.3 AMS1117-3.3
U 1 1 600D4288
P 3700 5050
F 0 "AMS1117-3.3" H 3700 5292 50  0000 C CNN
F 1 "AMS1117-3.3" H 3700 5201 50  0000 C CNN
F 2 "Package_TO_SOT_SMD:SOT-223-3_TabPin2" H 3700 5250 50  0001 C CNN
F 3 "http://www.advanced-monolithic.com/pdf/ds1117.pdf" H 3800 4800 50  0001 C CNN
	1    3700 5050
	1    0    0    -1  
$EndComp
$Comp
L Connector:USB_B_Micro J1
U 1 1 600D522C
P 2850 3800
F 0 "J1" H 2907 4267 50  0000 C CNN
F 1 "USB_B_Micro" H 2907 4176 50  0000 C CNN
F 2 "Connector_USB:USB_Micro-B_Molex_47346-0001" H 3000 3750 50  0001 C CNN
F 3 "~" H 3000 3750 50  0001 C CNN
	1    2850 3800
	1    0    0    -1  
$EndComp
$Comp
L Connector:Conn_01x02_Female Sensor1
U 1 1 600D63E1
P 3550 3350
F 0 "Sensor1" H 3442 3025 50  0001 C CNN
F 1 "Sensor" H 3442 3116 50  0000 C CNN
F 2 "Connector_JST:JST_XH_B2B-XH-A_1x02_P2.50mm_Vertical" H 3550 3350 50  0001 C CNN
F 3 "~" H 3550 3350 50  0001 C CNN
	1    3550 3350
	-1   0    0    1   
$EndComp
$Comp
L Connector:Conn_01x06_Female J3
U 1 1 600D6B8A
P 7950 2950
F 0 "J3" H 7978 2926 50  0000 L CNN
F 1 "Program" H 7978 2835 50  0000 L CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x06_P2.54mm_Vertical" H 7950 2950 50  0001 C CNN
F 3 "~" H 7950 2950 50  0001 C CNN
	1    7950 2950
	1    0    0    -1  
$EndComp
Wire Wire Line
	3250 5050 3400 5050
Wire Wire Line
	4000 5050 4750 5050
Wire Wire Line
	4750 5050 4750 4400
$Comp
L power:GND #PWR0101
U 1 1 600D8270
P 3700 5350
F 0 "#PWR0101" H 3700 5100 50  0001 C CNN
F 1 "GND" H 3705 5177 50  0000 C CNN
F 2 "" H 3700 5350 50  0001 C CNN
F 3 "" H 3700 5350 50  0001 C CNN
	1    3700 5350
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0102
U 1 1 600DBF8C
P 6550 4400
F 0 "#PWR0102" H 6550 4150 50  0001 C CNN
F 1 "GND" H 6555 4227 50  0000 C CNN
F 2 "" H 6550 4400 50  0001 C CNN
F 3 "" H 6550 4400 50  0001 C CNN
	1    6550 4400
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0103
U 1 1 600DC3A4
P 2850 4200
F 0 "#PWR0103" H 2850 3950 50  0001 C CNN
F 1 "GND" H 2855 4027 50  0000 C CNN
F 2 "" H 2850 4200 50  0001 C CNN
F 3 "" H 2850 4200 50  0001 C CNN
	1    2850 4200
	1    0    0    -1  
$EndComp
Wire Wire Line
	3150 3600 3250 3600
Wire Wire Line
	4100 2750 4100 3700
Connection ~ 4750 4400
$Comp
L power:GND #PWR0104
U 1 1 600E27DE
P 7750 3250
F 0 "#PWR0104" H 7750 3000 50  0001 C CNN
F 1 "GND" H 7755 3077 50  0000 C CNN
F 2 "" H 7750 3250 50  0001 C CNN
F 3 "" H 7750 3250 50  0001 C CNN
	1    7750 3250
	1    0    0    -1  
$EndComp
Wire Wire Line
	6700 3800 6550 3800
$Comp
L Device:R R1
U 1 1 600E55CB
P 4450 3500
F 0 "R1" V 4657 3500 50  0000 C CNN
F 1 "10K" V 4566 3500 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P10.16mm_Horizontal" V 4380 3500 50  0001 C CNN
F 3 "~" H 4450 3500 50  0001 C CNN
	1    4450 3500
	0    -1   -1   0   
$EndComp
Wire Wire Line
	4100 2750 7750 2750
Wire Wire Line
	4100 4400 4750 4400
Wire Wire Line
	4600 3700 4750 3700
Wire Wire Line
	4300 3900 4100 3900
Connection ~ 4100 3900
Wire Wire Line
	4100 3900 4100 4400
Wire Wire Line
	4300 3700 4100 3700
Connection ~ 4100 3700
Wire Wire Line
	4100 3700 4100 3900
$Comp
L Device:R R3
U 1 1 600EC464
P 6750 4100
F 0 "R3" V 6543 4100 50  0000 C CNN
F 1 "10K" V 6634 4100 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P10.16mm_Horizontal" V 6680 4100 50  0001 C CNN
F 3 "~" H 6750 4100 50  0001 C CNN
	1    6750 4100
	0    1    1    0   
$EndComp
Wire Wire Line
	7050 4100 6900 4100
Wire Wire Line
	6550 4100 6600 4100
Wire Wire Line
	7050 4100 7050 3050
Wire Wire Line
	7050 3050 7750 3050
Wire Wire Line
	4750 3700 4750 3150
Wire Wire Line
	4750 3150 7750 3150
Connection ~ 4750 3700
$Comp
L power:GND #PWR0105
U 1 1 600EFAD6
P 3750 3350
F 0 "#PWR0105" H 3750 3100 50  0001 C CNN
F 1 "GND" H 3755 3177 50  0000 C CNN
F 2 "" H 3750 3350 50  0001 C CNN
F 3 "" H 3750 3350 50  0001 C CNN
	1    3750 3350
	1    0    0    -1  
$EndComp
Wire Wire Line
	4750 3800 3900 3800
Wire Wire Line
	3900 3800 3900 3250
Wire Wire Line
	3900 3250 3750 3250
Wire Wire Line
	3250 3600 3250 5050
Wire Wire Line
	7750 2850 6550 2850
Wire Wire Line
	6550 2850 6550 3700
Wire Wire Line
	6700 3800 6700 2950
Wire Wire Line
	6700 2950 7750 2950
Wire Wire Line
	4600 3700 4600 3500
Wire Wire Line
	4300 3700 4300 3500
$Comp
L Device:R R2
U 1 1 600E3421
P 4450 4050
F 0 "R2" V 4243 4050 50  0000 C CNN
F 1 "10K" V 4334 4050 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P10.16mm_Horizontal" V 4380 4050 50  0001 C CNN
F 3 "~" H 4450 4050 50  0001 C CNN
	1    4450 4050
	0    1    1    0   
$EndComp
Wire Wire Line
	4750 3900 4600 3900
Wire Wire Line
	4600 3900 4600 4050
Wire Wire Line
	4300 3900 4300 4050
$EndSCHEMATC
