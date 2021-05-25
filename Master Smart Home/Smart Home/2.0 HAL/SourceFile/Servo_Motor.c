/*
 * Servo_Motor.c
 *
 * <  The driver of the Servo Motor Work with the signal control 50Hz , 20msec >
 *
 * The control signal of the servo must be on the 20msec and we control the angle of the servo depend on the ON time on the control signal 
 * in our case the Microcontroller frequency is 16MHz and we use Timer one prescaler 1024 so the time of the one count in the TCNT1 is will be 1/16MHz/1024 = 64*10^-6 -> 64Usec
 * to calculate the numer of counts we need to reach the value of the 20msec it will be (20*10^-3) / (4*10^-6) it will be 5000
 * we Used the fast PWM Mode in the Timer 1 by Hold the value of the top in the ICR1 and Hold the value of the ON time in the OCR1A 
 * to calculate the number of counts to get the ON time :
 * the servo angle is -90 _ | _ 90 and the 0 in the middle ,, the 1msec ON time make the servo axle be in the -90 angle , 1.5msec ON time make the servo axle be in the 0 angle and 2msec ON time make the servo axle be in the 90 angle  
 * so the least number input is 1msec that the timer need to counts (1*10^-3)/(4 *10^-6) = 250
 *
 * Created: 1/22/2021 11:54:05 PM
 *  Author: ahmedsoliman
 */ 


  #include "ATmega32A_Config.h"
  #include "ATmega32A_DIO_Config.h"
  #include <util/delay.h>
  
  
  #define Counts_20msecSignal_Num (5000)
  #define Counts_1msec_Num  (250)
  
     void SERVO_WRITE(double t, unsigned char servo_name)
	 {
		 
		 
		 /* Select the mode fast PWM as ICR1 top decimal 14*/
		 SET_Bit(TCCR1A,WGM11);
		 SET_Bit(TCCR1B,WGM12);
		 SET_Bit(TCCR1B,WGM13);
		 
		 /* LOAD The Value of the ICR1  */
		 
		 /* Store this value on the ICR1 that we make it the timer Top value so when it reach this value that mean that the 20msec is end the timer get overflow */
		 ICR1 = Counts_20msecSignal_Num;
		 
		 /* Set the timer clock as 64 is a prescaler that to avoid make the value of the number float to take more accuracy value */
		 SET_Bit(TCCR1B,CS10);
		 SET_Bit(TCCR1B,CS11);
		
		 switch(servo_name)
		 {
			 case 'A':
			       /* The value of the 1msec counts to define the ON time of output signal to decide the place of the Servo*/
			       OCR1A = t * Counts_1msec_Num;
				   
				    /* Work at the non inverting Mode */
				    SET_Bit(TCCR1A, COM1A1);
					/* Set The OC1A as an Output */
					DIO_pinConfiguration(GPIOD, PIN5, Output);
					_delay_us(10);
			 break;
			 case 'B':
			       /* The value of the 1msec counts to define the ON time of output signal to decide the place of the Servo*/
			       OCR1B = t * Counts_1msec_Num;
			       
			       /* Work at the non inverting Mode */
			       SET_Bit(TCCR1A, COM1B1);
				   
				   /* Set The OC1A as an Output */
				   DIO_pinConfiguration(GPIOD, PIN4, Output);
				   _delay_us(10);
			 break;
			 default:
			 /* Handle an Error massage the max Servo can operate reach */
			 break;
		 }
		 
	 }