#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "filtros.h"

void grayscale (RGB** img) {

	int i, j;
	RGB** gra;
	gra = malloc(altura*sizeof(RGB));
	for(i = 0; i < altura; i++) {
		gra[i] = malloc(largura*sizeof(RGB));
	}
	// Altera os valores de RGB
	//variaveis altura e largura definidas na função open e criadas no arquivo sruct.h

	for (i=0; i<altura; i++) {
		for (j=0; j<largura; j++) {
			//multiplica os valores de cada coluna de cor por uma constante e atribui os mesmos valores a todos os elementos.
			img[i][j].r = ((0.3*img[i][j].r) + (0.59*img[i][j].g) + (0.11*img[i][j].b));
			img[i][j].g = img[i][j].r;
			img[i][j].b = img[i][j].r;
		}
	}
}

void enlarge (RGB** img) {

	int zoom;
	printf("Insira a quantidade de vezes para aumentar a imagem:\n");
	scanf("%d", &zoom);

	int l, c, rl, rc;
	RGB** enl;
	enl = malloc(altura*zoom*sizeof(RGB));
	for(l = 0; l < altura*zoom; l++) {
		enl[l] = malloc(largura*zoom*sizeof(RGB));
	}

	FILE *saida;


 	saida=fopen("enlarge.ppm", "w");
 	fprintf(saida, "%s\n%d %d\n%d\n", tipo, largura*zoom, altura*zoom, qualidade);

	for(l = 0; l < altura; l++)
		for (rl = 0; rl < zoom; rl++) //repete linhas x vezes
			for(c = 0; c < largura; c++)
				for(rc = 0; rc < zoom; rc++) //repete colunas x vezes
					fprintf(saida, "%d %d %d\n", img[l][c].r, img[l][c].g, img[l][c].b);

	fclose(saida);

}

void reduce (RGB** img) {

	int zoomout;
	printf("Insira o valor da reducao (multiplo dos valores de altura e largura):\n");
	scanf("%d", &zoomout);

	while(altura%zoomout !=0 && largura%zoomout !=0) {
		printf("O valor para reduzir a imagem nao eh multiplo dos valores de altura e largura. Tente novamente:\n");
		scanf("%d", &zoomout);
	}

	int i, j;
	RGB** red;
	red = malloc(altura/zoomout*sizeof(RGB));
	for(i = 0; i < altura/zoomout; i++) {
		red[i] = malloc(largura/zoomout*sizeof(RGB));
	}

	for(i=0; i<altura; i+=zoomout){
		for(j=0; j<largura; j+=zoomout){
			red[(i/zoomout)][(j/zoomout)].r=img[i][j].r;
			red[(i/zoomout)][(j/zoomout)].g=img[i][j].g;
			red[(i/zoomout)][(j/zoomout)].b=img[i][j].b;
		}
	}

	altura/=zoomout;
	largura/=zoomout;

	saida(red);
}

void escolha_rotacao(RGB** img){

	// int graus, sentido;
	printf("----------Menu de Rotacao (sentido)---------\n");
	printf("1 - Horario\n2 - Anti-horario\n");
	printf("Escolha o sentido em que deseja rotacionar a imagem:\n");
	scanf("%d", &sentido);
	while(sentido<1 || sentido>2){
		printf("Por favor selecione uma das opcoes:\n1 - Horario\n2 - Anti-horario\n");
		scanf("%d", &sentido);
	}

	printf("----------Menu de Rotacao (graus)---------\n");
	printf("1 - 90 graus\n2 - 180 graus\n3 - 270 graus\n");
	printf("Digite uma das opcoes em deseja rotacionar a imagem:\n");
	scanf("%d", &graus);
	while(graus<1 || graus>3){
		printf("Por favor selecione uma das opcoes:\n1 - 90 graus\n2 - 180 graus\n3 - 270 graus\n");
		scanf("%d", &graus);
	}
	if(sentido == 1){
		while(graus>=1){
			rotate_horario(img);
			graus--;
		}
	}
	else if(sentido == 2){
		while(graus>=1){
			rotate_antihorario(img);
			graus--;
		}
	}
}

