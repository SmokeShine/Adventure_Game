#include <stdio.h>
#include <string.h>
#include <stdlib.h>
int main()
{
    printf("Hello World\n");
    int* i;
    int a;
    i=&a;
    a=5;
    printf("%d\n",*i);
    printf("Content of i is %p\n",i);

    char* str;
    str="Prateek";
    printf("%s with pointer \n",str);

   char str_x[20]="Prateek";
   str_x[2]='O';
   printf("%s----\n",str_x);
    char str2[80] = {'P', 'R', 'A','T','E','E','K' ,'\0'};  
    printf("%s with addressing\n",str2);
    str2[2]='Z';
    str_x="Hello";
    printf("%s\n\n",str2);
   /* char* str3=(char *)malloc(8*sizeof(char)); */
    
    char* str3;
    str3=str_x;
    printf("%s with malloc\n",str3);

    char st_array[]="Prateek";
    printf("%s with array\n",st_array);
   char name[20];
   char *address;

   strcpy(name, "Harry Lee");
   address = (char*)malloc( 50 * sizeof(char) );  /* allocating memory dynamically  */
   strcpy( address, "Lee Fort, 11-B Sans Street");

   printf("Name = %s\n", name );
   printf("Address: %s\n", address );
    char st_array_copy[20];
    strcpy(st_array_copy,st_array);
    printf("Array are second class citizen %s\n",st_array_copy);
}
