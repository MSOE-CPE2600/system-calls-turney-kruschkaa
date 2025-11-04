/*
* File: pmod.c
* Author: Alexander Kruschka
* Assignment: Lab 9 System Calls
* Section: 111
*/

#include <unistd.h>
#include <stdio.h>
#include <time.h>

int main(int argc, char* argv[])
{
    // Declare and initialize wait time
    struct timespec wait_time, end_time;
    wait_time.tv_sec = 1;
    wait_time.tv_nsec = 837272638;
    
    // Print PID for viewing purposes
    printf("Process PID: %d\n", getpid());

    // Lower priority by 10;
    nice(10);
    printf("Lowered priority by 10.\n");

    // Wait for specified wait time
    nanosleep(&wait_time, &end_time);

    // Exit program with goodbye message
    printf("Waited for 1,837,272,638 nanoseconds, exiting program.\n");
    return 0;
}