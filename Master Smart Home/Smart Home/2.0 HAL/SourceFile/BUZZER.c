/*
 * BUZZER.c
 *
 * Created: 7/19/2020 1:25:09 AM
 *  Author: ahmedsoliman
 */ 



  #include <ATmega32A_Config.h>
  #include <ATmega32A_DIO_Config.h>
  #include <StandardDataType.h>
  #include <util/delay.h>
  #include <BUZZER.h>
  
  /* define the Alarming delay to Make A sequence Of Tone*/
  #define PEP_DELAY (100)
  
  
  
  void BUZZER_Setup (BUZZER_dataType buz)
  {
	  /* Configuration The Pin Of The Buzzer As Output Pin */
	  DIO_pinConfiguration(buz.buzzerPORT,buz.buzzerPIN,Output);
  }
  
  
  void BUZZER_ALARM(BUZZER_dataType buz)
  {
	  /* That Make A sequence Of PeP By On an Off THe Buzzer */
	  DIO_pinWrite(buz.buzzerPORT, buz.buzzerPIN, HIGH);
	  _delay_ms(PEP_DELAY);
	  DIO_pinWrite(buz.buzzerPORT, buz.buzzerPIN, LOW);
	  _delay_ms(PEP_DELAY);
  }