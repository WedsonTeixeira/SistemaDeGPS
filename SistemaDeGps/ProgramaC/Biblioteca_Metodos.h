#include "Biblioteca_Struct.h"

void CriarArquivos()
{
    FILE *Arquivo1 = fopen("Cidades.dat","ab");
    FILE *Arquivo2 = fopen("Estradas.dat","ab");
    fclose(Arquivo1);
    fclose(Arquivo2);
}

void MensagemErroArquivo()
{
    system("cls");
    printf("Erro Ao Abrir Arquivo\n\n");
    system("pause");
}

bool PesquisarCidade(int Codigo, Cidade *Existente)
{
    FILE *Ler = fopen("Cidades.dat","rb");
    if(Ler == NULL)
    {
        MensagemErroArquivo();
    }
    else
    {
        while(fread(Existente,sizeof(Cidade),1,Ler) == 1)
        {
            if(Existente->Codigo == Codigo)
            {
                fclose(Ler);
                return true;
            }
        }
    }
    fclose(Ler);
    return false;
}

void CadastrarCidade()
{
    FILE *Gravar = fopen("Cidades.dat","ab");
    if(Gravar == NULL)
    {
        MensagemErroArquivo();
    }
    else
    {
        Cidade Nova;
        Cidade Existente;

        system("cls");
        printf("CADASTRO DE CIDADE\n\n");

        printf("CÓDIGO DA CIDADE.: ");
        scanf("%d", &Nova.Codigo);

        if(PesquisarCidade(Nova.Codigo, &Existente) == false)
        {

            fflush(stdin);
            printf("NOME DA CIDADE...: ");
            gets(Nova.Nome);

            fwrite(&Nova,sizeof(Cidade),1,Gravar);

            printf("\nCadastro Realizado Com Sucesso!\n\n");

        }
        else
        {
            printf("NOME DA CIDADE...: %s\n",Existente.Nome);
            printf("\nCidade Acima Cadastrada Com o Mesmo Código!\n\n");
        }
        fclose(Gravar);
        system("pause");
    }
}

void ExibirCidade()
{
    FILE *Ler = fopen("Cidades.dat","rb");
    if(Ler == NULL)
    {
        MensagemErroArquivo();
    }
    else
    {
        Cidade Existente;
        int Flag = 0;

        system("cls");
        printf("\tCIDADES\n\n");

        while(fread(&Existente,sizeof(Cidade),1,Ler) == 1)
        {
            Flag = 1;
            printf("CÓDIGO DA CIDADE.: %d\n", Existente.Codigo);
            printf("NOME DA CIDADE...: %s\n\n", Existente.Nome);
        }
        if(Flag == 0)
        {
            printf("A Lista Esta Vazia!\n\n");
        }
        fclose(Ler);
        system("pause");
    }
}

bool PesquisarEstrada(int Codigo, Estrada *Existente)
{
    FILE *Ler = fopen("Estradas.dat","rb");
    if(Ler == NULL)
    {
        MensagemErroArquivo();
    }
    else
    {
        while(fread(Existente,sizeof(Estrada),1,Ler) == 1)
        {
            if(Existente->CodigoCadastro == Codigo)
            {
                fclose(Ler);
                return true;
            }
        }
    }
    return false;
}

int PegarHash(int Chave, int Tamanho)
{
    double A = 0.6180339887;
    double Valor = Chave*A;
    Valor = Valor - (int) Valor;
    return (int) (Tamanho*Valor);
}

void CadastrarEstrada()
{
    FILE *Gravar = fopen("Estradas.dat","ab");
    if(Gravar == NULL)
    {
        MensagemErroArquivo();
    }
    else
    {
        Estrada Nova;
        Estrada EstradaExistente;
        Cidade CidadeExistente;

        system("cls");
        printf("CADASTRO DE ESTRADAS\n\n");

        printf("CÓDIGO DE CADASTRO..........: ");
        scanf("%d", &Nova.CodigoCadastro);

        Nova.Hash = PegarHash(Nova.CodigoCadastro,2039);

        if(PesquisarEstrada(Nova.CodigoCadastro, &EstradaExistente) == false)
        {
            fflush(stdin);
            printf("CÓDIGO DA CIDADE DE ORIGEM..: ");
            scanf("%d", &Nova.Origem.Codigo);

            if(PesquisarCidade(Nova.Origem.Codigo, &CidadeExistente) == true)
            {
                strcpy(Nova.Origem.Nome,CidadeExistente.Nome);

                printf("CÓDIGO DA CIDADE DE DESTINO.: ");
                scanf("%d", &Nova.Destino.Codigo);

                if(PesquisarCidade(Nova.Destino.Codigo, &CidadeExistente) == true)
                {
                    strcpy(Nova.Destino.Nome,CidadeExistente.Nome);

                    fflush(stdin);
                    printf("DISTANCIA ENTRE AS CIDADES..: ");
                    gets(Nova.Distancia);

                    fwrite(&Nova,sizeof(Estrada),1,Gravar);
                    fclose(Gravar);

                    printf("\nCadastro Realizado Com Sucesso!\n\n");
                }
                else
                {
                    printf("\nNão Existe Cidade Com Este Código!\n\n");
                }
            }
            else
            {
                printf("\nNão Existe Cidade Com Este Código!\n\n");
            }
        }
        else
        {
            printf("HASH DO CÓDIGO DE TRABALHO..: %d\n", EstradaExistente.Hash);
            printf("CÓDIGO DA CIDADE DE ORIGEM..: %d\n", EstradaExistente.Origem.Codigo);
            printf("NOME DA CIDADE DE ORIGEM....: %s\n", EstradaExistente.Origem.Nome);
            printf("CÓDIGO DA CIDADE DE DESTINO.: %d\n", EstradaExistente.Destino.Codigo);
            printf("NOME DA CIDADE DE DESTINO...: %s\n", EstradaExistente.Destino.Nome);
            printf("DISTANCIA ENTRE AS CIDADES..: %s\n", EstradaExistente.Distancia);

            printf("\nEstrada Acima Cadastrada Com o Mesmo Código!\n\n");
        }
        system("pause");
    }
}

