#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include<iostream>
#include <sstream>
#include <fstream>
#include<direct.h> // pour _getcwd
#include<io.h> // _finddata_t, _findfirst, _findnext et _findclose
/**
    Fonction qui applique le calcul du score de ressamblance entre deux images a un esnemble de fichier de points apparies
    Prend en entrée un seuil, le nombre de point a garder et la sortie
**/

using namespace std;

int main(int argc, char** argv) {
	if(argv[1]!= NULL && argv[2]!=NULL && argv[3]!=NULL){
        struct _finddata_t c_fichier;
        intptr_t hFichier;

        hFichier = _findfirst( "*.*" ,&c_fichier );

        // Chemin ou situe votre exe de calcul de score :
        char chem[100] = "D:\\exes\\fVote.exe ";

        // Definition des differents arguments que fVote en entree :
        string epsilon = argv[1];
        string min = argv[2];
        string sortie = argv[3];

        do {if (c_fichier.size!=0)
            cout<<c_fichier.name<<endl;

            string word;
            string ext;
            stringstream stream(c_fichier.name);
            getline(stream, word, '.'); //split string
            getline(stream, ext, '.'); //split string

            if(ext=="txt"){
                string result = chem + word + ".txt " + epsilon + " " + min + " " + sortie;

                char* cres;
                cres = (char*)result.c_str();

                cout<< result <<endl;

                system(cres);
            }

       }while( _findnext( hFichier, &c_fichier ) == 0 );

	}else{
		cout << "Veillez mettre les arguments dans l'ordre suivant : \n appli.exe Seuil Lim_pt NomSortie"<<endl;
	}

    return 0;
}

