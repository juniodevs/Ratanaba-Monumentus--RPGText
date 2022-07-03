#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include <locale.h>
#include "asciiarte.h"

struct personagem {
    char name[18];
    int pvjogador;
    int ataque;
    int ataquemagico;
    int adagas;
    int defesa;
    int nivel;
    int espada;
    int gold;
    int pocao;
}player; //STRUCT PARA CRIAÇÃO DE PERSONAGEM
struct enemy {
    char name[18];
    int pv;
    int ataque;
    int defesa;
}inimigo; //PRE DEFINIÇÃO DE INIMIGO

// loja(struct personagem *player){
//     printf("#########################");
//     printf("Seja bem vindo a loja!#\n");
//     printf("Voce tem %d gold#\n", player->gold);
//     printf("Opcoes\n");
//     printf("#1 - Aprimorar espada - 10c - o Aprimoramento aumenta sua espada em 1 de dano\n");
// } //LOJA DE APRIMORAMENTO DE ITENS

verificacaodemorte(struct personagem *player, struct enemy *enemy) {
    int coinsareceber = 0;
    if (player->pvjogador <= 0) {
        printf("\n%s morreu\n", player->name);
        DialogocomClear("#########################\nVoce perdeu o jogo!\n#########################", 0);
        Dialogo("3 2 1", 1);
        
        system("cls");
        carregarjogo(&player, &inimigo);
    }
    if (enemy->pv <= 0) {
        printf("\n%s", enemy->name); Dialogo(" Morreu!", 0);
        Dialogo("\n1", 1);
        Dialogo("\n2", 1);
        Dialogo("\n3", 1);
        coinsareceber = (rand()%10) + 10;
        
        Dialogo("\nVoce recebeu ", 0); printf("%d ",coinsareceber); Dialogo ("de coins\n", 0);

        player->gold = player->gold + coinsareceber;
        system("pause");
        system("cls");
    }
}//FUNÇÃO DE VERIFICAÇÃO DE MORTE (PERSONAGEM E INIMIGO)
regeneracao(struct personagem *player){
    if (player->pocao <= 0)
    {
        Dialogo("Voce nao tem pocao de vida",0);
    }
    else
    {
        player->pvjogador = 20;
        printf("#########################\n");
        printf("#Voce regenerou seu pv#\n");
        printf("#########################");
        player->pocao--;
    }
} //FUNÇÃO DE REGENERAÇÃO DE PV (PERSONAGEM)

salvarjogo(struct personagem *player, struct enemy *enemy) {
    FILE *save;
    save = fopen("salvamento.txt", "w");
    fprintf(save, "nome: %s\n", player->name);
    fprintf(save, "vida: %d\n", player->pvjogador);
    fprintf(save, "nivel: %d\n", player->nivel);
    fprintf(save, "ataque: %d\n", player->ataque);
    fprintf(save, "coins: %d\n", player->gold);
    fprintf(save, "defesa: %d\n", player->defesa);
    fprintf(save, "espada: %d\n", player->espada);
    fprintf(save, "pocoes: %d\n", player->pocao);
    fprintf(save, "nomeinimigo: %s\n", enemy->name);
    fprintf(save, "vidainimigo: %d\n", enemy->pv);
    fprintf(save, "ataqueinimigo: %d\n", enemy->ataque);
    fprintf(save, "defesainimigo: %d\n", enemy->defesa);
    fclose(save);
} //FUNÇÃO DE SALVAR JOGO

