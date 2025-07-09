#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>

#define MAX_LINE_LENGTH 1024
#define MAX_WARNINGS 100

//enter known insecure patterns here
const char* insecure_patterns[][2] = {
    {"gets(", "Use of 'gets' is insecure, use 'fgets' instead. "},
    {"strcpy(", "Use of 'strcpy' may cause buffer overflow. Use 'strncpy'."},
    {"strcat(", "Use of 'strcat' may cause buffer overflow. Use 'strncat'."},
    {"sprintf(", "Use of 'sprintf' may cause buffer overflow. Use 'snprintf'."},
    {"system(", "Use of 'system' may lead to command injection."}
};

const int pattern_count = sizeof(insecure_patterns)/sizeof(insecure_patterns[0]);

void scan_file(const char* filepath) {
    FILE* file = fopen(filepath, "r");
    if (!file) {
        printf("[ERROR] Could not open file: %s\n", filepath);
        return;
    }

    printf("[INFO] %s Opened\n", filepath);
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

void scan_directory(const char* path) {
    DIR* dir;
    struct dirent* entry;

    if ((dir = opendir(path)) == NULL) {
        perror("opendir() error");
        return;
    }

    while ((entry = readdir(dir)) != NULL) {
        const char* filename = entry->d_name;

        // Skip "." and ".."
        if (strcmp(filename, ".") == 0 || strcmp(filename, "..") == 0)
            continue;

        const char* ext = strrchr(filename, '.');
        if (ext && strcmp(ext, ".c") == 0) {
            char fullpath[512];
            snprintf(fullpath, sizeof(fullpath), "%s\\%s", path, filename);  // Note: Windows uses backslash
            scan_file(fullpath);
        }
    }

    closedir(dir);
}

int main(int argc, char* argv[]) {
    printf("🔐 Simple Static Security Scanner for .c files\n");

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
        scan_directory(argv[1]);  // Directory
    } else if (path_stat.st_mode & S_IFREG) {
        scan_file(argv[1]);       // Single file
    } else {
        printf("Unknown file type: %s\n", argv[1]);
    }

    return 0;
}

