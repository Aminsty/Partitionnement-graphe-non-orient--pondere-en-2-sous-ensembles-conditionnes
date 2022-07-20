//Réalisé par FAJRI Mohamed-Amine
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#define MAX_ITR 20

int N=0;//nombre de sommets

int** creer_matrice(char* path){//creation de la matrice d adjacence a partir du fichier txt
	int** matrice_adjascence;
	int i;
	char ligne[20];
	
	
	
	FILE* f;
	
	f=fopen(path, "r");
	
	if(f == NULL){
		printf("Erreur de lecture du fichier\n");
	}
	
	N = fgetc(f) - '0';
	fgets (ligne, 20, f);//vider le tampon
	
	matrice_adjascence = (int *)calloc(N, sizeof(int*));
	for(i = 0; i<N; i++) 
		matrice_adjascence[i] = (int *)calloc(N , sizeof(int));

	int j = 0;
	int k = 0;
	while (fgets (ligne, 20, f)) {
        
        for(i = 0; i < strlen(ligne); i++){
        	if(ligne[i]!=' ' && ligne[i]!='\n'){
        		int n = ligne[i] - '0';
        		matrice_adjascence[k][j] = n;
        		j++;
			}
			else
				continue;
		}
		j=0;
		
		k++;
    }
    fclose(f);
    return matrice_adjascence;
}

int f(int **a, int **b){//fonction objective, qui est la somme des poids
// des aretes avec un sommet de chaque sous-ensemble
	int i,j, s=0, k[N/2], somme=0;
	for(i=0;i<N;i++){
		for(j=0;j<N;j++){
			if(a[i][j]!=0){
				k[s]=i;
				s++;
				break;
			}
		}
	}
	for(i=0;i<N;i++){
		for(j=0;j<s;j++){
			somme+=b[i][k[j]];
		}
	}
	return somme;
}

