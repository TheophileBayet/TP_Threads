#include "synchro.h"
#include "ensitheora.h"
#include <pthread.h>
//using namespace std;



bool fini;

/* les variables pour la synchro, ici */
pthread_mutex_t mut ;
pthread_mutex_t mut_taille;
pthread_cond_t cond_taille;

/* l'implantation des fonctions de synchro ici */
void envoiTailleFenetre(th_ycbcr_buffer buffer) {
// C’est le thread decodant le flux qui connaˆıt la taille de l’image a ` afficher,
// il doit donc transmettre cette taille et attendre la cr ́eation de la fenˆetre avant
// de poursuivre.
printf("entree taille \n");
pthread_mutex_lock(&mut_taille);
//windowsx=buffer[0].width;
//windowsy=buffer[0].height;
printf("milieu taille \n");
pthread_cond_signal(&cond_taille);
pthread_mutex_unlock(&mut_taille);
printf("sortie taille \n");
}

void attendreTailleFenetre() {
  printf("entree wait \n");
pthread_mutex_lock(&mut_taille);
printf("mid wait \n");
pthread_cond_wait(&cond_taille,&mut_taille);
pthread_mutex_unlock(&mut_taille);
printf("out wait \n");
}

void signalerFenetreEtTexturePrete() {
}

void attendreFenetreTexture() {
}

void debutConsommerTexture() {
}

void finConsommerTexture() {
}


void debutDeposerTexture() {
}

void finDeposerTexture() {
}
