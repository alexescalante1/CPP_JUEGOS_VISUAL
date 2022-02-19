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
int ScreenX = 800,ScreenY = 800;
int NIVEL = 1;
int SCORE = 0;
int MUSIC = 0;

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

int CONCATENAR(string A,string B,char **R){int TAM=0,i=0;
    for(;A[TAM];TAM++);
    for(;B[i];i++,TAM++);TAM+=1;
    *R = new char [TAM];TAM=0;
    for(i=0;A[i];i++,TAM++){
        *(*(R)+TAM)=A[i];
    }
    for(i=0;B[i];i++,TAM++){
        *(*(R)+TAM)=B[i];
    }*(*(R)+TAM) = '\0';
    return TAM;
}

int CONVERTIR_INT_A_CAD(char **R,int NUM){int TAM=0,i=0;
    if(NUM == 0){
        *R = new char [1];
        *(*(R)+0)='0';
        *(*(R)+1)='\0';
        return 1;
    }
    for(int AUX=NUM;AUX!=0;i++,AUX/=10);
    *R = new char [i];TAM=i;*(*(R)+i)='\0';i-=1;
    for(;i>=0;i--,NUM/=10){
        *(*(R)+i)=(char)(NUM%10+48);
    }
    return TAM;
}

class PARTICULAS{
        float **POS_PARTICULAS;
        int TMUESTRA;
    public:
        void INICIALIZAR_CANT_P(int T){
            TMUESTRA = T;
            POS_PARTICULAS= new float*[T];
            for (int i = 0; i < T; i++){
                *(POS_PARTICULAS+i) = new float[2];
            }
        }

        void DEFINE_DIST(int D){
            for(int i=0;i<TMUESTRA;i++){
                *(*(POS_PARTICULAS+i)+0) = rand()%D;
                *(*(POS_PARTICULAS+i)+1) = rand()%D;
            }
        }

        void MOSTRAR_PARTT(int x,int y,int e,int eT,int R,int G,int B){
            for(int i=0;i<TMUESTRA;i++){
                setcolor(COLOR(R,G,B));
                setlinestyle(SOLID_LINE,1,eT);
                line(x+*(*(POS_PARTICULAS+i)+0),y+*(*(POS_PARTICULAS+i)+1),x+*(*(POS_PARTICULAS+i)+0)+1,y+*(*(POS_PARTICULAS+i)+1)+1);
            }
        }

};

class MATERIAL_STATICO{
        PARTICULAS *A;
        int CANT;
    public:
        MATERIAL_STATICO(int C){
            A = new PARTICULAS[C];
            CANT = C;
        }
        void DEFINIR_PARAMETROS(int C,int D){
            for(int i= 0;i<CANT;i++){
                A[i].INICIALIZAR_CANT_P(C);
                A[i].DEFINE_DIST(D);
            }
        }
        void MOSTRAR(int ID,int x,int y,int e,int eT,int R,int G,int B){
            A[ID].MOSTRAR_PARTT(x,y,e,eT,R,G,B);
        }
}BASE_P(10);

class GAME{
    private:
        char **MAP;
        int Xpos;
        int Ypos;
        int PLAYER1[2];
        int DIR_PLAYER;
        int SCORE_LVL;

        int TMUESTRA;
        float **PARTICULAS;
    public:
        GAME(int X,int Y,int DistCaminoAleatorio,int T){

            Xpos = X;
            Ypos = Y;
            MAP= new char*[Y];

            for (int i = 0; i < Y; i++){
                *(MAP+i) = new char[X];
            }
            for (int i = 0; i < Y; i++) { //INICIO - FIN
                for (int j = 0; j < X; j++){
                    if(i <= 10){
                        *(*(MAP+i)+j) = '5';
                    }else if( i > Y-10){
                        *(*(MAP+i)+j) = '2';
                    }else{
                        *(*(MAP+i)+j) = '0';
                    }
                }
            }

            int PxC = rand()%X; //POS X INICIAL PARA TRAZAR CAMINO
            int Avance = rand()%DistCaminoAleatorio;

            for (int PyC = 10, DIR = 0; PyC < Y-10;Avance--){ //TRAZA CAMINO
                if(DIR == 0){
                    PyC++;
                }else if(DIR == 1){     //IZQUIERDA
                    if(PxC > 2){
                        PxC--;
                    }else{
                        for(;PxC<X/2;PxC++){
                            *(*(MAP+PyC)+PxC) = '*';
                        }
                    }
                }else{                  //DERECHA
                    if(PxC < X-2){
                        PxC++;
                    }else{
                        for(;PxC>X/2;PxC--){
                            *(*(MAP+PyC)+PxC-1) = '*';
                        }
                    }
                }
                if(Avance <= 0){
                    DIR = rand()%3;
                    Avance = 1+rand()%(DistCaminoAleatorio-1);
                }
                *(*(MAP+PyC)+PxC) = '*';
            }

            *(PLAYER1+0) = X/2;
            *(PLAYER1+1) = Y-8;
            DIR_PLAYER = 1;

            TMUESTRA = T;
            PARTICULAS= new float*[T];
            for (int i = 0; i < T; i++){
                *(PARTICULAS+i) = new float[2];
            }

        }

