#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <linux/i2c-dev.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <fcntl.h>

// I2C Linux device handle
int g_i2cFile;

// open the Linux device
void i2cOpen()
{
	g_i2cFile = open("/dev/i2c-1", O_RDWR);
	if (g_i2cFile < 0) {
		perror("i2cOpen");
		exit(1);
	}
}

// close the Linux device
void i2cClose()
{
	close(g_i2cFile);
}

// set the I2C slave address for all subsequent I2C device transfers
void i2cSetAddress(int address)
{
	if (ioctl(g_i2cFile, I2C_SLAVE, address) < 0) {
		perror("i2cSetAddress");
		exit(1);
	}
}

// write a 16 bit value to a register pair
// write low byte of value to register reg,
// and high byte of value to register reg+1
void pca9555WriteRegisterPair(uint8_t reg, uint16_t value)
{
	uint8_t data[3];
	data[0] = reg;
	data[1] = value & 0xff;
	data[2] = (value >> 8) & 0xff;
	if (write(g_i2cFile, data, 3) != 3) {
		perror("pca9555SetRegisterPair");
	}
}

// read a 8 bit value from a register pair
uint8_t pca9555ReadRegisterSingle(uint8_t reg)
{
	uint8_t data[2];
	data[0] = reg;
	if (write(g_i2cFile, data, 1) != 1) {
		perror("pca9555ReadRegisterPair set register");
	}
	if (read(g_i2cFile, data, 1) != 1) {
		perror("pca9555ReadRegisterPair read value");
	}
	return data[0];
}

// read a 16 bit value from a register pair
uint16_t pca9555ReadRegisterPair(uint8_t reg)
{
	uint8_t data[3];
	data[0] = reg;
	if (write(g_i2cFile, data, 1) != 1) {
		perror("pca9555ReadRegisterPair set register");
	}
	if (read(g_i2cFile, data, 2) != 2) {
		perror("pca9555ReadRegisterPair read value");
	}
	return data[0] | (data[1] << 8);
}

// set IO ports to input, if the corresponding direction bit is 1,
// otherwise set it to output
void pca9555SetInputDirection(uint16_t direction)
{
	pca9555WriteRegisterPair(6, direction);
}

// set the IO port outputs
void pca9555SetOutput(uint16_t value)
{
	pca9555WriteRegisterPair(2, value);
}

// read the IO port inputs
uint16_t pca9555GetInput()
{
	return pca9555ReadRegisterPair(0);
}

int main(int argc, char** argv)
{
	// test output value
	int v = 3;

	// direction of the LED animation
	int directionLeft = 1;

	// open Linux I2C device
	i2cOpen();

	// set address of the PCA9555
	i2cSetAddress(0x68);

	// set input for IO pin 15, rest output
//	pca9555SetInputDirection(1 << 15);

	// LED animation loop
	while (1) {
//		// if button is pressed, invert output
//		int xor;
//		if (pca9555GetInput() & 0x8000) {
//			xor = 0;
//		} else {
//			xor = 0xffff;
//		}
//		
//		// set current output
//		pca9555SetOutput(v ^ xor);
//
//		// animate LED position
//		if (directionLeft) {
//			v <<= 1;
//		} else {
//			v >>= 1;
//		}
//		if (v == 0x6000) {
//			directionLeft = 0;
//		}
//		if (v == 3) {
//			directionLeft = 1;
//		}
//
		uint8_t value;
		value = pca9555ReadRegisterSingle(0x75);
		printf("value = 0x%02x\n", value);
		// wait 100 ms for next animation step
		usleep(100000);
//		printf("loop going\n");
	}

	// close Linux I2C device
	i2cClose();

	return 0;
}
