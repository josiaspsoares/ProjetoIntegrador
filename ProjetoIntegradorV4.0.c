#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include <time.h>
#ifdef __WIN32__
#include <windows.h>
#else
#include <unistd.h>
#endif
#include "erroFunctions.h"
#include "definicaoCores.h"

int cadastroTimesConcluido = 0;
int faseGruposCadastrada = 0;
int faseGruposRealizada = 0;
int oitavasCadastrada = 0;
int oitavasRealizada = 0;
int quartasCadastrada = 0;
int quartasRealizada = 0;
int semifinaisCadastrada = 0;
int semifinaisRealizada = 0;
int finalCadastrada = 0;
int finalRealizada = 0;
int terceiroCadastrada = 0;
int terceiroRealizada = 0;


typedef struct{
    char equipes[30];
    int id;
    int pontos;
    int vitorias;
    int empates;
    int derrotas;
    int gols;
    int golsSofridos;
    int saldo;
}DATA;
DATA CadastroGrupos[32];
DATA Oitavas[16];
DATA Quartas[8];
DATA Semifinais[4];
DATA Final[2];
DATA DisputaTerceiro[2];
DATA Podio[3];
DATA TabelaGeral[32];

typedef struct{
    char equipes[30];
    int id;
    int pontos;
    int vitorias;
    int empates;
    int derrotas;
    int gols;
    int golsSofridos;
    int saldo;
}COPIA;
COPIA TIMES[33];

typedef struct{
    char dataJogo[25];
    char horaJogo[10];
    char localJogo[60];
}PLAY;
PLAY FaseGrupos[48];
PLAY PartidasOitavas[8];
PLAY PartidasQuartas[4];
PLAY PartidasSemifinais[2];
PLAY PartidaTerceiro[1];
PLAY PartidaFinal[1];


void zerarVariaveis(int tamanho, DATA *FaseZerar);
void erro1(char *fase);
void erro2(char *etapa);
void erro3(char *ciclo);
void erro4(char *fase);
void cadastrarTimesManual();
void armazenarDadosTimes();
void cadastrarTimesAutomatico();
void exibirGrupos();
void cadastroFaseDeGrupos();
void cadastroPartidasAutomatico(int tamanho, PLAY *Partida, int arquivo);
void cadastroPartidasManualmente(int tamanho, PLAY *Partida, DATA *Fase);
void realizarFaseDeGrupos();
void exibirTabelaGrupos();
void classificados(int quantidade, DATA *Classificados);
void cadastrarOitavas();
void realizarOitavas();
void cadastrarQuartas();
void realizarQuartas();
void cadastrarSemifinais();
void realizarSemifinais();
void cadastrarTerceiro();
void realizarDisputaTerceiro();
void cadastrarFinal();
void realizarFinal();
void exibirPodio();
void exibirTabelaGeral();
void processarJogos();
void ordenaGrupoDecrescente(int t1, int t2);
void ordenaGrupoSaldo(int t3, int t4);
void ordenaGrupoGols(int t3, int t4);
void ordenaGrupoGolsSofridos(int t3, int t4);
void armazenarTabelaGeral(int tamanho, DATA *Fase);
void PreencherCopia();
void OrdenarSaldo();
void OrdenarGols();
void OrdenarGolsSofridos();
void OrdenarVitorias();
void OrdenarDerrotas();
void OrdenarEmpates();