void rotate_horario (RGB** img){
	int i, j;
	RGB** rot;
	rot = malloc(largura*sizeof(RGB));
	for(i = 0; i < largura; i++) {
		rot[i] = malloc(altura*sizeof(RGB));
	}
	// Altera os valores de RGB
	//variaveis altura e largura definidas na função open e criadas no arquivo sruct.h

	// if(graus==1){
		for (i=0; i<altura; i++) {
			for (j=0; j<largura; j++) {
				//gira 90 graus no sentido horario

				rot[i][j].r = img[altura-j-1][i].r;
				rot[i][j].g = img[altura-j-1][i].g;
				rot[i][j].b = img[altura-j-1][i].b;
			}
		}
		for (i=0; i<altura; i++) {
			for (j=0; j<largura; j++) {

				img[i][j].r = rot[i][j].r;
				img[i][j].g = rot[i][j].g;
		 		img[i][j].b = rot[i][j].b;
		 		}
		}
}

void rotate_antihorario (RGB** img){
	int i, j;
	RGB** rot;
	rot = malloc(largura*sizeof(RGB));
	for(i = 0; i < largura; i++) {
		rot[i] = malloc(altura*sizeof(RGB));
	}
	// Altera os valores de RGB
	//variaveis altura e largura definidas na função open e criadas no arquivo sruct.h

	// if(graus==1){
		for (i=0; i<altura; i++) {
			for (j=0; j<largura; j++) {
				//gira 90 graus no sentido horario

				rot[i][j].r = img[j][altura-i-1].r;
				rot[i][j].g = img[j][altura-i-1].g;
				rot[i][j].b = img[j][altura-i-1].b;
			}
		}
		for (i=0; i<altura; i++) {
			for (j=0; j<largura; j++) {

				img[i][j].r = rot[i][j].r;
				img[i][j].g = rot[i][j].g;
		 		img[i][j].b = rot[i][j].b;
		 		}
		}
}
void blurring (RGB** img){

	int l, c;
	RGB** blu;
	blu = malloc(altura*sizeof(RGB));
	for(l = 0; l < altura; l++) {
		blu[l] = malloc(largura*sizeof(RGB));
	}

	//Para os pixels que não estão na bora, é feita uma média artimética de 9 elementos e aplica-se o valor final no pixel central.
	//No entanto, o pixel central pode estar na borda da imagem, então é verificado cada caso e é feita uma média sem os pixels que ultrapassam essa borda.

	for (l = 0; l < altura; l++){
      for (c = 0; c < largura; c++){
      		//Primeiro pixel da primeira coluna
			if(l==0 && c==0){
				blu[l][c].r=(img[l][c].r+img[l][c+1].r+img[l+1][c].r+img[l+1][c+1].r)/4;
				blu[l][c].g=(img[l][c].g+img[l][c+1].g+img[l+1][c].g+img[l+1][c+1].g)/4;
				blu[l][c].b=(img[l][c].b+img[l][c+1].b+img[l+1][c].b+img[l+1][c+1].b)/4;
			}
			//Último pixel da primeira coluna
			else if(l==altura-1 && c==0){
				blu[l][c].r=(img[l][c].r+img[l-1][c].r+img[l-1][c+1].r+img[l][c+1].r)/4;
				blu[l][c].g=(img[l][c].g+img[l-1][c].g+img[l-1][c+1].g+img[l][c+1].g)/4;
				blu[l][c].b=(img[l][c].b+img[l-1][c].b+img[l-1][c+1].b+img[l][c+1].b)/4;
			}
			//Ultimo pixel da última coluna
			else if(l==altura-1 && c==largura-1){
				blu[l][c].r=(img[l][c].r+img[l-1][c].r+img[l-1][c-1].r+img[l][c-1].r)/4;
				blu[l][c].g=(img[l][c].g+img[l-1][c].g+img[l-1][c-1].g+img[l][c-1].g)/4;
				blu[l][c].b=(img[l][c].b+img[l-1][c].b+img[l-1][c-1].b+img[l][c-1].b)/4;
			}
			//Primeiro pixel da última coluna
			else if(l==0 && c==largura-1){
				blu[l][c].r=(img[l][c].r+img[l][c-1].r+img[l+1][c-1].r+img[l+1][c].r)/4;
				blu[l][c].g=(img[l][c].g+img[l][c-1].g+img[l+1][c-1].g+img[l+1][c].g)/4;
				blu[l][c].b=(img[l][c].b+img[l][c-1].b+img[l+1][c-1].b+img[l+1][c].b)/4;
			}
			//Pixels da primeira linha, mas que não são o primeiro nem o último
			else if(l==0){
				blu[l][c].r=(img[l][c-1].r+img[l][c].r+img[l][c+1].r+img[l+1][c-1].r+img[l+1][c].r+img[l+1][c+1].r)/6;
				blu[l][c].g=(img[l][c-1].g+img[l][c].g+img[l][c+1].g+img[l+1][c-1].g+img[l+1][c].g+img[l+1][c+1].g)/6;
				blu[l][c].b=(img[l][c-1].b+img[l][c].b+img[l][c+1].b+img[l+1][c-1].b+img[l+1][c].b+img[l+1][c+1].b)/6;
			}
			//Pixels da última linha, mas que não são o primeiro nem o último
			else if(l==altura-1){
				blu[l][c].r=(img[l-1][c-1].r+img[l-1][c].r+img[l-1][c+1].r+img[l][c-1].r+img[l][c].r+img[l][c+1].r)/6;
				blu[l][c].g=(img[l-1][c-1].g+img[l-1][c].g+img[l-1][c+1].g+img[l][c-1].g+img[l][c].g+img[l][c+1].g)/6;
				blu[l][c].b=(img[l-1][c-1].b+img[l-1][c].b+img[l-1][c+1].b+img[l][c-1].b+img[l][c].b+img[l][c+1].b)/6;
			}
			//Pixels da primeira coluna, mas que não são o primeiro nem o último
			else if(c==0){
				blu[l][c].r=(img[l-1][c].r+img[l-1][c+1].r+img[l][c].r+img[l][c+1].r+img[l+1][c].r+img[l+1][c+1].r)/6;
				blu[l][c].g=(img[l-1][c].g+img[l-1][c+1].g+img[l][c].g+img[l][c+1].g+img[l+1][c].g+img[l+1][c+1].g)/6;
				blu[l][c].b=(img[l-1][c].b+img[l-1][c+1].b+img[l][c].b+img[l][c+1].b+img[l+1][c].b+img[l+1][c+1].b)/6;
			}
			//Pixels da última coluna, mas que não são o primeiro nem o último
			else if(c==largura-1){
				blu[l][c].r=(img[l-1][c-1].r+img[l-1][c].r+img[l][c-1].r+img[l][c].r+img[l+1][c-1].r+img[l+1][c].r)/6;
				blu[l][c].g=(img[l-1][c-1].g+img[l-1][c].g+img[l][c-1].g+img[l][c].g+img[l+1][c-1].g+img[l+1][c].g)/6;
				blu[l][c].b=(img[l-1][c-1].b+img[l-1][c].b+img[l][c-1].b+img[l][c].b+img[l+1][c-1].b+img[l+1][c].b)/6;
			}
			//Pixels que não estão nas bordas
			else{
				blu[l][c].r=(img[l-1][c-1].r+img[l-1][c].r+img[l-1][c+1].r+img[l][c-1].r+img[l][c].r+img[l][c+1].r+img[l+1][c-1].r+img[l+1][c].r+img[l+1][c+1].r)/9;
				blu[l][c].g=(img[l-1][c-1].g+img[l-1][c].g+img[l-1][c+1].g+img[l][c-1].g+img[l][c].g+img[l][c+1].g+img[l+1][c-1].g+img[l+1][c].g+img[l+1][c+1].g)/9;
				blu[l][c].b=(img[l-1][c-1].b+img[l-1][c].b+img[l-1][c+1].b+img[l][c-1].b+img[l][c].b+img[l][c+1].b+img[l+1][c-1].b+img[l+1][c].b+img[l+1][c+1].b)/9;
			}
		}
	}
		saida(blu);
}

