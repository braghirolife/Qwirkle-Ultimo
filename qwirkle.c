#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


typedef struct jogadores{
    char nome[15];
    char mao[7][3];
    int pontos;
}jogadores;


void limpa_buffer(){
int c;
do{
    c = getchar();
}while(c != EOF && c != '\n');

}

void colocar_na_mao(jogadores *jogadores, char qwirkle[109][3]){
    int i = 0,k = 0;
    char zero[3] = "00";
    while(i<6){
        k = rand() % 108;
      if(strcmp(qwirkle[k],"00")!= 0){
      strcpy(jogadores->mao[i],qwirkle[k]);
      strcpy(qwirkle[k],zero);
      i++;
      }
      }
}


int menu(){
  char v[12],i;
  printf("\nOpcoes de jogo: passar , trocar, jogar. ");

  fgets(v,12,stdin);
  for(i=0;i<12;i++){
    if(v[i] == '\n'){
      v[i] = '\0';
      break;
    }
  }

  while(strcmp(v,"trocar") != 0 && strcmp(v,"jogar")!=0 && strcmp(v,"passar")!=0){
    printf("\nDigitou errado!");
    printf("\nDigite o comando certo: ");
    fgets(v,12,stdin);
    for(i=0;i<12;i++){
    if(v[i] == '\n'){
      v[i] = '\0';
      break;
    }
  }
  }

   if(strcmp(v,"passar") == 0){

    return 1;
  }
   if(strcmp(v,"jogar") == 0){

    return 2;
  }
   if(strcmp(v,"trocar") == 0){

    return 3;
  }
  return 0;

}

int computar_pontos(char jogo[150][150][3],int index, int index2){
  int pontos = 0,i=1,k=1;

    while(index2-i>=0 && strcmp(jogo[index][index2-i],"  ") != 0){ //conta pontos da linha para a esquerda
      pontos++;
      i++;
      if(i == 5){
      pontos+=6;
      }
    }
    i=1;
    while(strcmp(jogo[index][index2+i],"  ") != 0){ //conta ponos da linha para a direita
      pontos++;
      i++;
        if(i == 5){
          pontos+=6;
        }
    }
    i = 1;
    while(index-i >=0 && strcmp(jogo[index-i][index2],"  ") != 0){
      pontos++;
      i++;
      if(i == 5){
        pontos+=6;
      }
    }
    i = 1;
    while(strcmp(jogo[index+i][index2],"  ")!=0){
      pontos++;
      i++;
      if(i == 5){
      pontos+=6;
      }
    }
    if(i == 5){
      pontos+=6;
    }
  return pontos+1;
}

int jogada_permitida(char jogo[150][150][3], int row, int col,int x_x,int y_y){
  int i = 1,j=0,k=1;
  int flag;
  flag = 1;
    while(strcmp(jogo[row][col+k],"  ")!=0 && col+k<=x_x+1){
      if(strcmp(jogo[row][col],jogo[row][col+k]) == 0){
        flag = 0;
        return flag;
      }
      k++;
    }
    k=1;
    i=1;
    while(col-k>=0){
      if(strcmp(jogo[row][col],jogo[row][col-k])==0){
        flag = 0;
        return flag;
        }
        k++;
    }
    k=1;
    i=1;

    while(strcmp(jogo[row+k][col],"  ")!=0 && row+k<=y_y+1){
      if(strcmp(jogo[row][col],jogo[row+k][col])==0){
        flag = 0;
        return flag;
      }
      k++;
    }
    k=1;
    i=1;

    while(row-i>=0){
      if(strcmp(jogo[row][col],jogo[row-i][col])==0){
        flag = 0;
        return flag;
      }
      i++;
    }
      i=1;


    while(col+i <= x_x+1 && strcmp(jogo[row][col+i],"  ")!=0){
      if(jogo[row][col][0] == jogo[row][col+i][0] || jogo[row][col][1] == jogo[row][col+i][1] ){
        flag = 1;
        if(strcmp(jogo[row][col+i+1],"  ")==0){
          return flag;
        }
      }
      else{
        flag = 0;
        return flag;
      }
      i++;
    }
    i=1;
    while(strcmp(jogo[row+i][col],"  ")!=0 && row+i<=y_y+1){
      if(jogo[row][col][0] == jogo[row+i][col][0] || jogo[row][col][1] == jogo[row+i][col][1]){
        flag = 1;
        if(strcmp(jogo[row+i+1][col],"  ")==0){
          return flag;
        }
      }
      else{
        flag = 0;
        return flag;
      }
      i++;
    }
    i=1;

     while(col-i>=0 && strcmp(jogo[row][col-i],"  ")!=0 && col-i <= x_x+1){
      if(jogo[row][col][0] == jogo[row][col-i][0] || jogo[row][col][1] == jogo[row][col-i][1]){
        flag = 1;
        if(strcmp(jogo[row][col-i-1],"  ")==0){
          return flag;
        }
        }
        else {
          flag = 0;
        return flag;
        }
        i++;
    }

    i = 1;
    while( row-i>=0 && strcmp(jogo[row-i][col],"  ")!=0){
      if(jogo[row][col][0] == jogo[row-i][col][0] || jogo[row][col][1] == jogo[row-i][col][1]){
        flag = 1;
        if(strcmp(jogo[row-i-1][col],"  ")==0){
          return flag;
        }
      }
      else{
        flag = 0;
        return flag;
      }

      i++;
    }
  return flag;
}

