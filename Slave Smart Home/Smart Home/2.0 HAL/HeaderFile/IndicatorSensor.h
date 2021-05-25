/*
 *
 * @file <indicatorSensor.h>
 * @brief <This is a Header File for the indicator sensor For The Water Tank Level when it indicate read an LOW else it read HIGH>
 *
 * @APIS
 *					  sensor_setup()		< Setup driver Port and Pin via MCAL >
 *						returns   void 
 *						Takes	  indecationSensor_dataType
 *					 sensor_operate()		<it defines haw read from the sensor and return it is value>
 *                      return  digitalValue
 *                      Takes              indecationSensor_dataType     
 *
 * @authors <ahmedsoliman>
 * @date <7/19/2020 1:42:04 AM>
 *
 */

#ifndef INDICATORSENSOR_H_
#define INDICATORSENSOR_H_


    /*
	 *
	 * @brief <indecationSensor_dataType>
	 *		  GPIO *		sensorPORT < Should assign Port Address to it >
	 *        pinNumber     sensorPIN  <should assign pin Address to it >
	 *       
	 */     
   typedef struct
   {
	   GPIO * sensorPORT;
	   pinNumber sensorPIN;
	   DigitalValue indication;
   }indecationSensor_dataType;

    /*
	 *
	 * @brief <sensor_setup>
	 *
	 * <this function is to setup sensor with the microcontroller to be able to define it port and pin and it is input or output>
	 *
	 * @const indecationSensor_dataType  <struct>       <Should Pass a predefined indecationSensor_dataType LedDatatype Variable which has the Internal Values Filled >
	 *
	 *
	 * @return < void>
	 */
  
   void sensor_setup(indecationSensor_dataType sensor);
   
    /*
	 *
	 * @brief <sensor_operate>
	 *
	 * <this function is to operate the sensor function to read it is state >
	 *
	 * @const indecationSensor_dataType  <struct>       <Should Pass a predefined indecationSensor_dataType LedDatatype Variable which has the Internal Values Filled >
	 *
	 *
	 * @return < void>
	 */
   DigitalValue sensor_operate(indecationSensor_dataType sensor);





#endif /* INDICATORSENSOR_H_ */