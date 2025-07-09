#include <stdio.h>
#include <string.h>

int main() {
    char input[50];
    gets(input); // bad
    strcpy(input, "Hello"); // bad
    strcat(input, "World"); // bad
    sprintf(input, "%d", 123); // bad
    system("ls"); // very bad
    return 0;
}
