/*
 ============================================================================
 Name        : guptapr.buildrooms.c
 Author      : Prateek Gupta
 Version     : v1
 ============================================================================
 */

/*                                      File Usage - Ubuntu                                    */

/*
Compile: gcc -std=c89 guptapr.buildrooms.c -o guptapr.buildrooms
Execute: ./guptapr.buildrooms
Return: Create 7 rooms and randomly connects them.
Example Room
$ cat guptapr.rooms.47655/XYZZY_room 
ROOM NAME: XYZZY
CONNECTION 1: Ezio
CONNECTION 2: Drake
CONNECTION 3: PLOVER
ROOM TYPE: START_ROOM

$ cat guptapr.rooms.47655/Ezio_room 
ROOM NAME: Ezio
CONNECTION 1: XYZZY
CONNECTION 2: PLOVER
CONNECTION 3: Dungeon
CONNECTION 4: Zork
ROOM TYPE: MID_ROOM

*/

#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

typedef struct Room Room;

enum room_categories
{
    /*                           Categories for start, mid and end room                     */
    START_ROOM,
    MID_ROOM,
    END_ROOM
};

/*                               Charracter array to convert enum to text                   */
const char *room_type_str[] = {"START_ROOM", "MID_ROOM", "END_ROOM"};

/*                          Struct to create the room. Each room should have a title, number of connection, neighbours and room type                */
struct Room
{
    char title[10];
    int inbound_connections;
    Room *neighbours[6];
    enum room_categories room_type;
};

/*                                          Room objects                                       */
char *room_with_names[7];
Room January, February, March, April, May, June, July;

/*Helper variables*/
int selected[7];
Room arr_room[7];
Room list[2];

/*                                   Number to room text conversion                            */
char *RoomName(int num)
{
    switch (num)
    {
    case 1:
        return "XYZZY";
        break;
    case 2:
        return "PLUGH";
        break;
    case 3:
        return "PLOVER";
        break;
    case 4:
        return "twisty";
        break;
    case 5:
        return "Zork";
        break;
    case 6:
        return "Crowther";
        break;
    case 7:
        return "Dungeon";
        break;
    case 8:
        return "Nathan";
        break;
    case 9:
        return "Drake";
        break;
    case 10:
        return "Ezio";
    default:
        return "Time";
        break;
    }
}

/*                              Select 7 random rooms from 
                                        XYZZ
                                        PLUGH
                                        PLOVER
                                        twisty
                                        Zork
                                        Crowther
                                        Dungeon
                                        Nathan
                                        Drake
                                        Ezio
*/
void getRandom(int lower, int upper)
{

    int i;
    int num;
    int found;
    int count = 0;
    /*Loop till 7 rooms are not found*/
    while (count < 7)
    {
        found = 0;
        num = (rand() % (upper - lower + 1)) + lower;
        /*Check for duplicate*/
        for (i = 0; i < 7; i++)
        {
            if (selected[i] == num)
            {
                found = 1;
            }
        }
        /*Add Room*/
        if (found == 0)
        {
            selected[count] = num;
            count++;
        }
    }
    /*Update Room Name*/
    for (i = 0; i < 7; i++)
    {
        room_with_names[i] = RoomName(selected[i]);
    }
}

/*                              Check if all the constraints are satisfied                          */
int IsGraphFull()
{
    int check = 0;
    int check_January = 0, check_February = 0, check_March = 0, check_April = 0, check_May = 0, check_June = 0, check_July = 0;
    if ((January.inbound_connections >= 3) && (January.inbound_connections <= 6))
        check_January = 1;
    if ((February.inbound_connections >= 3) && (February.inbound_connections <= 6))
        check_February = 1;
    if ((March.inbound_connections >= 3) && (March.inbound_connections <= 6))
        check_March = 1;
    if ((April.inbound_connections >= 3) && (April.inbound_connections <= 6))
        check_April = 1;
    if ((May.inbound_connections >= 3) && (May.inbound_connections <= 6))
        check_May = 1;
    if ((June.inbound_connections >= 3) && (June.inbound_connections <= 6))
        check_June = 1;
    if ((July.inbound_connections >= 3) && (July.inbound_connections <= 6))
        check_July = 1;
    /*Check if constraints for all the rooms are met*/
    if (check_January == 1 && check_February == 1 && check_March == 1 && check_April == 1 && check_May == 1 && check_June == 1 && check_July == 1)
    {
        check = 1;
    }
    return check;
}

/*                                 Initiate rooms with zero connections                             */

void init_rooms()
{
    January.inbound_connections = 0;
    February.inbound_connections = 0;
    March.inbound_connections = 0;
    April.inbound_connections = 0;
    May.inbound_connections = 0;
    June.inbound_connections = 0;
    July.inbound_connections = 0;
}

