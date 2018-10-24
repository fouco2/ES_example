# Embedded system design example

*This repo contains an example of Embedded system that I have designed*

I chose to present you a small project done during the [Real-Time embedded systems course](http://edu.epfl.ch/coursebook/fr/real-time-embedded-systems-CS-476). 
The idea of this TP was to implement and profile different synchronization technics for a multi-processor design, with two nios 2 on a Cyclone V FPGA.  
It was a three weeks project by a group of two.

I found this project useful for my application because even if it was on a hardware design with two Nios-2 soft processors, the synchronisation technics between a Multicores ARM processor or just a multithreads code running on a single ARM through an RTOS are the same.


**Lab_Multiprocessor** <br />
<pre>
├── report                              
└── Lab_MultiProcessor                 
    ├── hdl 
    │    ├── DE0_Nano_SoC_top_level.vhd             # Top Level hardware entity
    │    └── prog_counter.vhd                       # custom parallele port design 
    └── quartus
        ├── pin_assignment_DE0_Nano_SoC.tcl         # pin assignement for the board 
        ├── tp.qpf                                  # Quartus project file
        ├── mp.qsys                                 # Qsys entity
        └── software
            ├── HardWare_counter                    #C Code of the project, classified by synchronization type
            │    ├── nios0                          #C code for the first Nios 
            │    └── nios1                         #C code for the second Nios
            ├── HardWare_mailbox
            ├── HardWare_mutex
            └── parallel_port_test.c
 </pre>
