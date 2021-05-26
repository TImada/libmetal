/*
 * Copyright (c) 2014, Mentor Graphics Corporation
 * Copyright (c) 2016, Xilinx Inc. and Contributors. All rights reserved.
 * Copyright (c) 2020, Takayuki Imada <takayuki.imada@gmail.com>
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/*
 * @file	freertos/raspi4/sys.c
 * @brief	machine specific system primitives implementation.
 */

#include <stdint.h>
#include <metal/compiler.h>
#include <metal/sys.h>

#define DAIF_IRQ_BIT (0x1U << 1)

#ifdef __CACHE_SUPPORTED__
extern void flush_dcache_all(void);
extern void flush_dcache_range(void *addr, void *end);
extern void invalidate_dcache_all(void);
extern void invalidate_dcache_range(void *addr, void *end);
#endif /* __CACHE_SUPPORTED __ */

void sys_irq_restore_enable(unsigned int flags)
{
    (void)flags;
	__asm__ __volatile__("msr DAIFClr, %0\n\t" : : "i" (DAIF_IRQ_BIT)  : "memory");
}

unsigned int sys_irq_save_disable(void)
{
	__asm__ __volatile__("msr DAIFSet, %0\n\t" : : "i" (DAIF_IRQ_BIT)  : "memory");
	return 0;
}

void metal_machine_cache_flush(void *addr, unsigned int len)
{
#ifdef __CACHE_SUPPORTED__
    void *end = addr + (intptr_t)len - 0x1U;

	if (!addr && !len)
        flush_dcache_all();
	else
		flush_dcache_range(addr, end);
#else
    (void)addr;
    (void)len;
#endif /* __CACHE_SUPPORTED __ */
}

void metal_machine_cache_invalidate(void *addr, unsigned int len)
{
#ifdef __CACHE_SUPPORTED__
    void *end = addr + (intptr_t)len - 0x1U;

	if (!addr && !len)
        invalidate_dcache_all();
	else
		invalidate_dcache_range(addr, end);
#else
    (void)addr;
    (void)len;
#endif /* __CACHE_SUPPORTED __ */
}

/**
 * @brief poll function until some event happens
 */
void metal_weak metal_generic_default_poll(void)
{
	asm volatile("wfi");
}

void *metal_machine_io_mem_map(void *va, metal_phys_addr_t pa,
				      size_t size, unsigned int flags)
{
    (void)pa;
    (void)size;
    (void)flags;

	return va;
}
