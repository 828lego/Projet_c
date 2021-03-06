#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "graph.h"
#include "tas.h"
#include "pFile.h"

enum etat {sain, immunise, malade, mort, none}; //états possibles des individus

typedef struct Individu{ //création d'une pour chaque individu
    enum etat statut_actuel;
    enum etat statut_future;
} individu;

void initialisation(individu Matrice_adjacence);

void jour_suivant(individu Matrice_adjacence);
void etat_future_malade(individu i);
void etat_future_sain(individu i, int voisin_malade);


double lambda; //probabilité de tomber malade
double beta; //probabilité de mourir
double gama; //probabilité d'être immunisé

int population = 20 * 20;
int population_longueur = 20;


//Initialisation Matrice d'adjacence
void initialiasation(individu matrice_adjacence[population_longueur][population_longueur]) {
    for(int k = 0; k < population_longueur; k++){
        for(int i = 0; i < population_longueur; i++){
            matrice_adjacence[k][i].statut_actuel = sain;
            matrice_adjacence[k][i].statut_future = none;
        }
    }
    int abscisse = (int)rand()%(population_longueur);
    int ordonnee = (int)rand()%(population_longueur);
    matrice_adjacence[abscisse][ordonnee].statut_actuel = malade;
}

void jour_suivant(individu Matrice_adjacence[population_longueur][population_longueur]) {
    for (int k; k < population_longueur; k++) {
        for (int i = 0; i < population_longueur; i++) {
            if (Matrice_adjacence[i][k].statut_actuel == sain) {
                int voisin_malade=0;
                if (i<population-1 && Matrice_adjacence[i+1][k].statut_actuel == malade) {
                    voisin_malade=voisin_malade+1;
                }
                if (i>0 && Matrice_adjacence[i-1][k].statut_actuel == malade) {
                    voisin_malade=voisin_malade+1;
                }
                if (k<population-1 && Matrice_adjacence[i][k+1].statut_actuel == malade) {
                    voisin_malade=voisin_malade+1;
                }
                if (k>0 && Matrice_adjacence[i][k-1].statut_actuel == malade) {
                    voisin_malade=voisin_malade+1;
                }
                etat_future_sain(Matrice_adjacence[k][i],voisin_malade);
            }
            if (Matrice_adjacence[i][k].statut_actuel == malade)
                etat_future_malade(Matrice_adjacence[k][i]);
        }
    }
    for(int k = 0; k < population_longueur; k++){
        for(int i = 0; i < population_longueur; i++){
            Matrice_adjacence[k][i].statut_actuel = Matrice_adjacence[k][i].statut_future;
            Matrice_adjacence[k][i].statut_future = none;
        }
    }
}

void etat_future_sain(individu i, int voisin_malade) {
    double aleatoire;
    aleatoire=(double)(rand()%100)/100;
    if (aleatoire<=1-pow(lambda,voisin_malade)) {
        i.statut_actuel = malade;
    }
    else {
        i.statut_actuel = sain;
    }
}


void etat_future_malade(individu i) {
    int a;
    double aleatoire;
    aleatoire=(double)(rand()%100)/100;
    if (aleatoire<=1-gama) {
        a=0;
        i.statut_actuel = immunise;
    }
    aleatoire=(double)(rand()%100)/100;
    if (a=!0 && aleatoire<=1-beta) {
        i.statut_actuel = mort;
    }
    else {
        i.statut_actuel = malade;
    }
}



int main() {
    srand(time(NULL)); // permet d'avoir tout le temps des nombres aléatoires

    //initialisation();
    individu Matrice_adjacence[population_longueur][population_longueur];

    initialisation(Matrice_adjacence[population_longueur][population_longueur]);

    jour_suivant(individu Matrice_adjacence[population_longueur][population_longueur]);


    return 0;
}
