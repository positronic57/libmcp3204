/*
 * MCP3204 library
 * libmcp3204.c
 *
 * Copyright (c) 2014  Goce Boshkovski
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License.
 */

/** @file libmcp3204.c
 *  @brief Implements the functions defined in the header file.
 *
 * @author Goce Boshkovski
 * @date 17-Aug-14
 * @copyright GNU General Public License v2.
 *
 */

#include <stdint.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/types.h>
#include <linux/spi/spidev.h>
#include "libmcp3204.h"

/*
 * The function configures the SPI interface of Raspberry PI 
 * according to MCP3204 SPI properties.
 */
int MCP3204_init(int *fd, char *dev, MCP3204 *ad, SPIMode spi_mode, float ref_voltage, char *errorMessage)
{
	uint8_t mode;
	uint8_t bits = 8;
	uint32_t speed = 100000;
	int ret;
	 
	if (spi_mode)
		mode |= SPI_MODE_3;
	else
		mode |= SPI_MODE_0;
	
	*fd = open(dev, O_RDWR);
	if (*fd < 0)
	{
		sprintf(errorMessage,"Cannot open device %s\n",dev);
		return 1;
	}
	
	/* set SPI mode */
	ret = ioctl(*fd, SPI_IOC_WR_MODE, &mode);
	if (ret == -1)
	{
		sprintf(errorMessage,"Cannot set the SPI mode.\n");
		return 1;
	}

	/* set SPI number of bits per word */
	ret = ioctl(*fd, SPI_IOC_RD_BITS_PER_WORD, &bits);
	if (ret == -1)
	{
		sprintf(errorMessage,"Cannot set number of bits per word.\n");
		return 1;
	}
	
	/* set SPI maximum clock speed */
	ret = ioctl(*fd, SPI_IOC_WR_MAX_SPEED_HZ, &speed);
	if (ret == -1)
	{
		sprintf(errorMessage,"Cannot set the maximum clock speed.\n");
		return 1;
	}
			
	ad->referenceVoltage=ref_voltage;

	return 0;
}

/*
 * Start the AD conversion process and read the digital value
 * of the analog signal from MCP3204.
 */
int MCP3204_convert(int fd, inputChannelMode channelMode, inputChannel channel, MCP3204 *ad,char *errorMessage)
{
	int ret;
	uint8_t tx[] = {0x00, 0x00, 0x00}; 
	uint8_t rx[] = {0x00, 0x00, 0x00};
	uint16_t delay = 0;
	uint8_t bits = 8;
	uint32_t speed = 100000;
	
	/* set the start bit */
	tx[0] |= START_BIT;
	
	/* define the channel input mode */
	if (channelMode==singleEnded)
		tx[0] |= SINGLE_ENDED;
	if (channelMode==differential)
		tx[0] &= DIFFERENTIAL;
		
	/* set the input channel/pair */
	switch(channel)
	{
		case CH0:
		case CH01:
			tx[1] |= CH_0;
			break;
		case CH1:
		case CH10:
			tx[1] |= CH_1;
			break;
		case CH2:
		case CH23:
			tx[1] |= CH_2;
			break;
		case CH3:
		case CH32:
			tx[1] |= CH_3;
			break;
	}
	
	struct spi_ioc_transfer tr = {
		.tx_buf = (unsigned long)tx,
		.rx_buf = (unsigned long)rx,
		.len = 3,
		.delay_usecs = delay,
		.speed_hz = speed,
		.bits_per_word = bits,
	};
	
	/* send the cmd to start the conversion and read the result */
	ret = ioctl(fd, SPI_IOC_MESSAGE(1), &tr);
	if (ret < 1)
	{
		sprintf(errorMessage,"Can't send SPI message.\n");
		return 1;
	}
	
	rx[1] &= 0x0F;
	ad->digitalValue = rx[1];
	ad->digitalValue <<= 8;
	ad->digitalValue |= rx[2];
	
	return 0;
}

/*
 * The function returns the result from the AD conversion.
 */
uint16_t MCP3204_getValue(MCP3204 ad)
{
	return ad.digitalValue;
}

/*
 * The function calculates the value of the analog input.
 */
float MCP3204_analogValue(MCP3204 ad)
{
	return (ad.digitalValue*ad.referenceVoltage)/4096;
}