int main(){
    system("color F");


    setlocale(LC_ALL, "Portuguese");
    int opcao;

    zerarVariaveis(32, CadastroGrupos);
    system("cls");

    do{
        printf( "\t*** MENU PRINCIPAL ***\n\n");
        printf(" 0) SAIR.\n");
        printf(" 1) CADASTRO DE TIMES.\n");
        printf(" 2) FASE DE GRUPOS.\n");
        printf(" 3) OITAVAS DE FINAL.\n");
        printf(" 4) QUARTAS DE FINAL.\n");
        printf(" 5) SEMIFINAIS.\n");
        printf(" 6) DISPUTA PELO 3∞ LUGAR.\n");
        printf(" 7) FINAL.\n");
        printf(" 8) ESTATÕSTICAS.\n\n");

        do {
            printf("OP«√O: ");
            fflush(stdin);
            scanf("%d", &opcao);
        }while (opcao!=0 && opcao!=1 && opcao!=2 && opcao!=3 && opcao!=4 && opcao!=5 && opcao!=6 && opcao!=7 && opcao!=8);

        switch (opcao){
            case 0: break;
            case 1: {

                if(cadastroTimesConcluido == 0){
                    system("cls");
                    printf("\n\t**** CADASTRO DE TIMES***\n");
                    printf( "\n\nVOC  DESEJA CADASTRAR AUTOMATICAMENTE OU MANUALMENTE?\n\n");
                    printf(" > Tecle 1 AUTOMATICAMENTE\n > Tecle 2 MANUALMENTE\n\n");

                    do {
                        printf( "OP«√O: ");
                        fflush(stdin);
                        scanf("%c", &opcao);
                    }while (opcao!='1' && opcao!='2');
                    
                    system("cls");
                    if (opcao=='1'){
                        cadastrarTimesAutomatico();
                        cadastroTimesConcluido = 1;
                    }
                    else if(opcao == '2'){
                        cadastrarTimesManual();
                        cadastroTimesConcluido = 1;
                    }
                }
                else{
                    erro1("DE TIMES");
                }

            };break;
            case 2: {

                do{
                    system("cls");
                    printf("\n\t**** FASE DE GRUPOS ***\n\n");
                    printf(" 0 - MENU ANTERIOR.\n");
                    printf(" 1 - EXIBIR GRUPOS.\n");
                    printf(" 2 - CADASTRAR JOGOS DA FASE DE GRUPOS.\n");
                    printf(" 3 - REALIZAR JOGOS DA FASE DE GRUPOS.\n");
                    printf(" 4 - EXIBIR TABELA DA FASE DE GRUPOS.\n");
                    printf(" 5 - EXIBIR CLASSIFICADOS PARA AS OITAVAS DE FINAL.\n\n");

                    do {
                        printf("OP«√O: ");
                        fflush(stdin);
                        scanf("%c", &opcao);
                    }while (opcao!='0' && opcao!='1' && opcao!='2' && opcao!= '3' && opcao!= '4'&& opcao!= '5');

                    switch(opcao){
                        case '0': break;
                        case '1': {
                            system("cls");
                            if(cadastroTimesConcluido == 0){
                                erro2("DE TIMES");
                            }
                            else{
                                exibirGrupos();
                            }
                        }; break;
                        case '2': {
                            system("cls");
                            if(cadastroTimesConcluido == 0){
                                erro2("DE TIMES");
                            }
                            else if(faseGruposCadastrada == 0){
                                printf("\n\t**** CADASTRO DE INFORMA«’ES***\n");
                                printf( "\n\nVOC  DESEJA CADASTRAR AUTOMATICAMENTE OU MANUALMENTE?\n\n");
                                printf(" > Tecle 1 AUTOMATICAMENTE\n > Tecle 2 MANUALMENTE\n\n");

                                do {
                                    printf( "OP«√O: ");
                                    fflush(stdin);
                                    scanf("%c", &opcao);
                                }while (opcao!='1' && opcao!='2');

                                if (opcao=='1'){
                                    cadastroPartidasAutomatico(48, FaseGrupos, 1);
                                    faseGruposCadastrada = 1;
                                }
                                else if(opcao == '2'){
                                    system("cls");
                                    cadastroFaseDeGrupos();
                                    faseGruposCadastrada = 1;
                                }
                            }
                            else{
                                erro1("DA FASE DE GRUPOS");
                            }


                        };break;
                        case '3': {
                            system("cls");
                            if(faseGruposCadastrada == 0){
                                erro2("DA FASE DE GRUPOS");
                            }
                            else if(faseGruposRealizada == 1){
                                erro4("A FASE DE GRUPOS");
                            }
                            else{
                                realizarFaseDeGrupos();
                                PreencherCopia();
                                faseGruposRealizada = 1;
                            }
                        };break;
                        case '4': {
                            system("cls");
                            if(faseGruposRealizada == 0){
                                erro3("FASE DE GRUPOS");
                            }
                            else{
                                exibirTabelaGrupos();
                            }
                        };break;
                        case '5': {
                            system("cls");
                            if(faseGruposRealizada == 0){
                                erro3("FASE DE GRUPOS");
                            }
                            else{
                                classificados(16, Oitavas);
                            }
                        }
                        default: break;
                    }
                }while(opcao != '0');

            };break;
            case 3: {

                do{
                    system("cls");
                    printf("\n\t**** OITAVAS DE FINAL ***\n\n");
                    printf(" 0 - SAIR.\n");
                    printf(" 1 - CADASTRAR JOGOS.\n");
                    printf(" 2 - REALIZAR JOGOS.\n");
                    printf(" 3 - EXIBIR CLASSIFICADOS PARA AS QUARTAS DE FINAL.\n\n");

                    do {
                        printf("OP«√O: ");
                        fflush(stdin);
                        scanf("%c", &opcao);
                    }while (opcao!='0' && opcao!='1' && opcao!='2' && opcao!= '3');

                    switch(opcao){
                        case '0': break;
                        case '1': {
                            system("cls");
                            if(faseGruposRealizada == 0){
                                erro3("FASE DE GRUPOS");
                            }
                            else if(oitavasCadastrada == 0){
                                printf("\n\t**** CADASTRO DE INFORMA«’ES***\n");
                                printf( "\n\nVOC  DESEJA CADASTRAR AUTOMATICAMENTE OU MANUALMENTE?\n\n");
                                printf(" > Tecle 1 AUTOMATICAMENTE\n > Tecle 2 MANUALMENTE\n\n");

                                do {
                                    printf( "OP«√O: ");
                                    fflush(stdin);
                                    scanf("%c", &opcao);
                                }while (opcao!='1' && opcao!='2');

                                if (opcao=='1'){
                                    cadastroPartidasAutomatico(8, PartidasOitavas, 2);
                                    oitavasCadastrada = 1;
                                }
                                else if(opcao == '2'){
                                    cadastroPartidasManualmente(8, PartidasOitavas, Oitavas);
                                    oitavasCadastrada = 1;
                                }
                            }
                            else{
                                erro1("DAS OITAVAS DE FINAL");
                            }
                        };break;
                        case '2': {
                            system("cls");
                            if(oitavasCadastrada == 0){
                                erro2("DAS OITAVAS DE FINAL");
                            }
                            else if(oitavasRealizada == 1){
                                erro4("AS OITAVAS DE FINAL");
                            }
                            else{
                                realizarOitavas();
                                oitavasRealizada = 1;
                            }
                        };break;
                        case '3': {
                            system("cls");
                            if(oitavasRealizada == 0){
                                erro5("OITAVAS DE FINAL");
                            }
                            else{
                                classificados(8, Quartas);
                            }
                        }break;
                        default: break;
                    }
                }while(opcao != '0');

            };break;
            case 4:
                 do{
                    system("cls");
                    printf("\n\t****  QUARTAS DE FINAL ***\n\n");
                    printf(" 0 - SAIR.\n");
                    printf(" 1 - CADASTRAR JOGOS.\n");
                    printf(" 2 - REALIZAR JOGOS.\n");
                    printf(" 3 - EXIBIR CLASSIFICADOS PARA AS SEMIFINAIS.\n\n");

                    do {
                        printf("OP«√O: ");
                        fflush(stdin);
                        scanf("%c", &opcao);
                    }while (opcao!='0' && opcao!='1' && opcao!='2' && opcao!= '3');

                    switch(opcao){
                        case '0': break;
                        case '1': {
                            system("cls");
                            if(oitavasRealizada == 0){
                                erro5("OITAVAS DE FINAL");
                            }
                            else if(quartasCadastrada == 0){
                                printf("\n\t**** CADASTRO DE INFORMA«’ES***\n");
                                printf( "\n\nVOC  DESEJA CADASTRAR AUTOMATICAMENTE OU MANUALMENTE?\n\n");
                                printf(" > Tecle 1 AUTOMATICAMENTE\n > Tecle 2 MANUALMENTE\n\n");

                                do {
                                    printf( "OP«√O: ");
                                    fflush(stdin);
                                    scanf("%c", &opcao);
                                }while (opcao!='1' && opcao!='2');

                                if (opcao=='1'){
                                    cadastroPartidasAutomatico(4, PartidasQuartas, 3);
                                    quartasCadastrada = 1;
                                }
                                else if(opcao == '2'){
                                    cadastroPartidasManualmente(4, PartidasQuartas, Quartas);
                                    quartasCadastrada = 1;
                                }
                            }
                            else{
                                erro1("DAS QUARTAS DE FINAL");
                            }
                        };break;
                        case '2': {
                            system("cls");
                            if(quartasCadastrada == 0){
                                erro2("DAS QUARTAS DE FINAL");
                            }
                            else if(quartasRealizada == 1){
                                erro6("AS QUARTAS DE FINAL");
                            }
                            else{
                                realizarQuartas();
                                quartasRealizada = 1;
                            }
                        };break;
                        case '3': {
                            system("cls");
                            if(quartasRealizada == 0){
                                erro5("QUARTAS DE FINAL");
                            }
                            else{
                                classificados(4, Semifinais);
                            }
                        }break;
                        default: break;
                    }
                }while(opcao != '0');
            ;break;


            case 5:
                 do{
                    system("cls");
                    printf("\n\t****  SEMIFINAL  ***\n\n");
                    printf(" 0 - SAIR.\n");
                    printf(" 1 - CADASTRAR JOGOS.\n");
                    printf(" 2 - REALIZAR JOGOS.\n");
                    printf(" 3 - EXIBIR CLASSIFICADOS PARA A FINAL .\n\n");

                    do {
                        printf("OP«√O: ");
                        fflush(stdin);
                        scanf("%c", &opcao);
                    }while (opcao!='0' && opcao!='1' && opcao!='2' && opcao!= '3');

                    switch(opcao){
                        case '0': break;
                        case '1': {
                            system("cls");
                            if(quartasRealizada == 0){
                                erro5("QUARTAS DE FINAL");
                            }
                            else if(semifinaisCadastrada == 0){
                                printf("\n\t**** CADASTRO DE INFORMA«’ES***\n");
                                printf( "\n\nVOC  DESEJA CADASTRAR AUTOMATICAMENTE OU MANUALMENTE?\n\n");
                                printf(" > Tecle 1 AUTOMATICAMENTE\n > Tecle 2 MANUALMENTE\n\n");

                                do {
                                    printf( "OP«√O: ");
                                    fflush(stdin);
                                    scanf("%c", &opcao);
                                }while (opcao!='1' && opcao!='2');

                                if (opcao=='1'){
                                    cadastroPartidasAutomatico(2, PartidasSemifinais, 4);
                                    semifinaisCadastrada = 1;
                                }
                                else if(opcao == '2'){
                                    cadastroPartidasManualmente(2, PartidasSemifinais, Semifinais);
                                    semifinaisCadastrada = 1;
                                }
                            }
                            else{
                                erro1("DAS SEMIFINAIS");
                            }
                        };break;
                        case '2': {
                            system("cls");
                            if(semifinaisCadastrada == 0){
                                erro2("DAS SEMIFINAIS");
                            }
                            else if(semifinaisRealizada == 1){
                                erro6("AS SEMIFINAIS");
                            }
                            else{
                                realizarSemifinais();
                                semifinaisRealizada = 1;
                            }
                        };break;
                        case '3': {
                            system("cls");
                            if(semifinaisRealizada == 0){
                                erro5("SEMIFINAIS");
                            }
                            else{
                                classificados(2, Final);
                            }
                        }break;
                        default: break;
                    }
                }while(opcao != '0');
            ;break;


            case 6:
                do{
                    system("cls");
                    printf("\n\t****  DISPUTA PELO TERCEIRO LUGAR  ***\n\n");
                    printf(" 0 - SAIR.\n");
                    printf(" 1 - CADASTRAR JOGO.\n");
                    printf(" 2 - REALIZAR JOGO.\n\n");

                    do {
                        printf("OP«√O: ");
                        fflush(stdin);
                        scanf("%c", &opcao);
                    }while (opcao!='0' && opcao!='1' && opcao!='2');

                    switch(opcao){
                        case '0': break;
                        case '1': {
                            system("cls");
                            if(semifinaisRealizada == 0){
                                erro5("SEMIFINAIS");
                            }
                            else if(terceiroCadastrada == 0){
                                printf("\n\t**** CADASTRO DE INFORMA«’ES***\n");
                                printf( "\n\nVOC  DESEJA CADASTRAR AUTOMATICAMENTE OU MANUALMENTE?\n\n");
                                printf(" > Tecle 1 AUTOMATICAMENTE\n > Tecle 2 MANUALMENTE\n\n");

                                do {
                                    printf( "OP«√O: ");
                                    fflush(stdin);
                                    scanf("%c", &opcao);
                                }while (opcao!='1' && opcao!='2');

                                if (opcao=='1'){
                                    cadastroPartidasAutomatico(1, PartidaTerceiro, 5);
                                    terceiroCadastrada = 1;
                                }
                                else if(opcao == '2'){
                                    cadastroPartidasManualmente(1, PartidaTerceiro, DisputaTerceiro);
                                    terceiroCadastrada = 1;
                                }
                            }
                            else{
                                erro1("DA DISPUTA PELO TERCEIRO LUGAR");
                            }
                        };break;
                        case '2': {
                            system("cls");
                            if(terceiroCadastrada == 0){
                                erro2("DA DISPUTA PELO TERCEIRO LUGAR");
                            }
                            else if(terceiroRealizada == 1){
                                erro4("A DISPUTA PELO TERCEIRO LUGAR");
                            }
                            else{
                                realizarDisputaTerceiro();
                                terceiroRealizada = 1;
                            }
                        };break;
                        default: break;
                    }
                }while(opcao != '0');
            ;break;

            case 7:
                do{
                    system("cls");
                    printf("\n\t****  DISPUTA DA FINAL  ***\n\n");
                    printf(" 0 - SAIR.\n");
                    printf(" 1 - CADASTRAR JOGO.\n");
                    printf(" 2 - REALIZAR JOGO.\n");
                    printf(" 3 - P”DIO.\n\n");

                    do {
                        printf("OP«√O: ");
                        fflush(stdin);
                        scanf("%c", &opcao);
                    }while (opcao!='0' && opcao!='1' && opcao!='2' && opcao!= '3');

                    switch(opcao){
                        case '0': break;
                        case '1': {
                            system("cls");
                            if(terceiroRealizada == 0){
                                erro3("DISPUTA PELO TERCEIRO LUGAR");
                            }
                            else if(finalCadastrada == 0){
                                printf("\n\t**** CADASTRO DE INFORMA«’ES***\n");
                                printf( "\n\nVOC  DESEJA CADASTRAR AUTOMATICAMENTE OU MANUALMENTE?\n\n");
                                printf(" > Tecle 1 AUTOMATICAMENTE\n > Tecle 2 MANUALMENTE\n\n");

                                do {
                                    printf( "OP«√O: ");
                                    fflush(stdin);
                                    scanf("%c", &opcao);
                                }while (opcao!='1' && opcao!='2');

                                if (opcao=='1'){
                                    cadastroPartidasAutomatico( 1, PartidaFinal, 6);
                                    finalCadastrada = 1;
                                }
                                else if(opcao == '2'){
                                    cadastroPartidasManualmente(1, PartidaFinal, Final);
                                    finalCadastrada = 1;
                                }
                            }
                            else{
                                erro1("DA FINAL");
                            }
                        };break;
                        case '2': {
                            system("cls");
                            if(finalCadastrada == 0){
                                erro2("DA FINAL");
                            }
                            else if(finalRealizada == 1){
                                erro4("A FINAL");
                            }
                            else{
                                realizarFinal();
                                finalRealizada = 1;
                            }
                        };break;
                        case '3': {
                            system("cls");
                            if(finalRealizada == 0){
                                erro3("FINAL");
                            }
                            else{
                                exibirPodio();
                            }
                        }break;
                        default: break;
                    }
                }while(opcao != '0');
            ;break;


            case 8:{
                do{
                    system("cls");
                    printf("\n\t**  ESTATISTICAS DA COPA  *\n\n");
                    printf(" 0 - SAIR.\n");
                    printf(" 1 - SALDO DE GOLS.\n");
                    printf(" 2 - GOLS FEITOS.\n");
                    printf(" 3 - GOLS SOFRIDOS.\n");
                    printf(" 4 - VITORIAS\n");
                    printf(" 5 - DERROTAS.\n");
                    printf(" 6 - EMPATES.\n\n");

                    do {
                        printf("OP«√O: ");
                        fflush(stdin);
                        scanf("%c", &opcao);
                    }while (opcao!='0' && opcao!='1' && opcao!='2' && opcao!= '3' && opcao!= '4' && opcao!= '5' && opcao!= '6');

                    system("cls");

                    switch(opcao){
                        case '1': {
                            OrdenarSaldo();
                            exibirTabelaGeral();
                        }break;

                        case '2': {
                            OrdenarGols();
                            exibirTabelaGeral();
                        }break;

                        case '3':{
                            OrdenarGolsSofridos();
                            exibirTabelaGeral();
                        }break;

                        case '4':{
                            OrdenarVitorias();
                            exibirTabelaGeral();
                        }break;

                        case '5':{
                            OrdenarDerrotas();
                            exibirTabelaGeral();
                        }break;

                        case '6':{
                            OrdenarEmpates();
                            exibirTabelaGeral();
                        }break;

                        default:
                        printf("OP«√O INV¡LIDA.\n\n");
                        break;
                    }

                }while(opcao != '0');
            }break;
        }

        system("cls");

    }while(opcao != 0);

    return 0;
}

void zerarVariaveis(int tamanho, DATA *FaseZerar){
     int i = 0;

    for(i = 0; i < tamanho; i++){
        FaseZerar[i].id = i;
        FaseZerar[i].pontos = 0;
        FaseZerar[i].vitorias = 0;
        FaseZerar[i].empates = 0;
        FaseZerar[i].derrotas = 0;
        FaseZerar[i].gols = 0;
        FaseZerar[i].golsSofridos = 0;
        FaseZerar[i].saldo = 0;
	}
}
//************************************************************************************************* QUAL O OBJETIVO DESSA FUN«√O?
void armazenarDadosTimes(){
    FILE *data = fopen("dadosTimes.txt", "wb");
    int i;

    for(i = 0; i < 32; i++){
		fwrite(&CadastroGrupos[i], sizeof(DATA), 1, data);
	}

	fclose(data);

    FILE *geral = fopen("dadosGerais.txt", "wb");

    for(i = 0; i < 32; i++){
		fwrite(&TabelaGeral[i], sizeof(DATA), 1, data);
	}

	fclose(geral);
}
//********************************************************************************************************************

