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

    //transmite a mensagem
    CamadaDeAplicacaoTransmissora(mensagem);

    //libera o espaço de memória
    free(mensagem);

}

void AplicacaoReceptora(char *mensagem) {

    //imprime a mensagem recebida
    printf("Mensagem recebida: \n%s\n", mensagem);

}

void CamadaDeAplicacaoTransmissora(char *mensagem) {

    printf("Iniciando camada de aplicacao transmissora...\n");

    //alocando espaço para a variável onde savalremos os bits da mensagem
    bool *quadro;
    quadro = (bool *) malloc(sizeof(bool)*(strlen(mensagem)-1)*8); //essa alocação ta certa?

    //declaração de variáveis auxiliares
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

    //chama a camada de enlace
    CamadaEnlaceDadosTransmissora(quadro, (strlen(mensagem)-1)*8);
    
    free(quadro);

}

void CamadaDeAplicacaoReceptora(bool *quadro, int tam_quadro) {

    printf("Iniciando camada de aplicacao receptora...\n");

    //aloca espaço para mensagem
    char* mensagem;
    mensagem = (char *) calloc(MSG_SIZE, sizeof(char));

    //declaração da variável auxiliar
    char *mensagem_aux_ptr = mensagem;

    //convertendo a mensagem em um array de bits (zeros e uns)
    for (size_t i = 0; i < tam_quadro/8; i++) {
        
        //converte um caractere
        for (int j = 0; j < 8; j++) 
            mensagem_aux_ptr[i] += (quadro[i*8 + j] << (7-j));

    }

    //chama a camada de aplicação que irá exibir a mensagem decodificada
    AplicacaoReceptora(mensagem);

    free(mensagem);

}
