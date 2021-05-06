#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h>
#include <time.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <pthread.h>
#include <assert.h>

#define NUM_THREADS 2

FILE *fptr;

int run_thread_a = 0;
pthread_mutex_t run_lock_a = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t run_cond_a = PTHREAD_COND_INITIALIZER;

int run_thread_b = 0;
pthread_mutex_t run_lock_b = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t run_cond_b = PTHREAD_COND_INITIALIZER;

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
int tagger = 0, Finished = 0;
int dummy = 0;

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
    static char newestDirName[256];
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
                stat(fileInDir->d_name, &dirAttributes);
                if ((int)dirAttributes.st_mtime > newestDirTime)
                {
                    newestDirTime = (int)dirAttributes.st_mtime;
                    memset(newestDirName, '\0', sizeof(newestDirName));
                    strcpy(newestDirName, fileInDir->d_name);
                }
            }
        }
    }
    closedir(dirToCheck);
    return newestDirName;
}

void *TimeKeeper(void *arguments)
{
    while (1)
    {
        /* Wait for Thread B to be runnable */
        pthread_mutex_lock(&run_lock_b);

        while (!run_thread_b)
            pthread_cond_wait(&run_cond_b, &run_lock_b);
            
        run_thread_b = 0;
        pthread_mutex_unlock(&run_lock_b);

        fptr = fopen("currentTime.txt", "w");
        if (fptr == NULL)
        {
            printf("Error!");
            exit(1);
        }
        time_t t = time(NULL);
        struct tm *tm = localtime(&t);
        char current_time[64];
        assert(strftime(current_time, sizeof(current_time), "%-I:%M%P, %A %B %e, %Y", tm));
        fprintf(fptr, "%s\n", current_time);

        fclose(fptr);
        /* Now wake thread A */
        pthread_mutex_lock(&run_lock_a);
        run_thread_a = 1;
        pthread_cond_signal(&run_cond_a);
        pthread_mutex_unlock(&run_lock_a);
    }
}

void printTime()
{

    /* printf("%s\n", current_time); */
    /*Create Write Thread*/

    char readTime[255];
    fptr = fopen("currentTime.txt", "r");
    if (fptr == NULL)
    {
        printf("No file to read\n");
    }
    fgets(readTime, 255, fptr);
    printf("\n%s\n", readTime);
    fclose(fptr);
}

