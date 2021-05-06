#include <stdio.h>
#include <string.h>
#include <dirent.h>
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

char *last_saved()
{
    int newestDirTime = -1;
    char targetDirPrefix[32] = "guptapr.rooms.";
    static char newestDirName[256]; /*using static so that memory is not flushed once function call is over*/
    memset(newestDirName, '\0', sizeof(newestDirName));
    DIR *dirToCheck;
    struct dirent *fileInDir;
    struct stat dirAttributes;
    dirToCheck = opendir(".");
    if (dirToCheck > 0)
    {
        while ((fileInDir = readdir(dirToCheck)) != NULL)
        {
            if (strstr(fileInDir->d_name, targetDirPrefix) != NULL)
            {
                /* printf("Found the prefix: %s\n",fileInDir->d_name); */
                stat(fileInDir->d_name, &dirAttributes);
                if ((int)dirAttributes.st_mtime > newestDirTime)
                {
                    newestDirTime = (int)dirAttributes.st_mtime;
                    memset(newestDirName, '\0', sizeof(newestDirName));
                    strcpy(newestDirName, fileInDir->d_name);
                    /*    printf("Newer subdir: %s, new time: %d\n",fileInDir->d_name,newestDirTime); */
                }
            }
        }
    }
    closedir(dirToCheck);
    /* printf("Newest entry found is %s\n", newestDirName); */
    return newestDirName;
}
int main()
{
    char *folder;
    Room *room_list[7] = {&January, &February, &March, &April, &May, &June, &July};
    init_rooms();
    printf("%s\n", "Welcome to the Adventure Game!!!\n");
    printf("Read the last folder created\n");
    folder = last_saved();
    printf("Checking files in the %s\n", folder);
    int i = 0;

    printf("###########End of Room Type##############\n");
    DIR *dir;
    FILE *entry_file;
    struct dirent *in_file;

    dir = opendir(folder);
    char buffer[30];
    if (dir == NULL)
    {
        printf("Error! Unable to read directory");
        exit(1);
    }

    while ((in_file = readdir(dir)) != NULL)
    {
        if (!strcmp(in_file->d_name, "."))
            continue;
        if (!strcmp(in_file->d_name, ".."))
            continue;
        /* printf("%s\n", in_file->d_name);*/
        char str[255];
        char *ptr;
        snprintf(str, sizeof(str), "%s/%s", folder, in_file->d_name);
        entry_file = fopen(str, "r");
        if (entry_file != NULL)
        {
            int j = 0;
            printf(".............................\n");
            /* whatever you want to do with files */
            while (EOF != fscanf(entry_file, "%[^\n]\n", buffer))
            {
                /*  printf("> %s\n", buffer); */
                strtok_r(buffer, ":", &ptr);
                if (strcmp(buffer, "ROOM NAME") == 0)
                {
                    /*   printf("%s\t%s\n", buffer, ptr + 1);*/ /*For removing spaces*/
                    strcpy(room_list[i]->title, ptr + 1);
                    printf("%s\n", room_list[i]->title);
                }
                else if (strcmp(buffer, "ROOM TYPE") == 0)
                {
                    if (strcmp(ptr + 1, "START ROOM") == 0)
                    {
                        room_list[i]->room_type = 0;
                    }
                    else if (strcmp(ptr + 1, "END ROOM") == 0)
                    {

                        room_list[i]->room_type = 2;
                    }
                    else
                    {
                        room_list[i]->room_type = 1;
                    }
                    printf("%s \t %s \n", room_list[i]->title, room_type_str[room_list[i]->room_type]);
                }
            }
            /* Need to do string comparison to read files */
            /* and then push to pointer*/
            fclose(entry_file);
            i++;
        }
    }

    closedir(dir);
    printf("###########End of Room Type####dddddddddddddddddd##########\n");
    /* char* s = concat(filename,room_list[i]->title); */
    FILE *entry_file_n;
    struct dirent *in_file_n;
    i = 0;
    dir = opendir(folder);
    char buffer_n[30];
    if (dir == NULL)
    {
        printf("Error! Unable to read directory");
        exit(1);
    }

    while ((in_file_n = readdir(dir)) != NULL)
    {
        if (!strcmp(in_file_n->d_name, "."))
            continue;
        if (!strcmp(in_file_n->d_name, ".."))
            continue;
        /* printf("%s\n", in_file->d_name);*/
        char str_n[255];
        char *ptr_n;
        printf("%s\n", in_file_n->d_name);
        snprintf(str_n, sizeof(str_n), "%s/%s", folder, in_file_n->d_name);
        entry_file_n = fopen(str_n, "r");
        if (entry_file_n != NULL)
        {
            int j_n = 0;
            while (EOF != fscanf(entry_file_n, "%[^\n]\n", buffer_n))
            {
                strtok_r(buffer_n, ":", &ptr_n);
                if ((strcmp(buffer_n, "ROOM NAME") != 0) && (strcmp(buffer_n, "ROOM TYPE") != 0))

                {
                    /*                   printf("%s\n", ptr_n+1);*/
                    int k;
                    for (k = 0; k < 7; k++)
                    {
                        if (strcmp(room_list[k]->title, ptr_n + 1) == 0)
                        {
                            room_list[i]->neighbours[j_n] = room_list[k];
                            j_n++;
                            break;
                        }
                    }
                }
                room_list[i]->inbound_connections=j_n;
            }
            fclose(entry_file_n);
            i++;
        }
    }
    closedir(dir);
    printf("###########End of Room Type######xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx########\n");
    for (i=0;i<7;i++)
    {
        printf("%s\t%d\n",room_list[i]->title,room_list[i]->inbound_connections);
    }
    printf("###########End of Room Type######xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx########\n");
    /*
                else
                {
                    printf("These are all neighbours\n");
                    printf("%d\n",j);
                    room_list[i]->neighbours[j]=getObject(ptr+1);
                    strcpy(room_list[i]->neighbours[j]->title,ptr+1);
                    printf("%s\n",ptr+1);
                    j++;
                }
        char str[255];
        strcpy(room_list[i]->title,"Good");
        fptr = fopen(str, "r");
        if (fptr == NULL)
        {
            printf("Error!");
            exit(1);
        }

        strcpy("ROOM NAME",room_list[i]->title);

        for (j = 0; j < room_list[i]->inbound_connections; j++)
        {
            strcpy("CONNECTION:",room_list[i]->neighbours[j]->title); 
        }
        strcpy("ROOM TYPE:", room_type_str[room_list[i]->room_type]);
        fclose(fptr);
        }
    */

    printf("Reading Rooms Data\n");
    printf("CURRENT LOCATION\n");
    printf("POSSIBLE CONNECTIONS\n");
    printf("WHERE TO?\n");
    printf("HUH? I DON'T UNDERSTAND THAT ROOM. TRY AGAIN\n");
    return 0;
}
