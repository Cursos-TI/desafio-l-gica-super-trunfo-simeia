// super_trunfo.c
// Super Trunfo - Nivel Mestre (versão "gente de verdade": funciona, mas sem preciosismo exagerado)

#include <stdio.h>
#include <string.h>

// não vou criar mil structs e funções, mas um struct ajuda a não virar salada
typedef struct {
    char estado;                 // 'A'..'H'
    char codigo[8];              // A01..H04 (8 é overkill, ok)
    char cidade[64];             // nome da cidade (com espaços)
    unsigned long int populacao; // nível mestre pede tipo sem sinal e "longo"
    double area;                 // km²
    double pib;                  // tanto faz a unidade, o usuário sabe o que digita
    int pontos;

    // derivados
    double densidade;    // pop/area
    double pib_percap;   // pib/pop
    double super_poder;  // soma híbrida com casting
} Carta;

static void ler_linha(char *buf, size_t n) {
    if (fgets(buf, (int)n, stdin)) {
        size_t k = strcspn(buf, "\n");
        buf[k] = '\0';
    }
}

int main(void) {
    Carta c1, c2;

    // ---- Entrada Carta 1
    printf("=== Carta 1 ===\n");
    printf("Estado (A-H): ");
    scanf(" %c", &c1.estado);

    printf("Codigo (ex: A01): ");
    scanf("%7s", c1.codigo);

    // consome \n pendente antes de ler linha com espaços
    int ch; while ((ch = getchar()) != '\n' && ch != EOF) {}

    printf("Nome da Cidade: ");
    ler_linha(c1.cidade, sizeof(c1.cidade));

    printf("Populacao (inteira, >=0): ");
    scanf("%lu", &c1.populacao);

    printf("Area (km2): ");
    scanf("%lf", &c1.area);

    printf("PIB (mesma unidade para ambas as cartas): ");
    scanf("%lf", &c1.pib);

    printf("Pontos turisticos (int): ");
    scanf("%d", &c1.pontos);

    // ---- Entrada Carta 2
    printf("\n=== Carta 2 ===\n");
    printf("Estado (A-H): ");
    scanf(" %c", &c2.estado);

    printf("Codigo (ex: B03): ");
    scanf("%7s", c2.codigo);

    while ((ch = getchar()) != '\n' && ch != EOF) {}

    printf("Nome da Cidade: ");
    ler_linha(c2.cidade, sizeof(c2.cidade));

    printf("Populacao (inteira, >=0): ");
    scanf("%lu", &c2.populacao);

    printf("Area (km2): ");
    scanf("%lf", &c2.area);

    printf("PIB (mesma unidade para ambas as cartas): ");
    scanf("%lf", &c2.pib);

    printf("Pontos turisticos (int): ");
    scanf("%d", &c2.pontos);

    // ---- Derivados (sem if/else; protecao simples com operador ternario)
    c1.densidade  = (c1.area > 0.0) ? ( (double)c1.populacao / c1.area ) : 0.0;
    c2.densidade  = (c2.area > 0.0) ? ( (double)c2.populacao / c2.area ) : 0.0;

    c1.pib_percap = (c1.populacao > 0UL) ? ( c1.pib / (double)c1.populacao ) : 0.0;
    c2.pib_percap = (c2.populacao > 0UL) ? ( c2.pib / (double)c2.populacao ) : 0.0;

    // inverso da densidade = 1/densidade = area/populacao (quando pop>0)
    double inv_dens1 = (c1.populacao > 0UL) ? ( c1.area / (double)c1.populacao ) : 0.0;
    double inv_dens2 = (c2.populacao > 0UL) ? ( c2.area / (double)c2.populacao ) : 0.0;

    // Super Poder = soma de TUDO que é numerico (atenção aos tipos)
    // pop (UL) + area (double) + pib (double) + pontos (int) + pib_percap (double) + inv_dens (double)
    // sim, as unidades ficam misturadas… o enunciado quer assim.
    c1.super_poder = (double)c1.populacao + c1.area + c1.pib + (double)c1.pontos + c1.pib_percap + inv_dens1;
    c2.super_poder = (double)c2.populacao + c2.area + c2.pib + (double)c2.pontos + c2.pib_percap + inv_dens2;

    // ---- Exibição “bonitinha o suficiente”
    printf("\n--- CARTA 1 ---\n");
    printf("Estado: %c\nCodigo: %s\nCidade: %s\n", c1.estado, c1.codigo, c1.cidade);
    printf("Populacao: %lu\nArea: %.2f km2\nPIB: %.2f\nPontos: %d\n", c1.populacao, c1.area, c1.pib, c1.pontos);
    printf("Densidade: %.2f hab/km2\nPIB per capita: %.2f\nSuper Poder: %.2f\n",
           c1.densidade, c1.pib_percap, c1.super_poder);

    printf("\n--- CARTA 2 ---\n");
    printf("Estado: %c\nCodigo: %s\nCidade: %s\n", c2.estado, c2.codigo, c2.cidade);
    printf("Populacao: %lu\nArea: %.2f km2\nPIB: %.2f\nPontos: %d\n", c2.populacao, c2.area, c2.pib, c2.pontos);
    printf("Densidade: %.2f hab/km2\nPIB per capita: %.2f\nSuper Poder: %.2f\n",
           c2.densidade, c2.pib_percap, c2.super_poder);

    // ---- Comparações (sem if). 1 -> Carta 1 venceu ; 0 -> Carta 2 venceu
    // regra especial: DENSIDADE MENOR vence. Demais: MAIOR vence.
    int v_pop   = (c1.populacao  > c2.populacao);
    int v_area  = (c1.area       > c2.area);
    int v_pib   = (c1.pib        > c2.pib);
    int v_pts   = (c1.pontos     > c2.pontos);
    int v_dens  = (c1.densidade  < c2.densidade); // invertido
    int v_pc    = (c1.pib_percap > c2.pib_percap);
    int v_power = (c1.super_poder> c2.super_poder);

    printf("\n=== Comparacao de Cartas ===\n");
    printf("Populacao: Carta 1 venceu (%d)\n", v_pop);
    printf("Area: Carta 1 venceu (%d)\n", v_area);
    printf("PIB: Carta 1 venceu (%d)\n", v_pib);
    printf("Pontos Turisticos: Carta 1 venceu (%d)\n", v_pts);
    printf("Densidade Populacional: Carta 1 venceu (%d)\n", v_dens);
    printf("PIB per Capita: Carta 1 venceu (%d)\n", v_pc);
    printf("Super Poder: Carta 1 venceu (%d)\n", v_power);

    // pronto. sem if/else, usando operadores relacionais e tipos certos.
    return 0;
}