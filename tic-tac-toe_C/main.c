#include <stdio.h>
#include <stdlib.h>
#include "pvp.c"
#include "pvm.c"

int main(void) {
  int escolha;

  do {
    system("clear");
    printf("Menu\n\n");
    printf("1. PvP\n");
    printf("2. PvM\n");
    printf("3. Sair\n\n");
    scanf("%d", &escolha);

    switch (escolha) {

        case 1: //Opção Jogador versus Jogador
            pvp(); 
            break;

        case 2: //Opção Jogador versus Máquina
            pvm();
            break;

        case 3: printf("Fim\n"); exit(0); //Final de processo

            break;

        default: printf("Ação inválida, digite novamente.\n\n");

            break;
    }

  } while (escolha != 3);
  return 0;
}
