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
#include <signal.h> // Required on Linux

#define SHM_SIZE 4097 // 1B Flag + 4KB Msg  
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
    exit(0);
}

int main() {
    shared = malloc(SHM_SIZE);
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

    char* reader = shared;
    if (*reader) {
        reader = shared + 1;
    }
    *reader = 1;
    char* message = shared + 2;

    // zk The program needs to support at least _two_ readers. 
    while (1)
    {
        if (*reader) {
            continue;
        }
        printf("%s", message);

        *reader = 1;
    }
    
    return 0;
}