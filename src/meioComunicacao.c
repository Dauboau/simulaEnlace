#include "../headers/meioComunicacao.h"
#include <stdio.h>
#include <stdlib.h>

void MeioDeComunicacao(bool *fluxoBrutoDeBits, int tam_quadro) {

    printf("Iniciando a transmisao do ponto A para o ponto B...\n");
    int erro = 0;
    int *fluxoBrutoDeBitsPontoB;

    fluxoBrutoDeBitsPontoB = (int *)malloc(sizeof(int) * tam_quadro);

    for (int i = 0; i < tam_quadro; i++)
    {

        if ((rand() % 100 + 1) >= erro)
        {
            fluxoBrutoDeBitsPontoB[i] = fluxoBrutoDeBits[i];
        }
        else
        {
            fluxoBrutoDeBitsPontoB[i] = fluxoBrutoDeBits[i] == 0 ? 1 : 0;
        }
    }

    //chamar a camada de enlace da aplicação receptora

    free(fluxoBrutoDeBitsPontoB);
    fluxoBrutoDeBits = fluxoBrutoDeBitsPontoB;
}