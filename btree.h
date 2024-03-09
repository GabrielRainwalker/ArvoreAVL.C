#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define I 2 // MUDE I PARA MUDAR O NÓ E MUDAR O MAX E MIN PARA ROTACIONAR
#define II (I * 2) // ORDEM -1
#define FALSE 0
#define TRUE 1

typedef struct TReg
{
    int Chave;
    char Mes[20];
} TReg;

typedef int TChave;
typedef struct TPag *TApont;
typedef struct TPag
{
    short n;
    TReg r[II];
    TApont p[II + 1];
} TPag;

void Inicializa(TApont *dici)
{
    *dici = NULL;
}

int converteMes(char *mes)
{
    if (strcmp(mes, "janeiro") == 0)
        return 1;
    else if (strcmp(mes, "fevereiro") == 0)
        return 2;
    else if (strcmp(mes, "marco") == 0)
        return 3;
    else if (strcmp(mes, "abril") == 0)
        return 4;
    else if (strcmp(mes, "maio") == 0)
        return 5;
    else if (strcmp(mes, "junho") == 0)
        return 6;
    else if (strcmp(mes, "julho") == 0)
        return 7;
    else if (strcmp(mes, "agosto") == 0)
        return 8;
    else if (strcmp(mes, "setembro") == 0)
        return 9;
    else if (strcmp(mes, "outubro") == 0)
        return 10;
    else if (strcmp(mes, "novembro") == 0)
        return 11;
    else if (strcmp(mes, "dezembro") == 0)
        return 12;
    else
        return 0;
}

void inOrd(TApont arv)
{
    int i;

    if (arv != NULL)
    {

        for (i = 0; i < arv->n; i++)
        {
            inOrd(arv->p[i]);
            printf("%s ", arv->r[i].Mes);
        }

        inOrd(arv->p[i]);
    }
    return;
}

void Pesquisa(TReg *x, TApont Ap)
{
    long i = 1;
    if (Ap == NULL)
    {
        printf("TReg nao esta presente na arvore\n");
        return;
    }
    while (i < Ap->n && x->Chave > Ap->r[i - 1].Chave)
        i++;
    if (x->Chave == Ap->r[i - 1].Chave)
    {
        *x = Ap->r[i - 1];
        return;
    }
    if (x->Chave < Ap->r[i - 1].Chave)
        Pesquisa(x, Ap->p[i - 1]);
    else
        Pesquisa(x, Ap->p[i]);
}

void InsereNaPagina(TApont Ap,
                    TReg Reg, TApont ApDir)
{
    short NaoPosi;
    int k;
    k = Ap->n;
    NaoPosi = (k > 0);
    while (NaoPosi)
    {
        if (Reg.Chave >= Ap->r[k - 1].Chave)
        {
            NaoPosi = FALSE;
            break;
        }
        Ap->r[k] = Ap->r[k - 1];
        Ap->p[k + 1] = Ap->p[k];
        k--;
        if (k < 1)
            NaoPosi = FALSE;
    }
    Ap->r[k] = Reg;
    Ap->p[k + 1] = ApDir;
    Ap->n++;
}

void Ins(TReg Reg, TApont Ap, short *Cresceu,
         TReg *RegReto, TApont *ApRetorno)
{
    long i = 1;
    long j;
    TApont ApTemp;

    if (Ap == NULL)
    {
        *Cresceu = TRUE;
        (*RegReto) = Reg;
        (*ApRetorno) = NULL;
        return;
    }

    while (i < Ap->n && Reg.Chave > Ap->r[i - 1].Chave)
        i++;

    if (Reg.Chave == Ap->r[i - 1].Chave)
    {
        printf(" Erro: Ja contem este Registro \n");
        *Cresceu = FALSE;
        return;
    }

    if (Reg.Chave < Ap->r[i - 1].Chave)
        i--;

    Ins(Reg, Ap->p[i], Cresceu, RegReto, ApRetorno);

    if (!*Cresceu)
        return;

    if (Ap->n < II)
    {
        InsereNaPagina(Ap, *RegReto, *ApRetorno);
        *Cresceu = FALSE;
        return;
    }

    ApTemp = (TApont)malloc(sizeof(TPag));
    ApTemp->n = 0;
    ApTemp->p[0] = NULL;
    if (i < I + 1)
    {
        InsereNaPagina(ApTemp, Ap->r[II - 1], Ap->p[II]);
        Ap->n--;
        InsereNaPagina(Ap, *RegReto, *ApRetorno);
    }
    else
        InsereNaPagina(ApTemp, *RegReto, *ApRetorno);
    for (j = I + 2; j <= II; j++)
        InsereNaPagina(ApTemp, Ap->r[j - 1], Ap->p[j]);
    Ap->n = I;
    ApTemp->p[0] = Ap->p[I + 1];
    *RegReto = Ap->r[I];
    *ApRetorno = ApTemp;
}

