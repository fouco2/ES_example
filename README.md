*This repo contains an exemple of Embedded system that i have design*

I choosed to present you a small project done during the Real-Time embedded systems course.
The idea of this TP was to implement and profile differents synchronysation technics for a multi-processor design. 
It was a three weeks project by group of two.

I found this project useful for my application because even if it was on a hardware design with two Nios-2 soft processor, the synchronisation technics between a multicore ARM processor or just a multithreads code running on a single ARM through a RTOS are the same.

**Lab_Multiprocessor**
├── report                                      # report of our project <br />
├── Lab_MultiProcessor                          # Project folder<br />
│    ├── hdl <br />
│    │    ├── DE0_Nano_SoC_top_level.vhd         # Top Level hardware entity<br />
│    │    └── prog_counter.vhd                   # custom parallele port design<br />
│    └── quartus <br />
│    │    ├── pin_assignment_DE0_Nano_SoC.tcl    # TCL of the board<br />
│    │    ├── tp.qpf                             # quartus project file<br />
│    │    ├── mp.qsys                            # qsys deign <br />
│    │    └── software<br />
│    │    │    ├── HardWare_counter              # C Code and bsp for the two processor<br />
│    │    │    ├── HardWare_mailbox<br />
│    │    │    ├── HardWare_mutex<br />
│    │    │    └── parallel_port_test.c<br />
