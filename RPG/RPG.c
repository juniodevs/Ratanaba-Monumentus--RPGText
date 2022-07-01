#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

struct personagem {
    char name[18];
    int pvjogador;
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

// loja(struct personagem *player){
//     printf("#########################");
//     printf("Seja bem vindo a loja!#\n");
//     printf("Voce tem %d gold#\n", player->gold);
//     printf("Opcoes\n");
//     printf("#1 - Aprimorar espada - 10c - o Aprimoramento aumenta sua espada em 1 de dano\n");
// }

ataquemagico(struct personagem *player, struct enemy *enemy) {
    int dano = 0;
    player->ataquemagico = 10 + (rand()%10);
    dano = (player->ataquemagico) - enemy->defesa;
    enemy->pv = enemy->pv - dano;
    printf("\n%s atacou %s e causou %d de dano\n", player->name, enemy->name, dano);
    player->ataquemagico--;
}

receberataque(struct personagem *player, struct enemy *enemy) {
    int dano = 0;
    dano = enemy->ataque - player->defesa;
    if (dano < 0) {
        dano = 0;
        printf("\n%s nao conseguiu atacar %s\n", enemy->name, player->name);
    }
    else
    {
        player->pvjogador = player->pvjogador - dano;
        delay(1000);
        printf("\n%s recebeu um ataque de %s e causou %d de dano\n", player->name, enemy->name, dano);
        delay(1000);
    }

}

verificacaodemorte(struct personagem *player, struct enemy *enemy) {

    int coinsareceber = 0;

    if (player->pvjogador <= 0) {
        printf("\n%s morreu\n", player->name);
        printf("#########################\n");
        printf("#Voce perdeu o jogo!#\n");
        delay(1000);
        printf("\n#########################");
        delay(1000);
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
        coinsareceber = (rand()%10) + 10;
        delay(1000);
        printf("#Voce recebeu %d de coins#\n", coinsareceber);
        player->gold = player->gold + coinsareceber;
        system("pause");
        system("cls");
    }
}

regeneracao(struct personagem *player){

    if (player->pocao <= 0)
    {
        printf("Voce nao tem pocao de vida\n");
    }
    else
    {
        player->pvjogador = 20;
        printf("#########################\n");
        printf("#Voce regenerou seu pv#\n");
        printf("#########################");
        player->pocao--;
    }
}

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
}

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
} // LOAD

resetenemy(struct enemy *enemy) {
    enemy->pv = 7 + rand()%10;
    enemy->ataque = 3 + rand()%5;
    enemy->defesa = 2 + rand()%2;
} // reseta a vida e ataque do inimigo

resetvida(struct personagem *player) {
    player->pvjogador = 20;
    player->ataque = 8;
    player->espada = 1;
} // reseta a vida do jogador

delay(int ms) {
    clock_t start = clock();
    while (clock() < start + ms);
} // timer para ações

atacar(struct personagem *player, struct enemy *enemy) {
    int dano = 0;
    player->espada = 1 + (rand()%2);
    player->ataque = 5+(rand()%10);
    dano = (player->espada + player->ataque) - enemy->defesa;
    enemy->pv = enemy->pv - dano;
    printf("\n%s atacou %s e causou %d de dano\n", player->name, enemy->name, dano);
    delay(1000);
} //função de ataque ao inimigo