        void DEFINE_PARTICULA(int D){
            for(int i=0;i<TMUESTRA;i++){
                *(*(PARTICULAS+i)+0) = rand()%D;
                *(*(PARTICULAS+i)+1) = 5+rand()%(D-10);
            }
        }

        bool CONTROLES(int x,int y,int e,int Ycubos,int Velocidad){
            SCORE_LVL = 0;

            setfillstyle(1,COLOR(70,70,70));
            bar(0,0,ScreenX,75);
            setfillstyle(1,COLOR(100,0,0));
            bar(0,80,ScreenX,ScreenY);

            for(int i=0,V=0;i<Ypos-3;V++){
                MOSTRAR_WI(x,y,e,Ypos-7-i,Ycubos);

                if(kbhit()){

                    switch(LMAYUS(getch())){
                        case IZQUIERDA:
                            if(*(PLAYER1+0)>0){
                                *(PLAYER1+0)-=1;
                            }
                            DIR_PLAYER = 3;
                            break;
                        case DERECHA:
                            if(*(PLAYER1+0)<Xpos-1){
                                *(PLAYER1+0)+=1;
                            }
                            DIR_PLAYER = 4;
                            break;
                        case ARRIBA:
                            *(PLAYER1+1)-=1;
                            DIR_PLAYER = 1;
                            break;
                        case ABAJO:
                            *(PLAYER1+1)+=1;
                            DIR_PLAYER = 2;
                    }

                    if(*(*(MAP+*(PLAYER1+1))+*(PLAYER1+0))!='0'){
                        if(*(*(MAP+*(PLAYER1+1))+*(PLAYER1+0))=='5'){
                            FIN_GAME(1);
                            return 1;
                        }
                    }else{
                        FIN_GAME(0);
                        return 0;
                    }
                }

                if(*(PLAYER1+1)>Ypos-8-i+Ycubos){
                    FIN_GAME(0);
                    return 0;
                }

                if(V == Velocidad){
                    i++;
                    V = 0;
                    SCORE_LVL++;
                    if(Velocidad>6){
                        Velocidad--;
                    }

                    settextstyle(10, HORIZ_DIR,2);
                    char *Rs,*CAD;
                    CONVERTIR_INT_A_CAD(&CAD,NIVEL);
                    CONCATENAR("NIVEL: ",CAD,&Rs);
                    outtextxy(10,10,Rs);

                    CONVERTIR_INT_A_CAD(&CAD,SCORE_LVL*10);
                    CONCATENAR("SCORE: ",CAD,&Rs);
                    outtextxy(10,40,Rs);

                }

                delay(20);

            }
            return 0;
        }

        void MOSTRAR_WI(int x,int y,int e,int YACT,int RANGO){

            for(int n = YACT-RANGO, i = 0;n < YACT+RANGO;n++,i++){
                for (int m = 0,j = 0; m < Xpos; m++,j++){
                    if(n>=0&&n<Ypos){

                        if(*(*(MAP+n)+m)=='*'){
                            DRAW_CUBO(x+e*j,y+e*i,e,80,80,80);
                            DRAW_CAMINO(x+e*j,y+e*i,e);

                        }else if(*(*(MAP+n)+m)=='2'||*(*(MAP+n)+m)=='5'){
                            DRAW_CUBO(x+e*j,y+e*i,e,117,240,35);
                            if(j%2==0){
                                BASE_P.MOSTRAR(0,x+e*j,y+e*i,e,4,74,225,64);
                            }
                            if(j%3==0){
                                BASE_P.MOSTRAR(1,x+e*j,y+e*i,e,3,71,216,55);
                            }
                            if(j%4==0){
                                BASE_P.MOSTRAR(2,x+e*j,y+e*i,e,5,200,215,70);
                            }
                            BASE_P.MOSTRAR(4,x+e*j,y+e*i,e,3,170,255,112);
                            BASE_P.MOSTRAR(5,x+e*j,y+e*i,e,6,180,255 ,65);

                        }else{
                            DRAW_CUBO(x+e*j,y+e*i,e,250,0,0);
                            DEFINE_PARTICULA(e);
                            DRAW_PARTICULAS(x+e*j,y+e*i,e,7,250,100,120);
                            DRAW_PARTICULAS(x+e*j,y+e*i,e,4,250,150,0);
                        }

                        if(n==*(PLAYER1+1)&&m==*(PLAYER1+0)){
                            DRAW_PLAYER(x+e*j+e/2,y+e*i+e/2,e);
                        }
                    }
                }
            }

        }

