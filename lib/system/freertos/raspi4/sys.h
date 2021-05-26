/*
 * Copyright (c) 2016, Xilinx Inc. and Contributors. All rights reserved.
 * Copyright (c) 2020, Takayuki Imada (takayuki.imada@gmail.com)
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/*
 * @file	freertos/raspi4/sys.h
 * @brief	freertos Raspberry pi 4B system primitives for libmetal.
 */

#ifndef __METAL_FREERTOS_SYS__H__
#error "Include metal/sys.h instead of metal/freertos/@PROJECT_MACHINE@/sys.h"
#endif

#ifndef __METAL_FREERTOS_RASPI4_SYS__H__
#define __METAL_FREERTOS_RASPI4_SYS__H__

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief   metal_raspi4_irq_isr
 *
 * Raspberry pi 4B ISR
 *
 * @param[in] arg input argument, interrupt vector id.
 */
void metal_raspi4_irq_isr(void);

/**
 * @brief   metal_raspi4_irq_int
 *
 * Raspberry Pi 4B interrupt controller initialization.
 *
 * @return 0 for success, or negative value for failure
 */
int metal_raspi4_irq_init(unsigned int irq_vect);

#ifdef __cplusplus
}
#endif

#endif /* __METAL_FREERTOS_RASPI4_SYS__H__ */