carregarjogo(struct personagem *player, struct enemy *enemy) {
    FILE *save;
    save = fopen("salvamento.txt", "r");
    fscanf(save, "nome: %s\n", player->name);
    fscanf(save, "vida: %d\n", &player->pvjogador);
    fscanf(save, "nivel: %d\n", &player->nivel);
    fscanf(save, "ataque: %d\n", &player->ataque);
    fscanf(save, "defesa: %d\n", &player->defesa);
    fscanf(save, "coins: %d\n", &player->gold);
    fscanf(save, "espada: %d\n", &player->espada);
    fscanf(save, "pocoes: %s\n", &player->pocao);
    fscanf(save, "nomeinimigo: %s\n", enemy->name);
    fscanf(save, "vidainimigo: %d\n", &enemy->pv);
    fscanf(save, "ataqueinimigo: %d\n", &enemy->ataque);
    fscanf(save, "defesainimigo: %d\n", &enemy->defesa);
    fclose(save);
    nivel(player, enemy);
} //FUNÇÃO DE CARREGAR JOGO

resetenemy(struct enemy *enemy) {
    enemy->pv = 7 + rand()%10;
    enemy->ataque = 3 + rand()%5;
    enemy->defesa = 2 + rand()%2;
} //FUNÇÃO DE RESET DE INIMIGO VIDA/ATAQUE/DEFESA

resetvida(struct personagem *player) {
    player->pvjogador = 20;
    player->ataque = 8;
    player->espada = 1;
    player->defesa = 1;
    player->pocao = 3;
} //FUNÇÃO DE RESET DE VIDA/ATAQUE DE PERSONAGEM DEPOIS DE BATALHAS

delay(int ms) {
    clock_t start = clock();
    while (clock() < start + ms);
} //FUNÇÃO DE ATRASO (BETA)

atacar(struct personagem *player, struct enemy *enemy) {
    int dano = 0;
    player->espada = 1 + (rand()%2);
    player->ataque = 5+(rand()%10);
    dano = (player->espada + player->ataque) - enemy->defesa;
    enemy->pv = enemy->pv - dano;
    printf("\n%s", player->name); Dialogo("atacou", 0); printf(" %s", enemy->name); Dialogo(" e causou", 0); printf(" %d ", dano); Dialogo("de dano", 0);
    delay(5000);
} //FUNÇÃO DE ATAQUE (PERSONAGEM X INIMIGO)

ataquemagico(struct personagem *player, struct enemy *enemy) {
    int dano = 0;
    player->ataquemagico = 10 + (rand()%10);
    dano = (player->ataquemagico) - enemy->defesa;
    enemy->pv = enemy->pv - dano;
    printf("\n%s", player->name); Dialogo("atacou", 0); printf(" %s", enemy->name); Dialogo(" e causou", 0); printf(" %d ", dano); Dialogo("de dano\n", 0);
    
    player->ataquemagico--;
} //ATAQUE MAGICO

receberataque(struct personagem *player, struct enemy *enemy) {
    int dano = 0;
    dano = enemy->ataque - player->defesa;
    if (dano <= 0) {
        dano = 0;
        printf("\n%s nao conseguiu atacar %s\n", enemy->name, player->name);

        delay(5000);
    }
    else
    {
        player->pvjogador = player->pvjogador - dano;
        
        printf("\n%s recebeu um ataque de %s e causou %d de dano\n", player->name, enemy->name, dano);
        delay(5000);
    }
} //FUNÇÃO DE RECEBER ATAQUE

void localdaseta2(int realPosition, int posicaoDaTecla2)
{
    if (realPosition == posicaoDaTecla2) {
        printf("\t\t\t => ");
    }
    else {
        printf("\t\t\t   ");
    }
}