/*                              Show Current Floor Plan and Assign Room Types                                       */
void show_grid(struct Room *room_list[7], char *filename)
{
    int i, j;
    for (i = 0; i < 7; i++)
    {
        room_list[i]->room_type = MID_ROOM;
    }

    /*                                          Random Selection of Start and End Room                          */
    int count = 0;
    int found;
    int num;
    int upper = 6;
    int lower = 0;
    int duplicate_check = 1;
    int indx[2];
    /*Select two random rooms for start and end*/
    /*Ensure they are not direction connections*/
    while (duplicate_check != 0)
    {
        indx[0] = -10;
        indx[1] = -10;
        count = 0;
        while (count < 2)
        {
            found = 0;
            num = (rand() % (upper - lower + 1)) + lower;
            for (i = 0; i < 2; i++)
            {
                if (indx[i] == num)
                {
                    found = 1;
                }
            }
            if (found == 0)
            {
                indx[count] = num;
                count++;
            }
        }
        /*                                      Check if connection is already present                                  */
        duplicate_check = 0;
        int in = 0;
        /*If direct neighbours, ignore and take another set*/
        for (i = 0; i < room_list[indx[0]]->inbound_connections; i++)
        {
            in = 1;
            int x = strcmp(room_list[indx[0]]->neighbours[i]->title, room_list[indx[1]]->title);
            if (x == 0)
            {
                duplicate_check = 1;
            }
        }
        /*If not neighbours, assign as start and end room*/
        if ((duplicate_check == 0) && (in == 1))
        {

            room_list[indx[0]]->room_type = START_ROOM;
            room_list[indx[1]]->room_type = END_ROOM;
        }
    }

    /*                                                  Saving Floor Plan                                               */
    FILE *fptr;
    for (i = 0; i < 7; i++)
    {
        char str[255];
        snprintf(str, sizeof(str), "./%s/%s_room", filename, room_list[i]->title);
        fptr = fopen(str, "w");
        if (fptr == NULL)
        {
            printf("Error!");
            exit(1);
        }
        fprintf(fptr, "ROOM NAME: %s\n", room_list[i]->title);
        /*Update all the connections in the file*/
        for (j = 0; j < room_list[i]->inbound_connections; j++)
        {
            fprintf(fptr, "CONNECTION %d: %s\n", j + 1, room_list[i]->neighbours[j]->title);
        }
        /*Add Room Type*/
        fprintf(fptr, "ROOM TYPE: %s\n", room_type_str[room_list[i]->room_type]);
        fclose(fptr);
    }
}
int main()
{
    int i;
    srand(time(0));
    getRandom(1, 10);
    /*                                                      Room Selection                                                  */
    strcpy(January.title, room_with_names[0]);
    strcpy(February.title, room_with_names[1]);
    strcpy(March.title, room_with_names[2]);
    strcpy(April.title, room_with_names[3]);
    strcpy(May.title, room_with_names[4]);
    strcpy(June.title, room_with_names[5]);
    strcpy(July.title, room_with_names[6]);
    init_rooms();
    Room *room_list[7] = {&January, &February, &March, &April, &May, &June, &July};
    int count;
    int found;
    int num;
    int upper = 6;
    int lower = 0;
    int duplicate_check = 0;
    int threshold = 0;
    /*                          Keep on selecting two rooms and connect them till all the graph constraints are satisfied               */
    while (IsGraphFull() != 1)
    {
        count = 0;
        int indx[2];
        while (count < 2)
        {
            found = 0;
            num = (rand() % (upper - lower + 1)) + lower;
            for (i = 0; i < 2; i++)
            {
                if (indx[i] == num)
                {
                    found = 1;
                }
            }
            if (found == 0)
            {
                indx[count] = num;
                count++;
            }
        }
        /*Try to connect room*/
        if (!((room_list[indx[0]]->inbound_connections >= 3) && (room_list[indx[0]]->inbound_connections <= 6) && (room_list[indx[1]]->inbound_connections >= 3) && (room_list[indx[1]]->inbound_connections <= 6)))
        {
            duplicate_check = 0;
            for (i = 0; i < room_list[indx[0]]->inbound_connections; i++)
            {
                int x = strcmp(room_list[indx[0]]->neighbours[i]->title, room_list[indx[1]]->title);
                if (x == 0)
                {
                    threshold++;
                    duplicate_check = 1;
                }
            }
            /*Connect*/
            if (duplicate_check == 0)
            {
                room_list[indx[0]]->neighbours[room_list[indx[0]]->inbound_connections] = room_list[indx[1]];
                room_list[indx[1]]->neighbours[room_list[indx[1]]->inbound_connections] = room_list[indx[0]];
                /*Update Connection count*/
                room_list[indx[0]]->inbound_connections++;
                room_list[indx[1]]->inbound_connections++;
            }
        }
    }

    /*                                                  Saving Floor Plan                       */
    int pid = getpid();
    int buffsize = 20;
    char *fileName = malloc(buffsize);
    char *prefix = "guptapr.rooms.";
    snprintf(fileName, buffsize, "%s%d", prefix, pid);
    struct stat st = {0};
    if (stat(fileName, &st) == -1)
    {
        mkdir(fileName, 0755);
    }
    show_grid(room_list, fileName);
    return 0;
}
