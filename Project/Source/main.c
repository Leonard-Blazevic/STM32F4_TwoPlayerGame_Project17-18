#include <main.h>
#include <gyro.h>



int main (void){
	
	uint8_t direction=0;
	
	gpio_led_init();
	
	gyro_init();

	while(1) {
	direction=get_direction();
	LEDTest(direction);
	
	}
}
