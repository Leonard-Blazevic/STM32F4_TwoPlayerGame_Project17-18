#include <main.h>
#include <gyro.h>



int main (void){
	
	uint8_t direction=0;
	
	GpioLEDInit();
	
	GyroInit();

	while(1) {
	direction=GetDirection();
	LEDTest(direction);
	
	}
}
