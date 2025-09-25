/**********************************************************
 *
 * sampleProgram1.c
 * CIS 451 Lab 5
 *
 * by Emily Heyboer and Eli Morgan
 *************************************************************/

#include <stdio.h> 
#include <stdlib.h> 
#include <sys/types.h> 
#include <sys/stat.h>
#include <sys/ipc.h> 
#include <sys/shm.h>


void reader( struct shmid shMemPtr) {
    while (1)
    {
        /* code */
    }
    
};

int main() {
    fork(); // Create 2nd instance
    reader();

    return 0;
}