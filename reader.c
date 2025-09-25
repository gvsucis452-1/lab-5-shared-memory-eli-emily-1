/**********************************************************
 *
 * reader.c
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
#include <string.h>

#define MAX_MSG_SIZE 4097 // 1B Flag + 4KB Msg  
#define READ_SHM 0

int main() {
    // Setup shared key
    const char PATH[] = "README.md";
    const key_t KEY = ftok(PATH, 'E');

    // Get & attach memory
    char *msg = malloc(MAX_MSG_SIZE);

    const int shmId = shmget(KEY, MAX_MSG_SIZE, READ_SHM);
    
    if (shmId < 0) { 
      perror ("Unable to get shared memory\n");
      free(msg);
      exit (1); 
    } 
    if (msg == NULL) {
        perror("Malloc failed\n");
        free(msg);
        exit(1);
    }

    // Attach shm to msg
    shmat(shmId, msg, 0); // Defaults to read/write permissions. Need write permission for FLAG byte.

    if(msg == (void*) -1) { 
        perror ("Unable to attach\n");
        free(msg);
        exit (1); 
    }

    // Handle new messages
    // 0 - Read mode
    // 1 - Write mode
    // 2 - Open mode ..? Probably not

    while (1)
    {
        // 1. Check lock byte
        // 2. Compare messages
        if (msg[0] == 0) {
            strcpy(msg[1], );
        // 3. Print if different/new
        // 4. Unlock
        }
    }
    
    free(msg);
    return 0;
}