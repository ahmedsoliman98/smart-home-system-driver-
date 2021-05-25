/*
 * SmartHome_Master.c
 *
 * Created: 4/8/2021 2:31:08 PM
 *  Author: ahmedsoliman
 */ 
#include "ATmega32A_Config.h"
#include "ATmega32A_DIO_Config.h"
#include "ATmega32A_Timers_Config.h"
#include "ATmega32A_SPI.h"
#include "ATmega32A_EEPROM_Config.h"
#include "Keypad_Config_Driver.h"
#include "LCD.h"
#include "SmartHome_Master.h"
#include "ATmega32A_Interrupt.h"



/************************************************** Variables *******************************************************************************/

	
/* set the Keypad Keys */	
unsigned  char KeyData[COL][ROW] = {'7','8','9','A',
	                                '4','5','6','B',
									'1','2','3','C',
									'#','0','*','D'};
/* Configure the keypad Port and Pin */
KEYPAD_PIN keypad0 = {GPIOC, PIN0, PIN1, PIN2, PIN3, PIN4, PIN5,PIN6, PIN7};	


/* Loop variable */
unsigned char i = 0;

/* data Enter Variable */
unsigned char Data_Enter;

/* Set The Timer Number We Used And Its Mode */
TIMER_DATATYPE counter = {Timer0,Timer_CTC_Mode, Timer_Fcpu_Div1024, Timer_TopCTC_Interrupt};

/* second counter */
volatile unsigned int OneSec = 0;

/* password checked flag */
unsigned char CheckedPass_Flag = 0;
unsigned char DATA_CHECKED = 0;
unsigned char OPR_MODE = 0;
unsigned char TRAILS_NUM = '2';
unsigned char SLAVE_DATA = 0;
unsigned int WAIT_TIME = 0;
unsigned char TEMP_LEVEL = 0;

unsigned char TurnOnCode;
unsigned char TurnOffCode;

static void Delay (int Waitting_Time)
{
	/* Reset the Value of the OneSec we reset the value at the first because we make the WAIT_TIME at the same timer so to make sure it count from 0 */
	OneSec = 0;
	GLOBAL_INT_ENABLE();
	while(OneSec <= Waitting_Time){/* wait */};
	GLOBAL_INT_DISABLE();
}

/* Read user input Data From keypad and Display it on the LCD */
static void EnteredData_Display(void)
{
	do
	{
		Data_Enter = keypad_Read(keypad0);
	} while (Data_Enter == 0);
	
	/* Display the real char typed for 200msec */
	LCD_DisplayChar(Data_Enter);
	Delay(20);
	
	/* store the Owner password on it is place in the memory */
	LCD_Select_RowCol(1, i+5);
	LCD_DisplayChar('*');
}


static void Check_Password(char Mode)
{
	if (Mode == OWNER_MODE)
	{
		LCD_DisplayString("Enter Owner Pass");
		LCD_Select_RowCol(1,5);
		for (i = 0; i < 5; i++)
		{
			EnteredData_Display();
			DATA_CHECKED = EEPEOM_Read(OwnerPass_address+i);
			if (DATA_CHECKED != Data_Enter)
			{
				/* if the data input not equal the data stored in memory that mean the password is wrong so make flag = 1 */
				CheckedPass_Flag = 1;
			}
		}
	}
	else if (Mode == GUEST_MODE)
	{
		LCD_DisplayString("Enter Guest Pass");
		LCD_Select_RowCol(1,5);
		for (i = 0; i < 5; i++)
		{
			EnteredData_Display();
			DATA_CHECKED = EEPEOM_Read(GuestPass_address+i);
			if (DATA_CHECKED != Data_Enter)
			{
				/* if the data input not equal the data stored in memory that mean the password is wrong so make flag = 1 */
				CheckedPass_Flag = 1;
			}
		}
	}
	
}

