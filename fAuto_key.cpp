#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include<iostream>
#include <sstream>
#include<direct.h> // pour _getcwd
#include<io.h> // _finddata_t, _findfirst, _findnext et _findclose
/**
 Fonction qui applique a un exemple de photo un exe de detection de point d'interet (ex detecteur sift)
**/
using namespace std;

int main() {

    // répertoire courant
    char* repCour = _getcwd( NULL, 0 );

    // Parcours des fichiers dans le répertoire courant
    struct _finddata_t c_fichier;
    intptr_t hFichier;

    hFichier = _findfirst( "*.*" ,&c_fichier );

    // Chemin ou se situe votre detecteur de point d'interet
    char chem[100] = "D:\\exes\\siftpp_tgi.exe ";
    char out[100] = " -o ";

    do {if (c_fichier.size!=0)
        cout<<c_fichier.name<<endl;

        string word;
        string ext;
        stringstream stream(c_fichier.name);
        getline(stream, word, '.'); //split string
        getline(stream, ext, '.'); //split string

        if(ext=="tif"){
            // Ne s'applique que fichier .tif

            string ch = "D:\\results_key\\" + word + ".key"; // chemin pour ecriture des resultat .key

            string result2 = chem + word + ".tif" + out + ch;

            char* cres;
            cres = (char*)result2.c_str();

            cout<< result2 <<endl;

            system(cres);
        }

    }while( _findnext( hFichier, &c_fichier ) == 0 );

 cout << "Le traitement est fini :)"<<endl;
 cin.get();
 return 0;
}




