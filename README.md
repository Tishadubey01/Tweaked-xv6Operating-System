# Overview

Various improvements have been made to the xv6 operating system such as the waitx and getpinfo syscall.
Xv6 is based on risc-v platform.
Scheduling techniques such as FCFS, PBS, and MLFQ have also been implemented.

## Run the shell

make qemu SCHEDULER=[FLAG]
FLAG=PBS,RR,FCFS,MLFQ
### Task 1
strace Syscall
Adding System Call
The files that have been modified are:

- user.h
- usys.S
- syscall.h
- syscall.c
- sysproc.c
- defs.h
- proc.c
- proc.h

The fields ctime (CREATION TIME),
etime (END TIME),
rtime (calculates RUN TIME)
& iotime (IO TIME) fields have been added to proc structure of proc.h file

- there is a separate strace.c file for trace system call

##### Calculating ctime, etime and rtime
ctime is recoreded in allocproc() function of proc.c (When process is born). It is set to ticks.

etime is recorded in exit() function (i.e when child exists, ticks are recorded) of proc.c.

rtime is updated in trap() function of trap.c. IF STATE IS RUNNING , THEN UPDATE rtime.

iotime is updated in trap() function of trap.c.(IF STATE IS SLEEPING , THEN UPDATE iotime.

- Tester file - time command.

time inputs a command and exec it normally

Uses waitx instead of normal wait

Displays wtime and rtime along with status that is the same as that returned by wait() syscall

procdump Sys Call
The files modified are:

- defs.h
- proc.c
- proc.h
  syscall gives a detailed list of all the processes present in the system at that particular instant. It loops through the ptable to obtain the details of the processes. wtime is calculates as current ticks - time of entering queue, which is updated everytime a process enters a queue.

#### setPriority Sys Call
*set_priority syscall The ser_priority syscall takes in two parameters (PID, PRIORITY) and sets the priority of the process with that PID to the one passed as a parameter.

### Task 2 - Scheduling techniques
All scheduling techiniques have been added to the scheduler function in proc.c. Add the flag SCHEDULER to choose between RR, FCFS, PBS, and MLFQ. This has been implemented in Makefile.

#### First come - First Served (FCFS)
Non preemptive ​policy so we removed the the yield() call in trap.c in case of FCFS as shown:

Iterate through the process table to find the process with min creation time as follows:

Check if the process found is runnable, if it is, execute it

#### Priority Based Scheduler
Assign default priority 60 to each entering process.

Set the default priority of a process as 60. The lower the value the higher the priority.

Dynamic Priority(DP) is calculated from static priority and niceness.

Niceness is defined in the pdf.
Find the minimum priority process by iterating through the process table (min priority number translates to maximum preference):

#### RR
To implement RR for same priority processes, iterate through all the processes again. Whichever has same priority as the min priority found, execute that. yield() is enabled for PBS in proc.c() so the process gets yielded out and if any other process with same priority is there, it gets executed next.

We also have a check within the 2nd loop to ensure no other process with lower priority has come in. If it has, we break out of the 2nd loop, otherwise RR is executed for same priority processes.

set_priority() calls yield() when the priority of a process becomes lower than its old priority.

#### MLFQ
We declared 5 queues with different priorities based on time slices, i.e. 1, 2, 4, 8, 16 timer ticks, as shown:

These queues contain runnable processes only.

The add process to queue and remove process from queue functions take arguments of the process and queue number and make appropriate changes in the array(pop and push).

Ageing is implemented by iterating through queues 1-4 and checking if any process has exceeded the age limit and subsequently moving it up in the queues.

Next, we iterate over all the queues in order, increase the tick associated with that process and its number of runs.

If that's the case, we call yield and push the process to the next queue. Otherwise increment the ticks and let the process remain in queue.
Release table lock once the process is over

Tester files
schedulertest.c
