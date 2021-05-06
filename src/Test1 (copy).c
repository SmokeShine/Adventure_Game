/*
 ============================================================================
 Name        : Test1.c
 Author      : 
 Version     :
 ============================================================================
 */

#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
/*Use gcc -std=c89 to  compile
https://courses.cs.washington.edu/courses/cse351/16wi/sections/1/Cheatsheet-c.pdf */

static char *room_with_names[7];

/*Added typedef to avoid writing stuct when initializing objects*/
typedef struct Room{
    char title[50];
    int room_id;
} Room;

typedef struct Map{
    char start_room[50];
    char end_room[50];
}Map;
/*
int * random_generator(int lower, int upper,int count)
{
    int num;
    int i;
    int list[count];
    for(i=0; i<count; i++)
    {
        num=(rand()%(upper-lower+1))+lower;
        list[i]=num;
    }
    return list;
}*/

char *RoomName(int num )
{
    switch(num)
    {    
        case 1:    
            return "one ";    
            break;    
        case 2:    
            return "two ";    
            break;    
        case 3:    
            return "three ";    
            break;    
        case 4:    
            return "four ";    
            break;    
        case 5:    
            return "five ";    
            break;    
        case 6:    
            return "six ";    
            break;    
        case 7:    
            return "seven ";    
            break;    
        case 8:    
            return "eight ";    
            break;    
        case 9:    
            return "nine ";    
            break;    
        case 0:    
            return "zero ";    
            break;    
        default:    
            return "Time ";    
            break;    
    }        
}

void  getRandom(int lower, int upper)
{

   int  selected[7];
   int i;
   int num;
   int found;
   int count=0;
   /* set the seed */
   while (count<7)
   {
     found=0;  
     num = (rand()%(upper-lower+1))+lower;
     for ( i = 0; i < 7; i++)
     {
        if (selected[i]==num)
        {
        found=1;  
        }
     }
     if (found==0)
     {
        selected[count]=num;
        count++;
     }
   }
   for(i=0;i<7;i++)
   {
       room_with_names[i]=RoomName(selected[i]) ; 
   }
}
int main() {
	printf("!!!Welcome to Procedural Room Building!!! \n");
    int i;
    srand(time(0));
    /*int a;
    scanf("%d",&a);
    printf("You entered %d",a);
    */
    printf("Loading Individual Room Properties \n");
    Room room;
    printf("*******************\n");
    strcpy(room.title,"Sample Room");
    room.room_id=1;
    printf("Here is the sample created \n");
    printf("Room Name: %s\n", room.title);
    printf("Room ID: %d\n",room.room_id);
    printf("Possible Room Names \n");
    printf("*******************\n");
    for(i=0;i<9;i++)
    {
       printf("%s\n",RoomName(i)) ; 
    }
    printf("*******************\n");
    printf("Creating Map Now \n");
    printf("Selecting Rooms\n");
    getRandom(0,9);
    
    for(i=0; i<7;i++)
    {
       printf("%s \n",room_with_names[i]);
    }
    printf("Populating titles for our rooms placeholders \n");
    Room January, February, March, April, May, June, July; 
    strcpy(January.title,room_with_names[0]);
    strcpy(February.title,room_with_names[1]);
    strcpy(March.title,room_with_names[2]);
    strcpy(April.title,room_with_names[3]);
    strcpy(May.title,room_with_names[4]);
    strcpy(June.title,room_with_names[5]);
    strcpy(July.title,room_with_names[6]);

    printf("Placeholder populated with new room names\n");
    printf("Linking Rooms. Each Room will be connected to minimum of three other rooms to a maximum value of six rooms. Room cannot be connected to each other\n");
    return 0;
}
