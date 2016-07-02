#include <stdio.h> 
#include <string.h>

int main()
{

	char str1[50];
	char str2[50];
	printf("Enter string1:"); scanf("%s",&str1);
	printf("\n Enter string 2:"); scanf("%s", &str2); 

	int cmp = strcoll(str1,str2);

	if(cmp == 0) {
	printf("strings are equal");
	}else
	if(cmp < 0) {
	printf("string 1:%s is lower",str1);
	} else {
	printf("string 1:%s is lower",str1);
	}
	return 0;
}