void Insere(TReg Reg, TApont *Ap)
{
    short Cresceu;
    TReg RegReto;
    TPag *ApRetorno, *ApTemp;
    Ins(Reg, *Ap, &Cresceu, &RegReto, &ApRetorno);
    if (Cresceu)
    {
        ApTemp = (TPag *)malloc(sizeof(TPag));
        ApTemp->n = 1;
        ApTemp->r[0] = RegReto;
        ApTemp->p[1] = ApRetorno;
        ApTemp->p[0] = *Ap;
        *Ap = ApTemp;
    }
}

void Reconstitui(TApont ApPag, TApont ApPai,
                 int PosPai, short *Diminuiu)
{
    TPag *Aux;
    long DispAux, j;
    if (PosPai < ApPai->n)
    {
        Aux = ApPai->p[PosPai + 1];
        DispAux = (Aux->n - I + 1) / 2;
        ApPag->r[ApPag->n] = ApPai->r[PosPai];
        ApPag->p[ApPag->n + 1] = Aux->p[0];
        ApPag->n++;
        if (DispAux > 0)
        {
            for (j = 1; j < DispAux; j++)
                InsereNaPagina(ApPag, Aux->r[j - 1], Aux->p[j]);
            ApPai->r[PosPai] = Aux->r[DispAux - 1];
            Aux->n -= DispAux;
            for (j = 0; j < Aux->n; j++)
                Aux->r[j] = Aux->r[j + DispAux];
            for (j = 0; j <= Aux->n; j++)
                Aux->p[j] = Aux->p[j + DispAux];
            *Diminuiu = FALSE;
        }
        else
        {
            for (j = 1; j <= I; j++)
                InsereNaPagina(ApPag, Aux->r[j - 1], Aux->p[j]);
            free(Aux);
            for (j = PosPai + 1; j < ApPai->n; j++)
            {
                ApPai->r[j - 1] = ApPai->r[j];
                ApPai->p[j] = ApPai->p[j + 1];
            }
            ApPai->n--;
            if (ApPai->n >= I)
                *Diminuiu = FALSE;
        }
    }
    else
    {
        Aux = ApPai->p[PosPai - 1];
        DispAux = (Aux->n - I + 1) / 2;
        for (j = ApPag->n; j >= 1; j--)
            ApPag->r[j] = ApPag->r[j - 1];
        ApPag->r[0] = ApPai->r[PosPai - 1];
        for (j = ApPag->n; j >= 0; j--)
            ApPag->p[j + 1] = ApPag->p[j];
        ApPag->n++;
        if (DispAux > 0)
        {
            for (j = 1; j < DispAux; j++)
                InsereNaPagina(ApPag, Aux->r[Aux->n - j],
                               Aux->p[Aux->n - j + 1]);
            ApPag->p[0] = Aux->p[Aux->n - DispAux + 1];
            ApPai->r[PosPai - 1] = Aux->r[Aux->n - DispAux];
            Aux->n -= DispAux;
            *Diminuiu = FALSE;
        }
        else
        {
            for (j = 1; j <= I; j++)
                InsereNaPagina(Aux, ApPag->r[j - 1], ApPag->p[j]);
            free(ApPag);
            ApPai->n--;
            if (ApPai->n >= I)
                *Diminuiu = FALSE;
        }
    }
}

