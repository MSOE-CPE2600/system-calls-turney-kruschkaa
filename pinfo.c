/*
* File: pinfo.c
* Author: Alexander Kruschka
* Assignment: Lab 9 System Calls
* Section: 111
*/

#define _GNU_SOURCE
#include <stdio.h>
#include <sched.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/resource.h>

int main(int argc, char* argv[])
{
    // Declare variables to be used
    int pid;
    int process_priority;
    int policy;

    // Establish PID to be used from either user input if entered or the current executing process
    if (argc > 1)
    {
        pid = atoi(argv[1]);
    }
    else
    {
        pid = getpid();
    }
    
    // Get information about PID process
    process_priority = getpriority(PRIO_PROCESS, pid);
    policy = sched_getscheduler(pid);

    // Check if invalid policy, if it is, then the PID doesn't exist
    if (policy < 0)
    {
        printf("Error getting process or invalid PID.\n");
        exit(EXIT_FAILURE);
    }

    // Print pid and process priority
    printf("PID: %d\n", pid);
    printf("Process Priority: %d\n", process_priority);

    // Print scheduling method as specific text
    printf("Scheduling method: ");
    if (policy == 0)
    {
        printf("SCHED_OTHER (normal-time sharing)\n");
    }
    else if (policy == 1)
    {
        printf("SCHED_FIFO (real-time fifo)\n");
    }
    else if (policy == 2)
    {
        printf("SCHED_RR (real-time round robin)\n");
    }
    else if (policy == 3)
    {
        printf("SCHED_BATCH (batch processing)\n");
    }
    else if (policy == 4)
    {
        printf("SCHED_IDLE (very low priority)\n");
    }
    else
    {
        printf("Unknown scheduling method.\n");
    }

    return 0;
}