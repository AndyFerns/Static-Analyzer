#ifndef SCANNER_H
#define SCANNER_H

//for warning flag
typedef struct Warning {
    char file[512];
    int line;
    char pattern[32];
    char message[256];
} Warning;

void scan_file(const char* filepath);
void scan_directory_recursive(const char* path);

#endif
