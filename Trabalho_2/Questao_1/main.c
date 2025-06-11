#include "stdio.h"
#include "stdlib.h"
#include "string.h"

#include "prototipos.h"

int main(){
    int opcao, inseriu, removeu;
    struct dadoEstado dadoEstado;
    struct dadoCidade dadoCidade;
    struct dadoCep dadoCep;
    struct dadoPessoa dadoPessoa;
    Estado *estado;
    Cidade *cidade;
    cidade = NULL;
    Ceps *raiz_ceps = NULL;
    Pessoa *raiz_pessoa = NULL;
    estado = NULL;


    do
    {
       printf("\n======= MENU =======\n "
            "1. Cadastrar Estado\n"
            "2. Cadastrar Cidade\n"
            "3. Cadastrar CEP\n"
            "4. Cadastrar Pessoa\n"
            "5. Remover um CEP\n"
            "6. Remover uma Pessoa\n"
            "0. Sair\n"
        );
         printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        getchar(); // Limpar o buffer do teclado
        switch(opcao)
        {
            case 1:
                dadoEstado = Ler_dados_Estado();
                inseriu = inserir_estado(&estado, criar_estado(dadoEstado));
                if(inseriu)
                    printf("Estado cadastrado com sucesso!\n");
                else
                    printf("Erro ao cadastrar o estado.\n");
                break;
            case 2:
                dadoCidade = Ler_dados_Cidade();
                inseriu = insere_cidades_arovreRB(&cidade, dadoCidade);
                if(inseriu)
                    printf("Cidade cadastrada com sucesso!\n");
                else
                    printf("Erro ao cadastrar a cidade.\n");
                break;
            case 3:
                dadoCep = Ler_dados_Cep();
                inseriu = insere_cep_arvoreRB(&raiz_ceps, dadoCep);
                if(inseriu)
                    printf("CEP cadastrado com sucesso!\n");
                else
                    printf("Erro ao cadastrar o CEP.\n");
                break;
            case 4:
                dadoPessoa = Ler_dados_Pessoa();
                inseriu = insere_pessoa_arvoreRB(&raiz_pessoa, dadoPessoa);
                if(inseriu)
                    printf("Pessoa cadastrada com sucesso!\n");
                else
                    printf("Erro ao cadastrar a pessoa.\n");
                break;
            case 5:
                printf("Digite o CEP a ser removido: ");
                scanf("%d", &dadoCep.cep);
                removeu = remove_arvore_cep(&raiz_ceps, dadoCep.cep);
                if(removeu)
                    printf("CEP removido com sucesso!\n");
                else
                    printf("Erro ao remover o CEP.\n");
                break;
            case 6:
                printf("Digite o CPF da pessoa a ser removida: ");
                fgets(dadoPessoa.cpf, sizeof(dadoPessoa.cpf), stdin);
                dadoPessoa.cpf[strcspn(dadoPessoa.cpf, "\n")] = 0; // Remove newline character
                removeu = remover_arvore_pessoa(&raiz_pessoa, dadoPessoa.cpf);
                if(removeu)
                    printf("Pessoa removida com sucesso!\n");
                else
                    printf("Erro ao remover a pessoa.\n");

                break;
            case 0:
                printf("Saindo...\n");
                break;
            default:
                printf("Opcao invalida! Tente novamente.\n");
        }
    }while (opcao != 0);
    
    return 0;
}