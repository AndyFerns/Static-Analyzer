#include "patterns.h"

const char* insecure_patterns[][2] = {
    {"gets(", "Use of 'gets' is insecure, use 'fgets' instead."},
    {"strcpy(", "Use of 'strcpy' may cause buffer overflow. Use 'strncpy'."},
    {"strcat(", "Use of 'strcat' may cause buffer overflow. Use 'strncat'."},
    {"sprintf(", "Use of 'sprintf' may cause buffer overflow. Use 'snprintf'."},
    {"system(", "Use of 'system' may lead to command injection."}
};

const int pattern_count = sizeof(insecure_patterns) / sizeof(insecure_patterns[0]);
