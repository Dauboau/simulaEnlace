#ifndef ENLACE_H
#define ENLACE_H

#include <stdbool.h>

void MeioDeComunicacao(bool *fluxoBrutoDeBits, int tam_quadro, int tipo_controle);
void CamadaEnlaceDadosReceptora(bool *quadro, int tam_quadro, int tipo_controle);

#endif