/*
 ============================================================================
 Name        : guptapr.buildrooms.c
 Author      : Prateek Gupta
 Version     : v1
 ============================================================================
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
    START_ROOM,
    MID_ROOM,
    END_ROOM
};
const char *room_type_str[] = {"START_ROOM", "MID_ROOM", "END_ROOM"};
struct Room
{
    char title[10];
    int inbound_connections;
    int outbound_connections;
    Room *neighbours[6];
    enum room_categories room_type;
};

char *room_with_names[7];
int selected[7];
Room January, February, March, April, May, June, July;
Room arr_room[7];
Room list[2];

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

void getRandom(int lower, int upper)
{

    int i;
    int num;
    int found;
    int count = 0;
    while (count < 7)
    {
        found = 0;
        num = (rand() % (upper - lower + 1)) + lower;
        for (i = 0; i < 7; i++)
        {
            if (selected[i] == num)
            {
                found = 1;
            }
        }
        if (found == 0)
        {
            selected[count] = num;
            count++;
        }
    }
    for (i = 0; i < 7; i++)
    {
        room_with_names[i] = RoomName(selected[i]);
    }
}
char *concat(const char *s1, const char *s2)
{
    char *result = malloc(strlen(s1) + strlen(s2) + 1);
    strcpy(result, s1);
    strcat(result, s2);
    return result;
}
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
    if (check_January == 1 && check_February == 1 && check_March == 1 && check_April == 1 && check_May == 1 && check_June == 1 && check_July == 1)
    {
        check = 1;
    }
    return check;
}
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
void show_grid(struct Room *room_list[7], char *filename)
{
    printf("#########Design Complete################\n");
    printf("%s \t %d\n", January.title, January.inbound_connections);
    printf("%s \t %d\n", February.title, February.inbound_connections);
    printf("%s \t %d\n", March.title, March.inbound_connections);
    printf("%s \t %d\n", April.title, April.inbound_connections);
    printf("%s \t %d\n", May.title, May.inbound_connections);
    printf("%s \t %d\n", June.title, June.inbound_connections);
    printf("%s \t %d\n", July.title, July.inbound_connections);
    printf("###########Neighbours##############\n");
    int i, j;
    for (i = 0; i < 7; i++)
    {
        room_list[i]->room_type = MID_ROOM;

        printf("\nRoom \t%s\n", room_list[i]->title);
        for (j = 0; j < room_list[i]->inbound_connections; j++)
        {
            printf("%s\t", room_list[i]->neighbours[j]->title);
        }
        printf("\n***************************\n");
    }
    printf("###########End of Neighbours##############\n");
    printf("Assigning Room Types\n");
    int count = 0;
    int found;
    int num;
    int upper = 6;
    int lower = 0;
    int duplicate_check = 1;

    int indx[2];
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

        duplicate_check = 0;
        int in = 0;
        for (i = 0; i < room_list[indx[0]]->inbound_connections; i++)
        {
            in = 1;
            int x = strcmp(room_list[indx[0]]->neighbours[i]->title, room_list[indx[1]]->title);
            if (x == 0)
            {
                duplicate_check = 1;
            }
        }
        if ((duplicate_check == 0) && (in == 1))
        {

            room_list[indx[0]]->room_type = START_ROOM;
            room_list[indx[1]]->room_type = END_ROOM;
        }
    }
    for (i = 0; i < 7; i++)
    {
        printf("%s \t %s \n", room_list[i]->title, room_type_str[room_list[i]->room_type]);
    }
    printf("###########End of Room Type##############\n");
    FILE *fptr;
    for (i = 0; i < 7; i++)
    {
        /* char* s = concat(filename,room_list[i]->title); */
        char str[255];
        snprintf(str, sizeof(str), "./%s/%s_room", filename, room_list[i]->title);
        printf("%s\n", str);
        fptr = fopen(str, "w");
        if (fptr == NULL)
        {
            printf("Error!");
            exit(1);
        }

        fprintf(fptr, "ROOM NAME: %s\n", room_list[i]->title);

        for (j = 0; j < room_list[i]->inbound_connections; j++)
        {
            fprintf(fptr, "CONNECTION %d: %s\n",j+1 ,room_list[i]->neighbours[j]->title); 
        }
        fprintf(fptr, "ROOM TYPE: %s\n\n", room_type_str[room_list[i]->room_type]);
        fclose(fptr);
    }
}
int main()
{
    int i;
    srand(time(0));
    getRandom(1, 10);
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
            if (duplicate_check == 0)
            {
                room_list[indx[0]]->neighbours[room_list[indx[0]]->inbound_connections] = room_list[indx[1]];
                room_list[indx[1]]->neighbours[room_list[indx[1]]->inbound_connections] = room_list[indx[0]];

                room_list[indx[0]]->inbound_connections++;
                room_list[indx[1]]->inbound_connections++;
            }
        }
    }
    /*show_grid(room_list);*/
    int pid = getpid();
    int buffsize = 20;
    char *fileName = malloc(buffsize);
    char *prefix = "guptapr.rooms.";
    snprintf(fileName, buffsize, "%s%d", prefix, pid);
    /*  printf("%s\n",fileName); */

    struct stat st = {0};

    if (stat(fileName, &st) == -1)
    {
        mkdir(fileName, 0755);
    }
    show_grid(room_list, fileName);
    return 0;
}
