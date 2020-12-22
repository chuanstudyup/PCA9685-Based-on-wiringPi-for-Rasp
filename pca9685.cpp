#include "pca9685.h"

/**
 * @brief  Instantiates a new PCA9685 PWM driver chip with the I2C address on the Wire interface. On Due we use Wire1 since its the interface on the 'default' I2C pins.
 * @param  addr The 7-bit I2C address to locate this chip, default is 0x40
 **/
PCA9685::PCA9685(uint8_t addr)
{
	_pcaFd = wiringPiI2CSetup(addr);
	if(_pcaFd >= 0)
	{
		double T = 20000;
		unsigned char prescale;
		double osc_clock = 25000000;
		unsigned char oldmode, newmode;
		//T /= 0.915;
		T /= 1000000;
		prescale = static_cast<unsigned char>(osc_clock/4096*T-1);
		//printf("prescale = 0X%x\n", prescale);
		oldmode = wiringPiI2CReadReg8(_pcaFd, PCA9685_MODE1);
		//printf("MODE1 = 0x%x\n", oldmode);
		
		newmode = (oldmode&0x7f) | 0x10; //准备进入sleep，设置时钟前必须先进入sleep模式
		wiringPiI2CWriteReg8(_pcaFd, PCA9685_MODE1, newmode);
		wiringPiI2CWriteReg8(_pcaFd, PCA9685_PRESCALE, prescale);
		oldmode &= 0xef; //清除sleep位
		wiringPiI2CWriteReg8(_pcaFd, PCA9685_MODE1, oldmode);
		delay(1);
		wiringPiI2CWriteReg8(_pcaFd, PCA9685_MODE1, oldmode | 0xa1);
		
		printf("PCA9685 deivce init successfully\n");
	}
	else
		perror("wiringPiI2CSetup error:");
}

/**
 * @brief  Set the pulseWidth of the channel
 * @param  channel  The pwm channel of PCA9685, 0-15
 * @param  pulseWidth The width of pluse, 0-20 000 us
 **/
void PCA9685::setPWM(uint8_t channel, uint32_t pulseWidth)
{
	uint16_t ON, OFF;
	ON = 0;
	OFF = static_cast<uint16_t> ((pulseWidth/20000.0 * 4096)*1.01); //最后的1.0067114是校准用的
	
	wiringPiI2CWriteReg16(_pcaFd, LED0_ON_L+4*channel, ON);
	wiringPiI2CWriteReg16(_pcaFd, LED0_OFF_L+4*channel, OFF);
}

