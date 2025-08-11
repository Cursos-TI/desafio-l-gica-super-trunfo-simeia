// super_trunfo_mestre.c
#include <stdio.h>

int main() {
    // Mesmos campos do Tema 2
    char estado1 = 'A', codigo1[4] = "A01", cidade1[30] = "Cidade Alpha";
    unsigned long populacao1 = 1200000;
    float area1 = 800.0f, pib1 = 50.0f; // bilhoes
    int pontos1 = 12;

    char estado2 = 'B', codigo2[4] = "B02", cidade2[30] = "Cidade Beta";
    unsigned long populacao2 = 900000;
    float area2 = 600.0f, pib2 = 40.0f; // bilhoes
    int pontos2 = 10;

    // Derivados
    float densidade1 = (area1 > 0) ? ((float)populacao1 / area1) : 0.0f;
    float densidade2 = (area2 > 0) ? ((float)populacao2 / area2) : 0.0f;
    float pibPerCapita1 = (populacao1 > 0) ? (pib1 * 1e9f / (float)populacao1) : 0.0f;
    float pibPerCapita2 = (populacao2 > 0) ? (pib2 * 1e9f / (float)populacao2) : 0.0f;

    // Menu 1
    int a1, a2;
    printf("Escolha o 1o atributo:\n");
    printf("1-Populacao  2-Area  3-PIB  4-Pontos  5-Densidade(menor vence)  6-PIB per capita\n");
    printf("Opcao: ");
    if (scanf("%d", &a1) != 1 || a1 < 1 || a1 > 6) { printf("Opcao invalida.\n"); return 0; }

    // Menu 2 (dinamico): não repete o primeiro
    printf("\nEscolha o 2o atributo (diferente do primeiro):\n");
    for (int i = 1; i <= 6; i++) {
        if (i != a1) {
            switch(i){
                case 1: printf("1-Populacao  "); break;
                case 2: printf("2-Area  "); break;
                case 3: printf("3-PIB  "); break;
                case 4: printf("4-Pontos  "); break;
                case 5: printf("5-Densidade  "); break;
                case 6: printf("6-PIB per capita  "); break;
            }
        }
    }
    printf("\nOpcao: ");
    if (scanf("%d", &a2) != 1 || a2 < 1 || a2 > 6 || a2 == a1) { printf("Opcao invalida.\n"); return 0; }

    // Funçãozinha inline (via switch+ternário) para comparar um atributo
    // Retorna:  1 se Carta1 vence; 2 se Carta2 vence; 0 se empate
    auto int compara(int tipo) {
        switch (tipo) {
            case 1: // População (maior vence)
                if (populacao1 == populacao2) return 0;
                return (populacao1 > populacao2) ? 1 : 2;
            case 2: // Área (maior vence)
                if (area1 == area2) return 0;
                return (area1 > area2) ? 1 : 2;
            case 3: // PIB (maior vence)
                if (pib1 == pib2) return 0;
                return (pib1 > pib2) ? 1 : 2;
            case 4: // Pontos (maior vence)
                if (pontos1 == pontos2) return 0;
                return (pontos1 > pontos2) ? 1 : 2;
            case 5: // Densidade (menor vence)
                if (densidade1 == densidade2) return 0;
                return (densidade1 < densidade2) ? 1 : 2;
            case 6: // PIB per capita (maior vence)
                if (pibPerCapita1 == pibPerCapita2) return 0;
                return (pibPerCapita1 > pibPerCapita2) ? 1 : 2;
        }
        return 0;
    }

    // Mostra os dois atributos e vencedores individuais
    int r1 = compara(a1);
    int r2 = compara(a2);

    printf("\nComparando %s (%c) x %s (%c)\n", cidade1, estado1, cidade2, estado2);
    auto void mostraNome(int tipo){
        switch(tipo){
            case 1: printf("Populacao"); break;
            case 2: printf("Area"); break;
            case 3: printf("PIB"); break;
            case 4: printf("Pontos Turisticos"); break;
            case 5: printf("Densidade"); break;
            case 6: printf("PIB per capita"); break;
        }
    }

    printf("Atributo 1: "); mostraNome(a1); printf(" -> ");
    if (r1 == 1) printf("Carta 1 venceu\n");
    else if (r1 == 2) printf("Carta 2 venceu\n");
    else printf("Empate\n");

    printf("Atributo 2: "); mostraNome(a2); printf(" -> ");
    if (r2 == 1) printf("Carta 1 venceu\n");
    else if (r2 == 2) printf("Carta 2 venceu\n");
    else printf("Empate\n");

    // ===== Soma dos atributos (normalizacao bem simples) =====
    // Normalizo cada atributo por um fator fixo só para manter as ordens e poder somar.
    auto float valorNorm(int tipo, int carta) {
        // pega valor bruto
        float v = 0.0f;
        if (tipo == 1) v = (carta==1)? (float)populacao1 : (float)populacao2;            // ~1e6
        if (tipo == 2) v = (carta==1)? area1 : area2;                                     // ~1e3
        if (tipo == 3) v = (carta==1)? pib1 : pib2;                                       // ~1e2 (bilhoes)
        if (tipo == 4) v = (carta==1)? (float)pontos1 : (float)pontos2;                   // dezenas
        if (tipo == 5) v = (carta==1)? densidade1 : densidade2;                           // ~10^3-10^4
        if (tipo == 6) v = (carta==1)? pibPerCapita1 : pibPerCapita2;                     // ~10^4-10^5

        // Para Densidade (menor é melhor), inverto de forma simples:
        if (tipo == 5) v = (v > 0.0f)? (1.0f / v) : 0.0f;

        // divide por um fator para todas ficarem na mesma ordem de grandeza (bem simples)
        if (tipo == 1) v /= 1000000.0f;
        if (tipo == 2) v /= 1000.0f;
        if (tipo == 3) v /= 10.0f;
        if (tipo == 4) v /= 10.0f;
        if (tipo == 5) v *= 1000.0f;     // densidade invertida costuma ficar pequena; multiplico um pouco
        if (tipo == 6) v /= 10000.0f;

        return v;
    }

    float soma1 = valorNorm(a1, 1) + valorNorm(a2, 1);
    float soma2 = valorNorm(a1, 2) + valorNorm(a2, 2);

    printf("\nSoma normalizada dos dois atributos:\n");
    printf("Carta 1: %.3f\n", soma1);
    printf("Carta 2: %.3f\n", soma2);

    if (soma1 > soma2) printf("Resultado FINAL: Carta 1 venceu a rodada!\n");
    else if (soma2 > soma1) printf("Resultado FINAL: Carta 2 venceu a rodada!\n");
    else printf("Resultado FINAL: Empate!\n");

    return 0;
}