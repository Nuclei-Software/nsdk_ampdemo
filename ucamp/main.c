#include <stdint.h>
#include <ucos_ii.h>

#include "nuclei_sdk_soc.h"

#define mainQUEUE_LENGTH (1)
static void prvSetupHardware(void);
extern void idle_task(void);

void prvSetupHardware(void)
{
}

#define STK_LEN 256

OS_STK task1_stk[STK_LEN];
OS_STK task2_stk[STK_LEN];
OS_STK task3_stk[STK_LEN];
OS_STK start_stk[STK_LEN];

#define TASK1_PRIO 13
#define TASK2_PRIO 12
#define TASK3_PRIO 11
#define TASK_START_PRIO 10

unsigned long mhartid;
#define LOOPS           50

void task1(void* args)
{
    int cnt = 0;
    for (;;) {
        if (cnt % LOOPS == 0) {
            printf("hartid %d, task1 is running... %d\r\n", mhartid, cnt);
        }
        cnt++;
        OSTimeDlyHMSM(0, 0, 2, 0);
    }
}

void task2(void* args)
{
    int cnt = 0;
    for (;;) {
        if (cnt % LOOPS == 0) {
            printf("hartid %d, task2 is running... %d\r\n", mhartid, cnt);
        }
        cnt++;
        OSTimeDlyHMSM(0, 0, 1, 0);
    }
}

void task3(void* args)
{
    int cnt = 0;
    for (;;) {
        if (cnt % LOOPS == 0) {
            printf("hartid %d, task3 is running... %d\r\n", mhartid, cnt);
        }
        cnt++;
        OSTimeDlyHMSM(0, 0, 1, 0);
    }
}

void start_task(void* args)
{
    printf("hartid %d, start all task...\r\n", mhartid);
    OSTaskCreate(task1, NULL, &task1_stk[STK_LEN - 1], TASK1_PRIO);
    OSTaskCreate(task2, NULL, &task2_stk[STK_LEN - 1], TASK2_PRIO);
    OSTaskCreate(task3, NULL, &task3_stk[STK_LEN - 1], TASK3_PRIO);
    OSTaskSuspend(TASK_START_PRIO);
}

int main(void)
{
    uint32_t dlyms = 0;

    mhartid = __RV_CSR_READ(CSR_MHARTID);

    dlyms = 2000 * mhartid;
    printf("Wait %d ms for hartid %d to bring up\n", dlyms, mhartid);
    delay_1ms(dlyms);

    printf("Start ucosii for hartid %d...\r\n", mhartid);
    prvSetupHardware();
    OSInit();
    OSTaskCreate(start_task, NULL, &start_stk[STK_LEN - 1], TASK_START_PRIO);
    printf("create start task success for hartid %d\r\n", mhartid);
    OSStart();
    while (1) {
    }
}
