#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

unsigned int result = 0; // global so the result on default is 0
int bit_index = 0; // same here

void handler(int signum){
	if(signum == SIGUSR1){
		result |= (0 << bit_index++);
	}
	else if(signum == SIGUSR2){
		result |= (1 << bit_index++);
	}

	if(bit_index == 8){
		printf("Recieved: %d",result);
		fflush(stdout);
		exit(0);
	}
}

int main(){
	int pid_num = getpid(),message;
	//creating sigaction struct for hadnling the custome signals
	struct sigaction act;
	act.sa_handler = &handler;
	// resetting default val for sigaction
	act.sa_flags=0;
	sigemptyset(&act.sa_mask);

	//redefining sigusr1\2 func
	sigaction(SIGUSR1,&act,NULL);
	sigaction(SIGUSR2,&act,NULL);

	//print self proccess ID
	printf("My PID is %d\n",pid_num);	
	while(1){
		pause();
	}
	return 0;
}