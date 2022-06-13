#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>

#define MAX_BUFF 100

int globCompare(char* str);
void usage();

int main(int argc, char *argv[]) 
{
	if(argc < 3) 
	{
		// error message
		fprintf(stderr, "Usage: not enough args\n");
		return 1;
	}
	

	char* expr = malloc(MAX_BUFF * sizeof(char*));
	char* path = malloc(MAX_BUFF * sizeof(char*));

	switch(argc) 
	{
		case(3):
			strcpy(expr,argv[1]);
			strcpy(path,argv[2]);
			if(globCompare(path)) { printf("glob searching\n"); }

			// TODO:
			//		have not tested for absolute paths to other direcories
			FILE* fp = fopen(argv[2], "r");
			char* line = malloc(MAX_BUFF * sizeof(char*));
			if(fp == NULL)
			{
				perror("ERROR");
				return 1;
			}
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

void usage() {
	fprintf(stderr, "mingrep usage...\n");
}

int globCompare(char* str)
{
	for(int i=strlen(str); i > 0; i--)
	{
		if(str[i] == '*')
		{
			return 1;
		}
	}
	return 0;
}
