#include "stdafx.h"
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <direct.h> // pour _getcwd
#include <io.h> // _finddata_t, _findfirst, _findnext et _findclose

/**
 Fonction servant à calculer le nombre de lignes minimun présent dans un ensemble de fichiers .txt
**/

using namespace std;

int CompterLigneFichier(const string & adresse){
    ifstream fichier(adresse, ios::in); // Ouverture du fichier

	if (fichier.fail()) {
		cout << "Impossible d'ouvrir le fichier !" << endl;
		return 0;
	}

    // Initialisation du compteur :
	int compt=0;

	while(!fichier.eof()) {
	    string ligne;
		getline(fichier, ligne);
		compt++; // A chaque ligne on incremente le compteur
	}
	return compt;
}

int main(int argc, char** argv) {

	struct _finddata_t c_fichier;
		intptr_t hFichier;

		hFichier = _findfirst( "*.*" ,&c_fichier );

		int min=9999999999;

		// On parcours tout les fichiers du dossier :
		do{
			string word;
			string ext;
			stringstream stream(c_fichier.name);
			getline(stream, word, '.'); //split string
			getline(stream, ext, '.'); //split string

			if(ext=="txt"){
                // Si il s'agit d'un fichier texte on calcule le nombre de lignes et on le compare au minimum

				if (c_fichier.size!=0){
					int test = CompterLigneFichier(c_fichier.name);
					//cout<<test<<endl;
					if(test<min){min=test;};
				}

			}

		}while( _findnext( hFichier, &c_fichier ) == 0 );

cout <<"Le min est : " << min << endl;

cin.get();

return 0;
}
