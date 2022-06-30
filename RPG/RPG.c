#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

struct personagem {

    char name[18];
    int pv;
    int ataque;
    int ataquemagico;
    int defesa;
    int nivel;
    int espada;
    int gold;
    int pocao;

}player;

struct enemy {
    char name[18];
    int pv;
    int ataque;
    int defesa;

}inimigo;

loja(struct personagem *player){
    printf("#########################");
    printf("Seja bem vindo a loja!#\n");
    printf("Voce tem %d gold#\n", player->gold);
    printf("Opcoes\n");
    printf("#1 - Aprimorar espada - 10c - o Aprimoramento aumenta sua espada em 1 de dano\n");
}

batalha(struct personagem *player, struct enemy *inimigo){

    int escolha = 0;

    for (inimigo->pv > 0; player->pv > 0;)
    {
    escolha = 0;
    printf("#########################");
    printf("#Voce tem %d pv\n", player->pv);
    printf("#O inimigo tem %d pv#\n", inimigo->pv);
    printf("#########################");
    printf("#Opcoes\n");
    printf("#1 - Ataque corporal#\n");
    printf("#2 - Ataque magico#\n");
    printf("#3 - Beber pocao de vida\n");
    printf("#########################");
    scanf("%d", &escolha);
    switch (escolha)
    {
    case 1:
        atacar(&player, &inimigo);
        verificacaodemorte(&player, &inimigo); 
        batalha(&player, &inimigo);
        break;
    case 2:

    ataquemagico(&player, &inimigo);
    verificacaodemorte(&player, &inimigo);
    batalha(&player, &inimigo);
    break;
    case 3:   
        regeneracao(&player);
        batalha(&player, &inimigo);
        break;
    default:
        printf("Opcao Invalida\n");
        batalha(&player, &inimigo);
        break;
    }

    receberataque(&player, &inimigo); //recebe o ataque do inimigo

    }
}

regeneracao(struct personagem *player){

    if (player->pocao < 0)
    {
        printf("Voce nao tem pocao de vida\n");
    }
    else
    {
        player->pv = 20;
        printf("#########################\n");
        printf("#Voce regenerou seu pv#\n");
        printf("#########################");
        player->pocao--;
    }
}

atacar(struct personagem *player, struct enemy *enemy) {
    int dano;
    player->ataque = rand() % 10 + 5;
    dano = (player->espada + player->ataque) - enemy->defesa;
    enemy->pv = enemy->pv - dano;
    printf("\n%s atacou %s e causou %d de dano\n", player->name, enemy->name, dano);
}

ataquemagico(struct personagem *player, struct enemy *enemy) {
    int dano;
    player->ataquemagico = rand() % 10 + 10;
    dano = (player->ataquemagico) - enemy->defesa;
    enemy->pv = enemy->pv - dano;
    printf("\n%s atacou %s e causou %d de dano\n", player->name, enemy->name, dano);
    player->ataquemagico--;
}

receberataque(struct personagem *player, struct enemy *enemy) {
    int dano;
    dano = enemy->ataque - player->defesa;
    player->pv = player->pv - dano;
    printf("\n%s recebeu um ataque de %s e causou %d de dano\n", player->name, enemy->name, dano);
}

verificacaodemorte(struct personagem *player, struct enemy *enemy) {

    int coinsareceber = 0;

    if (player->pv <= 0) {
        printf("\n%s morreu\n", player->name);
        printf("#########################\n");
        printf("#Voce perdeu o jogo!#\n");
        delay(2000);
        printf("\n#########################");
        delay(2000);
        printf("3");
        delay(1000);
        printf("2");
        delay(1000);
        printf("1");
        delay(1000);
        system("cls");
        carregarjogo(&player, &inimigo);
    }
    if (enemy->pv <= 0) {
        printf("\n%s morreu\n", enemy->name);
        printf("\n#########################");
        coinsareceber = rand() % 10 + 10;
        delay(2000);
        printf("#Voce recebeu %d de coins#\n", coinsareceber);
        player->gold = player->gold + coinsareceber;
        player->nivel++;
        system("pause");
        salvarjogo(&player, &inimigo);
        system("cls");
        nivel(&player, &inimigo);
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
    nivel(player, enemy);
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
    system("cls");
    printf("Guerreiro Maior: Ei voces, o chefe esta aguardando voces\n\n");
    delay(2000);
    printf("Os guerreiros seguiram ate o altar do chefe\n\n");
    delay(2000);
    printf("Guerreiro Maior: %s\n\n", player->name);
    delay(2000);
    printf("Guerreiro Maior: Boa Sorte!");
    delay(2000);
    system("pause");
    system("cls");

    player->nivel = 3;
    salvarjogo(player, enemy);
    resetenemy(enemy);
    system("cls");
    nivel(player, enemy);
    break;

    case 3:
    delay(2000);
    printf("Chefe-Rei: GUERREIROS, eu chamei hoje voces aqui, os mais fortes e valentes dessa vila");
    printf("")

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
    player.ataquemagico = 3;
    player.ataque = 8;
    player.defesa = 5;
    player.nivel = 1;
    player.espada = 1;
    player.pocao = 1;

    carregarjogo(&player, &inimigo);
    nivel(&player, &inimigo);

  return 0;
}