void cadastrarTimesManual(){
    int i, o;

    printf("\t *** Cadastro Manual de Times ***\n\n");

    for(i = 0, o = 1; i < 32; i += 1, o++){
        fflush(stdin);
        printf("Informe o nome do %2.d∞ time: ", o);
        gets(CadastroGrupos[i].equipes);
    }

    armazenarDadosTimes();
    system("cls");
}

void cadastrarTimesAutomatico(){

    FILE *team = fopen("Times.txt", "rb");
    int i, len;

    for(i = 0; i < 32; i++){
        fgets(CadastroGrupos[i].equipes, 50, team);
        len = strlen(CadastroGrupos[i].equipes) - 1;
        if (CadastroGrupos[i].equipes[len] == '\n')
            CadastroGrupos[i].equipes[len] = '\0';
    }

    for(i = 0; i < 31; i++){
        len = strlen(CadastroGrupos[i].equipes) - 1;
            CadastroGrupos[i].equipes[len] = '\0';
    }

    fclose(team);
    armazenarDadosTimes();
    system("cls");
}

void cadastroPartidasAutomatico(int tamanho, PLAY *Partida, int arquivo){

    int i, len;

    if(arquivo == 1){
        FILE *group = fopen("Locais.txt", "rb");
        FILE *day = fopen("Datas.txt", "rb");
        FILE *hour = fopen("Horas.txt", "rb");

         for(i = 0; i < tamanho; i++){
            fgets(Partida[i].localJogo, 50, group);
            len = strlen(Partida[i].localJogo) - 1;
            if (Partida[i].localJogo[len] == '\n')
                Partida[i].localJogo[len] = '\0';

            fgets(Partida[i].dataJogo, 50, day);
            len = strlen(Partida[i].dataJogo) - 1;
            if (Partida[i].dataJogo[len] == '\n')
                Partida[i].dataJogo[len] = '\0';

            fgets(Partida[i].horaJogo, 50, hour);
            len = strlen(Partida[i].horaJogo) - 1;
            if (Partida[i].horaJogo[len] == '\n')
                Partida[i].horaJogo[len] = '\0';
        }

        for(i = 0; i < tamanho; i++){
            len = strlen(Partida[i].localJogo) - 1;
                Partida[i].localJogo[len] = '\0';
            len = strlen(Partida[i].dataJogo) - 1;
                Partida[i].dataJogo[len] = '\0';
            len = strlen(Partida[i].horaJogo) - 1;
                Partida[i].horaJogo[len] = '\0';
        }

        fclose(group);
        fclose(day);
        fclose(hour);
        armazenarDadosTimes();
        system("cls");
    }
    else if(arquivo == 2){
        FILE *group = fopen("LocaisOitavas.txt", "rb");
        FILE *day = fopen("DatasOitavas.txt", "rb");
        FILE *hour = fopen("HorasOitavas.txt", "rb");

         for(i = 0; i < tamanho; i++){
            fgets(Partida[i].localJogo, 50, group);
            len = strlen(Partida[i].localJogo) - 1;
            if (Partida[i].localJogo[len] == '\n')
                Partida[i].localJogo[len] = '\0';

            fgets(Partida[i].dataJogo, 50, day);
            len = strlen(Partida[i].dataJogo) - 1;
            if (Partida[i].dataJogo[len] == '\n')
                Partida[i].dataJogo[len] = '\0';

            fgets(Partida[i].horaJogo, 50, hour);
            len = strlen(Partida[i].horaJogo) - 1;
            if (Partida[i].horaJogo[len] == '\n')
                Partida[i].horaJogo[len] = '\0';
        }

        for(i = 0; i < tamanho; i++){
            len = strlen(Partida[i].localJogo) - 1;
                Partida[i].localJogo[len] = '\0';
            len = strlen(Partida[i].dataJogo) - 1;
                Partida[i].dataJogo[len] = '\0';
            len = strlen(Partida[i].horaJogo) - 1;
                Partida[i].horaJogo[len] = '\0';
        }

        fclose(group);
        fclose(day);
        fclose(hour);
        armazenarDadosTimes();
        system("cls");
    }
    else if(arquivo == 3){
        FILE *group = fopen("LocaisQuartas.txt", "rb");
        FILE *day = fopen("DatasQuartas.txt", "rb");
        FILE *hour = fopen("HorasQuartas.txt", "rb");

         for(i = 0; i < tamanho; i++){
            fgets(Partida[i].localJogo, 50, group);
            len = strlen(Partida[i].localJogo) - 1;
            if (Partida[i].localJogo[len] == '\n')
                Partida[i].localJogo[len] = '\0';

            fgets(Partida[i].dataJogo, 50, day);
            len = strlen(Partida[i].dataJogo) - 1;
            if (Partida[i].dataJogo[len] == '\n')
                Partida[i].dataJogo[len] = '\0';

            fgets(Partida[i].horaJogo, 50, hour);
            len = strlen(Partida[i].horaJogo) - 1;
            if (Partida[i].horaJogo[len] == '\n')
                Partida[i].horaJogo[len] = '\0';
        }

        for(i = 0; i < tamanho; i++){
            len = strlen(Partida[i].localJogo) - 1;
                Partida[i].localJogo[len] = '\0';
            len = strlen(Partida[i].dataJogo) - 1;
                Partida[i].dataJogo[len] = '\0';
            len = strlen(Partida[i].horaJogo) - 1;
                Partida[i].horaJogo[len] = '\0';
        }

        fclose(group);
        fclose(day);
        fclose(hour);
        armazenarDadosTimes();
        system("cls");
    }
     else if(arquivo == 4){
        FILE *group = fopen("LocaisSemifinais.txt", "rb");
        FILE *day = fopen("DatasSemifinais.txt", "rb");
        FILE *hour = fopen("HorasSemifinais.txt", "rb");

         for(i = 0; i < tamanho; i++){
            fgets(Partida[i].localJogo, 50, group);
            len = strlen(Partida[i].localJogo) - 1;
            if (Partida[i].localJogo[len] == '\n')
                Partida[i].localJogo[len] = '\0';

            fgets(Partida[i].dataJogo, 50, day);
            len = strlen(Partida[i].dataJogo) - 1;
            if (Partida[i].dataJogo[len] == '\n')
                Partida[i].dataJogo[len] = '\0';

            fgets(Partida[i].horaJogo, 50, hour);
            len = strlen(Partida[i].horaJogo) - 1;
            if (Partida[i].horaJogo[len] == '\n')
                Partida[i].horaJogo[len] = '\0';
        }

        for(i = 0; i < tamanho; i++){
            len = strlen(Partida[i].localJogo) - 1;
                Partida[i].localJogo[len] = '\0';
            len = strlen(Partida[i].dataJogo) - 1;
                Partida[i].dataJogo[len] = '\0';
            len = strlen(Partida[i].horaJogo) - 1;
                Partida[i].horaJogo[len] = '\0';
        }

        fclose(group);
        fclose(day);
        fclose(hour);
        armazenarDadosTimes();
        system("cls");
    }
    else if(arquivo == 5){
        FILE *group = fopen("LocalTerceiro.txt", "rb");
        FILE *day = fopen("DataTerceiro.txt", "rb");
        FILE *hour = fopen("HoraTerceiro.txt", "rb");

         for(i = 0; i < tamanho; i++){
            fgets(Partida[i].localJogo, 50, group);
            len = strlen(Partida[i].localJogo) - 1;
            if (Partida[i].localJogo[len] == '\n')
                Partida[i].localJogo[len] = '\0';

            fgets(Partida[i].dataJogo, 50, day);
            len = strlen(Partida[i].dataJogo) - 1;
            if (Partida[i].dataJogo[len] == '\n')
                Partida[i].dataJogo[len] = '\0';

            fgets(Partida[i].horaJogo, 50, hour);
            len = strlen(Partida[i].horaJogo) - 1;
            if (Partida[i].horaJogo[len] == '\n')
                Partida[i].horaJogo[len] = '\0';
        }

        for(i = 0; i < tamanho; i++){
            len = strlen(Partida[i].localJogo) - 1;
                Partida[i].localJogo[len] = '\0';
            len = strlen(Partida[i].dataJogo) - 1;
                Partida[i].dataJogo[len] = '\0';
            len = strlen(Partida[i].horaJogo) - 1;
                Partida[i].horaJogo[len] = '\0';
        }

        fclose(group);
        fclose(day);
        fclose(hour);
        armazenarDadosTimes();
        system("cls");
    }
    else if(arquivo == 6){
        FILE *group = fopen("LocalFinal.txt", "rb");
        FILE *day = fopen("DataFinal.txt", "rb");
        FILE *hour = fopen("HoraFinal.txt", "rb");

         for(i = 0; i < tamanho; i++){
            fgets(Partida[i].localJogo, 50, group);
            len = strlen(Partida[i].localJogo) - 1;
            if (Partida[i].localJogo[len] == '\n')
                Partida[i].localJogo[len] = '\0';

            fgets(Partida[i].dataJogo, 50, day);
            len = strlen(Partida[i].dataJogo) - 1;
            if (Partida[i].dataJogo[len] == '\n')
                Partida[i].dataJogo[len] = '\0';

            fgets(Partida[i].horaJogo, 50, hour);
            len = strlen(Partida[i].horaJogo) - 1;
            if (Partida[i].horaJogo[len] == '\n')
                Partida[i].horaJogo[len] = '\0';
        }

        for(i = 0; i < tamanho; i++){
            len = strlen(Partida[i].localJogo) - 1;
                Partida[i].localJogo[len] = '\0';
            len = strlen(Partida[i].dataJogo) - 1;
                Partida[i].dataJogo[len] = '\0';
            len = strlen(Partida[i].horaJogo) - 1;
                Partida[i].horaJogo[len] = '\0';
        }

        fclose(group);
        fclose(day);
        fclose(hour);
        armazenarDadosTimes();
        system("cls");
    }
    
    
}

void cadastroPartidasManualmente(int tamanho, PLAY *Partida, DATA *Fase){

    int i, j;

    for(i = 0, j = 0; i < tamanho; i++, j += 2){
        system("cls");
        printf( "    *** InformaÁıes das Partidas *** \n\n");
        printf("\t     --- JOGO %d --- \n",i+1);
        printf( "\n\t   %s  x  %s\n\n", Fase[j].equipes, Fase[j + 1].equipes);
        printf("DIGITE A DATA: ");
    	fflush(stdin);
    	gets(Partida[i].dataJogo);
        printf("DIGITE O HORARIO DA PARTIDA: ");
    	gets(Partida[i].horaJogo);
        printf("DIGITE O LOCAL DA PARTIDA: ");
    	fflush(stdin);
    	gets(Partida[i].localJogo);
    }

    armazenarDadosTimes();
    system("cls");
}

void exibirGrupos(){

    char grupo = 'A';
    int i, j, k = 0;

    printf("\t *** Grupos ***\n\n");

    for(i = 0; i < 32; i += 4, grupo++){
        printf( "\n<< GRUPO %c >>\n", grupo );
        for(j = 0; j <  4; j += 1, k++){
            printf(" %2d - %s\n", k + 1, CadastroGrupos[k].equipes);
        }
    }

    printf("\n\n");
    system("pause");
    system("cls");

}

