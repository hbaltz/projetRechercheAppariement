#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include<iostream>
#include <sstream>
#include<direct.h> // pour _getcwd
#include<io.h> // _finddata_t, _findfirst, _findnext et _findclose
/**
    Fonction qui se sert des fonctions de semi-automatisation pour calculer les scores de ressemblance pour un ensemble d'images
**/

using namespace std;

int main(int argc, char** argv) {
	if (argv[1] != NULL && argv[2] != NULL){

		struct _finddata_t c_fichier;
		intptr_t hFichier;

		hFichier = _findfirst( "*.*" ,&c_fichier );

         // Chemin ou situe vos exes :
		char chem[100] = "D:\\exes\\fAuto_ann_dist.exe ";
		char chem2[100] = "D:\\exes\\fAutoScore.exe ";

		// Definition des differents arguments que vos exes prennent en entree :
		string epsilon = argv[1];
		string lim = argv[2];

		do {if (c_fichier.size!=0){
				cout<<c_fichier.name<<endl;

				bool calcul = false;
				int compt=0;

				string word;
				string ext;
				string nom;
				stringstream stream(c_fichier.name);
				getline(stream, word, '.'); //split string
				getline(stream, ext, '.'); //split string

				if(ext=="key"){
                    // Si le fichier est un fichier de point d'interet on le prend comme reference pour le calcul de distance avec l'ensmble des autres images
					string result = chem + word + ".key";

					char* cres;
					cres = (char*)result.c_str();

					cout<< result <<endl;

					system(cres);

					calcul = true; // Permet de savoir quand le calcul est termine pour lancer le alcul de score

					nom=word;
				}

				if(calcul){
                    // Si le calcul de distance entre point d'interet est fini on parcours les fichiers a la recherhce des points .txt

					struct _finddata_t c_fichier2;
					intptr_t hFichier2;

					hFichier2 = _findfirst( "*.*" ,&c_fichier2 );
					do {if (c_fichier2.size!=0){
							cout<<c_fichier2.name<<endl;

							string word2;
							string ext2;
							stringstream stream(c_fichier2.name);
							getline(stream, word2, '.'); //split string
							getline(stream, ext2, '.'); //split string

							if(ext2=="txt"){
                                //Si il s'agit d'un fichier .txt on lui applique la fonction de calcul de score de resseblnce
								string vd = "";
								string result2 = chem2 + vd +  epsilon + " " + lim + " " + nom;

								char* cres2;
								cres2 = (char*)result2.c_str();

								cout<<"--->" <<result2 <<endl;

								system(cres2);

								compt+=1; // Pour eviter de faire le calcul deux fois
							}
						}
					}while( _findnext( hFichier2, &c_fichier2 ) == 0 && compt<1 );

					calcul = false;
					compt = 0;
				}

			}

		}while( _findnext( hFichier, &c_fichier ) == 0 );
	}
	cout << "Le traitement est fini :)"<<endl;
	cin.get();

	return 0;
}
