#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <process.h>
#include <conio.h>
#include <math.h>

// Estrutura do Jogo.
typedef struct dadosPacman
{
    int vida;
    int poder;
    int colunaAtual;
    int linhaAtual;
    int mapa[21][20];
    char tecla;
    int totalComidas;
    int score;
} PACMAN;
// Estrutura do Fantasma.
typedef struct dadosFantasma
{
    int efeito;
    int colunaAtual;
    int linhaAtual;
    int esquerda;
    int direita;
    int cima;
    int baixo;
} FANTASMA;
// Declaracao Global
HANDLE h;
HANDLE trava;
PACMAN pac;
// Movimenta o Cursor na tela.
void gotoxy(int x,int y)
{
    COORD coord;
    coord.X=(short)x;
    coord.Y=(short)y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
}
// Funcao que esconde o cursos da tela.
void HideCursor()
{
    CONSOLE_CURSOR_INFO cursor = {1, FALSE};
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor);
}
// Funcao que deixa a aparencia do prinft colorida.
void ligacor(int fgcolor,int bgcolor)
{
    bgcolor*=pow(2,4);
    SetConsoleTextAttribute ( h, fgcolor | bgcolor);
}
// Funçao que remove a aparencia do prinft e deixa ele como default.
void desligacor()
{
    WORD wOldColorAttrs;
    CONSOLE_SCREEN_BUFFER_INFO csbiInfo;
    GetConsoleScreenBufferInfo(h, &csbiInfo);
    wOldColorAttrs = csbiInfo.wAttributes;
    SetConsoleTextAttribute ( h, wOldColorAttrs);
}
// Funcao que preenche a matriz do mapa.
void preencheMapa()
{
    //Pontas
    pac.mapa[1][1]=32;
    pac.mapa[21][1]=32;
    pac.mapa[1][19]=32;
    pac.mapa[21][19]=32;
    //Borda Top
    pac.mapa[2][1]=32;
    pac.mapa[3][1]=32;
    pac.mapa[4][1]=32;
    pac.mapa[5][1]=32;
    pac.mapa[6][1]=32;
    pac.mapa[7][1]=32;
    pac.mapa[8][1]=32;
    pac.mapa[9][1]=32;
    pac.mapa[10][1]=32;
    pac.mapa[11][1]=32;
    pac.mapa[12][1]=32;
    pac.mapa[13][1]=32;
    pac.mapa[14][1]=32;
    pac.mapa[15][1]=32;
    pac.mapa[16][1]=32;
    pac.mapa[17][1]=32;
    pac.mapa[18][1]=32;
    pac.mapa[19][1]=32;
    pac.mapa[20][1]=32;
    //Borda Bot
    pac.mapa[2][19]=32;
    pac.mapa[3][19]=32;
    pac.mapa[4][19]=32;
    pac.mapa[5][19]=32;
    pac.mapa[6][19]=32;
    pac.mapa[7][19]=32;
    pac.mapa[8][19]=32;
    pac.mapa[9][19]=32;
    pac.mapa[10][19]=32;
    pac.mapa[11][19]=32;
    pac.mapa[12][19]=32;
    pac.mapa[13][19]=32;
    pac.mapa[14][19]=32;
    pac.mapa[15][19]=32;
    pac.mapa[16][19]=32;
    pac.mapa[17][19]=32;
    pac.mapa[18][19]=32;
    pac.mapa[19][19]=32;
    pac.mapa[20][19]=32;
    //Borda Esquerda
    pac.mapa[1][2]=32;
    pac.mapa[1][3]=32;
    pac.mapa[1][4]=32;
    pac.mapa[1][5]=32;
    pac.mapa[1][7]=32;
    pac.mapa[1][9]=32;
    pac.mapa[1][11]=32;
    pac.mapa[1][12]=32;
    pac.mapa[1][13]=32;
    pac.mapa[1][14]=32;
    pac.mapa[1][15]=32;
    pac.mapa[1][16]=32;
    pac.mapa[1][17]=32;
    pac.mapa[1][18]=32;
    //Borda Direita
    pac.mapa[21][2]=32;
    pac.mapa[21][3]=32;
    pac.mapa[21][4]=32;
    pac.mapa[21][5]=32;
    pac.mapa[21][7]=32;
    pac.mapa[21][9]=32;
    pac.mapa[21][11]=32;
    pac.mapa[21][12]=32;
    pac.mapa[21][13]=32;
    pac.mapa[21][14]=32;
    pac.mapa[21][15]=32;
    pac.mapa[21][16]=32;
    pac.mapa[21][17]=32;
    pac.mapa[21][18]=32;
    //Interior Horizontal
    pac.mapa[3][3]=32;
    pac.mapa[4][3]=32;
    pac.mapa[5][3]=32;
    pac.mapa[7][3]=32;
    pac.mapa[8][3]=32;
    pac.mapa[9][3]=32;
    pac.mapa[13][3]=32;
    pac.mapa[14][3]=32;
    pac.mapa[15][3]=32;
    pac.mapa[17][3]=32;
    pac.mapa[18][3]=32;
    pac.mapa[19][3]=32;
    pac.mapa[13][7]=32;
    pac.mapa[14][7]=32;
    pac.mapa[15][7]=32;
    pac.mapa[7][13]=32;
    pac.mapa[8][13]=32;
    pac.mapa[9][13]=32;
    pac.mapa[10][13]=32;
    pac.mapa[12][13]=32;
    pac.mapa[13][13]=32;
    pac.mapa[14][13]=32;
    pac.mapa[15][13]=32;
    pac.mapa[2][15]=32;
    pac.mapa[3][15]=32;
    pac.mapa[19][15]=32;
    pac.mapa[20][15]=32;
    //Interior Vertical
    pac.mapa[11][2]=32;
    pac.mapa[11][3]=32;
    pac.mapa[7][9]=32;
    pac.mapa[7][10]=32;
    pac.mapa[7][11]=32;
    pac.mapa[15][9]=32;
    pac.mapa[15][10]=32;
    pac.mapa[15][11]=32;
    //Interior L
    pac.mapa[7][5]=32;
    pac.mapa[7][6]=32;
    pac.mapa[7][7]=32;
    pac.mapa[8][7]=32;
    pac.mapa[9][7]=32;
    pac.mapa[3][13]=32;
    pac.mapa[4][13]=32;
    pac.mapa[5][13]=32;
    pac.mapa[5][14]=32;
    pac.mapa[5][15]=32;
    pac.mapa[17][13]=32;
    pac.mapa[18][13]=32;
    pac.mapa[19][13]=32;
    pac.mapa[17][14]=32;
    pac.mapa[17][15]=32;
    //Interior Base Fantasma
    pac.mapa[9][9]=32;
    pac.mapa[10][9]=32;
    pac.mapa[12][9]=32;
    pac.mapa[13][9]=32;
    pac.mapa[9][10]=32;
    pac.mapa[13][10]=32;
    pac.mapa[9][11]=32;
    pac.mapa[10][11]=32;
    pac.mapa[11][11]=32;
    pac.mapa[12][11]=32;
    pac.mapa[13][11]=32;
    //Interior Base T
    pac.mapa[9][5]=32;
    pac.mapa[10][5]=32;
    pac.mapa[11][5]=32;
    pac.mapa[12][5]=32;
    pac.mapa[13][5]=32;
    pac.mapa[14][5]=32;
    pac.mapa[15][5]=32;
    pac.mapa[11][6]=32;
    pac.mapa[11][7]=32;
    pac.mapa[3][17]=32;
    pac.mapa[4][17]=32;
    pac.mapa[5][17]=32;
    pac.mapa[6][17]=32;
    pac.mapa[7][17]=32;
    pac.mapa[8][17]=32;
    pac.mapa[9][17]=32;
    pac.mapa[7][15]=32;
    pac.mapa[7][16]=32;
    pac.mapa[9][15]=32;
    pac.mapa[10][15]=32;
    pac.mapa[11][15]=32;
    pac.mapa[12][15]=32;
    pac.mapa[13][15]=32;
    pac.mapa[15][15]=32;
    pac.mapa[11][16]=32;
    pac.mapa[11][17]=32;
    pac.mapa[13][17]=32;
    pac.mapa[14][17]=32;
    pac.mapa[15][17]=32;
    pac.mapa[16][17]=32;
    pac.mapa[17][17]=32;
    pac.mapa[18][17]=32;
    pac.mapa[19][17]=32;
    pac.mapa[15][15]=32;
    pac.mapa[15][16]=32;
    //Interior Outras
    pac.mapa[2][5]=32;
    pac.mapa[3][5]=32;
    pac.mapa[4][5]=32;
    pac.mapa[5][5]=32;
    pac.mapa[5][6]=32;
    pac.mapa[5][7]=32;
    pac.mapa[2][7]=32;
    pac.mapa[3][7]=32;
    pac.mapa[4][7]=32;
    pac.mapa[2][9]=32;
    pac.mapa[3][9]=32;
    pac.mapa[4][9]=32;
    pac.mapa[5][9]=32;
    pac.mapa[5][10]=32;
    pac.mapa[2][11]=32;
    pac.mapa[3][11]=32;
    pac.mapa[4][11]=32;
    pac.mapa[5][11]=32;
    pac.mapa[17][5]=32;
    pac.mapa[18][5]=32;
    pac.mapa[19][5]=32;
    pac.mapa[20][5]=32;
    pac.mapa[17][6]=32;
    pac.mapa[17][7]=32;
    pac.mapa[18][7]=32;
    pac.mapa[19][7]=32;
    pac.mapa[20][7]=32;
    pac.mapa[17][9]=32;
    pac.mapa[18][9]=32;
    pac.mapa[19][9]=32;
    pac.mapa[20][9]=32;
    pac.mapa[17][10]=32;
    pac.mapa[17][11]=32;
    pac.mapa[18][11]=32;
    pac.mapa[19][11]=32;
    pac.mapa[20][11]=32;
    pac.mapa[5][15]=32;
    pac.mapa[17][13]=32;
    pac.mapa[18][13]=32;
    pac.mapa[19][13]=32;
    pac.mapa[17][14]=32;
    pac.mapa[17][15]=32;
    //Interior Base Fantasma
    pac.mapa[9][9]=32;
    pac.mapa[10][9]=32;
    pac.mapa[12][9]=32;
    pac.mapa[13][9]=32;
    pac.mapa[9][10]=32;
    pac.mapa[13][10]=32;
    pac.mapa[9][11]=32;
    pac.mapa[10][11]=32;
    pac.mapa[11][11]=32;
    pac.mapa[12][11]=32;
    pac.mapa[13][11]=32;
    //Interior Base T
    pac.mapa[9][5]=32;
    pac.mapa[10][5]=32;
    pac.mapa[11][5]=32;
    pac.mapa[12][5]=32;
    pac.mapa[13][5]=32;
    pac.mapa[14][5]=32;
    pac.mapa[15][5]=32;
    pac.mapa[11][6]=32;
    pac.mapa[11][7]=32;
    pac.mapa[3][17]=32;
    pac.mapa[4][17]=32;
    pac.mapa[5][17]=32;
    pac.mapa[6][17]=32;
    pac.mapa[7][17]=32;
    pac.mapa[8][17]=32;
    pac.mapa[9][17]=32;
    pac.mapa[7][15]=32;
    pac.mapa[7][16]=32;
    pac.mapa[9][15]=32;
    pac.mapa[10][15]=32;
    pac.mapa[11][15]=32;
    pac.mapa[12][15]=32;
    pac.mapa[13][15]=32;
    pac.mapa[15][15]=32;
    pac.mapa[11][16]=32;
    pac.mapa[11][17]=32;
    pac.mapa[13][17]=32;
    pac.mapa[14][17]=32;
    pac.mapa[15][17]=32;
    pac.mapa[16][17]=32;
    pac.mapa[17][17]=32;
    pac.mapa[18][17]=32;
    pac.mapa[19][17]=32;
    pac.mapa[15][15]=32;
    pac.mapa[15][16]=32;
    //Interior Outras
    pac.mapa[2][5]=32;
    pac.mapa[3][5]=32;
    pac.mapa[4][5]=32;
    pac.mapa[5][5]=32;
    pac.mapa[5][6]=32;
    pac.mapa[5][7]=32;
    pac.mapa[2][7]=32;
    pac.mapa[3][7]=32;
    pac.mapa[4][7]=32;
    pac.mapa[2][9]=32;
    pac.mapa[3][9]=32;
    pac.mapa[4][9]=32;
    pac.mapa[5][9]=32;
    pac.mapa[5][10]=32;
    pac.mapa[2][11]=32;
    pac.mapa[3][11]=32;
    pac.mapa[4][11]=32;
    pac.mapa[5][11]=32;
    pac.mapa[17][5]=32;
    pac.mapa[18][5]=32;
    pac.mapa[19][5]=32;
    pac.mapa[20][5]=32;
    pac.mapa[17][6]=32;
    pac.mapa[17][7]=32;
    pac.mapa[18][7]=32;
    pac.mapa[19][7]=32;
    pac.mapa[20][7]=32;
    pac.mapa[17][9]=32;
    pac.mapa[18][9]=32;
    pac.mapa[19][9]=32;
    pac.mapa[20][9]=32;
    pac.mapa[17][10]=32;
    pac.mapa[17][11]=32;
    pac.mapa[18][11]=32;
    pac.mapa[19][11]=32;
    pac.mapa[20][11]=32;
    //Comidas Poder
    pac.mapa[3][14]=184;
    pac.mapa[19][14]=184;
    pac.mapa[4][2]=184;
    pac.mapa[18][2]=184;
    //Comidas Pontos
    pac.mapa[2][18]=250;
    pac.mapa[3][18]=250;
    pac.mapa[4][18]=250;
    pac.mapa[5][18]=250;
    pac.mapa[6][18]=250;
    pac.mapa[7][18]=250;
    pac.mapa[7][18]=250;
    pac.mapa[7][18]=250;
    pac.mapa[8][18]=250;
    pac.mapa[9][18]=250;
    pac.mapa[10][18]=250;
    pac.mapa[11][18]=250;
    pac.mapa[12][18]=250;
    pac.mapa[13][18]=250;
    pac.mapa[14][18]=250;
    pac.mapa[15][18]=250;
    pac.mapa[16][18]=250;
    pac.mapa[17][18]=250;
    pac.mapa[18][18]=250;
    pac.mapa[19][18]=250;
    pac.mapa[20][18]=250;
    pac.mapa[2][17]=250;
    pac.mapa[2][16]=250;
    pac.mapa[3][16]=250;
    pac.mapa[4][16]=250;
    pac.mapa[4][15]=250;
    pac.mapa[4][14]=250;
    pac.mapa[2][14]=250;
    pac.mapa[2][13]=250;
    pac.mapa[2][12]=250;
    pac.mapa[3][12]=250;
    pac.mapa[4][12]=250;
    pac.mapa[5][12]=250;
    pac.mapa[6][12]=250;
    pac.mapa[7][12]=250;
    pac.mapa[15][12]=250;
    pac.mapa[16][12]=250;
    pac.mapa[17][12]=250;
    pac.mapa[18][12]=250;
    pac.mapa[19][12]=250;
    pac.mapa[20][12]=250;
    pac.mapa[5][16]=250;
    pac.mapa[6][16]=250;
    pac.mapa[6][15]=250;
    pac.mapa[6][14]=250;
    pac.mapa[6][13]=250;
    pac.mapa[7][14]=250;
    pac.mapa[8][14]=250;
    pac.mapa[9][14]=250;
    pac.mapa[10][14]=250;
    pac.mapa[11][14]=250;
    pac.mapa[12][14]=250;
    pac.mapa[13][14]=250;
    pac.mapa[14][14]=250;
    pac.mapa[15][14]=250;
    pac.mapa[16][14]=250;
    pac.mapa[16][13]=250;
    pac.mapa[16][15]=250;
    pac.mapa[16][16]=250;
    pac.mapa[17][16]=250;
    pac.mapa[18][16]=250;
    pac.mapa[19][16]=250;
    pac.mapa[20][16]=250;
    pac.mapa[20][17]=250;
    pac.mapa[18][15]=250;
    pac.mapa[18][14]=250;
    pac.mapa[20][14]=250;
    pac.mapa[20][13]=250;
    pac.mapa[8][15]=250;
    pac.mapa[8][16]=250;
    pac.mapa[9][16]=250;
    pac.mapa[10][16]=250;
    pac.mapa[10][17]=250;
    pac.mapa[12][17]=250;
    pac.mapa[12][16]=250;
    pac.mapa[13][16]=250;
    pac.mapa[14][16]=250;
    pac.mapa[14][15]=250;
    pac.mapa[3][2]=250;
    pac.mapa[19][2]=250;
    pac.mapa[2][2]=250;
    pac.mapa[2][3]=250;
    pac.mapa[2][4]=250;
    pac.mapa[3][4]=250;
    pac.mapa[4][4]=250;
    pac.mapa[5][4]=250;
    pac.mapa[6][4]=250;
    pac.mapa[7][4]=250;
    pac.mapa[8][4]=250;
    pac.mapa[9][4]=250;
    pac.mapa[10][4]=250;
    pac.mapa[10][3]=250;
    pac.mapa[10][2]=250;
    pac.mapa[9][2]=250;
    pac.mapa[8][2]=250;
    pac.mapa[7][2]=250;
    pac.mapa[6][2]=250;
    pac.mapa[5][2]=250;
    pac.mapa[17][2]=250;
    pac.mapa[16][2]=250;
    pac.mapa[15][2]=250;
    pac.mapa[14][2]=250;
    pac.mapa[13][2]=250;
    pac.mapa[12][2]=250;
    pac.mapa[12][3]=250;
    pac.mapa[12][4]=250;
    pac.mapa[11][4]=250;
    pac.mapa[13][4]=250;
    pac.mapa[14][4]=250;
    pac.mapa[15][4]=250;
    pac.mapa[16][4]=250;
    pac.mapa[16][3]=250;
    pac.mapa[17][4]=250;
    pac.mapa[18][4]=250;
    pac.mapa[19][4]=250;
    pac.mapa[20][4]=250;
    pac.mapa[20][3]=250;
    pac.mapa[20][2]=250;
    pac.mapa[6][5]=250;
    pac.mapa[6][6]=250;
    pac.mapa[8][5]=250;
    pac.mapa[8][6]=250;
    pac.mapa[9][6]=250;
    pac.mapa[10][6]=250;
    pac.mapa[10][7]=250;
    pac.mapa[6][7]=250;
    pac.mapa[12][7]=250;
    pac.mapa[12][6]=250;
    pac.mapa[13][6]=250;
    pac.mapa[14][6]=250;
    pac.mapa[15][6]=250;
    pac.mapa[16][7]=250;
    pac.mapa[16][6]=250;
    pac.mapa[16][5]=250;
    pac.mapa[6][8]=250;
    pac.mapa[7][8]=250;
    pac.mapa[16][8]=250;
    pac.mapa[15][8]=250;
    pac.mapa[6][11]=250;
    pac.mapa[6][10]=250;
    pac.mapa[6][9]=250;
    pac.mapa[16][11]=250;
    pac.mapa[16][10]=250;
    pac.mapa[16][9]=250;
    pac.mapa[11][13]=250;
    //Porta Fantasma
    pac.mapa[11][9]=177;
    //Portal Setas
    pac.mapa[1][8]=27;
    pac.mapa[21][8]=26;

}
// Cria a borda do jogo.
void borda()
{
    int coluna=0, linha=0;

    // Printa o mapa inteiro de preto.
    ligacor(0,0);
    for(coluna=0; coluna<35; coluna++)
    {
        for(linha=0; linha <30; linha++)
        {
            gotoxy(coluna,linha);
            printf(" ");
        }
    }

    // Cor da borda.
    ligacor(0,15);
    coluna=0;
    linha=0;
    // Cria as bordas de cima/baixo.
    while(linha<21)
    {
        gotoxy(coluna,linha);
        printf(" ");
        gotoxy(coluna+22,linha);
        printf(" ");
        gotoxy(coluna+34,linha);
        printf(" ");
        linha++;
    }
    coluna=1;
    linha=0;
    // Cria as bordas laterais.
    while(coluna<34)
    {
        gotoxy(coluna,linha);
        printf(" ");
        gotoxy(coluna,linha+20);
        printf(" ");
        coluna++;
    }

    coluna = 23;
    linha = 1;
    // Cria a area das informacoes do jogo.
    for(coluna=24; coluna<33; coluna++)
    {
        for(linha=2; linha<19; linha++)
        {
            gotoxy(coluna,linha);
            printf(" ");
        }
    }
}
// Percorre e printa a matriz.
void printaMapa()
{
    int coluna, linha;

    for(coluna=0; coluna<22; coluna++)
    {
        for(linha=0; linha<20; linha++)
        {
            gotoxy(coluna,linha);
            if(pac.mapa[coluna][linha]==32)
            {
                ligacor(0,9);
                printf("%c",pac.mapa[coluna][linha]);
                desligacor();
            }
            if(pac.mapa[coluna][linha]==250)
            {
                ligacor(14,0);
                printf("%c",pac.mapa[coluna][linha]);
                desligacor();
            }
            if(pac.mapa[coluna][linha]==184)
            {
                ligacor(12,0);
                printf("%c",pac.mapa[coluna][linha]);
                desligacor();
            }
            if(pac.mapa[coluna][linha]==177)
            {
                ligacor(7,0);
                printf("%c",pac.mapa[coluna][linha]);
                desligacor();
            }
            if(pac.mapa[coluna][linha]==26 || pac.mapa[coluna][linha]==27)
            {
                ligacor(14,0);
                printf("%c",pac.mapa[coluna][linha]);
                desligacor();
            }

        }
    }
}
// Printa as informacoes na tela(vidas,pontos,bonus,logo), e borda enfeitada.
void printaInfo()
{
    int coluna = 24;
    int linha = 3;

    ligacor(0,15);
    gotoxy(24,2);
    printf("%c",201);

    ligacor(0,15);
    gotoxy(32,2);
    printf("%c",187);

    ligacor(0,15);
    gotoxy(32,18);
    printf("%c",188);

    ligacor(0,15);
    gotoxy(24,18);
    printf("%c",200);

    //Borda Enfeite
    while(linha<18)
    {
        ligacor(0,15);
        gotoxy(coluna,linha);
        printf("%c",186);
        gotoxy(coluna+8,linha);
        printf("%c",186);
        linha++;
    }

    coluna = 25;
    linha = 2;

    while(coluna<32)
    {
        ligacor(0,15);
        gotoxy(coluna,linha);
        printf("%c",205);
        gotoxy(coluna,linha+16);
        printf("%c",205);
        coluna++;
    }
    //

    ligacor(0,12);
    gotoxy(27,6);
    printf("   ");

    gotoxy(26,7);
    printf(" ");
    gotoxy(28,7);
    printf(" ");
    gotoxy(30,7);
    printf(" ");

    gotoxy(26,8);
    printf("     ");
    gotoxy(26,9);
    printf("     ");
    gotoxy(26,10);
    printf(" ");
    gotoxy(28,10);
    printf(" ");
    gotoxy(30,10);
    printf(" ");

    ligacor(1,15);
    gotoxy(27,7);
    printf("%c",254);
    gotoxy(29,7);
    printf("%c",254);

    ligacor(15,12);
    gotoxy(26,3);
    printf("PAC");
    gotoxy(28,4);
    printf("MAN");


    ligacor(15,0);
    gotoxy(26,12);
    printf("LIVES");
    ligacor(12,0);
    gotoxy(26,13);
    printf(" %c%c%c ",3,3,3);

    ligacor(15,0);
    gotoxy(26,14);
    printf("%c:",2);

    ligacor(14,0);
    gotoxy(28,14);
    printf("00 ");

    ligacor(15,0);
    gotoxy(26,16);
    printf("SCORE");
    desligacor();
}
// Printa e atualiza o score.
void printaScore()
{
    WaitForSingleObject(trava,INFINITE);
    ligacor(14,0);
    gotoxy(26,17);
    printf("%.5d",pac.score);
    ReleaseMutex(trava);
}
// Atualiza a quantidade de vidas na tela.
void printaVida()
{
    if(pac.vida==2)
    {
        WaitForSingleObject(trava,INFINITE);
        ligacor(12,0);
        gotoxy(26,13);
        printf(" %c%c  ",3,3);
        ReleaseMutex(trava);
    }
    if(pac.vida==1)
    {
        WaitForSingleObject(trava,INFINITE);
        ligacor(12,0);
        gotoxy(26,13);
        printf(" %c   ",3);
        ReleaseMutex(trava);
    }
}
//Pega a tecla digitada e valida a direcao.
void pegatecla()
{
    char tecla;

    while(pac.vida>0)
    {

        tecla = getch();

        if(tecla == 75 /*&& pac.mapa[pac.colunaAtual-1][pac.linhaAtual]!=32*/)
            pac.tecla = 'e';

        if(tecla == 77 /*&& pac.mapa[pac.colunaAtual+1][pac.linhaAtual]!=32*/)
            pac.tecla = 'd';

        if(tecla == 72 /*&& pac.mapa[pac.colunaAtual][pac.linhaAtual-1]!=32*/)
            pac.tecla = 'c';

        if(tecla == 80 /*&& pac.mapa[pac.colunaAtual][pac.linhaAtual+1]!=32*/)
            pac.tecla = 'b';
    }
}
//Apaga posicao anterior.
void apaga(int coluna, int linha)
{
    _sleep(250);
    WaitForSingleObject(trava,INFINITE);
    ligacor(14,0);
    gotoxy(coluna,linha);
    printf(" ");
    desligacor();
    ReleaseMutex(trava);
}
//Ao comer a bolinha vermelha muda para 10 o tempo de poder, sendo 10 o máximo.
void ativaPoder()
{
    pac.poder = 10;
}
//Consome o tempo de poder.
void consomePoder()
{
    while(pac.vida>0 && pac.totalComidas<145)
    {
        if(pac.poder>=0)
        {

            WaitForSingleObject(trava,INFINITE);
            ligacor(14,0);
            gotoxy(28,14);
            printf("%.2d",pac.poder);
            ReleaseMutex(trava);
            _sleep(1000);
            pac.poder = pac.poder -1;
        }
    }
}
//Inicia o pacman.
void start()
{

    while(pac.vida>0 && pac.totalComidas<145)
    {

        WaitForSingleObject(trava,INFINITE);
        ligacor(14,0);
        gotoxy(pac.colunaAtual,pac.linhaAtual);
        printf("%c",2);
        desligacor();
        ReleaseMutex(trava);

        switch(pac.tecla)
        {
        //Esquerda
        case 'e':
            if(pac.colunaAtual==1 && pac.linhaAtual==8)
            {
                WaitForSingleObject(trava,INFINITE);
                ligacor(14,0);
                gotoxy(1,8);
                printf("%c",27);
                pac.colunaAtual=21;
                pac.linhaAtual=8;
                desligacor();
                ReleaseMutex(trava);
            }
            else if(pac.mapa[pac.colunaAtual-1][pac.linhaAtual]!=32)
            {
                if(pac.mapa[pac.colunaAtual-1][pac.linhaAtual]==250)
                {
                    pac.mapa[pac.colunaAtual-1][pac.linhaAtual]=NULL;
                    pac.score=pac.score+10;
                    pac.totalComidas++;
                    printaScore();
                }
                if(pac.mapa[pac.colunaAtual-1][pac.linhaAtual]==184)
                {
                    pac.mapa[pac.colunaAtual-1][pac.linhaAtual]=NULL;
                    ativaPoder();
                }
                apaga(pac.colunaAtual,pac.linhaAtual);
                WaitForSingleObject(trava,INFINITE);
                pac.colunaAtual--;
                ReleaseMutex(trava);
            }
            if(pac.colunaAtual+1==21 && pac.linhaAtual==8)
            {
                WaitForSingleObject(trava,INFINITE);
                gotoxy(21,8);
                printf("%c",26);
                ReleaseMutex(trava);
            }
            break;
        //Direita
        case 'd':
            if(pac.colunaAtual==21 && pac.linhaAtual==8)
            {
                WaitForSingleObject(trava,INFINITE);
                ligacor(14,0);
                gotoxy(21,8);
                printf("%c",26);
                desligacor();
                ReleaseMutex(trava);
                WaitForSingleObject(trava,INFINITE);
                pac.colunaAtual=1;
                pac.linhaAtual=8;
                ReleaseMutex(trava);
            }
            else if(pac.mapa[pac.colunaAtual+1][pac.linhaAtual]!=32)
            {
                if(pac.mapa[pac.colunaAtual+1][pac.linhaAtual]==250)
                {
                    pac.mapa[pac.colunaAtual+1][pac.linhaAtual]=NULL;
                    pac.score=pac.score+10;
                    pac.totalComidas++;
                    printaScore();
                }
                if(pac.mapa[pac.colunaAtual+1][pac.linhaAtual]==184)
                {
                    pac.mapa[pac.colunaAtual-1][pac.linhaAtual]=NULL;
                    ativaPoder();
                }
                apaga(pac.colunaAtual,pac.linhaAtual);
                WaitForSingleObject(trava,INFINITE);
                pac.colunaAtual++;
                ReleaseMutex(trava);
            }
            if(pac.colunaAtual-1==1 && pac.linhaAtual==8)
            {
                WaitForSingleObject(trava,INFINITE);
                gotoxy(1,8);
                printf("%c",27);
                ReleaseMutex(trava);
            }
            break;
        //Cima
        case 'c':
            if(pac.mapa[pac.colunaAtual][pac.linhaAtual-1]!=32)
            {
                if(pac.mapa[pac.colunaAtual][pac.linhaAtual-1]==250)
                {
                    pac.mapa[pac.colunaAtual][pac.linhaAtual-1]=NULL;
                    pac.score=pac.score+10;
                    pac.totalComidas++;
                    printaScore();
                }
                if(pac.mapa[pac.colunaAtual][pac.linhaAtual-1]==184)
                {
                    pac.mapa[pac.colunaAtual-1][pac.linhaAtual]=NULL;
                    ativaPoder();
                }
                apaga(pac.colunaAtual,pac.linhaAtual);
                WaitForSingleObject(trava,INFINITE);
                pac.linhaAtual--;
                ReleaseMutex(trava);
            }
            break;
        //Baixo
        case 'b':
            if(pac.mapa[pac.colunaAtual][pac.linhaAtual+1]!=32)
            {
                if(pac.mapa[pac.colunaAtual][pac.linhaAtual+1]==250)
                {
                    pac.mapa[pac.colunaAtual][pac.linhaAtual+1]=NULL;
                    pac.score=pac.score+10;
                    pac.totalComidas++;
                    printaScore();
                }
                if(pac.mapa[pac.colunaAtual][pac.linhaAtual+1]==184)
                {
                    pac.mapa[pac.colunaAtual-1][pac.linhaAtual]=NULL;
                    ativaPoder();
                }
                apaga(pac.colunaAtual,pac.linhaAtual);
                WaitForSingleObject(trava,INFINITE);
                pac.linhaAtual++;
                ReleaseMutex(trava);
            }
            break;
        }
    }

}
//Funcao do Fantasma.
void fantasma()
{
    int coluna= 11;
    int linha= 10;
    int sorteio;
    int totalDirecoes=0;
    int direcoes[4];
    int direcao=0;
    int vivo=0;

    FANTASMA fant;

    WaitForSingleObject(trava,INFINITE);
    gotoxy(coluna,linha);
    ligacor(13,0);
    printf("%c",2);
    ReleaseMutex(trava);

    _sleep(3000);

    WaitForSingleObject(trava,INFINITE);
    gotoxy(coluna,linha);
    printf(" ");
    ReleaseMutex(trava);

    linha=linha-2;

    WaitForSingleObject(trava,INFINITE);
    ligacor(13,0);
    gotoxy(coluna,linha);
    printf("%c",2);
    ReleaseMutex(trava);

    while(pac.vida>0 && vivo == 0 && pac.totalComidas<145)
    {

        _sleep(250);
        WaitForSingleObject(trava,INFINITE);
        gotoxy(coluna,linha);
        printf("%c",pac.mapa[coluna][linha]);
        ReleaseMutex(trava);

        totalDirecoes=0;

        //Esquerda
        if(pac.mapa[coluna-1][linha]!=32)
        {
            direcoes[totalDirecoes]=1;
            totalDirecoes++;
        }
        //Direita
        if(pac.mapa[coluna+1][linha]!=32)
        {
            direcoes[totalDirecoes]=2;
            totalDirecoes++;
        }
        //Cima
        if(pac.mapa[coluna][linha-1]!=32)
        {
            direcoes[totalDirecoes]=3;
            totalDirecoes++;
        }
        //Baixo
        if(pac.mapa[coluna][linha+1]!=32)
        {
            direcoes[totalDirecoes]=4;
            totalDirecoes++;
        }
        srand(time(NULL));
        sorteio = rand() % totalDirecoes;

        if(direcoes[sorteio]==1 && pac.mapa[coluna-1][linha]!=32 && pac.mapa[coluna-1][linha]!=27)
        {
            coluna--;
        }
        else if(direcoes[sorteio]==2 && pac.mapa[coluna+1][linha]!=32 && pac.mapa[coluna+1][linha]!=26)
        {
            coluna++;
        }
        else if(direcoes[sorteio]==3 && pac.mapa[coluna][linha-1]!=32)
        {
            linha--;
        }
        else if(direcoes[sorteio]==4 && pac.mapa[coluna][linha+1]!=32 && pac.mapa[coluna][linha+1]!=177)
        {
            linha++;
        }

        WaitForSingleObject(trava,INFINITE);
        if(pac.poder>0)
        {
            ligacor(9,0);
        }
        else
        {
           ligacor(13,0);
        }
        gotoxy(coluna,linha);
        printf("%c",2);
        ReleaseMutex(trava);

        if(pac.colunaAtual+1 == coluna && pac.linhaAtual+1 == linha && pac.poder==0)
        {
            pac.vida--;
            printaVida();
            WaitForSingleObject(trava,INFINITE);
            pac.colunaAtual = 11;
            pac.linhaAtual = 12;
            ReleaseMutex(trava);
        }
        if(pac.colunaAtual+1 == coluna && pac.linhaAtual+1 == linha && pac.poder>0)
        {
            vivo=1;
        }

    }

    if(pac.totalComidas<145){
    _sleep(5000);
    _beginthread(fantasma,NULL,NULL);
    }
}
//Funcao que cria os fantasmas.
void criaFantasma()
{
    int maximo = 0;
    while(maximo <= 8 && pac.totalComidas<145)
    {
        maximo++;
        _beginthread(fantasma,NULL,NULL);
        _sleep(3000);
    }
}

// Principal
int main()
{
    system("mode 35,21");
    h = GetStdHandle ( STD_OUTPUT_HANDLE );
    trava=CreateMutex(NULL,FALSE,NULL);
    HideCursor();
    //borda();
    preencheMapa();
    printaMapa();

    pac.vida = 3;
    pac.score = 0;
    pac.totalComidas = 0;
    //Posicao Inicial
    pac.colunaAtual = 11;
    pac.linhaAtual = 12;


    printaInfo();
    printaScore();
    printaVida();

    _beginthread(pegatecla,NULL,NULL);
    _beginthread(start,NULL,NULL);
    _beginthread(consomePoder,NULL,NULL);
    _beginthread(criaFantasma,NULL,NULL);
    while(pac.vida>0);
}
