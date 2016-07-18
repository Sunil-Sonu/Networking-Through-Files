#define NEW(n,t) (n*)calloc(sizeof(n),t)
#include<stdio.h>
#include<malloc.h>


int readFromFile(FILE *, int);
int writeToFile(FILE *);
int main()
{
	char ch;
	int lastRead = 0,writeOperation=0;
	int check = 1, readop = 1;
	FILE *rw;
	rw = fopen("D:\\Client-Server\\clientserver.bin", "a+b");
	while (check)
	{
		if (readop){
			int temp = readFromFile(rw, lastRead,writeOperation);
			if (temp != lastRead)
			{
				lastRead = temp;
				readop = 0;
			}
		}
		else{
			writeOperation = writeToFile(rw,writeOperation);
			readop = 1;
		}
	}
	return 0;
}


int readFromFile(FILE *read, int lastRead,int writeOperation)
{
	char ch;
	fseek(read, writeOperation, SEEK_SET);
	ch = fgetc(read);
	if (ch == EOF)
		return lastRead;
	else{

		printf("Server says : ");
		while (ch != EOF){
			printf("%c", ch);
			ch = fgetc(read);
			lastRead++;
		}
		printf("\n");
		return lastRead;
	}

}
int  writeToFile(FILE *write)
{
	char *Msg;
	int len;
	Msg = NEW(char, 1024);
	fseek(write, 0, SEEK_END);
	fflush(stdin);
	printf("You :");
	gets(Msg);
	printf("\n");
	len = strlen(Msg);
	fwrite(Msg, sizeof(char), len, write);
	fflush(write);
	memset(Msg, '\0', len);
	return ftell(write);
}