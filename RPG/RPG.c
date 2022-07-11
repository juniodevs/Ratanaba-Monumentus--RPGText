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
    int asciienemy;
    int ataque;
    int defesa;
}inimigo; //PRE DEFINIÇÃO DE INIMIGO

struct finalboss {
    char name[18];
    int pv;
    int ataque;
    int defesa;
}boss; //PRE DEFINIÇÃO DE BOSS


verificacaodemorte(struct personagem *player, struct enemy *enemy) {
    int coinsareceber = 0;
    if (player->pvjogador <= 0) {
        printf("\n%s morreu\n", player->name);
        DialogocomClear("#########################\nVoce perdeu o jogo!\n#########################", 0);
        Dialogo("3 2 1", 1);
        carregarjogo(player, enemy);
        nivel(player, enemy);
        
        clear();
    }
    if (enemy->pv <= 0) {
        printf("\n%s", enemy->name); Dialogo(" Morreu!", 0);
        Dialogo("\n1", 1);
        Dialogo("\n2", 1);
        Dialogo("\n3", 1);
        coinsareceber = (rand()%10) + 10;
        
        Dialogo("\nVoce recebeu ", 0); printf("%d ",coinsareceber); Dialogo ("de coins\n", 0);

        player->gold = player->gold + coinsareceber;
        clear();
        return;
    }
}//FUNÇÃO DE VERIFICAÇÃO DE MORTE (PERSONAGEM E INIMIGO)


regeneracao(struct personagem *player){
    if (player->pvjogador >= 100)
    {
        Dialogo("\nSua vida está cheia\n", 0);
    }
    else
    {
            if (player->pocao <= 0)
    {
        Dialogo("Voce nao tem pocao de vida",0);
    }
    else
    {
        player->pvjogador = 100;
        pocao();
        printf("\n");
        player->pocao--;
    }
    }
    

} //FUNÇÃO DE REGENERAÇÃO DE PV (PERSONAGEM)

void ASCIIinimigo(struct enemy *enemy) //TEMPLATE PARA ASCII
{
    if(enemy->asciienemy == 1) //Guerreiro
    {   
cor(1); printf("                         ~O");cor(2);printf("               o~\n"); //LEMBRAR DO \N PARA QUEBRAR LINHAS
cor(1); printf("                       /~()-{---");cor(2);printf("     ---}-()~/\n");
cor(1); printf("                        /~)");cor(2);printf("               (~.\n");
cor(1); printf("                        ~ ~");cor(2);printf("               ~ ~\n");
cor(3);
    }
    else if(enemy->asciienemy == 2)// Zumbie
    {
cor(1); printf("                         ~O");cor(2);printf("               o~\n"); //LEMBRAR DO \N PARA QUEBRAR LINHAS
cor(1); printf("                       /~()-{---");cor(2);printf("        --|~\ \n");
cor(1); printf("                        /~)");cor(2);printf("               |~.\n");
cor(1); printf("                        ~ ~");cor(2);printf("               ~ ~\n");
cor(3);
    }
    else if(enemy->asciienemy == 3)// Bruxa
    {
cor(1); printf("                         ~O");cor(2);printf("               O>\n"); //LEMBRAR DO \N PARA QUEBRAR LINHAS
cor(1); printf("                       /~()-{---");cor(2);printf("         ,/)\ \n");
cor(1); printf("                        /~)");cor(2);printf("          -----<---<<<.\n");
cor(1); printf("                        ~ ~");cor(2);printf("               ``\n");
cor(3);
    }
    else if(enemy->asciienemy == 4)// Dragao
    {
cor(1); printf("                         ~O");cor(2);printf("  \t\t _a' /(     ,>\n"); //LEMBRAR DO \N PARA QUEBRAR LINHAS
cor(1); printf("                       /~()-{---");cor(2);printf("\t~~_}\ \(    (\n");
cor(1); printf("                        /~)");cor(2);printf("     \t\(,_(,)'\n");
cor(1); printf("                        ~ ~");cor(2);printf("       \t_>, _>\n");
cor(3);





    }
    else
    {
cor(1); printf("                         ~O");cor(2);printf("               o~\n"); //LEMBRAR DO \N PARA QUEBRAR LINHAS
cor(1); printf("                       /~()-{---");cor(2);printf("     ---}-()~/\n");
cor(1); printf("                        /~)");cor(2);printf("               (~.\n");
cor(1); printf("                        ~ ~");cor(2);printf("               ~ ~\n");
cor(3);
    }
} //FIM ASCII INIMIGO

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
    fprintf(save, "asciienemy: %d\n", enemy->asciienemy);
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
    fscanf(save,"asciiinimigo: %d\n", &enemy->asciienemy);
    fscanf(save, "vidainimigo: %d\n", &enemy->pv);
    fscanf(save, "ataqueinimigo: %d\n", &enemy->ataque);
    fscanf(save, "defesainimigo: %d\n", &enemy->defesa);
    fclose(save);
    nivel(player, enemy);
} //FUNÇÃO DE CARREGAR JOGO

resetenemy(struct enemy *enemy) {
    enemy->pv = 40 + rand()%30;
    enemy->ataque = 10 + rand()%20;
    enemy->defesa = 2 + rand()%20;
    strcpy(enemy->name, "Inimigo");
} //FUNÇÃO DE RESET DE INIMIGO VIDA/ATAQUE

resetvida(struct personagem *player) {
    player->pvjogador = 100;
    player->ataque = 20 + rand()%20;
} //FUNÇÃO DE RESET DE VIDA/ATAQUE DE PERSONAGEM DEPOIS DE BATALHAS

delay(int ms) {
    clock_t start = clock();
    while (clock() < start + ms);
} //FUNÇÃO DE ATRASO (BETA)

atacar(struct personagem *player, struct enemy *enemy) {
    int dano = 0;
    player->ataque = 20 + rand()%20;
    dano = (player->espada + player->ataque) - enemy->defesa;

    if(dano < 0)
    {
        dano = 0;
        printf("\n%s ", enemy->name); Dialogo(" defendeu", 0); printf(" %d ", dano); Dialogo("de dano", 0);
        delay(1000);
    }
    else
    {
        printf("\n%s ", player->name); Dialogo("atacou", 0); printf(" %s", enemy->name); Dialogo(" e causou", 0); printf(" %d ", dano); Dialogo("de dano", 0);
        enemy->pv = enemy->pv - dano;
        delay(1000);
    }

} //FUNÇÃO DE ATAQUE (PERSONAGEM X INIMIGO)

presaveforDEBUG()
{
    player.adagas = 999;
    player.ataquemagico = 999;
    player.ataque = 999;
    player.defesa = 0;
    player.gold = 999;
    player.nivel = 1;
    player.pocao = 999;
    player.pvjogador = 100;
    strcpy(player.name, "DEBUGGER");
}

jogaradaga(struct personagem *player, struct enemy *enemy) {
    int dano = 0;
    player->ataque = 20 + rand()%20;
    dano = (player->ataque) - enemy->defesa;
    if(dano <= 0)
    {
        dano = 0;
        printf("\n%s ", enemy->name); Dialogo(" defendeu a adaga", 0); printf(" %d ", dano); Dialogo("de dano", 0);
    }
    else
    {
        enemy->pv = enemy->pv - dano;
        printf("\n%s ", player->name); Dialogo("jogou adaga em ", 0); printf(" %s", enemy->name); Dialogo(" e causou", 0); printf(" %d ", dano); Dialogo("de dano", 0);   
    }

} //FUNÇÃO DE JOGAR ADAGA (PERSONAGEM X INIMIGO)

ataquemagico(struct personagem *player, struct enemy *enemy) {
    int dano = 0;
    player->ataque = 20 + rand()%20;
    dano = player->ataque - enemy->defesa;
    if(dano <= 0)
    {
        dano = 0;
        printf("\n%s ", player->name); Dialogo("não conseguiu atacar o ", 0); printf(" %s", enemy->name); Dialogo(" com sua magia", 0);
        delay(500);
    }
    else
    {
        enemy->pv = enemy->pv - dano;
        printf("\n%s", player->name); Dialogo("usou uma capsula de magia ", 0); printf(" %s", enemy->name); Dialogo(" e causou", 0); printf(" %d ", dano); Dialogo("de dano", 0);
        delay(500);
    }
    player->ataquemagico--;
} //ATAQUE MAGICO

receberataque(struct personagem *player, struct enemy *enemy) {
    int dano = 0;
    enemy->ataque = 10 + rand()%20;
    player->defesa = 10 + rand()%10;
    dano = enemy->ataque - player->defesa;
    if (dano <= 0)
    {
        dano = 0;
        printf("\n%s nao conseguiu atacar %s\n", enemy->name, player->name);
        delay(500);
    }
    else if (dano > 0)
    {
        player->pvjogador = player->pvjogador - dano;
        printf("\n%s recebeu um ataque de %s e causou %d de dano\n", player->name, enemy->name, dano);
        delay(1000);
    }
} //FUNÇÃO DE RECEBER ATAQUE

