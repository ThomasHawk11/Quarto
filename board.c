//QUARTO : Moteur

//Directives de préprocesseur
#include <stdio.h>
#include <stdlib.h>
#include "board.h"

//Création des fonctions

//Définition du tab de jeu
struct board_t{
  piece tab[DIMENSION][DIMENSION];
  int ligne_last_piece;
  int colonne_last_piece;
};

//Définition d'une pièce
struct piece_t{
  enum size taille;
  enum shape forme;
  enum color couleur;
  enum top dessus;
};

//Création d'un nouveau tab
board new_game(){
  board b;
  b = malloc(sizeof(struct board_t));
  for(int i = 0 ; i < DIMENSION ; i++){
    for(int j = 0 ; j < DIMENSION ; j++){
      b->tab[i][j] = NULL ;
    }
  }
  b->ligne_last_piece = -1;
  b->colonne_last_piece = -2;
  return b;
}

//Copie d'une tab
board copy_game(board game){
    board copy = new_game();
    
    copy->ligne_last_piece = game->ligne_last_piece;
    copy->colonne_last_piece = game->colonne_last_piece;
    
    for(int i = 0 ; i < DIMENSION ; i++){
        for(int j = 0 ; j < DIMENSION ; j++){
            if(game->tab[i][j] != NULL){
                copy->tab[i][j] = game->tab[i][j];
            }
        }
    }
    return copy;
}

//Suppression du tab
void destroy_game(board game){
  free(game);
}

//Renvoie "true" si la case est occupée
bool is_occupied(board game, int line, int column){
  if(game->tab[line][column]!=NULL){
    return true;
  }
  return false;
}

//Renvoie la pièce placée sur une case du tab
piece get_piece(board game, int line, int column){
  if(game->tab[line][column]!=NULL || line < 0 || line > 3 || column < 0 || column > 3 ){
    return game->tab[line][column];
  }else{
    return NULL;
  }
}

//Taille de la pièce
enum size piece_size(piece a_piece){
  if(a_piece!=NULL){
    return a_piece->taille;
  }else{
    return TALL ;
  }
}

//Dessus de la pièce
enum top piece_top(piece a_piece){
  if(a_piece!=NULL){
    return a_piece->dessus;
  }else{
    return HOLLOW ;
  }
}

//Couleur de la pièce
enum color piece_color(piece a_piece){
  if(a_piece!=NULL){
    return a_piece->couleur;
  }else{
    return RED ;
  }
}

//Forme de la pièce
enum shape piece_shape(piece a_piece){
  if(a_piece!=NULL){
    return a_piece->forme;
  }else{
    return SQUARE ;
  }

}

