/* This file was modified as part of a git tutorial by 
 * shefin stevenson on 7/2/2016
 */
#include <stdio.h>
int main(int argc, char argv[])
{
  char name[10];
  
  printf("Who are you? ");
  fgets(name,10,stdin);
  
  printf("I am glad to meet you, %s.\n",name);
  
  return(0);
}



