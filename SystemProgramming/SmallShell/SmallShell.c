#include<sys/types.h>
#include<sys/wait.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
#include<stdio.h>

#define PROMPT "$>"
#define	LINE_LENGTH	80

int main(int argc, char* argv[])
{
	char buffer[LINE_LENGTH];
	pid_t pid;
	int c, count = 0;
	int background = 0;
	int status;	
	while(1)
	{
		printf(PROMPT);
		count = 0;
		while(1)
		{
			/*
			 *한 글자씩 받아서 buffer에 저장
			 */
			if((c = getchar()) == EOF)
				exit(1); //normal exit
			if(count < LINE_LENGTH)
				buffer[count++] = c;
			if(c == '\n' && count < LINE_LENGTH)
			{
				buffer[count - 1] = 0;
				break;
			}
			if(count >= LINE_LENGTH)
			{
				printf("input too long\n");
				count = 0;
				printf(PROMPT);
				continue;//실행파일 다시 입력
			}
		}//end of while
		
		//글자가 입력되지 않거나 &만 입력된 경우
		if(strlen(buffer) == 0 || (strlen(buffer) == 1 && \
					buffer[strlen(buffer)-1] == '&'))
			continue;//to for loop
		
		if(buffer[strlen(buffer)-1] == '&')
		{
			//끝 글자가 &인 경우
			background = 1;//background로 설정
			buffer[strlen(buffer)-1] = '\0';
		}
		else
			background = 0;//foreground

		if((pid =fork()) < 0)
		{
			perror("fork failed\n");
			exit(1);
		}
		else if( pid == 0)//child process
		{
			//실행 파일의 이름을 받아 실행
			//execlp(파일 이름, 전달인자, ... ,NULL)
			execlp(buffer, buffer, (char *)0);
			perror("execlp failed\n");
			exit(1);
		}
		if(background == 1)
			continue;
		else					//foreground
			/*
			 * wait(&status)의 반환값은 자식프로세서가
			 * 종료되면서 반환되는 값이다. 
			 * status는 자식프로세서가 종료될 때의 
			 * 상태 정보가 저장된다.
			 */
			while(wait(&status)!=pid);//wait for the exit of foreground	
	//	while(wait(&pid) == pid)
	//		printf("WAIT CHILD PROCESS\n");//wait for the exit of foreground
	//	wait(&status);
	}//end of while
}