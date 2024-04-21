#include "jeu.h"
#include <cassert>

/* A faire dans un second temps: petit menu pour exécuter les commandes de
 * l'utilisateur
 */


int interactif() {
    
    Grille main_g; 
    int dim;
    do{
    cout<<"Taille de la grille"
        << endl
        << "3: petit 3x3\t\t4: Classique 4x4\n5: Grand 5x5\t\t6: Immense 6x6\t\t\n8: Immense  8x8"<< endl;
    cin >>dim; 
    }while(dim<3 or dim>8 or dim==7);//Verificattion pour que dim soit correct
    init(main_g, dim, 2048, 5);
    // Action du joueur
    //Penser à rajouter dans l'affichage les action possibles 
    string action;
    
    bool continuer=true;
    affiche(main_g);
    do{//bool errorText=(not(action =="droite" or action =="gauche" or action =="haut" or action =="bas"));
        do{
            cout<< ">> ";cin >>action;
            if(not(action =="droite" or action =="gauche" or action =="haut" or action =="bas")) cout << "Erreur "; 
          }while(not(action =="droite" or action =="gauche" or action =="haut" or action =="bas"));
        if(equalString(action,"droite")){
            if (not droite(main_g)){continuer = false;}
        }else if(equalString(action,"gauche")){
            if (not gauche(main_g)){continuer = false;}
        }else if(equalString(action,"haut")){
            if (not haut(main_g)){continuer = false;}
        }else if(equalString(action,"bas")){
            if (not bas(main_g)){continuer = false;}   
        }else if(equalString(action,"stop")){continuer = false;}
         
        else{
        }
        
        
        chargerCase(main_g, place(main_g) , nouvelle(main_g));
        affiche(main_g);
        
        
        if( continuer == false){
            if(succes(main_g)  or vides(main_g)!=0){
                cout<<"Gagné"<<endl;
            }else{
                cout<<"Perdu"<<endl;
        }}
    }while(continuer);

  return 0;
}


/* Quelques fonctions de test mises à disposition.
 * Elles sont lancées par la fonction testFV qui est elle-même lançable
 * dans la fonction main()à située en fin de fichier.
 * Pour l'instant l'appel à cette fonction est mis en commentaire.
 */


void teste3() {
  Grille g;
  vector<vector<int>> v =
    { { 8, 4, 4, 4 }, { 4, 0, 4, 4 }, { 4, 4, 4, 4 }, { 4, 0, 0, 4} };
  cout << "Debut du test3\n";
  assert(charge(g, v, 32, 7)); // charge et teste le resultat
  affiche(g);

  gauche(g); affiche(g);
  droite(g); affiche(g);
  haut(g);   affiche(g);
  gauche(g); affiche(g);
  haut(g);   affiche(g);
  bas(g);    affiche(g);
  //assert(score(g) == 128 and succes(g));
  cout << "Teste3 OK" << endl;
}

void teste3bis() {
  Grille g;
  vector<vector<int>> v =
    { { 2, 4, 0, 0, 4 }, { 4, 0, 4, 8, 8 }, { 0, 0, 4, 0, 4 }, { 2, 4, 0, 0, 4},
      { 2, 4, 0, 4, 2 }
    };
  cout << "Debut du teste3bis" << endl;
  assert(charge(g, v, 64, 10)); // avec que des tuiles de valeur 2
  affiche(g);
  
  gauche(g); affiche(g);
  assert(score(g) == 56 and gauche(g) == -1);
  cout << "teste3bis-I: OK" << endl;
  // On repart de la meme configuration initiale mais on essaye
  // un autre deplacement
  Grille g2;
  assert(charge(g2, v, 8, 0));
  affiche(g2);
  
  haut(g2);   affiche(g2);
  bas(g2);    affiche(g2);
  droite(g2); affiche(g2);
  assert(score(g2) == 68 and vides(g2) == 16);
  cout << "teste3bis-II: OK" << endl;
  cout << "Fin de teste3bis" << endl;
}

void teste4() {
  Grille g;
  vector<vector<int>> v =
  // une grille bloquée.
    { { 128, 8, 2, 4 }, { 4, 16, 4, 8 }, { 8, 2, 8, 4}, { 2, 4, 16, 32} };
  cout << "Debut du test4" << endl;
  assert(charge(g, v, 2048, 7));
  affiche(g);
  
  assert(gauche(g) == -1 and droite(g) == -1 and
	 haut(g)   == -1 and droite(g) == -1);
  affiche(g);
  cout << "Teste4 OK" << endl;
}

void teste5() {
  Grille g;
  cout << "Debut du test5" << endl;
  assert(init(g, 5, 8, 0)); // on ne cree que des tuiles de valeur 4
  affiche(g);
  
  haut(g);   affiche(g);
  droite(g); affiche(g);
  assert(score(g) == 8 and succes(g));
  cout << "Teste5 OK" << endl;
}

void testFV() {
  teste3();
  teste3bis();
  teste4();
  teste5();
}
void monTeste1(){
    Grille g;
    assert(init(g, 4, 1024, 9)); // exemple d'initialisation d'une grille.
  affiche(g);
}

void monTeste2(){
    Grille g;
    init(g,4,1024,5);
  g.table  =
    { { 0,0,0,0 }, { 0,0,2,2 }, {2,2,2,2}, { 2, 4, 16, 32} };
    affiche(g);
  gauche(g); affiche(g);
    g.table  =
    { { 0,0,0,0 }, { 0,0,2,2 }, {2,2,2,2}, { 2, 4, 16, 32} };
    affiche(g);
  droite(g); affiche(g);
}
void monTeste3(){
    Grille g;
    g.table  =
    { { 2,2,64,2 }, { 2,0,0,0 }, {2,0,0,2}, { 64, 4, 64, 32} } ;
  affiche(g);
    bas(g); affiche(g);
    haut(g); affiche(g);
}

void monTest4(){
    Grille g;
    cout<<"Quel est votre objectif ?"<<endl;
    cin>>g.cible;
    g.table  =
  // une grille bloquée.
    { { 2,2,0,2 }, { 2,0,0,0 }, {2,0,0,32}, { 64, 4, 4, 32} } ;// exemple d'initialisation d'une grille
    
    do{
        char choix;
        affiche(g);
        cout<<"Appuyez sur g pour gauche, d pour droite, b pour bas ou h pour haut ou x pour s'arrêter"<<endl;
        cin>>choix;
        if(choix=='g'){
            gauche(g); 
            affiche(g);
        }
        if(choix=='d'){
            droite(g); 
            affiche(g);
        }
        if(choix=='b'){
            bas(g); 
            affiche(g);
        }
        if(choix=='h'){
            haut(g); 
            affiche(g);
        }
        if(choix=='x'){
            break;
        }
    }while(vides(g)!=0);
    
    cout<<"Objectif : "<<g.cible<<endl;
    if(succes(g)){
        cout<<"Bravo ! Objectif atteint !";
    }
    else{
        cout<<"Perdu... Tu n'as qu'à réessayer.";
    }
}


int main() {
  //monTeste1();
  //monTeste2();
  //monTeste3();
  //testFV();
  interactif();
  return 0;
}
