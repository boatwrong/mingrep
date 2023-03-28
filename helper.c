#include <stdio.h>
#include <sys/stat.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <dirent.h>
#include <unistd.h>

#include "helper.h"

int lastIndexOf(char* str, char* expr, int len)
{
    for (int i = len-1; i >=0; i--)
    {
        if (expr[0] == str[i])
        {
            return i;
        }
    }
    return -1;
}

char* getFileName(char* str)
{
    size_t len = strlen(str);
    int lastSlash = lastIndexOf(str, slashy, len);
    int fileNameLength = len - lastSlash -1;
    char* fileName = malloc(fileNameLength);
    for (int i = 0; i < fileNameLength; i++)
    {
        fileName[i] = str[i + 7];
    }
    return NULL;
}

void argsUsage()
{
    fprintf(stderr,"Not enough arguments. Usage: \n\n");
    fprintf(stderr,"\t./mingrep [-r] string file(s)");
}

void optionUsage()
{
    fprintf(stderr,"If youre here, youve put in an illegal flag\n\n");
    fprintf(stderr,"Current flag options of this program are: r\n");
}

// Check if searching throughout directory
int globCompare(char* str)
{
    for(int i=strlen(str); i > 0; i--)
    {
        if (str[i] == '*') { return 1; }
    }
    return 0;
}

void search(FILE *fp, char* path, char* expr)
{
    char* line = malloc(MAX_BUFF * sizeof(char*));
    if (NULL == fp) 
    {
        perror("ERROR, file not found"); 
    }
    fgets(line, MAX_BUFF, fp);
    int index=0;
    while (!feof(fp))
    {
        index++;
        if (strstr(line, expr) != NULL) 
        {
            fprintf(stdout, "%s - line %d:  ", path, index);
            fprintf(stdout, "%s", line);
        }
        fgets(line, MAX_BUFF, fp);
    }
    line = (char*)NULL;
    free(line);
    fclose(fp);
}

// Search through individual file for expression
void fileSearch(char* path, char* expr, bool doFileSearch)
{
    if (true == doFileSearch)
    {
        char* fileName = getFileName(path);
        if (strstr(fileName, expr) != NULL) 
        {
            fprintf(stdout, "%s\n", fileName);
        }
    }

    FILE* fp = fopen(path, "r");
    search(fp, path, expr);
}

// Search through whole directory
void globSearch(char* path, char* expr, bool doFileSearch)
{
    DIR *dir = opendir(path);
    struct dirent *de;
    // TODO: do i really need to do this or just check if somethign is not
    //			a file and then skip over it???
    de = readdir(dir);
    while (de != NULL)
    {
        de = readdir(dir);
        if (isFile(de->d_name)) {
            fileSearch(de->d_name, expr, doFileSearch);
        }
    }
}

int isFile(char* path)
{
    struct stat statPath;
    stat(path, &statPath);
    return S_ISREG(statPath.st_mode);
}

void recurse(char* path, char* expr, bool doFileSearch)
{
    if (isFile(path)) 
    {
        fileSearch(path, expr, doFileSearch);
        return;
    }
    char nextPath[MAX_BUFF];
    DIR* dir;
    struct dirent *de;
    if ((dir=opendir(path)) != NULL)
    {
        while ((de = readdir(dir)) != NULL)
        {
            strcpy(nextPath, path);
            strcat(nextPath, slashy);
            strcat(nextPath, de->d_name);
            if (0 != strcmp(de->d_name,".") && (0 != strcmp(de->d_name,"..")) && 0 != strcmp(de->d_name,".git"))
            {
                recurse(nextPath, expr, doFileSearch);
            }
        }
    }
}

int checkSTDIN(char* expr)
{
    if (!(isatty(fileno(stdin))))
    {
        FILE *piped;
        piped = fopen("/dev/stdin", "r");
        search(piped, "stdin", expr);
        return -3;
    }
    return 1;
}
