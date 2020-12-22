#ifndef PCA9685_H
#define PCA9685_H

#include <wiringPi.h>
#include <wiringPiI2C.h>
#include <cstdio>
#include <cstdint>
using namespace std;

#define PCA9685_SUBADR1 0x2
#define PCA9685_SUBADR2 0x3
#define PCA9685_SUBADR3 0x4

#define PCA9685_MODE1 0x0
#define PCA9685_PRESCALE 0xFE

#define LED0_ON_L 0x6
#define LED0_ON_H 0x7
#define LED0_OFF_L 0x8
#define LED0_OFF_H 0x9

#define ALLLED_ON_L 0xFA
#define ALLLED_ON_H 0xFB
#define ALLLED_OFF_L 0xFC
#define ALLLED_OFF_H 0xFD

/**
 * @brief  Class that stores state and functions for interacting with PCA9685 PWM chip
 */
class PCA9685{
	public:
		
		PCA9685(uint8_t addr = 0x40);
		void setPWM(uint8_t channel, uint32_t pulseWidth);
		
	private:
		int _pcaFd;
};
#endif
