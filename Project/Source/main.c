#include <main.h>
#include <input.h>



int main (void){
	
	uint8_t direction=0x00;
	
	gpio_led_init();
	button_init();
	gyro_init();

	while(1) {
	direction=MEMS();
	LEDTest(direction);
	
	}
}
