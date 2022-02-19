#include <conio.h>
#include <iostream>
#include <winbgim.h>
#include <math.h>
#include <time.h>

#define IZQUIERDA 97
#define DERECHA   100
#define ARRIBA    119
#define ABAJO     115
#define INTRO     13
#define ESC       27

using namespace std;
bool salir=0;

int LMAYUS(int TCLA){
    if(TCLA == 65){
        return IZQUIERDA;
    }
    if(TCLA == 68){
        return DERECHA;
    }
    if(TCLA == 87){
        return ARRIBA;
    }
    if(TCLA == 83){
        return ABAJO;
    }
    return TCLA;
}

class GAME{
    private:
        char **MAP;
        int Xpos;
        int Ypos;
        int PLAYER1[2];
        char ACT;
    public:
        GAME(int X,int Y,int DistCaminoAleatorio){

            Xpos = X;
            Ypos = Y;
            MAP= new char*[Y];

            for (int i = 0; i < Y; i++){
                MAP[i] = new char[X];
            }
            for (int i = 0; i < Y; i++) { //INICIO - FIN
                for (int j = 0; j < X; j++){
                    if(i == 0){
                        MAP[i][j] = '5';
                    }else if( i > Y-10){
                        MAP[i][j] = '2';
                    }else{
                        MAP[i][j] = '0';
                    }
                }
            }

            int PxC = rand()%X; //POS X INICIAL PARA TRAZAR CAMINO
            int Avance = rand()%DistCaminoAleatorio;

            for (int PyC = 0, DIR = 0; PyC < Y-10;Avance--){ //TRAZA CAMINO
                if(DIR == 0){
                    PyC++;
                }else if(DIR == 1){     //IZQUIERDA
                    if(PxC > 2){
                        PxC--;
                    }else{
                        for(;PxC<X/2;PxC++){
                            MAP[PyC][PxC] = '*';
                        }
                    }
                }else{                  //DERECHA
                    if(PxC < X-2){
                        PxC++;
                    }else{
                        for(;PxC>X/2;PxC--){
                            MAP[PyC][PxC-1] = '*';
                        }
                    }
                }
                if(Avance <= 0){
                    DIR = rand()%3;
                    Avance = 1+rand()%(DistCaminoAleatorio-1);
                }
                MAP[PyC][PxC] = '*';
            }

            PLAYER1[0] = X/2;
            PLAYER1[1] = Y-8;
            MAP[PLAYER1[1]][PLAYER1[0]] = '8';
            ACT = '2';

        }

        void MOSTRAR(){
            for (int i = 0; i < Ypos; i++) {
                for (int j = 0; j < Xpos; j++){
                    cout<<MAP[i][j];
                }cout<<"\n";
            }
        }

        void MOSTRAR_WINBGIM(int x,int y,int e){

            for (int i = 0; i < Ypos; i++) {
                for (int j = 0; j < Xpos; j++){

                    if(MAP[i][j]=='*'){
                        setfillstyle(1,COLOR(100,100,250));
                        DRAW_CUBO(x+e*j,y+e*i,e,14);

                    }else if(MAP[i][j]=='2'){
                        setfillstyle(1,COLOR(100,250,200));
                        DRAW_CUBO(x+e*j,y+e*i,e,8);
                    }else if(MAP[i][j]=='5'){
                        setfillstyle(1,COLOR(10,250,200));
                        DRAW_CUBO(x+e*j,y+e*i,e,4);
                    }
                    else{
                        setfillstyle(1,COLOR(10,10,100));
                        DRAW_CUBO(x+e*j,y+e*i,e,12);
                    }

                }
            }
        }

        bool MOSV(int x,int y,int e,int Ycubos,int Velocidad){

            for(int i=0,V=0;i<Ypos-3;V++){
                MOSTRAR_WI(x,y,e,Ypos-7-i,Ycubos);

                if(kbhit()){
                    MAP[PLAYER1[1]][PLAYER1[0]] = ACT;

                    switch(LMAYUS(getch())){
                        case IZQUIERDA:
                            PLAYER1[0]--;
                            break;
                        case DERECHA:
                            PLAYER1[0]++;
                            break;
                        case ARRIBA:
                            PLAYER1[1]--;
                            break;
                        case ABAJO:
                            PLAYER1[1]++;
                    }

                    if(MAP[PLAYER1[1]][PLAYER1[0]]=='*'){
                        ACT = '*';
                    }else{
                        ACT = '2';
                    }

                    if(MAP[PLAYER1[1]][PLAYER1[0]]!='0'){
                        if(MAP[PLAYER1[1]][PLAYER1[0]]=='5'){
                            YOUWIN();
                            return 1;
                        }else{
                            MAP[PLAYER1[1]][PLAYER1[0]] = '8';
                        }
                    }else{
                        GAMEOVER();
                        return 0;
                    }
                }

                if(PLAYER1[1]>Ypos-8-i+Ycubos){
                    GAMEOVER();
                    return 0;
                }

                if(V == Velocidad){
                    i++;
                    V = 0;
                    if(Velocidad>15){
                        Velocidad--;
                    }
                }
                delay(1);
            }
            return 0;
        }

        void MOSTRAR_WI(int x,int y,int e,int YACT,int RANGO){

            for(int n = YACT-RANGO, i = 0;n < YACT+RANGO;n++,i++){
                for (int m = 0,j = 0; m < Xpos; m++,j++){
                    if(n>=0&&n<Ypos){

                        if(MAP[n][m]=='*'){
                            setfillstyle(1,COLOR(10,10,100));
                            DRAW_CUBO(x+e*j,y+e*i,e,14);
                        }else if(MAP[n][m]=='2'){
                            setfillstyle(1,COLOR(100,250,200));
                            DRAW_CUBO(x+e*j,y+e*i,e,8);
                        }else if(MAP[n][m]=='5'){
                            setfillstyle(1,COLOR(10,250,200));
                            DRAW_CUBO(x+e*j,y+e*i,e,4);
                        }else if(MAP[n][m]=='8'){
                            setfillstyle(1,COLOR(250,250,250));
                            DRAW_CUBO(x+e*j,y+e*i,e,4);
                        }else{
                            setfillstyle(1,COLOR(250,50,100));
                            DRAW_CUBO(x+e*j,y+e*i,e,12);
                        }

                    }
                }
            }

        }

        void DRAW_CUBO(int x,int y,int e,int color){
            setcolor(color);
            bar(x,y,x+e,y+e);
//            rectangle(x+1,y+1,x+e-3,y+e-1);
        }

        void GAMEOVER(){
            cleardevice();
            setcolor(14);
            settextstyle(2, HORIZ_DIR, 15);
            outtextxy(200,100,"GAME OVER");
        }

        void YOUWIN(){
            cleardevice();
            setcolor(14);
            settextstyle(2, HORIZ_DIR, 15);
            outtextxy(200,100,"YOU WIN");
        }

};

int main(){

    int ScreenX = 800,ScreenY = 800;
    initwindow(ScreenX,ScreenY);
    int Block = 7;
    int Vel = 100;

    float Tam;

    do{
        cleardevice();
//        setcolor(4);
        setfillstyle(1,COLOR(250,250,250));
        bar(0,0,ScreenX,ScreenY);

        GAME A(Block,Block*5,3);

        Tam = (ScreenX/Block);

        if(A.MOSV(0,80,Tam,Block/2,Vel)){
            Block++;
            Vel-=5;

        }else{

        }

    }while(getch()!=ESC);

    closegraph();
    return 0;
}
