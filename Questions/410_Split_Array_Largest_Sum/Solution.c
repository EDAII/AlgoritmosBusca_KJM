#include <stdbool.h>

static inline int contarSubarraysNecessarios(int* numeros, int tamanho, long long limite) {
    int contagem = 1;
    long long somaAtual = 0;
    for (int i = 0; i < tamanho; i++) {
        somaAtual += numeros[i];
        if (somaAtual > limite) {
            contagem++;
            somaAtual = numeros[i];
        }
    }
    return contagem;
}

int splitArray(int* numeros, int tamanho, int quantidadeSubarrays) {
    long long limiteInferior = 0;
    long long limiteSuperior = 0;

    for (int i = 0; i < tamanho; i++) {
        if (numeros[i] > limiteInferior) limiteInferior = numeros[i];
        limiteSuperior += numeros[i];
    }

    int subarraysEmLimiteInferior = contarSubarraysNecessarios(numeros, tamanho, limiteInferior);
    if (subarraysEmLimiteInferior <= quantidadeSubarrays) return (int)limiteInferior;

    int subarraysEmLimiteSuperior = 1;

    while (limiteInferior + 1 < limiteSuperior) {
        long long intervalo = limiteSuperior - limiteInferior;

        double denominador = (double)(subarraysEmLimiteInferior - subarraysEmLimiteSuperior);
        long long palpite;
        if (denominador <= 0.0) {
            palpite = limiteInferior + intervalo / 2;
        } else {
            double fatorInterpolacao = (double)(quantidadeSubarrays - subarraysEmLimiteInferior) / denominador;
            if (fatorInterpolacao < 0.0) fatorInterpolacao = 0.0;
            if (fatorInterpolacao > 1.0) fatorInterpolacao = 1.0;
            long long estimativa = limiteInferior + (long long)(fatorInterpolacao * (double)intervalo);

            long long margem = intervalo / 4;
            long long minPalpite = limiteInferior + margem;
            long long maxPalpite = limiteSuperior - margem;
            if (minPalpite <= limiteInferior) minPalpite = limiteInferior + 1;
            if (maxPalpite >= limiteSuperior) maxPalpite = limiteSuperior - 1;

            if (estimativa < minPalpite) estimativa = minPalpite;
            if (estimativa > maxPalpite) estimativa = maxPalpite;

            if (estimativa <= limiteInferior) estimativa = limiteInferior + 1;
            if (estimativa >= limiteSuperior) estimativa = limiteSuperior - 1;
            palpite = estimativa;
        }

        int subarraysEmPalpite = contarSubarraysNecessarios(numeros, tamanho, palpite);
        if (subarraysEmPalpite <= quantidadeSubarrays) {
            limiteSuperior = palpite;
            subarraysEmLimiteSuperior = subarraysEmPalpite;
        } else {
            limiteInferior = palpite;
            subarraysEmLimiteInferior = subarraysEmPalpite;
        }
    }

    return (int)limiteSuperior;
}
