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
#include <signal.h> // Required on Linux

#define SHM_SIZE 4098
#define PATH "README.md"
#define FTOK_ID 'e'
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
    key_t key = ftok(PATH, FTOK_ID);

    if ((shmId = shmget(key, SHM_SIZE, IPC_CREAT|S_IRUSR|S_IWUSR)) < 0) { 
        perror ("Unable to get shared memory\n"); 
        exit (1); 
    } 
    if ((shared = shmat (shmId, 0, 0)) == (void*) -1) { 
        perror ("Unable to attach\n"); 
        exit (1); 
    }

    signal(SIGINT, handleSignal);

    char* reader1 = shared;
    char* reader2 = shared + 1;
    *reader1 = 0;
    *reader2 = 0;
    char* message = shared + 2;
    // zk Nice use of pointers to fit both into 
    // a single shared memory space. 

    while (1) {
        if (!(*reader1 && *reader2)) {
            continue;
        }

        printf("> ");
        fgets(message, SHM_SIZE - 2, stdin);

        *reader1 = 0;
        *reader2 = 0;
    }
}