void sharpening (RGB** img){

	int i,j;
	RGB** shar;
	shar = malloc(altura*sizeof(RGB));
	for(i = 0; i < altura; i++) {
		shar[i] = malloc(largura*sizeof(RGB));
	}

	//Para aumentar os detalhes,
	//numa matriz 3x3, são multiplicados por -1 as posições 0x1, 1x0, 2x1 e 1x2 e multiplicado por 5 a posição 1x1.
	//É feita a soma dessas multiplicações e aplica-se no pixel do meio da matriz.
	for (i = 0; i < altura; i++){
		for (j = 0; j < largura; j++){
				shar[i][j] = img[i][j];
		}
	}

	fprintf(imagem, "%s\n", tipo);
	fprintf(imagem, "%d %d\n", altura, largura);
	fprintf(imagem, "%d\n",qualidade);

	for (i = 1; i < altura-1; i++){
  		for (j = 1; j < largura-1; j++){
			img[i][j].r = 5*shar[i][j].r - shar[i-1][j].r - shar[i][j-1].r - shar[i][j+1].r - shar[i+1][j].r;
			img[i][j].g = 5*shar[i][j].g - shar[i-1][j].g - shar[i][j-1].g - shar[i][j+1].g - shar[i+1][j].g;
			img[i][j].b = 5*shar[i][j].b - shar[i-1][j].b - shar[i][j-1].b - shar[i][j+1].b - shar[i+1][j].b;
    	}
	}
	saida(shar);
}

