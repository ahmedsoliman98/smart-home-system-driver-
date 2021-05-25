/*
 * Ultrasonic_HCSR04.c
 *
 * < this driver we operate the ultrasonic sensor module HC-RS04 >
 * Module feature :
 * - operating current : <15mA       -operating voltage 5V        - Acuuracy 2mm           - practical measurment from 2 to <= 80 cm     
 * Operation concept : 
 * the module generate a sound signal with frequency 40kHz and because the max frequency can human hear is 20kHz the speed of sound is 346m/sec (this the number of Proteus assumption )and use the timer to measure the time then we get the send and receive distance divided by 2 get the distance between the object and the sensor  
 * We used the External interrupt and the timer0 (We can use the Input capture pin in timer 1 feature )
 * Steps of operating :
 *  - The microcontroller send an pulse Ton must be more than 10msec to the Trig pin of the module to initiate the transmission
 *  - The module start to send a signal with frequency 40kHz from the Tx and make Echo pin High
 *  - When the signal is returned to the module and receive on the Rx it make Echo pin low 
 * Note : the Protues simulation signal is get very large scale of the ON time so it We assume that max range should it measure is 290cm in the practical it 400cm
 * this value can not be reched before the Timer TCNT get overflow because this distance mean the number of tick equal 359 So we solve by check the overflow flag  
 * The max Range in the Simulation is 564cm when the var-Resistance get 50%
 * Created: 1/20/2021 4:27:54 AM
 *  Author: ahmedsoliman
 */ 


  #include "ATmega32A_Config.h"
  #include "ATmega32A_DIO_Config.h"
  #include "ATmega32A_Interrupt.h"
  #include "ATmega32A_Timers_Config.h"
  #include "Ultrasonic_HCSR-04.h"
  #include <util/delay.h>
  
  
  
  #define SOUND_SPEED (34600)/* in cm/sec */
  /* Set up the timer to co figure the timer 0 */
   TIMER_DATATYPE t_counter1 = {Timer0,Timer_Overflow_Mode, Timer_Fcpu_Div1024, Timer_No_Interrupt};
	/* Set up the timer to co figure the timer 0 */
  TIMER_DATATYPE t_counter2 = {Timer2,Timer_Overflow_Mode, Timer_Fcpu_Div1024, Timer_No_Interrupt};   
  /* make the flag variable to know the second time get ISR */
  volatile unsigned char flag_1 = 0;
  /* make the flag variable to know the second time get ISR */
  volatile unsigned char flag_2 = 0;
  /* define the duration variable for the pin interrupt 0 */
   short Object_distance1;
   /* define the duration variable for the pin interrupt 1 */
    short Object_distance2;
  
  static void interrupt_Function(void)
  {
	  unsigned short time_ON;
	  if (flag_1 == 0)
	  {
		  TIMER_INTIATE(t_counter1);
		 EXTINT_InterruptInit(EXINT_INT0, EXINT_FallingEdge);
		  flag_1 = 1;
	  }
	  else if(flag_1 == 1)
	  {
		  TCCR0 = 0; 
		  if (READ_Bit(TIFR,TOV0) == 1)
		  {
			  /* To solve the Problem of the Overflow the counter before get the maximum distance */
			  Object_distance1 = (TCNT0 + 255) * 1.1072;
			  /* CLear the flag Manually by Write a One */
			  SET_Bit(TIFR,TOV0);
		  }
		  else
		  {
			  Object_distance1 = TCNT0 * 1.1072;
		  }
		  EXTINT_InterruptInit(EXINT_INT0, EXINT_RisingEdge);	
		  flag_1 = 0;
		  TCNT0 = 0;
		  
	  }
  }
  static void interrupt_Function2(void)
  {
	  unsigned short time_ON;
	  if (flag_2 == 0)
	  {
		  TIMER_INTIATE(t_counter2);
		  EXTINT_InterruptInit(EXINT_INT1, EXINT_FallingEdge);
		  flag_2 = 1;
	  }
	  else if(flag_2 == 1)
	  {
		  TCCR2 = 0;
		  if (READ_Bit(TIFR,TOV2) == 1)
		  {
			  /* To solve the Problem of the Overflow the counter before get the maximum distance */
			  Object_distance2 = (TCNT2 + 255) * 1.1072;
			  /* CLear the flag Manually by Write a One */
			  SET_Bit(TIFR,TOV2);
		  }
		  else
		  {
			  Object_distance2 = TCNT2 * 1.1072;
		  }
		  EXTINT_InterruptInit(EXINT_INT1, EXINT_RisingEdge);
		  flag_2 = 0;
		  TCNT2 = 0;
		  
	  }
  }
  
     void ULTRASONIC_Setup(ULTRASONIC_DATATYPE U)
	 {
		 /* Make the trigger pin output  */
		 DIO_pinConfiguration(U.ultrasonic_port, U.ultrasonic_Trig, Output);
		 
		 /* Make the Echo Pin input Note that it must be on of the External interrupt Pin PB2, PD2, PD3 */
		 DIO_pinConfiguration(U.ultrasonic_port, U.ultrasonic_Echo, InputFloat);
		 
		 _delay_us(500);
		 /* Setup the interrupt pin depend on the user Selection (We Work at INT0, INT1 until handle INT2 ) */
		 switch(U.ultrasonic_Echo)
		 {
			 case PIN2 :
			      /* in this case we Setup the External interrupt Source number 0 */
				  EXTINT_InterruptInit(EXINT_INT0, EXINT_RisingEdge);
				  /* set the ISR Function depend on the user external interrupt choose */
				  EXTINT0_ISR = interrupt_Function;
			 break;
			 case PIN3 :
			      /* in this case we Setup the External interrupt Source number 1 */
			      EXTINT_InterruptInit(EXINT_INT1, EXINT_RisingEdge);
				  /* set the ISR Function depend on the user external interrupt choose */
				  EXTINT1_ISR = interrupt_Function2;
			 break;
			 default: 
			 /* Handle the error if the user select an Wrong pin to work as Echo pin */
			 break;
		 }
		 	
		 /* Enable the Global Interrupt */
		 SREG |= (1 << 7);		 
	 }		 
     unsigned short ULTRASONIC_OPERATE (ULTRASONIC_DATATYPE U)
	 {
		 unsigned short distance = 0x00;
		 /* start with send the trigger signal */
		 DIO_pinWrite(U.ultrasonic_port,U.ultrasonic_Trig, HIGH);
		 /* Make The pulse time ON is 10Usec */
		 _delay_us(15);
		 /* Return it to LOW again to be one pulse */
		  DIO_pinWrite(U.ultrasonic_port,U.ultrasonic_Trig, LOW);
		  switch(U.ultrasonic_Echo)
		  {
			  case PIN2:
			  distance = Object_distance1 ;
			  break;
			  case PIN3:
			  distance = Object_distance2;
			  break;
			  default:
			  break;
		  }
		  return distance;
	 }
	 
    