Project 
control CLP Motor(Mega2560) and receive CLP Motor Encoder(UNO)

Mega2560
1.controller
use timer to create Pulse to control CLP Motor

2.display
use LCD to show 
(1)RPM 
(2)steps,counted to 1000 will reset be 0 
(3)DIR(CW CCW)
(4)SPD(speed 0~9)

UNO
received CLP Motor Encoder that will use I2C to send information about steps

use interrupt to check Encoder Pulse

