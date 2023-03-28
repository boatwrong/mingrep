#include <stdio.h>
#define slashy "/"
#define MAX_BUFF 100
#define ERROR_EXIT -1
#define GOOD_EXIT 0

int lastIndexOf(char* str, char* expr, int len);
char* getFileName(char* str);
void argsUsage();
void optionUsage();
int globCompare(char* str);
void search(FILE *fp, char* path, char* expr);
void fileSearch(char* path, char* expr, bool doFileSearch);
void globSearch(char* path, char* expr, bool doFileSearch);
int isFile(char* path);
void recurse(char* path, char* expr, bool doFileSearch);
int checkSTDIN(char* expr);
