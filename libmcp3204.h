/*
 * MCP3204 library
 * libmcp3204.h
 *
 * Copyright (c) 2014  Goce Boshkovski
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License.
 */

#ifndef LIBMCP3204_H_
#define LIBMCP3204_H_

#define START_BIT 0x04
#define SINGLE_ENDED 0x02
#define DIFFERENTIAL 0xFB
#define CH_0 0x00
#define CH_1 0x40
#define CH_2 0x80
#define CH_3 0xC0

typedef enum inputchannelmode
{
	singleEnded = 0,
	differential
} inputChannelMode;

typedef enum inputchannel
{
	CH0 = 0,
	CH1,
	CH2,
	CH3,
	CH01,       /* CH0 = IN+, CH1 = IN- */
	CH10,       /* CH0 = IN-, CH1 = IN+ */
	CH23,       /* CH2 = IN+, CH3 = IN- */
	CH32        /* CH2 = IN-, CH3 = IN+ */
} inputChannel;
	
typedef enum spiMode
{
	mode_SPI_00 = 0,
	mode_SPI_11
} SPIMode;

typedef struct mcp3204
{
	uint16_t digitalValue;
	float referenceVoltage;
} MCP3204;


/*
 * The function configures the SPI interface of Raspberry PI 
 * according to MCP3204 SPI properties.
 */
int MCP3204_init(int *, char *, MCP3204 *, SPIMode, float, char *);

/*
 * Start the AD conversion process and read the digital value
 * of the analog signal from MCP3204.
 */
int MCP3204_convert(int, inputChannelMode, inputChannel, MCP3204 *, char *);

/*
 * Get the digital value already read from the AD convertor.
 */
uint16_t MCP3204_getValue(MCP3204);

/*
 * Calculate the value of the analog input.
 */
float MCP3204_analogValue(MCP3204);

#endif /* LIBMCP3204_H_ */
