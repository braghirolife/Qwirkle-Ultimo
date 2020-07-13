#ifndef QWIRKLE_H_INCLUDED
#define QWIRKLE_H_INCLUDED

typedef struct jogadores{
    char nome[15];
    char mao[7][3];
    int pontos;
}jogadores;

void colocar_na_mao(jogadores *jogadores, char qwirkle[109][3]);
void limpa_buffer();
int computar_pontos(char jogo[150][150][3],int index, int index2);
int jogada_permitida(char jogo[150][150][3], int row, int col,int x_x,int y_y);
void expandir(char jogo[150][150][3],int index, int index2, int *controle_row, int *controle_col,int **x_x,int **y_y);
void print(char jogo[150][150][3],int x_x,int y_y);
int menu();
void trocar(jogadores *jogadores, char qwirkle[109][3]);
int movimento(int *tmpx, int *tmpy, int index, int index2, int njogada);
int acabou(char qwirkle[109][3]);


#endif // QWIRKLE_H_INCLUDED
