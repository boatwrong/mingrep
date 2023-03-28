#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include "helper.h"

int main(int argc, char *argv[]) 
{
    if (3 > argc) 
    {
        optionUsage();
        return 1;
    }

    //TODO consider putting this parsing into a function?
    bool doRecurse = false;
    int c;

    if (4 >= argc)
    {
        while ((c = getopt(argc, argv, "r")) != -1)
        {
            switch(c)
            {
                case 'r':
                    doRecurse = true;
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
        recurse(argv[argc-1], argv[argc-2]);
    }

    else
    {
        fileSearch(argv[argc-1], argv[argc-2]);
    }
}
