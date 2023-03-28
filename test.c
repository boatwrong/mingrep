#include <string.h>
#include <stdlib.h>
#include <stdio.h>

// test file for debugging specific functionality 
int main() {
    FILE *piped; 
    piped = fopen("/dev/stdin", "r");
    char* line = malloc(BUFSIZ * sizeof(char*));
    if (NULL == piped) 
    {
        perror("ERROR, file not found"); 
    }
    fgets(line, BUFSIZ, piped);
    int index=0;
    while (!feof(piped))
    {
        index++;
        fprintf(stdout, "%s\n", line);
        fgets(line, BUFSIZ, piped);
    }
    line = (char*)NULL;
    free(line);
    fclose(piped);
    return 0;
}

