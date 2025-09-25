by Emily Heyboer and Eli Morgan

1. The sample programs prints two pointers: one that points to the start of shared memory and one that points to the end (labeled a and b respectively).

2. The function `shmget()` takes 3 parameters: the key, shared memory size, and flags. The key is used to identify the shared memory segment. When passed `IPC_PRIVATE` (like in the sample), `shmget()` will create a new memory segment. Size determines, rounded to the next multiple of `PAGE_SIZE`, how big this memory segment should be. Finally, the flags control the behavior of `shmget()` and the permissions applied to the shared memory. For example, `IPC_CREAT` (which is not necessary in this case), instructs `shmget()` to create a new shared memory segment if one using that key doesn't already exist. The flag also determines shared memory segment permissions (which are similar to file permissions). So in this case, `S_IRUSR` and `S_IWUSR` specify that the user should have read and write access respectively.

5.
![the output of ipcs showing a leftover shared memory segment](./ipcs-leftover.png)
![the output of ipcs before and after calling ipcrm](./ipcs-post-ipcrm.png)