static void RoomsControl_Display(void)
{
	do 
	{
		LCD_Clear();
		/*Display the Control settings in the Owner Mode */
		LCD_DisplayString("1-Room1  2-Room2");
		LCD_Select_RowCol(1,0);
		if (OPR_MODE == GUEST_MODE)
		{
			LCD_DisplayString("3-Room3  4-Room4");
		}
		else if (OPR_MODE == OWNER_MODE)
		{
			LCD_DisplayString("3-Room3  4-More");
		}
		/* Stuck until user enter data in this case the data entered not displayed on the LCD so we do not use EnteredData_Display function*/
		do
		{
			Data_Enter = keypad_Read(keypad0);
		} while (Data_Enter == 0 && WAIT_TIME <= ((OPR_MODE == GUEST_MODE) ? GUEST_LIMITEDTIME : OWNER_LIMITEDTIME));
		
		/* Case Of the Owner More Option Display Screen */
		if (Data_Enter == '4' && OPR_MODE == OWNER_MODE)
		{
			LCD_Clear();
			LCD_DisplayString("4-Room4     5-TV");
			LCD_Select_RowCol(1,0);
			LCD_DisplayString("6-Air Cond.7-RET");
			/* Stuck until user enter data in this case the data entered not displayed on the LCD so we do not use EnteredData_Display function*/
			do
			{
				Data_Enter = keypad_Read(keypad0);
			} while (Data_Enter == 0 && WAIT_TIME <=  OWNER_LIMITEDTIME);
		}
		
		/*depend on the guest user input we select which room we control */
		LCD_Clear();
		switch(Data_Enter)
		{
			case '1':
			/* control the Light on the room 1 so we display the current state of the light in the room one and the option ON/OFF/RETURN */
			LCD_DisplayString("Room1   S:");
			TurnOnCode  = ROOM1_ON;
			TurnOffCode = ROOM1_OFF;
			Exchange_Byte_Blocking(ROOM1);
			break;
			case '2':
			/* control the Light on the room 2 so we display the current state of the light in the room one and the option ON/OFF/RETURN */
			LCD_DisplayString("Room2   S:");
			TurnOnCode  = ROOM2_ON;
			TurnOffCode = ROOM2_OFF;
			Exchange_Byte_Blocking(ROOM2);
			break;
			case '3':
			/* control the Light on the room 3 so we display the current state of the light in the room one and the option ON/OFF/RETURN */
			LCD_DisplayString("Room3   S:");
			TurnOnCode  = ROOM3_ON;
			TurnOffCode = ROOM3_OFF;
			Exchange_Byte_Blocking(ROOM3);
			break;
			case '4':
			/* control the Light on the room 4 so we display the current state of the light in the room one and the option ON/OFF/RETURN */
			LCD_DisplayString("Room4   S:");
			TurnOnCode  = ROOM4_ON;
			TurnOffCode = ROOM4_OFF;
			Exchange_Byte_Blocking(ROOM4);
			break;
			case '5':
			/* control the operation of the TV so we display the current state of the operation and the option ON/OFF/RETURN */
			LCD_DisplayString("TV     S:");
			TurnOnCode  = TV_ON;
			TurnOffCode = TV_OFF;
			Exchange_Byte_Blocking(TV);
			break;
			case '6':
			/* in this case should display the air condition and temperature control screen but each one of them have a different next screen */
			break;
			case '7':
			/* for RET Selection in the screen that mean to return to the last screen */
			break;
			case 0:
			/* in this case the user do not enter any data and the time limit is finish */
			break;
			default:
			LCD_Clear();
			LCD_DisplayString("Wrong Input");
			Delay(50);
			break;
		}
		/* If the Data_Enter Equal to '7' that mean the user ask to return to the last screen in this case it will loop again in this function */ 
	} while (Data_Enter == '7' && WAIT_TIME <= OWNER_LIMITEDTIME);
}



static AirCondition_ControlDisplay(void)
{
	do 
	{
		/* air condition choice must the user select between the operation of the device or set the temperature */
		LCD_Clear();
		LCD_DisplayString("1-Temp Control");
		LCD_Select_RowCol(1,0);
		LCD_DisplayString("2-State  0-RET");
		/* Stuck until user enter data in this case the data entered not displayed on the LCD so we do not use EnteredData_Display function*/
		do
		{
			Data_Enter = keypad_Read(keypad0);
		} while (Data_Enter == 0 && WAIT_TIME <=  OWNER_LIMITEDTIME);
		if (Data_Enter == '1')
		{
			LCD_Clear();
			LCD_DisplayString("Set temp.: __");
			LCD_DisplayChar(0xDF); /* The Address Value Of The '°' stored in the LCD */
			LCD_DisplayChar('C');
			LCD_Select_RowCol(0,11);
			/* Display the number of the temperature user set level */
			do
			{
				Data_Enter = keypad_Read(keypad0);
			} while (Data_Enter == 0 && WAIT_TIME <=  OWNER_LIMITEDTIME);
			LCD_DisplayChar(Data_Enter);
			/* convert the data enter into an integer number */
			TEMP_LEVEL = (Data_Enter-48)*10;
			do
			{
				Data_Enter = keypad_Read(keypad0);
			} while (Data_Enter == 0 && WAIT_TIME <=  OWNER_LIMITEDTIME);
			LCD_DisplayChar(Data_Enter);
			TEMP_LEVEL += (Data_Enter -48);
			Delay(20);
			Exchange_Byte_Blocking(Temp_Mode);
			Exchange_Byte_Blocking(TEMP_LEVEL);
			
		}
		else if (Data_Enter == '2')
		{
			LCD_Clear();
			/* control the operation of the air condition so we display the current state of the operation and the option ON/OFF/RETURN */
			LCD_DisplayString("AirCond    S:");
			TurnOnCode  = AirCond_ON;
			TurnOffCode = AirCond_OFF;
			Exchange_Byte_Blocking(AirCondition);
			break;
		}
		else if (Data_Enter == '0')
		{
			/* this return choice so we break the current loop */
			break;
		}
		else
		{
			LCD_Clear();
			LCD_DisplayString("Wrong Input");
			Delay(50);
		}
	} while (WAIT_TIME <= OWNER_LIMITEDTIME);
}






