EESchema Schematic File Version 4
LIBS:OneTouchM3-PCB-cache
EELAYER 30 0
EELAYER END
$Descr User 9843 6299
encoding utf-8
Sheet 1 1
Title "OneTouch module for Renault Megane III"
Date "2019-08-13"
Rev "1.1"
Comp ""
Comment1 "blinks in that direction"
Comment2 "switch in one direction and the module will automatically drive the BCM to issue three"
Comment3 "Arduino based module for implementing One touch feature i.e. slightly activate the turn"
Comment4 ""
$EndDescr
Text Label 6200 1500 1    60   ~ 0
Raw
Text Label 4850 2000 0    60   ~ 0
D2
Text Label 4850 2100 0    60   ~ 0
D3
Text Label 4850 2200 0    60   ~ 0
D4
Text Label 4850 2300 0    60   ~ 0
D5
Text Label 4850 2400 0    60   ~ 0
D6
Text Label 4850 2500 0    60   ~ 0
D7
Text Label 4850 2600 0    60   ~ 0
D8
Text Label 4850 2700 0    60   ~ 0
D9
Text Label 6350 2700 0    60   ~ 0
D10_(SS)
Text Label 6350 2600 0    60   ~ 0
D11_(MOSI)
Text Label 6350 2500 0    60   ~ 0
D12_MISO
Text Label 6350 2400 0    60   ~ 0
D13_SCK
Text Label 6350 2300 0    60   ~ 0
A0
Text Label 6350 2200 0    60   ~ 0
A1
Text Label 6350 2100 0    60   ~ 0
A2
Text Label 6350 2000 0    60   ~ 0
A3
Text Label 5500 3200 3    60   ~ 0
A4
Text Label 5400 3200 3    60   ~ 0
A5
Text Notes 4400 575  0    60   ~ 0
Arduino Pro Mini
Wire Notes Line
	4375 650  5200 650 
Wire Notes Line
	5200 650  5200 475 
Text Label 5800 3200 3    60   ~ 0
A7
Text Label 5900 3200 3    60   ~ 0
A6
$Comp
L Connector_Generic:Conn_01x02 P3
U 1 1 56D74FB3
P 5400 3000
F 0 "P3" H 5400 3150 50  0001 C CNN
F 1 "ADC" V 5500 3000 50  0000 C CNN
F 2 "" H 5400 3000 50  0001 C CNN
F 3 "" H 5400 3000 50  0000 C CNN
	1    5400 3000
	0    -1   -1   0   
$EndComp
$Comp
L Connector_Generic:Conn_01x02 P5
U 1 1 56D7505C
P 5800 3000
F 0 "P5" H 5800 3150 50  0001 C CNN
F 1 "ADC" V 5900 3000 50  0000 C CNN
F 2 "" H 5800 3000 50  0001 C CNN
F 3 "" H 5800 3000 50  0000 C CNN
	1    5800 3000
	0    -1   -1   0   
$EndComp
$Comp
L Connector_Generic:Conn_01x12 P1
U 1 1 56D754D1
P 5350 2100
F 0 "P1" H 5350 2750 50  0000 C CNN
F 1 "Digital" V 5450 2100 50  0000 C CNN
F 2 "OneTouchM3:P1_digital" H 5350 2100 50  0001 C CNN
F 3 "" H 5350 2100 50  0000 C CNN
	1    5350 2100
	1    0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_01x12 P4
U 1 1 56D755F3
P 5900 2100
F 0 "P4" H 5900 2750 50  0000 C CNN
F 1 "Analog" V 6000 2100 50  0000 C CNN
F 2 "OneTouchM3:P4_analog" H 5900 2100 50  0001 C CNN
F 3 "" H 5900 2100 50  0000 C CNN
	1    5900 2100
	-1   0    0    -1  
$EndComp
Wire Wire Line
	5150 2100 4850 2100
Wire Wire Line
	4850 2300 5150 2300
Wire Wire Line
	4850 2500 5150 2500
Wire Wire Line
	5150 2700 4850 2700
Wire Wire Line
	6200 1500 6200 1600
Wire Wire Line
	6200 1600 6100 1600
Wire Wire Line
	6100 1700 6200 1700
Wire Wire Line
	6200 1700 6200 2800
