#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void vulnerable_function() {
    char input[10];
    gets(input);  // bad
    strcpy(input, "This is too long for buffer");  // bad
    strcat(input, "Danger!");  // bad
    sprintf(input, "%s", "formatting");  // bad
    system("dir");  // bad

    char buffer[5];
    gets(buffer);  // bad
    strcpy(buffer, "1234567890");  // bad
    strcat(buffer, "overflow");  // bad
    sprintf(buffer, "%d", 99999);  // bad
    system("calc.exe");  // bad
}