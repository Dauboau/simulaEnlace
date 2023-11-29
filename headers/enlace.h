#ifndef ENLACE_H
#define ENLACE_H

#include <stdbool.h>

#define CRC_32_LENGTH 33

void CamadaEnlaceDadosTransmissora(bool *quadro, int tam_quadro);
void CamadaEnlaceDadosTransmissoraControleDeErro(bool *quadro, int tam_quadro);
void CamadaEnlaceDadosTransmissoraControleDeErroBitParidadePar(bool *quadro, int tam_quadro, int tipo_controle);
void CamadaEnlaceDadosTransmissoraControleDeErroBitParidadeImpar(bool *quadro, int tam_quadro, int tipo_controle);
void CamadaEnlaceDadosTransmissoraControleDeErroCRC(bool *quadro, int tam_quadro, int tipo_controle);

void CamadaEnlaceDadosReceptora(bool *quadro, int tam_quadro, int tipo_controle);
void CamadaEnlaceDadosReceptoraControleDeErro(bool *quadro, int tam_quadro, int tipo_controle);
void CamadaEnlaceDadosReceptoraControleDeErroBitParidadePar(bool *quadro, int tam_quadro);
void CamadaEnlaceDadosReceptoraControleDeErroBitParidadeImpar(bool *quadro, int tam_quadro);
void CamadaEnlaceDadosReceptoraControleDeErroCRC(bool *quadro, int tam_quadro);

void MeioDeComunicacao(bool *fluxoBrutoDeBits, int tam_quadro, int tipo_controle);
void CamadaDeAplicacaoReceptora(bool *quadro, int tam_quadro);

#endif