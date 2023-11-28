#include "../headers/enlace.h"
#include <stdio.h>
#include <stdlib.h>

void CamadaEnlaceDadosTransmissora(bool *quadro, int tam_quadro) {

    printf("Iniciando camada de enlace transmissora...\n");

    CamadaEnlaceDadosTransmissoraControleDeErro(quadro, tam_quadro);

}

void CamadaEnlaceDadosTransmissoraControleDeErro(bool *quadro, int tam_quadro) {

    printf("Iniciando controle de erros da camada de enlace transmissora...\n");

    int tipoDeControleDeErro = 2; // Ecolhercom base no tipo de teste que se deseja realiazar

    switch (tipoDeControleDeErro) {

    case 0:

        CamadaEnlaceDadosTransmissoraControleDeErroBitParidadePar(quadro, tam_quadro);
        break;

    case 1:

        CamadaEnlaceDadosTransmissoraControleDeErroBitParidadeImpar(quadro, tam_quadro);
        break;
    
    case 2:
    
        CamadaEnlaceDadosTransmissoraControleDeErroCRC(quadro, tam_quadro);
        break;
    
    }

}

void CamadaEnlaceDadosTransmissoraControleDeErroBitParidadePar(bool *quadro, int tam_quadro) {

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

    free(quadro_cod);

}

void CamadaEnlaceDadosTransmissoraControleDeErroBitParidadeImpar(bool *quadro, int tam_quadro) {

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
    
    //adição do bit de paridade ao final do qaudro codificado
    quadro_cod[tam_quadro] = paridade;

    free(quadro_cod);

}

void CamadaEnlaceDadosTransmissoraControleDeErroCRC(bool *quadro, int tam_quadro) {

    printf("Iniciando checagem CRC32\n");

    // x32 + x26 + x23 + x22 + x16 + x12 + x11 + x10 + x8 + x7 + x5 + x4 + x2 + x + 1
    // 1 0000 0100 1100 0001 0001 1101 1011 0111
    //const bool polinomio[CRC_32_LENGTH] = { 1,
    //                                        0, 0, 0, 0, 
    //                                        0, 1, 0, 0, 
    //                                        1, 1, 0, 0, 
    //                                        0, 0, 0, 1, 
    //                                        0, 0, 0, 1, 
    //                                        1, 1, 0, 1, 
    //                                        1, 0, 1, 1, 
    //                                        0, 1, 1, 1};

    const bool quadro_teste[9] = {1, 1, 1, 1, 0, 0, 1, 0, 1 };
    int tam_quadro_teste = 9;
    const bool polinomio[6] = {1, 0, 1, 1, 0, 1};

    bool *quadro_crc;
    int tam_quadro_crc = tam_quadro_teste + 5;
    quadro_crc = (bool *) calloc(tam_quadro_crc, sizeof(bool)); 

    //for (size_t i = 0; i < tam_quadro_teste; i++) {
    //    quadro_crc[i] = quadro_teste[i];
    //}

    for (size_t i = 0; i < tam_quadro_teste; i++) {
        quadro_crc[i] = quadro_teste[i];
    }

    for (size_t i = 0; i < tam_quadro_teste; i++) {
        
        if(quadro_crc[i]) {

            //Faz o XOR com todos os elementos do polinomio
            for (size_t j = 0; j < 6; j++) 
                quadro_crc[i+j] ^= polinomio[j];

        }

    }

    for (size_t i = 0; i < tam_quadro_teste; i++) {
        quadro_crc[i] = quadro_teste[i];
    }

    for(int i = 0; i<tam_quadro_teste; i++){
        if(quadro_crc[i])
            printf("1");
        else
            printf("0");
    }
    printf("|");

    for(int i = tam_quadro_teste; i<tam_quadro_crc; i++){
        if(quadro_crc[i])
            printf("1");
        else
            printf("0");
    }
    printf("\n");

    //==========================================================================
    for (size_t i = 0; i < tam_quadro_teste; i++) {
        
        if(quadro_crc[i]) {

            //Faz o XOR com todos os elementos do polinomio
            for (size_t j = 0; j < 6; j++) 
                quadro_crc[i+j] ^= polinomio[j];

        }

    }

    for(int i = 0; i<tam_quadro_teste; i++){
        if(quadro_crc[i])
            printf("1");
        else
            printf("0");
    }
    printf("|");

    for(int i = tam_quadro_teste; i<tam_quadro_crc; i++){
        if(quadro_crc[i])
            printf("1");
        else
            printf("0");
    }

    //bool *quadro_crc;
    //int tam_quadro_crc = tam_quadro + 32;

    //quadro_crc = (bool *) calloc(tam_quadro_crc, sizeof(bool));   
//
    //for (size_t i = 0; i < tam_quadro; i++) {
    //    quadro_crc[i] = quadro[i];
    //}
//
    //for (size_t i = 0; i < tam_quadro; i++) {
    //    
    //    //if(quadro_crc[i]) {
//
    //        //Faz o XOR com todos os elementos do polinomio
    //        for (size_t j = 0; j < tam_quadro; j++) 
    //            quadro_crc[i+j] ^= polinomio[j];
//
    //    //}
//
    //}
//
    //for (size_t i = 0; i < tam_quadro; i++) {
    //    quadro_crc[i] = quadro[i];
    //}
//
    //for(int i = 0; i<tam_quadro; i++){
    //    if(quadro_crc[i])
    //        printf("1");
    //    else
    //        printf("0");
    //}
    //printf("|");
//
    //for(int i = tam_quadro; i<tam_quadro_crc; i++){
    //    if(quadro_crc[i])
    //        printf("1");
    //    else
    //        printf("0");
    //}

    free(quadro_crc);

}