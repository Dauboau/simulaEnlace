#include "../headers/enlace.h"
#include <stdio.h>
#include <stdlib.h>

void CamadaEnlaceDadosTransmissora(bool *quadro, int tam_quadro) {

    printf("Iniciando camada de enlace transmissora...\n");

    CamadaEnlaceDadosTransmissoraControleDeErro(quadro, tam_quadro);

}

void CamadaEnlaceDadosReceptora(bool *quadro, int tam_quadro, int tipo_controle) {

    printf("Iniciando camada de enlace receptora...\n");

    CamadaEnlaceDadosReceptoraControleDeErro(quadro, tam_quadro, tipo_controle);

}

void CamadaEnlaceDadosTransmissoraControleDeErro(bool *quadro, int tam_quadro) {

    printf("Iniciando controle de erros da camada de enlace transmissora...\n");

    int tipo_controle; // Ecolhercom base no tipo de teste que se deseja realiazar

    //lê o tipo de controle desejado
    printf("Escolha um tipo de controle de erro:\n");
    printf("0 - Paridade par\n");
    printf("1 - Paridade impar\n");
    printf("2 - CRC32\n");

    scanf("%d", &tipo_controle);

    //realiza a chamada da função responsável pelo método de controle escolhido
    switch (tipo_controle) {

    case 0:

        CamadaEnlaceDadosTransmissoraControleDeErroBitParidadePar(quadro, tam_quadro, tipo_controle);
        break;

    case 1:

        CamadaEnlaceDadosTransmissoraControleDeErroBitParidadeImpar(quadro, tam_quadro, tipo_controle);
        break;
    
    case 2:
    
        CamadaEnlaceDadosTransmissoraControleDeErroCRC(quadro, tam_quadro, tipo_controle);
        break;

    default:

        printf("Comando inválido!\n");
        exit(EXIT_FAILURE);
    
    }

}

void CamadaEnlaceDadosReceptoraControleDeErro(bool *quadro, int tam_quadro, int tipo_controle) {

    printf("Iniciando controle de erros da camada de enlace receptora...\n");

    switch (tipo_controle) {

    case 0:

        CamadaEnlaceDadosReceptoraControleDeErroBitParidadePar(quadro, tam_quadro);
        break;

    case 1:

        CamadaEnlaceDadosReceptoraControleDeErroBitParidadeImpar(quadro, tam_quadro);
        break;
    
    case 2:
    
        CamadaEnlaceDadosReceptoraControleDeErroCRC(quadro, tam_quadro);
        break;
    
    }

}

void CamadaEnlaceDadosTransmissoraControleDeErroBitParidadePar(bool *quadro, int tam_quadro, int tipo_controle) {

    //alocação de memória para armazenar o quadro codificado
    bool *quadro_cod;
    quadro_cod = malloc(sizeof(bool)*(tam_quadro +1));

    //variável para armazenar o bit de pariade
    bool paridade = false;


    //calculo de paridade e cópia do quadro para o quadro codificado
    for (size_t i = 0; i < tam_quadro; i++) {

        //verifica se o bit é 1 para alterar a paridade
        if(quadro[i])
            paridade = !paridade;

        quadro_cod[i] = quadro[i]; 

    }
    
    //adição do bit de paridade ao final do qaudro codificado
    quadro_cod[tam_quadro] = paridade;

    //imprime o quadro
    printf("Quadro a ser enviado:\t");
    for(int i = 0; i < tam_quadro; i++){
        if(quadro_cod[i])
            printf("1");
        else
            printf("0");
    }
    printf("\n");

    //imprime o bit de paridade
    printf("Bit de paridade:\t%c\n", (quadro_cod[tam_quadro] ? '1' : '0'));

    //realiza o envio dos bits
    MeioDeComunicacao(quadro_cod, tam_quadro+1, tipo_controle);

    free(quadro_cod);

}

