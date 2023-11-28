#include "../headers/aplicacao.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void AplicacaoTransmissora() {

    //aloca espaço para mensagem
    char* mensagem;
    mensagem = malloc(sizeof(char)*MSG_SIZE);

    //lê a mesnagem digitada pelo usuário
    printf("Digite uma mensagem:\n");
    fgets(mensagem, MSG_SIZE, stdin);

    CamadaDeAplicacaoTransmissora(mensagem);

    //libera o espaço de memória
    free(mensagem);

}

void CamadaDeAplicacaoTransmissora(char *mensagem) {

    //alocando espaço para a variável onde savalremos os bits da mensagem
    bool *quadro;
    quadro = malloc(sizeof(bool)*strlen(mensagem)*8); //essa alocação ta certa?

    char aux_char;

    //convertendo a mensagem em um array de bits (zeros e uns)
    for (size_t i = 0; i < strlen(mensagem); i++) {
        
        aux_char = *mensagem;
        
        //converte um caractere
        for (int j = 7; j >= 0; --j) 
            quadro[i*8 + j] = ((aux_char >> j) & 1);

        mensagem++;

    }

    CamadaEnlaceDadosTransmissora(quadro, strlen(mensagem)*8);

    free(quadro);

}