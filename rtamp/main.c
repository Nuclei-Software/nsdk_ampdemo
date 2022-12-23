/*
 * Copyright (c) 2006-2019, RT-Thread Development Team
 * Copyright (c) 2019-Present Nuclei Limited. All rights reserved.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2020-03-26     Huaqi      the first version
 */

#include "nuclei_sdk_soc.h"
#include <rtthread.h>

#define THREAD_PRIORITY 2
#define THREAD_STACK_SIZE 512
#define THREAD_TIMESLICE 5
#define THREAD_NUM      5

#define LOOPS           100

/* Align stack when using static thread */
ALIGN(RT_ALIGN_SIZE)
static rt_uint8_t thread_stack[THREAD_NUM][THREAD_STACK_SIZE];
static struct rt_thread tid[THREAD_NUM];
unsigned long mhartid;

/* Thread entry function */
static void thread_entry(void* parameter)
{
    rt_uint32_t count = 0;

    while (1) {
        if (count % LOOPS == 0) {
            rt_kprintf("hartid %d: thread %d count: %d\n", mhartid, (rt_uint32_t)parameter, count);
        }
        count ++;
        rt_thread_mdelay(500);
    }
}

/* Thread demo */
int create_thread_demo(void)
{
    unsigned long i;
    for (i = 0; i < THREAD_NUM; i ++) {
        /* Create static threads */
        rt_thread_init(&tid[i], "thread", thread_entry, (void*)i, thread_stack[i],
                       THREAD_STACK_SIZE, THREAD_PRIORITY, THREAD_TIMESLICE);
    }

    /* Startup threads  */
    for (i = 0; i < THREAD_NUM; i ++) {
        rt_thread_startup(&tid[i]);
    }

    return 0;
}

int main(void)
{
    rt_uint32_t count = 0;
    rt_uint32_t dlyms = 0;

    mhartid = __RV_CSR_READ(CSR_MHARTID);

    dlyms = 2000 * mhartid;
    rt_kprintf("Wait %d ms for hartid %d to bring up\n", dlyms, mhartid);
    rt_thread_mdelay(dlyms);

    create_thread_demo();

    while (1) {
        if (count % LOOPS == 0) {
            rt_kprintf("hartid %d, main thread count: %d\n", mhartid, count);
        }
        rt_thread_mdelay(1000);
        count ++;
    }
}