        void DRAW_CUBO(int x,int y,int e,int R,int G,int B){
            setfillstyle(1,COLOR(R,G,B));
            bar(x,y,x+e,y+e);
        }

        void DRAW_PARTICULAS(int x,int y,int e,int eT,int R,int G,int B){
            for(int i=0;i<TMUESTRA;i++){
                setcolor(COLOR(R,G,B));
                setlinestyle(SOLID_LINE,1,eT);
                line(x+*(*(PARTICULAS+i)+0),y+*(*(PARTICULAS+i)+1),x+*(*(PARTICULAS+i)+0)+1,y+*(*(PARTICULAS+i)+1)+1);
            }
        }

        void DRAW_CAMINO(int x,int y,int e){
            setcolor(0);
            float i=e/4;

            for(int m=0;m<=e;m+=i){
                line(x+m,y,x+m,y+e);
            }

            line(x,y+i,x+i,y+i);
            line(x+2*i,y+i,x+i*3,y+i);

            line(x+i,y,x+i*2,y);
            line(x+i,y+e,x+i*2,y+e);

            line(x+i*3,y,x+i*4,y);
            line(x+i*3,y+e,x+i*4,y+e);

        }

        void DRAW_PLAYER(int x,int y,int e){

            if(DIR_PLAYER==1){
                setcolor(15);
                sector(x,y,0,360,e/4,e/3);

                setcolor(7);
                sector(x,y-e/3,0,360,e/7,e/6);
                sector(x,y+e/3,0,360,e/20,e/20);

                setcolor(15);
                sector(x+e/20,y-e/2.5,0,360,e/80,e/60);
                sector(x-e/20,y-e/2.5,0,360,e/80,e/60);

                setcolor(0);
                line(x+e/20,y-e/2.5,(x+e/20)+1,(y-e/2.5)+1);
                line(x-e/20,y-e/2.5,(x-e/20)+1,(y-e/2.5)+1);

                setcolor(15);
                sector(x+e/8,y-e/3.5,0,360,e/40,e/20);
                sector(x-e/8,y-e/3.5,0,360,e/40,e/20);
            }else if(DIR_PLAYER==2){
                setcolor(15);
                sector(x,y,0,360,e/4,e/3);

                setcolor(7);
                sector(x,y+e/3,0,360,e/7,e/6);
                sector(x,y-e/3,0,360,e/20,e/20);

                setcolor(15);
                sector(x+e/20,y+e/2.5,0,360,e/80,e/60);
                sector(x-e/20,y+e/2.5,0,360,e/80,e/60);

                setcolor(0);
                line(x+e/20,y+e/2.5,(x+e/20)+1,(y+e/2.5)+1);
                line(x-e/20,y+e/2.5,(x-e/20)+1,(y+e/2.5)+1);

                setcolor(15);
                sector(x+e/8,y+e/3.5,0,360,e/40,e/20);
                sector(x-e/8,y+e/3.5,0,360,e/40,e/20);
            }else if(DIR_PLAYER==3){

                setcolor(15);
                sector(x,y,0,360,e/3,e/4);

                setcolor(7);
                sector(x-e/3,y,0,360,e/6,e/7);
                sector(x+e/3,y,0,360,e/20,e/20);

//                OJOS
                setcolor(15);
                sector(x-e/2.5,y+e/20,0,360,e/60,e/80);
                sector(x-e/2.5,y-e/20,0,360,e/60,e/80);

                setcolor(0);
                line(x-e/2.5,y+e/20,(x-e/2.5)+1,(y+e/20)+1);
                line(x-e/2.5,y-e/20,(x-e/2.5)+1,(y-e/20)+1);

//                OREJAS
                setcolor(15);
                sector(x-e/3.5,y+e/8,0,360,e/20,e/40);
                sector(x-e/3.5,y-e/8,0,360,e/20,e/40);

            }else{
                setcolor(15);
                sector(x,y,0,360,e/3,e/4);

                setcolor(7);
                sector(x+e/3,y,0,360,e/6,e/7);
                sector(x-e/3,y,0,360,e/20,e/20);


                //OJOS
                setcolor(15);
                sector(x+e/2.5,y+e/20,0,360,e/60,e/80);
                sector(x+e/2.5,y-e/20,0,360,e/60,e/80);

                setcolor(0);
                line(x+e/2.5,y+e/20,(x+e/2.5)+1,(y+e/20)+1);
                line(x+e/2.5,y-e/20,(x+e/2.5)+1,(y-e/20)+1);

                //OREJAS
                setcolor(15);
                sector(x+e/3.5,y+e/8,0,360,e/20,e/40);
                sector(x+e/3.5,y-e/8,0,360,e/20,e/40);
            }
        }

