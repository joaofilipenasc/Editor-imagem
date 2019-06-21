#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "filtros.h"

int main () {
	//chama a função inicio
	inicio();
	//Definição da matriz RGB

	RGB** img;

	img = malloc(altura*sizeof(RGB));
	int i,j;
	for(i = 0; i < altura; i++) {
		img[i] = malloc(largura*sizeof(RGB));
	}
	//pula comentários da imagem
	pular_comentario(img);
	//chama a função de leitura
	read(img);
	//chama a função de escolha dos filtros
	comandos(img);
	//desaloca a alocacao dinamica
	// desalocar(img);

	return 0;
}