void cadastroFaseDeGrupos(){

    system("cls");
    char grupo;
    int i = 0, j = 0, c = 0, k = 0, t = 0;

    grupo='A';
    k=1;
    c=0;
    for(i=0;i<8;i++,grupo++){
        for(j=0;j<2;j++){
        	strcpy (FaseGrupos[t].dataJogo, " ");
        	strcpy (FaseGrupos[t].horaJogo, " ");
        	strcpy (FaseGrupos[t].localJogo, " ");

        	printf("    *** InformaÁıes das Partidas *** \n\n");
            printf("\t  <<< GRUPO %c >>> \n",grupo);
            printf("\tRODADA 1 --- JOGO %d \n",t+1);
            printf("\n\t%s  x  %s\n\n", CadastroGrupos[c].equipes, CadastroGrupos[k].equipes);
            printf("DIGITE A DATA: ");
    		fflush(stdin);
    		gets(FaseGrupos[t].dataJogo);
            printf("DIGITE O HORARIO DA PARTIDA: ");
    		gets(FaseGrupos[t].horaJogo);
            printf("DIGITE O LOCAL DA PARTIDA: ");
    		fflush(stdin);
    		gets(FaseGrupos[t].localJogo);

            t++;
            c+=2;//
            k+=2;
            system("cls");
    	}

    }

    grupo='A';
    k=2;
    c=0;
    for(i=0;i<8;i++,grupo++){
   		if(k!=2 && c!=0){
            k+=2;
            c+=2;
        }

        for(j=0;j<2;j++){
        	strcpy (FaseGrupos[t].dataJogo, " ");
        	strcpy (FaseGrupos[t].horaJogo, " ");
        	strcpy (FaseGrupos[t].localJogo, " ");

        	printf("    *** InformaÁıes das Partidas *** \n\n");
            printf( "\t  <<< GRUPO %c >>> \n",grupo);
            printf("\tRODADA 2 --- JOGO %d \n",t+1);
            printf("\n\t%s  x  %s\n\n", CadastroGrupos[c].equipes, CadastroGrupos[k].equipes);
            printf("DIGITE A DATA: ");
    		fflush(stdin);
    		gets(FaseGrupos[t].dataJogo);
            printf("DIGITE O HORARIO DA PARTIDA: ");
    		gets(FaseGrupos[t].horaJogo);
            printf("DIGITE O LOCAL DA PARTIDA: ");
    		fflush(stdin);
    		gets(FaseGrupos[t].localJogo);

            t++;
            c++;//
            k++;
            system("cls");
    	}

    }

    grupo='A';
    k=3;
    c=0;
   	for(i=0;i<8;i++,grupo++){
   		if(c!=0 && k!=3){
            c+=2;
            k+=6;
        }

        for(j=0;j<2;j++){
        	strcpy (FaseGrupos[t].dataJogo, " "); // Limpando o lixo
        	strcpy (FaseGrupos[t].horaJogo, " "); // Limpando o lixo
        	strcpy (FaseGrupos[t].localJogo, " "); // Limpando o lixo

        	printf("    *** InformaÁıes das Partidas *** \n\n");
            printf( "\t  <<< GRUPO %c >>> \n",grupo);
            printf("\tRODADA 3 --- JOGO %d \n",t+1);
            printf("\n\t%s  x  %s\n\n", CadastroGrupos[c].equipes, CadastroGrupos[k].equipes);
            printf("DIGITE A DATA: ");
    		fflush(stdin);
    		gets(FaseGrupos[t].dataJogo);
            printf("DIGITE O HORARIO DA PARTIDA: ");
    		gets(FaseGrupos[t].horaJogo);
            printf("DIGITE O LOCAL DA PARTIDA: ");
    		fflush(stdin);
    		gets(FaseGrupos[t].localJogo);

            t++;
            c++;//
            k--;
            system("cls");
    	}

    }

    system("cls");

}

void realizarFaseDeGrupos(){
    char opcao, grupo;
    int automatico = 0, i = 0, j = 0, c = 0, k = 0, t = 0, gols1 = 0, gols2 = 0;
    for(i = 0; i < 32; i++){
        CadastroGrupos[i].id = i;
        CadastroGrupos[i].pontos = 0;
        CadastroGrupos[i].vitorias = 0;
        CadastroGrupos[i].empates = 0;
        CadastroGrupos[i].derrotas = 0;
        CadastroGrupos[i].gols = 0;
        CadastroGrupos[i].golsSofridos = 0;
        CadastroGrupos[i].saldo = 0;
	}

    printf("\n\t**** RealizaÁ„o das Partidas da Fase de Grupos ***\n");
    printf( "\n\nVOC  DESEJA INSERIR OS RESULTADOS DOS JOGOS AUTOM¡TICAMENTE OU MANUALMENTE?\n\n");
    printf(" > Tecle 1 AUTOMATICAMENTE\n > Tecle 2 MANUALMENTE\n\n");

    do {
    	printf( "OP«√O: ");
    	fflush(stdin);
    	scanf("%c", &opcao);
    }while (opcao!='1' && opcao!='2');

    if (opcao=='1'){
       automatico = 1;
       srand(time(NULL));
    }
    else if(opcao == '2'){
    	automatico = 0;
    }

    system("cls");

    grupo='A';
    k=1;
    c=0;
    t = 0;
   	for(i=0;i<8;i++,grupo++)
   	{
        for(j=0;j<2;j++)
        {
            printf ("\t      <<< GRUPO %c >>> \n\n",grupo);
            printf("\t    RODADA 1 --- JOGO %d ",t+1);
            printf( "\n\t< %s [0] x [0] %s >\n", CadastroGrupos[c].equipes, CadastroGrupos[k].equipes);
            printf("\nDIA: %s",FaseGrupos[t].dataJogo);
            printf("\nLOCAL: %s",FaseGrupos[t].localJogo);
            printf("\nHORARIO: %s\n",FaseGrupos[t].horaJogo);
            t++;

            if(automatico == 0){
	            do {
	            	printf("Insira o placar do primeiro time: ");
	                scanf("%d", &gols1);
	            }while (gols1>20 || gols1<0);

	            do {
	             	printf("Insira o placar do segundo time: ");
	                scanf("%d", &gols2);
	            }while (gols2>20 || gols2<0);

	            printf( "\n\t< %s [%d] x [%d] %s >\n", CadastroGrupos[c].equipes, gols1, gols2, CadastroGrupos[k].equipes);
                usleep(500000);
	            system("cls");
            }
            else{
            	gols1 = rand() % 7; // Sorteia os gols do time 1
            	gols2 = rand() % 7; // Sorteia os gols do time 2

            	printf( "\n\t< %s [%d] x [%d] %s >\n\n", CadastroGrupos[c].equipes, gols1, gols2, CadastroGrupos[k].equipes);
                system("pause");
	            system("cls");
            }

            //0PONTOS, 1VITORIAS, 2DERROTAS, 3EMPATES,4GOLS, 5GOLS CONTRA, 6SALDO

            if( gols1>gols2 ){
                CadastroGrupos[c].pontos += 3;//pontos
                CadastroGrupos[k].pontos += 0;//pontos
                CadastroGrupos[c].vitorias += 1;//vitorias
                CadastroGrupos[k].derrotas += 1;//derrotas
                CadastroGrupos[c].gols += gols1;
                CadastroGrupos[k].gols += gols2;
                CadastroGrupos[c].golsSofridos += gols2;
                CadastroGrupos[k].golsSofridos  += gols1;
            }
            else if(gols2>gols1){
                CadastroGrupos[k].pontos += 3;//pontos
                CadastroGrupos[c].pontos += 0;//pontos
                CadastroGrupos[k].vitorias  += 1;//vitorias
                CadastroGrupos[c].derrotas  += 1;//derrotas
                CadastroGrupos[c].gols += gols1;
                CadastroGrupos[k].gols += gols2;
                CadastroGrupos[c].golsSofridos += gols2;
                CadastroGrupos[k].golsSofridos += gols1;
            }
            else {
                CadastroGrupos[k].pontos += 1;//pontos
                CadastroGrupos[c].pontos += 1;//pontos
                CadastroGrupos[k].empates  += 1;//empate
                CadastroGrupos[c].empates  += 1;//empate
                CadastroGrupos[c].gols +=gols1;
                CadastroGrupos[k].gols +=gols2;
                CadastroGrupos[c].golsSofridos +=gols2;
                CadastroGrupos[k].golsSofridos +=gols1;
            }

        c+=2;//
        k+=2;

        }
   	}

    system("cls");
   	grupo='A';//ZERANDO A VARIAVEL GRUPO PARA CONTAR DE A ATù H NOVAMENTE
   	k=2;//RECEBE 2 O CONTADOR QUE IRù PERCORRER O LAùO ABAIXO INICIADO EM 1;
   	c=0;//ZERANDO CONTADOR QUE IRù PERCORRER O LAùO ABAIXO INICIADO EM 0;
   	for(i=0;i<8;i++,grupo++)//grupo++ grupo dentro do for responsùvel por mudar a letra do primeiro for das linhas abaixo
   	{
        if(k!=2 && c!=0)
        {
        k+=2;
        c+=2;
        }
        for(j=0;j<2;j++){
    		printf ("\t      <<< GRUPO %c >>> \n\n",grupo);
            printf("\t    RODADA 2 --- JOGO %d ",t+1);
            printf( "\n\t< %s [0] x [0] %s >\n", CadastroGrupos[c].equipes, CadastroGrupos[k].equipes);
            printf("\nDIA: %s",FaseGrupos[t].dataJogo);
            printf("\nLOCAL: %s",FaseGrupos[t].localJogo);
            printf("\nHORARIO: %s\n",FaseGrupos[t].horaJogo);
            t++;

            if(automatico == 0){
	            do {
	            	printf("Insira o placar do primeiro time: ");
	                scanf("%d", &gols1);
	            }while (gols1>20 || gols1<0);

	            do {
	             	printf("Insira o placar do segundo time: ");
	                scanf("%d", &gols2);
	            }while (gols2>20 || gols2<0);

	            printf( "\n\t< %s [%d] x [%d] %s >\n", CadastroGrupos[c].equipes, gols1, gols2, CadastroGrupos[k].equipes);
	            usleep(500000);
                system("cls");
            }
            else{
            	gols1 = rand() % 7;
            	gols2 = rand() % 7;

            	printf( "\n\t< %s [%d] x [%d] %s >\n\n", CadastroGrupos[c].equipes, gols1, gols2, CadastroGrupos[k].equipes);
                system("pause");
	            system("cls");
            }

   			if( gols1>gols2 ){
                CadastroGrupos[c].pontos += 3;//pontos
                CadastroGrupos[k].pontos += 0;//pontos
                CadastroGrupos[c].vitorias += 1;//vitorias
                CadastroGrupos[k].derrotas += 1;//derrotas
                CadastroGrupos[c].gols +=gols1;
                CadastroGrupos[k].gols +=gols2;
                CadastroGrupos[c].golsSofridos +=gols2;
                CadastroGrupos[k].golsSofridos +=gols1;
            }
            else if(gols2>gols1){
                CadastroGrupos[k].pontos += 3;//pontos
                CadastroGrupos[c].pontos += 0;//pontos
                CadastroGrupos[k].vitorias += 1;//vitorias
                CadastroGrupos[c].derrotas  += 1;//derrotas
                CadastroGrupos[c].gols +=gols1;
                CadastroGrupos[k].gols +=gols2;
                CadastroGrupos[c].golsSofridos +=gols2;
                CadastroGrupos[k].golsSofridos +=gols1;
            }
            else {
                CadastroGrupos[k].pontos += 1;//pontos
                CadastroGrupos[c].pontos += 1;//pontos
                CadastroGrupos[k].empates  += 1;//empate
                CadastroGrupos[c].empates  += 1;//empate
                CadastroGrupos[c].gols +=gols1;
                CadastroGrupos[k].gols +=gols2;
                CadastroGrupos[c].golsSofridos +=gols2;
                CadastroGrupos[k].golsSofridos +=gols1;
            }
            k++;
            c++;
        }
   }

    system("cls");

   	grupo='A';
   	c=0;
   	k=3;
   	for(i=0;i<8;i++,grupo++)
   	{
        if(c!=0 && k!=3){
        c+=2;
        k+=6;
        }
        for(j=0;j<2;j++){
            printf ("\t      <<< GRUPO %c >>> \n\n",grupo);
            printf("\t    RODADA 3 --- JOGO %d ",t+1);
            printf( "\n\t< %s [0] x [0] %s >\n", CadastroGrupos[c].equipes, CadastroGrupos[k].equipes);
            printf("\nDIA: %s",FaseGrupos[t].dataJogo);
            printf("\nLOCAL: %s",FaseGrupos[t].localJogo);
            printf("\nHORARIO: %s\n",FaseGrupos[t].horaJogo);
            t++;

            if(automatico == 0){
	            do {
	            	printf("Insira o placar do primeiro time: ");
	                scanf("%d", &gols1);
	            }while (gols1>20 || gols1<0);

	            do {
	             	printf("Insira o placar do segundo time: ");
	                scanf("%d", &gols2);
	            }while (gols2>20 || gols2<0);

	            printf( "\n\t< %s [%d] x [%d] %s >\n", CadastroGrupos[c].equipes, gols1, gols2, CadastroGrupos[k].equipes);
	            usleep(500000);
                system("cls");
            }
            else{
            	gols1 = rand() % 7;
            	gols2 = rand() % 7;

            	printf( "\n\t< %s [%d] x [%d] %s >\n\n", CadastroGrupos[c].equipes, gols1, gols2, CadastroGrupos[k].equipes);
                system("pause");
	            system("cls");
            }


          if( gols1>gols2 ){
            CadastroGrupos[c].pontos += 3;//pontos
            CadastroGrupos[k].pontos += 0;//pontos
            CadastroGrupos[c].vitorias += 1;//vitorias
            CadastroGrupos[k].derrotas += 1;//derrotas
            CadastroGrupos[c].gols +=gols1;
            CadastroGrupos[k].gols +=gols2;
            CadastroGrupos[c].golsSofridos +=gols2;
            CadastroGrupos[k].golsSofridos +=gols1;
        }
        else if(gols2>gols1){
            CadastroGrupos[k].pontos += 3;//pontos
            CadastroGrupos[c].pontos += 0;//pontos
            CadastroGrupos[k].vitorias  += 1;//vitorias
            CadastroGrupos[c].derrotas  += 1;//derrotas
            CadastroGrupos[c].gols +=gols1;
            CadastroGrupos[k].gols +=gols2;
            CadastroGrupos[c].golsSofridos +=gols2;
            CadastroGrupos[k].golsSofridos +=gols1;
        }
        else {
            CadastroGrupos[k].pontos += 1;//pontos
            CadastroGrupos[c].pontos += 1;//pontos
            CadastroGrupos[k].empates += 1;//empate
            CadastroGrupos[c].empates += 1;//empate
            CadastroGrupos[c].gols +=gols1;
            CadastroGrupos[k].gols +=gols2;
            CadastroGrupos[c].golsSofridos +=gols2;
            CadastroGrupos[k].golsSofridos +=gols1;
        }

        c++;
        k--;

        }
    }

    //PREENCHENDO SG
    for (i=0;i < 32;i++){
        CadastroGrupos[i].saldo=  CadastroGrupos[i].gols - CadastroGrupos[i].golsSofridos;
    }

    armazenarDadosTimes();
    processarJogos();
    system("cls");
}

