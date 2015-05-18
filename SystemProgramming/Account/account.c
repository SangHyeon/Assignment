#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<stdlib.h>

#define NUM_RECORDS 100

struct record {
	int id; //account num
	char name[20]; //account owner
	int balance; //balance
};

void rec_lock(int fd, int recno, int len, short type);
void display(struct record *current);

int main(int argc, char * argv[])
{
	struct record current;
	int record_no;
	int fd, pos, i, n;
	char yse;
	char operation;
	int amount = 0;
	
	if( (fd = open("Account_File", O_RDWR)) == -1)
		exit(1); //can not open file

	while(1) {
		printf("enter account number \n");
		scanf("%d%*c", &record_no);
		if(record_no <= 0 && record_no > 99)
			break;

		printf("enter operation name \n");
		scanf("%c%*c", &operation);

		switch(operation) {
			case 'r' : //inqury
				rec_lock(fd, record_no, seizeof(current), F_RDLCK);
				pos = record_no * sizeof(struct record);
				lseek(fd, pos, SEEK_SET);
				n = read(fd, &current, sizeof(current));
				display(&current);
				rec_lock(fd, record_no, sizeof(current), F_UNLCK);
				break;
			case 'd' : //deposit
				rec_lock(fd, record_no, sizeof(current), F_WRLCK);

		}

	}


}
