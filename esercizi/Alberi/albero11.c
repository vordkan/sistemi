#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

int glob = 5;
int pid = 0;

void print_process_tree(int pid, int level) {
    int i;
    for (i = 0; i < level; i++)
        printf("  ");
    printf("|- PID: %d\n", pid);
    
    // Trova i figli di questo processo e li stampa ricorsivamente
    char command[50];
    sprintf(command, "pgrep -P %d", pid);
    FILE *fp = popen(command, "r");
    if (fp != NULL) {
        char output[50];
        while (fgets(output, sizeof(output), fp) != NULL) {
            int child_pid = atoi(output);
            print_process_tree(child_pid, level + 1);
        }
        pclose(fp);
    }
}

int main() {
    fork();
    glob--;
    
    if (fork()) {
        glob--;
    }
        
    if (pid == 0) {
        pid = fork();
        glob--;
    }
    
    printf("Sono %d figlio di %d. Glob: %d\n\n", getpid(), getppid(), glob);
    
    // Stampare l'albero dei processi dopo che tutti i processi figli sono stati creati
    printf("Process Tree:\n");
    print_process_tree(getpid(), 0);
    
    return 0;
}