void CamadaEnlaceDadosTransmissoraControleDeErroBitParidadeImpar(bool *quadro, int tam_quadro, int tipo_controle) {

    //alocação de memória para armazenar o quadro codificado
    bool *quadro_cod;
    quadro_cod = malloc(sizeof(bool)*(tam_quadro +1));

    //variável para armazenar o bit de pariade
    bool paridade = true;


    //calculo de paridade e cópia do quadro para o quadro codificado
    for (size_t i = 0; i < tam_quadro; i++) {

        //verifica se o bit é 1 para alterar a paridade
        if(quadro[i])
            paridade = !paridade;

        quadro_cod[i] = quadro[i]; 

    }
    
    //adição do bit de paridade ao final do quadro codificado
    quadro_cod[tam_quadro] = paridade;

    //imprime o quadro
    printf("Quadro a ser enviado:\t");
    for(int i = 0; i < tam_quadro; i++){
        if(quadro_cod[i])
            printf("1");
        else
            printf("0");
    }
    printf("\n");

    //imprime o bit de paridade
    printf("Bit de paridade:\t%c\n", (quadro_cod[tam_quadro] ? '1' : '0'));

    //realiza o envio dos bits
    MeioDeComunicacao(quadro_cod, tam_quadro+1, tipo_controle);

    free(quadro_cod);

}

void CamadaEnlaceDadosTransmissoraControleDeErroCRC(bool *quadro, int tam_quadro, int tipo_controle) {

    printf("Iniciando checagem CRC32\n");

    //  x32 + x26 + x23 + x22 + x16 + x12 + x11 + x10 + x8 + x7 + x5 + x4 + x2 + x + 1
    //  1 0000 0100 1100 0001 0001 1101 1011 0111
    const bool polinomio[CRC_32_LENGTH] = { 1,
                                            0, 0, 0, 0, 
                                            0, 1, 0, 0, 
                                            1, 1, 0, 0, 
                                            0, 0, 0, 1, 
                                            0, 0, 0, 1, 
                                            1, 1, 0, 1, 
                                            1, 0, 1, 1, 
                                            0, 1, 1, 1};

    bool *quadro_crc;
    int tam_quadro_crc = tam_quadro + CRC_32_LENGTH-1;
    quadro_crc = (bool *) calloc(tam_quadro_crc, sizeof(bool)); 

    for (size_t i = 0; i < tam_quadro; i++) {
        quadro_crc[i] = quadro[i];
    }

    for (size_t i = 0; i < tam_quadro; i++) {
        
        if(quadro_crc[i]) {

            //Faz o XOR com todos os elementos do polinomio
            for (size_t j = 0; j < CRC_32_LENGTH; j++)
                quadro_crc[i+j] ^= polinomio[j];
                            
        }

    }

    //copia novamente a mensagem para o inicio do quadro
    for (size_t i = 0; i < tam_quadro; i++) {
        quadro_crc[i] = quadro[i];
    }

    //imprime o quadro
    printf("Quadro enviado:\t");
    for(int i = 0; i < tam_quadro; i++){
        if(quadro_crc[i])
            printf("1");
        else
            printf("0");
    }
    printf("\n");

    printf("CRC32:\t");
    for(int i = tam_quadro; i < tam_quadro_crc; i++){
        if(quadro_crc[i])
            printf("1");
        else
            printf("0");
    }
    printf("\n");

    //realiza o envio dos bits
    MeioDeComunicacao(quadro_crc, tam_quadro_crc, tipo_controle);

    free(quadro_crc);

}

void CamadaEnlaceDadosReceptoraControleDeErroBitParidadePar(bool *quadro, int tam_quadro) {

    //alocação de memória para armazenar o quadro codificado
    bool *quadro_decod;
    quadro_decod = malloc(sizeof(bool)*(tam_quadro +1));

    //variável para armazenar o bit de pariade
    bool paridade = false;

    //calculo de paridade e cópia do quadro para o quadro codificado
    for (size_t i = 0; i < tam_quadro; i++) {

        //verifica se o bit é 1 para alterar a paridade
        if(quadro[i])
            paridade = !paridade;

        quadro_decod[i] = quadro[i]; 

    }
    
    //verifica se o bit de paridade corresponde ao valor esperado
    if(quadro_decod[tam_quadro-1] != paridade){

        printf("A mensagem apresentou um erro! Fechando aplicacao...");
        exit(EXIT_FAILURE);

    }

    //imprime o quadro
    printf("Quadro recebido:\t");
    for(int i = 0; i < tam_quadro; i++){
        if(quadro_decod[i])
            printf("1");
        else
            printf("0");
    }
    printf("\n");

    //imprime o bit de paridade
    printf("Bit de paridade:\t%c\n", (quadro_decod[tam_quadro-1] ? '1' : '0'));

    //envia a mensagem para a camada de aplicação
    CamadaDeAplicacaoReceptora(quadro_decod, tam_quadro-1);

    free(quadro_decod);

}

