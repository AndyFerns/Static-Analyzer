#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include "scanner.h"
#include "patterns.h"

#define MAX_LINE_LENGTH 1024

// file scanning logic
void scan_file(const char* filepath) {
    FILE* file = fopen(filepath, "r");
    if (!file) {
        printf("[ERROR] Could not open file: %s\n", filepath);
        return;
    }

    printf("[INFO] Opened: %s\n", filepath);
    char line[MAX_LINE_LENGTH];
    int line_number = 0;

    while (fgets(line, sizeof(line), file)) {
        line_number++;
        for (int i = 0; i < pattern_count; i++) {
            if (strstr(line, insecure_patterns[i][0])) {
                printf("[WARNING] Security Issues Detected!\n");
                printf("[Line %d] %s --> %s\n", line_number, insecure_patterns[i][0], insecure_patterns[i][1]);
            }
        }
    }
    fclose(file);
}

// directory scanning logic
void scan_directory(const char* path) {
    DIR* dir;
    struct dirent* entry;

    if ((dir = opendir(path)) == NULL) {
        perror("opendir() error");
        return;
    }

    while ((entry = readdir(dir)) != NULL) {
        const char* filename = entry->d_name;

        if (strcmp(filename, ".") == 0 || strcmp(filename, "..") == 0)
            continue;

        const char* ext = strrchr(filename, '.');
        if (ext && strcmp(ext, ".c") == 0) {
            char fullpath[512];
            snprintf(fullpath, sizeof(fullpath), "%s\\%s", path, filename);
            scan_file(fullpath);
        }
    }

    closedir(dir);
}
