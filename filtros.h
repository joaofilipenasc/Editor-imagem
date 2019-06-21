#include "struct.h"

#ifndef filtros_h
#define filtros_h

void read (RGB** img);

void comandos (RGB** img);

void grayscale (RGB** img);

void enlarge (RGB** img);

void rotate_horario (RGB** img);

void rotate_antihorario (RGB** img);

void escolha_rotacao(RGB** img);

void reduce (RGB** img);

void blurring (RGB** img);

void sharpening (RGB** img);

void border (RGB** img);

#endif
