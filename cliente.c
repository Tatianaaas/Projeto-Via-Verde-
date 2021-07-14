/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */


#include "funcoes.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "API_Leitura.h"

/*
 * Função de registo de clientes
 * @param apontador para estrutura do cliente
 * @param tamanho do array de clientes
 * @param número de elementos do array cliente
 */

void alocacaoClientes(struct cliente **clientes, int *tam, int *elementos) {
    *clientes = (struct cliente*) malloc((*tam) * sizeof (struct cliente));
    if (*clientes == NULL) {
        printf("Erro ao alocar");
    } else {
        *elementos = 0;
    }
}

void registoClientes(struct cliente **clientes, int *tam, int *elementos) {
    FILE *f;
    int i, carros = 0;
    struct cliente *novo;
    if (*elementos >*tam) {
        novo = realloc(*clientes, ((*elementos)+(*tam)) * sizeof (struct cliente));
        if (novo == NULL) {
            printf("Erro ao realocar\n");
        } else {
            *clientes = novo;
            (*tam) += (*elementos);
        }
    }
    if ((f = fopen("clientes.txt", "wb")) == NULL) {
        perror(NULL);
    } else {
        /*
         * Se houver dados repetidos estes ser-lhes-ão pedidos novamente            
         */
        (*clientes + (*elementos))->numcli = (*elementos) + 1;
        printf("Cliente numero %d", (*clientes + (*elementos))->numcli);
        readString((*clientes + (*elementos))->nome, NOME, "Nome:");
        for (i = 0; i<*elementos; i++) {
            if ((strncmp((*clientes + i)->nome, (*clientes + (*elementos))->nome, NOME)) == 0 && i != *elementos) {
                printf("O nome introduzido ja existe , tente outro nome\n");
                readString((*clientes + (*elementos))->nome, NOME, "Nome:");
            }
        }
        readString((*clientes + (*elementos))->morada, MORADA, "Morada:");
        for (i = 0; i<*elementos; i++) {
            if ((strncmp((*clientes + i)->morada, (*clientes + (*elementos))->morada, MORADA)) == 0 && i != *elementos) {
                printf("A morada introduzida ja existe , tente outra morada\n");
                readString((*clientes + (*elementos))->morada, MORADA, "Morada:");
            }
        }
        readLong(&(*clientes + (*elementos))->nif, 100000000, 999999999, "NIF(9 digitos):");
        for (i = 0; i<*elementos; i++) {
            if ((*clientes + i)->nif == (*clientes + *elementos)->nif && i != *elementos) {
                printf("O NIF introduzido ja existe , tente outro numero\n");
                readLong(&(*clientes + (*elementos))->nif, 100000000, 999999999, "NIF(9 digitos):");
            }
        }
        readLong(&(*clientes + (*elementos))->cc, 10000000, 99999999, "CARTAO CIDADAO(8 digitos):");
        for (i = 0; i<*elementos; i++) {
            if ((*clientes + i)->cc == (*clientes + *elementos)->cc && i != *elementos) {
                printf("O Cartao de Cidadao introduzido ja existe , tente outro numero\n");
                readLong(&(*clientes + (*elementos))->cc, 1000000, 99999999, "CARTAO CIDADAO:");
            }
        }

        readLong(&(*clientes + (*elementos))->nib, 100000000, 999999999, "NIB(9 digitos):");
        for (i = 0; i<*elementos; i++) {
            if ((*clientes + i)->nib == (*clientes + *elementos)->nib && i != *elementos) {
                printf("O NIB introduzido ja existe , tente outro numero\n");
                readLong(&(*clientes + (*elementos))->nib, 100000000, 999999999, "NIB:");
            }
        }
        readInt(&carros, 0, CARROS, "Quantos carros pretende registar:");
        for (i = 0; i < carros; i++) {
            printf("\nCarro %d", i + 1);
            readString((*clientes + *elementos)->veiculos[i].matricula, MATRICULA, "Matricula:");
            readString((*clientes + *elementos)->veiculos[i].marca, NOME, "Marca:");
            readString((*clientes + *elementos)->veiculos[i].modelo, NOME, "Modelo:");
        }
        printf("\nDados introduzidos válidos\n");
        (*elementos)++;
        fwrite((*clientes), sizeof (struct cliente), (*elementos), f);
    }
    fclose(f);

}

