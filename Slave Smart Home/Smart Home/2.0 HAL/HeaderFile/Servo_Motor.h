/*
 * Servo_Motor.h
 *
 * < it The driver of the Servo Motor Work with the signal control 50Hz , 20msec >
 * The control signal of the servo must be on the 20msec and we control the angle of the servo depend on the ON time on the control signal 
 * in our case the Microcontroller frequency is 16MHz and we use Timer one prescaler 1024 so the time of the one count in the TCNT1 is will be 1/16MHz/1024 = 64*10^-6 -> 64Usec
 * to calculate the numer of counts we need to reach the value of the 20msec it will be (20*10^-3) / (64*10^-6) it will be 312.5 -> 313
 * we Used the fast PWM Mode in the Timer 1 by Hold the value of the top in the ICR1 and Hold the value of the ON time in the OCR1A 
 * to calculate the number of counts to get the ON time :
 * the servo angle is -90 _ | _ 90 and the 0 in the middle ,, the 1msec ON time make the servo axle be in the -90 angle , 1.5msec ON time make the servo axle be in the 0 angle and 2msec ON time make the servo axle be in the 90 angle  
 * so the least number input is 1msec that the timer need to counts (1*10^-3)/(64 *10^-6) = 15.625 -> 16
 *
 * Created: 1/22/2021 11:54:05 PM
 *  Author: ahmedsoliman
 */ 


#ifndef SERVO_MOTOR_H_
#define SERVO_MOTOR_H_



  void SERVO_WRITE(double t, unsigned char servo_name);


#endif /* SERVO_MOTOR_H_ */