/* 

RC Car w/ PICO using freeRTOS
Author: Odot!
Date: 12/4/2024
Time: 7:19AM

*/



#include "pico/stdlib.h"
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"

#define MOTOR_A_FWD 14
#define MOTOR_A_REV 15
#define MOTOR_B_FWD 16
#define MOTOR_B_REV 17

SemaphoreHandle_t xSemaphore;


void vTaskControlMotors(void *pvParameters){
	while(1){
		if (xSemaphoreTake(xSemaphore , portMAX_DELAY) == pdTRUE){
			char command = *(char *)pvParameters;

			switch(command){
				case 'F':
					gpio_put(MOTOR_A_FWD,1);
					gpio_put(MOTOR_B_REV,0);
					gpio_put(MOTOR_A_FWD,1);
					gpio_put(MOTOR_B_REV,0);
				break;

				case 'B':
                                        gpio_put(MOTOR_A_FWD,0);
                                        gpio_put(MOTOR_B_REV,1);
                                        gpio_put(MOTOR_A_FWD,0);
                                        gpio_put(MOTOR_B_REV,1);
                                break;


				case 'L':
                                        gpio_put(MOTOR_A_FWD,0);
                                        gpio_put(MOTOR_B_REV,1);
                                        gpio_put(MOTOR_A_FWD,1);
                                        gpio_put(MOTOR_B_REV,0);
                                break;


				case 'R':
                                        gpio_put(MOTOR_A_FWD,0);
                                        gpio_put(MOTOR_B_REV,0);
                                        gpio_put(MOTOR_A_FWD,0);
                                        gpio_put(MOTOR_B_REV,0);
                                break;
			}
			xSemphoreGive(xSemaphore);
		}
		vTaskDelay(100 / portTICK_PERIOD_MS);
	}
}



void vTaskBluetooth(void *pvParameters){
	char command;
	while(1){
		if(uart_is_readable(uart0)){
			command = uart_getc(uart0);

			xSemaphoreTake(xSemaphore, portMAX_DELAY);
			*(char *)pvParameters = command;
			xSemaphoreGive(xSemaphore);

		}
	vTaskDelay(50 / portTICK_PERIOD_MS);

	}

}



init main(){
	stdio_init_all();
	gpio_init(MOTOR_A_FWD);
	gpio_set_dir(MOTOR_A_FWD, GPIO_OUT);

	gpio_init(MOTOR_A_REV);
        gpio_set_dir(MOTOR_A_REV, GPIO_OUT);

	gpio_init(MOTOR_B_FWD);
        gpio_set_dir(MOTOR_B_FWD, GPIO_OUT);

	gpio_init(MOTOR_B_REV);
        gpio_set_dir(MOTOR_B_REV, GPIO_OUT);

	char command = 'S';

	xSemaphore = xSemaphoreCreateMutex();

	xTaskCreate(vTaskControlMotors, "Control Motors", 256, &command, 1, NULL):
	xTaskCreate(vTaskBluetooth, "Bluetooth", 256, &command, 1, NULL):

	vTaskStartScheduler();

	while(1);
	return(0);
}

