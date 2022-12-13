#include <stdio.h>
#include <stdlib.h>
#include "heap.h"

HEAP* HEAP_create(int heapTam, COMP* compara) {
    HEAP* novo = malloc(sizeof(HEAP));
    novo -> tam = heapTam;
    novo -> comparador = compara;   //função de comparação
    novo -> numElems = 0;
    novo -> elems = malloc(sizeof(void*) * heapTam);

    for (int i = 0; i < heapTam; i++) { //apontando todos os elementos para NULL
        novo -> elems[i] = NULL;
    }

    return novo;
}

void HEAP_add(HEAP* heap, void* newelem) {
    if (heap->numElems < heap->tam) { //caso ainda haja espaço na heap
        if (heap->numElems == 0) {    //quando a heap estiver vazia o elemento será inserido no começo
            heap->elems[0] = newelem;
            heap->numElems++;
        }

        else {   //para outros casos
            heap->elems[heap->numElems] = newelem;  //inicialmente o novo elemento é inserido no final da heap
            heap->numElems++;
            int pai = heap->numElems;
            for (int i = heap->numElems - 1; i > 0; i = i / 2) { //em seguida ocorrerá o processo de caminhada para encontrar a posição correta
                if (heap->comparador(heap->elems[i], heap->elems[i / 2]) == 1) {    //caso o elemento atual seja menor que o pai
                    void* aux = heap->elems[i];         //reorganização dos elementos
                    heap->elems[i] = heap->elems[i / 2];
                    heap->elems[i / 2] = aux;
                }
            }
        }
    }

    else {
        printf("Não é possivel adicionar mais elementos, a Heap está cheia.\n");
    }
}

void* HEAP_remove(HEAP* heap) {                         //caso a heap não esteja vazia
    if (heap->numElems > 0) { 
        int pai = 0;                                  //raiz da arvore(pai)
        int filho = (pai * 2) + 1;                  
        void* lixo = heap->elems[0];                //remoção do primeiro elemento
        heap-> elems[0] = heap->elems[heap->numElems - 1];  //o último elemento se tornará o primeiro
        heap-> elems[heap->numElems - 1] = lixo;  //o elemento a ser removido se torna o último
        heap-> numElems--;
        
        while(filho < heap->numElems){                      //loop para verificar se há elemento menor na direita
            if (filho + 1 < heap->numElems){                
                if (heap-> comparador(heap-> elems[filho], //comparação entre o filho atual e o próximo
                    heap -> elems[filho + 1]) < 0){       //caso o próximo filho seja maior que o atual a variavel "filho" será atualizada para ele
                    filho++;                                                                             
                }
            }
            
            else if (heap->comparador(heap->elems[pai], heap->elems[filho]) < 0){ //caso o atual filho seja menor que o atual pai
                void* aux = heap->elems[pai];
                //reorganização da heap
                heap->elems[pai] = heap->elems[filho];   //o pai se tornará o filho e o antigo filho se tornará o pai
                heap->elems[filho] = aux;               
                pai = filho;                             
                filho = (2 * pai) + 1;                       
            }
            
            else {  //caso nenhum dos casos seja satisfeito a função encerrará
                break;
            }
        }
	    return lixo;
    }
}
 

