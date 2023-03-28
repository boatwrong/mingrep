#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include "helper.h"

int main(int argc, char *argv[]) 
{
    if (3 > argc) 
    {
        argsUsage();
        return 1;
    }

    //TODO consider putting this parsing into a function?
    bool doRecurse = false;
    bool doFileSearch = false;
    int c;

    if (4 >= argc)
    {
        while ((c = getopt(argc, argv, "rf")) != -1)
        {
            // getopt handles multiple flags
            switch(c)
            {
                case 'r':
                    fprintf(stdout, "doing recursive\n");
                    doRecurse = true;
                    break;
                case 'f':
                    fprintf(stdout, "dooing file name search\n");
                    doFileSearch = true;
                    break;
                default:
                    optionUsage();
                    break;
            }
        } 
    }

    //	https://linux.die.net/man/3/stat
    //	TODO: Look back at this for reference about filetype

    if (doRecurse)
    {
        recurse(argv[argc-1], argv[argc-2], doFileSearch);
    }

    else
    {
        fileSearch(argv[argc-1], argv[argc-2], doFileSearch);
    }
}
