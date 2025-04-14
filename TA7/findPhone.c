#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

int main(int argc, char* argv[]){
	// safety check
	if(argc < 2 || argc > 4){
		fprintf(stderr,"ERROR(main): <Name> or <Mid Name> or <Full Name>");
		exit(1);
	}

	//creating a pipe for duo communication
	// pipefd[0] - read pipefd[1] - write
	int pipefd_1[2]; // grep to sed
	int pipefd_2[2]; // sed to sed
	int pipefd_3[2]; // sed to awk

	if( pipe(pipefd_1) == -1 || pipe(pipefd_2) == -1 || pipe(pipefd_3) == -1){
		perror("ERROR(main): Tried to create a pipe");
		exit(1);
	}

	// child 2 will generate the cat exec and redirect the pipfd[0] to STDIN and file fd to the STDOUT
	pid_t ch1_pid = fork();

	if(ch1_pid == -1){
		perror("ERROR(main): Failed to create a child");
		exit(1);
	}


	// great success
	if(ch1_pid == 0){
		close(pipefd_1[0]);
	// generating one line string
	int j =0, j_total =0,indx_runner=0;
	for (size_t i = 1; i < argc; i++)
	{
		j =0;
		while(argv[i][j] != '\0'){
			j++;
		}
		j_total += j;
	}
	char total_string[j_total+argc-1];
	for (size_t i = 1; i < argc; i++) {
		j = 0;
		while (argv[i][j] != '\0') {
			total_string[indx_runner++] = argv[i][j++];
		}
		if (i < argc - 1) {
			total_string[indx_runner++] = ' ';
		}
	}
	total_string[indx_runner] = '\0';

	// generate the grep executeable
	char *n_argv[4];
	n_argv[0] = "grep";
	for (size_t i = 0; i < argc; i++)
	{
		n_argv[i+1] = argv[i+1];
	}
	n_argv[1] = total_string;
	n_argv[2] = "phonebook.txt";
	n_argv[3] = (char*)NULL;

	// the grep exec outputs into the STDOUT so we will dup2 to pipefd_1
	dup2(pipefd_1[1],STDOUT_FILENO);
	// close the reading like in child1 fork
	close(pipefd_1[1]);
	close(pipefd_2[0]);
	close(pipefd_2[1]);
	close(pipefd_3[0]);
	close(pipefd_3[1]);
	if(execvp("grep",n_argv) == -1){
		perror("ERROR(child1): couldn't construct execvp on grep");
		exit(1);
	}
	}
	
	pid_t ch2_pid = fork();
	if(ch2_pid == -1){
		perror("ERROR(main): Failed to create a child2");
		exit(1);
	}
	if(ch2_pid == 0){
		dup2(pipefd_1[0],STDIN_FILENO);
		dup2(pipefd_2[1],STDOUT_FILENO);
		close(pipefd_2[1]);
		close(pipefd_1[1]);
		close(pipefd_2[0]);
		close(pipefd_3[0]);
		close(pipefd_3[1]);
		if(execlp("sed", "sed", "s/ /#/g", NULL) == -1){
			perror("ERROR(child2): couldn't construct execlp on sed 1st");
			exit(1);
		}
	}


	pid_t ch3_pid = fork();
	if(ch3_pid == -1){
		perror("ERROR(main): Failed to create a child3");
		exit(1);
	}
	if(ch3_pid == 0){
		dup2(pipefd_2[0],STDIN_FILENO);
		dup2(pipefd_3[1],STDOUT_FILENO);
		close(pipefd_3[1]);
		close(pipefd_2[1]);
		close(pipefd_3[0]);
		close(pipefd_1[0]);
		close(pipefd_1[1]);
		if(execlp("sed", "sed", "s/,/ /", NULL) == -1){
			perror("ERROR(child3): couldn't construct execlp on sed 2nd");
			exit(1);
		}
	}

	pid_t ch4_pid = fork();
	if(ch4_pid == -1){
		perror("ERROR(main): Failed to create a child3");
		exit(1);
	}
	if(ch4_pid == 0){
		dup2(pipefd_3[0],STDIN_FILENO);
		close(pipefd_1[0]);
		close(pipefd_1[1]);
		close(pipefd_2[0]);
		close(pipefd_2[1]);
		close(pipefd_3[0]);
		close(pipefd_3[1]);
		if(execlp("awk", "awk", "{print$2}", NULL) == -1){
			perror("ERROR(child4): couldn't construct execlp on awk");
			exit(1);
		}
	}

	close(pipefd_1[0]);
	close(pipefd_1[1]);
	close(pipefd_2[0]);
	close(pipefd_2[1]);
	close(pipefd_3[0]);
	close(pipefd_3[1]);

	wait(NULL);
	waitpid(ch1_pid, NULL, 0);
	waitpid(ch2_pid, NULL, 0);
	waitpid(ch3_pid, NULL, 0);
	waitpid(ch4_pid, NULL, 0);

	return 0;
}