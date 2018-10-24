/*
 * "Hello World" example.
 *
 * This example prints 'Hello from Nios II' to the STDOUT stream. It runs on
 * the Nios II 'standard', 'full_featured', 'fast', and 'low_cost' example
 * designs. It runs with or without the MicroC/OS-II RTOS and requires a STDOUT
 * device in your system's hardware.
 * The memory footprint of this hosted application is ~69 kbytes by default
 * using the standard reference design.
 *
 * For a reduced footprint version of this template, and an explanation of how
 * to reduce the memory footprint for a given application, see the
 * "small_hello_world" template.
 *
 */

#include <stdio.h>

#include <stdio.h>
#include "altera_avalon_mailbox_simple.h"
#include "altera_avalon_mailbox_simple_regs.h"
#include "system.h"
#include "io.h"

#include <stdio.h>
#include "system.h"

#include <io.h>
#include <sys/alt_irq.h>

#include <altera_avalon_mutex.h>
#include "altera_avalon_performance_counter.h"
#include "altera_avalon_mailbox_simple.h"
#include "altera_avalon_mailbox_simple_regs.h"


#define TASK_STACKSIZE 2048
OS_STK task_stk[TASK_STACKSIZE];
OS_STK task1_stk[TASK_STACKSIZE];

#define QUEUE_SIZE 10
OS_EVENT *queue_res;

typedef struct {
	int message;
} msg;

msg* msg_queue[10];
msg *some_msg;
alt_u32 *message;
unsigned int start, stop;


void rx_cb (void* message) {
    /* Get message read from mailbox */
	//alt_u32* data, message;
	alt_u32*data=message;
	if (message!= NULL) {
	printf ("Message received");
	}
else
  printf ("Incomplete receive");

}
void task_mailbox_polling(void* pdata)
{
	alt_u32* message;
	int timeout     = 50000;
	altera_avalon_mailbox_dev* mailbox_rcv;
	/* This example is running on receiver processor */
	mailbox_rcv = altera_avalon_mailbox_open("/dev/mailbox_simple_0", NULL,rx_cb);
	if (!mailbox_rcv){
		printf ("FAIL: Unable to open mailbox_simple");

	}
	/* For interrupt disable system */

	altera_avalon_mailbox_retrieve_poll(mailbox_rcv,message, timeout);
	if (message == NULL)
		printf ("Receive Error");
	else{
		printf ("Message received with Command 0x %x \n", message);
    	some_msg->message=message;
    	OSQPost(queue_res, some_msg);
	}
	altera_avalon_mailbox_close (mailbox_rcv);
}

void task_queue(void* pdata){
	msg* bla;
	INT8U err;
    printf (" task queue start \n");

	while(1){
		bla= (struct msg*)OSQPend(queue_res,0,&err);

		if(err==OS_NO_ERR)
			printf("getting message from queue and mailbox: %u \n",bla->message);
		else
			printf("Not getting message");
	}
}
int main()
{
	INT8U err;
	queue_res = OSQCreate(msg_queue, QUEUE_SIZE);
	OSTaskCreateExt(task_queue,
					NULL,
					(void *)&task1_stk[TASK_STACKSIZE-1],
					1,1,
					task1_stk,
					TASK_STACKSIZE,
					NULL,
					0);
	OSTaskCreateExt(task_mailbox_polling,
					NULL,
					(void *)&task_stk[TASK_STACKSIZE-1],
					2,2,
					task_stk,
					TASK_STACKSIZE,
					NULL,
					0);

	OSStart();
	return 0;

}