void CamadaEnlaceDadosReceptoraControleDeErroBitParidadeImpar(bool *quadro, int tam_quadro) {

    //alocação de memória para armazenar o quadro codificado
    bool *quadro_decod;
    quadro_decod = malloc(sizeof(bool)*(tam_quadro +1));

    //variável para armazenar o bit de pariade
    bool paridade = true;


    //calculo de paridade e cópia do quadro para o quadro codificado
    for (size_t i = 0; i < tam_quadro; i++) {

        //verifica se o bit é 1 para alterar a paridade
        if(quadro[i])
            paridade = !paridade;

        quadro_decod[i] = quadro[i]; 

    }
    
    //verifica se o bit de paridade corresponde ao valor esperado
    if(quadro_decod[tam_quadro-1] != paridade){

        printf("A mensagem apresentou um erro! Fechando aplicacao...");
        exit(EXIT_FAILURE);

    }

    //imprime o quadro
    printf("Quadro recebido:\t");
    for(int i = 0; i < tam_quadro; i++){
        if(quadro_decod[i])
            printf("1");
        else
            printf("0");
    }
    printf("\n");

    //imprime o bit de paridade
    printf("Bit de paridade:\t%c\n", (quadro_decod[tam_quadro-1] ? '1' : '0'));

    //envia a mensagem para a camada de aplicação
    CamadaDeAplicacaoReceptora(quadro_decod, tam_quadro-1);

    free(quadro_decod);

}

void CamadaEnlaceDadosReceptoraControleDeErroCRC(bool *quadro, int tam_quadro) {

    printf("Iniciando checagem CRC32\n");

    //  x32 + x26 + x23 + x22 + x16 + x12 + x11 + x10 + x8 + x7 + x5 + x4 + x2 + x + 1
    //  1 0000 0100 1100 0001 0001 1101 1011 0111
    const bool polinomio[CRC_32_LENGTH] = { 1,
                                            0, 0, 0, 0, 
                                            0, 1, 0, 0, 
                                            1, 1, 0, 0, 
                                            0, 0, 0, 1, 
                                            0, 0, 0, 1, 
                                            1, 1, 0, 1, 
                                            1, 0, 1, 1, 
                                            0, 1, 1, 1};

    bool *quadro_crc;
    int tam_quadro_crc = tam_quadro + CRC_32_LENGTH-1;
    quadro_crc = (bool *) calloc(tam_quadro_crc, sizeof(bool)); 

    bool *quadro_decod;
    int tam_quadro_decod = tam_quadro - CRC_32_LENGTH+1;
    quadro_decod = (bool *) calloc(tam_quadro_decod, sizeof(bool)); 

    for (size_t i = 0; i < tam_quadro; i++) {
        
        if(quadro_crc[i]) {

            //Faz o XOR com todos os elementos do polinomio
            for (size_t j = 0; j < CRC_32_LENGTH; j++) 
                quadro_crc[i+j] ^= polinomio[j];

        }

    }

    bool quadro_valido = true;

    //verifica se o resto da operação é zero
    for (size_t i = 0; i < tam_quadro_crc; i++) {
        
        //se qualquer um dos bits der 1 ele marca o quadro como inválido
        if(quadro_crc[i])
            quadro_valido = false;
        
    }

    if(!quadro_valido) {

        printf("A mensagem apresentou um erro! Fechando aplicacao...");
        exit(EXIT_FAILURE);

    }else {

        for (size_t i = 0; i < tam_quadro_decod; i++) 
            quadro_decod[i] = quadro[i];

    }    

    //imprime o quadro
    printf("Quadro recebido: \n");
    for(int i = 0; i < tam_quadro_decod; i++){
        if(quadro_decod[i])
            printf("1");
        else
            printf("0");
    }
    printf("\n");

    //chama camada de aplicação
    CamadaDeAplicacaoReceptora(quadro_decod, tam_quadro_decod);

    free(quadro_crc);
    free(quadro_decod);

}
