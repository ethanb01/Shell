#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <linux/limits.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "LineParser.h"

char* read_line(char*, int, FILE*);
void execute(cmdLine*);
void check_exit(char*);
void print_prompt();

int main(int argc, char const *argv[])
{
	while(1)
	{
		print_prompt();
		char input[2048];
		read_line(input , 2048, stdin);
		check_exit(input);
		cmdLine *cl;
		cl = parseCmdLines(input);
		execute(cl);


		freeCmdLines(cl);
	}
	return 0;
}

char* read_line(char *str, int n, FILE *stream){
	char *ans = fgets(str, n, stream);
	if (ans == NULL)
		return NULL;
	int newlineIndex = strcspn(str, "\n");
	str[newlineIndex] = 0;
	return str;}

void execute(cmdLine *pCmdLine){	
	int status = 0;
	pid_t pid = fork();
	if(pid<0){
		perror("FORK ERROR");
	}
	else if(pid==0)
	{
		printf("child pid: %d\n",(int)pid );
		char *cmd = pCmdLine->arguments[0];
		execvp(cmd,pCmdLine->arguments);
	}
	else{
		wait(&status);
		printf("exit code: %d\n", WIFEXITED(status));
	}


}

void check_exit(char *input){
	if(strcmp(input, "_exit")==0)
		exit(0);
}

void print_prompt(){
	char buf[PATH_MAX];
	getcwd(buf, PATH_MAX);
	printf("%s$ >>> ",buf);
}

