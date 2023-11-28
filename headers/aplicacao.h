#ifndef APLICACAO_H
#define APLICACAO_H

#include <stdbool.h>

#define MSG_SIZE 256

void AplicacaoTransmissora();
void CamadaDeAplicacaoTransmissora(char *mensagem);
void CamadaEnlaceDadosTransmissora(bool *quadro, int tam_quadro);

#endif