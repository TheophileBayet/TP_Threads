#include <stdio.h>
#include <unistd.h>
#include <assert.h>
#include <SDL2/SDL.h>
#include <pthread.h>

#include "stream_common.h"
#include "oggstream.h"


int main(int argc, char *argv[]) {
    int res;

    if (argc != 2) {
	fprintf(stderr, "Usage: %s FILE", argv[0]);
	exit(EXIT_FAILURE);
    }
    assert(argc == 2);


    // Initialisation de la SDL
    res = SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO|SDL_INIT_EVENTS);
    atexit(SDL_Quit);
    assert(res == 0);

    // start the two stream readers
    pthread_t t1;
    pthread_t t2;

    pthread_create(&t1,NULL,theoraStreamReader,argv[1]);
    printf(" pthread_create theoraStreamReader \n");
    pthread_create(&t2,NULL,vorbisStreamReader,argv[1]);
    printf(" pthread_create vorbisStreamReader \n");

    // wait audio thread
    pthread_join(t2,NULL);
    // 1 seconde de garde pour le son,
    sleep(1);

    // tuer les deux threads videos si ils sont bloqués
    pthread_cancel(t1);
    pthread_cancel(t2);
    // attendre les 2 threads videos
    pthread_join(t1,NULL);
    pthread_join(t2,NULL);

    exit(EXIT_SUCCESS);
}