void expandir(char jogo[150][150][3],int index, int index2,int *tmpx, int *tmpy,int **x_x,int **y_y){
  int i =0, j = 0,z,k;
  if(index == **y_y - 1   || index == 0){
    (**y_y)++;
        if(*tmpy >= 0){
          (*tmpy)++;
        }
    if(index == 0){
  for(z=**y_y-2;z>=0;z--){
      for(j=0;j<**x_x;j++){
        strcpy(jogo[z+1][j],jogo[z][j]);
        strcpy(jogo[z][j],"  ");
      }
    }
    }
  }

  if(index2 == **x_x - 1 || index2 == 0 ){
    (**x_x)++;
        if(*tmpx >= 0){
          (*tmpx)++;
        }
    for(i = 0; i<**y_y; i++){
      strcpy(jogo[i][**x_x-1],"  ");
      //strcpy(jogo[i][x_x-2]," ");
  }
  if(index2 == 0){
  for(i=0;i<**y_y;i++){
      for(j=**x_x-2;j>=0;j--){
        strcpy(jogo[i][j+1],jogo[i][j]);
        strcpy(jogo[i][j],"  ");
      }
    }
  }
}
  if(strcmp(jogo[**y_y-1][**x_x-1],"  ")!=0){
    (**x_x)++;
    (**y_y)++;
  }
}
void print(char jogo[150][150][3],int x_x, int y_y){
  int i , j=0;
  printf("  ");
  for(i=0; i < x_x ; i++){
    if(i>0){
      printf("  ");
      printf("%d",i);
    }
    if(i==0){
      printf("%d",i);
      }
}
  printf("\n");
  for( i = 0; i < y_y ; i++){
    printf("%d|",i);
    for( j = 0; j < x_x ; j++){

      printf("%s|",jogo[i][j]);
    }
    printf("\n");
  }
}


 

   

void trocar(jogadores *jogadores, char qwirkle[109][3]){
  int i=0,k=0,v=0,flag=0;
  char trocar[3];
  char subst[3];
  srand(time(NULL));
  k = rand() % 108;
  while(1){
    if(strcmp(qwirkle[k],"00")!=0){
      strcpy(subst,qwirkle[k]);
      break;
    }
    k = rand() % 108;
  }
  printf("\nDigite a peca que deseja trocar: ");
  limpa_buffer();
  fgets(trocar,3,stdin);
  while(1){
    if(strcmp(jogadores->mao[i],trocar) == 0){
      for(v=0;v<108;v++){
        if(strcmp("00",qwirkle[v]) == 0 && flag == 0){
          strcpy(qwirkle[v],jogadores->mao[i]);
          strcpy(jogadores->mao[i],subst);
          flag = 1;
          limpa_buffer();
          return;
        }
      }
      if(flag == 1){
        printf("\nTroca realizada!");
        limpa_buffer();
        return;
      }
    }
    i++;
    if(i>=6){
    printf("\nNao foi possivel realizar a troca");
    limpa_buffer();
    return;
    i=0;
  }
  }

}


int movimento(int *tmpx, int *tmpy, int index, int index2, int njogada){
  if(njogada == 2){
    if(index == *tmpx){
            *tmpy = -1;
            return 0;
        }else{
            if(index2 == *tmpy){
                *tmpx = -1;
                return 0;
            }else{
                return 1;
            }
        }
    }else{
        if(njogada > 2){
            if(index == *tmpx){
                return 0;
            }else{
                if(index2 == *tmpy){
                    return 0;
                }else{
                    return 1;
                }
            }
        }
        return 0;
    }
}

int acabou(char qwirkle[109][3]){
  int contagem = 0, flag = 0;
  for(int i = 0; i<109; i++){
    if(strcmp(qwirkle[i],"00")==0){
      contagem++;
    }
  }
  if(contagem == 108){
    flag = 1;
    return flag;
  }
  else{
    flag = 0;
    return flag;
  }
}


