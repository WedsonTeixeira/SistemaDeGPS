typedef struct{
    int  Codigo;
    char Nome[35];
}Cidade;

typedef struct{
    int    CodigoCadastro;
    int    Hash;
    Cidade Origem;
    Cidade Destino;
    char   Distancia[10];
}Estrada;
