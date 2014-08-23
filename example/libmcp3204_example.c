/*
 * libmcp3204_example.c
 *
 * Copyright (c) 2014  Goce Boshkovski
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License.
 *
 * Example of using libmcp3204 library on Raspberry Pi. An analog signal generated 
 * by TMP36 temperature sensor is converted by the MCP3204 to a digital value
 * that is transferred to Raspberry Pi for calculating the actual temperature value.
 * 
 */

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "libmcp3204.h"

float TMP36_temperature(float);

int main()
{
	int fileDescriptor;
	char error[55];

	MCP3204 ad_MCP3204;

	if (MCP3204_init(&fileDescriptor,"/dev/spidev0.1",&ad_MCP3204,mode_SPI_00,2.491,error))
	{
		printf("Cannot initialize the MCP3204 ADC.\n");
		printf("%s\n",error);
		exit(1);
	}

	if (MCP3204_convert(fileDescriptor,singleEnded,CH0,&ad_MCP3204,error))
	{
		printf("Error during conversion.\n");
		printf("%s\n",error);
		exit(1);
	}

	printf("Digital value of the sensor reading: %d\n",MCP3204_getValue(ad_MCP3204));
	printf("Analog value: %.4fV\n",MCP3204_analogValue(ad_MCP3204));
	printf("Temperature t=%.2f%cC\n",TMP36_temperature(MCP3204_analogValue(ad_MCP3204)),176);
	
	close(fileDescriptor);

	return 0;
}

float TMP36_temperature(float voltage_level)
{
	return (voltage_level*1000-500)/10;
}