batalha(struct personagem *player, struct enemy *inimigo){

    int posicaodatecla2 = 1, KeyDown2 = 0; //VARIAVEIS DE CONTROLE DE TECLAS
    int contadordeturno = 0; //contador de turnos

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
            printf("\t\t\tTurno\t [%d]\n", contadordeturno);
            localdaseta(1, posicaodatecla2); printf("* - Ataque corporal\n"); 
            localdaseta(2, posicaodatecla2); printf("* - Ataque magico\n");
            localdaseta(3, posicaodatecla2); printf("* - Beber pocao de vida\n");
            localdaseta(4, posicaodatecla2); printf("* - Jogar Adaga\n");
            printf("\t\t\t------------------\n");

            ASCIIinimigo(inimigo);

            KeyDown2 = getch(); //RECEBER ENTER
            
            if (KeyDown2 == 80 && posicaodatecla2 != MAX) {
            posicaodatecla2++;
            } else if (KeyDown2 == 72 && posicaodatecla2 != MIN) {
            posicaodatecla2--;
            } else {
            posicaodatecla2 = posicaodatecla2;
            }
      }
    contadordeturno++;
    switch (posicaodatecla2)
    {
    case 1: //ATAQUE CORPORAL
        printf("                   O                              O\n");
        printf("              {o)xxx|===========-  *  -===========|xxx(o}\n");
        printf("                   O                              O\n\n\n");
        atacar(player, inimigo);
        verificacaodemorte(player, inimigo);

        break;
    case 2: //ATAQUE MAGICO

        ataquemagico(player, inimigo);
        verificacaodemorte(player, inimigo);
    break;
    case 3: //BEBER POCAO DE VIDA
        regeneracao(player);
        break;
    case 4: //JOGAR ADAGA
        jogaradaga(player, inimigo);
        verificacaodemorte(player, inimigo);
        break;
    default:
        printf("Opcao Invalida\n");
        break;
    }
    if (inimigo->pv > 0)
    {
        receberataque(player, inimigo); //RECEBER ATAQUE DO INIMIGO
        verificacaodemorte(player, inimigo);
    }
    }
    else
    {
        int contadordeturno = 0;
        system("cls");
        break;
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

void clear()
{
    printf("\n[Pressione Enter para continuar]");
    char enter = 0;
    while (enter != '\r' && enter != '\n') // VERIFICAÇÃO DO ENTER
    {
        enter = getchar();
    }
    {
        enter = getchar();
    }
    delay(500);
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
    presaveforDEBUG(player, inimigo);
    system("cls");
    presaveforDEBUG();
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
            inimigo->asciienemy = 3;
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
    
      #define MAX 5
      #define MIN 1

      Dialogo("Seja Bem-vindo a loja!\n", 0);
      Dialogo("Aqui você pode aprimorar e comprar itens!\n", 0);
      system("pause");
      while (KeyDown != 13)
      { 
        system("cls");

            // MOSTRAR O MENU DE LOJA
            printf("\t\t\t      --------[LOJA]--------\n");
            localdaseta(1, posicaodatecla); printf("80c - APRIMORAR SUA ESPADA\n"); 
            localdaseta(2, posicaodatecla); printf("10c - COMPRAR CAPSULAS DE MAGIA\n");
            localdaseta(3, posicaodatecla); printf("50c - COMPRAR POCAO DE VIDA\n");
            localdaseta(4, posicaodatecla); printf("20c - COMPRAR ADAGA\n");
            localdaseta(5, posicaodatecla); printf("SAIR\n");
            localdaseta(6, posicaodatecla); printf("VOCE POSSUI %d CAPSULAS, %d POCOES E %d ADAGAS\n", player->ataquemagico, player->pocao, player->adagas);
            localdaseta(7, posicaodatecla); printf("VOCE TEM: %d COINS\n", player->gold);
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
        case 1: //APRIMORAR ESPADA
            system("cls");

            if(player->gold >= 80) //PREÇO DO APRIMORAMENTO DA ESPADA
            {
            Dialogo("Aprimorando sua espada!\n", 0);
            int bonusdeespada = 2 + rand() % 2; //BONUS DA ESPADA
            player->espada + bonusdeespada;
            Dialogo("Sua espada ganhou", 0); printf(" %d ", bonusdeespada); Dialogo("ponto de bônus!\n", 0);
            delay(1000);
            player->gold -= 80; //CUSTO DO APRIMORAMENTO DA ESPADA
            }

            else
            {
            Dialogo("Você não tem coins suficientes para comprar este update!", 0);
            }
            menudeloja(player);
            break;
        case 2: //COMPRAR CAPSULAS DE MAGIA
            system("cls");
            if(player->gold >= 10) //PREÇO DA CAPSULA
            {
            Dialogo("Comprando capsulas de magia!\n", 0);
            DialogocomClear("Você comprou uma capsula de magia!\n", 0);
            player->ataquemagico += 1;
            player->gold -= 10;
            delay(1000);
            }

            else
            {
             Dialogo("Você não tem coins suficientes para comprar ecapsula de magia", 0);
            }
            menudeloja(player);
            break;
        case 3: //COMPRA POCAO DE VIDA
            system("cls");
            if (player->gold >= 50) //PREÇO DA POCAO DE VIDA
            {
            Dialogo("Comprando pocao de vida!\n", 0);
            DialogocomClear("Você comprou uma pocao de vida!\n", 0);
            player->pocao += 1;
            player->gold -= 50;
            delay(1000);
            }
            else
            {
             Dialogo("Você não tem coins suficientes para comprar uma pocao de vida", 0);
            }
            menudeloja(player);
            break;
        case 4:
            system("cls");
            if (player->gold >= 20) //PREÇO DA ADAGA
            {
            Dialogo("Comprando adaga!\n", 0);
            DialogocomClear("Você comprou uma adaga!\n", 0);
            player->adagas += 1;
            player->gold -= 20;
            delay(1000);
            }
            else
            {
             Dialogo("Você não tem coins suficientes para comprar uma adaga", 0);
            }
            menudeloja(player);
            break;

        case 5: //SAIR DA LOJA
        Dialogo("Espero te ver novamente em breve!\n", 0);
        delay(1000);
        system("cls");
        break;

    }
} //LOJA DE APRIMORAMENTO DE ITENS

nivel(struct personagem *player, struct enemy *enemy) {
    int escolhas = 0; //ESCOLHA DO JOGADOR
    int caminhos = 0; //COMINHOS A SEGUIR
    int speed = 0; //SPEED SEU AMIGO CONFIANÇA
    int acerto = 0; //CASO ACERTE O ENIGMA
switch (player->nivel)
{
case 1:
    resetvida(player);
    Dialogo("Provavelmente é a primeira vez que você coloca seus pés nessas terras distantes.\n\n", 0);
    Dialogo("Como podemos lhe chamar?\n", 0);
    scanf("%s", player->name);
    delay(500);
    
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
    cor(2);Dialogo("Gyro: ", 0); cor(3);Dialogo("Majestade, se me permite a pergunta, por que é necessária a presença de tantos guerreiros para tal missão?\n", 0);
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
    clear();
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
    Dialogo("Escolha: ", 0); scanf("%d", &escolhas);
    
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

    clear();

    cor(10);Dialogo("Rei: ",0);cor(3);Dialogo("Então que fique decidido dessa forma.",0);
    cor(2);Dialogo(" Gyro ", 0); cor(3); printf("e ");cor(9);Dialogo("Brando ", 0); cor(3); Dialogo("vocês irão juntos.\n Assim sobrando",0);
    cor(1);Dialogo(" Howard ", 0); cor(3); printf("e ");cor(4);Dialogo(" Sheldon ", 0);cor(3); Dialogo("como sendo a outra dupla\n",0);
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
    cor(5);Dialogo("Speed: ", 0); cor(3);Dialogo("Sim, meu Rei!\n",0);
    delay(20);
    printf("%s ", player->name);Dialogo("Sim, meu Rei!\n",0);
    delay(2000);

    cor(10);Dialogo("Rei: ",0);cor(3);Dialogo("Antes gostaria de orientá-los quanto aos inimigos que encontrarão nessas terras\n",0);
    Dialogo("inexploradas do leste. Acredita-se que lá habitam criaturas mágicas de outro mundo, e que\n",0);
    Dialogo("para derrotá-las será preciso imbuir suas armas com encantamentos rúnicos de um ferreiro\n",0);
    Dialogo("mágico. Por sorte, temos o ancião",0); cor(10); Dialogo(" Cultrapali, ", 0); cor(3); Dialogo("conhecedor das artes\n",0);
    Dialogo("mágicas da forja de armas. Então vocês deverão primeiramente se dirigir aos\n",0);
    Dialogo("seus aposentos às minhas ordens e adquirir um encantamento mágico em suas armas. Eu\n",0);
    Dialogo("pessoalmente deixei o senhor",0); cor(10); Dialogo(" Cultrapali, ", 0); cor(3); Dialogo("encarregado de passar as informações do mapa de\n",0);
    Dialogo("rotas até o palácio translúcido.\n",0);
    delay(7000);

    clear();

    Dialogo("Narrador: ", 0); cor(3); Dialogo("Então, os 6 guerreiros se dirigiram ao local onde vivia o ancião que o Rei\nhavia mencionado. Ao baterem na porta do casebre de madeira rústico do senhor,\npara a surpresa de todos, o velho foi bem hospitaleiro com os empolgados\naventureiros. Lá foram realizadas as melhorias nas armas de todos lá presentes.\n",0);cor(10); Dialogo(" Cultrapali ", 0); cor(3); Dialogo("foi direto ao prover todo o suporte para as rotas até o tão almejado\nobjetivo, porém, alertou a todos sobre os perigos que viriam a seguir.\n\n", 0);
    delay(500);
    cor(10); Dialogo("Cultrapali: ", 0); cor(3); Dialogo("Meus jovens, é preciso muita coragem para adentrar tanto aquelas terras do leste.\nDevo avisá-los que diversos perigos esperam vocês, e que precisam ir dispostos a\ndarem suas vidas em nome do reino.\n", 0);
    delay(500);
    cor(9); Dialogo("Brando ", 0); cor(3); Dialogo("Tá de brincadeira né cara? Será preciso só força bruta para pegarmos o tesouro\ne sairmos vivos de lá.\n",0);
    delay(500);
    cor(4); Dialogo("Sheldon ", 0); cor(3); Dialogo("Não seja tão arrogante ",0);cor(9); Dialogo("Brando ", 0); cor(3); Dialogo("não vai ser com perigos comuns que\nvamos lidar nessa jornada.\n",0);
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
        cor(5);Dialogo("Speed: ", 0); cor(3);Dialogo("Admiro sua preocupação com nossa equipe\n",0);
        delay(500);
        player->amizade++;
    }
    else if (escolhas == 2 || escolhas == 4)
    {
        cor(5);Dialogo("Speed: ", 0); cor(3);Dialogo("Sua falta de preocupação pode nos colocar em risco nisso tudo\n",0);
        delay(500);
        player->amizade--;
    }
    else
    {
        cor(5);Dialogo("Speed: ", 0); cor(3);Dialogo("Admiro sua preocupação com nossa equipe\n",0);
        delay(500);
        player->amizade++;
    }
    cor(1);Dialogo("Howard: ", 0); cor(3); Dialogo("Espero que tudo ocorra bem, e nada aconteça com nenhum de nós.\n",0);
    delay(500);
    cor(10); Dialogo("Cultrapali: ", 0); cor(3); Dialogo("Que os Deuses guardem vossos caminhos!\n", 0);
    delay(500);
    cor(4);Dialogo("Sheldon: ",0); cor(3);Dialogo("Um momento, eu gostaria de esclarecer uma dúvida senhor Cultrapali.\n", 0);
    delay(500);
    cor(10); Dialogo("Cultrapali: ", 0); cor(3); Dialogo("Diga-me meu jovem.\n", 0);
    delay(500);
    cor(4);Dialogo("Sheldon: ",0); cor(3);Dialogo("Você mencionou que até o caminho do palácio existem diversos caminhos\nalternativos, o que exatamente quis dizer quando mencionou isso?\n", 0);
    delay(500);
    cor(10); Dialogo("Cultrapali: ", 0); cor(3); Dialogo("Deixe-me ser mais claro. Como todos sabem, nenhum guerreiro nunca foi tão\nlonge naquelas terras obscuras. Tudo o que tínhamos até pouco tempo eram só rumores de como\nera aquele lugar. Mas os estudiosos do Rei obtiveram mapas antigos que informam a\nlocalização exata do lugar que estamos procurando. Porém, como já era de se esperar,\nexistem algumas formas de se chegar lá. No mapa que eu vos entreguei estão todos esses\ncaminhos. Como o Rei os dividiu em duplas seria melhor que ficasse a escolha de cada\numa escolher o caminho que quiser tomar.\n", 0);
    delay(7000);
    printf("\n%s\n", player->name);
    delay(500);
    Dialogo("1 - Então vamos nessa \n",0);
    Dialogo("2 - Que os Deuses nos guardem nessa jornada.\n",0);
    Dialogo("Escolha: ", 0); scanf("%d", &escolhas);
    if (escolhas == 1)
    {
        printf("\n%s ", player->name); Dialogo("Então vamos nessa\n",0);
    }
    else if (escolhas == 2)
    {
        printf("\n%s ", player->name); Dialogo("Que os Deuses nos guardem nessa jornada\n",0);
    }
    else
    {
        printf("\n%s ", player->name); Dialogo("Então vamos nessa\n",0);
    }
    delay(7000);

    clear();

    Dialogo("Narrador: Então as demais duplas de aventureiros tomam seus caminhos, restando\nsomente Speed e ", 0); printf("%s ", player->name); Dialogo("escolherem. Eles observam o mapa e se\ndeparam com a imagens de dois possíveis caminhos junto de escritos que\nrespectivamente dizem “(imagem de uma caverna na montanha carmesim) Essa\nantiga caverna atravessa a colossal montanha do dragão carmesim” e “(imagem da\nfloresta das bruxas) Essa floresta está cheia de segredos obscuros e maldições\n”.",0);
    delay(7000);

    printf("\n%s\n", player->name);
    delay(500);
    Dialogo("Qual caminho você deseja seguir?\n", 0);
    cor(1);Dialogo("1 - Caverna da montanha carmesim \n",0);
    cor(4);Dialogo("2 - Floresta das bruxas.\n",0); cor(3);
    Dialogo("Escolha: ", 0); scanf("%d", &caminhos);
    delay(7000);

    if (caminhos == 1) //CAMINHO PARA IR PELA CAVERNA
    {
        player->nivel = 3;
    }
    else if (caminhos == 2) // CAMINHO PARA IR PELA FLORESTA
    {
        player->nivel = 5;
    }
    else
    {
        player->nivel = 3;
    }
    salvarjogo(player, enemy);
    resetenemy(enemy);
    system("cls");
    nivel(player, enemy);
    break;


    case 3: //CAMINHO CAVERNA DA MONTANHA CARMESIM (PRIMEIRA ESCOLHA)
    cor(1); Dialogo("Caverna da montanha marmesim",0); cor(3);
    delay(500);
    clear();
    Dialogo("Narrador:", 0); printf("%s ", player->name); Dialogo("e Speed chegam até o caminho marcado no mapa e\ndecidem analisar o local para coletar informações. Logo de cara se deparam com uma\ntoupeira de formato humanoide vestida com roupas de minerador. E para surpresa\ndos ambos, o ser desconhecido foi bem receptivo com os guerreiros. \n",0);
    delay(2000);

    printf("\n%s\n", player->name);
    delay(500);
    Dialogo("1 - Olá, somos Guerreiros do Reino de Ratanaba. Estamos buscando informações sobre o\nlocal. \n",0);
    Dialogo("2 - Que tipo de criatura é essa? Identifique-se!\n",0);
    Dialogo("3 - Com licença senhor, sou ",0); printf("%s. ", player->name); Dialogo("Eu e meu companheiro estamos em busca\nde informações sobre esse lugar. \n",0);
    Dialogo("4 - Afaste-se de nós e se identifique. Somos Guerreiros orgulhosos de Ratanaba!\n", 0);
    Dialogo("Escolha: ", 0); scanf("%d", &escolhas);

    if (escolhas == 1 || escolhas == 3)
    {
        cor(2); Dialogo("Lewers: ", 0); cor(3); Dialogo("Me chamo Lewers, sou meio que o cara designado a ser guia de possíveis mineiros que\nresolvem se aventurar por essas bandas.\n",0);
    }
    else if (escolhas == 2 || escolhas == 4)
    {
         cor(2); Dialogo("Lewers: ", 0); cor(3); Dialogo("Quanta hostilidade! Não represento perigo algum, me chamo -Lewers, sou o guia deste local.\n",0);
    }
    else
    {
        cor(2); Dialogo("Lewers: ", 0); cor(3); Dialogo("Me chamo Lewers, sou meio que o cara designado a ser guia de possíveis mineiros que\nresolvem se aventurar por essas bandas.\n",0);
    }
    delay(500);

    cor(5);Dialogo("Speed: ", 0); cor(3);Dialogo("Espera, você é um guia? Essas terras do leste não eram inexploradas?\n",0);
    delay(500);
    cor(2); Dialogo("Lewers: ", 0); cor(3); Dialogo("Não confunda as coisas cara, essa região só não é habitada por humanos. Por\nessas bandas existem somente criaturas mágicas.\n",0);
    delay(500);
    cor(5); Dialogo("Speed: ", 0); cor(3); Dialogo("Não é surpresa que isso seja um mistério para humanos, tantos perigos assim, se\nfossem do conhecimento dos humanos causariam certa comoção. Aliás, perdoe minha\nindelicadeza, me chamo Speed, sou um guerreiro de Ratanaba.\n",0);
    delay(500);
    cor(2); Dialogo("Lewers: ", 0); cor(3); Dialogo("Não achei que fosse de Ratanaba, sua energia vital exala uma origem diferente.\n",0);
    delay(500);
    cor(5); Dialogo("Speed: ", 0); cor(3); Dialogo("c... como assim? É claro que sou do reino de Ratanba! E que história é essa\nde energia vital?\n",0);
    delay(500);
    cor(2); Dialogo("Lewers: ", 0); cor(3); Dialogo("Calma cara, não precisa de tanto alarde assim. Nós criaturas mágica\nconseguimos ver a procedência da sua energia vital, ou seja, o local no qual você nasceu.\nSó fiz um comentário, não quis ser invasivo.\n",0);
    delay(500);
    printf("\n%s\n", player->name);
    delay(500);
    Dialogo("1 - Calma, então você não nasceu no Reino de Ratanaba Speed?\n",0);
    Dialogo("2 - Esse cara deve estar louco, Speed é claramente de Ratanaba.\n",0);
    Dialogo("3 - Que curioso, então você era de outra terra originalmente.\n",0);
    Dialogo("4 - É óbvio que temos um equívoco aqui, sei que Speed é de Ratanaba.\n", 0);
    Dialogo("Escolha: ", 0); scanf("%d", &escolhas);
    delay(500);
    if (escolhas == 1 || escolhas == 3)
    {
        cor(5); Dialogo("Speed: ", 0); cor(3); Dialogo("Claro que não cara, ele com certeza se enganou quanto a isso (fala isso em um tom mais alto).\n",0);
        speed = 1;
        player->amizade++;
    }
    else if (escolhas == 2 || escolhas == 4)
    {
        cor(5); Dialogo("Speed: ", 0); cor(3); Dialogo("Exatamente!! Esse cara se enganou (fala isso em um tom mais alto)\n",0);
        speed = 2;
        player->amizade--;

    }
    else
    {
        cor(5); Dialogo("Speed: ", 0); cor(3); Dialogo("Claro que não cara, ele com certeza se enganou quanto a isso (fala isso em um tom mais alto).\n",0);
        speed = 1;
        player->amizade++;
    }
    delay(500);
    cor(2); Dialogo("Lewers: ", 0); cor(3); Dialogo("Tudo bem, realmente não importa de onde você é. O que vocês desejam com\nessas cavernas antigas?\n",0);
    delay(500);
    cor(5); Dialogo("Speed: ", 0); cor(3); Dialogo("Buscamos um jeito de atravessar essas cavernas até o outro lado da montanha.\n",0);
    delay(500);
    cor(2); Dialogo("Lewers: ", 0); cor(3); Dialogo("Acredito que vá ser bem difícil, mas como são guerreiros acredito que vocês\npossam conseguir.\n",0);
    delay(500);
    cor(5); Dialogo("Speed: ", 0); cor(3); Dialogo("E o que exatamente deixaria tudo isso difícil?\n",0);
    delay(500);
    cor(2); Dialogo("Lewers: ", 0); cor(3); Dialogo("Cara, essa montanha não se chama montanha do dragão carmesim atoa. Como\nera de esperar, em uma das salas de escavação daqui vive um grande dragão de sangue e\nentranhas carmesim. Sem contar os mortos vivos de sangue amaldiçoado.\n",0);
    delay(500);
    printf("\n%s\n", player->name);
    delay(500);
    Dialogo("1 - Então esses são os perigos que o senhor Cultrapali mencionou.\n",0);
    Dialogo("2 - Vamos pessoalmente acabar com todos esses monstros!\n",0);
    Dialogo("3 - Devemos ter o máximo de cautela daqui pra frente.\n",0);
    Dialogo("4 - Nós cuidaremos de exterminar essas criaturas, pode ter certeza!\n", 0);
    Dialogo("Escolha: ", 0); scanf("%d", &escolhas);
    delay(500);
    if (escolhas == 1 || escolhas == 3)
    {
        cor(5); Dialogo("Speed: ", 0); cor(3); Dialogo("Devemos ter muito cuidado nessa área.\n",0);
    }
    else if (escolhas == 2 || escolhas == 4)
    {
        cor(5); Dialogo("Speed: ", 0); cor(3); Dialogo("Devemos enfrentar as criaturas, mas com cautela.\n",0);
    }
    else
    {
        cor(5); Dialogo("Speed: ", 0); cor(3); Dialogo("Devemos ter muito cuidado nessa área.\n",0);
    }

    delay(500);
    cor(2); Dialogo("Lewers: ", 0); cor(3); Dialogo("Então estão dispostos mesmo a seguir caminho?\n",0);
    delay(500);
    cor(5); Dialogo("Speed: ", 0); cor(3); Dialogo("Claro que estamos!!\n",0);
    delay(500);
    cor(2); Dialogo("Lewers: ", 0); cor(3); Dialogo("Então vamos. Mas antes, como eu havia mencionado, sou apenas um guia,\nentão os perigos daqui ficarão para vocês. Outra coisa, não cheguei a mencionar, mas sou\num vendedor de itens, deixe-me mostrar o que tenho pra vocês:\n",0);
    delay(500);
    system("pause");
    menudeloja(player);
    delay(500);
    cor(2); Dialogo("Lewers: ", 0); cor(3); Dialogo("Se já escolheram o que queriam, me acompanhem.\n",0);
    delay(500);
    Dialogo("Narrador: ", 0); cor(2); Dialogo("Lewers ", 0); cor(3); Dialogo("adentra a caverna na frente enquanto os guerreiros o acompanham.\nLogo no início é possível perceber que aquela estranha caverna aparenta estar viva, com\ntodo aquela aparência sangrenta, com estalactites que se assemelham a dentes, e diversos\ncristais vermelhos. É possível ver escrituras nas paredes que dizem “Tudo nesse lugar está\nvivo, mais vivo até mesmo do que os que aqui pisam, porque para eles, está reservada uma\nmorte sangrenta.”Depois de entrarem na caverna, instantes antes de chegarem ao lugar\n",0);
    Dialogo("que",0); cor(2);Dialogo(" Lewers ", 0); cor(3); Dialogo("está, ",0); cor(5); Dialogo("Speed ", 0); cor(3); Dialogo("fala com ",0); printf("%s\n\n", player->name);
    delay(7000);
    if (speed == 1)
    {
        Dialogo("Speed: ", 0); cor(3); Dialogo("Obrigado por ter ficado do meu lado lá atrás,\nadmiro sua confiança em mim\n",0);
    

        printf("\n%s\n", player->name);
        delay(500);
        Dialogo("1 - Sem problemas, apenas tenho confiança em meu companheiro.\n",0);
        Dialogo("2 - Sempre vou estar do lado de um amigo.\n",0);
        Dialogo("Escolha: ", 0); scanf("%d", &escolhas);
        delay(500);
    }
    else if (speed == 2)
    {
        Dialogo("Speed: ", 0); cor(3); Dialogo("Cara, lá atrás, não leva em consideração o que\naquele maluco falou, sou sim do Reino de Ratanaba.\n",0);
        printf("\n%s\n", player->name);
        delay(500);
        Dialogo("1 - Só achei meio estranho o que ele falou, não precisa ficar tão preocupado assim cara.\n",0);
        Dialogo("2 - Se você diz né. Não vou me preocupar com isso, fica de boa cara.\n",0);
        Dialogo("Escolha: ", 0); scanf("%d", &escolhas);
        delay(500);
    }
    else
    {
        Dialogo("Speed: ", 0); cor(3); Dialogo("Obrigado por ter ficado do meu lado lá atrás,\nadmiro sua confiança em mim\n",0);
    

        printf("\n%s\n", player->name);
        delay(500);
        Dialogo("1 - Sem problemas, apenas tenho confiança em meu companheiro.\n",0);
        Dialogo("2 - Sempre vou estar do lado de um amigo.\n",0);
        Dialogo("Escolha: ", 0); scanf("%d", &escolhas);
        delay(500);
    }


    cor(5); Dialogo("Speed: ", 0); cor(3); Dialogo("Me preocupo com isso porque não quero que tenham nenhuma visão errada\nde mim.\n",0);
    delay(500);
    cor(2); Dialogo("*Lewers interrompe*\n", 0); cor(3);
    delay(500);
    cor(2); Dialogo("Lewers: ", 0); cor(3); Dialogo("Chegamos. Vejam, naquela próxima sala já podemos ver um do mortos vivos de\nsangue amaldiçoado. Vocês devem derrotar ele se quiserem seguir em frente.\n",0);
    delay(500);
    cor(5); Dialogo("Speed: ", 0); cor(3); Dialogo("Então vamos!!!",0);
    delay(5000);
    clear();
    resetenemy(enemy);
    enemy->asciienemy = 2;
    strcpy(enemy->name, "Zumbilesca");
    enemy->pv = 30;
    cor(1);
    Dialogo("BATALHA INICIADA:\n", 0);
    Dialogo("“Você se depara com um ser asqueroso de aparência zumbilesca, enfrente-o e vença\ncom sua determinação!”\n", 0);
    cor(3);
    delay(500);
    system("pause");
    batalha(player, enemy);
    delay(500);
    cor(1);
    Dialogo("FIM DA BATALHA:\n", 0);
    Dialogo("“A criatura derrotada começa a se desfazer e aos poucos vai desaparecendo”\n", 0);
    cor(3);
    delay(500);
    cor(2); Dialogo("Lewers: ", 0); cor(3); Dialogo("Vocês são bons caras. Se quiserem comprar algo agora que terminaram\na batalha, fiquem a vontade:\n",0);
    delay(500);
    system("pause");
    menudeloja(player);
    delay(500);
    cor(5); Dialogo("Speed: ", 0); cor(3); Dialogo("Você se saiu bem",0); printf(" %s\n", player->name);
    delay(500);
    printf("\n%s\n", player->name);
    delay(500);
    Dialogo("1 - Valeu cara, você também se saiu bem na batalha.\n",0);
    Dialogo("2 - Você ajudou um pouco, eu acho.\n",0);
    Dialogo("3 - Sem você eu não conseguiria.\n",0);
    Dialogo("4 - Sou bem forte, coisas assim não me abalam.\n", 0);
    Dialogo("Escolha: ", 0); scanf("%d", &escolhas);
    delay(500);
    cor(2); Dialogo("*Lewers interrompe*\n", 0); cor(3);
    delay(500);
    cor(2); Dialogo("Lewers: ", 0); cor(3); Dialogo("Prestem atenção!! Outro morto vivo está saindo da sala logo a frente,\ntomem cuidado.\n",0);
    delay(500);
    cor(5); Dialogo("Speed: ", 0); cor(3); Dialogo("Essas coisas devem estar por todo o lugar. Vamos pôr um fim nisso!!\n",0);
    delay(500);
    cor(1);

    Dialogo("BATALHA INICIADA:\n", 0);
    Dialogo("“Você se depara com um ser asqueroso de aparência zumbilesca, enfrente-o e vença\ncom sua determinação!”\n", 0);
    cor(3);
    resetenemy(enemy);
    strcpy(enemy->name, "Zumbilesca");
    enemy->pv = 30;
    delay(500);
    system("pause");
    batalha(player, enemy);
    delay(500);
    cor(1);
    Dialogo("FIM DA BATALHA:\n", 0);
    Dialogo("“A criatura derrotada começa a se desfazer e aos poucos vai desaparecendo”\n", 0);
    cor(3);
    delay(1000);
    cor(2); Dialogo("Lewers: ", 0); cor(3); Dialogo("Não achei que fossem guerreiros tão habilidosos. O morto vivo não teve a\nmenor chance.\n",0);
    delay(500);
    printf("\n%s\n", player->name);
    delay(500);
    Dialogo("1 - Somos grandes guerreiros de Ratanaba.\n",0);
    Dialogo("2 - Foi meio complicado mas conseguimos\n",0);
    Dialogo("3 - Temos a força para passar por todos os perigos desse lugar.\n",0);
    Dialogo("4 - Ainda bem que estamos em dois nessa missão.\n", 0);
    Dialogo("Escolha: ", 0); scanf("%d", &escolhas);
    delay(500);
    cor(2); Dialogo("Lewers: ", 0); cor(3); Dialogo("Vocês estão se saindo melhor que os outros guerreiros que estão logo a frente.\n",0);
    delay(500);
    cor(5); Dialogo("Speed: ", 0); cor(3); Dialogo("Outros guerreiros?\n",0);
    delay(500);
    cor(2); Dialogo("Lewers: ", 0); cor(3); Dialogo("Sim, são outros caras do mesmo lugar que vocês são.\n",0);
    delay(500);
    Dialogo("Narrador: Logo a frente", 0); printf(" %s ", player->name); printf("e "); cor(5); Dialogo("Speed ", 0); cor(3); Dialogo("encontram",0); cor(1);Dialogo(" Howard ", 0); cor(3); printf("e "); cor(4); Dialogo(" Sheldon\n",0);
    cor(3); Dialogo("parados em frente a uma grande porta com alguns escritos\n",0);
    delay(500);
    cor(5); Dialogo("Speed: ", 0); cor(3); Dialogo("Então vocês vieram por esse caminho também.\n",0);
    delay(500);
    cor(4);Dialogo("Sheldon: ",0); cor(3);Dialogo("Sim. Passamos por todos os monstros mas não conseguimos resolver esse\nmaldito enigma para abrir essa porta.\n",0);
    delay(500);
    cor(1);Dialogo("Howard: ", 0); cor(3);Dialogo("Tentem e vejam se conseguem passar por isso.\n",0);
    delay(500);
    cor(5); Dialogo("Speed: ", 0); cor(3); Dialogo("Você é bom com enigmas ",0); printf("%s ", player->name); Dialogo("Veja se consegue passar por isso.\n",0);
    delay(500);
    printf("\n%s\n", player->name);
    delay(500);
    Dialogo("1 - Verei o que posso fazer.\n",0);
    Dialogo("2 - Algo assim não é nada pra mim!\n",0);
    Dialogo("Escolha: ", 0); scanf("%d", &escolhas);
    delay(500);
    
    while (acerto == 0)
    {
    Dialogo("Enigma\n",0);
    delay(500);
    Dialogo("“O que é que de manhã tem quatro patas, de tarde tem duas e de noite tem três?”\n",0);
    delay(500);
    printf("1 - Cachorro\n");
    delay(500);
    printf("2 - Gato\n");
    delay(500);
    printf("3 - Homem\n");
    delay(500);
    printf("4 - Fênix\n");
    Dialogo("Escolha: ", 0); scanf("%d", &escolhas);

    if (escolhas == 3)
    {
        Dialogo("Acertou!\n",0);
        acerto = 1;
    }
    else
    {
        Dialogo("Você Errou!\n",0);
        delay(500);
        acerto = 0;
        Dialogo("Narrador: Um Raio vermelho sai da parede e acerta sua mão.\n",0);
        Dialogo("Você recebeu 5 de dano.\n",0);
        player->pvjogador -= 5;
    }
    }
    delay(500);
    cor(4);Dialogo("Sheldon: ",0); cor(3);Dialogo("Você é bom com essas coisas hein cara\n",0);
    delay(500);
    clear();
    player->nivel = 4;
    salvarjogo(player, enemy);
    delay(500);
    nivel(player, enemy);
    break;

    case 4: // BOSS CAVER DA MONTANHA CARMESIM
    delay(500);
    Dialogo("Narrador: A grande porta se abre, e atrás dela, para a surpresa dos guerreiros, está o\ngigantesco dragão carmesim. Todos se preparam para a luta que virá a seguir.", 0);
    delay(500);
    resetenemy(enemy);
    enemy->asciienemy = 4;
    strcpy(enemy->name, "Dragão Carmesim");
    enemy->pv = 40;
    cor(1);
    Dialogo("\nBATALHA INICIADA:\n", 0);
    Dialogo("“O gigante dragão exala uma aura macabra, seus dentes são afiados como lâminas, e\ntodo seu corpo parece estar banhado com um sangue mágico escarlate”\n", 0);
    delay(500);
    cor(3);
    delay(500);
    system("pause");
    batalha(player, enemy);
    delay(500);
    cor(1);
    Dialogo("\nFIM DA BATALHA:\n", 0);
    Dialogo("“A criatura derrotada começa a se desfazer e aos poucos vai desaparecendo”\n", 0);
    Dialogo("Narrador: O Dragão Carmesin acabou dropando 50 moedas",0);
    player->gold += 50;
    delay(500);
    cor(5); Dialogo("Speed: ", 0); cor(3); Dialogo("Esse dragão foi duro na queda, ainda bem que estamos juntos nessa batalha.\n",0);
    delay(500);
    cor(2); Dialogo("Lewers: ", 0); cor(3); Dialogo("Vocês se provaram fortes guerreiros. Sintam-se a vontade de comprar algo caso queiram: \n",0);
    delay(500);
    menudeloja(player);
    delay(500);
    printf("\n%s\n", player->name);
    delay(500);
    Dialogo("1 - Vocês ajudaram muito na luta\n",0);
    Dialogo("2 - Com nossas forças derrotamos aquela criatura horrenda \n",0);
    Dialogo("Escolha: ", 0); scanf("%d", &escolhas);
    delay(500);
    Dialogo("Narrador: Antes que pudessem perceber, atrás do que antes era o dragão, surge uma\nsaída para aquela montanha vermelha. Os guerreiros se despedem de Lewers e\nseguem viagem para o próximo lugar no mapa, a cidade das criaturas mágicas\nValladolid", 0);
    delay(500);
    clear();
    player->nivel = 7;
    salvarjogo(player, enemy);
    delay(500);
    nivel(player, enemy);
    break;

    case 5: //FLORESTA DAS BRUXAS (SEGUNDA ESCOLHA)
    cor(4); Dialogo("Floresta das Bruxas",0); cor(3);
    delay(500);
    clear();
    Dialogo("Narrador: ",0);printf("%s", player->name);Dialogo(" e Speed chegam até o caminho marcado no mapa e\ndecidem analisar o local para coletar informações. Logo de cara se deparam com uma\nárvore de forma humanoide. E para surpresa dos ambos, o ser desconhecido foi bem\nreceptivo com os guerreiros.\n",0);
    delay(500);
    printf("\n%s\n", player->name);
    delay(500);
    Dialogo("1 - Olá, somos Guerreiros do Reino de Ratanaba. Estamos buscando informações sobre o local.\n",0);
    Dialogo("2 - Que tipo de criatura é essa? Identifique-se!\n",0);
    Dialogo("3 - Com licença senhor, sou",0);printf("%s ", player->name);Dialogo("Eu e meu companheiro estamos em busca\nde informações sobre esse lugar.\n",0);
    Dialogo("4 - Afaste-se de nós e se identifique. Somos Guerreiros orgulhosos de Ratanaba!\n", 0);
    Dialogo("Escolha: ", 0); scanf("%d", &escolhas);
    delay(500);
        if (escolhas == 1 || escolhas == 3)
    {
        cor(2);Dialogo("George: ", 0); cor(3); Dialogo("Me chamo George, ssou o guia dessa floresta, sem mim aqui\nninguém conseguiria atravessar essa floresta.\n",0);
    }
    else if (escolhas == 2 || escolhas == 4)
    {
         cor(2);Dialogo("George: ", 0); cor(3); Dialogo("Quanta hostilidade! Não represento perigo algum, me chamo -George, sou o guia deste local.\n",0);
    }
    else
    {
        cor(2);Dialogo("George: ", 0); cor(3); Dialogo("Me chamo George, ssou o guia dessa floresta, sem mim aqui\nninguém conseguiria atravessar essa floresta.\n",0);
    }
    delay(500);
    cor(5); Dialogo("Speed: ", 0); cor(3); Dialogo("Espera, você é um guia? Essas terras do leste não eram inexploradas?\n", 0);
    delay(500);
    cor(2);Dialogo("George: ", 0); cor(3); Dialogo("Não confunda as coisas cara, essa região só não é habitada por humanos. Por\nessas bandas existem somente criaturas mágicas.\n",0);
    delay(500);
    cor(5); Dialogo("Speed: ", 0); cor(3); Dialogo(" Não é surpresa que isso seja um mistério para humanos, tantos perigos assim, se\nfossem do conhecimento dos humanos causariam certa comoção. Aliás, perdoe minha\nindelicadeza, me chamo Speed, sou um guerreiro de Ratanaba.\n", 0);
    delay(500);
    cor(2);Dialogo("George: ", 0); cor(3); Dialogo("Não achei que fosse de Ratanaba, sua energia vital exala uma origem diferente.\n",0);
    delay(500);
    cor(5); Dialogo("Speed: ", 0); cor(3); Dialogo("c... como assim? É claro que sou do reino de Ratanba! E que história é essa de\nenergia vital?\n", 0);
    delay(500);
    cor(2);Dialogo("George: ", 0); cor(3); Dialogo("Calma cara, não precisa de tanto alarde assim. Nós criaturas mágicas\nconseguimos ver a procedência da sua energia vital, ou seja, o local no qual você nasceu.\nSó fiz um comentário, não quis ser invasivo.\n",0);
        delay(500);
    printf("\n%s\n", player->name);
    delay(500);
    Dialogo("1 - Calma, então você não nasceu no Reino de Ratanaba Speed?\n",0);
    Dialogo("2 - Esse cara deve estar louco, Speed é claramente de Ratanaba.\n",0);
    Dialogo("3 - Que curioso, então você era de outra terra originalmente.\n",0);
    Dialogo("4 - É óbvio que temos um equívoco aqui, sei que Speed é de Ratanaba.\n", 0);
    Dialogo("Escolha: ", 0); scanf("%d", &escolhas);
    delay(500);
    if (escolhas == 1 || escolhas == 3)
    {
        cor(5); Dialogo("Speed: ", 0); cor(3); Dialogo("Claro que não cara, ele com certeza se enganou quanto a isso (fala isso em um tom mais alto).\n",0);
        speed = 1;
        player->amizade++;
    }
    else if (escolhas == 2 || escolhas == 4)
    {
        cor(5); Dialogo("Speed: ", 0); cor(3); Dialogo("Exatamente!! Esse cara se enganou (fala isso em um tom mais alto)\n",0);
        speed = 2;
        player->amizade--;

    }
    else
    {
        cor(5); Dialogo("Speed: ", 0); cor(3); Dialogo("Claro que não cara, ele com certeza se enganou quanto a isso (fala isso em um tom mais alto).\n",0);
        speed = 1;
        player->amizade++;
    }
    delay(500);
    cor(2);Dialogo("George: ", 0); cor(3); Dialogo("Tudo bem, realmente não importa de onde você é. O que vocês desejam com\nessas cavernas antigas?\n",0);
    delay(500);
    cor(5); Dialogo("Speed: ", 0); cor(3); Dialogo("Buscamos um jeito de atravessar essa floresta.\n",0);
    delay(500);
    cor(2);Dialogo("George: ", 0); cor(3); Dialogo("Acredito que vá ser bem difícil, mas como são guerreiros acredito que vocês\npossam conseguir.\n",0);
    delay(500);
    cor(5); Dialogo("Speed: ", 0); cor(3); Dialogo("E o que exatamente deixaria tudo isso difícil?\n", 0);
    delay(500);
    cor(2);Dialogo("George: ", 0); cor(3); Dialogo("Cara, essa floresta não se chama floresta das bruxas atoa. Como era de esperar,\nesse lugar está cheio de bruxas capazes de usar magias antigas e lançar maldições.\n",0);
    delay(500);
    printf("\n%s\n", player->name);
    delay(500);
    Dialogo("1 - Então esses são os perigos que o senhor Cultrapali mencionou.\n",0);
    Dialogo("2 - Vamos pessoalmente acabar com todos esses monstros!\n",0);
    Dialogo("3 - Devemos ter o máximo de cautela daqui pra frente.\n",0);
    Dialogo("4 - Nós cuidaremos de exterminar essas criaturas, pode ter certeza!\n", 0);
    Dialogo("Escolha: ", 0); scanf("%d", &escolhas);
    delay(500);
    if (escolhas == 1 || escolhas == 3)
    {
        cor(5); Dialogo("Speed: ", 0); cor(3); Dialogo("Devemos ter muito cuidado nessa área.\n",0);
    }
    else if (escolhas == 2 || escolhas == 4)
    {
        cor(5); Dialogo("Speed: ", 0); cor(3); Dialogo("Devemos enfrentar as criaturas, mas com cautela.\n",0);
    }
    else
    {
        cor(5); Dialogo("Speed: ", 0); cor(3); Dialogo("Devemos ter muito cuidado nessa área.\n",0);
    }
    delay(500);
    cor(2);Dialogo("George: ", 0); cor(3); Dialogo("Então estão dispostos mesmo a seguir caminho?\n",0);
    delay(500);
    cor(5); Dialogo("Speed: ", 0); cor(3); Dialogo("Claro que estamos!!\n",0);
    delay(500);
    cor(2);Dialogo("George: ", 0); cor(3); Dialogo("Então vamos. Mas antes, como eu havia mencionado, sou apenas um guia,\nentão os perigos daqui ficarão para vocês. Outra coisa, não cheguei a mencionar, mas\ncarrego comigo alguns itens, deixe-me mostrar o que tenho pra vocês caso queiram\ncomprar:\n",0);
    delay(500);
    clear();
    menudeloja(player);
    delay(500);
    cor(2);Dialogo("George: ", 0); cor(3); Dialogo("Se já escolheram o que queriam, me acompanhem.\n",0);
    delay(500);
    Dialogo("Narrador: ", 0); cor(2); Dialogo("George ", 0); cor(3); Dialogo("entra floresta adentro. No início do caminho é possível perceber que\ntodas aquelas árvores não possuem um tamanho comum, e quanto mais andam, percebem\nque elas tomam uma forma colossal e assustadora. É possível ler certos escritos em uma\ndas gigantescas árvores: “Esse lugar é lar de bruxas, não ouse chegar em nossos\ndomínios, lembre-se, se olhar nos olhos da escuridão ela te olhará de volta.” Depois de\nentrarem na floresta, instantes antes de chegarem ao lugar que ",0); cor(2); Dialogo("George ", 0); cor(3); Dialogo("está, Speed fala com \n",0); printf("%s", player->name);
        if (speed == 1)
    {
        cor(5);Dialogo("Speed: ", 0); cor(3); Dialogo("Obrigado por ter ficado do meu lado lá atrás,\nadmiro sua confiança em mim\n",0);
    

        printf("\n%s\n", player->name);
        delay(500);
        Dialogo("1 - Sem problemas, apenas tenho confiança em meu companheiro.\n",0);
        Dialogo("2 - Sempre vou estar do lado de um amigo.\n",0);
        Dialogo("Escolha: ", 0); scanf("%d", &escolhas);
        delay(500);
    }
    else if (speed == 2)
    {
        cor(5);Dialogo("Speed: ", 0); cor(3); Dialogo("Cara, lá atrás, não leva em consideração o que\naquele maluco falou, sou sim do Reino de Ratanaba.\n",0);
        printf("\n%s\n", player->name);
        delay(500);
        Dialogo("1 - Só achei meio estranho o que ele falou, não precisa ficar tão preocupado assim cara.\n",0);
        Dialogo("2 - Se você diz né. Não vou me preocupar com isso, fica de boa cara.\n",0);
        Dialogo("Escolha: ", 0); scanf("%d", &escolhas);
        delay(500);
    }
    else
    {
        cor(5);Dialogo("Speed: ", 0); cor(3); Dialogo("Obrigado por ter ficado do meu lado lá atrás,\nadmiro sua confiança em mim\n",0);
    

        printf("\n%s\n", player->name);
        delay(500);
        Dialogo("1 - Sem problemas, apenas tenho confiança em meu companheiro.\n",0);
        Dialogo("2 - Sempre vou estar do lado de um amigo.\n",0);
        Dialogo("Escolha: ", 0); scanf("%d", &escolhas);
        delay(500);
    }
    cor(2);Dialogo("*George interrompe*\n", 0); cor(3);
    delay(500);
    cor(2);Dialogo("George: ", 0); cor(3); Dialogo("Estão vendo aquela casa de madeira no meio do caminho? Nela vive uma bruxa\nque mata todos que queiram passar. Se quiserem seguir, vocês devem eliminá-la.\n",0);
    delay(500);
    Dialogo("Narrador: No momento em que George termina de falar, a dita bruxa sai de sua casa e\ndesafia ambos os guerreiros para uma batalha.", 0); 
    delay(500);
    cor(1); Dialogo("\nBruxa da Floresta: ",0); cor(3); Dialogo("hahahaha venham para que eu possa matá-los!! \n",0);  
    delay(500);
    resetenemy(enemy);
    enemy->asciienemy = 3;
    strcpy(enemy->name, "Bruxa da Floresta");
    enemy->pv = 30;
    cor(1);
    Dialogo("\nBATALHA INICIADA:\n", 0);
    Dialogo("“A bruxa montada em uma vassoura puxa sua varinha de um saco mágico e parte\npara cima dos guerreiros”\n", 0);
    cor(3);
    delay(500);
    system("pause");
    batalha(player, enemy);
    delay(500);
    cor(1);
    Dialogo("\nFIM DA BATALHA:\n", 0);
    Dialogo("“A bruxa derrotada começa a se desfazer e aos poucos vai desaparecendo”\n", 0);
    delay(500);
    cor(5); Dialogo("Speed: ", 0); cor(3); Dialogo("Essas magias são bem complicadas de lidar. Você se saiu bem", 0); printf("%s\n ",player->name);
    delay(500);
        printf("\n%s\n", player->name);
    delay(500);
    Dialogo("1 - Valeu cara, você também se saiu bem na batalha.\n",0);
    Dialogo("2 - Você ajudou um pouco, eu acho.\n",0);
    Dialogo("3 - Sem você eu não conseguiria.\n",0);
    Dialogo("4 - Sou bem forte, coisas assim não me abalam.\n", 0);
    Dialogo("Escolha: ", 0); scanf("%d", &escolhas);
    delay(500);
    cor(2);Dialogo("George: ", 0); cor(3); Dialogo("Vocês deram uma lição naquela bruxa. Se precisarem de suprimentos podem\ncomprar comigo:", 0);
    delay(500);
    clear();
    menudeloja(player);
    delay(500);
    Dialogo("Após a vitória é possível escutar o grito de uma mulher pedindo ajuda logo\ndepois da casa da bruxa derrotada. Os guerreiros preocupados vão ao encontro da\nvoz e se deparam com a mulher amarrada. Quando se aproximam, a mulher se revela\ncomo sendo uma bruxa disfarçada. Os guerreiros se preparam para a luta que virá a\nseguir.\n", 0);
    delay(500);
    cor(1); Dialogo("\nBruxa da Floresta: ",0); cor(3); Dialogo("HAHAHAHA como podem cair em uma armadilha tão boba? Tratarei eu\nmesma de matá-los!!\n",0);
    delay(500);
    resetenemy(enemy);
    enemy->asciienemy = 3;
    strcpy(enemy->name, "Bruxa da Floresta");
    enemy->pv = 30;
    cor(1);
    Dialogo("\nBATALHA INICIADA:\n", 0);
    Dialogo("“A bruxa montada em uma vassoura puxa sua varinha de um saco mágico e parte\npara cima dos guerreiros”\n", 0);
    cor(3);
    delay(500);
    system("pause");
    batalha(player, enemy);
    delay(500);
    cor(1);
    Dialogo("\nFIM DA BATALHA:\n", 0);
    Dialogo("“A bruxa derrotada começa a se desfazer e aos poucos vai desaparecendo, mas antes disso ela diz:”\n", 0);
    delay(500);
    cor(1); Dialogo("\nBruxa da Floresta: ",0); cor(3); Dialogo("Você vão ser eliminados pela bruxa rainha seus malditos\n",0);
    delay(500);
    cor(2);Dialogo("George: ", 0); cor(3); Dialogo("Não achei que fossem guerreiros tão habilidosos. O bruxa não teve a menor\nchance. Vocês são bons caras. Se quiserem comprar algo agora que terminaram a batalha,\niquem a vontade:", 0);
    delay(1000);
    clear();
    menudeloja(player);
    delay(500);
    printf("\n%s\n\n", player->name);
    delay(500);
    Dialogo("1 - Bruxa rainha? O que ela quis dizer com isso?\n",0);
    Dialogo("2 - Essa bruxa mencionou sobre essa tal bruxa rainha, devemos nos preocupar com ela?\n",0);
    Dialogo("Escolha: ", 0); scanf("%d", &escolhas);
    delay(500);
    cor(2);Dialogo("George: ", 0); cor(3); Dialogo("A bruxa rainha habita essa floresta desde o início dos tempos. Nem eu sei onde\nela pode entrar. Se tiverem sorte poderão sair desse lugar sem vê-la.\n", 0);
    delay(500);
    cor(5);Dialogo("Speed: ", 0); cor(3); Dialogo("Espero que ela não apareça, todo cuidado é pouco nesse lugar.\n", 0);
    delay(500);
    cor(2);Dialogo("George: ", 0); cor(3); Dialogo("Não se preocupem,  vocês estão se saindo melhor que os outros guerreiros que.\nestão logo a frente.\n", 0);
    delay(500);
    cor(5);Dialogo("Speed: ", 0); cor(3); Dialogo("Outros guerreiros?\n", 0);
    delay(500);
    cor(2);Dialogo("George: ", 0); cor(3); Dialogo("Sim, são outros caras do mesmo lugar que vocês são.\n", 0);
    delay(7000);
    clear();
    Dialogo("Narrador: Logo a frente",0); printf(" %s ", player->name); Dialogo("e Speed encontram ", 0); cor(2);Dialogo("Gyro ", 0); cor(3); printf("e "); cor(9);Dialogo("Brando\n", 0); cor(3);
    Dialogo("parados em frente a uma grande porta com alguns escritos.\n", 0);
    delay(500);
    cor(5);Dialogo("Speed: ", 0); cor(3); Dialogo("Então vocês vieram por esse caminho também.\n", 0);
    delay(500);
    cor(9);Dialogo("Brando: ", 0); cor(3); Dialogo("Sim. Passamos por todos os monstros mas não conseguimos resolver esse\nmaldito enigma para abrir essa porta.", 0);
    delay(500);
    cor(2);Dialogo("Gyro: ", 0); cor(3);Dialogo("Tentem e vejam se conseguem passar por isso.\n", 0);
    delay(500);
    cor(5);Dialogo("Speed: ", 0); cor(3); Dialogo("Você é bom com enigmas ", 0); printf("%s", player->name); Dialogo(", Veja se consegue passar por isso.\n", 0);
    delay(500);
    printf("\n%s\n", player->name);
    delay(500);
    Dialogo("1 - Verei o que posso fazer.\n",0);
    Dialogo("2 - Algo assim não é nada pra mim!\n",0);
    Dialogo("Escolha: ", 0); scanf("%d", &escolhas);
    delay(500);
    
    while (acerto == 0)
    {
    Dialogo("Enigma\n",0);
    delay(500);
    Dialogo("“Qual o ser que mesmo ao atravessar um rio não se molha?”\n",0);
    delay(500);
    printf("1 - Môvel\n");
    delay(500);
    printf("2 - Vaca\n");
    delay(500);
    printf("3 - Ponte\n");
    delay(500);
    printf("4 - Fênix\n");
    Dialogo("Escolha: ", 0); scanf("%d", &escolhas);

    if (escolhas == 3)
    {
        Dialogo("Acertou!\n",0);
        acerto = 1;
    }
    else
    {
        Dialogo("Você Errou!\n",0);
        delay(500);
        acerto = 0;
        Dialogo("Narrador: Um Raio vermelho sai da parede e acerta sua mão.\n",0);
        Dialogo("Você recebeu 5 de dano.\n",0);
        player->pvjogador -= 5;
    }
    }
    delay(500);
    cor(9);Dialogo("Brando: ",0); cor(3);Dialogo("Você é bom com essas coisas hein cara\n",0);
    delay(2000);
    clear();
    player->nivel = 6;
    salvarjogo(player, enemy);
    delay(500);
    nivel(player, enemy);
    break;

    case 6: //BOSS DA FLORESTA DAS BRUXAS
    Dialogo("Narrador: A grande porta se abre, e atrás dela, para a surpresa dos guerreiros, está a\nbruxa rainha em busca de eliminar os invasores de sua floresta Todos se preparam\npara a luta que virá a seguir.\n",0);
    delay(500);
    resetenemy(enemy);
    enemy->asciienemy = 3;
    strcpy(enemy->name, "Bruxa Rainha");
    enemy->pv = 40;
    cor(1);
    Dialogo("\nBATALHA INICIADA:\n", 0);
    Dialogo("A bruxa exala uma aura macabra, seu rosto mostra nada além do que uma escuridão\nprofunda que mostra o seu ódio, ela jura os guerreiros de morte e parte para oencontro deles.\n", 0);
    delay(500);
    cor(3);
    delay(500);
    system("pause");
    batalha(player, enemy);
    delay(500);
    cor(1);
    Dialogo("\nFIM DA BATALHA:\n", 0);
    cor(3);
    Dialogo("A bruxa derrotada começa a se desfazer e aos poucos vai desaparecendo\n", 0);
    Dialogo("Narrador: A Bruxa rainha acabou dropando 50 moedas\n",0);
    player->gold += 50;
    cor(3);
    Dialogo("Narrador: Antes que pudessem perceber, atrás do que antes era a bruxa rainha, surge\numa saída daquele lugar em meio às árvores. Os guerreiros se despedem de George\ne seguem viagem para o próximo lugar no mapa, a cidade das criaturas mágicas Valladolid \n",0);
    delay(500); //MANDAR PARA VALLALOID
    clear();
    player->nivel = 7;
    salvarjogo(player, enemy);
    delay(500);
    nivel(player, enemy);
    break;
    
    case 7: //CIDADE DE VALLADOID
    cor(5);Dialogo("Cidade das criaturas mágicas Valladolid",0);cor(3);
    player->pvjogador = 100;
    delay(500);
    clear();
    Dialogo("Narrador: Os guerreiros ao chegarem, observam que esse lugar é na verdade um\nreino. Eles se dirigem para a entrada das muralhas que envolvem a cidade e\npercebem que elas estão sendo seguradas por dois guardas mágicos armadurados\nde aparência animalesca. Em frente a eles, surpreendentemente, estão os todos os\noutros guerreiros de Ratanaba discutindo com os guardas.\n",0);
    delay(500);
    cor(5);Dialogo("Speed: ", 0); cor(3); Dialogo("O que está acontecendo aqui?", 0);
    delay(500);
    cor(9);Dialogo("Brando: ", 0); cor(3); Dialogo("Esses caras estão falando que não podemos entrar na cidade porque não somos\ncidadãos do reino.\n", 0);
    delay(500);
    cor(4);Dialogo("Sheldon: ",0); cor(3);Dialogo("Isso é uma palhaçada! Precisamos passar por esse lugar para chegar na\npróxima localização do mapa.\n",0);
    delay(500);
    cor(1);Dialogo("Guarda 01: ",0); cor(3);Dialogo("Não sejam ridículos, óbvio que não poderão entrar em nosso reino.\n",0);
    delay(500);
    cor(1);Dialogo("Guarda 02: ",0); cor(3);Dialogo("Exatamente! Por que nós deveríamos liberar a passagem para vocês?\n",0);
    delay(500);
    printf("\n%s\n", player->name);
    delay(500);
    Dialogo("1 - Então esses são os perigos que o senhor Cultrapali mencionou.\n",0);
    Dialogo("2 - Vamos pessoalmente acabar com todos esses monstros!\n",0);
    Dialogo("Escolha: ", 0); scanf("%d", &escolhas);
    delay(500);
    cor(1);Dialogo("Guarda 01: ",0); cor(3);Dialogo(" Não dou a mínima para o que vocês querem, sumam da minha frente\n",0);
    delay(500);
    cor(1);Dialogo("Howard: ",0); cor(3);Dialogo(" Que caras irritantes. Como vamos chegar em nosso objetivo?\n",0);
    delay(500);
    cor(2);Dialogo("Gyro: ", 0); cor(3);Dialogo("Acho que vamos ter que passar por eles na base da for…\n",0);
    cor(9);Dialogo("*Cavaleiro chega e interrompe a conversa”\n",0);
    delay(500);
    cor(9);Dialogo("Thomas: ",0); cor(3);Dialogo("O que esses idiotas querem guardas?\n",0);
    delay(500);
    cor(1);Dialogo("Guarda 02: ",0); cor(3);Dialogo("Querem entrar em nossa cidade para chegarem em outro lugar.\n",0);
    delay(500);
    cor(4);Dialogo("Sheldon: ",0); cor(3);Dialogo("Como assim idiotas? Você quer brigar com a gente cara?\n",0);
    delay(500);
    cor(9);Dialogo("Thomas: ",0); cor(3);Dialogo("Como se vocês fossem capazes de me enfrentar. Não sejam tolos.\n",0);
    delay(500);
    printf("\n%s\n", player->name);
    delay(500);
    Dialogo("1 - Então prove sua força e nos enfrente!\n",0);
    Dialogo("2 - Quanta arrogância, em frente-nós se for capaz\n",0);
    Dialogo("Escolha: ", 0); scanf("%d", &escolhas);
    delay(500);
    cor(9);Dialogo("Thomas: ", 0);cor(3);Dialogo("Não vou perder meu tempo dessa forma com fracotes.\n",0);
    delay(500);
    cor(9);Dialogo("Brando: ", 0);cor(3);Dialogo("Esse cara tá me dando nos nervos. Se está tão seguro de sua força então nos\nenfrente.\n",0);
    delay(500);
    cor(9);Dialogo("Thomas: ", 0);cor(3);Dialogo("Vamos resolver dessa forma, em nosso reino irá acontecer um grande torneio de\nluta. Se vocês conseguirem chegar ao final e ganharem, podem seguir viagem. O que\nacham?\n",0);
    delay(500);
    cor(1);Dialogo("Howard: ",0); cor(3);Dialogo("É claro que aceitamos!! Vamos mostrar pra você que somos capazes!\n",0);
    delay(500);
    cor(2);Dialogo("Gyro: ", 0); cor(3);Dialogo("Vamos fazer você provar da própria arrogância!\n",0);
    delay(500);
    cor(9);Dialogo("Thomas: ", 0);cor(3);Dialogo("Vamos? Só um de vocês poderá entrar nesse torneio.\n",0);
    delay(500);
    printf("\n%s\n", player->name);
    delay(500);
    Dialogo("1 - Eu irei! Vou fazer esse cara entender que somos guerreiros orgulhosos e fortes.\n",0);
    Dialogo("2 - Vou entrar nesse torneio. Ele feriu o nosso orgulho de guerreiros de Ratanaba.\n",0);
    Dialogo("Escolha: ", 0); scanf("%d", &escolhas);
    delay(500);
    cor(5);Dialogo("Speed: ", 0); cor(3); Dialogo("Esse é o espírito",0); printf(" %s. ", player->name); cor(3); Dialogo("Nós confiamos em você!\n",0);
    delay(500);
    Dialogo("Narrador: Thomas conduz os guerreiros pela cidade e os mostra um grande coliseu\nonde ocorrerá o torneio. Lá ele diz que *nome do jogador* pode se preparar como\nquiser com o vendedor Lincon para a sua batalha.\n",0);
    delay(500);
    cor(2);Dialogo("Lincon: ", 0); cor(3); Dialogo("Eae garotos, o que trouxe vocês à minha loja?\n",0);
    delay(500);
    cor(2);Dialogo("Gyro: ", 0); cor(3);Dialogo("Viemos em busca de coisas que possam ajudar nosso amigo aqui para o torneio.\n",0);
    delay(500);
    cor(2);Dialogo("Lincon: ", 0); cor(3); Dialogo("Vejam o que posso oferecer a você amigo:\n",0);
    clear();
    menudeloja(player);
    delay(500);
    cor(2);Dialogo("Lincon: ", 0); cor(3); Dialogo("Espero que isso seja de ajuda em sua batalha",0); printf(" %s. \n", player->name);
    delay(500);
    printf("\n%s\n", player->name);
    delay(500);
    Dialogo("1 - Isso vai ser de grande ajuda nesse torneio.\n",0);
    Dialogo("2 - Acho que posso me virar com isso.\n",0);
    Dialogo("Escolha: ", 0); scanf("%d", &escolhas);
    delay(500);
    cor(5);Dialogo("Speed: ", 0); cor(3); Dialogo("Já fizemos o que tínhamos que fazer, vamos para o coliseu.\n",0);
    delay(500);
    cor(2);Dialogo("Lincon: ", 0); cor(3); Dialogo("Espera, você aí, de onde você é guerreiro?\n",0);
    delay(500);
    cor(5);Dialogo("Speed: ", 0); cor(3); Dialogo("O… o que? Como assim?\n",0);
    delay(500);
    cor(2);Dialogo("Lincon: ", 0); cor(3); Dialogo("Vocês são de Ratanaba não são? Essa sua armadura está ornamentada com\nsímbolos da nação de Kanto\n",0);
    delay(500);
    cor(9);Dialogo("Brando: ", 0);cor(3);Dialogo("Verdade, nunca vi uma armadura assim em nosso reino.\n",0);
    delay(500);
    printf("\n%s\n", player->name);
    delay(500);
    Dialogo("1 - Acredito em Speed, talvez seja só um engano.\n",0);
    Dialogo("2 - Isso é verdade Speed? Essa armadura não é da nossa nação?\n",0);
    Dialogo("3 - Confio no que Speed falou, isso é só um engano.\n",0);
    Dialogo("4 - Como assim Kanto?\n", 0);
    Dialogo("Escolha: ", 0); scanf("%d", &escolhas);
    delay(500);
    if (escolhas == 1 || escolhas == 3)
    {
        cor(5); Dialogo("Speed: ", 0); cor(3); Dialogo("Verdade, devemos nos atentar a outras coisas agora cara, isso é perda de tempo.\n",0);
        speed = 1;
        player->amizade++;
    }
    else if (escolhas == 2 || escolhas == 4)
    {
        cor(5); Dialogo("Speed: ", 0); cor(3); Dialogo("Não faço ideia do que esse cara esteja falando. Vamos focar no que devemos fazer agora.\n",0);
        speed = 2;
        player->amizade--;

    }
    else
    {
        cor(5); Dialogo("Speed: ", 0); cor(3); Dialogo("Claro que não cara, ele com certeza se enganou quanto a isso (fala isso em um tom mais alto).\n",0);
        speed = 1;
        player->amizade++;
    }
    delay(500);
    cor(1);Dialogo("Howard: ",0); cor(3);Dialogo("Isso é meio estranho, mas ele está certo, vamos fazer o que temos que fazer agora.\n",0);
    delay(500);
    clear();
    Dialogo("Narrador: Os guerreiros deixam de lado a discussão e resolvem ir para o coliseu. Lá\nsão divulgados os guerreiros que *nome do jogador* irá enfrentar. Sendo\nrespectivamente Sans, um lutador esqueleto, Jhonny, um atirador de elite, e Thomas, o\npríncipe do reino de Valladolid.\n",0); printf(" %s ", player->name);Dialogo("entra na arena de combate e\nencontra Sans.",0);
    delay(500);
    cor(10);Dialogo("Apresentador do Coliseu: ",0);cor(3);Dialogo("Senhoras e senhores, hoje temos uma luta interessante. Do\nlado esquerdo temos Sans, o nosso lutador orgulhoso. Do outro temos um lutador humano\ndo Reino de Ratanaba.\n",0);
    delay(500);
    cor(1);Dialogo("Plateia: ",0);cor(3);Dialogo("ACABA COM ELE SANS!!!\n",0);
    delay(500);
    cor(6);Dialogo("Sans: ",0);cor(3);Dialogo("Olá guerreiro estrangeiro, será uma honra lutar com você nesse torneio.\nPrometo dar o meu máximo nessa batalha.\n",0);
    delay(500);
    printf("\n%s\n", player->name);
    delay(500);
    Dialogo("1 - Faremos uma batalha justa e honrosa meu amigo.\n",0);
    Dialogo("2 - Vou acabar com você!!?\n",0);
    Dialogo("3 - Gosto do seu espírito de luta, será uma honra lutar com você!\n",0);
    Dialogo("4 - Em nome do reino de Ratanaba, eu vou derrota-lo!\n", 0);
    Dialogo("Escolha: ", 0); scanf("%d", &escolhas);
    delay(500);
    cor(10);Dialogo("Apresentador do Coliseu: ",0);cor(3);Dialogo("LUTEM!!!\n",0);
    delay(500);
    resetenemy(enemy);
    enemy->asciienemy = 1;
    strcpy(enemy->name, "Sans");
    enemy->pv = 60;
    cor(1);
    Dialogo("\nBATALHA INICIADA:\n", 0);
    Dialogo("“Sans é um poderoso lutador extremamente ágil e experiente com o combate com os\npunhos. Tenha determinação e vença-o”.\n", 0);
    delay(500);
    cor(3);
    delay(500);
    system("pause");
    batalha(player, enemy);
    delay(500);
    cor(1);
    Dialogo("\nFIM DA BATALHA:\n", 0);
    cor(3);
    Dialogo("Sans cai no chão derrotado inconsciente\nVocê ganha 50 ouro de apostas!", 0);
    player->gold += 50;
    delay(500);
    cor(10);Dialogo("Apresentador do Coliseu: ",0);cor(3);Dialogo("O lutador",0); printf(" %s ", player->name);Dialogo("se mostrou um um forte\ncompetidor nessa luta",0);
    delay(500);
    cor(9);Dialogo("Thomas: ",0);cor(3);Dialogo(" Você é interessante cara. Não achei que fosse tão forte assim, espero que nos\nencontremos no final desse torneio.\n",0);
    delay(500);
    Dialogo("Narrador: ",0); printf(" %s ", player->name);Dialogo("e os demais guerreiros voltam para a loja de Lincon\npara adquirir novos itens para a próxima batalha. ",0);
    delay(500);
    cor(2);Dialogo("Lincon: ", 0); cor(3); Dialogo("Então você se saiu bem, não é garoto. Dê uma olhada no que tenho para vender:", 0);
    delay(500);
    clear();
    menudeloja(player);
    delay(500);
    cor(2);Dialogo("Lincon: ", 0); cor(3); Dialogo("O príncipe Thomas realmente está ansioso por uma luta com você", 0); printf(" %s, ", player->name);Dialogo("ele vê potencial em você.\n", 0);
    delay(500);
    cor(4);Dialogo("Sheldon: ",0); cor(3);Dialogo("Esses caras loucos por luta são os piores.\n",0);
    delay(500);
    cor(2);Dialogo("Gyro: ", 0); cor(3);Dialogo("Por que?\n", 0);
    delay(500);
    cor(4);Dialogo("Sheldon: ",0); cor(3);Dialogo("Porque esse tipo de cara faz tudo que for possível pra vencer. Por isso você\ndeve tomar cuidado",0);printf(" %s, ", player->name);Dialogo("isso pode ser só um torneio, mas essa luta pode\ncustar a sua vida.\n", 0);
    delay(500);
    printf("\n%s\n", player->name);
    delay(500);
    Dialogo("1 - Agradeço o seu aviso, tomarei cuidado.\n",0);
    Dialogo("2 - Isso não importa! Eu o derrotarei de qualquer forma.\n",0);
    Dialogo("3 - Tomarei todo cuidado possível.\n",0);
    Dialogo("4 - Basta ir com tudo pra cima dele.\n", 0);
    Dialogo("Escolha: ", 0); scanf("%d", &escolhas);
    delay(500);
    Dialogo("Narrador: Os guerreiros voltam para o coliseu para a próxima batalha. Lá encontram\nJhonny já preparado para a luta.",0); printf(" %s, ", player->name);Dialogo("entra na arena e o combate se inicia.\n", 0);
    delay(500);
    cor(10);Dialogo("Apresentador do Coliseu: ",0);cor(3);Dialogo("Temos agora o guerreiro",0); printf(" %s ", player->name);Dialogo("e o lutador Jhonny. Que essa batalha seja proveitosa.\n", 0);
    delay(500);
    cor(5);Dialogo("Jhonny: ",0);cor(3);Dialogo("Vou acabar com você cara! Essa luta está nas minhas mãos.\n",0);
    delay(500);
    printf("\n%s\n", player->name);
    delay(500);
    Dialogo("1 - É o que veremos.\n",0);
    Dialogo("2 - Eu vou destruir você!\n",0);
    Dialogo("3 - Farei você ver que não será dessa forma\n",0);
    Dialogo("4 - Tome cuidado, posso acabar com você facilmente da forma que eu quiser\n", 0);
    Dialogo("Escolha: ", 0); scanf("%d", &escolhas);
    delay(500);
    cor(10);Dialogo("Apresentador do Coliseu: ",0);cor(3);Dialogo("LUTEM!!!",0);
    delay(500);
    resetenemy(enemy);
    enemy->asciienemy = 1;
    strcpy(enemy->name, "Jhonny");
    enemy->pv = 53;
    cor(1);
    Dialogo("\nBATALHA INICIADA:\n", 0);
    Dialogo("“Jhonny é um lutador muito habilidoso com armas a distância.\nTenha determinação e vença-o”.\n", 0);
    delay(500);
    cor(3);
    delay(500);
    system("pause");
    batalha(player, enemy);
    delay(500);
    cor(1);
    Dialogo("\nFIM DA BATALHA:\n", 0);
    cor(3);
    Dialogo("Jhonny cai no chão derrotado inconsciente\nVocê ganha 50 ouro de apostas!", 0);
    player->gold += 50;
    delay(500);
    cor(1);Dialogo("Plateia: ",0);cor(3);Dialogo("ACABEM COM ESSE CARA!!!\n",0);
    delay(500);
    cor(10);Dialogo("Apresentador do Coliseu: ",0);cor(3);Dialogo("Aparentemente a plateia não gostou da vitória do\nguerreiro estrangeiro.",0);
    delay(500);
    cor(1);Dialogo("Plateia: ",0);cor(3);Dialogo("O PRÍNCIPE VAI ACABAR COM A RAÇA DESSE CARA!\n",0);
    delay(500);
    







    break;

    case 8: //FINAL (PALÁCIO FANTASMA)
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
    player.gold = 100;
    player.nivel = 1;
    player.pocao = 0;
    player.pvjogador = 100;
    inimigo.asciienemy = 1;

    menu(&player, &inimigo);

    SetConsoleOutputCP(CPAGE_DEFAULT);
  return 0;
}