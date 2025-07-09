#include <stdio.h>
#include <sys/stat.h>
#include "scanner.h"

#define GREEN   "\033[1;32m"
#define RESET   "\033[0m"

int main(int argc, char* argv[]) {
    printf(GREEN "🔐 Simple Static Security Scanner for .c files\n" RESET);

    if (argc < 2) {
        printf("Usage: %s <file_or_directory_to_scan>\n", argv[0]);
        return 1;
    }

    struct stat path_stat;
    if (stat(argv[1], &path_stat) != 0) {
        perror("stat() error");
        return 1;
    }

    if (path_stat.st_mode & S_IFDIR) {
        scan_directory_recursive(argv[1]);
    } else if (path_stat.st_mode & S_IFREG) {
        scan_file(argv[1]);
    } else {
        printf("Unknown file type: %s\n", argv[1]);
    }

    return 0;
}
