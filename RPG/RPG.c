#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include <locale.h>
#include "asciiarte.h"

struct personagem {
    char name[18];
    int amizade;
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
    player->amizade = 0;
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
            localdaseta2(1, posicaodatecla2); printf(" * - Ataque corporal\n"); 
            localdaseta2(2, posicaodatecla2); printf(" * - Ataque magico\n");
            localdaseta2(3, posicaodatecla2); printf(" * - Beber pocao de vida\n");
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
        for(y=0; y<=4; y++)
        {
        }
        }
    
    // LIMPAR A TELA APOS O TEXTO UTILIZANDO O ENTER
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

void debugmode(struct personagem *player, struct enemy *inimigo)
{
    system("cls");
      int posicaodatecla4 = 1, KeyDown4 = 0;
    
      #define MAX 4
      #define MIN 1
    
      while (KeyDown4 != 13)
      {
        system("cls");

            // MOSTRAR O MENU
            printf("\t\t\t-----[DEBUG]-----\n");
            localdaseta(1, posicaodatecla4); printf("TESTAR BATALHA\n"); 
            localdaseta(2, posicaodatecla4); printf("TESTAR LOJA\n");
            localdaseta(3, posicaodatecla4); printf("RECEBER 100 COINS\n");
            localdaseta(4, posicaodatecla4); printf("SAIR\n");
            printf("\t\t\t------------------\n");

            KeyDown4 = getch(); //RECEBER ENTER
            
            if (KeyDown4 == 80 && posicaodatecla4 != MAX) {
            posicaodatecla4++;
            } else if (KeyDown4 == 72 && posicaodatecla4 != MIN) {
            posicaodatecla4--;
            } else {
            posicaodatecla4 = posicaodatecla4;
            }
    }
    
    switch (posicaodatecla4) {
        case 1:
            system("cls");
            resetenemy(inimigo);
            resetvida(player);
            batalha(player, inimigo);
            break;
        case 2:
            system("cls");
            menudeloja(player);
            break;
        case 3:
            system("cls");
            player->gold += 100;
            debugmode(player, inimigo);
            break;
        case 4:
            system("cls");
            break;
    }
}

void menu(struct personagem *player, struct enemy *inimigo)
{
    system("cls");
      int posicaodatecla = 1, KeyDown = 0;
    
      #define MAX 5
      #define MIN 1
    
      while (KeyDown != 13)
      {
        system("cls");

            // MOSTRAR O MENU
            printf("\t\t\t------[MENU]------     ^     ________\n");
            localdaseta(1, posicaodatecla); printf("NOVO JOGO          | |   |        |\n"); 
            localdaseta(2, posicaodatecla); printf("CARREGAR JOGO      | |   |        | \n");
            localdaseta(3, posicaodatecla); printf("CRÉDITOS           | |   |        |\n");
            localdaseta(4, posicaodatecla); printf("SAIR               | |    \\      /\n");
            localdaseta(5, posicaodatecla); printf("DEBUG            `--8--'   \\_  _/\n");
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
            resetvida(player);
            nivel(player, inimigo);
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
            DialogocomClear("História por: Julio Cesar \nVisual: Sergio Mota \nProgramacao: Júnior Veras", 0);
            menu(player, inimigo);
            break;
        case 4:
            system("cls");
            break;
        case 5:
            system("cls");
            DialogocomClear("Debug Mode", 0);
            debugmode(player, inimigo);
            break;
    }
}


menudeloja(struct personagem *player){
    system("cls");
      int posicaodatecla = 1, KeyDown = 0;
    
      #define MAX 4
      #define MIN 1

      Dialogo("Seja Bem-vindo a loja!\n", 0);
      Dialogo("Aqui você pode aprimorar e comprar itens!\n", 0);
      system("pause");
      while (KeyDown != 13)
      { 
        system("cls");

            // MOSTRAR O MENU DE LOJA
            printf("\t\t\t      --------[LOJA]--------\n");
            localdaseta(1, posicaodatecla); printf("APRIMORAR SUA ESPADA\n"); 
            localdaseta(2, posicaodatecla); printf("COMPRAR CAPSULAS DE MAGIA\n");
            localdaseta(3, posicaodatecla); printf("COMPRAR POCAO DE VIDA\n");
            localdaseta(4, posicaodatecla); printf("SAIR\n");
            localdaseta(5, posicaodatecla); printf("VOCE POSSUI %d CAPSULAS E %d POCOES\n", player->ataquemagico, player->pocao);
            localdaseta(6, posicaodatecla); printf("VOCE TEM: %d COINS\n", player->gold);
            printf("\t\t\t      ----------------------\n");

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
            break;
        case 2:
            system("cls");
            break;
        case 3:
            system("cls");
            break;
        case 4:
            system("cls");
            break;
    }
} //LOJA DE APRIMORAMENTO DE ITENS




