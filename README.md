# lab2_morse_skeleton
Skeleton code that's imported for Lab 2: Morse

Other than the serial print UART file, no additional files were used. Additioanlly, port 8 instead of port 7 was used on the arduino for the push button.

Calculations:
The button press duration for what is considered a dot, dash, and space were not increased or altered in the code. A dot is still defined as 30ms to 200ms, a dash is still defined as 200ms to 400ms, and a space is still considered any unpressed interval greater than 400ms. In my code, I converted the ticks between the rising and falling edge (taking into account the timer prescale value of 1024 I chose to use) into miliseconds by multiplying the ticks by (102400/16000000). I did include an overflow interrupt which can be added into the calculation: press duration in ms = (65536 * # of overflows + ticks from the last overflow to the falling edge) * (1024000/16000000). However, since I chose the prescale value of 1024 (1 tick per 1024 actual ticks), I didn't really need to account for the case of overflows since the duration of dots and dashes are smaller than the overflow count. 

Another calculation choice I made was to set the timer count to zero each time the button is pressed down (rising edge). This leads to an easier calcuation when subtracting the falling edge from the rising edge as it ensures the value would never be negative. 