$Comp
L power:GND #PWR04
U 1 1 56D75A03
P 6200 2800
F 0 "#PWR04" H 6200 2550 50  0001 C CNN
F 1 "GND" H 6200 2650 50  0000 C CNN
F 2 "" H 6200 2800 50  0000 C CNN
F 3 "" H 6200 2800 50  0000 C CNN
	1    6200 2800
	1    0    0    -1  
$EndComp
Wire Wire Line
	6100 1900 6300 1900
Wire Wire Line
	6300 1900 6300 1500
$Comp
L power:VCC #PWR05
U 1 1 56D75A9D
P 6300 1500
F 0 "#PWR05" H 6300 1350 50  0001 C CNN
F 1 "VCC" H 6300 1650 50  0000 C CNN
F 2 "" H 6300 1500 50  0000 C CNN
F 3 "" H 6300 1500 50  0000 C CNN
	1    6300 1500
	1    0    0    -1  
$EndComp
Wire Wire Line
	6350 2000 6100 2000
Wire Wire Line
	6100 2100 6350 2100
Wire Wire Line
	6350 2200 6100 2200
Wire Wire Line
	6100 2300 6350 2300
Wire Wire Line
	6350 2400 6100 2400
Wire Wire Line
	6350 2600 6100 2600
Wire Notes Line
	7050 3400 4350 3400
Wire Notes Line
	4350 3400 4350 500 
$Comp
L Device:R R1
U 1 1 5BE9FD10
P 1050 3300
F 0 "R1" H 1120 3346 50  0000 L CNN
F 1 "100k" H 1120 3255 50  0000 L CNN
F 2 "OneTouchM3:R" V 980 3300 50  0001 C CNN
F 3 "~" H 1050 3300 50  0001 C CNN
	1    1050 3300
	1    0    0    -1  
$EndComp
NoConn ~ 4850 2100
NoConn ~ 4850 2300
NoConn ~ 4850 2500
NoConn ~ 4850 2700
NoConn ~ 6350 2600
NoConn ~ 6350 2400
NoConn ~ 6350 2300
NoConn ~ 6350 2200
NoConn ~ 6350 2100
NoConn ~ 6350 2000
$Comp
L power:GND #PWR0106
U 1 1 5BEB7EC7
P 6750 3750
F 0 "#PWR0106" H 6750 3500 50  0001 C CNN
F 1 "GND" H 6755 3577 50  0000 C CNN
F 2 "" H 6750 3750 50  0001 C CNN
F 3 "" H 6750 3750 50  0001 C CNN
	1    6750 3750
	1    0    0    -1  
$EndComp
$Comp
L power:PWR_FLAG #FLG0101
U 1 1 5BEB8C56
P 6350 3750
F 0 "#FLG0101" H 6350 3825 50  0001 C CNN
F 1 "PWR_FLAG" H 6350 3924 50  0000 C CNN
F 2 "" H 6350 3750 50  0001 C CNN
F 3 "~" H 6350 3750 50  0001 C CNN
	1    6350 3750
	1    0    0    -1  
$EndComp
$Comp
L power:VCC #PWR0107
U 1 1 5BEB8DDD
P 6350 3750
F 0 "#PWR0107" H 6350 3600 50  0001 C CNN
F 1 "VCC" H 6368 3923 50  0000 C CNN
F 2 "" H 6350 3750 50  0001 C CNN
F 3 "" H 6350 3750 50  0001 C CNN
	1    6350 3750
	-1   0    0    1   
$EndComp
NoConn ~ 5900 3200
NoConn ~ 5800 3200
NoConn ~ 5500 3200
NoConn ~ 5400 3200
$Comp
L power:PWR_FLAG #FLG0102
U 1 1 5BEBC1F6
P 6750 3750
F 0 "#FLG0102" H 6750 3825 50  0001 C CNN
F 1 "PWR_FLAG" H 6750 3924 50  0000 C CNN
F 2 "" H 6750 3750 50  0001 C CNN
F 3 "~" H 6750 3750 50  0001 C CNN
	1    6750 3750
	1    0    0    -1  
$EndComp
Wire Wire Line
	6100 1800 6350 1800
Text Label 6350 1800 0    50   ~ 0
Reset1
$Comp
L Diode:1N4007 D1
U 1 1 5BEB2D76
P 1050 2900
F 0 "D1" V 1100 3050 50  0000 R CNN
F 1 "1N4007" V 1000 3250 50  0000 R CNN
F 2 "OneTouchM3:D" H 1050 2725 50  0001 C CNN
F 3 "http://www.vishay.com/docs/88503/1n4001.pdf" H 1050 2900 50  0001 C CNN
	1    1050 2900
	0    -1   -1   0   
