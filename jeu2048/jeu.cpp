#include "jeu.h"
#include <iomanip> // pour setw dans affichage.


/* Structure de position
typedef struct{
    int x; 
    int y;
    int val;
} Case; */

/* Les definitions actuelles des fonctions servent uniquement à ce que le
 * compilateur ne râle pas. Il faut bien sur écrire le code de ces fonctions
 */

int vides(const Grille &g) {
    int res = 0;
    for(int i= 0 ; i < dimension(g); i++){
        for (int j = 0 ; j < dimension(g) ; j++){
            if( g.table.at(i).at(j) == 0 ){
                res = res +1;
            }
        }
    }
    return res; 
}

int proportion(const Grille &g) { return g.prop2; }

int cible(const Grille &g)  { return g.cible; }

int dimension(const Grille &g)  { return g.table.size(); }

int score(const Grille &g)  { return g.score; }

bool succes(const Grille &g) { 
    if (score(g) >= cible(g)){ return true; }
    else{return false;}
}

/*Fonction permet de placer une case en fonction de son indice (en partant de 1 puis de droite à gauche de haut en bas) 

@Grille g dans laquelle il faut placer la case 
@int n l'indice de la case
@int val la veleur à mettre dans la case
*/
bool chargerCase(Grille &g , int n , int val){
    int i=0, j=0, dim= dimension(g);
    vector<vector<int>> v = g.table;
    while(n>1){
        if(v.at(i).at(j)==0){n=n-1;}
        j=j+1;
        if(j>=dim){
            i=i+1;
            j=0;
        }  
    }
    g.table.at(i).at(j-1) =val;
}
bool init(Grille &g, int dimension, int cible, int proportion) {
    if(dimension <=0 or // Vérifcation dimension positif stric
        cible<=0 or // Vérifcation cible positif stric
       proportion <0 or proportion > 10 // la proportion de 2 est entre 0 et 10
      ){ ;return false;}
    else{
        g.cible = cible; 
        g.score = 0;
        vector<int> ligne; // Initialise une ligne 
        ligne =vector<int> (dimension); 
        for(int i = 0; i< dimension ; i++){ligne.at(i) = 0 ;}//Rempli la ligne avec des 0
        vector<vector<int>> colonne;  // Initialise une colonne
        for (int i= 0; i< dimension ; i++){
            colonne.push_back(ligne);
        }
        g.table = colonne;
        g.prop2 = proportion; //Initialise la proportion de 2 
        g.prop4 = 10 - proportion; // Initialise la proportion de 4
        chargerCase(g, place(g) , nouvelle(g));
        chargerCase(g, place(g) , nouvelle(g));
    }
    return true; 
}


// Ne pas oublier de vérifier la validité des paramètres !
bool charge(Grille &g, vector<vector<int>> &v, int cible, int proportion) {
  size_t dim = v.size(); bool res = false;
  if (dim < 4) {
    cerr << "Nombre de lignes insuffisant: " << v.size() << endl;
    return res;
  }
    else if(cible<=0){ cerr << "Nombre cible incorrect (négatif)"; return res; }
    else if(proportion <0 and proportion > 10){ cerr << "Proportion incorrecte il doit être entre 0 et 10"; return res;} 
    else{
        g.score = 0;
        for(int i =0; i<dim; i++){
            for (int j = 0; j< v.at(i).size(); j++){
                g.table.at(i).at(j) = v.at(i).at(j);
            }
        }
    }
  // a faire
  return res;
}
    
/*fusion : Renvoie true si la fusion et possible ET si la position de fin est correcte
@param  en initialisant la grille `a partir du vecteur v : chacune de ses
lignes donne les valeurs des tuiles, de gauche `a droite (la valeur 0 d´esigne une case vide).
Le score de la grille est initialis´e `a 0 quel que soit le contenu de v.
Cette fonction permet de placer la grille dans une configuration d´efinie `a l’avance.case1 contenant sa position , sa valeur
@param case2 contenant sa position , sa valeur
@param fin la case à changer avec la valeur fusionné des deux cases si cela est possible

*/
bool fusion(int case1, int case2){ 
    if(case1 == case2 and case1!=0 and case2 !=0){
        case1 = 0;
        case2 = case2*case2;
        return true;
    }
    else{return false;}
}

/*slide : renvoie un vecteur ou toutes les cases sont slidés et fusionnés (si cela est possible) vers l'indice 0
@param v est un vecteur d'entier provenant de la grille
*/
vector<int> slide(vector<int> v){
    
        cout <<"repère" ;
    int nbDernier=0;
    size_t indice =0; 
    for(size_t i =0 ; i<v.size(); i++){
        if(v.at(i) != 0){
            indice = indice +1;
            if(v.at(i) == v.at(indice-1)){
                v.at(indice-1)= v.at(i)*v.at(i);
                v.at(i) = 0;
            }
            else{
                v.at(indice-1) = nbDernier;
                v.at(i) = 0;
            }
        }
    } 
}


    
int droite(Grille &g)  { int res = -1; return res; }

int gauche(Grille &g) { int res = -1; return res; }
    
    
/* en initialisant la grille `a partir du vecteur v : chacune de ses
lignes donne les valeurs des tuiles, de gauche `a droite (la valeur 0 d´esigne une case vide).
Le score de la grille est initialis´e `a 0 quel que soit le contenu de v.
Cette fonction permet de placer la grille dans une configuration d´efinie `a l’avance.*/
int haut(Grille &g)    { int res = -1; return res; }

int bas(Grille &g)     { int res = -1; return res; }


/*		 Pour les extensions éventuelles */
void sauve(const Grille &g, string filename) {

}


void restaure(Grille &g, string filename) {

}


/*
 * 		Fonctions mise à disposition. Pas de raison d'y toucher !
 *	Rappel: la fonction main() est dans le fichier test.cpp
 */	

void affiche (const Grille &g) {
  int i, j, k; /*en initialisant la grille `a partir du vecteur v : chacune de ses
lignes donne les valeurs des tuiles, de gauche `a droite (la valeur 0 d´esigne une case vide).
Le score de la grille est initialis´e `a 0 quel que soit le contenu de v.
Cette fonction permet de placer la grille dans une configuration d´efinie `a l’avance.*/
  int max = dimension(g);
  cout << endl << " \t ";
  for(k = 0; k < (6+1)*max-1; k = k+1) { cout << "-"; }
  cout << endl;
  /* Verifier si on veut que la ligne du haut soit 0 ou max-1  */
  for(i = 0; i < max; i = i+1) {
    cout << "\t|";
    for(j=0; j < max; j=j+1) {
      if(g.table.at(i).at(j) == 0) {
	cout << "      |";
      } else { cout << " " << setw(4) << g.table.at(i).at(j) << " |" ; }
    }
    if (i != max-1) {
      cout << endl << "\t|";
      for(k = 0; k < (6+1)*max-1; k = k+1) { cout << "-"; }
      cout << "|" << endl;
    } else {
      cout << endl << "\t ";
      for(k = 0; k < (6+1)*max-1; k = k+1) { cout << "-"; }
      cout << endl;
    }
  }
  cout << endl << "Score: " << score(g) << ", Vides: " << vides(g) << endl;
}
