#include <stdio.h>
#include <string.h>
#include <stdbool.h>
int PrivateTest(void);
bool IsPasswordValid(void);
int main(void){
	bool PWverify;
	puts("Enter your password:");
	PWverify=IsPasswordValid();
	if(!PWverify){
		puts("Password Error!! Please try again.");
		return -1;
	}
	else puts("Welcome. Your password is correct.");
	return 0;
}
int PrivateTest(void)
{
	system("cat /home/hacker/flag");
	return 0;
}
bool IsPasswordValid(void){
	char Password[12];
	gets(Password);
	if(!strcmp(Password, "secure pro"))
		return(true);
	else return(false);
}
