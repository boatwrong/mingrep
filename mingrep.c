#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include "helper.h"

int main(int argc, char *argv[]) 
{
    if (2 == argc)
    {
        int res = checkSTDIN(argv[1]);
        if (-3 == res)
        {
            return 0;
        }
        argsUsage();
        return 1;
    }
    if (3 > argc) 
    {
        argsUsage();
        return 1;
    }

    bool doRecurse = false;
    bool doFileSearch = false;
    int c;

    if (4 >= argc)
    {
        while ((c = getopt(argc, argv, "rf")) != -1)
        {
            switch(c)
            {
                case 'r':
                    doRecurse = true;
                    break;
                case 'f':
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
        return 0;
    }
    else
    {
        fileSearch(argv[argc-1], argv[argc-2], doFileSearch);
        return 0;
    }
    return 1;
}