/*
bool has_winner(board game){
  int comparaison[4]={0,0,0,0};
   Chaque valeur du tableau représente le nombre de comparaison vraie pour chaque
  caractéristiques. Il y aura un gagnant si l'on retrouve un 3 dans le tableau 
  if(game->ligne_last_piece == -1){
    return 0;
  }else{
    //Vérification en colonne
    if(game->tab[0][game->colonne_last_piece]!=NULL && game->tab[1][game->colonne_last_piece]!=NULL && game->tab[2][game->colonne_last_piece]!=NULL && game->tab[3][game->colonne_last_piece]!=NULL){
      for(int i=0 ; i < DIMENSION - 1 ; i++){
        if(piece_size(game->tab[i][game->colonne_last_piece]) == piece_size(game->tab[i+1][game->colonne_last_piece])){
          comparaison[0] = comparaison[0] +1;
        }
        else if(piece_shape(game->tab[i][game->colonne_last_piece]) == piece_shape(game->tab[i+1][game->colonne_last_piece])){
          comparaison[1] = comparaison[1] +1;
        }
        else if(piece_color(game->tab[i][game->colonne_last_piece]) == piece_color(game->tab[i+1][game->colonne_last_piece])){
          comparaison[2] = comparaison[2] +1;
        }
        else if(piece_top(game->tab[i][game->colonne_last_piece]) == piece_top(game->tab[i+1][game->colonne_last_piece])){
          comparaison[3] = comparaison[3] +1;
        }
      }

    //Vérification en ligne
    }else if(game->tab[game->ligne_last_piece][0]!=NULL && game->tab[game->ligne_last_piece][1]!=NULL && game->tab[game->ligne_last_piece][2]!=NULL && game->tab[game->ligne_last_piece][3]!=NULL){
      for(int i=0 ; i < DIMENSION - 1 ; i++){
        if(piece_size(game->tab[game->ligne_last_piece][i]) == piece_size(game->tab[game->ligne_last_piece][i+1])){
          comparaison[0] = comparaison[0] +1;
        }
        else if(piece_shape(game->tab[game->ligne_last_piece][i]) == piece_shape(game->tab[game->ligne_last_piece][i+1])){
          comparaison[1] = comparaison[1] +1;
        }
        else if(piece_color(game->tab[game->ligne_last_piece][i]) == piece_color(game->tab[game->ligne_last_piece][i+1])){
          comparaison[2] = comparaison[2] +1;
        }
        else if(piece_top(game->tab[game->ligne_last_piece][i]) == piece_top(game->tab[game->ligne_last_piece][i+1])){
          comparaison[3] = comparaison[3] +1;
        }
      }
    }

    //Vérification en diagonale
    else if(game->tab[0][0]!=NULL && game->tab[1][1]!=NULL && game->tab[2][2]!=NULL && game->tab[3][3]!=NULL ){
      for(int i=0 ; i < DIMENSION - 1 ; i++){
        if(piece_size(game->tab[i][i]) == piece_size(game->tab[i+1][i+1])){
          comparaison[0] = comparaison[0] +1;
        }
        else if(piece_shape(game->tab[i][i]) == piece_shape(game->tab[i+1][i+1])){
          comparaison[1] = comparaison[1] +1;
        }
        else if(piece_color(game->tab[i][i]) == piece_color(game->tab[i+1][i+1])){
          comparaison[2] = comparaison[2] +1;
        }
        else if(piece_top(game->tab[i][i]) == piece_top(game->tab[i+1][i+1])){
          comparaison[3] = comparaison[3] +1;
        }
      }
    }

    //Vérification de la deuxième diagonale
    else if(game->tab[0][3]!=NULL && game->tab[1][2]!=NULL && game->tab[2][1]!=NULL && game->tab[3][0]!=NULL ){
      for(int i=0 ; i < DIMENSION - 1 ; i++){
        if(piece_size(game->tab[i][3-i]) == piece_size(game->tab[i][3-i])){
          comparaison[0] = comparaison[0] +1;
        }
        else if(piece_shape(game->tab[i][3-i]) == piece_shape(game->tab[i][3-i])){
          comparaison[1] = comparaison[1] +1;
        }
        else if(piece_color(game->tab[i][3-i]) == piece_color(game->tab[i][3-1])){
          comparaison[2] = comparaison[2] +1;
        }
        else if(piece_top(game->tab[i][3-i]) == piece_top(game->tab[i][3-1])){
          comparaison[3] = comparaison[3] +1;
        }
      }
    }
    for(int i=0 ; i < 4 ; i++){
      if(comparaison[i]==3){
        return 1;
      }
    }
  }
  return 0;
}
*/





