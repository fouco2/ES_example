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
//counter address set value
#define RESET_COUNTER 4
#define START_COUNTER 8
#define STOP_COUNTER 12
#define IRQ_ENABLE_COUNTER 16 //bit 0
#define CLR_EOT_COUNTER 20 //bit 0
#define SET_COMP_COUNTER 28 //set a compare value
#define MS50	25000000

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
	int i=0;
	IOWR_32DIRECT(PIO_1_BASE,4,1); //output mode
	IOWR_32DIRECT(PIO_1_BASE,0,0x4f& value_showhex(i++));

	IOWR_32DIRECT(PROG_COUNTER_1_BASE, RESET_COUNTER, 0);
	IOWR_32DIRECT(PROG_COUNTER_1_BASE, SET_COMP_COUNTER, MS50);
	IOWR_32DIRECT(PROG_COUNTER_1_BASE, CLR_EOT_COUNTER, 1);
	IOWR_32DIRECT(PROG_COUNTER_1_BASE, START_COUNTER, 0);
	printf("counter_start %d\n",IORD_32DIRECT(PROG_COUNTER_1_BASE, START_COUNTER));
	while(i<=100){
		if(IORD_32DIRECT(PROG_COUNTER_1_BASE, READ_EOT_COUNTER)==3){
			IOWR_32DIRECT(PIO_1_BASE,0,value_showhex(i%10));
			IOWR_32DIRECT(PROG_COUNTER_1_BASE, RESET_COUNTER, 0);
			IOWR_32DIRECT(PROG_COUNTER_1_BASE, CLR_EOT_COUNTER, 1);
			IOWR_32DIRECT(PROG_COUNTER_1_BASE, START_COUNTER, 0);
			i++;
		}
	}
  return 0;

}

