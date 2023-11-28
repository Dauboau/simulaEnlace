#include "../headers/enlace.h"
#include <stdio.h>
#include <stdlib.h>

void CamadaEnlaceDadosTransmissora(bool *quadro, int tam_quadro) {

    printf("Iniciando camada de enlace transmissora...\n");

    CamadaEnlaceDadosTransmissoraControleDeErro(quadro, tam_quadro);

}

void CamadaEnlaceDadosTransmissoraControleDeErro(bool *quadro, int tam_quadro) {

    printf("Iniciando controle de erros da camada de enlace transmissora...\n");

    int tipoDeControleDeErro = 0; // Ecolhercom base no tipo de teste que se deseja realiazar

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

    // x32 + x26 + x23 + x22 + x16 + x12 + x11 + x10 + x8 + x7 + x5 + x4 + x2 + x + 1
    // 1000 0100 1100 0001 0001 1101 1011 0111
    const bool polinomio[CRC_32_LENGTH] = { 1, 0, 0, 0, 0, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1, 
                                      0, 0, 0, 1, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 1 };

    bool *quadro_crc;
    quadro_crc = malloc(sizeof(bool)*(tam_quadro + 31));        

}