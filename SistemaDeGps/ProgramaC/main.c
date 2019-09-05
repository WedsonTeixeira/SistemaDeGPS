#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <windows.h>
#include <stdbool.h>
#include "Biblioteca_Metodos.h"

int main()
{
    setlocale(LC_ALL,"Portuguese");
    SetConsoleOutputCP(1254);
    SetConsoleCP(1254);

    CriarArquivos();

    int Opcao;

    do
    {
        system("cls");

        fflush(stdin);

        printf("CONTROLE DE ESTRADAS\n\n");
        printf("1 - NOVA CIDADE\n");
        printf("2 - NOVA ESTRADA\n");
        printf("3 - EXIBIR CIDADES\n");
        printf("4 - EXIBIR ESTRADAS\n");
        printf("5 - ORDENAR ESTRADAS\n");
        printf("6 - ARQUIVO PARA HASKELL\n");
        printf("7 - SAIR\n\n");
        printf("Informe a Opção: ");
        scanf("%d", &Opcao);

        switch(Opcao)
        {
            case 1:
                CadastrarCidade();
                break;
            case 2:
                CadastrarEstrada();
                break;
            case 3:
                ExibirCidade();
                break;
            case 4:
                ExibirEstrada();
                break;
            case 5:
                OrdenarEstrada();
                break;
            case 6:
                CriarArquivosHaskell();
                break;
        }

    }while(Opcao != 7);
}
