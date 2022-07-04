#include<unistd.h>
#include<stdio.h>
#include<sys/types.h>
#include<sys/param.h>
#include<dirent.h>
#include<string.h>

#define MAX_BUFF 200

void indent(int level);
void tree(char* path, int level);
const char* slashy = "/";
int main(int argc, char *argv[])
{
	char path[MAX_BUFF];
	getcwd(path, MAX_BUFF);
	tree(path, 0);
    return 0;
}

void tree(char* path, int level)
{

	char nextPath[MAX_BUFF];
	DIR* dir;
	DIR* nextDir;
	struct dirent *de;

	if((dir=opendir(path)) != NULL)
	{

		while((de = readdir(dir)) != NULL)
		{
			indent(level);
			printf("%s\n", de->d_name);
			strcpy(nextPath, path);
			strcat(nextPath, slashy);
			strcat(nextPath, de->d_name);

			if((nextDir=opendir(nextPath)) != NULL)
			{

				if(0 != strcmp(de->d_name,".") && (0 != strcmp(de->d_name,"..")) && 0 != strcmp(de->d_name,".git"))
				{
					tree(nextPath, level + 2);
				}
			}
		}
	}
 }

void indent(int level)
{
	for(int i=0; i<level*2; i++)
	{
		printf("-");
	}
}
