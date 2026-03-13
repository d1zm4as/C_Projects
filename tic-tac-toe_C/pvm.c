#include <stdio.h>
#include <stdlib.h>
void tabul(char casas2[3][3]) {
  printf("\t%c | %c | %c\a\n", casas2[0][0], casas2[0][1], casas2[0][2]);
  printf("  --------------- \n");
  printf("\t%c | %c | %c\a\n", casas2[1][0], casas2[1][1], casas2[1][2]);
  printf("  --------------- \n");
  printf("\t%c | %c | %c\a\n", casas2[2][0], casas2[2][1], casas2[2][2]);
  printf("\n");
}
int vitoria_linhas(char matriz[3][3]){
  int contador =0;
  for(int linhas = 0;linhas<3;linhas++){
    if(matriz[linhas][0] == matriz[linhas][1] && matriz[linhas][0] == matriz[linhas][2]){
      contador=3;
    }
  }
  if(contador==3){
    return 1;
  }else{
    return 0;
  }
  }
int vitoria_colunas(char matriz[3][3]){
  int contador = 0;
  for(int colunas =0;colunas<3;colunas++){
    if(matriz[0][colunas] == matriz[1][colunas] && matriz[0][colunas] == matriz[2][colunas]){
      contador=3;
      }
      }
    if(matriz[0][0] == matriz[1][1] && matriz[0][0] == matriz[2][2]){
      contador=3;
    }
  if(matriz[0][2] == matriz[1][1] && matriz[0][2] == matriz[2][0]){
      contador=3;
    }
  
      if(contador ==3){
        return 1;
      }else{
        return 0;
      }
     }

int pvm(void) {
  int jogadas = 0;
  int ca = 0;
  int la = 0;
  int vl = 0;
  int vc =0;
  char escolha;
  int contador = 0;
  int logica = 0;
  char tab[3][3] = {
      {'1', '2', '3'},
      {'4', '5', '6'},
      {'7', '8', '9'},
  };
  while (jogadas < 9) {
    tabul(tab);
    srand(time(NULL));
    if (jogadas % 2 == 0) {
      printf("Jogador 1 escolha uma casa : \n");
      scanf("%c", &escolha);
      for (int linhas = 0; linhas < 3; linhas++) {
        for (int colunas = 0; colunas < 3; colunas++) {
          if (tab[linhas][colunas] == escolha) {
            tab[linhas][colunas] = 'X';
            jogadas++;
          }
        }
      }
    } else {
      printf("Vez da CPU... \n");
      while(logica!=1){
          if(tab[0][0] == tab[0][1] && (tab[0][2] !='X' || tab[0][2]!='O')){
            tab[0][2] = 'O';
            break;
      }else if(tab[0][0] == tab[0][2]  && (tab[0][2] !='X' || tab[0][1]!='O')){
            tab[0][1] = 'O';
            break;
        }else if(tab[0][1] == tab[0][2]  && (tab[0][0] !='X' || tab[0][0]!='O')){
            tab[0][0] = 'O';
            break;
            }else if(tab[1][0] == tab[1][1] && (tab[1][2] !='X' && tab[1][2]!='O')){
            tab[1][2] = 'O';
            break;
            }else if(tab[1][1] == tab[1][2] && (tab[1][0] !='X' && tab[1][0] !='O')){
              tab[1][0] = 'O';
              break;
            }else if(tab[1][0] == tab[1][2] && tab[1][1]!='X' && tab[1][1] !='O'){
            tab[1][1] = 'O';
            break;
            }else if(tab[2][0] == tab[2][1] &&(tab[2][2] !='X' || tab[2][2] !='O')){
            tab[2][2] = 'O';
            break;
            }else if(tab[2][0] == tab[2][2] && (tab[2][1] !='X' || tab[2][1] !='O')){
            tab[2][1] = 'O';
            break;
            }else if(tab[2][1] == tab[2][2] && (tab[2][0] !='X' || tab[2][0] !='O')){
            tab[2][0] ='O';
            break;
            }else if(tab[0][0] == tab[1][0] && (tab[2][0] !='X' || tab[2][0]!='O')){
            tab[2][0] = 'O';
            break;
            }else if(tab[0][0] == tab[2][0] &&(tab[1][0] !='O' && tab[1][0] !='X')){
            tab[1][0] = 'O';
            break;
            }else if(tab[1][0] == tab[2][0]&&(tab[0][0] !='X' && tab[0][0] !='O')){
            tab[0][0] = 'O';
            break;
            }else if(tab[0][1] == tab[1][1] && (tab[2][1] !='O' || tab[2][1] !='X')){
              tab[2][1] = 'O';
              break;
            }else if(tab[0][1] == tab[2][1] && (tab[1][1] !='X' || tab[1][1] !='O' )){
              tab[1][1] = 'O';
              break;
            }else if(tab[2][1] == tab[1][1] && (tab[0][1] !='X' || tab[0][1] !='O')){
            tab[0][1] = 'O';
            break;
            }else if(tab[0][2] == tab[1][2] && (tab[2][2] =!'X' || tab[2][2] != 'O')){
            tab[2][2] = 'O';
            break;
            }else if(tab[0][2] == tab[2][2] &&(tab[1][2] !='X' || tab[1][2] !='O' )){
            tab[1][2] = 'O';
            break;
            } else if(tab[1][2] == tab[2][2] && (tab[0][2] !='X' || tab[0][2] != 'O')){
            tab[0][2] = 'O';
            break;
            } else if(tab[0][0] == tab[1][1] && (tab[2][2] !='O' && tab[2][2] !='X')){
            tab[2][2] = 'O';
            break;
            }else if(tab[1][1] == tab[2][2] && (tab[0][0] !='X'||tab[0][0] !='O' )){
            tab[0][0] = 'O';
            break;
            } else if(tab[0][2] == tab[1][1] &&(tab[2][0] !='X' || tab[2][0] != 'O')){
              tab[2][0] = 'O';
            break;
            }else if(tab[1][1] ==tab[2][0] && (tab[0][2] == 'X' && tab[0][2] != 'O')){
            tab[0][2] = 'O';
            break;
            }else if(tab[0][2] == tab[1][1] && (tab[2][0] !='X' || tab[2][0] == 'O')){
            tab[2][0] = 'O';
            break;
            } else if(tab[2][0] == tab[0][2] && (tab[1][1] !='X' || tab[1][1] !='O')){
            tab[1][1] = 'O';
            break;
            } else if(tab[0][0] == tab[2][2] && (tab[1][1]!='O' || tab[1][1] !='X')){
            tab[1][1] ='O';
            break;
            }
          else{
          la = random()%3;
          ca = random()%3;
          if(tab[la][ca] != 'X' && tab[la][ca] !='O'){
            tab[la][ca] = 'O';
            break;
          }
          
        }
        }
      jogadas++;
      if(jogadas==9){
          logica =1;
          break;
      }
      }
  printf("Fim da jogada = %d \n",jogadas);
  tabul(tab);
  system("clear");
  }
  
  }

  
