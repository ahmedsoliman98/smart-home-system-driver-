/*
 * indicatorSensor.c
 *
 * Created: 7/19/2020 1:42:22 AM
 *  Author: ahmedsoliman
 */ 
  
  
  
   #include <ATmega32A_Config.h>
   #include <ATmega32A_DIO_Config.h>
   #include <StandardDataType.h>
   #include <IndicatorSensor.h>
   
   
   
   void sensor_setup(indecationSensor_dataType sensor)
   {
	   /* Configuration The PinOf The Sensor As an Input Pull up Pin So It default Is LOW */
	   DIO_pinConfiguration(sensor.sensorPORT, sensor.sensorPIN, InputFloat);
   }
   
   
   
   DigitalValue sensor_operate(indecationSensor_dataType sensor)
   {
	   /* read The Pin State Refer To The Condition OfThe sensor If It Indicate Will return High Else Will Return LOW */ 
	   return ( DIO_pinRead(sensor.sensorPORT, sensor.sensorPIN) );
   }