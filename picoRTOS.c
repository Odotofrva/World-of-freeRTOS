


// Simple Multithreading 
// Two Tasks: (Task 1) Blink LED and (Task 2) Read the status of a button pressed.




#include "pico/stdlib.h"	// issue when compiled. 
				// need to find the official pico library.
#include "FreeRTOS.h"
#include "task.h"


// task 1: 

void vTaskBlinkLED(void *pvParameters){
	const uint LED_PIN = 25;
	gpio_init(LED_PIN);
	gpio_set_dir(LED_PIN, GPIO_OUT);

	while(1){
		gpio_put(LED_PIN, 1);
		vTaskDelay(500 / portTICK_PERIOD_MS); // 500ms

		gpio_put(LED_PIN, 0);
		vTaskDelay(500 / portTICK_PERIOD_MS);
	}

}


// task 2

void vTaskReadButton(void *pvParameters){
	const uint BUTTON_PIN = 15;

	gpio_init(BUTTON_PIN);
	gpio_set_dir(BUTTON_PIN, GPIO_PIN);
	gpio_pull_up(BUTTON_PIN);


	while(1){
		if (!gpio_get(BUTTON_PIN)){
			printf("Button Pressed ODOT!!!\n");
	}
		vTaskDelay(100 / portTICK_PERIOD_MS);
}




int main() {
	stdio_init_all();

	xTaskCreate(vTaskBlinkLED, "Blink LED", 256, NULL, 1, NULL);
	xTaskCreate(vTaskReadButton, "Read Button", 256, NULL, 1, NULL);

	vTaskStartScheduler();

	while(1);
	return 0;
}

