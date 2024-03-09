/* PROGRAMA DE ARVORE TIPO B COM CHAVES DE MESES */
/* AUTORES:
Elter Rodrigues - 22309480,
João Jardim - 22307063,
Vinicious César - 22307319 ,
Gabriel Duarte - 22303292 */

#include "btree.h"

int main(int argc, char *argv[])
{
    printf("Digite os meses de entrada, ou tecle 0 para começar a remover elementos\n");
    TReg x;
    TPag *D;
    Inicializa(&D);
    printf("Mes: ");
    scanf("%s%*[^\n]", x.Mes);
    getchar();
    while (strcmp(x.Mes, "0") != 0)
    {
        x.Chave = converteMes(x.Mes);
        if (x.Chave == 0)
        {
            printf("Erro: mes invalido\n");
        }
        else
        {
            Insere(x, &D);
            Imprime(D);
            inOrd(D);
            printf("\n");
        }
        printf("Mes: ");
        scanf("%s%*[^\n]", x.Mes);
        getchar();
    }
    Testa(D);
    printf("Digite os meses de entrada, ou tecle 0 para começar a remover elementos\n");
    printf("Mes: ");
    scanf("%s%*[^\n]", x.Mes);
    getchar();
    while (strcmp(x.Mes, "0") != 0)
    {
        x.Chave = converteMes(x.Mes);
        if (x.Chave == 0)
        {
            printf("Erro: mes invalido\n");
        }
        else
        {
            Retira(x.Chave, &D);
            Imprime(D);
        }
        printf("Mes: ");
        scanf("%s%*[^\n]", x.Mes);
        getchar();
    }
    Testa(D);
    return 0;
}
