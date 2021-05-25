/*
 * L298N_MotorDriver.c
 *
 * Created: 10/10/2020 1:22:45 PM
 *  Author: ahmedsoliman
 */ 
  
  
  #include "ATmega32A_Config.h"
  #include "ATmega32A_DIO_Config.h"
  #include "L298N_MotorDriver.h"
  
  
  
  void MotorDriver_Setup(MotorDriver PINS)
  {
	  DIO_pinConfiguration(PINS.DriverPORT,PINS.MOTOR_INA1,Output);
	  DIO_pinConfiguration(PINS.DriverPORT,PINS.MOTOR_INA2,Output);
	  DIO_pinConfiguration(PINS.DriverPORT,PINS.MOTOR_INA3,Output);
	  DIO_pinConfiguration(PINS.DriverPORT,PINS.MOTOR_INA4,Output);
  }
  
  
  
  void Motor_Direction(MotorDriver motordirection)
  {
	  switch (motordirection.MOTORNUM)
	  {
		  case Two_Motor :
		  /* in This Case Motor A is the Back Motor that give The Main Motion To The Robot And Th Motor B is Direction Motor */
		        switch(motordirection.MOVMENT)
				{
					case Forward:
					     DIO_pinWrite(motordirection.DriverPORT,motordirection.MOTOR_INA1,HIGH);
						 DIO_pinWrite(motordirection.DriverPORT,motordirection.MOTOR_INA2,LOW);
						 break;
					case Reverce:
					     DIO_pinWrite(motordirection.DriverPORT,motordirection.MOTOR_INA1,LOW);
					     DIO_pinWrite(motordirection.DriverPORT,motordirection.MOTOR_INA2,HIGH);
						 break;
				    case Left:
					     DIO_pinWrite(motordirection.DriverPORT,motordirection.MOTOR_INA1,HIGH);
					     DIO_pinWrite(motordirection.DriverPORT,motordirection.MOTOR_INA2,LOW);
						 DIO_pinWrite(motordirection.DriverPORT,motordirection.MOTOR_INA3,HIGH);
						 DIO_pinWrite(motordirection.DriverPORT,motordirection.MOTOR_INA4,LOW);
						 break;
					case Right:
					     DIO_pinWrite(motordirection.DriverPORT,motordirection.MOTOR_INA1,HIGH);
					     DIO_pinWrite(motordirection.DriverPORT,motordirection.MOTOR_INA2,LOW);
					     DIO_pinWrite(motordirection.DriverPORT,motordirection.MOTOR_INA3,LOW);
					     DIO_pinWrite(motordirection.DriverPORT,motordirection.MOTOR_INA4,HIGH);
					case Spin:
					     /* in This Case We CAn not Make Robot Spin With The Only Two Motor So it Will Be Neglected An Do Nothing */
					default:
					       /* Handle The Error Function */
						   break;
				}	
		case More:
		     switch (motordirection.MOVMENT)
			 {
				 case Forward:
				 DIO_pinWrite(motordirection.DriverPORT,motordirection.MOTOR_INA1,HIGH);
				 DIO_pinWrite(motordirection.DriverPORT,motordirection.MOTOR_INA2,LOW);
				 DIO_pinWrite(motordirection.DriverPORT,motordirection.MOTOR_INA3,HIGH);
				 DIO_pinWrite(motordirection.DriverPORT,motordirection.MOTOR_INA4,LOW);
				 break;
				 case Reverce:
				 DIO_pinWrite(motordirection.DriverPORT,motordirection.MOTOR_INA1,LOW);
				 DIO_pinWrite(motordirection.DriverPORT,motordirection.MOTOR_INA2,HIGH);
				 DIO_pinWrite(motordirection.DriverPORT,motordirection.MOTOR_INA1,LOW);
				 DIO_pinWrite(motordirection.DriverPORT,motordirection.MOTOR_INA2,HIGH);
				 break;
				 case Left:
				 DIO_pinWrite(motordirection.DriverPORT,motordirection.MOTOR_INA1,HIGH);
				 DIO_pinWrite(motordirection.DriverPORT,motordirection.MOTOR_INA2,LOW);
				 DIO_pinWrite(motordirection.DriverPORT,motordirection.MOTOR_INA3,HIGH);
				 DIO_pinWrite(motordirection.DriverPORT,motordirection.MOTOR_INA4,LOW);
				 break;
				 case Right:
				 DIO_pinWrite(motordirection.DriverPORT,motordirection.MOTOR_INA1,HIGH);
				 DIO_pinWrite(motordirection.DriverPORT,motordirection.MOTOR_INA2,LOW);
				 DIO_pinWrite(motordirection.DriverPORT,motordirection.MOTOR_INA3,LOW);
				 DIO_pinWrite(motordirection.DriverPORT,motordirection.MOTOR_INA4,HIGH);
				 case Spin:
				 /* it the same as the last 2 cases but we need to finish timer first */
				 default:
				 /* Handle The Error Function */
				 break;
			 }				 				
	  }		  
  }