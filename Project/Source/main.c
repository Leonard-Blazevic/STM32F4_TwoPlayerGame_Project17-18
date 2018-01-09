#include <main.h>
#include <input.h>

int main (void){
	
	gpio_led_init();
	button_init();
	gyro_init();
	
	while(1) {
		MEMS();
	}
}