void  ordenaGrupoDecrescente(int t1, int t2){

    int i,j,temp = 0;
    DATA temp1;

    for (  i = t1 ; i < t2   ; i ++){
        for ( j = i + 1; j < t2 ; j ++){
            if (CadastroGrupos[i].pontos  < CadastroGrupos[j].pontos ){
                temp = CadastroGrupos[i].pontos;
                temp1 = CadastroGrupos[i];
                CadastroGrupos[i].pontos = CadastroGrupos[j].pontos;
                CadastroGrupos[i] = CadastroGrupos[j];
                CadastroGrupos[j].pontos = temp;
                CadastroGrupos[j] = temp1;
            }

        }
    }
}

void  ordenaGrupoSaldo(int t3, int t4){

    int i, j, tempX;
    DATA temp2;

    for (  i = t3 ; i < t4   ; i ++){
        for ( j = i + 1; j < t4 ; j ++){
            if (CadastroGrupos[i].saldo  < CadastroGrupos[j].saldo){
                tempX = CadastroGrupos[i].saldo;
                temp2 = CadastroGrupos[i];
                CadastroGrupos[i].saldo = CadastroGrupos[j].saldo;
                CadastroGrupos[i] = CadastroGrupos[j];
                CadastroGrupos[j].saldo = tempX;
                CadastroGrupos[j] = temp2;
            }
        }
    }

}

void  ordenaGrupoGols(int t3, int t4){

    int i, j, tempX;
    DATA temp2;

    for (  i = t3 ; i < t4   ; i ++){
        for ( j = i + 1; j < t4 ; j ++){
            if (CadastroGrupos[i].gols  < CadastroGrupos[j].gols){
                tempX = CadastroGrupos[i].gols;
                temp2 = CadastroGrupos[i];
                CadastroGrupos[i].gols = CadastroGrupos[j].gols;
                CadastroGrupos[i] = CadastroGrupos[j];
                CadastroGrupos[j].gols = tempX;
                CadastroGrupos[j] = temp2;
            }
        }
    }

}

void  ordenaGrupoGolsSofridos(int t3, int t4){

    int i, j, tempX;
    DATA temp2;

    for (  i = t3 ; i < t4   ; i ++){
        for ( j = i + 1; j < t4 ; j ++){
            if (CadastroGrupos[i].golsSofridos > CadastroGrupos[j].golsSofridos){
                tempX = CadastroGrupos[i].golsSofridos;
                temp2 = CadastroGrupos[i];
                CadastroGrupos[i].golsSofridos = CadastroGrupos[j].golsSofridos;
                CadastroGrupos[i] = CadastroGrupos[j];
                CadastroGrupos[j].golsSofridos = tempX;
                CadastroGrupos[j] = temp2;
            }
        }
    }

}

void processarJogos(){
    int i = 0, j = 0;

    ordenaGrupoDecrescente(0, 4);
    ordenaGrupoDecrescente(4, 8);
    ordenaGrupoDecrescente(8, 12);
    ordenaGrupoDecrescente(12, 16);
    ordenaGrupoDecrescente(16, 20);
    ordenaGrupoDecrescente(20, 24);
    ordenaGrupoDecrescente(24, 28);
    ordenaGrupoDecrescente(28, 32);

    for(i = 0; i < 32; i +=4){
        if(CadastroGrupos[i].pontos == CadastroGrupos[i + 1].pontos == CadastroGrupos[i + 2].pontos == CadastroGrupos[i + 3].pontos){
            ordenaGrupoSaldo(i,i + 4);
        }
        else if(CadastroGrupos[i].pontos == CadastroGrupos[i + 1].pontos == CadastroGrupos[i + 2].pontos){
            ordenaGrupoSaldo(i, i + 3);

            if(CadastroGrupos[i].saldo == CadastroGrupos[i + 1].saldo == CadastroGrupos[i + 2].saldo){
                ordenaGrupoGols(i, i + 3);

                if(CadastroGrupos[i].gols == CadastroGrupos[i + 1].gols == CadastroGrupos[i + 2].gols){
                    ordenaGrupoGolsSofridos(i, i + 3);
                }
                else if(CadastroGrupos[i].gols == CadastroGrupos[i + 1].gols){
                    ordenaGrupoGolsSofridos(i, i + 2);
                }
                else if(CadastroGrupos[i + 1].gols == CadastroGrupos[i + 2].gols){
                    ordenaGrupoGolsSofridos(i + 1, i + 3);
                }

            }
            else if(CadastroGrupos[i].saldo == CadastroGrupos[i + 1].saldo){
                ordenaGrupoGols(i, i + 2);

                if(CadastroGrupos[i].gols == CadastroGrupos[i + 1].gols){
                    ordenaGrupoGolsSofridos(i, i + 2);
                }

            }
            else if(CadastroGrupos[i + 1].saldo == CadastroGrupos[i + 2].saldo){
                ordenaGrupoGols(i + 1, i + 3);

                if(CadastroGrupos[i + 1].gols == CadastroGrupos[i + 2].gols){
                    ordenaGrupoGolsSofridos(i + 1, i + 3);
                }

            }

        }
        else if(CadastroGrupos[i + 1].pontos == CadastroGrupos[i + 2].pontos == CadastroGrupos[i + 3].pontos){
            ordenaGrupoSaldo(i + 1, i + 4);

            if(CadastroGrupos[i + 1].saldo == CadastroGrupos[i + 2].saldo == CadastroGrupos[i + 3].saldo){
                ordenaGrupoGols(i + 1, i + 4);
            }
            else if(CadastroGrupos[i + 1].saldo == CadastroGrupos[i + 2].saldo){
                ordenaGrupoGols(i + 1, i + 3);
            }
            else if(CadastroGrupos[i + 2].saldo == CadastroGrupos[i + 3].saldo){
                ordenaGrupoGols(i + 2, i + 4);
            }

        }
        else if(CadastroGrupos[i + 1].pontos == CadastroGrupos[i + 2].pontos){
            ordenaGrupoSaldo(i + 1, i + 3);
            if(CadastroGrupos[i + 1].saldo == CadastroGrupos[i + 2].saldo){
                ordenaGrupoGols(i + 1, i + 3);

                if(CadastroGrupos[i + 1].gols == CadastroGrupos[i + 2].gols){
                    ordenaGrupoGolsSofridos(i + 1, i + 3);
                }

            }
        }
        else{
            if(CadastroGrupos[i].pontos == CadastroGrupos[i + 1].pontos){
                ordenaGrupoSaldo(i, i + 2);
                if(CadastroGrupos[i].saldo == CadastroGrupos[i + 1].saldo){
                    ordenaGrupoGols(i, i + 2);

                    if(CadastroGrupos[i].gols == CadastroGrupos[i + 1].gols){
                        ordenaGrupoGolsSofridos(i, i + 2);
                    }

                }
            }
            if(CadastroGrupos[i + 2].pontos == CadastroGrupos[i + 3].pontos){
                ordenaGrupoSaldo(i + 2, i + 4);
                if(CadastroGrupos[i + 2].saldo == CadastroGrupos[i + 3].saldo){
                    ordenaGrupoGols(i + 2, i + 4);

                    if(CadastroGrupos[i + 2].gols == CadastroGrupos[i + 3].gols){
                        ordenaGrupoGolsSofridos(i + 2, i + 4);
                    }

                }
            }
        }
    }

    for(i = 0; i <= 32; i += 1){
      	TabelaGeral[i] = CadastroGrupos[i];
    }

    armazenarDadosTimes();

    for(i = 0; i < 32; i += 8){
        Oitavas[j] = CadastroGrupos[i];
        j++;
        Oitavas[j] = CadastroGrupos[i + 5];
        j++;
        Oitavas[j] = CadastroGrupos[i + 4];
        j++;
        Oitavas[j] = CadastroGrupos[i + 1];
        j++;
    }

}

