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

//record LOCK & UNLOCK
void rec_lock(int fd, int recno, int len, short type);

//display account information
void display(struct record *current);

int main(int argc, char * argv[])
{
	struct record current;
	int record_no;//account number (0~99)
	int fd, pos, n;
	char operation;
	int amount;

	if( (fd = open("Account_File", O_RDWR)) == -1)
		exit(1); //can not open file

	while(1) {
		printf("enter account number \n");
		scanf("%d%*c", &record_no);
		if(record_no <= 0 && record_no >= 99) {
			printf("Retry \n");
			break;
		}
		printf("enter operation name \n");
		scanf("%c%*c", &operation);

		switch(operation) {
			case 'r' : //inquiry
				rec_lock(fd, record_no, sizeof(struct record), F_RDLCK);//reader's lock
				pos = record_no * sizeof(struct record);//position of current account info
				lseek(fd, pos, SEEK_SET);//set position
				n = read(fd, &current, sizeof(struct record));//read current account struct
				display(&current);//display
				rec_lock(fd, record_no, sizeof(struct record), F_UNLCK);//unlock
				break;
			case 'd' : //deposit
				rec_lock(fd, record_no, sizeof(struct record), F_WRLCK);//writer's lock
				pos = record_no * sizeof(struct record);
				lseek(fd, pos, SEEK_SET);
				n = read(fd, &current, sizeof(struct record));
				display(&current);
				printf("enter amount\n");
				scanf("%d%*c", &amount);
				current.balance += amount;//modify balance
				lseek(fd, pos, SEEK_SET);
				write(fd, &current, sizeof(struct record));//write balance amount
				display(&current);
				rec_lock(fd, record_no, sizeof(struct record), F_UNLCK);//unlock
				break;
			case 'w' : //withdraw
				rec_lock(fd, record_no, sizeof(struct record), F_WRLCK);//writer's lock
				pos = record_no * sizeof(struct record);
				lseek(fd, pos, SEEK_SET);
				n = read(fd, &current, sizeof(struct record));
				display(&current);
				printf("enter amount\n");
				scanf("%d%*c", &amount);
				current.balance -= amount;//modify balance
				lseek(fd, pos, SEEK_SET);
				write(fd, &current, sizeof(struct record));
				display(&current);
				rec_lock(fd, record_no, sizeof(struct record), F_UNLCK);//unlock
				break;
			case 't' : //transfer
				rec_lock(fd, record_no, sizeof(struct record), F_WRLCK);
				//current account
				pos = record_no * sizeof(struct record);
				lseek(fd, pos, SEEK_SET);
				n = read(fd, &current, sizeof(struct record));
				display(&current);
				printf("<transfer> enter account number \n");
				scanf("%d%*c", &record_no);
				if(record_no <= 0 && record_no >= 99) {
					printf("Retry \n");
					break;
				}
				printf("<transfer> enter amount\n");
				scanf("%d%*c", &amount);
				current.balance -= amount;//transfer balance
				lseek(fd, pos, SEEK_SET);
				write(fd, &current, sizeof(struct record));
				display(&current);
				//transfer account
				pos = record_no * sizeof(struct record);
				lseek(fd, pos, SEEK_SET);
				n = read(fd, &current, sizeof(struct record));
				current.balance += amount;//transfer
				lseek(fd, pos, SEEK_SET);
				write(fd, &current, sizeof(struct record));//complete transfer

				rec_lock(fd, record_no, sizeof(struct record), F_UNLCK);//unlock
				break;

			case 'q' : //quit
				printf("EXIT PROGRAM\n ");
				return 0;
			default : //error
				printf("input error\n");
				continue;
		};
	}
	close(fd);//close file
}

void rec_lock(int fd, int recno, int len, short type)
{
	struct flock fl;//FILE LOCK Struct
	switch (type) {
		case F_RDLCK ://reader's lock
		case F_WRLCK ://writer's lock
		case F_UNLCK ://unlock
			fl.l_type = type;//type = F_RDLCK, F_WRLCK, F_UNLCK
			fl.l_whence = SEEK_SET;//front of file
			fl.l_start = recno * len;//lock start point
			fl.l_len = len;//lock region length
			fcntl(fd, F_SETLKW, &fl);//file, command, lock struct
			return;
		default:
			return;
	};
}

void display(struct record *current)
{
	printf("Account number  :  %d \n", current->id);
	printf("Account owner   :  %s \n", current->name);
	printf("Account balance :  %d \n", current->balance);

	printf("\n");
}