/*
 * Função que permite alterar os dados dos clientes
 * @param apontador para estrutura do cliente
 * @param número de elementos do array cliente
 */
void editarClientes(struct cliente **clientes, int *elementos) {
    FILE *f;
    int num, i = 0, j = -1, opcao;
    int carro = 0;
    //Se o número de elementos atual for 0 , é apresentada uma mensagem   
    if (*elementos == 0) {
        printf("\nNao existem clientes registados\n");
    }//Caso o contrário , é permitida a alteração dos dados dos clientes 
    else {
        // Solicitacao do numero do cliente a editar 
        readInt(&num, 1, 100, "Insira o numero do cliente que  pretende editar:");
        while (i<*elementos && j != i) {
            if ((*clientes + i)->numcli == num) {
                j = i;
            }
            i++;
        }
        if (j == -1) {
            printf("O numero que inseriu não se encontra registado\n");
        } else {
            if ((f = fopen("clientes.txt", "wb")) == NULL) {
                perror(NULL);
            } else {
                /*
                 * No caso de se encontrar o número do cliente na lista dos registos e se
                 * o ficheiro for aberto corretamente , inicia-se a alteração de dados. 
                 * O funcionario pode optar por alterar parâmetros específicos ou
                 * todos os parâmetros de uma só vez.
                 */
                while (opcao != 8) {
                    printf("\nEDITAR:\n1-NOME\n2-MORADA\n3-NIF\n4-NR CARTAO CIDADAO\n5-NIB\n6-CARRO\n7-TUDO\n8-VOLTAR\n");
                    readInt(&opcao, 1, 8, "Escolha uma opcao:");
                    if (opcao == 1) {
                        // alterar apenas o nome
                        readString((*clientes + j)->nome, NOME, "NOME:");
                        for (i = 0; i<*elementos; i++) {
                            printf("O nome introduzido ja existe , tente outro nome\n");
                            readString((*clientes + j)->nome, NOME, "NOME:");
                        }
                    } else if (opcao == 2) {
                        //alterar apenas a morada
                        readString((*clientes + j)->morada, MORADA, "MORADA:");
                        for (i = 0; i<*elementos; i++) {
                            if ((strncmp((*clientes + i)->morada, (*clientes + j)->morada, MORADA)) == 0 && i != j) {
                                printf("A morada introduzida ja existe , tente outra morada\n");
                                readString((*clientes + j)->morada, MORADA, "MORADA:");
                            }
                        }
                    } else if (opcao == 3) {
                        //alterar apenas o NIF
                        readLong(&(*clientes + j)->nif, 100000000, 999999999, "NIF(9 digitos):");
                        for (i = 0; i<*elementos; i++) {
                            if ((*clientes + i)->nif == (*clientes + j)->nif && i != j) {
                                printf("O NIF introduzido ja existe , tente outro numero\n");
                                readLong(&(*clientes + j)->nif, 100000000, 999999999, "NIF(9 digitos):");
                            }
                        }
                    } else if (opcao == 4) {
                        //alterar apenas o número do Cartao de Cidadao
                        readLong(&(*clientes + j)->cc, 10000000, 99999999, "CARTAO CIDADAO(8 digitos):");
                        for (i = 0; i<*elementos; i++) {
                            if ((*clientes + i)->cc == (*clientes + j)->cc && i != j) {
                                printf("O Cartao de Cidadao introduzido ja existe , tente outro numero\n");
                                readLong(&(*clientes + j)->cc, 1000000, 99999999, "CARTAO CIDADAO(8 digitos):");
                            }
                        }
                    } else if (opcao == 5) {
                        //alterar apenas o NIB
                        readLong(&(*clientes + j)->nib, 100000000, 999999999, "NIB(9 digitos):");
                        for (i = 0; i<*elementos; i++) {
                            if ((*clientes + i)->nib == (*clientes + j)->nib && i != j) {
                                printf("O NIB introduzido ja existe , tente outro numero\n");
                                readLong(&(*clientes + j)->nib, 100000000, 999999999, "NIB(9 digitos):");
                            }
                        }

                    } else if (opcao == 6) {
                        readInt(&carro, 0, CARROS, "Que carro pretende alterar:");
                        if (carro > 0) {
                            printf("Carro %d", carro);
                            readString((*clientes + *elementos)->veiculos[carro - 1].matricula, MATRICULA, "Matricula:");
                            readString((*clientes + *elementos)->veiculos[carro - 1].marca, NOME, "Marca:");
                            readString((*clientes + *elementos)->veiculos[carro - 1].modelo, NOME, "Modelo:");
                        }
                    } else if (opcao == 7) {
                        //alterar todos os campos
                        readString((*clientes + j)->nome, NOME, "NOME:");
                        for (i = 0; i<*elementos; i++) {
                            if ((strncmp((*clientes + i)->nome, (*clientes + j)->nome, NOME)) == 0 && i != j) {
                                printf("O nome introduzido ja existe , tente outro nome\n");
                                readString((*clientes + j)->nome, NOME, "NOME:");
                            }
                        }
                        readString((*clientes + j)->morada, MORADA, "MORADA:");
                        for (i = 0; i<*elementos; i++) {
                            if ((strncmp((*clientes + i)->morada, (*clientes + j)->morada, MORADA)) == 0 && i != j) {
                                printf("A morada introduzida ja existe , tente outra morada\n");
                                readString((*clientes + j)->morada, MORADA, "MORADA:");
                            }
                        }
                        readLong(&(*clientes + j)->nif, 100000000, 999999999, "NIF(9 digitos):");
                        for (i = 0; i<*elementos; i++) {
                            if ((*clientes + i)->nif == (*clientes + j)->nif && i != j) {
                                printf("O NIF introduzido ja existe , tente outro numero\n");
                                readLong(&(*clientes + j)->nif, 100000000, 999999999, "NIF(9 digitos):");
                            }
                        }
                        readLong(&(*clientes + j)->cc, 1000000, 99999999, "CARTAO CIDADAO(8 digitos):");
                        for (i = 0; i<*elementos; i++) {
                            if ((*clientes + i)->cc == (*clientes + j)->cc && i != j) {
                                printf("O Cartao de Cidadao introduzido ja existe , tente outro numero\n");
                                readLong(&(*clientes + j)->cc, 1000000, 99999999, "CARTAO CIDADAO(8 digitos):");
                            }
                        }
                        readLong(&(*clientes + j)->nib, 100000000, 999999999, "NIB:");
                        for (i = 0; i<*elementos; i++) {
                            if ((*clientes + i)->nib == (*clientes + j)->nib && i != j) {
                                printf("O NIB introduzido ja existe , tente outro numero\n");
                                readLong(&(*clientes + j)->nib, 100000000, 999999999, "NIB(9 digitos):");
                            }
                        }
                        readInt(&carro, 0, CARROS, "Que carro pretende alterar:");
                        if (carro > 0) {
                            printf("Carro %d", carro);
                            readString((*clientes + *elementos)->veiculos[carro - 1].matricula, MATRICULA, "Matricula:");
                            readString((*clientes + *elementos)->veiculos[carro - 1].marca, NOME, "Marca:");
                            readString((*clientes + *elementos)->veiculos[carro - 1].modelo, NOME, "Modelo:");
                        }
                    }
                    fwrite((*clientes), sizeof (struct cliente), 1, f);
                }
            }
            fclose(f);
        }
    }
}

