#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "struct.h"
#include "filtros.h"


void desalocar(RGB** img){

	int i;
	for(i = largura - 1; i >= 0; i--) {
	 	free(img[i]);
	 }

	 free(img);

}

//Função de abertura do arquivo.
void inicio(){

	printf("Seja bem-vindo(a) ao editor!\n");
	printf("Digite o nome da imagem a ser alterada com a extensao:\n");

	//variaveis indicadas no arquivo struct.h ( nome_da imagem, File *imagem, altura, largura, qualidade)
	scanf("%s", nome_da_imagem);


	//verifica se possui algum arquivo com o nome digitado, e caso seja verdadeiro abertura no modo leitura.
	if ((imagem = fopen(nome_da_imagem, "r")) == NULL) {
		printf("Erro ao abrir o arquivo. %s\n", nome_da_imagem);
		//não encnotrando o respctivo nome o programa é encerrado
		exit(1);
    }
    //identificação do tipo, atura, largura e qualidade.
	fscanf(imagem, "%s %d %d %d", tipo, &largura, &altura, &qualidade);
	//Linha abaixo demonstra os valores encontrados na imagem
	printf("tipo: %s\naltura:%d\nlargura: %d\nqualidade: %d\n", tipo, altura, largura, qualidade);

	//backup dos valores
	altura_s = altura;
	largura_s = largura;
}

//função de leitura da imagem, em que faz a leitura das cores de acordo com o RGB.
void read(RGB** img) {
	int i;
	int j;
	for (i=0; i<altura; i++){
		for (j=0; j<largura; j++) {
			fscanf(imagem, "%d", &img[i][j].r);
			fscanf(imagem, "%d", &img[i][j].g);
			fscanf(imagem, "%d", &img[i][j].b);
		}
	}
}

void pular_comentario(RGB** img) {

	char buffer = fgetc(imagem);

	do {
		if(buffer == '#')
			while(buffer != '\n')
				buffer = fgetc(imagem);
			else
				ungetc(buffer, imagem);
				buffer = fgetc(imagem);

	}while(buffer == '#');

	ungetc(buffer, imagem);
}

void comandos (RGB** img){
	printf("****************FILTROS******************\n");
	printf("1 - Grayscale\n");
	printf("2 - Enlarge\n");
	printf("3 - Rotate\n");
	printf("4 - Reduce \n");
	printf("5 - Blurring\n");
 	printf("6 - Sharpening\n");
 	printf("7 - Border\n");
 	printf("8 - FIM\n");

	printf("Digite o número do filtro que deseja utilizar:\n");
	int numero;
	scanf("%d", &numero);

 	while(numero < 1 || numero > 8){
 		printf("Infelizmente não encontramos o filtro desejado. \nEscolha novamente, digite o número do filtro que deseja utilizar:\n");
		scanf("%d", &numero);
 	}

	if(numero == Grayscale){
 		grayscale(img);
		saida(img);
		printf("Imagem gerada com sucesso, acesse a pasta do programa.\n");
		exit(1);
 	}
 	if(numero == Enlarge){
 		enlarge(img);
		printf("Imagem gerada com sucesso, acesse a pasta do programa.\n");
		exit(1);
 	}
 	if(numero == Rotate){
 		escolha_rotacao(img);
 		// rotate(img);
 		saida(img);
 		printf("Imagem gerada com sucesso, acesse a pasta do programa.\n");
		exit(1);
 	}
 	if(numero == Reduce){
 		reduce(img);
		printf("Imagem gerada com sucesso, acesse a pasta do programa.\n");
		exit(1);
 	}
 	if(numero == Blurring){
		blurring(img);
 		printf("Imagem gerada com sucesso, acesse a pasta do programa.\n");
 		exit(1);
 	}
 	if(numero == Sharpening){
		sharpening(img);
 		printf("Imagem gerada com sucesso, acesse a pasta do programa.\n");
 		exit(1);
 	}
 	if(numero == Border){
 		border(img);
 		printf("Imagem gerada com sucesso, acesse a pasta do programa.\n");
 		exit(1);
 		//printf("Filtro ainda nao implementado\n");
 		//comandos(img);
 	}
 	if(numero == Fim){
 		printf("Programa finalizado com sucesso.\n");
 		exit(1);
 	}
 }


void saida(RGB** img) {

	int i, j;
	//Criação do arquivo Saida
	FILE *saida;
	//abertura do arquivo saida no modo escrita
	saida = fopen("editada.ppm", "w");
	//definição do tipo, altura, largura e qualidade.
	fprintf(saida, "%s\n %d %d\n %d\n", tipo, largura, altura, qualidade);

	//definição da imagem de saida usando RGB, com base nos valores referenciados nos filtros.
	for(i=0; i<altura; i++){
		for(j=0; j<largura; j++) {
			fprintf(saida, "%d %d %d\n", img[i][j].r, img[i][j].g, img[i][j].b);
		}
	}
	//Fechando o arquivo saída
	fclose(saida);

	//valores restaurados conforme o backup
	altura = altura_s;
	largura = largura_s;
	//fechando o arquivo imagem aberto na função open
	fclose(imagem);
}
