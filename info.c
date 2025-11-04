/*
* File: info.c
* Author: Alexander Kruschka
* Assignment: Lab 9 System Calls
* Section: 111
*/

#define _GNU_SOURCE
#include <time.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/utsname.h>
#include <sys/sysinfo.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{
    // Declare variables to use in program
    struct timespec time;
    struct utsname sys_info;
    int total_seconds;
    int hours;
    int minutes;
    int seconds;
    long long unsigned int nanoseconds;
    char host_name[256];

    // Get current time
    if (clock_gettime(CLOCK_REALTIME, &time) == -1)
    {
        printf("Error getting current time.");
        exit(EXIT_FAILURE);
    }

    // Determine total seconds passed since 12am today in CST
    total_seconds = time.tv_sec % 86400;
    total_seconds = total_seconds;
    hours = total_seconds / 3600;
    minutes = (total_seconds / 60) - (hours * 60);
    seconds = total_seconds % 60;

    // Convert seconds to nanoseconds
    nanoseconds = total_seconds * 1e9;
    nanoseconds = nanoseconds + time.tv_nsec;
        
    // Print total time in nanoseconds and formatted
    printf("The current time (UTC) in nanoseconds is: %lld\n", nanoseconds);
    printf("The current formatted time (UTC) is: %d:%d:%d:%lld\n", hours, minutes, seconds, nanoseconds % 1000000000);

    // Get name of network with error checking
    if(gethostname(host_name, sizeof(host_name)) == -1)
    {
        printf("Error getting system host name.");
        exit(EXIT_FAILURE);
    }
    
    // Print acquired name of network
    printf("System Network Name: %s\n", host_name);
    
    // Get system information with error checking
    if (uname(&sys_info) == -1)
    {
        printf("Error calling system info.");
        exit(EXIT_FAILURE);
    }

    // Print system information
    printf("Operating System Name: %s\n", sys_info.sysname);
    printf("Operating System Release: %s\n", sys_info.release);
    printf("Operating System Version: %s\n", sys_info.version);
    printf("Hardward Type: %s\n", sys_info.machine);
    printf("Number of Processors: %d\n", get_nprocs());

    // Calculate total physical memory
    long page_size = sysconf(_SC_PAGESIZE);
    long total_pages = sysconf(_SC_PHYS_PAGES);
    long total_memory = total_pages * page_size;

    // Print calculated physical memory
    printf("Total Physical Memory in Bytes: %ld\n", total_memory);

    // Calculate total free memory
    long free_pages = sysconf(_SC_AVPHYS_PAGES);
    long free_memory = free_pages * page_size;

    // Print calculated free memory
    printf("Total Free Memory in Bytes: %ld\n", free_memory);

    return 0;
}