void exibirTabelaGrupos(){
    system("cls");
    int i, j;
    char grupo = 'A';

    printf("+------------------+-------+--------+-------+-------+-------+-------+-------+\n");
    printf("|                        .::Tabela ClassificatÛria::.                       |\n");
    printf("+------------------+-------+--------+-------+-------+-------+-------+-------+\n");

    for(j = 0; j < 32; j += 4, grupo++){
        printf("|                             .::GRUPO %c::.                                 |\n", grupo);
        printf("+------------------+-------+--------+-------+-------+-------+-------+-------+\n");
        printf("|       TIME       |   P   |   SG   |   G+  |   G-  |   V   |   D   |   E   |\n");
        printf("+------------------+-------+--------+-------+-------+-------+-------+-------+\n");

        for(i = j; i < j + 4; i += 1){
            printf("|  %-15s |   %2d  |   %2d   |   %2d  |   %2d  |   %2d  |   %2d  |   %2d  |\n", CadastroGrupos[i].equipes, CadastroGrupos[i].pontos, CadastroGrupos[i].saldo, CadastroGrupos[i].gols, CadastroGrupos[i].golsSofridos, CadastroGrupos[i].vitorias, CadastroGrupos[i].derrotas, CadastroGrupos[i].empates);
            printf("+------------------+-------+--------+-------+-------+-------+-------+-------+\n");
        }
    }

    printf("\n\n");
    system("pause");
}

void classificados(int quantidade, DATA *Classificados){
    int i;

    printf ("\t<<< TIMES CLASSIFICADOS >>>\n\n");
    for(i = 0; i < quantidade; i++){
        printf("%2d - %s\n", i + 1, Classificados[i].equipes);
    }

    printf("\n");
    system("pause");
}

void realizarOitavas(){
    int i, j = 0;
    int numJogo = 1;
    int penaltes1, penaltes2;
    zerarVariaveis(16, Oitavas);

    for(i = 0, j = 0; i < 16; i += 2, numJogo++){

        char opcao;

        do{
        	system("cls");
         	system("color 0F");
            printf( "\t*** REALIZAR JOGOS - OITAVAS DE FINAL ***\n");
            printf("\n\t\t  --- JOGO %d --- \n", numJogo );
            printf( "\n\t< %s [%d] x [%d] %s >\n",Oitavas[i].equipes, Oitavas[i].gols, Oitavas[i + 1].gols, Oitavas[i + 1].equipes);
            printf("\nDIA: %s",PartidasOitavas[numJogo - 1].dataJogo);
            printf("\nLOCAL: %s",PartidasOitavas[numJogo - 1].localJogo);
            printf("\nHORARIO: %s\n",PartidasOitavas[numJogo - 1].horaJogo);

            printf("\n  -> Gols do(a) %s: ", strupr(Oitavas[i].equipes));
            fflush(stdin);
            scanf("%d", &Oitavas[i].gols);
            printf("  -> Gols do(a) %s: ", strupr(Oitavas[i + 1].equipes));
            fflush(stdin);
            scanf("%d", &Oitavas[i + 1].gols);

           printf( "\n\t< %s [%d] x [%d] %s >\n",Oitavas[i].equipes, Oitavas[i].gols, Oitavas[i + 1].gols, Oitavas[i + 1].equipes);

            printf( "\n  + Atualizar o placar - digite A.");
            printf( "\n  = Ir para o prÛximo jogo ou decis„o por pÍnaltis - digite I.\n");
            printf( "\n  ---> ");
            fflush(stdin);
            scanf("%c", &opcao);

            if(opcao != 'I' && opcao != 'i'){
               system("color C");
               system("cls");
         	}

    	}while(opcao != 'I' && opcao != 'i');

        if((Oitavas[i].gols) >  (Oitavas[i + 1].gols)){
            Quartas[j] = Oitavas[i];
            Oitavas[i].vitorias = 1;
            Oitavas[i + 1].derrotas = 1;
            Oitavas[i].golsSofridos = Oitavas[i + 1].gols;
            Oitavas[i + 1].golsSofridos = Oitavas[i].gols;
            Oitavas[i].saldo = Oitavas[i].gols -  Oitavas[i + 1].gols;
            Oitavas[i + 1].saldo = Oitavas[i + 1].gols -  Oitavas[i].gols;
            j++;
            printf( "\n    >>> O(A) %s FOI CLASSIFICADO(A) <<<\n", strupr(Oitavas[i].equipes));
            printf("\n");
            system("pause");
            system("cls");
        }
        else if((Oitavas[i + 1].gols) >  (Oitavas[i].gols)){
            Quartas[j] = Oitavas[i + 1];
            Oitavas[i + 1].vitorias = 1;
            Oitavas[i].derrotas = 1;
            Oitavas[i].golsSofridos = Oitavas[i + 1].gols;
            Oitavas[i + 1].golsSofridos = Oitavas[i].gols;
            Oitavas[i].saldo = Oitavas[i].gols -  Oitavas[i + 1].gols;
            Oitavas[i + 1].saldo = Oitavas[i + 1].gols -  Oitavas[i].gols;
            j++;
            printf( "\n    >>> O(A) %s FOI CLASSIFICADO(A) <<<\n", strupr(Oitavas[i + 1].equipes));
            printf("\n");
            system("pause");
            system("cls");
        }
        else {
            system("color 0F");
            system("cls");
            penaltes1 = 0;
            penaltes2 = 0;

        	do{
               system("cls");
                system("color 0F");
                printf("\t  *** DISPUTA POR P NALTES ***\n");
                printf("\n\t\t--- JOGO %d --- \n", numJogo );
                printf( "\n\t< %s [%d] x [%d] %s >\n",Oitavas[i].equipes, penaltes1, penaltes2, Oitavas[i + 1].equipes);

                printf("\n  -> PÍnaltis convertidos pelo(a) %s: ", strupr(Oitavas[i].equipes));
                fflush(stdin);
                scanf("%d", &penaltes1);
                printf("  -> Penaltis convertidos pelo(a) %s: ", strupr(Oitavas[i + 1].equipes));
                fflush(stdin);
                scanf("%d", &penaltes2);

                printf( "\n\t< %s [%d] x [%d] %s >\n",Oitavas[i].equipes, penaltes1, penaltes2, Oitavas[i + 1].equipes);

                printf("\n  + Atualizar o placar - digite A.");
                printf( "\n  = CobranÁa de PÍnaltis ConcluÌda - digite S.\n");
                printf( "\n  ---> ");
                fflush(stdin);
                scanf("%c", &opcao);

                if(opcao != 'S' && opcao != 's'){
                    system("color C");
                    system("cls");
                }

         	}while(opcao != 'S' && opcao != 's' || penaltes1 == penaltes2 );

            if((penaltes1) >  (penaltes2)){
                Quartas[j] = Oitavas[i];
                Oitavas[i].vitorias = 1;
                Oitavas[i + 1].derrotas = 1;
                Oitavas[i].golsSofridos = Oitavas[i + 1].gols;
                Oitavas[i + 1].golsSofridos = Oitavas[i].gols;
                Oitavas[i].saldo = Oitavas[i].gols -  Oitavas[i + 1].gols;
                Oitavas[i + 1].saldo = Oitavas[i + 1].gols -  Oitavas[i].gols;
                j++;

                printf( "\n    >>> O(A) %s FOI CLASSIFICADO(A) <<<\n", strupr(Oitavas[i].equipes));
                printf("\n");
                system("pause");
                system("cls");
            }
            else if((penaltes2) >  (penaltes1)){
                Quartas[j] = Oitavas[i + 1];
                Oitavas[i + 1].vitorias = 1;
                Oitavas[i].derrotas = 1;
                Oitavas[i].golsSofridos = Oitavas[i + 1].gols;
                Oitavas[i + 1].golsSofridos = Oitavas[i].gols;
                Oitavas[i].saldo = Oitavas[i].gols -  Oitavas[i + 1].gols;
                Oitavas[i + 1].saldo = Oitavas[i + 1].gols -  Oitavas[i].gols;
                j++;

                printf( "\n> O(A) %s FOI CLASSIFICADO(A) <\n", strupr(Oitavas[i + 1].equipes));
                printf("\n");
                system("pause");
                system("cls");
            }
        }

        system("color 0F");
        system("cls");

    }

    for(i = 0; i < 16; i++){
        TIMES[Oitavas[i].id].saldo += Oitavas[i].saldo;
        TIMES[Oitavas[i].id].gols += Oitavas[i].gols;
        TIMES[Oitavas[i].id].golsSofridos += Oitavas[i].golsSofridos;
        TIMES[Oitavas[i].id].vitorias += Oitavas[i].vitorias;
        TIMES[Oitavas[i].id].derrotas += Oitavas[i].derrotas;
        TIMES[Oitavas[i].id].empates += Oitavas[i].empates;
    }
    

}

