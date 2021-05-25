/*
 * Smart_Home.c
 *
 * Created: 4/4/2021 7:46:49 PM
 *  Author: ahmedsoliman
 */ 


#include "SmartHome_Slave.h"

int main(void)
{
	HomeSlave_INT();
    while(1)
    {
        HomeSlave_OPR();
    }
}