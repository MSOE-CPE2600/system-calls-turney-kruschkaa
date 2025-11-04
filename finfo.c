/*
* File: finfo.c
* Author: Alexander Kruschka
* Assignment: Lab 9 System Calls
* Section: 111
*/

#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <sys/stat.h>

int main(int argc, char* argv[])
{
    // Declare variables to be used
    int fp;
    struct stat stat_info;
    mode_t permissions;
    time_t last_modified_time;
    struct tm *tm_info;
    char formatted_time[80];
    
    // Check if file name entered, if not, exit with error
    if (argc < 2)
    {
        printf("No file name entered, please enter a valid file name.\n");
        exit(EXIT_FAILURE);
    }

    // Open file as check for existance, if not, exit with error
    fp = open(argv[1], O_RDONLY);
    if (fp == -1)
    {
        printf("Error, invalid file entered.\n");
        exit(EXIT_FAILURE);
    }

    // Get file info with stat and error check
    if (stat(argv[1], &stat_info) == -1)
    {
        printf("Error, failed to get stat info of file.\n");
        exit(EXIT_FAILURE);
    }

    // Print file type
    printf("File type: ");
    if (S_ISREG(stat_info.st_mode)) {
        printf("Regular File\n");
    } else if (S_ISDIR(stat_info.st_mode)) {
        printf("Directory\n");
    } else if (S_ISBLK(stat_info.st_mode)) {
        printf("Block Device\n");
    } else if (S_ISCHR(stat_info.st_mode)) {
        printf("Character Devide\n");
    } else if (S_ISFIFO(stat_info.st_mode)) {
        printf("FIFO/Pipe\n");
    } else if (S_ISLNK(stat_info.st_mode)) {
        printf("Symlink\n");
    } else {
        printf("Socket\n");
    }

    // Get file permissions
    permissions = stat_info.st_mode & (S_IRWXU | S_IRWXG | S_IRWXO);

    // Print permissions of file in readable format
    printf("Permissions:\n");
    printf("-Owner: %s%s%s\n",
           (permissions & S_IRUSR) ? "r" : "-",
           (permissions & S_IWUSR) ? "w" : "-",
           (permissions & S_IXUSR) ? "x" : "-");
    printf("-Group: %s%s%s\n",
           (permissions & S_IRGRP) ? "r" : "-",
           (permissions & S_IWGRP) ? "w" : "-",
           (permissions & S_IXGRP) ? "x" : "-");
    printf("-Other: %s%s%s\n",
           (permissions & S_IROTH) ? "r" : "-",
           (permissions & S_IWOTH) ? "w" : "-",
           (permissions & S_IXOTH) ? "x" : "-");

    // Get file owner UID and print it
    printf("Owner UID: %d\n", stat_info.st_uid);

    // Get file size in bytes and print
    printf("File Size: %ld Bytes\n", (long)stat_info.st_size);

    // Get file time information and format into readable format
    last_modified_time = stat_info.st_mtime;
    tm_info = localtime(&last_modified_time);
    strftime(formatted_time, sizeof(formatted_time), "%m-%d-%Y %H:%M:%S", tm_info);

    // Print formatted time of last modification
    printf("Date of Last Modification: %s\n", formatted_time);

    // Close file pointer and quit program
    close(fp);
    return 0;
}