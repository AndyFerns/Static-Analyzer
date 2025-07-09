#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <stdlib.h>
#include "scanner.h"
#include "export.h"

#define GREEN "\033[1;32m"
#define RESET "\033[0m"

int main(int argc, char* argv[]) {
    printf(GREEN "Simple Static Security Scanner for .c files\n" RESET);

    if (argc < 2) {
        printf("Usage: %s <target> [--summary] [--output json|csv]\n", argv[0]);
        return 1;
    }

    const char* target = argv[1];
    int summary_mode = 0;
    int output_json = 0;
    int output_csv = 0;

    for (int i = 2; i < argc; i++) {
        if (strcmp(argv[i], "--summary") == 0) summary_mode = 1;
        else if (strcmp(argv[i], "--output") == 0 && i + 1 < argc) {
            if (strcmp(argv[i + 1], "json") == 0) output_json = 1;
            else if (strcmp(argv[i + 1], "csv") == 0) output_csv = 1;
            i++;
        }
    }

    Warning warnings[1000];
    int warning_count = 0;

    struct stat st;
    if (stat(target, &st) != 0) {
        perror("stat() error");
        return 1;
    }

    if (st.st_mode & S_IFDIR)
        scan_directory_recursive(target, warnings, &warning_count); 
    else if (st.st_mode & S_IFREG)
        scan_file(target, warnings, &warning_count);
    else {
        printf("[ERROR] Unknown file type: %s\n", target);
        return 1;
    }

    if (summary_mode) {
        printf("\nTotal warnings: %d\n", warning_count);
    }

    if (output_json)
        save_as_json(warnings, warning_count);
    if (output_csv)
        save_as_csv(warnings, warning_count);

    return 0;
}