void Antecessor(TApont Ap, int Ind,
                TApont ApPai, short *Diminuiu)
{
    if (ApPai->p[ApPai->n] != NULL)
    {
        Antecessor(Ap, Ind, ApPai->p[ApPai->n], Diminuiu);
        if (*Diminuiu)
            Reconstitui(ApPai->p[ApPai->n], ApPai, (long)ApPai->n, Diminuiu);
        return;
    }
    Ap->r[Ind - 1] = ApPai->r[ApPai->n - 1];
    ApPai->n--;
    *Diminuiu = (ApPai->n < I);
}

void Ret(TChave Ch, TApont *Ap, short *Diminuiu)
{
    long j, Ind = 1;
    TApont Pag;
    if (*Ap == NULL)
    {
        printf("Erro: registro nao esta na arvore\n");
        *Diminuiu = FALSE;
        return;
    }
    Pag = *Ap;
    while (Ind < Pag->n && Ch > Pag->r[Ind - 1].Chave)
        Ind++;
    if (Ch == Pag->r[Ind - 1].Chave)
    {
        if (Pag->p[Ind - 1] == NULL)
        {
            Pag->n--;
            *Diminuiu = (Pag->n < I);
            for (j = Ind; j <= Pag->n; j++)
            {
                Pag->r[j - 1] = Pag->r[j];
                Pag->p[j] = Pag->p[j + 1];
            }
            return;
        }
        Antecessor(*Ap, Ind, Pag->p[Ind - 1], Diminuiu);
        if (*Diminuiu)
            Reconstitui(Pag->p[Ind - 1], *Ap, Ind - 1, Diminuiu);
        return;
    }
    if (Ch > Pag->r[Ind - 1].Chave)
        Ind++;
    Ret(Ch, &Pag->p[Ind - 1], Diminuiu);
    if (*Diminuiu)
        Reconstitui(Pag->p[Ind - 1], *Ap, Ind - 1, Diminuiu);
}

void Retira(TChave Ch, TApont *Ap)
{
    short Diminuiu;
    TApont Aux;
    Ret(Ch, Ap, &Diminuiu);
    if (Diminuiu && (*Ap)->n == 0)
    {
        Aux = *Ap;
        *Ap = Aux->p[0];
        free(Aux);
    }
}

void ImprimeI(TApont p, int nivel)
{
    long i;
    if (p == NULL)
        return;
    printf("Nivel %d : ", nivel);
    for (i = 0; i < p->n; i++)
        printf("%s ", p->r[i].Mes);
    putchar('\n');
    nivel++;
    for (i = 0; i <= p->n; i++)
        ImprimeI(p->p[i], nivel);
}

void Imprime(TApont p)
{
    int n = 0;
    ImprimeI(p, n);
}

void TestaI(TApont p, int pai, short direita)
{
    int i;
    int ant = 0;
    if (p == NULL)
        return;
    if (p->r[0].Chave > pai && direita == FALSE)
    {
        printf("Erro: filho maior que o pai  %d\n", p->r[0].Chave, pai);
        return;
    }
    for (i = 0; i < p->n; i++)
    {
        if (p->r[i].Chave <= ant)
        {
            printf("Erro: folha maior que a folha a esquerda %d\n",
                   (long)p->r[i].Chave, ant);
            return;
        }
        ant = p->r[i].Chave;
    }
    for (i = 0; i < p->n; i++)
        TestaI(p->p[i], p->r[i].Chave, FALSE);
    TestaI(p->p[p->n], p->r[i].Chave, TRUE);
}

void Testa(TApont p)
{
    int i;
    if (p == NULL)
        return;
    for (i = 0; i < p->n; i++)
        TestaI(p->p[i], p->r[i].Chave, FALSE);
    TestaI(p->p[p->n], p->r[i].Chave, TRUE);
}