        void FIN_GAME(bool V){
            setfillstyle(1,COLOR(0,0,0));
            bar(0,0,ScreenX,ScreenY);
            if(V){
                setcolor(10);
                settextstyle(2, HORIZ_DIR, 15);
                outtextxy(280,100,"YOU WIN");
                PlaySound(TEXT("WIN.wav"), NULL,SND_ASYNC);
            }else{
                setcolor(12);
                settextstyle(2, HORIZ_DIR, 15);
                outtextxy(245,100,"GAME OVER");
                PlaySound(TEXT("LOSE.wav"), NULL,SND_ASYNC);
            }

            settextstyle(10, HORIZ_DIR,2);
            char *Rs,*CAD;
            CONVERTIR_INT_A_CAD(&CAD,SCORE_LVL*10);
            CONCATENAR("SCORE: ",CAD,&Rs);
            outtextxy(330,320,Rs);

            setcolor(10);
            settextstyle(10, HORIZ_DIR,3);
            outtextxy(120,700,"PRESIONA CUALQUIER TECLA PARA CONTINUAR");
            setcolor(12);
            settextstyle(10, HORIZ_DIR,1);
            outtextxy(320,730,"ESC PARA SALIR");
            delay(2000);
        }

        int GET_SCORE(){
            return SCORE_LVL;
        }
};

int main(){

    initwindow(ScreenX,ScreenY);
    float PARTICION_VENTANA;

    int Bloques = 6;
    int Velocidad = 40;
    int DensidadDeParticulas;

    setcolor(10);
    settextstyle(2, HORIZ_DIR,15);
    outtextxy(20,35,"EL SUELO ES LAVA");
    settextstyle(10, HORIZ_DIR,3);
    outtextxy(25,90,"BY: Alex Escalante");

    settextstyle(10, HORIZ_DIR,1);
    outtextxy(25,120,"CONTROLES: W A S D");
    settextstyle(10, HORIZ_DIR,3);
    outtextxy(185,700,"PRESIONA ENTER PARA CONTINUAR");

    setcolor(12);
    settextstyle(10, HORIZ_DIR,1);
    outtextxy(300,730,"ESC PARA SALIR");

    PlaySound(TEXT("STAR.wav"), NULL,SND_ASYNC|SND_LOOP);

    while(getch()!=ESC){

        char *Rs,*CAD;
        setfillstyle(1,COLOR(0,0,0));
        bar(0,0,ScreenX,ScreenY);
        settextstyle(2, HORIZ_DIR, 15);
        setcolor(10);

        CONVERTIR_INT_A_CAD(&CAD,NIVEL);
        CONCATENAR("NIVEL ",CAD,&Rs);
        outtextxy(310,100,Rs);

        settextstyle(10, HORIZ_DIR, 2);
        CONVERTIR_INT_A_CAD(&CAD,SCORE*10);
        CONCATENAR("SCORE TOTAL: ",CAD,&Rs);
        outtextxy(305,160,Rs);

        delay(3000);

        if(Bloques<10){
            DensidadDeParticulas = 4;
        }else if(Bloques<15){
            DensidadDeParticulas = 3;
        }else if(Bloques<20){
            DensidadDeParticulas = 2;
        }else{
            DensidadDeParticulas = 1;
        }

        PARTICION_VENTANA = (ScreenX/Bloques);

        GAME A(Bloques,Bloques*5,3,DensidadDeParticulas);
        BASE_P.DEFINIR_PARAMETROS(DensidadDeParticulas+1,PARTICION_VENTANA);

        if(A.CONTROLES(0,80,PARTICION_VENTANA,Bloques/2,Velocidad)){
            Bloques++;
            NIVEL++;
            SCORE += A.GET_SCORE();
            if(NIVEL<=8){
                Velocidad-=5;
            }
        }

        int Sound = rand()%5;
        while(MUSIC==Sound){  //SELECCIONA SOUNDTRACK
            Sound = rand()%5;
        }
        MUSIC = Sound;

        CONVERTIR_INT_A_CAD(&CAD,MUSIC);
        CONCATENAR(CAD,"M.wav",&Rs);
        PlaySound(TEXT(Rs), NULL,SND_ASYNC|SND_LOOP);
    }

    closegraph();
    return 0;
}
