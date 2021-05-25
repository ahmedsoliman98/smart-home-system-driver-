/*
 * SmartHome_Master.h
 *
 * Created: 4/8/2021 2:30:46 PM
 *  Author: ahmedsoliman
 */ 


#ifndef SMARTHOME_MASTER_H_
#define SMARTHOME_MASTER_H_

/****************************************************** Definition ***************************************************************/
#define State_address  (0x01)
/* set limit to the password to be 4 char */
#define OwnerPass_address  (0x02)
#define GuestPass_address  (0x08)
/* This Value is Reached By the Counter Of TCNT After Passed 10msec */
#define TOP_CTC_VALUE    (156)
#define   Dummy         (0x00)
/* Chip Select is an Input Output PIN So Can Be Any One */
#define CHIP_SELECT_PORT    GPIOB
#define CHIP_SELECT_PIN     PIN4
/* To Decide Which If We Have More Than One SPI */
#define SPI_communcation    SPI0

#define OWNER_MODE  ('1')
#define GUEST_MODE  ('2')

#define ROOM1        (0x01)
#define ROOM2        (0x02)
#define ROOM3        (0x03)
#define ROOM4        (0x04)
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
/* Statue address */
#define ON          (0x05)
#define OFF         (0x06)
#define Temp_Mode   (0x33)
#define BLOCK_STATE (0x07)

#define GUEST_LIMITEDTIME (200)
#define OWNER_LIMITEDTIME (700)



				
/*************************************** Functions *******************************************************************************************/ 

void SmartHome_INT(void);
void SmartHome_OPR(void);

#endif /* SMARTHOME_MASTER_H_ */