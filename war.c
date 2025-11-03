#include <stdio.h>     
#include <stdlib.h>    
#include <string.h>    
#include <time.h>      
#include <locale.h>    
#define NUM_TERRITORIOS 5
#define NUM_MISSOES 3
#define TAM_NOME 30
#define TAM_COR 10
typedef struct {
    char nome[TAM_NOME];
    char cor[TAM_COR];
    int tropas;
} Territorio;
Territorio* alocarMapa();
void inicializarTerritorios(Territorio* mapa);
void liberarMemoria(Territorio* mapa);
void exibirMenuPrincipal();
void exibirMapa(const Territorio* mapa);
void exibirMissao(int idMissao);
void faseDeAtaque(Territorio* mapa);
void simularAtaque(Territorio* atacante, Territorio* defensor);
int sortearMissao();
int verificarVitoria(const Territorio* mapa, int idMissao, const char* corJogador);
void limparBufferEntrada();
int main() {
    setlocale(LC_ALL, "Portuguese"); // Permite acentuação
    srand(time(NULL));               // Inicializa o gerador de números aleatórios

    Territorio* mapa = alocarMapa(); // Alocação dinâmica
    if (mapa == NULL) {
        printf("Erro ao alocar memória!\n");
        return 1;
    }

    inicializarTerritorios(mapa);    // Preenche os territórios
    char corJogador[TAM_COR] = "Vermelho";  // Exemplo fixo (poderia ser escolhido)
    int missao = sortearMissao();    // Sorteia missão

    int opcao;
    int venceu = 0;

    do {
        exibirMapa(mapa);
        exibirMissao(missao);
        exibirMenuPrincipal();
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        limparBufferEntrada();

        switch (opcao) {
            case 1:
                faseDeAtaque(mapa);
                break;
            case 2:
                venceu = verificarVitoria(mapa, missao, corJogador);
                if (venceu)
                    printf("\n🎉 Parabéns! Você cumpriu sua missão!\n");
                else
                    printf("\nMissão ainda não concluída.\n");
                break;
            case 0:
                printf("\nEncerrando o jogo...\n");
                break;
            default:
                printf("Opção inválida!\n");
        }

        if (opcao != 0) {
            printf("\nPressione ENTER para continuar...");
            getchar();
        }

    } while (opcao != 0 && !venceu);

    liberarMemoria(mapa); // Libera memória alocada
    return 0;
}
Territorio* alocarMapa() {
    return (Territorio*) calloc(NUM_TERRITORIOS, sizeof(Territorio));
}

void inicializarTerritorios(Territorio* mapa) {
    for (int i = 0; i < NUM_TERRITORIOS; i++) {
        sprintf(mapa[i].nome, "Territorio %d", i + 1);
        strcpy(mapa[i].cor, "Neutro");
        mapa[i].tropas = rand() % 5 + 1;
    }
}

void liberarMemoria(Territorio* mapa) {
    free(mapa);
}

void exibirMapa(const Territorio* mapa) {
    printf("\n===== ESTADO ATUAL DO MAPA =====\n");
    for (int i = 0; i < NUM_TERRITORIOS; i++) {
        printf("%d. %-15s | Cor: %-10s | Tropas: %d\n", 
               i + 1, mapa[i].nome, mapa[i].cor, mapa[i].tropas);
    }
}

void exibirMenuPrincipal() {
    printf("\n===== MENU PRINCIPAL =====\n");
    printf("1 - Atacar\n");
    printf("2 - Verificar missão\n");
    printf("0 - Sair\n");
}

void exibirMissao(int idMissao) {
    printf("\n🎯 Missão %d: ", idMissao);
    switch (idMissao) {
        case 1: printf("Conquistar 3 territórios inimigos.\n"); break;
        case 2: printf("Eliminar o exército azul.\n"); break;
        case 3: printf("Controlar todos os territórios.\n"); break;
    }
}

void limparBufferEntrada() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int sortearMissao() {
    return rand() % NUM_MISSOES + 1;
}

int verificarVitoria(const Territorio* mapa, int idMissao, const char* corJogador) {
    // Lógica simples para exemplo
    int conquistados = 0;
    for (int i = 0; i < NUM_TERRITORIOS; i++) {
        if (strcmp(mapa[i].cor, corJogador) == 0)
            conquistados++;
    }
    if (idMissao == 1 && conquistados >= 3) return 1;
    if (idMissao == 3 && conquistados == NUM_TERRITORIOS) return 1;
    return 0;
}