void border (RGB** img){


    /* Detecção de borda.
     Pixels nos quais há uma mudança brusca na intensidade
     Nesse filtro, em uma matriz 3x3, são multiplicados por 1 como as posições 0x1, 1x0, 2x1 e 1x2 e multiplicados por -4 a posição ixj.
    (1x1).
     Matriz bor salva a imagem.
    */

	int i,j;
	RGB** bor;
	bor = malloc(altura*sizeof(RGB));
	for(i = 0; i < altura; i++) {
		bor[i] = malloc(largura*sizeof(RGB));
	}

	for(i=0; i < altura; i++){
		for(j=0; j  < largura; j++){
			/* Primeiro pixel da primeira coluna. */
			if (i == 0 && j == 0 ) {
				bor[i][j].r = img[i][j].r*(-4)+img[i][j+1].r*(1)+img[i+1][j].r*(1);
				bor[i][j].g = img[i][j].g*(-4)+img[i][j+1].g*(1)+img[i+1][j].g*(1);
				bor[i][j].b = img[i][j].b*(-4)+img[i][j+1].b*(1)+img[i+1][j].b*(1);
			}
			/* Último pixel da primeira coluna. */
			else  if (i == altura - 1 && j == 0 ) {
				bor[i][j].r = img[i-1][j].r*(1)+img[i][j].r*(-4)+img[i][j+1].r*(1);
				bor[i][j].g = img[i-1][j].g*(1)+img[i][j].g*(-4)+img[i][j+1].g*(1);
				bor[i][j].b = img[i-1][j].b*(1)+img[i][j].b*(-4)+img[i][j+1].b*(1);
			}
			/* Último pixel da última coluna. */
			else  if (i == altura - 1 && j == largura - 1 ) {
				bor[i][j].r = img[i-1][j].r*(1)+img[i][j-1].r*(1)+img[i][j].r*(-4);
				bor[i][j].g = img[i-1][j].g*(1)+img[i][j-1].g*(1)+img[i][j].g*(-4);
				bor[i][j].b = img[i-1][j].b*(1)+img[i][j-1].b*(1)+img[i][j].b*(-4);
			}
			/* Primeiro pixel da última coluna. */
			else  if (i == 0 && j == largura- 1 ) {
				bor[i][j].r = img[i][j-1].r*(1)+img[i][j].r*(-4)+img[i+1][j].r*(1);
				bor[i][j].g = img[i][j-1].g*(1)+img[i][j].g*(-4)+img[i+1][j].g*(1);
				bor[i][j].b = img[i][j-1].b*(1)+img[i][j].b*(-4)+img[i+1][j].b*(1);
			}
			/*  Pixels da primeira linha, mas que não são o primeiro ou o último elemento. */
			else  if (i == 0 ) {
				bor[i][j].r = img[i][j-1].r*(1)+img[i][j].r*(-4)+img[i][j+1].r*(1)+img[i+1][j].r*(1);
				bor[i][j].g = img[i][j-1].g*(1)+img[i][j].g*(-4)+img[i][j+1].g*(1)+img[i+1][j].g*(1);
				bor[i][j].b = img[i][j-1].b*(1)+img[i][j].b*(-4)+img[i][j+1].b*(1)+img[i+1][j].b*(1);
			}
			/* Pixels da última linha, mas que não são o primeiro ou o último elemento. */
			else  if (i == altura- 1 ) {
				bor[i][j].r = img[i-1][j].r*(1)+img[i][j-1].r*(1)+img[i][j].r*(-4)+img[i][j+1].r*(1);
				bor[i][j].g = img[i-1][j].g*(1)+img[i][j-1].g*(1)+img[i][j].g*(-4)+img[i][j+1].g*(1);
				bor[i][j].b = img[i-1][j].b*(1)+img[i][j-1].b*(1)+img[i][j].b*(-4)+img[i][j+1].b*(1);
			}
			/*  Pixels da primeira coluna, mas que não são o primeiro ou o último elemento. */
			else if (j == 0 ) {
				bor[i][j].r = img[i-1][j].r*(1)+img[i][j].r*(-4)+img[i][j+1].r*(1)+img[i+1][j].r*(1);
				bor[i][j].g = img[i-1][j].g*(1)+img[i][j].g*(-4)+img[i][j+1].g*(1)+img[i+1][j].g*(1);
				bor[i][j].b = img[i-1][j].b*(1)+img[i][j].b*(-4)+img[i][j+1].b*(1)+img[i+1][j].b*(1);
			}
			/* Pixels da última vez, mas que não são o primeiro o último elemento. */
			else if (j == largura- 1 ) {
				bor[i][j].r = img[i-1][j].r*(1)+img[i][j-1].r*(1)+img[i][j].r*(-4)+img[i+1][j].r*(1);
				bor[i][j].g = img[i-1][j].g*(1)+img[i][j-1].g*(1)+img[i][j].g*(-4)+img[i+1][j].g*(1);
				bor[i][j].b = img[i-1][j].b*(1)+img[i][j-1].b*(1)+img[i][j].b*(-4)+img[i+1][j].b*(1);
			}
			/*  Pixels que não estão na borda da imagem. */
			else {
				bor[i][j].r = img[i-1][j].r*(1)+img[i][j-1].r*(1)+img[i][j].r*(-4)+img[i][j+1].r*(1)+img[i+1][j].r*(1);
				bor[i][j].g = img[i-1][j].g*(1)+img[i][j-1].g*(1)+img[i][j].g*(-4)+img[i][j+1].g*(1)+img[i+1][j].g*(1);
				bor[i][j].b = img[i-1][j].b*(1)+img[i][j-1].b*(1)+img[i][j].b*(-4)+img[i][j+1].b*(1)+img[i+1][j].b*(1);
			}
			/* Caso o resultado da soma ultrapasse os valores entre 0 e 255, estabelece o maior valor possivel. */

			if (bor[i][j].r > 255 ){
				bor[i][j].r = 255 ;
			}

			if (bor[i][j].r < 0 ){
				bor [i][j].r = 0 ;
			}

			if (bor[i][j].g > 255 ){
				bor[i][j].g = 255 ;
			}

			if (bor[i][j].g < 0 ){
				bor[i][j].g = 0 ;
			}

			if (bor[i][j].b > 255){
				bor[i][j].b = 255 ;
			}

			if (bor[i][j].b < 0 ){
				bor[i][j].b = 0 ;
			}

		}

	}

	saida(bor);

}
