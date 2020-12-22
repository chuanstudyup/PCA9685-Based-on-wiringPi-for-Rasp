#include "pca9685.h"

int main()
{
	wiringPiSetup();
	
	PCA9685 pca;
	pca.setPWM(0,1500);
	printf("End\n");
	return 0;
}