$EndComp
$Comp
L Device:R R2
U 1 1 5BEB31E0
P 1050 3750
F 0 "R2" H 1120 3796 50  0000 L CNN
F 1 "47k" H 1120 3705 50  0000 L CNN
F 2 "OneTouchM3:R" V 980 3750 50  0001 C CNN
F 3 "~" H 1050 3750 50  0001 C CNN
	1    1050 3750
	1    0    0    -1  
$EndComp
Wire Wire Line
	1050 3050 1050 3150
$Comp
L power:GND #PWR01
U 1 1 5BEB590C
P 1050 3900
F 0 "#PWR01" H 1050 3650 50  0001 C CNN
F 1 "GND" H 1055 3727 50  0000 C CNN
F 2 "" H 1050 3900 50  0001 C CNN
F 3 "" H 1050 3900 50  0001 C CNN
	1    1050 3900
	1    0    0    -1  
$EndComp
$Comp
L Device:R R3
U 1 1 5BEB6AEE
P 1850 3300
F 0 "R3" H 1920 3346 50  0000 L CNN
F 1 "100k" H 1920 3255 50  0000 L CNN
F 2 "OneTouchM3:R" V 1780 3300 50  0001 C CNN
F 3 "~" H 1850 3300 50  0001 C CNN
	1    1850 3300
	1    0    0    -1  
$EndComp
$Comp
L Diode:1N4007 D2
U 1 1 5BEB6AF4
P 1850 2900
F 0 "D2" V 1900 3100 50  0000 R CNN
F 1 "1N4007" V 1800 3250 50  0000 R CNN
F 2 "OneTouchM3:D" H 1850 2725 50  0001 C CNN
F 3 "http://www.vishay.com/docs/88503/1n4001.pdf" H 1850 2900 50  0001 C CNN
	1    1850 2900
	0    -1   -1   0   
$EndComp
$Comp
L Device:R R4
U 1 1 5BEB6AFA
P 1850 3750
F 0 "R4" H 1920 3796 50  0000 L CNN
F 1 "47k" H 1920 3705 50  0000 L CNN
F 2 "OneTouchM3:R" V 1780 3750 50  0001 C CNN
F 3 "~" H 1850 3750 50  0001 C CNN
	1    1850 3750
	1    0    0    -1  
$EndComp
Wire Wire Line
	1850 3050 1850 3150
Wire Wire Line
	1850 3450 1850 3550
$Comp
L power:GND #PWR02
U 1 1 5BEB6B02
P 1850 3900
F 0 "#PWR02" H 1850 3650 50  0001 C CNN
F 1 "GND" H 1855 3727 50  0000 C CNN
F 2 "" H 1850 3900 50  0001 C CNN
F 3 "" H 1850 3900 50  0001 C CNN
	1    1850 3900
	1    0    0    -1  
$EndComp
Text Label 1050 2750 2    50   ~ 0
Right_turn_sw
Text Label 1850 2750 2    50   ~ 0
Left_turn_sw
Wire Wire Line
	1500 3550 1850 3550
Connection ~ 1850 3550
Wire Wire Line
	1850 3550 1850 3600
Connection ~ 1050 3550
Wire Wire Line
	1050 3550 1050 3600
Wire Wire Line
	1050 3450 1050 3550
$Comp
L Device:R R5
U 1 1 5BEBD84A
P 2600 3300
F 0 "R5" H 2670 3346 50  0000 L CNN
F 1 "100k" H 2670 3255 50  0000 L CNN
F 2 "OneTouchM3:R" V 2530 3300 50  0001 C CNN
F 3 "~" H 2600 3300 50  0001 C CNN
	1    2600 3300
	1    0    0    -1  
$EndComp
$Comp
L Diode:1N4007 D3
U 1 1 5BEBD850
P 2600 2900
F 0 "D3" V 2650 3100 50  0000 R CNN
F 1 "1N4007" V 2550 3250 50  0000 R CNN
F 2 "OneTouchM3:D" H 2600 2725 50  0001 C CNN
F 3 "http://www.vishay.com/docs/88503/1n4001.pdf" H 2600 2900 50  0001 C CNN
	1    2600 2900
	0    -1   -1   0   
