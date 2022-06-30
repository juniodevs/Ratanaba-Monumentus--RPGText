#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

struct personagem {
    char name[18];
    int pv;
    int ataque;
    int defesa;
    int nivel;
    int espada;
    int gold;

}player;

struct enemy {
    char name[18];
    int pv;
    int ataque;
    int defesa;

}inimigo;

loja(struct personagem *player){
    printf("#########################");
    printf("#Seja bem vindo a loja!#\n");
    printf("#Voce tem %d gold#\n", player->gold);
    printf("#Opcoes\n");
    printf("#1 - Aprimorar espada - 10c - o Aprimoramento aumenta sua espada em 1 de dano\n");
}

atacar(struct personagem *player, struct enemy *enemy) {
    int dano;
    dano = (player->espada + player->ataque) - enemy->defesa;
    enemy->pv = enemy->pv - dano;
    printf("\n%s atacou %s e causou %d de dano\n", player->name, enemy->name, dano);
    verificacaodemorte(player, enemy);
}

receberataque(struct personagem *player, struct enemy *enemy) {
    int dano;
    dano = enemy->ataque - player->defesa;
    player->pv = player->pv - dano;
    printf("\n%s recebeu um ataque de %s e causou %d de dano\n", player->name, enemy->name, dano);
    verificacaodemorte(player, enemy);
}

verificacaodemorte(struct personagem *player, struct enemy *enemy) {
    if (player->pv <= 0) {
        printf("\n%s morreu\n", player->name);
        exit(0);
    }
    if (enemy->pv <= 0) {
        printf("\n%s morreu\n", enemy->name);
        exit(0);
    }
}

salvarjogo(struct personagem *player, struct enemy *enemy) {
    FILE *save;
    save = fopen("salvamento.txt", "w");
    fprintf(save, "%s\n", player->name);
    fprintf(save, "%d\n", player->pv);
    fprintf(save, "%d\n", player->nivel);
    fprintf(save, "%d\n", player->ataque);
    fprintf(save, "%d\n", player->gold);    
    fprintf(save, "%d\n", player->defesa);
    fprintf(save, "%d\n", player->espada);
    fprintf(save, "%s\n", enemy->name);
    fprintf(save, "%d\n", enemy->pv);
    fprintf(save, "%d\n", enemy->ataque);
    fprintf(save, "%d\n", enemy->defesa);
    fclose(save);
}

carregarjogo(struct personagem *player, struct enemy *enemy) {
    FILE *save;
    save = fopen("salvamento.txt", "r");
    fscanf(save, "%s\n", player->name);
    fscanf(save, "%d\n", &player->pv);
    fscanf(save, "%d\n", &player->nivel);
    fscanf(save, "%d\n", &player->ataque);
    fscanf(save, "%d\n", &player->defesa);
    fscanf(save, "%d\n", &player->gold);
    fscanf(save, "%d\n", &player->espada);
    fscanf(save, "%s\n", enemy->name);
    fscanf(save, "%d\n", &enemy->pv);
    fscanf(save, "%d\n", &enemy->ataque);
    fscanf(save, "%d\n", &enemy->defesa);
    fclose(save);
}

resetenemy(struct enemy *enemy) {
    strcpy(enemy->name, "Guerreiro Inimigo");
    inimigo.pv = 4 + rand()%10;
    inimigo.ataque = 2;
    inimigo.defesa = 2;
}

delay(int ms) {
    clock_t start = clock();
    while (clock() < start + ms);
}


nivel(struct personagem *player, struct enemy *enemy) {
switch (player->nivel)
{
case 1:
    printf("Provavelmente e a primeira vez que voce coloca seus pes nessas terras distantes.\n\n");
    delay(2000);
    printf("Como podemos lhe chamar?\n\n");
    scanf("%s", player->name);
    delay(2000);
    system("cls");
    printf("Bem-vindo %s\n\n", player->name);
    delay(2000);
    printf("Antes e começar irei lhe dar alguns itens\n\n");
    delay(2000);
    printf("Voce recebeu uma espada.\n\n");
    delay(2000);
    printf("Voce recebeu 20 pontos de vida e 9 pontos de ataque com espada e 5 pontos de defesa.\n\n");
    delay(2000);
    system("pause");

    player->nivel = 2;
    salvarjogo(player, enemy);
    resetenemy(enemy);
    system("cls");
    nivel(player, enemy);
    break;

case 2:
    delay(2000);
    printf("Seu nome e %s\n\n", player->name);
    delay(2000);
    printf("Voce mora na Vila de Highlander, um guerreiro bastante valente,");
    printf("e por este motivo o Chefe-rei chama voce e alguns outros guerreiros");
    printf("para tratar sobre alguns assuntos\n\n");
    delay(2000);
    system("pause");
    system("cls");
    delay(2000);
    printf("Guerreiro: %s\n\n", player->name);
    delay(2000);
    printf("Voce ouve seu nome ser chamado de longe\n\n");
    delay(2000);
    printf("Ao olhar para tras voce ver Alex, um velho amigo de infancia\n\n");
    delay(2000);
    printf("%s: Alex, a quanto tempo meu velho e bom amigo\n\n", player->name);
    delay(2000);
    printf("Alex: E, faz bastante tempo que nao nos vemos\n\n");
    delay(2000);
    printf("Alex: O Rei-Chafe tambem o chamou aqui hoje?\n\n");
    delay(2000);
    printf("%s: Sim, passei a noite tentando enteder do que se tratava esses segredos\n\n", player->name);
    delay(2000);
    system("pause");

    player->nivel = 3;
    salvarjogo(player, enemy);
    resetenemy(enemy);
    system("cls");
    nivel(player, enemy);
    break;
}
}

int main()
{
    srand(time(NULL));
    strcpy(inimigo.name, "Guerreiro Inimigo");
    inimigo.pv = 10;
    inimigo.ataque = 2;
    inimigo.defesa = 2;
    player.pv = 20;
    player.ataque = 8;
    player.defesa = 5;
    player.nivel = 1;
    player.espada = 1;

    carregarjogo(&player, &inimigo);
    nivel(&player, &inimigo);
    
  return 0;
}