batalha(struct personagem *player, struct enemy *inimigo){

    int posicaodatecla2 = 1, KeyDown2 = 0;

    #define MAX 4
    #define MIN 1

    for (inimigo->pv >= 0 ; player->pvjogador >= 0;)
    {
        posicaodatecla2 = 1; KeyDown2 = 0;
    if (inimigo->pv >= 0 && player->pvjogador >= 0)
    {
    while (KeyDown2 != 13)
      {
        system("cls");
        
            printf("\n\n");
            printf("                         ==================\n");
            printf("                         Voce tem %d pv\n", player->pvjogador);
            printf("                         O inimigo tem %d pv\n", inimigo->pv);
            printf("                         ==================\n");
            printf("\t\t\t-[MENU DE BATALHA]-\n");
            localdaseta2(1, posicaodatecla2); printf("* - Ataque corporal\n"); 
            localdaseta2(2, posicaodatecla2); printf("* - Ataque magico\n");
            localdaseta2(3, posicaodatecla2); printf("* - Beber pocao de vida\n");
            localdaseta2(4, posicaodatecla2); printf("-AINDAPORVIR-\n");
            printf("\t\t\t------------------\n");

            ASCIIinimigo();

            KeyDown2 = getch(); //RECEBER ENTER
            
            if (KeyDown2 == 80 && posicaodatecla2 != MAX) {
            posicaodatecla2++;
            } else if (KeyDown2 == 72 && posicaodatecla2 != MIN) {
            posicaodatecla2--;
            } else {
            posicaodatecla2 = posicaodatecla2;
            }
      }

    switch (posicaodatecla2)
    {
    case 1:
        printf("                   O                              O\n");
        printf("              {o)xxx|===========-  *  -===========|xxx(o}\n");
        printf("                   O                              O\n\n\n");
        atacar(player, inimigo);
        verificacaodemorte(player, inimigo);

        break;
    case 2:

        ataquemagico(player, inimigo);
        verificacaodemorte(player, inimigo);
    break;
    case 3:
        regeneracao(player);
        break;
    default:
        printf("Opcao Invalida\n");
        break;
    }
    if (inimigo->pv>=0)
    {
        receberataque(player, inimigo); //RECEBER ATAQUE DO INIMIGO
        verificacaodemorte(player, inimigo);
    }
    }
    else
    {
        player->nivel++;
        salvarjogo(player, inimigo);
        system("cls");
        return nivel(player, inimigo);
    }
    }
}

void Dialogo(char text[], int seconds)
{   
    int x; double y;
    // DELAY EM SEGUNDOS
    sleep(seconds);
    
        // PRINTAR O TEXTO DE FORMA LENTA
        for(x=0; text[x]!=NULL; x++)
        {
        printf("%c",text[x]);
        for(y=0; y<=8888888; y++)
        {
        }
        }
    
    // LIMPAR A TELA APOS O TEXTO UTILIZANDO O ENTER
}

novojogo(struct personagem *player, struct enemy *inimigo)
{
    nivel(player, inimigo);
}

void clear()
{
    printf("\n\n[Pressione Enter para continuar]");
    char enter = 0;
    while (enter != '\r' && enter != '\n') // VERIFICAÇÃO DO ENTER
    {
        enter = getchar();
    }
    {
        enter = getchar();
    }
    system("cls");
}

void DialogocomClear(char text[], int seconds)
{   
    system("cls");
    int x; double y;
    // DELAY EM MILISSEGUNDOS
    sleep(seconds);
    
        // PRINTAR O TEXTO DE FORMA LENTA
        for(x=0; text[x]!=NULL; x++)
        {
        printf("%c",text[x]);
        for(y=0; y<=8888888; y++)
        {
        }
        }
    
    // LIMPAR A TELA APOS O TEXTO UTILIZANDO O ENTER
    printf("\n\n[Pressione Enter para continuar]");
    char enter = 0;
    while (enter != '\r' && enter != '\n') // VERIFICAÇÃO DO ENTER
    {
        enter = getchar();
    }
    {
        enter = getchar();
    }
    
    // LIMPAR A TELA APOS O TEXTO UTILIZANDO O ENTER
    system("cls");
}

void localdaseta(int realPosition, int posicaoDaTecla)
{
    if (realPosition == posicaoDaTecla) {
        printf("\t\t\t=> ");
    }
    else {
        printf("\t\t\t   ");
    }
}

