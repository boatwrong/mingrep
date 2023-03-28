#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{
    if (!(isatty(fileno(stdin))))
    {
        FILE *piped;
        int i = 0;
        char pipe[65536];
        while(-1 != (pipe[i++] = getchar()));
        pipe[i-1] = '\0';
        pipe[i-2] = '\0';
        fprintf(piped, "%s", pipe);
        return 0;
    }
    return 1;
}
