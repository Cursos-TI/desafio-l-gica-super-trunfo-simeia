// super_trunfo.c
// Versao "iniciante": direto, sem frescura, mas faz o que o PDF pede.

#include <stdio.h>

int main() {
    // CARTA 1
    char estado1;
    char codigo1[5];   // ex: A01
    char cidade1[60];  // com espacos
    unsigned long int pop1; // pedido: unsigned long int
    float area1, pib1;
    int pontos1;

    // derivados
    float dens1, pibcap1, invdens1, super1;

    // CARTA 2
    char estado2;
    char codigo2[5];
    char cidade2[60];
    unsigned long int pop2;
    float area2, pib2;
    int pontos2;

    float dens2, pibcap2, invdens2, super2;

    // ---- entrada carta 1
    printf("== Carta 1 ==\n");
    printf("Estado (A-H): ");
    scanf(" %c", &estado1);

    printf("Codigo (A01..H04): ");
    scanf(" %4s", codigo1);

    printf("Nome da cidade: ");
    scanf(" %59[^\n]", cidade1);

    printf("Populacao: ");
    scanf("%lu", &pop1);

    printf("Area (km2): ");
    scanf("%f", &area1);

    printf("PIB: ");
    scanf("%f", &pib1);

    printf("Pontos turisticos: ");
    scanf("%d", &pontos1);

    // ---- entrada carta 2
    printf("\n== Carta 2 ==\n");
    printf("Estado (A-H): ");
    scanf(" %c", &estado2);

    printf("Codigo (A01..H04): ");
    scanf(" %4s", codigo2);

    printf("Nome da cidade: ");
    scanf(" %59[^\n]", cidade2);

    printf("Populacao: ");
    scanf("%lu", &pop2);

    printf("Area (km2): ");
    scanf("%f", &area2);

    printf("PIB: ");
    scanf("%f", &pib2);

    printf("Pontos turisticos: ");
    scanf("%d", &pontos2);

    // ---- calculos (sem if, como solicitado por voce)
    dens1 = (float)pop1 / area1;       // hab/km2
    pibcap1 = pib1 / (float)pop1;      // per capita
    invdens1 = 1.0f / dens1;           // inverso (menor densidade => maior inverso)
    super1 = (float)pop1 + area1 + pib1 + (float)pontos1 + pibcap1 + invdens1; // soma heterogenea

    dens2 = (float)pop2 / area2;
    pibcap2 = pib2 / (float)pop2;
    invdens2 = 1.0f / dens2;
    super2 = (float)pop2 + area2 + pib2 + (float)pontos2 + pibcap2 + invdens2;

    // ---- exibicao simples
    printf("\n--- CARTA 1 ---\n");
    printf("Estado: %c\nCodigo: %s\nCidade: %s\n", estado1, codigo1, cidade1);
    printf("Populacao: %lu\nArea: %.2f\nPIB: %.2f\nPontos: %d\n", pop1, area1, pib1, pontos1);
    printf("Densidade: %.2f\nPIB per capita: %.2f\nSuper Poder: %.2f\n", dens1, pibcap1, super1);

    printf("\n--- CARTA 2 ---\n");
    printf("Estado: %c\nCodigo: %s\nCidade: %s\n", estado2, codigo2, cidade2);
    printf("Populacao: %lu\nArea: %.2f\nPIB: %.2f\nPontos: %d\n", pop2, area2, pib2, pontos2);
    printf("Densidade: %.2f\nPIB per capita: %.2f\nSuper Poder: %.2f\n", dens2, pibcap2, super2);

    // ---- comparacoes (1 = Carta 1 venceu, 0 = Carta 2 venceu)
    // Regra especial: densidade MENOR vence; demais MAIOR vence.
    printf("\n=== Comparacao de Cartas ===\n");
    printf("Populacao: %d\n", (pop1 > pop2));
    printf("Area: %d\n", (area1 > area2));
    printf("PIB: %d\n", (pib1 > pib2));
    printf("Pontos Turisticos: %d\n", (pontos1 > pontos2));
    printf("Densidade (menor vence): %d\n", (dens1 < dens2));
    printf("PIB per Capita: %d\n", (pibcap1 > pibcap2));
    printf("Super Poder: %d\n", (super1 > super2));

    return 0;
}