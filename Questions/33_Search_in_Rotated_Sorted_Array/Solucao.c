#include <math.h>

int buscaSequencialNoBloco(int* numeros, int inicio, int fim, int alvo) {
    for (int i = inicio; i <= fim; i++) {
        if (numeros[i] == alvo) {
            return i;
        }
    }
    return -1;
}


int search(int* nums, int numsSize, int target) {
    if (numsSize <= 0) {
        return -1;
    }

    int tamanhoDoBloco = (int)sqrt(numsSize);
    if (tamanhoDoBloco == 0) {
        tamanhoDoBloco = 1;
    }

    for (int i = 0; i < numsSize; i += tamanhoDoBloco) {
        int indiceInicio = i;
        int indiceFim = i + tamanhoDoBloco - 1;

        if (indiceFim >= numsSize) {
            indiceFim = numsSize - 1;
        }

        int primeiroElemento = nums[indiceInicio];
        int ultimoElemento = nums[indiceFim];

        if (primeiroElemento <= ultimoElemento) {
            if (target >= primeiroElemento && target <= ultimoElemento) {
                return buscaSequencialNoBloco(nums, indiceInicio, indiceFim, target);
            }
        }
        else { 
            if (target >= primeiroElemento || target <= ultimoElemento) {
                return buscaSequencialNoBloco(nums, indiceInicio, indiceFim, target);
            }
        }
    }
    
    return -1;
}