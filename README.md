### C Library for communication with Microchip MCP3204 on Raspberry Pi

#### Short Description

Libmcp3204 is a user space C library for communication with Microchip MCP3204 12-bit 4 channel ADC over SPI interface on Linux systems.
It provides access to MCP3204 ADC using the SPI kernel module present on the system (spi_bcm2708 in case of Rasperry Pi with Raspbian).
The low level SPI communication (data and control signals) is done by the kernel module, while the library implements the data exchange 
protocol supported by the MCP3204 ADC.

Ioctl() and SPI_IOC_MESSAGE(N) requests are used to achieve a full-duplex synchronous communication with the ADC. It supports single ended and differential
input channel modes of MCP3204. The SPI communication can be done either by SPI mode 0,0 or SPI mode 1,1. 


#### Supported Hardware

The library has been developed and tested on Raspberry Pi.
Should work on any other Linux system with SPI hardware and apropriate kernel module.

#### Usage

The initialization of the on-board SPI and MCP3204 is done via MCP3204_init() function.
For example, if MPC3204 is connected to SPI device /dev/spidev0.1, with reference voltage 2.491V and SPI mode is 0,0 the init function is:

	int fd;
	MCP3204 ADC;
	char error[20];
		
	MCP3204_init(&fd,"/dev/spidev0.1",&ADC,mode_SPI_00,2.491,error);
  
where:

 - fd is a file descriptor required for accessing the SPI device file;
 - ADC is the structure that represents MCP3204;
 - mode_SPI_00 defines the SPI mode as 0,0;
 - error points to the error message string generated in case of a failure.

The init function sets the SPI clock frequency by default to 100KHz. The current version of the library doesn't support change of this parameter. 
  
After the init process is successfully finished, MCP3204_convert() function starts the AD conversion of the selected analog input channel that can be
configured as single-ended or pseudo-differential pair. If the analog input is connected to channel 0, then the AD conversion is started
with:

	MCP3204_convert(fd,singleEnded,CH0,&ADC,error);

where:

 - fd is the same file descriptor as the one from MCP3204_init() function;
 - ADC is the structure that represents MCP3204;
 - error points to the error message string generated in case of a failure.


The digital value that is a result of the conversation and the original analog value are available via MCP3204_getValue() and MCP3204_analogValue() functions
accordingly:

	MCP3204_getValue(ADC); //returns the result of the ADC
	MCP3204_analogValue(ADC); //returns the analog value of the input

#### Documentation and Examples

The doc folder contains detailed description of the library.

The library source code is distributed with example program that demonstrates the usage of the libmcp3024 for temperature measurement with TMP36 analog temperature
sensor.

#### Test Hardware

The library has been developed and tested on several generations of Raspberry Pi running Raspian.

**WARNING:** 

The library source is provided as it is without any warranty. Use it on your own risk!

The author does not take any responsibility for the damage caused while using this software.
 