void realizarQuartas(){
    int i, j = 0;
    int numJogo = 1;
    int penaltes1, penaltes2;
    zerarVariaveis(8, Quartas);

    for(i = 0, j = 0; i < 8; i += 2, numJogo++){

        char opcao;

        do{
        	system("cls");
         	system("color 0F");
            printf( "\t*** REALIZAR JOGOS - QUARTAS DE FINAL ***\n");
            printf("\n\t\t  --- JOGO %d --- \n", numJogo );
            printf( "\n\t< %s [%d] x [%d] %s >\n",Quartas[i].equipes, Quartas[i].gols, Quartas[i + 1].gols, Quartas[i + 1].equipes);
            printf("\nDIA: %s",PartidasQuartas[numJogo - 1].dataJogo);
            printf("\nLOCAL: %s",PartidasQuartas[numJogo - 1].localJogo);
            printf("\nHORARIO: %s\n",PartidasQuartas[numJogo - 1].horaJogo);

            printf("\n  -> Gols do(a) %s: ", strupr(Quartas[i].equipes));
            fflush(stdin);
            scanf("%d", &Quartas[i].gols);
            printf("  -> Gols do(a) %s: ", strupr(Quartas[i + 1].equipes));
            fflush(stdin);
            scanf("%d", &Quartas[i + 1].gols);

           printf( "\n\t< %s [%d] x [%d] %s >\n",Quartas[i].equipes, Quartas[i].gols, Quartas[i + 1].gols, Quartas[i + 1].equipes);

            printf( "\n  + Atualizar o placar - digite A.");
            printf( "\n  = Ir para o prÛximo jogo ou decis„o por pÍnaltis - digite I.\n");
            printf( "\n  ---> ");
            fflush(stdin);
            scanf("%c", &opcao);

            if(opcao != 'I' && opcao != 'i'){
               system("color C");
               system("cls");
         	}

    	}while(opcao != 'I' && opcao != 'i');

        if((Quartas[i].gols) >  (Quartas[i + 1].gols)){
            Semifinais[j] = Quartas[i];
            j++;
            printf( "\n    >>> O(A) %s FOI CLASSIFICADO(A) <<<\n", strupr(Quartas[i].equipes));
            printf("\n");
            system("pause");
            system("cls");
        }
        else if((Quartas[i + 1].gols) >  (Quartas[i].gols)){
            Semifinais[j] = Quartas[i + 1];
            j++;
            printf( "\n    >>> O(A) %s FOI CLASSIFICADO(A) <<<\n", strupr(Quartas[i + 1].equipes));
            printf("\n");
            system("pause");
            system("cls");
        }
        else {
            system("color 0F");
            system("cls");
            penaltes1 = 0;
            penaltes2 = 0;

        	do{
               system("cls");
                system("color 0F");
                printf("\t  *** DISPUTA POR P NALTES ***\n");
                printf("\n\t\t--- JOGO %d --- \n", numJogo );
                printf( "\n\t< %s [%d] x [%d] %s >\n",Quartas[i].equipes, penaltes1, penaltes2, Quartas[i + 1].equipes);

                printf("\n  -> PÍnaltis convertidos pelo(a) %s: ", strupr(Quartas[i].equipes));
                fflush(stdin);
                scanf("%d", &penaltes1);
                printf("  -> Penaltis convertidos pelo(a) %s: ", strupr(Quartas[i + 1].equipes));
                fflush(stdin);
                scanf("%d", &penaltes2);

                printf( "\n\t< %s [%d] x [%d] %s >\n",Quartas[i].equipes, penaltes1, penaltes2, Quartas[i + 1].equipes);

                printf("\n  + Atualizar o placar - digite A.");
                printf( "\n  = CobranÁa de PÍnaltis ConcluÌda - digite S.\n");
                printf( "\n  ---> ");
                fflush(stdin);
                scanf("%c", &opcao);

                if(opcao != 'S' && opcao != 's'){
                    system("color C");
                    system("cls");
                }

         	}while(opcao != 'S' && opcao != 's' || penaltes1 == penaltes2 );

            if((penaltes1) >  (penaltes2)){
                Semifinais[j] = Quartas[i];
                j++;

                printf( "\n    >>> O(A) %s FOI CLASSIFICADO(A) <<<\n", strupr(Quartas[i].equipes));
                printf("\n");
                system("pause");
                system("cls");
            }
            else if((penaltes2) >  (penaltes1)){
                Semifinais[j] = Quartas[i + 1];
                j++;

                printf( "\n> O(A) %s FOI CLASSIFICADO(A) <\n", strupr(Quartas[i + 1].equipes));
                printf("\n");
                system("pause");
                system("cls");
            }
        }

        system("color 0F");
        system("cls");

    }

}

void realizarSemifinais(){
    int i, j = 0;
    int numJogo = 1;
    int penaltes1, penaltes2;
    zerarVariaveis(4, Semifinais);

    for(i = 0, j = 0; i < 4; i += 2, numJogo++){

        char opcao;

        do{
        	system("cls");
         	system("color 0F");
            printf( "\t*** REALIZAR JOGOS - SEMIFINAIS ***\n");
            printf("\n\t\t  --- JOGO %d --- \n", numJogo );
            printf( "\n\t< %s [%d] x [%d] %s >\n",Semifinais[i].equipes, Semifinais[i].gols, Semifinais[i + 1].gols, Semifinais[i + 1].equipes);
            printf("\nDIA: %s",PartidasSemifinais[numJogo - 1].dataJogo);
            printf("\nLOCAL: %s",PartidasSemifinais[numJogo - 1].localJogo);
            printf("\nHORARIO: %s\n",PartidasSemifinais[numJogo - 1].horaJogo);

            printf("\n  -> Gols do(a) %s: ", strupr(Semifinais[i].equipes));
            fflush(stdin);
            scanf("%d", &Semifinais[i].gols);
            printf("  -> Gols do(a) %s: ", strupr(Semifinais[i + 1].equipes));
            fflush(stdin);
            scanf("%d", &Semifinais[i + 1].gols);

           printf( "\n\t< %s [%d] x [%d] %s >\n",Semifinais[i].equipes, Semifinais[i].gols, Semifinais[i + 1].gols, Semifinais[i + 1].equipes);

            printf( "\n  + Atualizar o placar - digite A.");
            printf( "\n  = Ir para o prÛximo jogo ou decis„o por pÍnaltis - digite I.\n");
            printf( "\n  ---> ");
            fflush(stdin);
            scanf("%c", &opcao);

            if(opcao != 'I' && opcao != 'i'){
               system("color C");
               system("cls");
         	}

    	}while(opcao != 'I' && opcao != 'i');

        if((Semifinais[i].gols) >  (Semifinais[i + 1].gols)){
            Final[j] = Semifinais[i];
            DisputaTerceiro[j] = Semifinais[i + 1];
            j++;
            printf( "\n    >>> O(A) %s … FINALISTA <<<\n", strupr(Semifinais[i].equipes));
            printf("\n");
            system("pause");
            system("cls");
        }
        else if((Semifinais[i + 1].gols) >  (Semifinais[i].gols)){
            Final[j] = Semifinais[i + 1];
            DisputaTerceiro[j] = Semifinais[i];
            j++;
            printf( "\n    >>> O(A) %s … FINALISTA <<<\n", strupr(Semifinais[i + 1].equipes));
            printf("\n");
            system("pause");
            system("cls");
        }
        else {
            system("color 0F");
            system("cls");
            penaltes1 = 0;
            penaltes2 = 0;

        	do{
               system("cls");
                system("color 0F");
                printf("\t  *** DISPUTA POR P NALTES ***\n");
                printf("\n\t\t--- JOGO %d --- \n", numJogo );
                printf( "\n\t< %s [%d] x [%d] %s >\n",Semifinais[i].equipes, penaltes1, penaltes2, Semifinais[i + 1].equipes);

                printf("\n  -> PÍnaltis convertidos pelo(a) %s: ", strupr(Semifinais[i].equipes));
                fflush(stdin);
                scanf("%d", &penaltes1);
                printf("  -> Penaltis convertidos pelo(a) %s: ", strupr(Semifinais[i + 1].equipes));
                fflush(stdin);
                scanf("%d", &penaltes2);

                printf( "\n\t< %s [%d] x [%d] %s >\n",Semifinais[i].equipes, penaltes1, penaltes2, Semifinais[i + 1].equipes);

                printf("\n  + Atualizar o placar - digite A.");
                printf( "\n  = CobranÁa de PÍnaltis ConcluÌda - digite S.\n");
                printf( "\n  ---> ");
                fflush(stdin);
                scanf("%c", &opcao);

                if(opcao != 'S' && opcao != 's'){
                    system("color C");
                    system("cls");
                }

         	}while(opcao != 'S' && opcao != 's' || penaltes1 == penaltes2 );

            if((penaltes1) >  (penaltes2)){
                Final[j] = Semifinais[i];
                DisputaTerceiro[j] = Semifinais[i + 1];
                j++;

                printf( "\n    >>> O(A) %s … FINALISTA <<<\n", strupr(Semifinais[i].equipes));
                printf("\n");
                system("pause");
                system("cls");
            }
            else if((penaltes2) >  (penaltes1)){
                Final[j] = Semifinais[i + 1];
                DisputaTerceiro[j] = Semifinais[i];
                j++;

                printf( "\n> O(A) %s … FINALISTA <\n", strupr(Semifinais[i + 1].equipes));
                printf("\n");
                system("pause");
                system("cls");
            }
        }

        system("color 0F");
        system("cls");

    }

}

void realizarDisputaTerceiro(){
    int i, j = 0;
    int numJogo = 1;
    int penaltes1, penaltes2;
    zerarVariaveis(2, DisputaTerceiro);

    for(i = 0, j = 0; i < 2; i += 2, numJogo++){

        char opcao;

        do{
        	system("cls");
         	system("color 0F");
            printf( "\t*** REALIZAR JOGO - DISPUTA PELO 3∞ LUGAR ***\n");
            printf("\n\t\t  --- JOGO %d --- \n", numJogo );
            printf( "\n\t< %s [%d] x [%d] %s >\n",DisputaTerceiro[i].equipes, DisputaTerceiro[i].gols, DisputaTerceiro[i + 1].gols, DisputaTerceiro[i + 1].equipes);
            printf("\nDIA: %s",PartidaTerceiro[numJogo - 1].dataJogo);
            printf("\nLOCAL: %s",PartidaTerceiro[numJogo - 1].localJogo);
            printf("\nHORARIO: %s\n",PartidaTerceiro[numJogo - 1].horaJogo);

            printf("\n  -> Gols do(a) %s: ", strupr(DisputaTerceiro[i].equipes));
            fflush(stdin);
            scanf("%d", &DisputaTerceiro[i].gols);
            printf("  -> Gols do(a) %s: ", strupr(DisputaTerceiro[i + 1].equipes));
            fflush(stdin);
            scanf("%d", &DisputaTerceiro[i + 1].gols);

           printf( "\n\t< %s [%d] x [%d] %s >\n",DisputaTerceiro[i].equipes, DisputaTerceiro[i].gols, DisputaTerceiro[i + 1].gols, DisputaTerceiro[i + 1].equipes);

            printf( "\n  + Atualizar o placar - digite A.");
            printf( "\n  = Ir para o prÛximo jogo ou decis„o por pÍnaltis - digite I.\n");
            printf( "\n  ---> ");
            fflush(stdin);
            scanf("%c", &opcao);

            if(opcao != 'I' && opcao != 'i'){
               system("color C");
               system("cls");
         	}

    	}while(opcao != 'I' && opcao != 'i');

        if((DisputaTerceiro[i].gols) >  (DisputaTerceiro[i + 1].gols)){
            Podio[2] = DisputaTerceiro[i];
            j++;

            printf( "\n    >>> O(A) TERCEIRO(A) COLOCADO(A) … O(A) %s <<<\n", strupr(DisputaTerceiro[i].equipes));
            printf("\n");
            system("pause");
            system("cls");
        }
        else if((DisputaTerceiro[i + 1].gols) >  (DisputaTerceiro[i].gols)){
            Podio[2] = DisputaTerceiro[i + 1];
            j++;

            printf( "\n    >>> O(A) TERCEIRO(A) COLOCADO(A) … O(A) %s <<<\n", strupr(DisputaTerceiro[i + 1].equipes));
            printf("\n");
            system("pause");
            system("cls");
        }
        else {
            system("color 0F");
            system("cls");
            penaltes1 = 0;
            penaltes2 = 0;

        	do{
               system("cls");
                system("color 0F");
                printf("\t  *** DISPUTA POR P NALTES ***\n");
                printf("\n\t\t--- JOGO %d --- \n", numJogo );
                printf( "\n\t< %s [%d] x [%d] %s >\n",DisputaTerceiro[i].equipes, penaltes1, penaltes2, DisputaTerceiro[i + 1].equipes);

                printf("\n  -> PÍnaltis convertidos pelo(a) %s: ", strupr(DisputaTerceiro[i].equipes));
                fflush(stdin);
                scanf("%d", &penaltes1);
                printf("  -> Penaltis convertidos pelo(a) %s: ", strupr(DisputaTerceiro[i + 1].equipes));
                fflush(stdin);
                scanf("%d", &penaltes2);

                printf( "\n\t< %s [%d] x [%d] %s >\n",DisputaTerceiro[i].equipes, penaltes1, penaltes2, DisputaTerceiro[i + 1].equipes);

                printf("\n  + Atualizar o placar - digite A.");
                printf( "\n  = CobranÁa de PÍnaltis ConcluÌda - digite S.\n");
                printf( "\n  ---> ");
                fflush(stdin);
                scanf("%c", &opcao);

                if(opcao != 'S' && opcao != 's'){
                    system("color C");
                    system("cls");
                }

         	}while(opcao != 'S' && opcao != 's' || penaltes1 == penaltes2 );

            if((penaltes1) >  (penaltes2)){
                Podio[2] = DisputaTerceiro[i];
                j++;

                printf( "\n    >>> O(A) TERCEIRO(A) COLOCADO(A) … O(A) %s <<<\n", strupr(DisputaTerceiro[i].equipes));
                printf("\n");
                system("pause");
                system("cls");
            }
            else if((penaltes2) >  (penaltes1)){
                Podio[2] = DisputaTerceiro[i + 1];
                j++;

                printf( "\n    >>> O(A) TERCEIRO(A) COLOCADO(A) … O(A) %s <<<\n", strupr(DisputaTerceiro[i + 1].equipes));
                printf("\n");
                system("pause");
                system("cls");
            }
        }

        system("color 0F");
        system("cls");

    }

}