void ExibirEstrada()
{
    FILE *Ler = fopen("Estradas.dat","rb");
    if(Ler == NULL)
    {
        MensagemErroArquivo();
    }
    else
    {
        Estrada Existente;
        int Flag = 0;

        system("cls");
        printf("\tESTRADAS\n\n");

        while(fread(&Existente,sizeof(Estrada),1,Ler) == 1)
        {
            Flag = 1;
            printf("CÓDIGO DE CADASTRO..........: %d\n", Existente.CodigoCadastro);
            printf("HASH DO CÓDIGO DE TRABALHO..: %d\n", Existente.Hash);
            printf("CÓDIGO DA CIDADE DE ORIGEM..: %d\n", Existente.Origem.Codigo);
            printf("NOME DA CIDADE DE ORIGEM....: %s\n", Existente.Origem.Nome);
            printf("CÓDIGO DA CIDADE DE DESTINO.: %d\n", Existente.Destino.Codigo);
            printf("NOME DA CIDADE DE DESTINO...: %s\n", Existente.Destino.Nome);
            printf("DISTANCIA ENTRE AS CIDADES..: %s\n\n", Existente.Distancia);
        }
        if(Flag == 0)
        {
            printf("A Lista Esta Vazia!\n\n");
        }
        fclose(Ler);
        system("pause");
    }
}

void InsertionSortEstradas(Estrada Dados[], int TotalDados)
{
    Estrada Aux;
    int Indice1, Indice2;

    for(Indice1 = 1;  Indice1 < TotalDados; Indice1++)
    {
        Aux = Dados[Indice1];
        Indice2 = Indice1 - 1;

        while(Indice2 >= 0 && Dados[Indice2].CodigoCadastro > Aux.CodigoCadastro)
        {
            Dados[Indice2 + 1] = Dados[Indice2];
            Indice2 = Indice2 - 1;
        }

        Dados[Indice2 + 1] = Aux;
    }
}

void OrdenarEstrada()
{
    FILE *Ler = fopen("Estradas.dat","r+b");
    if(Ler == NULL)
    {
        MensagemErroArquivo();
    }
    else
    {
        int Tamanho;

        system("cls");
        printf("\tORDENAÇÃO DAS ESTRADAS\n\n");

        fseek(Ler,0,SEEK_END);

        Tamanho = ftell(Ler)/sizeof(Estrada);

        if(Tamanho == 0)
        {
            printf("Não Há Estradas Para Ordenar!\n\n");
        }
        else
        {
            Estrada *TodasEstradas = (Estrada*) malloc(sizeof(Estrada)*Tamanho);

            rewind(Ler);
            fread(TodasEstradas,sizeof(Estrada),Tamanho,Ler);

            InsertionSortEstradas(TodasEstradas, Tamanho);

            rewind(Ler);
            fwrite(TodasEstradas,sizeof(Estrada),Tamanho,Ler);

            printf("Estradas Ordenadas Com Sucesso!\n\n");
        }
        fclose(Ler);
        system("pause");
    }
}

void CriarArquivosHaskell()
{
    FILE *Ler = fopen("Estradas.dat","rb");
    FILE *Gravar = fopen("..\\BaseDeDadosHaskell.txt","wb");

    if(Ler == NULL || Gravar == NULL)
    {
        MensagemErroArquivo();
    }
    else
    {
        Estrada Existente;

        system("cls");
        printf("\tCRIANDO BASE DE DADOS PARA HASKELL\n\n");

        while(fread(&Existente,sizeof(Estrada),1,Ler) == 1)
        {
            fprintf(Gravar,"\"%s\",\"%s\",%s\n", Existente.Origem.Nome, Existente.Destino.Nome, Existente.Distancia);
            fprintf(Gravar,"\"%s\",\"%s\",%s\n", Existente.Destino.Nome, Existente.Origem.Nome, Existente.Distancia);
        }
        fclose(Ler);
        fclose(Gravar);

        printf("Arquivo Criando Com Sucesso!\n\n");

        printf("1º Passo: Abra o Arquivo \"ProgramaHaskell.hs\".\n");
        printf("2º Passo: Digite \"gerarProlog\" no Compilador\n\n");
        system("pause");
    }

}