void *mainGame(void *arguments)
{
    while (1)
    {

        DIR *dir;
        FILE *entry_file;
        struct dirent *in_file;
        char *folder;
        char *PREVIOUS_LOCATION = (char *)malloc(100);
        int numCharsEntered = -5;
        int i = 0, j_n = 0, z = 0, k = 0, hist = 0, connection = 0, hist_ = 0, loop_in = 0;
        char buffer[200];
        char str[255];
        char *ptr;

        size_t bufferSize = 0;
        char *history[20];
        char *lineEntered = NULL;

        Room *room_list[7] = {&January, &February, &March, &April, &May, &June, &July};

        Room *CURRENT_LOCATION, *END_LOCATION;

        init_rooms();
        folder = last_saved();

        dir = opendir(folder);
        if (dir == NULL)
        {
            printf("Error! Unable to read directory");
            exit(1);
        }
        i = 0;
        while ((in_file = readdir(dir)) != NULL)
        {
            if (!strcmp(in_file->d_name, "."))
                continue;
            if (!strcmp(in_file->d_name, ".."))
                continue;
            snprintf(str, sizeof(str), "%s/%s", folder, in_file->d_name);
            entry_file = fopen(str, "r");
            if (entry_file != NULL)
            {
                while (EOF != fscanf(entry_file, "%[^\n]\n", buffer))
                {
                    strtok_r(buffer, ":", &ptr);
                    if (strcmp(buffer, "ROOM NAME") == 0)
                    {
                        strcpy(room_list[i]->title, ptr + 1);
                    }
                    else if (strcmp(buffer, "ROOM TYPE") == 0)
                    {
                        if (strcmp(ptr + 1, "START_ROOM") == 0)
                        {
                            room_list[i]->room_type = 0;
                            CURRENT_LOCATION = room_list[i];
                        }
                        else if (strcmp(ptr + 1, "END_ROOM") == 0)
                        {

                            room_list[i]->room_type = 2;
                            END_LOCATION = room_list[i];
                        }
                        else
                        {
                            room_list[i]->room_type = 1;
                        }
                    }
                }
                fclose(entry_file);
                i++;
            }
        }

        closedir(dir);

        i = 0;
        dir = opendir(folder);

        while ((in_file = readdir(dir)) != NULL)
        {
            if (!strcmp(in_file->d_name, "."))
                continue;
            if (!strcmp(in_file->d_name, ".."))
                continue;

            snprintf(str, sizeof(str), "%s/%s", folder, in_file->d_name);
            entry_file = fopen(str, "r");
            if (entry_file != NULL)
            {
                j_n = 0;
                while (EOF != fscanf(entry_file, "%[^\n]\n", buffer))
                {
                    strtok_r(buffer, ":", &ptr);

                    if ((strcmp(buffer, "ROOM TYPE") != 0) && (strcmp(buffer, "ROOM NAME") != 0))
                    {
                        for (k = 0; k < 7; k++)
                        {
                            if (strcmp(room_list[k]->title, ptr + 1) == 0)
                            {
                                room_list[i]->neighbours[j_n] = room_list[k];
                                j_n++;
                                break;
                            }
                        }
                    }

                    room_list[i]->inbound_connections = j_n;
                }
                fclose(entry_file);
                i++;
            }
        }
        closedir(dir);

        strcpy(PREVIOUS_LOCATION, CURRENT_LOCATION->title);

        while (1)
        {
            loop_in = 0;
            if (strcmp(CURRENT_LOCATION->title, END_LOCATION->title) == 0)
            {
                printf("YOU HAVE FOUND THE END ROOM. CONGRATULATIONS!\n");
                printf("YOU TOOK %d STEPS. YOUR PATH TO VICTORY WAS:\n", hist);
                for (hist_ = 0; hist_ < hist; hist_++)
                {
                    printf("%s\n", history[hist_]);
                    free(history[hist_]);
                }
                Finished = 1;
                break;
            }

            printf("CURRENT LOCATION: %s\n", CURRENT_LOCATION->title);
            printf("POSSIBLE CONNECTIONS: ");
            for (z = 0; z < CURRENT_LOCATION->inbound_connections - 1; z++)
            {
                printf("%s, ", CURRENT_LOCATION->neighbours[z]->title);
            }
            printf("%s.\n", CURRENT_LOCATION->neighbours[CURRENT_LOCATION->inbound_connections - 1]->title);
            printf("WHERE TO? >");
            numCharsEntered = getline(&lineEntered, &bufferSize, stdin);
            lineEntered[numCharsEntered - 1] = '\0';
            while (strcmp(lineEntered, "time") == 0)
            {

                if (strcmp(lineEntered, "time") == 0)
                {

                    /* Now wake thread B */
                    pthread_mutex_lock(&run_lock_b);
                    run_thread_b = 1;
                    
                    pthread_cond_signal(&run_cond_b);
                    pthread_mutex_unlock(&run_lock_b);

                    /* Wait for Thread A to be runnable */
                    pthread_mutex_lock(&run_lock_a);
                    while (!run_thread_a)
                        pthread_cond_wait(&run_cond_a, &run_lock_a);
                    run_thread_a = 0;
                    pthread_mutex_unlock(&run_lock_a);
                    printTime();

                    printf("WHERE TO? >");

                    numCharsEntered = getline(&lineEntered, &bufferSize, stdin);
                    lineEntered[numCharsEntered - 1] = '\0';

                    if (strcmp(PREVIOUS_LOCATION, CURRENT_LOCATION->title) == 0)
                    {
                        loop_in = 0;
                    }
                }
            }
            for (connection = 0; connection < CURRENT_LOCATION->inbound_connections; connection++)
            {
                if (strcmp(lineEntered, CURRENT_LOCATION->neighbours[connection]->title) == 0)
                {
                    CURRENT_LOCATION = CURRENT_LOCATION->neighbours[connection];
                    history[hist] = (char *)malloc(100);
                    strcpy(history[hist], CURRENT_LOCATION->title);
                    hist++;
                    printf("\n");
                    strcpy(PREVIOUS_LOCATION, CURRENT_LOCATION->title);
                    loop_in = 1;
                    break;
                }
            }

            if ((strcmp(PREVIOUS_LOCATION, CURRENT_LOCATION->title) == 0) && (loop_in == 0))
            {
                printf("\nHUH? I DON'T UNDERSTAND THAT ROOM. TRY AGAIN.\n\n");
            }
            lineEntered = NULL;
            free(lineEntered);
        }
        free(PREVIOUS_LOCATION);
        return NULL;
    }
}

void *perform_work(void *argument)
{
    int passed_in_value;
    passed_in_value = *((int *)argument);
    printf("Hello World! It's me, thread with argument %d\n", passed_in_value);
    return NULL;
}

int main()
{
    int status;
    pthread_t threads_a;
    pthread_t threads_b;

    pthread_create(&threads_a, NULL, mainGame, NULL);
    pthread_create(&threads_b, NULL, TimeKeeper, NULL);

    pthread_join(threads_a, NULL);

    return 0;
}