/*
 * Função para eliminar o registo de um cliente
 * @param apontador para estrutura do cliente
 * @param tamanho do array de clientes
 * @param numero de elementos do array cliente
 */
void eliminarRegisto(struct cliente **clientes, int *tam, int *elementos) {
    FILE *f;
    int i = 0, j = -1, num;

    if (*elementos == 0) {
        printf("\nNao existem clientes registados\n");
    } else {
        if ((f = fopen("clientes.txt", "wb")) == NULL) {
            perror(NULL);
        } else {
            readInt(&num, 1, 100, "Insira o numero do cliente que  pretende eliminar:");
            for (i = 0; i<*elementos; i++) {
                if ((*clientes + i)->numcli == num) {
                    j = i;
                }
            }
            if (j == -1) {
                printf("Nao existe nenhum cliente com o numero inserido.\n");
            } else {
                /*
                 * Se o numero inserido correpsonder a um numero de cliente 
                 * resgistado,esse registo é eliminado.         
                 */
                while (j < (*elementos) - 1) {
                    (*clientes)[j] = (*clientes)[j + 1];
                    j++;
                }
                (*elementos)--;
                fwrite((*clientes), sizeof (struct cliente), (*elementos), f);
                printf("-----Cliente eliminado----\n");
            }
            fclose(f);
        }
    }
}

