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

/*Remove global variables*/

/*Added typedef to avoid writing stuct when initializing objects*/
typedef struct Room{
    char title[50];
    int inbound_connections;
    int outbound_connections;
    int in[6];
    int out[6];
} Room;

char *room_with_names[7];
int  selected[7];
Room January,February,March,April,May,June,July;
struct Room arr_room[7];
struct Room list[2];

Room ABSelection(int num )
{
    switch(num)
    {    
        case 0:    
            return January;    
            break;    
        case 1:    
            return February;    
            break;    
        case 2:    
            return March;    
            break;    
        case 3:    
            return April;    
            break;    
        case 4:    
            return May;    
            break;    
        case 5:    
            return June;    
            break;    
        case 6:    
            return July;    
        default:    
            return January;    
            break;    
    }        
}


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

int IsGraphFull()
{
    int check=0;
    int check_January=0,check_February=0,check_March=0,check_April=0,check_May=0,check_June=0,check_July=0;
    if ((January.inbound_connections==January.outbound_connections) &&  (January.inbound_connections>=3) && (January.inbound_connections<=6))
        check_January=1;
    if ((February.inbound_connections==February.outbound_connections) &&  (February.inbound_connections>=3) && (February.inbound_connections<=6))
        check_February=1;
    if ((March.inbound_connections==March.outbound_connections) &&  (March.inbound_connections>=3) && (March.inbound_connections<=6))
        check_March=1;
    if ((April.inbound_connections==April.outbound_connections) &&  (April.inbound_connections>=3) && (April.inbound_connections<=6))
        check_April=1;
    if ((May.inbound_connections==May.outbound_connections) &&  (May.inbound_connections>=3) && (May.inbound_connections<=6))
        check_May=1;
    if ((June.inbound_connections==June.outbound_connections) &&  (June.inbound_connections>=3) && (June.inbound_connections<=6))
        check_June=1;
    if ((July.inbound_connections==July.outbound_connections) &&  (July.inbound_connections>=3) && (July.inbound_connections<=6))
        check_July=1;
  /*  printf("%d\n",check_January);
    printf("%d\n",check_February);
    printf("%d\n",check_March);
    printf("%d\n",check_April);
    printf("%d\n",check_May);
    printf("%d\n",check_June);
    printf("%d\n",check_July);
    */
    if (check_January==1 && check_February==1 && check_March==1 && check_April==1 && check_May==1 && check_June==1 && check_July==1)
    {
        check=1;
    }
/*
    printf("In the loop");
    printf("%d\n",check_January);
    printf("%d\n",check_February);
    printf("%d\n",check_March);
    printf("%d\n",check_April);
    printf("%d\n",check_May);
    printf("%d\n",check_June);
    printf("%d\n",check_July);
    printf("In the loop");
*/
    return check;
}
void init_rooms()
{
    January.inbound_connections=0;
    January.outbound_connections=0;
    February.inbound_connections=0;
    February.outbound_connections=0;
    March.inbound_connections=0;
    March.outbound_connections=0;
    April.inbound_connections=0;
    April.outbound_connections=0;
    May.inbound_connections=0;
    May.outbound_connections=0;
    June.inbound_connections=0;
    June.outbound_connections=0;
    July.inbound_connections=0;
    July.outbound_connections=0;
}
int main() {
/*	printf("!!!Welcome to Procedural Room Building!!! \n"); */
    int i;
    srand(time(0));
    /*int a;
    scanf("%d",&a);
    printf("You entered %d",a);
    
    printf("Loading Individual Room Properties \n"); 
    Room room;
    printf("*******************\n");
    strcpy(room.title,"Sample Room");
    room.inbound_connections=1;
    room.outbound_connections=1;
    printf("Here is the sample created \n");
    printf("Room Name: %s\n", room.title);
    printf("Room Inbound Connections: %d\n",room.inbound_connections);
    printf("Room Outbound Connections: %d\n",room.outbound_connections);
    printf("Possible Room Names \n");
    for(i=0;i<10;i++)
    {
       printf("%s\n",RoomName(i)) ; 
    }
    printf("Creating Map Now \n");
    printf("Selecting Rooms\n");
    */
    getRandom(0,9);
   /* 
    for(i=0; i<7;i++)
    {
       printf("%s \n",room_with_names[i]);
    }
    */
  /*  printf("Populating titles for our rooms placeholders \n"); */
    strcpy(January.title,room_with_names[0]);
    strcpy(February.title,room_with_names[1]);
    strcpy(March.title,room_with_names[2]);
    strcpy(April.title,room_with_names[3]);
    strcpy(May.title,room_with_names[4]);
    strcpy(June.title,room_with_names[5]);
    strcpy(July.title,room_with_names[6]);
    init_rooms();
  /*  printf("Placeholder populated with new room names\n");
    printf("Linking Rooms. Each Room will be connected to minimum of three other rooms to a maximum value of six rooms. Same Room cannot be connected to itself\n");
    */
    Room *room_list[7]={&January,&February,&March,&April,&May,&June,&July};
  /*  printf("Start\n%s\n",room_list[0]->title); */
    int count;
    int found;
    int num;
    int upper = 6;
    int lower=0;
    while (IsGraphFull()!=1)
    {
    
        count=0;
    /*    printf("Selecting two rooms\n"); */
        int indx[2];
        while (count<2)
        {
        /*    printf("Now adding adding connection\n");*/
            found=0;  
            num = (rand()%(upper-lower+1))+lower;
            for ( i = 0; i < 2; i++)
            {
                if (indx[i]==num)
                {
                    found=1;  
                }
            }
            if (found==0)
            {
                indx[count]=num;
                count++;
            }
        }
      /*  printf("**********aaaaaaaa*********\n");
        printf("Selected Rooms:%s and %s \n",room_list[indx[0]]->title,room_list[indx[1]]->title);
        printf("**********aaaaaaaaaa*********\n");
        printf("Checking if connection is not breaching threshold\n");
        */
        if (!((room_list[indx[0]]->inbound_connections>=3)&&(room_list[indx[0]]->inbound_connections<=6)&&(room_list[indx[1]]->inbound_connections>=3)&&(room_list[indx[1]]->inbound_connections<=6)))
        {
           /* printf("Updating Inbound and Outbound Connection Count\n");*/
            room_list[indx[0]]->inbound_connections++;
            room_list[indx[1]]->inbound_connections++;
            room_list[indx[0]]->outbound_connections++;
            room_list[indx[1]]->outbound_connections++;
        }
        
    }
            printf("#########Design Complete################\n");
            printf("%s \t %d\n",January.title,January.inbound_connections);
            printf("%s \t %d\n",February.title,February.inbound_connections);
            printf("%s \t %d\n",March.title,March.inbound_connections);
            printf("%s \t %d\n",April.title,April.inbound_connections);
            printf("%s \t %d\n",May.title,May.inbound_connections);
            printf("%s \t %d\n",June.title,June.inbound_connections);
            printf("%s \t %d\n",July.title,July.inbound_connections);
            printf("#########################\n");
    return 0;
}
