// Working with Arduino and freeRTOS
// Multithreading 2 tasks 
// cannot compile due to needs of the Arduio library installation.


#include <Arduino.h>
#include <freeRTOS.h>




int count1 = 0;
int count2 = 0;

void task1(void * parameters) {
	for(;;){ 					// infinite for loop
		Serial.print('Task 1 counter: ");
		Serial.println(count1++);
		vTaskDelay(1000 / portTICK_PERIOD_MS);
	}
}


void task2(void * parameters){
	for(;;){
		Serial.print('Task 2 counter : ");
		Serial.println(count1++);
		vTaskDelay(1000 / portTICK_PERIOD_MS);
	}

}




void setup(){
	Serial.begin(9600);



	xTaskCreate(
		task1,		// function name
		'Task 1', 	// task name
		1000,  		// stack size
		NULL,  		// task parameters
		1,		// task priority
		NULL		// tasks handle
	);


	xTaskCreate(task2,'Task 2', 1000, NULL, 1, NULL);

}


void loop(){

}

