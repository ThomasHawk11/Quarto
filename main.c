//QUARTO : Interface

//Directives de préprocesseur
#include <stdio.h>
#include <stdlib.h>
#include "board.c"

//Pré-initialisation de fonctions
void afficher_piece(piece p);

//Création des fonctions

//Affichage du tableau et des pièces qu'il contient
void affiche_grille(board game){
  printf("    0     1     2     3\n");
  for(int i=0 ; i < DIMENSION ; i++){
    printf(" ╬═════╬═════╬═════╬═════╬\n");
    printf("%d║",i);
    for(int j=0 ; j < DIMENSION ; j++){
      if(is_occupied(game,i,j) == 1){        //Si la case est occupée, on affiche la
        afficher_piece(get_piece(game,i,j)); //pièce qui se trouve dessus.
        printf("║"); 
      }else{
      printf("     ║");      
      }
    }
    printf("\n");
  }
  printf(" ╬═════╬═════╬═════╬═════╬\n");
}


// Fonction permettant de demander à l'utilisateur de
// choisir les caractéristiques d'une pièce.
piece demander_piece(){

  //Demande la taille de la pièce.
  printf("\nQuelle est la taille de la pièce ?\n0 : TALL\n1 : SHORT\n");
  int taille = 2;
  enum size size;
  printf("→ ");
  while(taille !=1 && taille !=0){
    while (scanf("%d",&taille)!= 1){
      getchar();
    }
  }

  if(taille == 0){
    size = TALL;
  }else{
    size = SHORT;
  }

  //Demande la forme de la pièce
  printf("\nQuelle est la forme de la pièce ?\n0 : SQUARE\n1 : CIRCULAR\n");
  int forme = 2;
  enum shape shape;
  printf("→ ");
  while(forme != 1 && forme != 0){
    while (scanf("%d",&forme)!= 1){
      getchar();
    }
  }

  if(forme == 0){
    shape = SQUARE;
  }else{
    shape = CIRCULAR;
  }

  //Demande la couleur de la pièce.
  printf("\nQuelle est la couleur de la pièce ?\n0 : RED\n1 : BLUE\n");
  int couleur = 2;
  enum color color;
  printf("→ ");
  while(couleur != 1 && couleur != 0){
    while (scanf("%d",&couleur)!= 1){
      getchar();
    }
  }

  if(couleur == 0){
    color = RED;
  }else{
    color = BLUE;
  }

  //Demande si la pièce est pleine ou creuse.
  printf("\nLa pièce est-elle creuse ou pleine ?\n0 : HOLLOW\n1 : SOLID\n");
  int dessus = 2;
  enum top top;
  printf("→ ");
  while(dessus != 1 && dessus != 0){
    while (scanf("%d",&dessus)!= 1){
      getchar();
    }
  }

  if(dessus == 0){
    top = HOLLOW;
  }else{
    top = SOLID;
  }

  //Retourne la picèe en fonction des caractéristiques choisis.
  return get_piece_from_characteristics(size, shape, color, top);

}


// Fonction permettant de demander au joueur la position
// à laquelle il veut placer sa pièce.
void demander_position(board game,piece p){
  int x;
  int y;
  printf("A quelle position voulez-vous mettre votre pièce ?\n");
  printf("LIGNE : ");
  scanf("%d",&x);
  printf("COLONNE : ");
  scanf("%d",&y);
  //Vérifie si la pièce peut être placée.
  enum return_code res = place_piece(game, x, y, p);
  if(res == SUCCESS){
  	printf("\nLa piece a été placée avec succès.\n\n");
	}
	else {
	  printf("\nUn problème a eu lieu lors du placement\n\n");
	}
}

// Fonction permettant d'afficher la pièce en fonction
// des paramètres choisis.
void afficher_piece(piece p){
  
  //Possibilités de caractéristiques des pièces ROUGES.
  if(piece_color(p)==RED){
    if(piece_size(p)==TALL){
      printf("\033[31m █\033[m");
    }else{
      printf("\033[31m ▂\033[m");
    }
  
    if(piece_shape(p)==SQUARE && piece_top(p)==HOLLOW){
      printf("\033[31m ◻ \033[m");
    }
    else if(piece_shape(p)==SQUARE && piece_top(p)!=HOLLOW){
      printf("\033[31m ■ \033[m");
    }
    else if(piece_shape(p)!=SQUARE && piece_top(p)==HOLLOW){
      printf("\033[31m ◯ \033[m");
    }
    else if(piece_shape(p)!=SQUARE && piece_top(p)!=HOLLOW){
      printf("\033[31m ⬤ \033[m");
    }
  }

  //Possibilités de caractéristiques des pièces BLEUES.
  if(piece_color(p)!=RED){
    if(piece_size(p)==TALL){
      printf("\033[34m █\033[m");
    }else{
      printf("\033[34m ▂\033[m");
    }
  
    if(piece_shape(p)==SQUARE && piece_top(p)==HOLLOW){
      printf("\033[34m ◻ \033[m");
    }
    else if(piece_shape(p)==SQUARE && piece_top(p)!=HOLLOW){
      printf("\033[34m ■ \033[m");
    }
    else if(piece_shape(p)!=SQUARE && piece_top(p)==HOLLOW){
      printf("\033[34m ◯ \033[m");
    }
    else if(piece_shape(p)!=SQUARE && piece_top(p)!=HOLLOW){
      printf("\033[34m ⬤ \033[m");
    }
  }

}

// Corps principal du jeu.
int main(int args, char **argv){
  int continuer = 1; //Variable utilisée pour recommencer une partie.
  while(continuer==1){
    printf("\033[32m▀▄▀▄▀▄▀▄▀▄▀▄▀▄ QUARTO ▀▄▀▄▀▄▀▄▀▄▀▄▀▄\n\n\033[m");
	  board game = new_game();
	  printf("Un plateau est créé.\n\n");
    affiche_grille(game);
  
    int joueur = 1;

    while(has_winner(game)==0){
      printf("\nAu tour du joueur %d de jouer.\n",joueur);
      piece p = get_piece_from_characteristics( TALL, SQUARE, RED, HOLLOW); // Initialisation d'une pièce quelconque.
      p = demander_piece();
      
      printf("\nPièce choisie : ");
      afficher_piece(p);
      printf("\n\n");
      
      demander_position(game,p);
      
    
      affiche_grille(game);

      // Changement de joueur
      if(joueur==1){
        joueur = 2;
      }else{
        joueur = 1;
      }
    
    }

    //Détermination du gagnant.
    if(joueur==1){
      printf("\nLe joueur 2 a gagné !\n");
    }else{
      printf("\nLe joueur 1 a gagné !\n");
    }

    //Possibilité de rejouer.
    printf("\nVoulez-vous rejouer ?\n0 : NON\n1 : OUI\n");
    printf("→ ");
    scanf("%d",&continuer);
    if(continuer==0){
      printf("\nSuppression du plateau...\n");
      destroy_game(game);
    }

  }
  //Fin de partie.
  printf("\033[31m\n▀▄▀▄▀▄▀▄▀ PARTIE TERMINEE ▄▀▄▀▄▀▄▀▄\n\033[m");
	return 0;
}


