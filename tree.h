#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

struct arv {
	char meses[12];
	int mesNum;
	int bal;  /* BALANCEADOR */
	struct arv* esq;
	struct arv* dir;
};

typedef struct arv Arv;

void mesesnumerico(Arv *arvnum, int i) {    /* TRANSFORMA STRING EM NUMERAL */
	int mesNum;
	if (strcasecmp(arvnum[i].meses, "janeiro") == 0) {
		mesNum = 1;
	} else if (strcasecmp(arvnum[i].meses, "Janeiro") == 0) {
		mesNum = 1;
	} else if (strcasecmp(arvnum[i].meses, "fevereiro") == 0) {
		mesNum = 2;
	} else if (strcasecmp(arvnum[i].meses, "Fevereiro") == 0) {
		mesNum = 2;
	} else if (strcasecmp(arvnum[i].meses, "março") == 0) {
		mesNum = 3;
	} else if (strcasecmp(arvnum[i].meses, "Março") == 0) {
		mesNum = 3;
	} else if (strcasecmp(arvnum[i].meses, "abril") == 0) {
		mesNum = 4;
	} else if (strcasecmp(arvnum[i].meses, "Abril") == 0) {
		mesNum = 4;
	} else if (strcasecmp(arvnum[i].meses, "maio") == 0) {
		mesNum = 5;
	} else if (strcasecmp(arvnum[i].meses, "Maio") == 0) {
		mesNum = 5;
	} else if (strcasecmp(arvnum[i].meses, "junho") == 0) {
		mesNum = 6;
	} else if (strcasecmp(arvnum[i].meses, "Junho") == 0) {
		mesNum = 6;
	} else if (strcasecmp(arvnum[i].meses, "julho") == 0) {
		mesNum = 7;
	} else if (strcasecmp(arvnum[i].meses, "Julho") == 0) {
		mesNum = 7;
	} else if (strcasecmp(arvnum[i].meses, "agosto") == 0) {
		mesNum = 8;
	} else if (strcasecmp(arvnum[i].meses, "Agosto") == 0) {
		mesNum = 8;
	} else if (strcasecmp(arvnum[i].meses, "setembro") == 0) {
		mesNum = 9;
	} else if (strcasecmp(arvnum[i].meses, "Setembro") == 0) {
		mesNum = 9;
	} else if (strcasecmp(arvnum[i].meses, "outubro") == 0) {
		mesNum = 10;
	} else if (strcasecmp(arvnum[i].meses, "Outubro") == 0) {
		mesNum = 10;
	} else if (strcasecmp(arvnum[i].meses, "novembro") == 0) {
		mesNum = 11;
	} else if (strcasecmp(arvnum[i].meses, "Novembro") == 0) {
		mesNum = 11;
	} else if (strcasecmp(arvnum[i].meses, "dezembro") == 0) {
		mesNum = 12;
	} else if (strcasecmp(arvnum[i].meses, "Dezembro") == 0) {
		mesNum = 12;
	} else {
		printf("Mês inválido, digite novamente \n");
		return;
	}
	arvnum[i].mesNum = mesNum;
}

Arv* arv_criavazia(void){
	return NULL;
}

int arv_altura(Arv *a){
	if (a == NULL)
		return 0;
	int hesq = arv_altura(a -> esq);
	int hdir = arv_altura(a -> dir);
	return hesq > hdir ? hesq + 1 : hdir + 1;
}

Arv* arv_cria (int m, Arv* esq, Arv* dir){
	Arv* p=(Arv*)malloc(sizeof(Arv));
	p->mesNum = m;
	p->bal = arv_altura(esq) - arv_altura(dir);
	p->esq = esq;
	p->dir = dir;
	return p;
}

int verifica_AVL(Arv* a) {
  if (a == NULL)
    return 1;
  return abs(arv_altura(a->esq) - arv_altura(a->dir)) <= 1;
}

void escreve(Arv* e) {
	if (e != NULL) {
    	escreve(e->esq);
    	printf("%d(%d)", e-> mesNum, e-> bal);
    	escreve(e->dir);
  }
}

void escreve_verifica(Arv* a) { 
  if (!verifica_AVL(a)) 
    printf("Não AVL!\n");
  escreve(a); 
  printf("\n");
}

void RR(Arv** e) {
  Arv* b = *e;
  Arv* a = b->esq;
  b->esq = a->dir;
  a->dir = b;
  a->bal = 0;
  b->bal = 0;
  *e = a;
}

void LL(Arv** e) {
  Arv* a = *e;
  Arv* b = a->dir;
  a->dir = b->esq;
  b->esq = a;
  a->bal = 0;
  b->bal = 0;
  *e = b;
}

void RL(Arv** e) {
  Arv *c = *e;
  Arv *a = c->esq;
  Arv *b = a->dir;
  c->esq = b->dir;
  a->dir = b->esq;
  b->esq = a;
  b->dir = c;
  switch(b->bal) {
  case -1:
    a->bal = 0;
    c->bal = 1;
    break;
  case 0:
    a->bal = 0;
    c->bal = 0;
    break;
  case +1:
    a->bal = -1;
    c->bal = 0;
    break;
  }
  b->bal = 0;
  *e = b;
}

void LR(Arv** e) {
  Arv *a = *e;
  Arv *c = a->dir;
  Arv *b = c->esq;
  c->esq = b->dir;
  a->dir = b->esq;
  b->esq = a;
  b->dir = c;
  switch(b->bal) {
  case -1:
    a->bal = 0;
    c->bal = 1;
    break;
  case 0:
    a->bal = 0;
    c->bal = 0;
    break;
  case +1:
    a->bal = -1;
    c->bal = 0;
    break;
  }
  b->bal = 0;
  *e = b;  
}

int arv_insere(Arv** a, int mesNum , int *cresceu) {
  if (*a == NULL) {
    *a = arv_cria(mesNum, NULL, NULL);
    *cresceu = 1;
    return 1;
  }
    
  if (mesNum == (*a)->mesNum) 
    return 0;

  if (mesNum < (*a) -> mesNum) {
    if (arv_insere(&(*a)->esq, mesNum, cresceu)) {
      if (*cresceu) {
	switch ((*a)->bal) {
	case -1:
	  if ((*a)->esq->bal == -1)
	    LL(a);
	  else
	    LR(a);
	  *cresceu = 0;
	  break;
	case 0:
	  (*a)->bal = -1;
	  *cresceu = 1;
	  break;
	case +1:
	  (*a)->bal = 0;
	  *cresceu = 0;
	  break;
	}
      }
      return 1;
    }
    else
      return 0;
  }
  
  if (arv_insere(&(*a)->dir, mesNum, cresceu)) {
      if (*cresceu) {
	switch ((*a)->bal) {
	case -1:
	  (*a)->bal = 0;
	  *cresceu = 0;
	  break;
	case 0:
	  (*a)->bal = +1;
	  *cresceu = 1;
	  break;
	case +1:
	  if ((*a)->dir->bal == +1)
	    RR(a);
	  else
	    RL(a);
	  *cresceu = 0;
	  break;
	}
      }
      return 1;
    }
    else
      return 0;
}


int insere(Arv **a, int mesNum) {
  int cresceu;
  return arv_insere(a, mesNum, &cresceu);
}

