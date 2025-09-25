/**********************************************************
 *
 * writer.c
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

#define SHM_SIZE 4097
int shmId;
void* shared;

void handleSignal(int signal) {
    printf("Shutting down...\n");
    if (shmdt (shared) < 0) { 
        perror ("Unable to detach\n"); 
        exit (1); 
    } 
    if (shmctl (shmId, IPC_RMID, 0) < 0) { 
        perror ("Unable to deallocate\n"); 
        exit(1); 
    }
    exit(0);
}

int main(int argc, char* argv[]) {
    key_t key = ftok("README.md", 'e');

    if ((shmId = shmget(key, SHM_SIZE, IPC_CREAT|S_IRUSR|S_IWUSR)) < 0) { 
        perror ("Unable to get shared memory\n"); 
        exit (1); 
    } 
    if ((shared = shmat (shmId, 0, 0)) == (void*) -1) { 
        perror ("Unable to attach\n"); 
        exit (1); 
    }

    signal(SIGINT, handleSignal);

    char* turn = shared;
    *turn = 0;
    char* message = shared + 1;

    while (1) {
        if (*turn) {
            continue;
        }
        
        printf("> ");
        fgets(message, SHM_SIZE - 1, stdin);

        *turn = 1;
    }
}