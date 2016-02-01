#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include<iostream>
#include <sstream>
#include<direct.h> // pour _getcwd
#include<io.h> // _finddata_t, _findfirst, _findnext et _findclose
/**
    Fonction qui applique le calcul de distance entre vecteur de descritpion SIFT a un esnemble de fichier de point d'interet prend en entrée le fichier de reference et un seuil
**/

using namespace std;

int main(int argc, char** argv) {
	if(argv[1]!= NULL && argv[2]!= NULL){

		cout << "calcul de distance ? o/n" <<endl;
		string choix;
		cin >> choix;

        struct _finddata_t c_fichier;
        intptr_t hFichier;

        hFichier = _findfirst( "*.*" ,&c_fichier );

        // Chemin ou situe votre exe de calcul de distance :
        char chem[100] = "D:\\ProjetRecherche\\appariementImg\\exes\\ann_ppv_multiple_export_distances.exe ";

        // Definition des differents arguments que ann_ppv prend en entree :
        char req[100] = " --kprequete ";
        char ref[100] = " --kpreference ";
        char result[100] = " --result ";
        char exp_dist[100] = " --export_distances";
        char seuil[100] = " --seuil ";

		string adr_ref = argv[1];
		string sl = argv[2];

		string unit;
		string dec;
		stringstream stream(sl);
		getline(stream, unit, '.'); //split string
		getline(stream, dec, '.'); //split string

	   do {if (c_fichier.size!=0){
			cout<<c_fichier.name<<endl;

			string word;
			string ext;
			stringstream stream(c_fichier.name);
			getline(stream, word, '.'); //split string
			getline(stream, ext, '.'); //split string

			if((ext=="key" || ext=="sift")&& choix == "o"){
				string ch = "D:\\results_ann_ppv_seuil\\" + word + "_" + unit + "_" + dec + ".txt"; // chemin pour ecriture des logs

				string s = "";

				string result2 = chem + s + req + word + "." + ext + ref + adr_ref + result + ch + exp_dist + seuil + sl;

				char* cres;
				cres = (char*)result2.c_str();

				cout<< result2 <<endl;

				system(cres);
			}

			else{
				string ch = "D:\\results_ann_ppv_seuil\\" + word + "_" + unit + "_" + dec + ".txt"; // chemin pour ecriture des logs

				string s = "";

				string result2 = chem + s + req + word + "." + ext + ref + adr_ref + result + ch + seuil + sl;

				char* cres;
				cres = (char*)result2.c_str();

				cout<< result2 <<endl;

				system(cres);
			}}

	   }while( _findnext( hFichier, &c_fichier ) == 0 );

	 cout << "Le traitement est fini :)"<<endl;
	 cin.get();


	}else{
		cout << "Veillez mettre les arguments dans l'ordre suivant : \n appli.exe Seuil"<<endl;
	}

    return 0;
}