void realizarFinal(){
    int i, j = 0;
    int numJogo = 1;
    int penaltes1, penaltes2;
    zerarVariaveis(2, Final);

    for(i = 0, j = 0; i < 2; i += 2, numJogo++){

        char opcao;

        do{
        	system("cls");
         	system("color 0F");
            printf( "\t*** REALIZAR JOGO - FINAL ***\n");
            printf("\n\t\t  --- JOGO %d --- \n", numJogo );
            printf( "\n\t< %s [%d] x [%d] %s >\n",Final[i].equipes, Final[i].gols, Final[i + 1].gols, Final[i + 1].equipes);
            printf("\nDIA: %s",PartidaFinal[numJogo - 1].dataJogo);
            printf("\nLOCAL: %s",PartidaFinal[numJogo - 1].localJogo);
            printf("\nHORARIO: %s\n",PartidaFinal[numJogo - 1].horaJogo);

            printf("\n  -> Gols do(a) %s: ", strupr(Final[i].equipes));
            fflush(stdin);
            scanf("%d", &Final[i].gols);
            printf("  -> Gols do(a) %s: ", strupr(Final[i + 1].equipes));
            fflush(stdin);
            scanf("%d", &Final[i + 1].gols);

           printf( "\n\t< %s [%d] x [%d] %s >\n",Final[i].equipes, Final[i].gols, Final[i + 1].gols, Final[i + 1].equipes);

            printf( "\n  + Atualizar o placar - digite A.");
            printf( "\n  = Ir para o prÛximo jogo ou decis„o por pÍnaltis - digite I.\n");
            printf( "\n  ---> ");
            fflush(stdin);
            scanf("%c", &opcao);

            if(opcao != 'I' && opcao != 'i'){
               system("color C");
               system("cls");
         	}

    	}while(opcao != 'I' && opcao != 'i');

        if((Final[i].gols) >  (Final[i + 1].gols)){
            Podio[j] = Final[i];
            j++;
            Podio[j] = Final[i + 1];

            printf( "\n    >>> A SELE«√O CAMPE√ … O(A) %s <<<\n", strupr(Final[i].equipes));
            printf("\n");
            system("pause");
            system("cls");
        }
        else if((Final[i + 1].gols) >  (Final[i].gols)){
            Podio[j] = Final[i + 1];
            j++;
            Podio[j] = Final[i];

            printf( "\n    >>> A SELE«√O CAMPE√ … O(A) %s <<<\n", strupr(Final[i + 1].equipes));
            printf("\n");
            system("pause");
            system("cls");
        }
        else {
            system("color 0F");
            system("cls");
            penaltes1 = 0;
            penaltes2 = 0;

        	do{
               system("cls");
                system("color 0F");
                printf("\t  *** DISPUTA POR P NALTES ***\n");
                printf("\n\t\t--- JOGO %d --- \n", numJogo );
                printf( "\n\t< %s [%d] x [%d] %s >\n",Final[i].equipes, penaltes1, penaltes2, Final[i + 1].equipes);

                printf("\n  -> PÍnaltis convertidos pelo(a) %s: ", strupr(Final[i].equipes));
                fflush(stdin);
                scanf("%d", &penaltes1);
                printf("  -> Penaltis convertidos pelo(a) %s: ", strupr(Final[i + 1].equipes));
                fflush(stdin);
                scanf("%d", &penaltes2);

                printf( "\n\t< %s [%d] x [%d] %s >\n",Final[i].equipes, penaltes1, penaltes2, Final[i + 1].equipes);

                printf("\n  + Atualizar o placar - digite A.");
                printf( "\n  = CobranÁa de PÍnaltis ConcluÌda - digite S.\n");
                printf( "\n  ---> ");
                fflush(stdin);
                scanf("%c", &opcao);

                if(opcao != 'S' && opcao != 's'){
                    system("color C");
                    system("cls");
                }

         	}while(opcao != 'S' && opcao != 's' || penaltes1 == penaltes2 );

            if((penaltes1) >  (penaltes2)){
                Podio[j] = Final[i];
                j++;
                Podio[j] = Final[i + 1];

                printf( "\n    >>> A SELE«√O CAMPE√ … O(A) %s <<<\n", strupr(Final[i].equipes));
                printf("\n");
                system("pause");
                system("cls");
            }
            else if((penaltes2) >  (penaltes1)){
                Podio[j] = Final[i + 1];
                j++;
                Podio[j] = Final[i];

                printf( "\n    >>> A SELE«√O CAMPE√ … O(A) %s <<<\n", strupr(Final[i + 1].equipes));
                printf("\n");
                system("pause");
                system("cls");
            }
        }

        system("color 0F");
        system("cls");

    }

}

void exibirPodio(){

    printf ("\t<<< P”DIO DA COPA >>>\n\n");
    printf( " -> SELE«√O CAMPE√: %s\n", Podio[0].equipes);
    printf( " -> SELE«√O VICE-CAMPE√: %s\n", Podio[1].equipes);
    printf( " -> SELE«√O TERCEIRA-COLOCADA: %s\n", Podio[2].equipes);

    printf("\n");
    system("pause");
}

void armazenarTabelaGeral(int tamanho, DATA *Fase){
    int i;

    for(i = 0; i < tamanho; i++){
        TIMES[Fase[i].id].saldo += Fase[i].saldo;
        TIMES[Fase[i].id].gols += Fase[i].gols;
        TIMES[Fase[i].id].golsSofridos += Fase[i].golsSofridos;
        TIMES[Fase[i].id].vitorias += Fase[i].vitorias;
        TIMES[Fase[i].id].derrotas += Fase[i].derrotas;
        TIMES[Fase[i].id].empates += Fase[i].empates;
    }
}

void PreencherCopia()
{
    int i;
    int j;

    for(i=0;i<32;i++)
        {
            strcpy(TIMES[i].equipes,CadastroGrupos[i].equipes);
            TIMES[i].derrotas+=CadastroGrupos[i].derrotas;
            TIMES[i].empates+=CadastroGrupos[i].empates;
            TIMES[i].gols+=CadastroGrupos[i].gols;
            TIMES[i].golsSofridos+=CadastroGrupos[i].golsSofridos;
            TIMES[i].id = CadastroGrupos[i].id;
            TIMES[i].pontos+=CadastroGrupos[i].pontos;
            TIMES[i].saldo+=CadastroGrupos[i].saldo;
            TIMES[i].vitorias+=CadastroGrupos[i].vitorias;
        }
}

void OrdenarSaldo(){
        int i;
        int j;
                for(i=0;i<32;i++)
                {
                    for(j=i+1;j<32;j++)
                    {
                        if(TIMES[i].saldo<TIMES[j].saldo)
                        {
                        TIMES[32] = TIMES[i];
                        TIMES[i]=TIMES[j];
                        TIMES[j]=TIMES[32];
                        }

                    }
                }

}

void OrdenarGols(){
        int i;
        int j;
            for(i=0;i<32;i++)
                {
                    for(j=i+1;j<32;j++)
                    {
                        if(TIMES[i].gols<TIMES[j].gols)
                        {
                        TIMES[32] = TIMES[i];
                        TIMES[i]=TIMES[j];
                        TIMES[j]=TIMES[32];
                        }
                    }
                }
}


void OrdenarGolsSofridos(){
        int i;
        int j;
            for(i=0;i<32;i++)
            {
                for(j=i+1;j<32;j++)
                {
                    if(TIMES[i].golsSofridos<TIMES[j].golsSofridos)
                    {
                    TIMES[32] = TIMES[i];
                    TIMES[i]=TIMES[j];
                    TIMES[j]=TIMES[32];
                    }

                }
            }
}

void OrdenarVitorias()
        {
        int i;
        int j;
            for(i=0;i<32;i++)
            {
                for(j=i+1;j<32;j++)
                {
                    if(TIMES[i].vitorias<TIMES[j].vitorias)
                    {
                    TIMES[33] = TIMES[i];
                    TIMES[i]=TIMES[j];
                    TIMES[j]=TIMES[33];
                    }
                }
            }
}

void OrdenarDerrotas(){
    int i;
    int j;
            for(i=0;i<32;i++)
            {
                for(j=i+1;j<32;j++)
                {
                    if(TIMES[i].derrotas<TIMES[j].derrotas)
                    {
                    TIMES[32] = TIMES[i];
                    TIMES[i]=TIMES[j];
                    TIMES[j]=TIMES[32];
                    }
                }
            }
}

void OrdenarEmpates(){
    int i;
    int j;
            for(i=0;i<32;i++)
            {
                for(j=i+1;j<32;j++)
                {
                    if(TIMES[i].empates<TIMES[j].empates)
                    {
                    TIMES[32] = TIMES[i];
                    TIMES[i]=TIMES[j];
                    TIMES[j]=TIMES[32];
                    }
                }
            }
    }

void exibirTabelaGeral(){
    system("cls");
    int i, j;

    printf("+------------------+--------+-------+-------+-------+-------+-------+\n");
    printf("|                         .::EstatÌsticas::.                        |\n");
    printf("+------------------+--------+-------+-------+-------+-------+-------+\n");
    printf("|       TIME       |   SG   |   G+  |   G-  |   V   |   D   |   E   |\n");
    printf("+------------------+--------+-------+-------+-------+-------+-------+\n");

    for(j = 0; j < 32; j += 1){
        printf("|  %-15s |   %2d   |   %2d  |   %2d  |   %2d  |   %2d  |   %2d  |\n", TIMES[j].equipes,TIMES[j].saldo,TIMES[j].gols,TIMES[j].golsSofridos,TIMES[j].vitorias,TIMES[j].derrotas, TIMES[j].empates);
        printf("+------------------+--------+-------+-------+-------+-------+-------+\n");
    }

    printf("\n\n");
    system("pause");
}
