#include "Interface.h"

#include <stdio.h>
#include <stdlib.h>

void initInterface(Interface* this, World* w) {
    int i;
    char* str;
    Command* c;

    this->w = w;

    defineCommands(this);

    for (i = 0; i < 14; i++) {
        str = NULL;
        c = &(this->commands[i]);
        str = c->getAsString(c);
        printf("\n\n%s\n", str);
        free(str);
    }
}

void defineCommands(Interface* this) {
    initCommand(&(this->commands[0]), "carrega", "Carrega a informacao sobre o mundo de um ficheiro (apenas territorios)", "<nome_fich>");
    initCommand(&(this->commands[1]), "cria", "Cria n territorios do tipo especificado", "<tipo> <n>");
    initCommand(&(this->commands[2]), "conquista", "Tenta conquistar um territorio", "<nome>");
    initCommand(&(this->commands[3]), "passa", "Passa a chance de conquistar", "");
    initCommand(&(this->commands[4]), "maisouro", "Compra 1 unidade de ouro ao preco de 2 unidades de produtos", "");
    initCommand(&(this->commands[5]), "maisprod", "Compra 1 unidade produtos ao preco de 2 unidades de ouro", "");
    initCommand(&(this->commands[6]), "maismilitar", "Compra 1 unidade militar ao preco de 1 unidade de ouro e 1 unidade de produtos", "");
    initCommand(&(this->commands[7]), "adquire", "Compra uma determinada tecnologia", "<nome>");
    initCommand(&(this->commands[8]), "lista", "Lista a informacao sobre o mundo ou sobre um territorio em especifico", "(<nome>)");
    initCommand(&(this->commands[9]), "avanca", "Passa ao proximo turno", "");
    initCommand(&(this->commands[10]), "grava", "Cria um save em memoria com a informacao sobre o jogo atual com o nome especificado", "<nome_save>");
    initCommand(&(this->commands[11]), "ativa", "Carrega a informacao em memoria sobre o save com nome especificado", "<nome_save>");
    initCommand(&(this->commands[12]), "apaga", "Apaga a informacao em memoria sobre o save especificado", "<nome_save>");
    initCommand(&(this->commands[13]), "info", "Devolve as instrucoes e descricao de um comando especificado", "<nome_cmd>");
}

void setNextPhase(Interface* this, int a) {
    this->nextPhase = a;
}