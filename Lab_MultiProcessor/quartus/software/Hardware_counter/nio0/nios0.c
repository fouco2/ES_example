/*
 * "7 segment" example.
 *
 * This example prints a value on a private PIO every MS50 sample.
 * for nios0 use PIO0 and counter 0
 * for nios1 use PIO1 and counter 1
 * the PIO has to be wire at top level on a 7 segment digit
 */

#include <stdio.h>
#include "system.h"

#include <io.h>
#include <sys/alt_irq.h>

#include <altera_avalon_mutex.h>
#include "altera_avalon_performance_counter.h"

//counter address set value
#define RESET_COUNTER 4
#define START_COUNTER 8
#define STOP_COUNTER 12
#define IRQ_ENABLE_COUNTER 16 //bit 0
#define CLR_EOT_COUNTER 20 //bit 0
#define SET_COMP_COUNTER 28 //set a compare value
#define MS50 1000000

#define READ_VAL_COUNTER 0 //bit 0
#define READ_IRQ_COUNTER 16 //bit 0
#define READ_EOT_COUNTER 20 //bit 0
#define READ_COMP_COUNTER 28 //read compare value


//address offsets for the custom parallel port
#define DIR_OFFSET 0
#define WRITE_OFFSET 4
#define SET_OFFSET 12
#define CLEAR_OFFSET 16

int value_showhex(int value)
{
	static unsigned char _hex_digits_data[] = {0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92, 0x82, 0xf8, 0x80, 0x90};
	int led_value;
	led_value = _hex_digits_data[value & 0xF];
	//printf("led value %d\n",led_value);
	return led_value;
}

int main()
{
	printf("Hello from Nios II %d \n",ALT_CPU_CPU_ID_VALUE);
	alt_mutex_dev* mutex=altera_avalon_mutex_open(MUTEX_0_NAME);

	printf("Hello from Nios II %d \n",ALT_CPU_CPU_ID_VALUE);
	int i=0;
	int read;
	int j;
	for(j=0;j<315000;j++)
	{

	}
	printf("counter_start %d\n",IORD_32DIRECT(PROG_COUNTER_2_BASE, START_COUNTER));

	while(i<=1000){
		for(j=0;j<31500;j++)
		{

		}
		altera_avalon_mutex_lock(mutex,1);

		printf("nios0 read %d \n",IORD_32DIRECT(PROG_COUNTER_2_BASE,0));
		IOWR_32DIRECT(PROG_COUNTER_2_BASE, STOP_COUNTER, 0);
		printf("nios0 after stop read %d \n",IORD_32DIRECT(PROG_COUNTER_2_BASE,0));
		printf("nios0 after stop read %d \n",IORD_32DIRECT(PROG_COUNTER_2_BASE,0));

		altera_avalon_mutex_unlock(mutex);
		i++;
	}

  return 0;

}

