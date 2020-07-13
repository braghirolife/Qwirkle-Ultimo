#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "qwirkle.h"


int jogada(jogadores *jogadores,char jogo[150][150][3],char qwirkle[109][3],int *x_x, int *y_y);

int trapaca(jogadores *jogadores, char qwirkle[109][3], char jogo[150][150][3],int *x_x,int *y_y);

int main(void) {
  int x_x = 1;
  int y_y = 1;
  srand(time(NULL));
  int n_jogadores;
  int i,j;
  char jogo[150][150][3];

  for( i = 0; i < 150; i++){
    for( j = 0; j< 150 ; j++){
      strcpy(jogo[i][j],"  ");
    }
  }

  char qwirkle[109][3] = {"A1" , "A2", "A3", "A4", "A5", "A6","B1", "B2", "B3", "B4", "B5", "B6", "C1", "C2", "C3", "C4", "C5", "C6","D1","D2","D3","D4","D5","D6","E1","E2","E3","E4","E5","E6","F1","F2","F3","F4","F5","F6","A1" , "A2", "A3", "A4", "A5", "A6","B1", "B2", "B3", "B4", "B5", "B6", "C1", "C2", "C3", "C4", "C5", "C6","D1","D2","D3","D4","D5","D6","E1","E2","E3","E4","E5","E6","F1","F2","F3","F4","F5","F6","A1" , "A2", "A3", "A4", "A5", "A6","B1", "B2", "B3", "B4", "B5", "B6", "C1", "C2", "C3", "C4", "C5", "C6","D1","D2","D3","D4","D5","D6","E1","E2","E3","E4","E5","E6","F1","F2","F3","F4","F5","F6"};

   char peca[3];
   char cheat[2];
  printf("Digite o numero de jogadores (de 2 a 4): \n");
  scanf("%d",&n_jogadores);
  jogadores jogadores[n_jogadores];
  setbuf(stdin,NULL);
  printf("Digite o nome dos jogadores: \n");
  for(i = 0; i < n_jogadores; i++){
    printf("Digite o nome do jogador#%d: ", i+1);
    setbuf(stdin,NULL);
    fgets(jogadores[i].nome, 15, stdin);
  }
    system("clear");
    for(i = 0; i < n_jogadores; i++){
     colocar_na_mao(&jogadores[i], qwirkle);
     jogadores[i].pontos = 0;
    }

  printf("Cheat mode? S/N: ");
  fgets(cheat,2,stdin);


  if(strcmp(cheat,"S") == 0){
    limpa_buffer();
    while(1){
      for(i=0;i<n_jogadores;i++){
      jogadores[i].pontos += trapaca(&jogadores[i],qwirkle,jogo,&x_x,&y_y);
      printf("\nPontos do %s: %d",jogadores[i].nome,jogadores[i].pontos);
      printf("\n");
      if(i==n_jogadores-1){
        i=-1;
      }
      if(acabou(qwirkle)){
        return 0;
      }
      }
    }
  }


//Inicia normal

  if(strcmp(cheat,"N")==0){
    limpa_buffer();
  while(1){
    for(i=0;i<n_jogadores;i++){
    jogadores[i].pontos += jogada(&jogadores[i],jogo,qwirkle,&x_x,&y_y);
    printf("\nPontos do %s: %d",jogadores[i].nome,jogadores[i].pontos);
    printf("\n");
  if(i == n_jogadores - 1){
    i = -1;
    }
    if(acabou(qwirkle)){
      return 0;
    }
}
}
}
}

int jogada(jogadores *jogadores,char jogo[150][150][3],char qwirkle[109][3],int *x_x, int *y_y){
  int i = 0,index,index2,pontos=0, njogada = 1,random,a;
  int l, k;
  char peca[3];
  setbuf(stdin,NULL);
  printf("Mao do jogador %s: ",jogadores->nome);
  for( int j = 0; j<6;j++){
    printf("%s ", jogadores->mao[j]);
  }
  printf("\n");
  print(jogo,*x_x,*y_y);
  a = menu();
  if(a == 3){
    int res = 1;
    while(res){
    trocar(jogadores,qwirkle);
    printf("\nDeseja trocar mais pecas?");
    printf("\n(Digite 1 para sim e 0 para nao)");
    scanf("%d", &res);
    }
    printf("\nNova mao do usuario: ");
    for(int j = 0; j < 6; j++){
      printf("%s|",jogadores->mao[j]);
    }
  }
  int tmpx = 0;
  int tmpy = 0;
  while(a == 2){
  int achou = 0;
  int correta = 0;
    printf("\nDigite a peca e a posicao que voce deseja jogar %s: ",jogadores->nome);
    setbuf(stdin, NULL);
    fgets(peca,3,stdin);
    scanf(" %d",&index);
    scanf("%d",&index2);
    for(i = 0;i < 6; i++){
      if(strcmp(jogadores->mao[i],peca)==0){
        achou = 1;
        break;
      }
    }
    if(achou == 0 || strcmp(jogo[index][index2],"  ") != 0){
      printf("\nMovimento invalido"); 
    }else{
        strcpy(jogo[index][index2],peca);
      if(jogada_permitida(jogo,index,index2,*x_x,*y_y) == 1  && movimento(&tmpx, &tmpy, index, index2, njogada) == 0){
        pontos += computar_pontos(jogo,index,index2);
        strcpy(jogadores->mao[i],"00");
        correta = 1;
        if(njogada == 1){
            tmpx = index;
            tmpy = index2;
        }
        njogada++;
      }
      else{
      printf("\nMovimento invalido"); 
        strcpy(jogo[index][index2], "  ");
        printf("\nDeseja continuar jogando?");
        printf("\n(Digite 2 para sim e 1 para passar)");
        scanf("%d", &a);
        correta = a;
      }
      if(correta == 1){
        expandir(jogo,index,index2,&tmpx,&tmpy,&x_x,&y_y);
        printf("\nDeseja continuar jogando?");
        printf("\n(Digite 2 para sim e 1 para passar)");
        scanf("%d", &a);
        if(a == 2){
          printf("Mao do %s: ",jogadores->nome);
          for(int j=0; j<6 ; j++){
            if(strcmp(jogadores->mao[j],"00")!=0){
            printf("%s ",jogadores->mao[j]);
            }
          }
          printf("\n");
          print(jogo,*x_x,*y_y);
        }
        if(a == 1){
            for(l=0 ; l<7; l++){
                while(strcmp(jogadores->mao[l],"00") == 0 ){
                  random = rand() % 108;
                  if(strcmp(qwirkle[random],"00")!=0){
                  strcpy(jogadores->mao[l],qwirkle[random]);
                  strcpy(qwirkle[random],"00");
                  break;
                  }
                }
            }
          printf("\nNova mao do usuario: ");
          for(int j = 0; j < 6; j++){
            printf("%s|",jogadores->mao[j]);
          }
        }
        }
      }
  }
  return pontos;
}


