#ifndef _PILHA_  			 
#define _PILHA_

#define TAM 4

void init(int *pilha, int dado) {

	int a;

	if(dado == 1) {
		dado *= 8;
		for(a=0; a<TAM; a++, dado-=2) { pilha[a] = dado; }
	}
	else {
		for(a=0; a<TAM; a++) { pilha[a] = -1; }
	}
}

void push(int *pilha, int dado) {

}

int pop(int *pilha) {

	return 0;
}

int getDado(int *pilha, int pos) {

	if(pos >= 0 && pos < 4) {
		return pilha[pos];
	}

	return -1;
}

#endif 
