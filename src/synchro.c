#include "synchro.h"
#include "ensitheora.h"
#include <pthread.h>
//using namespace std;



bool fini;

/* les variables pour la synchro, ici */
pthread_mutex_t mut ;
// Synchro pour taille de la fenêtre
pthread_mutex_t mut_taille;
pthread_cond_t cond_taille;
bool bool_taille = false;
// Synchro pour Fenetre
pthread_mutex_t mut_Fen;
pthread_cond_t cond_Fen;
// Synchro pour Texture
//pthread_cond_t cond_texture;

/* l'implantation des fonctions de synchro ici */
void envoiTailleFenetre(th_ycbcr_buffer buffer) {
// C’est le thread decodant le flux qui connaˆıt la taille de l’image a ` afficher,
// il doit donc transmettre cette taille et attendre la cr ́eation de la fenˆetre avant
// de poursuivre.
printf("entree taille \n");
pthread_mutex_lock(&mut_taille);
windowsx=buffer[0].width;
windowsy=buffer[0].height;
printf("milieu taille \n");
pthread_cond_signal(&cond_taille);
bool_taille=true;
pthread_mutex_unlock(&mut_taille);
printf("sortie taille \n");
}

void attendreTailleFenetre() {
  printf("entree wait \n");
pthread_mutex_lock(&mut_taille);
printf("mid wait \n");
if (!bool_taille) pthread_cond_wait(&cond_taille,&mut_taille);
pthread_mutex_unlock(&mut_taille);
printf("out wait \n");
}

void signalerFenetreEtTexturePrete() {
  pthread_mutex_lock(&mut_Fen);
  pthread_cond_signal(&cond_Fen);
  pthread_mutex_unlock(&mut_Fen);

}

void attendreFenetreTexture() {
  pthread_mutex_lock(&mut_Fen);
  pthread_cond_wait(&cond_Fen,&mut_Fen);
  pthread_mutex_unlock(&mut_Fen);
}

void debutConsommerTexture() {
}

void finConsommerTexture() {

}


void debutDeposerTexture() {
}

void finDeposerTexture() {
}
