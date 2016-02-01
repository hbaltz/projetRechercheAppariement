#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <direct.h> // pour _getcwd
#include <io.h> // _finddata_t, _findfirst, _findnext et _findclose
#include <algorithm>    // std::sort
/**
    Fonction de mises en forme qui parcours les resultat pour creer une page html permettant de voir l'ensemble des images avec les n plus proches photos qui lui sont apparie
    Prend en entree n : le nombre de plus proches photos qui seront affiche
**/
using namespace std;

vector<pair<string,double>> TrouverMax(const string & adresse){
    ifstream fichier(adresse, ios::in);

	double max=0;
	string res;

    // Preparation de vecteur de cuple de double pour pouvoir trier les resultats
	pair<string ,double> resV;
	vector<pair<string ,double>> resL;


	while(!fichier.eof()) {

		double score;
        string chaine1;

        fichier >>  chaine1 >> score;
	    string ligne;

		resV = make_pair(chaine1, score);
		resL.push_back(resV);


	}
	return resL;
}

// Permet de trier les resultats
bool pairCompare(const std::pair<string, double>& firstElem, const std::pair<string, double>& secondElem) {
  return firstElem.second > secondElem.second;
}

int main(int argc, char** argv) {
    // Si n n'est pas renseinge on affiche uniquement le plus proche voisin
	int n=1;

	if (argv[1] != NULL){
		n=strtod(argv[1],NULL);
	}

	//Ecriture du fichier html en parrelele d'un fichier .txt exploitable

	ofstream fichier("D:/test.html", ios::out | ios::app);  // ouverture en écriture avec effacement du fichier ouvert
	ofstream fichier2("D:/test.txt", ios::out | ios::app);  // ouverture en écriture avec effacement du fichier ouvert

	fichier << "<!doctype html>" <<endl;
	fichier << "<html lang=\"fr\">" <<endl;
	fichier << "<head>" <<endl;
	fichier << "<meta charset=\"latin\">"<<endl;
	fichier << "<title>Resultat fonction de score</title>" <<endl;
	//fichier << "<link rel=\"stylesheet\" href=\"style.css\">" <<endl;

	fichier << "</head>" <<endl;
	fichier << "<body>" <<endl;

	vector<pair<string,double>> res;

	struct _finddata_t c_fichier;
	intptr_t hFichier;

	hFichier = _findfirst( "*.*" ,&c_fichier );

	do {if (c_fichier.size!=0){
		cout<<c_fichier.name<<endl;

		string word;
		string ext;
		stringstream stream(c_fichier.name);
		getline(stream, word, '.'); //split string
		getline(stream, ext, '.'); //split string

		string part4,part5,part6,imgRef;

		stringstream stream3(word);
		getline(stream3, part4, '_');
		getline(stream3, part4, '_');
		getline(stream3, part4, '_');
		getline(stream3, part4, '_');

		imgRef = part4;

		while(getline(stream3, part4, '_')){
			stringstream stream4(part4);
			getline(stream4, part4, '.');

			imgRef = imgRef + "_" + part4;

		}

		string chImRe="file:///D:/src/"+imgRef+".jpg";



		if(ext=="txt" ){

			res = TrouverMax(c_fichier.name);
			sort(res.begin(), res.end(), pairCompare);
			cout << "ok !"<<endl;



			fichier <<"<p>"<<"Reference : " << imgRef <<"</p>" <<endl;
			fichier << "<p> <img src="+chImRe+" width=\"800\">" << endl;

			cout << n << endl;

			for (int i = 0; i < n; i++)
			{
				string imgAp;

				stringstream stream2(res[i+1].first);
				getline(stream2, imgAp, '.');

				string chImAp="file:///D:/src/"+imgAp+".jpg";

				//cout << chImAp <<endl;

				fichier << "<p> N°" << i+1 << " Score : " << res[i+1].second <<endl;
				fichier << "<img src="+chImAp+" width=\"200\"> </p>"<<endl;

				fichier2 << imgRef << " " << imgAp << " " << res[i+1].second << endl;
			}

		}
	}
	}while( _findnext( hFichier, &c_fichier ) == 0 );

	fichier << "</body>" <<endl;
	fichier << "</html>" <<endl;



	fichier.close();
	fichier2.close();
	cin.get();


	return 0;
}
