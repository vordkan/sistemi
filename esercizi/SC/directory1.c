/*
    scrivere un programma in C Posiz in ambiente linux che data una directory da riga di comando
     cerchi tutti i file con un numero di hard link > 1 e ne stampi i nomi e i permessi del proprietario
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>

#define PATH_MAX 10

// Funzione per stampare i permessi del proprietario in formato leggibile
void print_owner_permissions(mode_t mode) {
    printf("%c%c%c",
           (mode & S_IRUSR) ? 'r' : '-',
           (mode & S_IWUSR) ? 'w' : '-',
           (mode & S_IXUSR) ? 'x' : '-');
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Uso: %s <directory>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    const char *dir_path = argv[1];
    DIR *dir = opendir(dir_path);
    if (dir == NULL) {
        perror("opendir");
        exit(EXIT_FAILURE);
    }

    struct dirent *entry;
    struct stat file_stat;
    char file_path[PATH_MAX];

    while ((entry = readdir(dir)) != NULL) {
        // Costruisci il percorso completo del file
        snprintf(file_path, PATH_MAX, "%s/%s", dir_path, entry->d_name);

        // Ottieni le informazioni sul file
        if (stat(file_path, &file_stat) == -1) {
            perror("stat");
            continue;
        }

        // Controlla se il numero di hard link è maggiore di 1
        if (file_stat.st_nlink > 1) {
            printf("File: %s, Permessi proprietario: ", entry->d_name);
            print_owner_permissions(file_stat.st_mode);
            printf("\n");
        }
    }

    closedir(dir);
    return 0;
}
