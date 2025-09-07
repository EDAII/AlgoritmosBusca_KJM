#include <stdbool.h>

bool podeDividir(int* nums, int numsSize, int k, long long somaMaximaPermitida) {
    int subarraysNecessarios = 1;
    long long somaAtual = 0;

    for (int i = 0; i < numsSize; i++) {
        somaAtual += nums[i];
        if (somaAtual > somaMaximaPermitida) {
            subarraysNecessarios++;
            somaAtual = nums[i];
        }
    }
    return subarraysNecessarios <= k;
}

int splitArray(int* nums, int numsSize, int k) {
    long long inicioBusca = 0;
    long long fimBusca = 0;

    for (int i = 0; i < numsSize; i++) {
        if (nums[i] > inicioBusca) {
            inicioBusca = nums[i];
        }
        fimBusca += nums[i];
    }

    long long melhorResposta = fimBusca;

    while (inicioBusca <= fimBusca) {
        long long meio = inicioBusca + (fimBusca - inicioBusca) / 2;

        if (podeDividir(nums, numsSize, k, meio)) {
            melhorResposta = meio;
            fimBusca = meio - 1;
        } else {
            inicioBusca = meio + 1;
        }
    }

    return (int)melhorResposta;
}
