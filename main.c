//Réalisé par FAJRI Mohamed-Amine
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "graph.h">
#define MAX_ITR 20
int main(){
	char *list_tabou[20];//la liste tabou est un tableau
	//de chaines de caracteres où on va stocker les sous-ensembles
	//parcourues par la manière : sommets_sous_ensemble1+sommets_sous_ensemble2
	
	char* path = "donnees.txt";
	int** m;
	m = creer_matrice(path);
	int **a,**b, **best1, **best2;
	int i, j, iter=0, f_cur, f_best;
	a = (int *)calloc(N, sizeof(int*));
	b = (int *)calloc(N, sizeof(int*));
	best1 = (int *)calloc(N, sizeof(int*));
	best2 = (int *)calloc(N, sizeof(int*));
	for(i = 0; i<N; i++){
		a[i] = (int *)calloc(N , sizeof(int));
		b[i] = (int *)calloc(N , sizeof(int));
		best1[i] = (int *)calloc(N , sizeof(int));
		best2[i] = (int *)calloc(N , sizeof(int));
	}//on initialise l'algorithme en posant 2 solutions initiales qui correspondent
	// aux sommets 1 et 2 et 3 et 4 pour le premier sous-ensemble
	//et 5 et 6 et 7 et 8 pour le deuxième sous-ensemble
	for(i=0; i<N; i++){
		for(j=0;j<N;j++){
			if(i<N/2)
				a[i][j]=m[i][j];
			else
				a[i][j]=0;
		}
	}
	for(i=0; i<N; i++){
		for(j=0;j<N;j++){
			if(i<N/2)
				b[i][j]=0;
			else
				b[i][j]=m[i][j];
		}
	}
	list_tabou[0]= "0123+4567";
	printf("Nombre de sommets: %d\n", N);
	f_best = f(a,b);
	printf("Solution initiale : %d\n", f_best);
	best1=a;
	best2=b;
	int k=0;
	while(iter<MAX_ITR){//la boucle de la méthode tabou, 
	//le critère d'arrêt est dépasser le nombre max d'itération MAX_ITR
		bool cond;//condition booléenne qu'on va utiliser après
		iter++;
		k++;
		char l_cur[20];
		int h=0, p;
		//voisinage de la solution, on teste d'abord pour trouver
		//les sommets qui ne sont pas dans le premier sous-ensemble
		//en utlisant le booléen cond, et quand on trouve le premier sommet
		//non inclu on l'inclu dans ce sous-ensemble et on le retire de l'autre,
		//et on fait le même dans l'autre sous-ensemble donc la condition AUB=V 
		//est toujours réalisé
		for(i=0; i<N; i++){
			cond=true;
			for(j=0;j<N;j++){
				if(a[i][j]!=0){
					cond=false;
					break;
				}
			}
			if(cond==true){
				for(j=0;j<N;j++){
					a[i][j]=b[i][j];
					b[i][j]=0;
					l_cur[h++]=i;//on remplit une chaine de caractère de la
					//même forme que les chaines de la liste tabou sont remplis
					//pour tester si ce voisin existe déjà dans la liste tabou
				}
				break;
			}
		}
		l_cur[h++]='+';
		for(i=0; i<N; i++){
			cond=true;
			for(j=0;j<N;j++){
				if(b[i][j]!=0){
					cond=false;
					break;
				}
			}
			if(cond==true){
				for(j=0;j<N;j++){
					b[i][j]=a[i][j];
					a[i][j]=0;
					l_cur[h++]=i;
				}
				break;
			}
		}
		for(p=0;p<k;p++){//teste si le voisin existe dans la liste tabou
			cond=true;
			if(strcmp(l_cur,list_tabou[p])==0){
				cond=false;
				break;
			}
		}
		if(cond==true){//si il n'existe pas on l'ajoute à la liste et
		// on prend la valeur de sa fonction objective pour l'évaluer
			f_cur=f(a, b);
			list_tabou[k++]=l_cur;
		}
		if(k==20){//si la liste tabou est saturée, on supprimer 
		//l'élément le plus ancien
			for(p=0;p<k-1;p++){
				list_tabou[p]=list_tabou[p+1];
			}
		}
		if(f_cur<f_best){//le critere d'aspiration est le meilleur
		//régional, c'est à dire on prend la solution si elle est
		//la meilleure dans le voisinage courant
			f_best=f_cur;
			best1=a;
			best2=b;
		}
		/*for(i=0; i<N; i++){
			for(j=0;j<N;j++){
				printf("%d--%d-", a[i][j], b[i][j]);
			}
			printf("\n");
		}*/
	}
	printf("La solution optimale est le partitionnement avec les 2 sous-ensembles :\n");
	for(i=0; i<N; i++){
			for(j=0;j<N;j++){
				printf("%d ", a[i][j]);
			}
			printf("\n");
		}
		printf("-----\n");
		for(i=0; i<N; i++){
			for(j=0;j<N;j++){
				printf("%d ", b[i][j]);
			}
			printf("\n");
		}
	printf("La somme des poids : %d", f_best);//on sort de la
	//boucle après le critère d'arrêt et on affiche la solution optimale
}
