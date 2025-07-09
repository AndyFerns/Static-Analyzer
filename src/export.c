#include <stdlib.h>
#include <stdio.h>
#include "scanner.h"
#include "export.h"
#include <sys/stat.h>

#define GREEN "\033[1;32m"
#define RESET "\033[0m"

void save_as_json(Warning* warnings, int count) {
    mkdir("outputs");
    FILE* f = fopen("outputs/summary.json", "w");
    if (!f) {
        printf("[ERROR] Could not write JSON\n");
        return;
    }

    fprintf(f, "[\n");
    for (int i = 0; i < count; i++) {
        fprintf(f,
            "  {\n"
            "    \"file\": \"%s\",\n"
            "    \"line\": %d,\n"
            "    \"pattern\": \"%s\",\n"
            "    \"message\": \"%s\"\n"
            "  }%s\n",
            warnings[i].file, warnings[i].line, warnings[i].pattern, warnings[i].message,
            (i < count - 1 ? "," : "")
        );
    }
    fprintf(f, "]\n");
    fclose(f);
    printf(GREEN "[INFO]" RESET " Saved output to outputs/summary.json\n");
}

void save_as_csv(Warning* warnings, int count) {
    mkdir("outputs");
    FILE* f = fopen("outputs/summary.csv", "w");
    if (!f) {
        printf("[ERROR] Could not write CSV\n");
        return;
    }

    fprintf(f, "file,line,pattern,message\n");
    for (int i = 0; i < count; i++) {
        fprintf(f, "\"%s\",%d,\"%s\",\"%s\"\n",
                warnings[i].file,
                warnings[i].line,
                warnings[i].pattern,
                warnings[i].message);
    }
    fclose(f);
    printf(GREEN "[INFO]" RESET " Saved output to outputs/summary.csv\n");
}