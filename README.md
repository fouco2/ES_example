This repo contains an exemple of Embedded system that i have design 

I choosed to present you a small project done during the Real-Time embedded systems course.
The idea of this TP was to implement and profile differents synchronysation technics for a multi-processor design. 
It was a three weeks project by group of two.

I found this project useful for my application because even if it was on a hardware design with two Nios-2 soft processor, the synchronisation technics between a multicore ARM processor or just a multithreads code running on a single ARM through a RTOS are the same.

# Lab_Multiprocessor
├── report                                      # report of our project 
├── Lab_MultiProcessor                          # Project folder
|   ├── hdl
│   |    ├── DE0_Nano_SoC_top_level.vhd 
│   |    └── prog_counter.vhd
│   └── quartus
│        ├── pin_assignment_DE0_Nano_SoC.tcl
│        ├── tp.qpf
│        ├── mp.qsys
│        └── software
│   |    |    ├── HardWare_counter 
│   |    |    ├── HardWare_mailbox
│   |    |    ├── HardWare_mutex
│   |    |    └── parallel_port_test.c
