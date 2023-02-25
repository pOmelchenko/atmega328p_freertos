#include "FreeRTOS.h"
#include "task.h"
#include "led.h"
#include "apptastk.h"

#define mainLED_TASK_PRIORITY       (tskIDLE_PRIORITY)
#define mainLED_TASK_PRIORITY       (tskIDLE_PRIORITY+1)

void vLEDFlashTask(void *pvParams)
{
    vLEDInit();
    portTickType xLastWakeTime;
    const portTickType xFrequency = 100;
    xLastWakeTime = xTaskGetTickCount();

    for(;;) {
        vLEDToggle();
        vTaskDelayUntil(&xLastWakeTime, xFrequency);
    }
}

void vApplicationIdleHook(void);

int main(void)
{
    xTaskCreate(vLEDFlashTask, (int8_t*) "LED", configMINIMAL_STACK_SIZE, NULL, mainLED_TASK_PRIORITY, NULL);

    vTaskStartScheduler();

    return 0;
}

void vApplicationIdleHook(void)
{
//    vCoRoutineSchedule();
}
