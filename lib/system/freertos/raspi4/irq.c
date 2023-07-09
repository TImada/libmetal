/*
 * Copyright (c) 2016 - 2017, Xilinx Inc. and Contributors. All rights reserved.
 * Copyright (c) 2020, Takayuki Imada <takayuki.imada@gmail.com>
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/*
 * @file    freertos/raspi4/irq.c
 * @brief    FreeRTOS libmetal Raspberry pi 4B irq controller definitions.
 */

#include <errno.h>
#include <metal/irq_controller.h>
#include <metal/sys.h>
#include <metal/log.h>
#include <metal/mutex.h>
#include <metal/list.h>
#include <metal/utilities.h>
#include <metal/alloc.h>

#define BASE_IRQ    (44U)
#define NUM_IRQS    (1U)

static struct metal_irq irqs[NUM_IRQS]; /* Consider only one IRQ */
static unsigned int vector = 0x0;

static void metal_raspi4_irq_set_enable(struct metal_irq_controller *irq_cntr,
                     int irq, unsigned int state)
{
    /* Do nothing here (IRQ enabling is done in metal_raspi4_irq_register()) */
    (void)irq_cntr;
    (void)irq;
    (void)state;
    return;
}

/** Raspberry Pi 4B common platform IRQ controller */
static METAL_IRQ_CONTROLLER_DECLARE(raspi4_irq_cntr,
                    BASE_IRQ, 1,
                    NULL,
                    metal_raspi4_irq_set_enable, NULL,
                    irqs);

/**
 * @brief default handler
 */
void metal_raspi4_irq_isr(void)
{
    unsigned int tmp;

    tmp = vector - BASE_IRQ;
    if (tmp) { /* tmp should be 0U */
        return;
    }
    
    (void)metal_irq_handle(&irqs[tmp], (int)vector);
    return;
}

int metal_raspi4_irq_init(unsigned int irq_vect)
{
    int ret = 0;

    vector = irq_vect;
    ret =  metal_irq_register_controller(&raspi4_irq_cntr);
    if (ret < 0) {
        metal_log(METAL_LOG_ERROR, "%s: register irq controller failed.\n",
              __func__);
    }
    return ret;
}
