#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef struct_h
#define struct_h
//tipo que define o uso do padrão de cores RGB
typedef struct rgb{
	int r;
	int g;
	int b;
}RGB;

//Arquivo imagem usado na fução opne
FILE *imagem;
//Nome de imagem digitado pelo usuario na função open
char nome_da_imagem[100];
//Tipo da imagem encontrada dentro do arquivo de imagem
char tipo[2];
//Definição do filtro escolhido pelo usuário
char comando[20];

int altura;

int largura;

int qualidade;

int altura_s;

int largura_s;

int graus;

int sentido;

void inicio();

void saida();

void pular_comentario();

void desalocar();

enum filtros {
 	Grayscale=1,
 	Enlarge,
 	Rotate,
	Reduce,
 	Blurring,
 	Sharpening,
 	Border,
 	Fim
 };

#endif
