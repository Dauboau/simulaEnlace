#include "../headers/aplicacao.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void AplicacaoTransmissora() {

    //aloca espaço para mensagem
    char* mensagem;
    mensagem = (char *) malloc(sizeof(char)*MSG_SIZE);

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
    quadro = (bool *) malloc(sizeof(bool)*(strlen(mensagem)-1)*8); //essa alocação ta certa?

    char aux_char;
    char *mensagem_aux_ptr = mensagem;

    //convertendo a mensagem em um array de bits (zeros e uns)
    for (size_t i = 0; i < strlen(mensagem)-1; i++) {
        
        aux_char = *mensagem_aux_ptr;
        
        //converte um caractere
        for (int j = 0; j < 8; j++) 
            quadro[i*8 + j] = ((aux_char >> (7-j)) & 1);

        mensagem_aux_ptr++;

    }

    CamadaEnlaceDadosTransmissora(quadro, (strlen(mensagem)-1)*8);

    free(quadro);

}