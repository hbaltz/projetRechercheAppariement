#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <numeric>
#include <iterator>
/**
 Fonction de score a appliquer a un fichier .txt  consitue des couples de point apparies et de leur score : x1 y1 x2 y2 score (le score doit etre en cinquieme colonne)
**/
using namespace std;

// Definition de la classe Point2D
class Point2D{
public:
	float X;
	float Y;
};

// Definition de la classe Point2DDistance
class Point2DDistance : public Point2D{
public:
	double distance;
};

// Definition de la classe AppariementPointDistance
class AppariementPointDistance{
public :
	Point2D ptrequete;
	std::vector<Point2DDistance> ptsppv;
};

// Fonction qui va recuperer les informations utiles dans le fichier .txt
bool LectureFichier(const string & adresse, vector<double> & distances){

    // Ouverture du fichier
    ifstream fichier(adresse, ios::in);

	if (fichier.fail()) {
		cout << "Impossible d'ouvrir le fichier !" << endl;
		return false;
	}

	std::vector<AppariementPointDistance> appariements;

    // Recuperation des scores :
	while(!fichier.eof()) {
	    string ligne;
		getline(fichier, ligne);
		if(ligne.empty()){continue;}

		std::istringstream iss(ligne.c_str());
		std::vector<std::string> contenuligne;
		while(!iss.eof()){
			std::string stmp;
			iss>>stmp;
			if(stmp.empty()){continue;}
			contenuligne.push_back(stmp);
		}

		AppariementPointDistance apptmp;
		apptmp.ptrequete.X=atof(contenuligne[0].c_str());
		apptmp.ptrequete.Y=atof(contenuligne[1].c_str());

		for(size_t n=2;n<contenuligne.size();n=n+3){
			Point2DDistance pttmp;
			pttmp.X=atof(contenuligne[n].c_str());
			pttmp.Y=atof(contenuligne[n+1].c_str());
			pttmp.distance=atof(contenuligne[n+2].c_str());
			//cout<<atof(contenuligne[n+2].c_str())<<endl;
			apptmp.ptsppv.push_back(pttmp);
		}

		appariements.push_back(apptmp);
	}

	for(size_t n=0;n<appariements.size();n++){
		for(size_t j=0;j<appariements[n].ptsppv.size();j++){
			distances.push_back(appariements[n].ptsppv[j].distance);
		}
	}
	return true;

}

// Implementation d'une fonction de score de type smoyenne cartesienne
double fonction_de_vote(const float epsilon, const vector<double> & distances, double & valmax, double & valmin,int lim){
	vector<double> vecteur_somme;
	double score=0;
	int i=0;
	for(size_t n=0;n<distances.size();n++){
		if (distances[n] <= epsilon && i<=lim){
			double scoretmp=1.0-((distances[n])/epsilon);
			vecteur_somme.push_back(scoretmp);
			score=score+scoretmp;
			i=i+1;
		}
	}

	score = score/vecteur_somme.size();

	std::vector<double>::const_iterator imax=std::max_element(distances.begin(),distances.end());
	valmax=(*imax);

	std::vector<double>::const_iterator imin=std::min_element(distances.begin(),distances.end());
	valmin=(*imin);

	return score;
}

int main(int argc, char** argv) {
	if(argv[1]!= NULL && argv[2] != NULL && argv[3]!= NULL && argv[4]!=NULL){
		string adresse = argv[1];
		string sortie = argv[4];

		string word;
		stringstream stream(adresse);
		getline(stream, word, '.'); //split string

		string ch = "D:\\results_vote\\" + word + "_log.txt"; // chemin pour ecriture des logs

		vector<double> distances;
		if(!LectureFichier(adresse,distances)){return 0;}
		std::sort(distances.begin(), distances.end());

		float epsilon;
		epsilon = strtod(argv[2], NULL);

		double score;
		double valmax;
		double valmin;
		int limite=	strtod(argv[3],NULL);

		// Affichage des resultats

		score = fonction_de_vote(epsilon, distances, valmax, valmin,limite);
		cout << "Le score de la fonction de vote est : " << score << endl;
		cout << "Valeur min : " << valmin << endl;
		cout << "Valeur max : " << valmax << endl;

		// Ecriture des resultats dans des fichiers .txt :

		ofstream fichier("D:/log_res_"+ sortie +".txt", ios::out | ios::app);  // ouverture en écriture avec effacement du fichier ouvert
        if(fichier){

				fichier << "----------------------------------------------------------------------------------------" << endl;
				fichier << " " << endl;
				fichier << adresse << endl;
				fichier << " " << endl;
				fichier << "Seuil : " << epsilon << endl;
				fichier << "Limite de points : " << limite << endl;
                fichier << "Le score de la fonction de vote est : " << score << endl;
                fichier << "Valeur min : " << valmin << endl;
				fichier << "Valeur max : " << valmax << endl;
				fichier << " " << endl;

                fichier.close();
        }

		ofstream fichier2(ch, ios::out | ios::app);  // ouverture en écriture avec effacement du fichier ouvert
        if(fichier2){

				fichier2 << "----------------------------------------------------------------------------------------" << endl;
				fichier2 << " " << endl;
				fichier2 << adresse << endl;
				fichier2 << " " << endl;
				fichier2 << "Seuil : " << epsilon << endl;
				fichier2 << "Limite de points : " << limite << endl;
                fichier2 << "Le score de la fonction de vote est : " << score << endl;
                fichier2 << "Valeur min : " << valmin << endl;
				fichier2 << "Valeur max : " << valmax << endl;
				fichier2 << " " << endl;

                fichier2.close();
        }

		ofstream fichier3("D:/log_res_lite_"+ sortie +".txt", ios::out | ios::app);  // ouverture en écriture avec effacement du fichier ouvert
        if(fichier3){

				fichier3 << adresse << " " << score <<endl;
                fichier3.close();
        }

	}else{
		cout << "Veillez mettre les arguments dans l'ordre suivant : \n appli.exe \"Chemin du fichier texte\" Seuil Nbre_pt_limite"<<endl;
	}

    return 0;
}
