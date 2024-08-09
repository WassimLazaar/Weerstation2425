/*
 * Copyright (c) 2016 Intel Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
 */


/* 1000 msec = 1 sec */
#define SLEEP_TIME_MS   500

int main(void)
{

	while (1) {
		printk("main branch placeholder\n");

		printk("een extra feature toegevoegd\n");
		printk("een extra feature toegevoegd2\n");
		printk("multithreading placeholder\n");
		k_msleep(SLEEP_TIME_MS);
	}
	return 0;
}
