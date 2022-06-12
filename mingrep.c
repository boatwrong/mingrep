#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>

#define MAX_BUFF 100

void usage();

int main(int argc, char *argv[]) {
	if(argc < 3) {
//		usage();
	}

	int len;
	char* expr = (char*)NULL;
	char* ogDir = malloc(MAX_BUFF * sizeof(char*));
	char* dir = malloc(MAX_BUFF * sizeof(char*));
	char* searchPath = malloc(MAX_BUFF * sizeof(char*));
	char* path = malloc(MAX_BUFF * sizeof(char*));
	char* parent = "../";
	getcwd(ogDir,MAX_BUFF);

	printf("%s\n", ogDir);
	printf("moving to parent directory...\n");
	path = strcat(parent, ogDir);
	chdir(path);
	getcwd(dir, MAX_BUFF);
	printf("Current directory: %s\n", dir);
	switch(argc) {
		case(3):
			printf("base case\n");
			// base case of searching for expression in file
			break;
		case(4):
			// one flag
			printf("base case with a flag\n");
			break;
		default:
			// more than one flag, extra conditions
			break;
	}
	return 0;

}

void search() {

}






void usage() {
	fprintf(stderr, "mingrep usage...\n");
}