batalha(struct personagem *player, struct enemy *inimigo){

    int escolha = 0;

    for (inimigo->pv >= 0 ; player->pvjogador >= 0;)
    {
    escolha = 0;
    if (inimigo->pv >= 0 && player->pvjogador >= 0)
    {
    printf("#########################\n");
    printf("# Voce tem %d pv #\n", player->pvjogador);
    printf("# O inimigo tem %d pv #\n", inimigo->pv);
    printf("#########################\n");
    printf("# Opcoes\n");
    printf("# 1 - Ataque corporal #\n");
    printf("# 2 - Ataque magico #\n");
    printf("# 3 - Beber pocao de vida #\n");
    printf("#########################\n\n");
    scanf("%d", &escolha);
    switch (escolha)
    {
    case 1:
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
        receberataque(player, inimigo); //recebe o ataque do inimigo
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

menu(struct personagem *player, struct enemy *inimigo) {
    int escolha = 0;
    printf("#########################\n");
    printf("# 1 - Iniciar jogo      #\n");
    printf("# 2 - Carregar jogo     #\n");
    printf("# 3 - Sair              #\n");
    printf("#########################\n\n");
    scanf("%d", &escolha);
    switch (escolha)
    {
    case 1:
        resetvida(player);
        resetenemy(inimigo);
        nivel(player, inimigo);
        break;
    case 2:
        carregarjogo(player, inimigo);
        nivel(player, inimigo);
        break;
    case 3:
        printf("#########################\n");
        printf("#  Obrigado por jogar   #\n");
        printf("#########################\n");
        system("pause");
        system("cls");
        break;
    default:
        printf("Opcao Invalida\n");
        delay(2000);
        system("cls");
        menu(player, inimigo);
    }
}

nivel(struct personagem *player, struct enemy *enemy) {
switch (player->nivel)
{
case 1:
    resetvida(player);
    printf("Provavelmente e a primeira vez que voce coloca seus pes nessas terras distantes.\n\n");
    delay(1000);
    printf("Como podemos lhe chamar?\n\n");
    scanf("%s", player->name);
    delay(1000);
    system("cls");
    printf("Bem-vindo %s\n\n", player->name);
    delay(1000);
    printf("Antes e comecar irei lhe dar alguns itens\n\n");
    delay(1000);
    printf("Voce recebeu uma espada.\n\n");
    delay(1000);
    printf("Voce recebeu 20 pontos de vida e 9 pontos de ataque com espada e 5 pontos de defesa.\n\n");
    delay(1000);
    system("pause");

    player->nivel = 2;
    salvarjogo(player, enemy);
    resetenemy(enemy);
    system("cls");
    nivel(player, enemy);
    break;

case 2:
    resetvida(player);
    delay(1000);
    printf("Seu nome e %s\n\n", player->name);
    delay(1000);
    printf("Voce mora na Vila de Ratanaba, um guerreiro bastante valente,\n");
    printf("e por este motivo o Chefe-rei chama voce e alguns outros guerreiros\n");
    printf("para tratar sobre alguns assuntos secretos\n\n");
    delay(1000);
    system("pause");
    system("cls");
    delay(1000);
    printf("Voz desconecida: %s\n\n", player->name);
    delay(1000);
    printf("Narrador: Voce ouve seu nome ser chamado de longe\n");
    delay(1000);
    printf("Ao olhar para tras voce ver Alex, um velho amigo de infancia\n\n");
    delay(1000);
    printf("%s: Alex, a quanto tempo meu velho e bom amigo\n\n", player->name);
    delay(1000);
    printf("Alex: Eh, faz bastante tempo que nao nos vemos\n\n");
    delay(1000);
    printf("Alex: O Rei-Chafe tambem o chamou aqui hoje?\n\n");
    delay(1000);
    printf("%s: Sim, passei a noite tentando enteder do que se tratava esses segredos\n\n", player->name);
    delay(1000);
    system("pause");
    system("cls");
    printf("Guerreiro Maior: Ei voces, o chefe esta aguardando voces\n\n");
    delay(1000);
    printf("Narrador: Os guerreiros seguiram ate o altar do chefe\n\n");
    delay(1000);
    printf("Guerreiro Maior: %s, Boa Sorte!\n\n", player->name);
    delay(1000);
    system("pause");
    system("cls");

    player->nivel = 3;
    salvarjogo(player, enemy);
    resetenemy(enemy);
    system("cls");
    nivel(player, enemy);
    break;

    case 3:
    delay(1000);
    printf("Chefe-Rei: GUERREIROS, eu chamei hoje voces aqui, os mais fortes e valentes dessa vila\n");
    printf("para fazermos uma grande descoberta, encontramos mapas perdidos de nossos acenstrais\n\n");
    delay(5000);
    printf("Chefe-Rei: Voces iram partir esta noite, e aquele que conseguir entronctrar o tesouro\n");
    printf("sera muito bem recompensado\n\n");
    delay(1000);
    printf("Guerreiro Azul: Ja que e apenas uma exploracao, porque vossa exelencia chamou estes tantos de guerreiros\n");
    printf("Eu faria isto sozinho sem nenhuma preocupacao\n\n");
    delay(5000);
    printf("Chefe-Rei: Silencio garoto, nao e algo que voce possa fazer sozinho\n");
    printf("infelizmente nos nao somos os unicos que sabemos deste tesouro\n");
    printf("nossos inimigos tambem estao a caminho, entao peco-lhes que tomem bastante cuidado\n\n");
    delay(5000);
    system("pause");
    system("cls");
    printf("Guerreiro Vermelho: Okay meu Chefe, como sera separado as equipes?\n\n");
    delay(1000);
    printf("Chefe-Rei: voces serao separados em 3 grupos\n");
    delay(1000);
    printf("Grupo 1: Guerreiro Azul e Vermelho\n");
    delay(1000);
    printf("Grupo 2: Guerreiro Verde e Amarelo\n");
    delay(1000);
    printf("Grupo 3: Alex e %s\n\n", player->name);
    delay(1000);
    system("pause");
    player->nivel = 4;
    salvarjogo(player, enemy);
    resetenemy(enemy);
    system("cls");
    nivel(player, enemy);
    break;

    case 4:

    printf("### NAQUELA NOITE ###\n\n");
    delay(1000);
    printf("Alex: voce tem ideia do que estamos preste a presenciar?\n", player->name);
    printf("eu ouvi alguns boatos sobre uma maldicao neste tesouro.\n\n");
    delay(5000);
    int alternativa;
    printf("Escolha uma das alternativas:\n\n");
    printf("1 - Maldicao? isso nao existe, deve ser apenas boatos\n");
    printf("2 - Eu tambem andei pensando muito sobre isso, mas nao podemos fazer nada\n");
    printf("3 - Nos vamos conseguir, afinal nos somos os melhores de ratanaba\n");
    scanf("%d", &alternativa);
    if (alternativa == 1)
    {
        printf("%s: Maldicao? isso nao existe, deve ser apenas boatos\n\n", player->name);
        delay(1000);
        printf("Alex: Acho que voce nao deveria subestimar esse tipo de coisa\n\n");
    }
    else if (alternativa == 2)
    {
        printf("%s: Eu tambem andei pensando muito sobre isso, mas nao podemos fazer nada\n\n", player->name);
        delay(1000);
        printf("Alex: Voce acha que ainda da tempo de desistir?\n\n");
        delay(1000);
        printf("%s: Se fizermos isso, o chefe iria nos queimar em praca publica\n\n", player->name);
        delay(1000);
        printf("Alex: Voce tem razao\n\n");
    }
    else if (alternativa == 3)
    {
        printf("%s: Nos vamos conseguir, afinal nos somos os melhores de ratanaba\n\n", player->name);
        delay(1000);
        printf("Alex: Verdade, devem ser apenas boatos\n\n");
    }
    else
    {
        printf("%s: Nos vamos conseguir, afinal nos somos os melhores de ratanaba\n\n", player->name);
        delay(1000);
        printf("Alex: Verdade, devem ser apenas boatos\n\n");
    }
    delay(5000);
    printf("\nNarrador: Os dois guerreiros chegaram na carroca a qual eles iriam ate o monumento encontrado\n\n");
    delay(5000);

    system("pause");
    system("cls");

    player->nivel = 5;
    salvarjogo(player, enemy);
    resetenemy(enemy);
    system("cls");
    nivel(player, enemy);
    break;

    case 5:

    resetvida(&player);
    resetenemy(&enemy);
    printf("### NAQUELA MADRUGADA ###\n\n");
    delay(1000);
    printf("Narrador: A carroca estava em total silencio, nenhum homem naquele lugar\n");
    printf("era capaz de falar uma palavra se quer\n");
    delay(5000);
    system("pause");
    system("cls");
    printf("### UM POUCO MAIS TARDE ###");
    delay(1000);
    printf("\nNarrador: A carroca chegou ao monumento, parecia ser uma piramide\n");
    printf("no primeiro momento, todos ficaram encucados com aquilo, pois nunca tinham\n");
    printf("visto algo de tamanha magnitude\n\n");
    delay(2000);
    printf("Desconhecido: EEEEEEI!, ALI ESTAO ELES!\n\n");
    delay(1000);
    printf("Narrador: Todos olharam para tras, parecia ser um guerreiro, mas nao de sua mesma vila\n");
    delay(1000);
    printf("O Guerreiro correu ate os grupos, ele parecia estar bastante hostil\n\n");
    delay(2000);
    printf("%s estava no alvo do Inimigo\n\n", player->name);

    system("pause");
    system("cls");

    resetvida(&player);
    resetenemy(enemy);

    batalha(player, enemy);

    system("pause");
    system("cls");
    player->nivel = 6;
    resetvida(&player);
    resetenemy(enemy);
    salvarjogo(player, enemy);
    nivel(player, enemy);
    break;

    case 6:
    printf("### CONTINUACAO ###\n\n");
    delay(1000);
    system("pause");
    break;
}
}

int main()
{
    srand(time(NULL));
    strcpy(inimigo.name, "Inimigo");
    inimigo.pv = 10;
    inimigo.ataque = 2;
    inimigo.defesa = 2;
    player.pvjogador = 20;
    player.ataquemagico = 3;
    player.defesa = 5;
    player.nivel = 1;
    player.pocao = 1;

    menu(&player, &inimigo);

  return 0;
}