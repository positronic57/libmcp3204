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

/**
 * @file libmcp3204.h
 * @brief 
 * Header file of libmcp3204 library. It contains the prototypes of all
 * functions available in the library, definitions of all macros
 * and constans.
 * 
 * @author Goce Boshkovski
 * @date 17-Aug-14
 * @copyright GNU General Public License v2.
 * 
 */

#ifndef LIBMCP3204_H_
#define LIBMCP3204_H_

/** \defgroup confBits Configuration bits for the MCP3204 */
/* @{ */
#define START_BIT 0x04
#define SINGLE_ENDED 0x02
#define DIFFERENTIAL 0xFB
#define CH_0 0x00
#define CH_1 0x40
#define CH_2 0x80
#define CH_3 0xC0
/* @} */

/** \defgroup inChannels Input channels definitions */
/* @{ */
/**
 * @brief Defines the input channel mode.
 */
typedef enum inputchannelmode
{
	singleEnded = 0, /**< Defines the input channel as single ended. */
	differential     /**< Defines the input channel as differential. */
} inputChannelMode;

/**
 * @brief Defines the input channel.
 */
typedef enum inputchannel
{
	CH0 = 0, /**< Input channel 0 of ADC. */
	CH1,     /**< Input channel 1 of ADC. */
	CH2,     /**< Input channel 2 of ADC. */
	CH3,     /**< Input channel 3 of ADC. */
	CH01,    /**< Differential input CH0 = IN+, CH1 = IN- */
	CH10,    /**< Differential input CH0 = IN-, CH1 = IN+ */
	CH23,    /**< Differential input CH2 = IN+, CH3 = IN- */
	CH32     /**< Differential input CH2 = IN-, CH3 = IN+ */
} inputChannel;
/* @} */
	
/**
 * @brief Defines the SPI mode.
 */
typedef enum spiMode
{
	mode_SPI_00 = 0, /**< Defines the SPI mode as 0,0. */
	mode_SPI_11	 /**< Defines the SPI mode as 1,1. */
} SPIMode;

/**
 * @brief MCP3204 is represented by this structure.
 */
typedef struct mcp3204
{
	uint16_t digitalValue;	/**< Output from the analog to digital conversion.*/
	float referenceVoltage; /**< Reference voltage applied on the ADC.*/
} MCP3204;

/** \defgroup libFunctions MAX7221 library functions */
/* @{ */

/**
 * @brief The function configures the SPI interface of Raspberry Pi 
 * according to MCP3204 SPI properties.
 *
 * @param[in] fd is a file descriptor used for accessing the SPI device file.
 * @param[in] dev is the device file of the SPI device.
 * @param[in,out] ad is a pointer to the structure that represents MCP3204.
 * @param[in] spi_mode defines the SPI mode.
 * @param[in] ref_voltage defines the reference voltage of the MCP3204 ADC.
 * @param[out] errorMessage is a pointer for the buffer that contains error messages.
 *
 * @return int 0 for successfull initialization, 1 in case of error.
 */
int MCP3204_init(int *fd, char *dev, MCP3204 *ad, SPIMode spi_mode, float ref_voltage, char *errorMessage);

/**
 * @brief Starts the AD conversion process and read the digital value
 * of the analog signal from MCP3204.
 *
 * @param[in] fd is a file descriptor used for accessing the SPI device file.
 * @param[in] channelMode defines the mode of the selected ADC input channel.
 * @param[in] channel selects the ACD input channel. 
 * @param[in,out] ad is a pointer to the structure that represents MCP3204.
 * @param[in] errorMessage is a pointer for the buffer that contains error messages.
 *
 * @return int 0 for successfull conversion 1 in case of failure.
 */
int MCP3204_convert(int fd, inputChannelMode channelMode, inputChannel channel, MCP3204 *ad,char *errorMessage);

/**
 * @brief The function returns the result from the AD conversion.
 *
 * @param[in] ad structure that represents MCP3204. 
 *
 * @return uint16_t output from the AD conversion.
 */
uint16_t MCP3204_getValue(MCP3204 ad);

/**
 * @brief The function calculates the value of the analog input.
 * 
 * @param[in] ad structure that represents MCP3204. 
 *
 * @return float value of the analog input.
 */
float MCP3204_analogValue(MCP3204 ad);
/* @} */

#endif /* LIBMCP3204_H_ */
