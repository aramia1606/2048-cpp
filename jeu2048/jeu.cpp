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

bool equalString(string s1, string s2){
    if(s1.size() != s2.size()){return false;}
    for(int i =0 ; i<s1.size() ; i++){
        if(s1.at(i) != s2.at(i)){return false;}
    }
    return true;
}

/*Fonction permet de placer une case en fonction de son indice (en partant de 1 puis de droite à gauche de haut en bas) 

@Grille g dans laquelle il faut placer la case 
@int n l'indice de la case
@int val la veleur à mettre dans la case
*/
bool chargerCase(Grille &g , int n , int val){
    if(vides(g)==0){
        return false;
    }
    if(val%2==0){
    size_t i=0, j=0, dim= dimension(g);
    vector<vector<int>> v = g.table;
        do{
        i=(rand()%dim); //on tire aléatoirement i et j, on a donc une case aléatoire. Si cette case est vide, on la remplit, sinon on retire.
        j=(rand()%dim);
        }while(v.at(i).at(j)!=0);
        g.table.at(i).at(j) =val;
    }
    return true;
}

bool init(Grille &g, int dimension, int cible, int proportion) {
    if(dimension <=0 or // Vérifcation dimension positif strict
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
        g.cible = cible; 
        g.score = 0;
        vector<vector<int>> colonne;  // Initialise une colonne
        for (int i= 0; i< dim ; i++){
            colonne.push_back(v.at(i));
        }
        g.table = colonne;
        g.prop2 = proportion; //Initialise la proportion de 2 
        g.prop4 = 10 - proportion; // Initialise la proportion de 4
    return true; 
        }
  
  // a faire
  return res;
}


void afficheVector(vector<int> v, string s){
    for(size_t i =0 ; i<v.size(); i++){cout << v.at(i)<<" ";}cout<<s<<endl;
}

/*slide : renvoie un vecteur ou toutes les cases sont slidés et fusionnés (si cela est possible) vers l'indice 0 (vers la gauche)
@param v est un vecteur d'entier provenant de la grille
*/
vector<int> slide(Grille &g, vector<int> v){
    size_t indice =0;
    //cout<<"slide0";
    for(size_t i =1 ; i<v.size(); i++){
        //cout<<"slide1";
        if(v.at(i) != 0){
            if(v.at(indice) ==0){
                v.at(indice)=v.at(i);
                v.at(i) =  0;
                //cout<<"slide2";
            }
            else if(v.at(i) == v.at(indice) ){
                //cout<<"slide3";
                v.at(indice)=v.at(i)+v.at(i);
                g.score= g.score + v.at(indice);
                v.at(i)=0;
                indice = indice+1;
                //cout<<"slide4";
            }
            else{
                indice = indice +1;
                v.at(indice)=v.at(i);
                //cout<<"slide5";
                if (indice != i) {
                     v.at(i)= 0;
                }
            }
        }
    }
}

vector<int> inverse(vector<int> v){
    vector<int> inverse;
    for(int i=v.size()-1 ; i>=0; i--){
        inverse.push_back(v.at(i));
    }
    return inverse;
}
/*isSameGrille renvoie true si deux grilles sont identiques, false dans le cas contraire
@g1 est la première grille 
@g2 est la seconde
*/
bool isSameGrille(Grille g1, Grille g2){ 
    int size=g1.table.size();
    vector<vector<int>> table1=g1.table, table2=g2.table;
    if(g1.table.size()!= g2.table.size()){return false;}
    for(int i=0; i<size ; i++){
        for(int j=0; j<size ; j++){
            if(table1.at(i).at(j) !=table2.at(i).at(j)){return false;}
        }
    }
    return true;
}
    
int droite(Grille &g)  {
    Grille instanceg=g;
    for(int i=0; i<dimension(g); i++){
        g.table.at(i)=inverse(slide(g, inverse(g.table.at(i))));
    }
    if(isSameGrille(instanceg, g)){return -1;}   
    return vides(g); 
}

int gauche(Grille &g) {
    Grille instanceg=g;
    for(int i=0; i<dimension(g); i++){
        g.table.at(i)=slide(g, g.table.at(i));
    }
    if(isSameGrille(instanceg, g)){return -1;}  
    return vides(g); 
} 


    
    
/* en initialisant la grille `a partir du vecteur v : chacune de ses
lignes donne les valeurs des tuiles, de gauche `a droite (la valeur 0 d´esigne une case vide).
Le score de la grille est initialis´e `a 0 quel que soit le contenu de v.
Cette fonction permet de placer la grille dans une configuration d´efinie `a l’avance.*/
int haut(Grille &g)    { 
    Grille instanceg=g;
    for(int i=0; i<dimension(g); i++){
        vector<int> colonne;
        for(int j=0; j<dimension(g); j++){
            colonne.push_back(g.table.at(j).at(i));
        }
        vector<int> slidedColonne= slide(g, colonne);
        for(int k=0; k<dimension(g); k++){
            g.table.at(k).at(i)=slidedColonne.at(k);
        }
    }
    if(isSameGrille(instanceg, g)){return -1;}   
    return vides(g);  
}

int bas(Grille &g)     { 
    Grille instanceg=g;
    for(int i=0; i<dimension(g); i++){
        vector<int> colonne;
        for(int j=0; j<dimension(g); j++){
            colonne.push_back(g.table.at(j).at(i));
        }
        vector<int> slidedColonne= inverse(slide(g, inverse(colonne)));
        for(int k=0; k<dimension(g); k++){
            g.table.at(k).at(i)=slidedColonne.at(k);
        }
    }
    if(isSameGrille(instanceg, g)){return -1;}   
    return vides(g);    
}


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