nivel(struct personagem *player, struct enemy *enemy) {
    int escolhas = 0;
switch (player->nivel)
{
case 1:
    resetvida(player);
    Dialogo("Provavelmente é a primeira vez que você coloca seus pés nessas terras distantes.\n\n", 0);
    Dialogo("Como podemos lhe chamar?\n", 0);
    scanf("%s", player->name);
    
    system("cls");
    Dialogo("Bem-vindo", 0); printf(" %s\n", player->name);
    clear();

    player->nivel = 2;
    salvarjogo(player, enemy);
    resetenemy(enemy);
    system("cls");
    nivel(player, enemy);
    break;

case 2:
    resetvida(player);

    Dialogo("Narrador: O Rei convoca a presença de ", 0); printf("%s", player->name); Dialogo(" e mais 5 guerreiros para a\nsala central do palacio dourado de Ratanabá. Os guerreiros de imediato se\napresentam ao rei e buscam entender para o que haviam sido chamados.\n", 0);
    delay(1000);
    cor(2);Dialogo("Gyro: ", 0); cor(3);Dialogo("Majestade, se me permite a pergunta, por que é necessária a presença de tantos\nguerreiros para tal missão?\n", 0);
    delay(500);
    cor(9);Dialogo("Brando: ", 0); cor(3);Dialogo("Também acho desnecessário tantas pessoas aqui, eu mesmo poderia resolver\ntudo isso sozinho.\n", 0);
    delay(500);
    cor(10);Dialogo("Rei: ",0);cor(3);Dialogo("Não sejam tolos! Não acham que eu não os teria convocado a essa sala se nao\ntivesse um motivo plausível?\n", 0);
    delay(500);
    cor(5);Dialogo("Speed: ", 0); cor(3);Dialogo("É como o Rei disse seus idiotas, vocês insistem nessa arrogância desnecessária!\n", 0);
    delay(500);
    cor(4);Dialogo("Sheldon: ",0); cor(3);Dialogo("Calado Speed! Todos sabem que você só tem toda essa cortesia ao Rei por ter\nsegundas intenções. \n", 0);
    cor(5);Dialogo("Speed: ", 0); cor(3);Dialogo("Como ousa seu insolente? Quer arranjar briga comigo?\n",0);
    delay(500);
    cor(1);Dialogo("Howard: ", 0); cor(3);Dialogo("Cara, esses idiotas só dão problema.\n\n", 0);
    delay(500);
    system("pause");
    system("cls");
    cor(10);Dialogo("Rei: ",0);cor(3);Dialogo("CALADOS!! Eu os convoquei hoje pois são os guerreiros mais competentes de todo o\nreino. Essa missão pode determinar o futuro de todos de nossa nação.\n",0);
    delay(500);
    cor(9);Dialogo("Brando: ", 0); cor(3);Dialogo("E quem é esse ", 0); printf("%s ", player->name); Dialogo("Nunca o vi e ele ainda não deu uma palavra\ndesde que chegamos ao salão do Rei. \n", 0);
    delay(500); cor(3);
    printf("%s\n\n", player->name);
    delay(500);
    Dialogo("1 - Não sou familiarizado com a presença de tantos outros guerreiros renomados, perdão.\n",0);
    Dialogo("2 - Vim somente para ouvir as instruções do Rei, vocês não representam nada para mim.\n", 0);
    Dialogo("3 - Me desculpe pela grosseria, sou um guerreiro novo nas terras do Rei\n",0);
    Dialogo("4 - Não é da sua conta, Seu insolente!\n", 0);
    Dialogo("Escolha: ", 0);
    scanf("%d", &escolhas);
    if (escolhas == 1 || escolhas==3)
    {
        cor(9);Dialogo("Brando: ", 0); cor(3);Dialogo("Me chamo Brando. Não o conheço mas acredito que você vá ser de grande ajuda nessa missão.\n",0);
        delay(500);
        player->amizade++;
    }
    else if (escolhas == 2 || escolhas == 4)
    {
        cor(9);Dialogo("Brando: ", 0); cor(3);Dialogo("Quanta arrogância! Não acredito que o Rei convocou um guerreiro tão petulante.\n",0);
        delay(500);
        player->amizade--;
    }
    else
    {
        cor(9);Dialogo("Brando: ", 0); cor(3);Dialogo("Me chamo Brando. Não o conheço mas acredito que você vá ser de grande ajuda nessa missão.\n",0);
        delay(500);
        player->amizade++;
    }

    Dialogo("Narrador: Gyro interrompe a conversa com uma pergunta a ", 0); printf("%s\n", player->name);
    delay(1000);
    cor(2);Dialogo("Gyro: ", 0); cor(3);Dialogo("Você ao menos será de ajuda nessa missão garoto?\n", 0);
    delay(500);cor(3);
    printf("%s\n\n", player->name);
    delay(500);
    Dialogo("1 - Darei o meu máximo para ajudar a todos.\n",0);
    Dialogo("2 - Tá brincando? Eu sou o guerreiro mais forte das terras de Ratanabá!\n", 0);
    Dialogo("3 - Se preciso for, darei a minha vida pelo reino!\n",0);
    Dialogo("4 - Farei o que tiver ao meu alcance para ajudá-los.\n", 0);
    Dialogo("Escolha: ", 0); scanf("%d", &escolhas);


    if (escolhas == 1 || escolhas == 3)
    {
        cor(2);Dialogo("Gyro: ", 0); cor(3);Dialogo("Vejo que é um guerreiro respeitoso, aprecio pessoas assim\n", 0);
        delay(500);
        player->amizade++;
    }
    else if (escolhas == 2)
    {
        cor(2);Dialogo("Gyro: ", 0); cor(3);Dialogo("Vejo que é um guerreiro respeitoso, aprecio pessoas assim\n", 0);
        delay(500);
        player->amizade--;
    }
    else
    {
        cor(2);Dialogo("Gyro: ", 0); cor(3);Dialogo("Vejo que é um guerreiro respeitoso, aprecio pessoas assim\n", 0);
        delay(500);
        player->amizade++;
    }
    delay(500);
    cor(1);Dialogo("Howard: ", 0); cor(3);Dialogo("Bom, se foi escolha do Rei que ele estivesse aqui, então pra mim tudo bem.\n", 0);
    delay(500);
    cor(10);Dialogo("Rei: ",0);cor(3);Dialogo("Poupem essas apresentações, não temos tanto tempo. Primeiramente gostaria de\ndividi-los em duplas para que essa tarefa seja mais fácil de ser concluída.\n",0);
    delay(500);
    cor(5);Dialogo("Speed: ", 0); cor(3);Dialogo("Deixe-me acompanhar o garoto majestade. Ele me chamou atenção, acredito\nque deve ser um ótimo guerreiro em batalha.\n",0);
    delay(500);
    cor(10);Dialogo("Rei: ",0);cor(3);Dialogo("O que acha dessa decisão\n",0); printf("%s?\n", player->name);
    delay(500);
    Dialogo("1 - Por mim tudo bem majestade, ele me parece um bom guerreiro.\n",0);
    Dialogo("2 - Se ele não me atrapalhar tudo bem.\n", 0);
    Dialogo("3 - Eu acho que ele vai ser de grande ajuda nessa missão!\n",0);
    Dialogo("4 - Acho que esse cara não é tão forte, mas tudo bem ele ir comigo.\n", 0);
    Dialogo("Escolha: ", 0); scanf("%d", &escolhas);

    if (escolhas == 1 || escolhas == 3)
    {
        cor(5);Dialogo("Speed: ", 0); cor(3);Dialogo("Que bom que está de acordo em seguir viagem comigo\n", 0);
        delay(500);
        player->amizade++;
    }
    else if (escolhas == 2 || escolhas == 4)
    {
        cor(5);Dialogo("Speed: ", 0); cor(3);Dialogo("Quanta prepotência garoto, vejo que será um tanto\ncomplicado trabalhar com você \n", 0);
        delay(500);
        player->amizade--;
    }
    else
    {
        cor(5);Dialogo("Speed: ", 0); cor(3);Dialogo("Que bom que está de acordo em seguir viagem comigo\n", 0);
        delay(500);
        player->amizade++;
    }
    delay(500);

    system("pause");
    system("cls");

    cor(10);Dialogo("Rei: ",0);cor(3);Dialogo("Então que fique decidido dessa forma.",0);
    cor(2);Dialogo("Gyro ", 0); cor(3); printf("e ");cor(9);Dialogo("Brando ", 0); cor(3); Dialogo("vocês irão juntos.\n Assim sobrando",0);
    cor(1);Dialogo("Howard ", 0); cor(3); printf("e ");cor(4);Dialogo("Sheldon ", 0);cor(3); Dialogo("como sendo a outra dupla\n",0);
    delay(500);
    cor(4);Dialogo("Sheldon ", 0); cor(3);Dialogo("Aceitamos de bom grado sua decisão, mas por qual motivo devemos sair nessa\nmissão majestade?\n", 0);
    delay(500);
    cor(2);Dialogo("Gyro ", 0); cor(3);Dialogo("Também gostaria de saber o motivo de tanta pressa nessa jornada.\n", 0);
    delay(500);
    cor(10);Dialogo("Rei: ",0);cor(3);Dialogo("Eu já iria chegar nesse assunto. Vejam, como todos sabem, nosso reino tem passado\npor momentos complicados referente às condições básicas de nossos cidadãos, como a\nfome e a falta de moradia. Além de estarmos constantemente entrando em guerra\ncom outros reinos. Com o passar dos anos, a falta de recursos acabou sendo o principal motivo\ndesses acontecimentos.\n",0);
    delay(2000);

    printf("\n%s\n\n", player->name);
    delay(500);
    Dialogo("1 - Nossa, quem poderia imaginar que essa lenda é real no final de contas\n",0);
    Dialogo("2 - Espero que esses caras não me atrapalhem nessa jornada\n", 0);
    Dialogo("3 - Estou ansioso para me aventurar nesse lugar desconhecido\n",0);
    Dialogo("4 - Contando que não entrem no meu caminho, ajudarei de bom grado o reino.\n", 0);
    Dialogo("Escolha: ", 0); scanf("%d", &escolhas);

    if (escolhas == 1 || escolhas == 3)
    {
        cor(10);Dialogo("Rei: ",0);cor(3);Dialogo("Admiro sua empolgação meu guerreiro!\n",0);
        delay(500);
        player->amizade++;
    }
    else if (escolhas == 2 || escolhas == 4)
    {
        cor(10);Dialogo("Rei: ",0);cor(3);Dialogo("Deixe seu orgulho de lado e foque no objetivo meu jovem\n",0);
        delay(500);
        player->amizade--;
    }
    else
    {
        cor(10);Dialogo("Rei: ",0);cor(3);Dialogo("Admiro sua empolgação meu guerreiro!\n",0);
        delay(500);
        player->amizade++;
    }

    cor(9);Dialogo("Brando ", 0); cor(3);Dialogo("Acho que uma aventura desse nível está à altura de um herói como eu!\n",0);
    delay(500);

    cor(1);Dialogo("Howard ", 0); cor(3);Dialogo("Farei o que tiver ao meu alcance meu Rei.\n",0);
    delay(500);

    cor(10);Dialogo("Rei: ",0);cor(3);Dialogo("Então estão todos de acordo em partir em viagem rumo ao leste?\n",0);

    cor(2);Dialogo("Gyro ", 0); cor(3);Dialogo("Sim meu Rei!\n",0);
    delay(20);
    cor(1);Dialogo("Howard ", 0); cor(3);Dialogo("Sim, meu Rei!\n",0);
    delay(20);
    cor(4);Dialogo("Sheldon ", 0); cor(3);Dialogo("Sim, meu Rei!\n",0);
    delay(20);
    cor(9);Dialogo("Brando ", 0); cor(3);Dialogo("Sim, meu Rei!\n",0);
    delay(20);
    cor(5);Dialogo("Speed ", 0); cor(3);Dialogo("Sim, meu Rei!\n",0);
    delay(20);
    printf("%s ", player->name);Dialogo("Sim, meu Rei!\n",0);
    delay(2000);

    cor(10);Dialogo("Rei: ",0);cor(3);Dialogo("Antes gostaria de orientá-los quanto aos inimigos que encontrarão nessas terras\n",0);
    Dialogo("inexploradas do leste. Acredita-se que lá habitam criaturas mágicas de outro mundo, e que\n\n",0);
    Dialogo("para derrotá-las será preciso imbuir suas armas com encantamentos rúnicos de um ferreiro\n",0);
    Dialogo("mágico. Por sorte, temos o ancião",0); cor(10); Dialogo(" Cultrapali, ", 0); cor(3); Dialogo("conhecedor das artes\n",0);
    Dialogo("mágicas da forja de armas. Então vocês deverão primeiramente se dirigir aos\n",0);
    Dialogo("seus aposentos às minhas ordens e adquirir um encantamento mágico em suas armas. Eu\n",0);
    Dialogo("pessoalmente deixei o senhor",0); cor(10); Dialogo(" Cultrapali, ", 0); cor(3); Dialogo("encarregado de passar as informações do mapa de\n",0);
    Dialogo("rotas até o palácio translúcido.\n",0);
    delay(7000);

    system("pause");
    delay(20);
    system("cls");

    Dialogo("Narrador: ", 0); cor(3); Dialogo("Então, os 6 guerreiros se dirigiram ao local onde vivia o ancião que o Rei\nhavia mencionado. Ao baterem na porta do casebre de madeira rústico do senhor,\npara a surpresa de todos, o velho foi bem hospitaleiro com os empolgados\naventureiros. Lá foram realizadas as melhorias nas armas de todos lá presentes.\n",0);cor(10); Dialogo(" Cultrapali ", 0); cor(3); Dialogo("foi direto ao prover todo o suporte para as rotas até o tão almejado\nobjetivo, porém, alertou a todos sobre os perigos que viriam a seguir.\n\n", 0);
    delay(500);
    cor(10); Dialogo("Cultrapali: ", 0); cor(3); Dialogo("Meus jovens, é preciso muita coragem para adentrar tanto aquelas terras do leste.\nDevo avisá-los que diversos perigos esperam vocês, e que precisam ir dispostos a\ndarem suas vidas em nome do reino.\n", 0);
    delay(500);
    cor(9); Dialogo("Brando ", 0); cor(3); Dialogo("Tá de brincadeira né cara? Será preciso só força bruta para pegarmos o tesouro\ne sairmos vivos de lá.\n",0);
    delay(500);
    cor(4); Dialogo("Sheldon ", 0); cor(3); Dialogo("Não seja tão arrogante",0);cor(9); Dialogo("Brando ", 0); cor(3); Dialogo("não vai ser com perigos comuns que\nvamos lidar nessa jornada.\n",0);
    delay(500);
    printf("\n%s\n", player->name);
    delay(500);
    Dialogo("1 - Verdade, devemos ir com cautela nessa viagem para preservar a segurança da\nnossa equipe.\n",0);
    Dialogo("2 - ",0); cor(9); Dialogo("Brando ",0); cor(3);Dialogo("tem razão, se formos com tudo iremos conseguir\n",0);  
    Dialogo("3 - Todo cuidado é pouco quando se está lidando com o desconhecido, nenhum de nós\npode colocar a vida em risco atoa.\n",0);
    Dialogo("4 - Só precisamos colocar nossas forças individuais nisso tudo para conseguir o objetivo.\n", 0);
    Dialogo("Escolha: ", 0); scanf("%d", &escolhas);
    if (escolhas == 1 || escolhas == 3)
    {
        cor(5);Dialogo("Speed ", 0); cor(3);Dialogo("Admiro sua preocupação com nossa equipe\n",0);
        delay(500);
        player->amizade++;
    }
    else if (escolhas == 2 || escolhas == 4)
    {
        cor(5);Dialogo("Speed ", 0); cor(3);Dialogo("Sua falta de preocupação pode nos colocar em risco nisso tudo\n",0);
        delay(500);
        player->amizade--;
    }
    else
    {
        cor(5);Dialogo("Speed ", 0); cor(3);Dialogo("Admiro sua preocupação com nossa equipe\n",0);
        delay(500);
        player->amizade++;
    }
    cor(1);Dialogo("Howard: ", 0); cor(3); Dialogo("Espero que tudo ocorra bem, e nada aconteça com nenhum de nós.\n",0);
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
    UINT CPAGE_UTF8 = 65001;
    UINT CPAGE_DEFAULT = GetConsoleOutputCP();
    SetConsoleOutputCP(CPAGE_UTF8);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
    srand(time(NULL));
    player.adagas = 5;
    player.ataquemagico = 3;
    player.ataque = 0;
    player.defesa = 0;
    player.gold = 0;
    player.nivel = 1;
    player.pocao = 0;
    player.pvjogador = 0;

    menu(&player, &inimigo);

    SetConsoleOutputCP(CPAGE_DEFAULT);
  return 0;
}