/*
 * Função para listar os registos dos clientes efetuados 
 * @param apontador para estrutura do cliente
 * @param tamanho do array de clientes
 * @param numero de elementos do array cliente
 */
void listarClientes(struct cliente **clientes, int *tam, int *elementos) {
    FILE *f;
    int numero, i = 0, opcao = 0, j = -1, c;
    struct cliente *novo;

    if (*elementos >*tam) {
        novo = realloc(*clientes, ((*elementos)+(*tam)) * sizeof (struct cliente));
        if (novo == NULL) {
            printf("Erro ao realocar");
        } else {
            *clientes = novo;
            (*tam) += (*elementos);
        }
    }
    /*
     * O funcionário pode optar por listar um cliente à sua escolha ou
     * listar todos os clientes registados na via verde.
     */
    if (*elementos == 0) {
        printf("\nNao existem clientes registados\n");
    } else {
        if ((f = fopen("clientes.txt", "rb")) == NULL) {
            perror(NULL);
        } else {
            printf("LISTAR:\n1-SELECIONAR UM CLIENTE\n2-TODOS OS CLIENTES\n");
            readInt(&opcao, 1, 5, "Escolha uma opcao:");


            if (opcao == 1) {
                readInt(&numero, 1, 100, "NUMERO DO CLIENTE:");
                for (i = 0; i<*elementos; i++) {
                    if ((*clientes + i)->numcli == numero) {
                        j = i;
                    }
                }
                fread(*clientes, sizeof (struct cliente), 1, f);
                printf("\nNumero  Cliente:%d", (*clientes + j)->numcli);
                printf("\nNOME:%s", (*clientes + j)->nome);
                printf("\nMORADA:%s", (*clientes + j)->morada);
                printf("\nNIF:%ld", (*clientes + j)->nif);
                printf("\nNUMERO CC:%ld", (*clientes + j)->cc);
                printf("\nNIB:%ld", (*clientes + j)->nib);
                printf("\nPontos:%d", (*clientes + j)->pontos);
                printf("\n\n");
            } else if (opcao == 2) {
                fread(*clientes, sizeof (struct cliente), *elementos, f);
                i = 0;
                while (i<*elementos) {
                    printf("\nNumero  Cliente:%d", (*clientes + i)->numcli);
                    printf("\nNOME:%s", (*clientes + i)->nome);
                    printf("\nMORADA:%s", (*clientes + i)->morada);
                    printf("\nNIF:%ld", (*clientes + i)->nif);
                    printf("\nNUMERO CC:%ld", (*clientes + i)->cc);
                    printf("\nNIB:%ld", (*clientes + i)->nib);
                    printf("\nPontos:%d", (*clientes + i)->pontos);
                    printf("\n\n");
                    i++;
                }

            }
        }
    }
    fclose(f);
}