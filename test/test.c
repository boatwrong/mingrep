#include<stdio.h>
#include<dirent.h>
#include<sys/stat.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>

#define MAX_BUFF 100

void recursed(char* path, char* expr);
int isFile(char* path);
void globSearch();
void fileSearch(char* path, char* expr);
int globCompare(char* str);
void usage();
void recurse(char* path, char* expr);

int main(int argc, char *argv[]) 
{
	recurse(argv[1], "23");
	return 0;
}

void fileSearch(char* path, char* expr) 
{
			FILE* fp = fopen(path, "r");
			char* line = malloc(MAX_BUFF * sizeof(char*));
			if(fp == NULL) { perror("ERROR, file not found"); }
			fgets(line, MAX_BUFF, fp);
			int index=0;
			while(!feof(fp))
			{
				index++;
				if(strstr(line, expr) != NULL) 
				{
					printf("%s - line %d:  ", path, index);
					printf("%s\n", line);
				}
				fgets(line, MAX_BUFF, fp);
			} 
			line = (char*)NULL;
			free(line);
			fclose(fp);
}

int isFile(char* path)
{
	struct stat statPath;
	stat(path, &statPath);
	return S_ISREG(statPath.st_mode);
}

void recurse(char* path, char* expr)
{
	printf("in recurse function looking at: \'%s\'\n", path);
	//TODO move this file check to first parsing of args and skip
	//		this function call altogether
	struct stat buf;
	stat(path, &buf);
	if((buf.st_mode & S_IFMT) == S_IFREG)
	{
		printf("searching file: %s\n", path);
		fileSearch(path,expr);
		return; 
	}
	DIR *dir = opendir(path);
	printf("Directory \'%s\' opened\n", path);
	struct dirent *de;
	while((de = readdir(dir)) != NULL)
	{
		printf("in while loop analyzing directory \'%s\'\n", de->d_name);
		if(0 == strcmp(de->d_name,".")) {continue;}
		if(0 == strcmp(de->d_name,"..")) {continue;}
		printf("calling recurse on: \'%s\'\n", de->d_name);
		recurse(de->d_name, expr);
	}
}



