$EndComp
$Comp
L Device:R R6
U 1 1 5BEBD856
P 2600 3750
F 0 "R6" H 2670 3796 50  0000 L CNN
F 1 "47k" H 2670 3705 50  0000 L CNN
F 2 "OneTouchM3:R" V 2530 3750 50  0001 C CNN
F 3 "~" H 2600 3750 50  0001 C CNN
	1    2600 3750
	1    0    0    -1  
$EndComp
Wire Wire Line
	2600 3050 2600 3150
$Comp
L power:GND #PWR06
U 1 1 5BEBD85D
P 2600 3900
F 0 "#PWR06" H 2600 3650 50  0001 C CNN
F 1 "GND" H 2605 3727 50  0000 C CNN
F 2 "" H 2600 3900 50  0001 C CNN
F 3 "" H 2600 3900 50  0001 C CNN
	1    2600 3900
	1    0    0    -1  
$EndComp
$Comp
L Device:R R7
U 1 1 5BEBD863
P 3350 3300
F 0 "R7" H 3420 3346 50  0000 L CNN
F 1 "100k" H 3420 3255 50  0000 L CNN
F 2 "OneTouchM3:R" V 3280 3300 50  0001 C CNN
F 3 "~" H 3350 3300 50  0001 C CNN
	1    3350 3300
	1    0    0    -1  
$EndComp
$Comp
L Diode:1N4007 D4
U 1 1 5BEBD869
P 3350 2900
F 0 "D4" V 3400 3100 50  0000 R CNN
F 1 "1N4007" V 3300 3250 50  0000 R CNN
F 2 "OneTouchM3:D" H 3350 2725 50  0001 C CNN
F 3 "http://www.vishay.com/docs/88503/1n4001.pdf" H 3350 2900 50  0001 C CNN
	1    3350 2900
	0    -1   -1   0   
$EndComp
$Comp
L Device:R R8
U 1 1 5BEBD86F
P 3350 3750
F 0 "R8" H 3420 3796 50  0000 L CNN
F 1 "47k" H 3420 3705 50  0000 L CNN
F 2 "OneTouchM3:R" V 3280 3750 50  0001 C CNN
F 3 "~" H 3350 3750 50  0001 C CNN
	1    3350 3750
	1    0    0    -1  
$EndComp
Wire Wire Line
	3350 3050 3350 3150
Wire Wire Line
	3350 3450 3350 3550
$Comp
L power:GND #PWR07
U 1 1 5BEBD877
P 3350 3900
F 0 "#PWR07" H 3350 3650 50  0001 C CNN
F 1 "GND" H 3355 3727 50  0000 C CNN
F 2 "" H 3350 3900 50  0001 C CNN
F 3 "" H 3350 3900 50  0001 C CNN
	1    3350 3900
	1    0    0    -1  
$EndComp
Text Label 2600 2750 2    50   ~ 0
Right_blink
Text Label 3350 2750 2    50   ~ 0
Left_blink
Connection ~ 3350 3550
Wire Wire Line
	3350 3550 3350 3600
Connection ~ 2600 3550
Wire Wire Line
	2600 3550 2600 3600
Wire Wire Line
	2600 3450 2600 3550
Wire Wire Line
	2250 3550 2600 3550
Wire Notes Line
	7050 3400 7050 500 
$Comp
L Device:R R9
U 1 1 5BEC7024
P 7200 3000
F 0 "R9" H 7270 3046 50  0000 L CNN
F 1 "220" H 7270 2955 50  0000 L CNN
F 2 "OneTouchM3:R" V 7130 3000 50  0001 C CNN
F 3 "~" H 7200 3000 50  0001 C CNN
	1    7200 3000
	1    0    0    -1  
$EndComp
Wire Wire Line
	7200 2850 7200 2700
Wire Wire Line
	6100 2700 7200 2700
$Comp
L power:GND #PWR08
U 1 1 5BEC8E80
P 7200 3700
F 0 "#PWR08" H 7200 3450 50  0001 C CNN
F 1 "GND" H 7205 3527 50  0000 C CNN
F 2 "" H 7200 3700 50  0001 C CNN
F 3 "" H 7200 3700 50  0001 C CNN
	1    7200 3700
	1    0    0    -1  
$EndComp
Wire Wire Line
	7200 3300 7200 3150
Wire Wire Line
	7200 3500 7200 3700
