#include<stdio.h>
#include<dirent.h>
#include<sys/stat.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>

#define MAX_BUFF 100

int isFile(char* path);
void globSearch();
void fileSearch(char* path, char* expr);
int globCompare(char* str);
void usage();
void recurse(char* path, char* expr);

int main(int argc, char *argv[]) 
{
	if(argc < 3) 
	{
		usage();
		return 1;
	}
	char* expr = malloc(MAX_BUFF * sizeof(char*));
	char* path = malloc(MAX_BUFF * sizeof(char*));
	char* flags = malloc(MAX_BUFF * sizeof(char*));
//	https://linux.die.net/man/3/stat
//	TODO: Look back at this for reference about filetype
	switch(argc) 
	{
		case(3):
			strcpy(expr,argv[1]);
			strcpy(path,argv[2]);
			if(globCompare(path) && !isFile(path))
			{
				char* newPath = malloc((strlen(path)) * sizeof(char));
				memcpy(newPath, path, strlen(path)-1);
				globSearch(newPath, expr);
			}
			else { fileSearch(path, expr); }
			break;
		// flags have been used 
		case(4):
			if(argc < 4) { usage(); return 1; }
			strcpy(flags,argv[1]);
			strcpy(expr,argv[2]);
			strcpy(path,argv[3]);
			if(strstr(flags, "-r") != NULL) { recurse(path, expr); }
			break;
		default:
			break;
	}
	expr = (char*)NULL;
	free(expr);
	path = (char*)NULL;
	free(path);
	return 0;
}

// Error message for improper use
void usage() {
	fprintf(stderr, "mingrep usage...\n");
}

// Check if searching throughout directory
int globCompare(char* str)
{
	for(int i=strlen(str); i > 0; i--)
	{
		if(str[i] == '*') { return 1; }
	}
	return 0;
}

// Search through individual file for expression
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

// Search through whole directory
void globSearch(char* path, char* expr)
{
	DIR *dir = opendir(path);
	struct dirent *de;
	// TODO: do i really need to do this or just check if somethign is not
	//			a file and then skip over it???
	de = readdir(dir); 
	while(de != NULL)
	{
		de = readdir(dir); 
		if(isFile(de->d_name)) { fileSearch(de->d_name, expr); }
//		EOF
	}
}

// check if path references a file or directory
int isFile(char* path)
{
	struct stat statPath;
	stat(path, &statPath);
	return S_ISREG(statPath.st_mode);
}

// recursively search
void recurse(char* path, char* expr)
{
	/*
	char* currDir = ".";
	char* parentDir = "..";
	printf("in recursion method\n");
	// base case: [path] is a file
	if(isFile(path)) { 
		fileSearch(path,expr);
		return; 
	}
	// recursion case: [path] is a directory
	else
	{
		DIR *dir = opendir(path);
		struct dirent *de;
	*/
		struct stat buf;
		stat(path, &buf);
		if((buf.st_mode & S_IFMT) == S_IFREG)
		{
			printf("is file\n");
		}
		else
		{
			printf("is directory\n");
		}


		// TODO: do i really need to do this or just check if somethign is not
		//			a file and then skip over it???
		/*
		while((de = readdir(dir)) != NULL)
		{
			if(!strcmp(de->d_name, currDir) || !strcmp(de->d_name, parentDir))
			{
				continue;
			}
			printf("sending path: [%s] to recurse function\n", de->d_name);
			recurse(de->d_name, expr);
		}
	}
		*/
}
