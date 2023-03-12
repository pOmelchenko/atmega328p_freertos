#include <FreeRTOS.h>
#include <task.h>
#include <led.h>
#include "apptastk.h"

_Noreturn void vLEDFlashTask(void *pvParam)
{
    vLEDInit();
    portTickType xLastWakeTime;
    const portTickType xFrequency = 1000 / portTICK_PERIOD_MS;
    xLastWakeTime = xTaskGetTickCount();

    for(;;) {
        vLEDToggle();
        vTaskDelayUntil(&xLastWakeTime, xFrequency);
    }
}

void vApplicationIdleHook(void);

int main(void)
{
    xTaskCreate(
            vLEDFlashTask,
            "LED",
            configMINIMAL_STACK_SIZE,
            NULL,
            tskIDLE_PRIORITY,
            NULL);

    vTaskStartScheduler();

    return 0;
}

void vApplicationIdleHook(void)
{
//    vCoRoutineSchedule();
}