$Comp
L Isolator:SFH617A-1 U1
U 1 1 5BECA988
P 7500 3400
F 0 "U1" H 7500 3725 50  0000 C CNN
F 1 "EL817" H 7500 3634 50  0000 C CNN
F 2 "OneTouchM3:Optocoupler" H 7300 3200 50  0001 L CIN
F 3 "http://www.vishay.com/docs/83740/sfh617a.pdf" H 7500 3400 50  0001 L CNN
	1    7500 3400
	1    0    0    -1  
$EndComp
$Comp
L Diode:1N4007 D5
U 1 1 5BECAAB7
P 8250 3700
F 0 "D5" V 8296 3621 50  0000 R CNN
F 1 "1N4007" V 8205 3621 50  0000 R CNN
F 2 "OneTouchM3:D" H 8250 3525 50  0001 C CNN
F 3 "http://www.vishay.com/docs/88503/1n4001.pdf" H 8250 3700 50  0001 C CNN
	1    8250 3700
	0    1    1    0   
$EndComp
Wire Wire Line
	8250 3300 8250 3550
Text Label 7800 3500 0    50   ~ 0
Right_BCM
Text Label 8250 3850 3    50   ~ 0
Common_BCM
$Comp
L Device:R R10
U 1 1 5BECC89B
P 9250 3000
F 0 "R10" H 9320 3046 50  0000 L CNN
F 1 "220" H 9320 2955 50  0000 L CNN
F 2 "OneTouchM3:R" V 9180 3000 50  0001 C CNN
F 3 "~" H 9250 3000 50  0001 C CNN
	1    9250 3000
	-1   0    0    -1  
$EndComp
$Comp
L power:GND #PWR09
U 1 1 5BECC8A2
P 9250 3700
F 0 "#PWR09" H 9250 3450 50  0001 C CNN
F 1 "GND" H 9255 3527 50  0000 C CNN
F 2 "" H 9250 3700 50  0001 C CNN
F 3 "" H 9250 3700 50  0001 C CNN
	1    9250 3700
	-1   0    0    -1  
$EndComp
Wire Wire Line
	9250 3300 9250 3150
Wire Wire Line
	9250 3500 9250 3700
$Comp
L Isolator:SFH617A-1 U2
U 1 1 5BECC8AA
P 8950 3400
F 0 "U2" H 8950 3725 50  0000 C CNN
F 1 "EL817" H 8950 3634 50  0000 C CNN
F 2 "OneTouchM3:Optocoupler" H 8750 3200 50  0001 L CIN
F 3 "http://www.vishay.com/docs/83740/sfh617a.pdf" H 8950 3400 50  0001 L CNN
	1    8950 3400
	-1   0    0    -1  
$EndComp
Text Label 8650 3500 2    50   ~ 0
Left_BCM
Wire Wire Line
	6100 2500 9250 2500
Wire Wire Line
	9250 2500 9250 2850
$Comp
L Device:C C1
U 1 1 5BEDDDCE
P 700 3750
F 0 "C1" H 815 3796 50  0000 L CNN
F 1 "100n" H 815 3705 50  0000 L CNN
F 2 "OneTouchM3:C" H 738 3600 50  0001 C CNN
F 3 "~" H 700 3750 50  0001 C CNN
	1    700  3750
	1    0    0    -1  
$EndComp
Wire Wire Line
	700  3600 700  3550
Wire Wire Line
	700  3550 1050 3550
Wire Wire Line
	700  3900 1050 3900
Connection ~ 1050 3900
$Comp
L Device:C C4
U 1 1 5BEE266B
P 3000 3750
F 0 "C4" H 3115 3796 50  0000 L CNN
F 1 "100n" H 3115 3705 50  0000 L CNN
F 2 "OneTouchM3:C" H 3038 3600 50  0001 C CNN
F 3 "~" H 3000 3750 50  0001 C CNN
	1    3000 3750
	1    0    0    -1  
$EndComp
Wire Wire Line
	3000 3900 3350 3900
Connection ~ 3350 3900
Wire Wire Line
	3000 3600 3000 3550
Wire Wire Line
	3000 3550 3350 3550
$Comp
L Device:C C3
U 1 1 5BEE6EA6
P 2250 3750
F 0 "C3" H 2365 3796 50  0000 L CNN
F 1 "100n" H 2365 3705 50  0000 L CNN
F 2 "OneTouchM3:C" H 2288 3600 50  0001 C CNN
F 3 "~" H 2250 3750 50  0001 C CNN
	1    2250 3750
	1    0    0    -1  