void menu(struct personagem *player, struct enemy *inimigo)
{
    system("cls");
      int posicaodatecla = 1, KeyDown = 0;
    
      #define MAX 4
      #define MIN 1
    
      while (KeyDown != 13)
      {

        system("cls");

            // MOSTRAR O MENU
            printf("\t\t\t------[MENU]------     ^     ________\n");
            localdaseta(1, posicaodatecla); printf("NOVO JOGO          | |   |        |\n"); 
            localdaseta(2, posicaodatecla); printf("CARREGAR JOGO      | |   |        | \n");
            localdaseta(3, posicaodatecla); printf("CRÉDITOS          | |   |        |\n");
            localdaseta(4, posicaodatecla); printf("SAIR               | |    \\      /\n");
            localdaseta(5, posicaodatecla); printf("                 `--8--'   \\_  _/\n");
            printf("\t\t\t------------------     0        vv\n");

            KeyDown = getch(); //RECEBER ENTER
            
            if (KeyDown == 80 && posicaodatecla != MAX) {
            posicaodatecla++;
            } else if (KeyDown == 72 && posicaodatecla != MIN) {
            posicaodatecla--;
            } else {
            posicaodatecla = posicaodatecla;
            }
    }
    
    switch (posicaodatecla) {
        case 1:
            system("cls");
            DialogocomClear("Um novo jogo esta sendo criado!\n", 0);

            novojogo(player, inimigo);
            break;
        case 2:
            system("cls");
            DialogocomClear("Carregando jogo...", 0);
            carregarjogo(player, inimigo);
            nivel(player, inimigo);
            break;
        case 3:
            system("cls");
            DialogocomClear("Obrigado por jogar!", 0);
            DialogocomClear("Historia por: Julio Cesar \nVisual: Sergio Mota \nProgramacao: Junior Veras", 0);
            menu(player, inimigo);
            break;
        case 4:
            system("cls");
            break;
    }
}

nivel(struct personagem *player, struct enemy *enemy) {
switch (player->nivel)
{
case 1:
    resetvida(player);
    Dialogo("Provavelmente e a primeira vez que voce coloca seus pes nessas terras distantes.\n\n", 0);
    Dialogo("Como podemos lhe chamar?\n", 0);
    scanf("%s", player->name);
    
    system("cls");
    Dialogo("Bem-vindo", 0); printf(" %s\n", player->name);
    delay(2000);
    Dialogo("Antes e comecar irei lhe dar alguns itens\nVoce recebeu uma espada.\nVoce recebeu 20 pontos de vida e 9 pontos de ataque com espada e 5 pontos de defesa.", 0);
    delay(2000);
    clear();

    player->nivel = 2;
    salvarjogo(player, enemy);
    resetenemy(enemy);
    system("cls");
    nivel(player, enemy);
    break;

case 2:
    resetvida(player);
    
    player->nivel = 3;
    salvarjogo(player, enemy);
    resetenemy(enemy);
    system("cls");
    nivel(player, enemy);
    break;

    case 3:
    resetvida(player);



    system("pause");
    player->nivel = 4;
    salvarjogo(player, enemy);
    resetenemy(enemy);
    system("cls");
    nivel(player, enemy);
    break;

    case 4:
    resetvida(player);

    player->nivel = 5;
    salvarjogo(player, enemy);
    resetenemy(enemy);
    system("cls");
    nivel(player, enemy);
    break;

    case 5:

    resetvida(&player);
    resetenemy(&enemy);

    // batalha(player, enemy);

    player->nivel = 6;
    resetvida(&player);
    resetenemy(enemy);
    salvarjogo(player, enemy);
    nivel(player, enemy);
    break;

    case 6:
    printf("### CONTINUACAO ###\n\n");
    
    system("pause");
    break;
}
}

int main()
{   
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
    setlocale(LC_ALL, "Portuguese");
    srand(time(NULL));
    menu(&player, &inimigo);

  return 0;
}