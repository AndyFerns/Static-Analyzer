#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include "scanner.h"
#include "patterns.h"

// ANSI Colors
#define RED     "\033[1;31m"
#define GREEN   "\033[1;32m"
#define YELLOW  "\033[1;33m"
#define RESET   "\033[0m"

#define MAX_LINE_LENGTH 1024

// file scanning logic
void scan_file(const char* filepath) {
    FILE* file = fopen(filepath, "r");
    if (!file) {
        printf(RED "[ERROR]" RESET " Could not open file: %s\n", filepath);
        return;
    }

    printf(YELLOW "[INFO]" RESET " Scanning: %s\n", filepath);
    char line[MAX_LINE_LENGTH];
    int line_number = 0;

    while (fgets(line, sizeof(line), file)) {
        line_number++;
        for (int i = 0; i < pattern_count; i++) {
            if (strstr(line, insecure_patterns[i][0])) {
                printf(RED "  [WARNING]" RESET " Line %d: %s --> %s\n",
                       line_number,
                       insecure_patterns[i][0],
                       insecure_patterns[i][1]);
            }
        }
    }
    fclose(file);
}

// directory scanning logic
void scan_directory_recursive(const char* path) {
    DIR* dir = opendir(path);
    if (!dir) {
        perror("opendir() error");
        return;
    }

    struct dirent* entry;
    while ((entry = readdir(dir)) != NULL) {
        const char* name = entry->d_name;

        // Skip . and ..
        if (strcmp(name, ".") == 0 || strcmp(name, "..") == 0)
            continue;

        char fullpath[512];
        snprintf(fullpath, sizeof(fullpath), "%s\\%s", path, name);

        struct stat st;
        if (stat(fullpath, &st) == 0) {
            if (S_ISDIR(st.st_mode)) {
                // Recurse into subdirectory
                scan_directory_recursive(fullpath);
            } else if (S_ISREG(st.st_mode)) {
                const char* ext = strrchr(name, '.');
                if (ext && strcmp(ext, ".c") == 0) {
                    scan_file(fullpath);
                }
            }
        }
    }

    closedir(dir);
}
