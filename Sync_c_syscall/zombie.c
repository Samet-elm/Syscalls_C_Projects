#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h> //rand() fonksiyonu için

#define MAX_DOORMEN 10
#define MAX_SLAYERS 3
/*number of zombies in the game:
you should synchronize threads editing this variable
*/
int zombieCounter = 0;
int killCounter = 0;

void zombieEntered();
void zombieKilled();
int tooManyZombiesInTheRoom();
int killed100Zombies();
int zombiesExist();
int getKilledCount();
int getInTheRoomCount();
void *doorMan(void *p);
void *slayer(void *p);

/* Keeps track of number of zombies entered.*/
void zombieEntered()
{
    zombieCounter += 1;
}
/* Keeps track of number of zombies killed.*/
void zombieKilled()
{
    killCounter += 1;
    zombieCounter -= 1;
}
/* Returns true if number of zombies in the room are
greater than or equal to 100.*/
int tooManyZombiesInTheRoom()
{
    int count = getInTheRoomCount();
    if (count >= 100)
    {
        //printf("you are died\n");
        return 1;
    }
    return 0;
}

/*Returns true if more than 100 zombies have been killed.*/
int killed100Zombies()
{
    int kill = getKilledCount();
    if (kill >= 100)
    {
        //printf("conguralations you killed 100 zombies\n");
        return 1;
    }
    return 0;
}

/* Returns true if there is at least one zombies in the room.*/
int zombiesExist()
{
    int count = getInTheRoomCount();
    if (count >= 1)
    {
        return 0;
    }
    else
    {
        //printf("There are no zombies in the room\n");
        return 1;
    }
    return 0;
}
/*Returns the number of zombies killed.*/
int getKilledCount()
{
    return killCounter;
}

/* Returns the number of zombies in the room.*/
int getInTheRoomCount()
{
    return zombieCounter;
}

/*doorman thread*/
void *doorMan(void *p)
{
    do
    {
        usleep(2000);
        //%50 ihtimalle kapıdan bir zombi alınır
        if (rand() % 2 == 1)
        {
            zombieEntered();
        }
        // printf("odadaki zombie sayısı: %d", zombieCounter);
    } while (!killed100Zombies() && !tooManyZombiesInTheRoom() && !zombiesExist());
    return 0;
}

/*slayer thread*/
void *slayer(void *p)
{
    do
    {
        usleep(2000);
        zombieKilled();
        // printf("odadaki zombie sayısı: %d", zombieCounter);
    } while (!killed100Zombies() && !tooManyZombiesInTheRoom() && !zombiesExist());
    return 0;
}
/*simulator main thread*/
int main(int argc, char **argv)
{
    pthread_t threads_d[MAX_DOORMEN];
    pthread_t threads_s[MAX_SLAYERS];
    int i = 0, j = 0;
    for (i = 0; i < MAX_DOORMEN; i++)
    {
        pthread_create(&threads_d[i], NULL, doorMan, NULL);
    }

    for (j = 0; j < MAX_SLAYERS; j++)
    {
        pthread_create(&threads_s[j], NULL, slayer, NULL);
    }

    for (i = 0; i < MAX_DOORMEN; i++)
    {
        pthread_join(threads_d[i], NULL);
    }

    for (j = 0; j < MAX_SLAYERS; j++)
    {
        pthread_join(threads_s[j], NULL);
    }

    if (zombieCounter >= 100)
    {
        printf("100 or more zombies in the room\n");
        printf("you died\n");
    }
    if (killCounter >= 100)
    {
        printf("conguralations,you killed 100 zombies\n");
    }
    if (zombieCounter < 1)
    {
        printf("there are no zombies in the room\n");
    }
    printf("Total number of zombies in the room:%d\n",zombieCounter);
    printf("Number of killed zombies:%d\n", killCounter);

    return 0;
}
