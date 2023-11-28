#ifndef ENLACE_H
#define ENLACE_H

#include <stdbool.h>

void CamadaEnlaceDadosTransmissora(bool *quadro, int tam_quadro);
void CamadaEnlaceDadosTransmissoraControleDeErro(bool *quadro, int tam_quadro);
void CamadaEnlaceDadosTransmissoraControleDeErroBitParidadePar(bool *quadro, int tam_quadro);
void CamadaEnlaceDadosTransmissoraControleDeErroBitParidadeImpar(bool *quadro, int tam_quadro);
void CamadaEnlaceDadosTransmissoraControleDeErroCRC(bool *quadro, int tam_quadro);

#endif