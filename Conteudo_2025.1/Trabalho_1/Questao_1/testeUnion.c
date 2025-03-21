#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "stdbool.h"


typedef struct item{
    char nome[50];
    float preco;
    bool porPeso;
    union 
    {
        /* data */
        unsigned peso;
        float volume;
    };
    
}Item;


int main(){
    Item item;
    strcpy(item.nome, "Coca-Cola");
    item.preco = 5.0;
    item.peso = 16.5;
    item.porPeso = true;
    printf("Nome: %s\n", item.nome);
    printf("Preco: %.2f\n", item.preco);
    if(item.porPeso){
        printf("Peso: %.2f\n", item.peso);
    }else{
        printf("Volume: %.2f\n", item.volume);
    }

    return 0;
}