//Fonction qui permet savoir si il y a un gagnant selon un tab de jeu
bool has_winner(board game){
      int check[4]={0,0,0,0};
    
    //Test de la ligne
    for(int i = 0 ; i < DIMENSION ; i++){
        if(game->tab[game->ligne_last_piece][i] == NULL){
            break;
        }
        if(game->tab[game->ligne_last_piece][i]->taille == game->tab[game->ligne_last_piece][game->colonne_last_piece]->taille){
            check[0]++;
        }
        if(game->tab[game->ligne_last_piece][i]->forme == game->tab[game->ligne_last_piece][game->colonne_last_piece]->forme){
            check[1]++;
        }
        if(game->tab[game->ligne_last_piece][i]->couleur == game->tab[game->ligne_last_piece][game->colonne_last_piece]->couleur){
            check[2]++;
        }
        if(game->tab[game->ligne_last_piece][i]->dessus== game->tab[game->ligne_last_piece][game->colonne_last_piece]->dessus){
            check[3]++;
        }
    }
    for(int i=0 ; i < DIMENSION ; i++){
      if(check[i]==4){
        return 1;
      }
      check[i]=0;
    }
    
    //Test de la colonne
    for(int i = 0 ; i < DIMENSION ; i++){
        if(game->tab[i][game->colonne_last_piece] == NULL){
            break;
        }
        if(game->tab[i][game->colonne_last_piece]->taille == game->tab[game->ligne_last_piece][game->colonne_last_piece]->taille){
            check[0]++;
        }
        if(game->tab[i][game->colonne_last_piece]->forme == game->tab[game->ligne_last_piece][game->colonne_last_piece]->forme){
            check[1]++;
        }
        if(game->tab[i][game->colonne_last_piece]->couleur == game->tab[game->ligne_last_piece][game->colonne_last_piece]->couleur){
            check[2]++;
        }
        if(game->tab[i][game->colonne_last_piece]->dessus== game->tab[game->ligne_last_piece][game->colonne_last_piece]->dessus){
            check[3]++;
        }
    }
    for(int i=0 ; i < DIMENSION ; i++){
      if(check[i]==4){
        return 1;
      }
      check[i]=0;
    }

    
    //Test de la première diagonale
    if(game->ligne_last_piece == game->colonne_last_piece){
        
        for(int i = 0 ; i < DIMENSION ; i++){
            
            if(game->tab[i][i] == NULL){
                break;
            }
            if(game->tab[i][i]->taille == game->tab[game->ligne_last_piece][game->colonne_last_piece]->taille){
                check[0]++;
            }
            if(game->tab[i][i]->forme == game->tab[game->ligne_last_piece][game->colonne_last_piece]->forme){
                check[1]++;
            }
            if(game->tab[i][i]->couleur == game->tab[game->ligne_last_piece][game->colonne_last_piece]->couleur){
                check[2]++;
            }
            if(game->tab[i][i]->dessus == game->tab[game->ligne_last_piece][game->colonne_last_piece]->dessus){
                check[3]++;
            }
        }
        
    for(int i=0 ; i < DIMENSION ; i++){
      if(check[i]==4){
        return 1;
      }
      check[i]=0;
    }
  }
    
    //Test de la deuxième diagonale
    if(game->ligne_last_piece == DIMENSION - game->colonne_last_piece - 1){
       
       for(int i = 0 ; i < DIMENSION ; i++){
            
            if(game->tab[DIMENSION - i - 1][i] == NULL){
                break;
            }
            if(game->tab[DIMENSION - i - 1][i]->taille == game->tab[game->ligne_last_piece][game->colonne_last_piece]->taille){
                check[0]++;
            }
            if(game->tab[DIMENSION - i - 1][i]->forme == game->tab[game->ligne_last_piece][game->colonne_last_piece]->forme){
                check[1]++;
            }
            if(game->tab[DIMENSION - i - 1][i]->couleur == game->tab[game->ligne_last_piece][game->colonne_last_piece]->couleur){
                check[2]++;
            }
            if(game->tab[DIMENSION - i - 1][i]->dessus == game->tab[game->ligne_last_piece][game->colonne_last_piece]->dessus){
                check[3]++;
            }
        }
        
    for(int i=0 ; i < DIMENSION ; i++){
      if(check[i]==4){
        return 1;
      }
      check[i]=0;
    }

  }
    
    return 0;
}


//Renvoie "true" si la pièce est présente sur le tab
bool is_present_on_board(board game, piece a_piece){
  for(int i = 0 ; i < DIMENSION ; i++){
    for(int j = 0 ; j < DIMENSION ; j++){
      if(game->tab[i][j]!=NULL
         && piece_size(a_piece)==piece_size(game->tab[i][j]) 
         && piece_shape(a_piece)==piece_shape(game->tab[i][j]) 
         && piece_color(a_piece)==piece_color(game->tab[i][j]) 
         && piece_top(a_piece)==piece_top(game->tab[i][j])){
        return true;
      }
    }
  }
  return false;
}

//Placer une pièce sur le tab
enum return_code place_piece(board game, int line, int column, piece a_piece){
    if(line<0 || line>=DIMENSION || column<0 || column>=DIMENSION || is_occupied(game, line, column)){
        return POSITION;
    }
    else if(is_present_on_board(game, a_piece)){
        return PIECE;
    }
    game->tab[line][column] = a_piece;
    game->ligne_last_piece = line;
    game->colonne_last_piece = column;
    return SUCCESS;
}


//Création d'une pièce
piece get_piece_from_characteristics(enum size a_size, enum shape a_shape, enum color a_color,  enum top a_top){
  piece p;
  p = malloc(sizeof(struct piece_t));
  p->taille=a_size;
  p->forme=a_shape;
  p->couleur=a_color;
  p->dessus=a_top;
  return p;
}
