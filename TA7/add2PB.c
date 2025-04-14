#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

int main(int argc, char* argv[]){
	// safety check 
	if(argc < 3 || argc > 4){
		fprintf(stderr,"ERROR(main): <Name> optional:<Mid Name> optional:<Last Name>,<Phone Number>");
		exit(1);
	}

	//creating a pipe for duo communication
	// pipefd[0] - read pipefd[1] - write
	int pipefd[2];
	if( pipe(pipefd) == -1){
		perror("ERROR(main): Trying to create a pipe");
		exit(1);
	}
	// generating a child 1
	pid_t ch1_pid = fork();

	if(ch1_pid == -1){
		perror("ERROR(main): Failed to create a child");
		exit(1);
	}
	// we will determine that the child1 will read and the child2 will write
	// child 1 will generate the echo and redirect the STDOUT to the pipefd[1] fd
	if(ch1_pid == 0){
		close(pipefd[0]); // we close the reading point of the pipe for the child to prevent leaks
		char *n_argv[argc+1];
		n_argv[0] = "echo";
		for (size_t i = 0; i < argc; i++)
		{
			n_argv[i+1] = argv[i+1];
		}
		n_argv[argc+1] = (char*)NULL;
		// redefining stdout with pipefd[1] (pipe)
		dup2(pipefd[1],STDOUT_FILENO);
		if(execvp("echo",n_argv) == -1){
			perror("ERROR(child1): couldn't construct execvp");
			exit(1);
		}
		close(pipefd[1]);
	}
	// child 2 will generate the cat exec and redirect the pipfd[0] to STDIN and file fd to the STDOUT
	pid_t ch2_pid = fork();
		if(ch2_pid == -1){
			perror("ERROR(main): Failed to create a child");
			exit(1);
		}
		if(ch2_pid == 0){
			close(pipefd[1]); // we close the writing point of the pipe for the child to prevent leaks
			// redefining STDIN with pipefd[0] (pipe)
			dup2(pipefd[0],STDIN_FILENO);
			int file = open("phonebook.txt", O_WRONLY | O_APPEND | O_CREAT, 0644 );
			// file safety
			if(file == -1){
				perror("ERROR(child2): couldn't create/write into file");
				exit(1);
			}
			// changing the STDOUT to file for the cat to print into the file
			dup2(file,STDOUT_FILENO);
			if(execlp("cat","cat",NULL) == -1){
				perror("ERROR(child1): couldn't construct execvp");
				exit(1);
			}
			close(file);
			close(pipefd[0]);
		}

	close(pipefd[1]);  // we close the reading point of the pipe to prevent leaks (for the parent)
	close(pipefd[0]);
	
	waitpid(ch1_pid, NULL, 0);
	waitpid(ch2_pid, NULL, 0);

	return 0;
}