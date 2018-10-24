/*
 * 
 *
 * This example prints 'Hello from Nios II' to the STDOUT stream.
 * after that it send a message to the hardware mailbox and indicate
 * on the UART is transfer is done or not. 
 *
 */

#include <stdio.h>
#include "system.h"
#include "io.h"

#include <altera_avalon_mutex.h>
#include "altera_avalon_performance_counter.h"
#include "altera_avalon_mailbox_simple.h"
#include "altera_avalon_mailbox_simple_regs.h"

void tx_cb (void* report, int status) {
    if (!status) {
       printf("Transfer done");
    } else {
       printf ("“error in transfer");
    }
}
int main(){

	printf("Hello from Nios II!\n");

	alt_u32 message= 1;
	int timeout     = 50000;
	alt_u32 status;
	altera_avalon_mailbox_dev* mailbox_sender;
	mailbox_sender = altera_avalon_mailbox_open("/dev/mailbox_simple_0", tx_cb, NULL);
	if(!mailbox_sender){
		printf ("FAIL: Unable to open mailbox_simple");
		return 1;
	}

	timeout = 0;
	status = altera_avalon_mailbox_send(mailbox_sender, message,timeout, POLL);
	if (status)
		printf ("error in transfer");
	else
		printf ("Transfer done");
	altera_avalon_mailbox_close(mailbox_sender);

	return 0;
}