int trapaca(jogadores *jogadores, char qwirkle[109][3], char jogo[150][150][3],int *x_x,int *y_y){
  int i = 0,index,index2,pontos=0, njogada = 1,random,a;
  int l, k;
  char peca[3];
  limpa_buffer();
  printf("Mao do jogador %s: ",jogadores->nome);
  for( int j = 0; j<6;j++){
    printf("%s ", jogadores->mao[j]);
  }
  printf("\n");
  print(jogo,*x_x,*y_y);
  a = menu();
  if(a == 3){
    int res = 1;
    while(res)
    trocar(jogadores,qwirkle);
    printf("\nDeseja trocar mais pecas?");
    printf("\n(Digite 1 para sim e 0 para nao)");
    scanf("%d", &res);
  }
  int tmpx = 0;
  int tmpy = 0;
  while(a == 2){
  int achou = 0;
  int correta = 0;
    printf("\nDigite a peca e a posicao que voce deseja jogar %s: ",jogadores->nome);
    setbuf(stdin, NULL);
    fgets(peca,3,stdin);
    // limpa_buffer();
    scanf(" %d",&index);
    scanf("%d",&index2);
    for(i = 0;i < 6; i++){
      if(strcmp(jogadores->mao[i],peca)==0){
        // system("clear");
        achou = 1;
        break;
      }
    }
    if(strcmp(jogo[index][index2],"  ") != 0){
      printf("\nMovimento invalido");
    }else{
      if(achou == 1){
        strcpy(jogo[index][index2],peca);
        if(jogada_permitida(jogo,index,index2,*x_x,*y_y) == 1  && movimento(&tmpx, &tmpy, index, index2, njogada) == 0){
          pontos += computar_pontos(jogo,index,index2);
          strcpy(jogadores->mao[i],"00");
          correta = 1;
          if(njogada == 1){
              tmpx = index;
              tmpy = index2;
          }
          njogada++;
        }
        else{
        printf("\nMovimento invalido");
          strcpy(jogo[index][index2], "  ");
          printf("\nDeseja continuar jogando?");
          printf("\n(Digite 2 para sim e 1 para passar)");
          scanf("%d", &a);
          correta = a;
        }
      }else{
        strcpy(jogo[index][index2],peca);
        if(jogada_permitida(jogo,index,index2,*x_x,*y_y) == 1  && movimento(&tmpx, &tmpy, index, index2, njogada) == 0){
          pontos += computar_pontos(jogo,index,index2);
          correta = 1;
          if(njogada == 1){
              tmpx = index;
              tmpy = index2;
          }
          njogada++;
        }
        else{
        printf("\nMovimento invalido");
          strcpy(jogo[index][index2], "  ");
          printf("\nDeseja continuar jogando?");
          printf("\n(Digite 2 para sim e 1 para passar)");
          scanf("%d", &a);
          correta = a;
        }
      }
      if(correta == 1){
        expandir(jogo,index,index2,&tmpx,&tmpy,&x_x,&y_y);
        printf("\nDeseja continuar jogando?");
        printf("\n(Digite 2 para sim e 1 para passar)");
        scanf("%d", &a);
        if(a == 2){
          printf("Mao do %s: ",jogadores->nome);
          for(int j=0; j<6 ; j++){
            if(strcmp(jogadores->mao[j],"00")!=0){
            printf("%s ",jogadores->mao[j]);
            }
          }
          printf("\n");
          print(jogo,*x_x,*y_y);
        }
        if(a == 1){
            for(l=0 ; l<7; l++){
                while(strcmp(jogadores->mao[l],"00") == 0 ){
                  random = rand() % 108;
                  if(strcmp(qwirkle[random],"00")!=0){
                  strcpy(jogadores->mao[l],qwirkle[random]);
                  strcpy(qwirkle[random],"00");
                  break;
                  }
                }
            }
          printf("\nNova mao do usuario: ");
          for(int j = 0; j < 6; j++){
            printf("%s|",jogadores->mao[j]);
          }
        }
        }
      }
  }
  return pontos;
}
