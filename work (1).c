/* PROGRAMA DE ARVORE BINARIA - AVL */
/* AUTORES:
Elter Rodrigues - 22309480,
Jo�o Jardim - 22307063,
Vinicious C�sar - 22307319 ,
Gabriel Duarte - 22303292 */

#include "tree.h"

int main(){
    setlocale(LC_ALL, "Portuguese");
    
    int qtd;
    printf("Quantos Meses deseja inserir? ");
    scanf("%d",&qtd);
    
    Arv *arvore= (Arv *) malloc(qtd * sizeof(Arv));
    if (arvore == NULL) {
        printf("Erro de mem�ria\n");
        return 1;
    }
    int i = 0;
    while (i < qtd) {    
        printf("\nQuantidade de meses cadastradas � %d: \n", i+1);
        
        printf("Digite o m�s que deseja inserir: ");
        scanf("%s", arvore[i].meses);
    
        mesesnumerico(arvore, i);
    
        i++; 
    }
    
    system("pause");
    return 0;
}
