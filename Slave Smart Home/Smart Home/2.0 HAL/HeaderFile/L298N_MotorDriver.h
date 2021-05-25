/*
 * L298N_MotorDriver.h
 *
 * Created: 10/10/2020 1:22:12 PM
 *  Author: ahmedsoliman
 */ 


#ifndef L298N_MOTORDRIVER_H_
#define L298N_MOTORDRIVER_H_


	typedef enum
	{
		Forward,
		Reverce,
		Left,
		Right,
		Spin,
	}MotorMovment;

	typedef enum
	{
		Two_Motor,
		More,
	}MotorNum;
	
	typedef struct
	{
		GPIO            * DriverPORT;
		pinNumber       MOTOR_INA1;
		pinNumber       MOTOR_INA2;
		pinNumber       MOTOR_INA3;
		pinNumber       MOTOR_INA4;
		MotorNum        MOTORNUM;
		MotorMovment     MOVMENT;
	}MotorDriver;
	
	void MotorDriver_Setup(MotorDriver PINS);
	void Motor_Direction(MotorDriver motordirection); 
	
	


#endif /* L298N_MOTORDRIVER_H_ */