$EndComp
Wire Wire Line
	2250 3900 2600 3900
Connection ~ 2600 3900
Wire Wire Line
	2250 3600 2250 3550
$Comp
L Device:C C2
U 1 1 5BEEFF94
P 1500 3750
F 0 "C2" H 1615 3796 50  0000 L CNN
F 1 "100n" H 1615 3705 50  0000 L CNN
F 2 "OneTouchM3:C" H 1538 3600 50  0001 C CNN
F 3 "~" H 1500 3750 50  0001 C CNN
	1    1500 3750
	1    0    0    -1  
$EndComp
Wire Wire Line
	1500 3900 1850 3900
Connection ~ 1850 3900
Wire Wire Line
	1500 3600 1500 3550
NoConn ~ 6200 1500
NoConn ~ 6350 1800
$Comp
L Connector:DB9_Male J3
U 1 1 5BEC774C
P 700 4950
F 0 "J3" H 620 4258 50  0000 C CNN
F 1 "Car connector" H 620 4349 50  0000 C CNN
F 2 "OneTouchM3:Car_connector" H 700 4950 50  0001 C CNN
F 3 " ~" H 700 4950 50  0001 C CNN
	1    700  4950
	-1   0    0    1   
$EndComp
Text Label 1000 5250 0    50   ~ 0
Right_turn_sw
Text Label 1000 4950 0    50   ~ 0
Common_BCM
Text Label 1000 5350 0    50   ~ 0
VCC
Text Label 1000 4750 0    50   ~ 0
Right_BCM
Text Label 1000 4850 0    50   ~ 0
Left_blink
Text Label 1000 4650 0    50   ~ 0
Right_blink
Text Label 1000 5150 0    50   ~ 0
Left_BCM
Text Notes 1600 5250 0    50   ~ 0
12V when right turn switch activated, 0V when not
Text Label 1000 5050 0    50   ~ 0
Left_turn_sw
Text Notes 1600 5050 0    50   ~ 0
12V when left turn switch activated, 0V when not
Text Notes 1600 4950 0    50   ~ 0
Pin 37, from the gray BCM's socket
Text Notes 1600 4750 0    50   ~ 0
Pin 39, from the gray BCM's socket
Text Notes 1600 5150 0    50   ~ 0
Pin 40, from the gray BCM's socket
Text Notes 1600 5350 0    50   ~ 0
5V
Text Notes 1600 4850 0    50   ~ 0
Pin 11, from the brown BCM's socket
Text Notes 1600 4650 0    50   ~ 0
Pin 10, from the brown BCM's socket
Text Notes 550  5600 0    50   ~ 0
Note. The C1, c2, C3 and C4 are used for switches debouncing, due to imperfect electrical contact
Text Notes 800  5700 0    50   ~ 0
R1, R3, R5 and R7 protects Arduino for vltage spikes up to 100V, due to its internal clamping diodes
Wire Wire Line
	1050 3550 1350 3550
Wire Wire Line
	1350 3550 1350 2000
Wire Wire Line
	1850 3550 2150 3550
Wire Wire Line
	2150 3550 2150 2200
Wire Wire Line
	2600 3550 2900 3550
Wire Wire Line
	2900 3550 2900 2400
Wire Wire Line
	3350 3550 3650 3550
Wire Wire Line
	3650 3550 3650 2600
Wire Wire Line
	1350 2000 5150 2000
Wire Wire Line
	2150 2200 5150 2200
Wire Wire Line
	2900 2400 5150 2400
Wire Wire Line
	3650 2600 5150 2600
NoConn ~ 5150 1900
NoConn ~ 5150 1600
NoConn ~ 5150 1800
NoConn ~ 5150 1700
Text Label 1000 4550 0    50   ~ 0
GND
Text Label 5150 1600 2    50   ~ 0
Tx
Text Label 5150 1700 2    50   ~ 0
Rx
Text Label 5150 1800 2    50   ~ 0
Reset
Text Label 5150 1900 2    50   ~ 0
GND
Wire Wire Line
	8650 3300 8250 3300
Connection ~ 8250 3300
Wire Wire Line
	8250 3300 7800 3300
$EndSCHEMATC
