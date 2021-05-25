/*
 * Ultrasonic_HCSR04.h
 *
 * in this driver we operate the ultrasonic sensor module HC-RS04 
 * Module feature :
 * - operating current : <15mA       -operating voltage 5V        - Acuuracy 2mm           - practical measurment from 2 to <= 80 cm     
 * Operation concept : 
 * the module generate a sound signal with frequency 40kHz and because the max frequency can human hear is 20kHz the speed of sound is 346m/sec (this the number of Proteus assumption )and use the timer to measure the time then we get the send and receive distance divided by 2 get the distance between the object and the sensor  
 * We used the External interrupt and the timer0 (We can use the Input capture pin in timer 1 feature )
 * Steps of operating :
 *  - The microcontroller send an pulse Ton must be more than 10msec to the Trig pin of the module to initiate the transmission
 *  - The module start to send a signal with frequency 40kHz from the Tx and make Echo pin High
 *  - When the signal is returned to the module and receive on the Rx it make Echo pin low 
 *  
 *					  ULTRASONIC_Setup()		< Setup ultrasonic port and pin via MCAL >
 *						returns   void
 *						Takes	  ULTRASONIC_DATATYPE
 *					  ULTRASONIC_OPERATE()	 < Start the operation of the ultrasonic send the signal and make the calculation to return the distance >
 *                      returns   unsigned char
 *                      Takes                ULTRASONIC_DATATYPE 
 * Created: 1/20/2021 4:27:54 AM
 *  Author: ahmedsoliman
 */ 


#ifndef ULTRASONIC_HCSR-04_H_
#define ULTRASONIC_HCSR-04_H_



  typedef struct  
  {
	  GPIO* ultrasonic_port;
	  pinNumber ultrasonic_Trig;
	 /* must be on of the External interrupt Pin PB2, PD2, PD3 */
	  pinNumber ultrasonic_Echo;
  }ULTRASONIC_DATATYPE;
  
  void ULTRASONIC_Setup(ULTRASONIC_DATATYPE U);
  unsigned short ULTRASONIC_OPERATE (ULTRASONIC_DATATYPE U);



#endif /* ULTRASONIC_HCSR-04_H_ */