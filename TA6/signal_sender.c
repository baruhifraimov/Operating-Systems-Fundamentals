#include <stdio.h>
#include <unistd.h>
#include <signal.h>

// Here we will use SIGUSR1

int main(){
	// Send the specified pid the custome signal
	int rcv_pid,message;
	printf("Enter receiver PID:");
	scanf("%d",&rcv_pid);
	// Send the specified pid the custome signal
	printf("Enter message:");
	scanf("%d",&message);;
	for (int i = 0; i < 8; i++)
	{
		usleep(100000);
		if(((message>>i)&1) == 0){
			kill(rcv_pid,SIGUSR1);
		}
		else{
			kill(rcv_pid,SIGUSR2);
		
		}
	}
	return 0;
}