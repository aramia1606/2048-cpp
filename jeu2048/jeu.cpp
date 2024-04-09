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
    int res = -1; return res; 
}

int proportion(const Grille &g) { return g.prop2; }

int cible(const Grille &g)  { return g.cible; }

int dimension(const Grille &g)  { return g.table.size(); }

int score(const Grille &g)  { return g.score; }

bool succes(const Grille &g) { 
    if (score(g) >= cible(g)){ return true; }
    else{return false;}
}

bool init(Grille &g, int dimension, int cible, int proportion) {
    if(dimension <=0 or // Vérifcation diomension positif stric
        cible<=0 or // Vérifcation cible positif 
       (proportion <0 and proportion > 10) // la proportion de 2 est entre 0 et 10 
      ){return false;}
    else{
        vector<int> ligne; // Initialise une ligne 
        ligne =vector<int> (dimension); 
        vector<vector<int>> colonne;  // Initialise une colonne
        for (int i= 0; i< dimension ; i++){
            colonne.push_back(ligne);
        }
        g.prop2 = proportion; //Initialise la proportion de 2 
        g.prop4 = 10 - proportion; // Initialise la proportion de 4
        
        int i = place(g); 
        int j = place(g); 
        colonne.at(i).at(j) = nouvelle(g); // Initialise une case avec 2 ou 4
        int a = place(g); 
        int b = place(g); 
        colonne.at(a).at(b) = nouvelle(g);// Initialise une case avec 2 ou 4
        g.table = colonne;
        return true; 
    }
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
@param a passage par réference du nombre de cases vides après un slide*/
vector<int> slide(vector<int> v, int &a){
    int n = 0; // nombres de cases déplacées 
    for (int i = 0 ; i<v.size() ; i++){
        if(v.at(i) != 0){
            v.at(n+1) = v.at(i); //Déplacement de la case à coté de la dernière déplacée
            v.at(i) = 0;
            if (n>0 and not fusion( v.at(n-1)  ,  v.at(n) ){
                n=n+1;
            }
        }
   }
    a=v.size() -n; // nombre de case vides restantes
    return v;

}
    
    
int droite(Grille &g)  {
    int nb;
    for(int i =0; i<dimension(g) ; i++){
        vector<int> ligne;
        for(int j =0; j<dimension(g) ; j++){
            ligne.at(j).push_back(g.table.at(j).at(dimension(g)-i))
            
        }
        int a=0;
        ligne = g.table.at(i);
        g.table.at(i) = slide(ligne , a);
        nb=nb+a;
    }
}

int gauche(Grille &g)  { 
    int nb; // Nombre de case vides dans la grille 
    for(int i =0; i<dimension(g) ; i++){
        int a; // Nombre de case vide dans une ligne 
        vector<int> ligne = g.table.at(i);
        g.table.at(i) = slide(ligne , a);
        nb=nb+a;
    }
    return nb;
}
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
  /* Verifier si on veut que la ligne du haut soit 0 ou max-1 */
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