static DeviceCurrent_stateDisplay(void)
{
	/* To make sure that this function is not going to operate if the time out */
	if (WAIT_TIME <= ((OPR_MODE == GUEST_MODE) ? GUEST_LIMITEDTIME : OWNER_LIMITEDTIME))
	{
		/* display the current state of room light or electric device selected */
		/* Stable Delay to SPI System */
		Delay(10);
		/* Get the Data From the slave of the current State of the Device */
		SLAVE_DATA = Exchange_Byte_Blocking(Dummy);
		switch(SLAVE_DATA)
		{
			case OFF:
			LCD_DisplayString("OFF");
			break;
			case ON:
			LCD_DisplayString("ON");
			break;
			case Temp_Mode:
			/* in this case we do not use this function */
			break;
			default:
			LCD_Clear();
			LCD_DisplayString("Error in Slave");
			break;
		}
	}
}

static TurnOnOff_ControlDisplay(void)
{
	Data_Enter = 0;
	if ((WAIT_TIME <= ((OPR_MODE == GUEST_MODE) ? GUEST_LIMITEDTIME : OWNER_LIMITEDTIME)) && (SLAVE_DATA != Temp_Mode))
	{
		LCD_Select_RowCol(1,0);
		LCD_DisplayString("1-ON 2-OFF 0-RET");
		/* get the order state from the user */
		do
		{
			Data_Enter = keypad_Read(keypad0);
		} while (Data_Enter == 0 && (WAIT_TIME <= ((OPR_MODE == GUEST_MODE) ? GUEST_LIMITEDTIME : OWNER_LIMITEDTIME)));
		
		switch(Data_Enter)
		{
			case '1':
			Exchange_Byte_Blocking(TurnOnCode);
			break;
			case '2':
			Exchange_Byte_Blocking(TurnOffCode);
			break;
			case '0':
			/* Return state to the first display */
			break;
			case 0:
			/* in this case the user do not enter any data and the time limit is finish */
			break;
			default:
			LCD_Clear();
			LCD_DisplayString("Wrong Input");
			Delay(50);
			break;
		}
	}
	
}


void SmartHome_INT(void)
{
	LCD_init();
	keypad_Intiat(keypad0);
	
	/* operate the count of the Timer */
	TIMER_INTIATE(counter);
	/* set up the CTC top value on it is register */
	TIMER_DELAY(counter, TOP_CTC_VALUE);
	
	/* set up the SPI communication to send and receive the data from the Slave */
	SPI_communcation.EnableControl = SPI_Enable;
	SPI_communcation.DataOreder = SPI_MSB;
	SPI_communcation.ModeSelect = SPI_MASTER;
	SPI_communcation.ClkMode = SPI_ClkMode0;
	SPI_communcation.InterruptState = SPI_InterruptDisable;
	SPI_communcation.SCKFreq = SPI_FCPU_By_2;
	SPI_Intiat();
	/* Config  a Chip Select Pin As Output */
	DIO_pinConfiguration(CHIP_SELECT_PORT, CHIP_SELECT_PIN, Output);
	GLOBAL_INT_ENABLE();
	
}


