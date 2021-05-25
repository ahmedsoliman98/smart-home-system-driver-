/*
 * SmartHome_Slave.h
 *
 * Created: 4/14/2021 9:37:25 PM
 *  Author: ahmedsoliman
 */ 


#ifndef SMARTHOME_SLAVE_H_
#define SMARTHOME_SLAVE_H_


/* To Decide Which If We Have More Than One SPI */
#define SPI_communcation    SPI0

/* This Value is Reached By the Counter Of TCNT After Passed 10msec */
#define TOP_CTC_VALUE    (156)

/* Devices  ports and pins */
#define ROOMs_PORT   (GPIOD)
#define TV_PORT      (GPIOC)
#define AIRCOND_PORT (GPIOC)
#define ROOM1_PIN    (PIN4)
#define ROOM2_PIN    (PIN5)
#define ROOM3_PIN    (PIN6)
#define ROOM4_PIN    (PIN7)
#define TV_PIN       (PIN0)
#define AIRCOND_PIN  (PIN1)


/* SPI addresses */
#define ROOM1 (0x01)
#define ROOM2 (0x02)
#define ROOM3 (0x03)
#define ROOM4 (0x04)
#define TV           (0x20)
#define AirCondition (0x21)
/**** Room Turn On & Off ***/
#define ROOM1_ON   (0x08)
#define ROOM1_OFF  (0x09)
#define ROOM2_ON   (0x10)
#define ROOM2_OFF  (0x11)
#define ROOM3_ON   (0x12)
#define ROOM3_OFF  (0x13)
#define ROOM4_ON   (0x14)
#define ROOM4_OFF  (0x15)
/* Electric devices On & Off */
#define TV_ON       (0x16)
#define TV_OFF      (0x17)
#define AirCond_ON  (0x18)
#define AirCond_OFF (0x19)
#define ON    (0x05)
#define OFF   (0x06)
#define Temp_Mode   (0x33)
#define BLOCK_STATE (0x07)

/* Dummy Byte */
#define Dummy (0x00)


 void HomeSlave_INT(void);
 void HomeSlave_OPR(void);



#endif /* SMARTHOME_SLAVE_H_ */