void SmartHome_OPR(void)
{
	
	/* the Initial value of the EEPROM place is 0xFF so if it Still on that case that mean it is first time and we need Setup */
	if (EEPEOM_Read(State_address) == 0xFF)
	{
		LCD_Clear();
		/* we Want to the welcome screen is display for 500msec so the OneSec counter is increase each 10msec pass so we wait until it reach 50 */
		LCD_DisplayString("Welcome to Smart ");
		LCD_Select_RowCol(1,0);
		LCD_DisplayString("  Home System   ");
		/* Display the opening Screen for 1sec */
		Delay(100);
		
		/* Set the Owner Password */
		LCD_Clear();
		LCD_DisplayString(" Set Owner Pass : ");
		LCD_Select_RowCol(1,5);
		for (i = 0; i < 5; i++)
		{
			EnteredData_Display();
			EEPROM_Write(OwnerPass_address+i, Data_Enter);
		}
		
		/* Set the Guest Password */
		LCD_Clear();
		LCD_DisplayString(" Set Guest Pass : ");
		LCD_Select_RowCol(1,5);
		for (i = 0; i < 5; i++)
		{
			EnteredData_Display();
			EEPROM_Write(GuestPass_address+i, Data_Enter);
		}
		
		/* change the EEPROM State place value to mention that the setup configuration is finish */
		EEPROM_Write(State_address, 0x00);
	}
	else if (EEPEOM_Read(State_address) == 0x00)
	{
		LCD_Clear();
		LCD_DisplayString("Select Mode :");
		LCD_Select_RowCol(1,0);
		LCD_DisplayString("1-Owner  2-Guest");
		
		/* Stuck until user enter data in this case the data entered not displayed on the LCD so we do not use EnteredData_Display function*/
		do
		{
			Data_Enter = keypad_Read(keypad0);
		} while (Data_Enter == 0);
		/* checked the entered password depend on the user enter data 1/2 for checked guest or owner Mode */
		OPR_MODE = Data_Enter;
			LCD_Clear();
			
			/* check the Enter from the user */
			if (OPR_MODE == OWNER_MODE || OPR_MODE == GUEST_MODE)
			{
				if (TRAILS_NUM == '0')
				{
					/* refer to the locked Mode */
					EEPROM_Write(State_address, '*');
				}
				else
				{
					Check_Password(OPR_MODE);
					if(CheckedPass_Flag == 1)
					{
						LCD_Clear();
						LCD_DisplayString("Wrong Password");
						LCD_Select_RowCol(1,0);
						LCD_DisplayString("remain trails ");
						LCD_DisplayChar(TRAILS_NUM);
						Delay(400);
						TRAILS_NUM--;
					}
					else
					{
						LCD_Clear();
						if (OPR_MODE == OWNER_MODE)
						{
							/***************************************************Display the Control settings in the Owner Mode **********************************************/
							GLOBAL_INT_ENABLE();
							WAIT_TIME = 0;
							do
							{
								RoomsControl_Display();
								if (Data_Enter == '6')
								{
									AirCondition_ControlDisplay();
								} 
								DeviceCurrent_stateDisplay();
								TurnOnOff_ControlDisplay();
								
							}while (WAIT_TIME <= OWNER_LIMITEDTIME);
							LCD_Clear();
							LCD_DisplayString("    Time Out");
							Delay(50);
							GLOBAL_INT_DISABLE();
							/* Reset the Value of the OneSec */
							WAIT_TIME = 0;
						}
						else
						{
							/***************************************************** Guest Control Display ***************************************************/
							/* we give the guest limited time to control 2min */
							GLOBAL_INT_ENABLE();
							WAIT_TIME = 0;
							do
							{
								RoomsControl_Display();
								
							}while (WAIT_TIME <= GUEST_LIMITEDTIME);
							LCD_Clear();
							LCD_DisplayString("    Time Out");
							Delay(50);
							GLOBAL_INT_DISABLE();
							/* Reset the Value of the OneSec */
							WAIT_TIME = 0;
						}
					}
				}
			}
			else
			{
				LCD_Clear();
				LCD_DisplayString("Wrong Input");
				Delay(50);
			}
		
	}
	/* this mean that the user enter the wrong password more than 3 time so it will go to block mode */
	else if (EEPEOM_Read(State_address) == '*')
	{	
		/* we send to lock off all the home devices */	
		Exchange_Byte_Blocking(BLOCK_STATE);
		LCD_Clear();
		LCD_DisplayString("Home Block Mode");
		Delay(1000);
		/* return after 10sec to ask for password */
		EEPROM_Write(State_address, 0x00);
	}
			
}

/* this definition we get from the ATmega32A_intrrupt Library we implement */
ISR (TIMER0_COMP_vect)
{
	OneSec++;
	WAIT_TIME++;
}

