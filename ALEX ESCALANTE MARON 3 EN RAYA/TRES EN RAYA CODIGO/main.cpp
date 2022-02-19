#include <iostream>
#include <stdio.h>
#include <windows.h>
#include <winbgim.h>

#define IZQUIERDA 97
#define DERECHA   100
#define ARRIBA    119
#define ABAJO     115
#define INTRO     13
#define ESC       27

using namespace std;

bool GAMEOVER;

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

int CONVERTIR_INT_A_CAD(char **R,long long NUM){int TAM=0,i=0;
    for(long long AUX=NUM;AUX!=0;i++,AUX/=10);
    *R = new char [i];TAM=i;*(*(R)+i)='\0';i-=1;
    for(;i>=0;i--,NUM/=10){
        *(*(R)+i)=(char)(NUM%10+48);
    }
    return TAM;
}

class TRESENRAYA{
    char **MRAYA;
    int Mx,My,VPOSX,VPOSY, TAM;
    int CONTPLAYER1,CONTPLAYER2;
    bool PLAYER,VCURSOR;
    public:
    TRESENRAYA(){
        MRAYA = new char*[3];
        for(int i=0;i<3;i++){
            *(MRAYA+i) = new char[3];
        }
        CONTPLAYER1 = 0,CONTPLAYER2 = 0;
    }
    void INICIALIZACION(){
        for(int i=0;i<3;i++){
            for(int j=0;j<3;j++){
                *(*(MRAYA + i)+j) = '*';
            }
        }
        Mx = 1,My = 1,PLAYER = 1,VCURSOR = 1;GAMEOVER=1;
        *(*(MRAYA + My)+Mx) = '+';
    }

    void DEFINEVISUAL(int Px,int Py,int T){
        VPOSX = Px;
        VPOSY = Py;
        TAM  = T;
    }
    bool VALIDAPOS(int X,int Y){
        if(X>=0&&X<3&&Y>=0&&Y<3){
            if(*(*(MRAYA+X)+Y)!='X'&&*(*(MRAYA+X)+Y)!='O'){
                return 1;
            }
        }
        return 0;
    }
    bool VALIDAEXCEPC(){
        for(int i = 0; i<3 ; i++){
            for(int j = 0; j<3 ; j++){
                if(i+j==1||i-j==1||j-i==1){
                    if(!(*(*(MRAYA + i)+j)!='*'&&*(*(MRAYA + i)+j)!='+')){
                        return 0;
                    }
                }
            }
        }
        if(MRAYA[1][1]!='*'){
            return 0;
        }
        return 1;
    }
    void AVANCE(int DIR){
        if(DIR==1){
            for(int i=1;i<=2;i++){
                if(VALIDAPOS(My,Mx-i)){
                    *(*(MRAYA + My)+Mx) = '*';
                    Mx-=i;
                    *(*(MRAYA + My)+Mx) = '+';
                    return;
                }
            }
            for(int i=0;i<3;i++){
                for(int j=Mx;j>=0;j--){
                    if(i!=My&&j!=Mx){
                        if(VALIDAPOS(i,j)){
                            *(*(MRAYA + My)+Mx) = '*';
                            My=i,Mx=j;*(*(MRAYA + My)+Mx) = '+';return;
                        }
                    }
                }
            }
        }
        if(DIR==2){
            for(int i=1;i<=2;i++){
                if(VALIDAPOS(My,Mx+i)){
                    *(*(MRAYA + My)+Mx) = '*';
                    Mx+=i;
                    *(*(MRAYA + My)+Mx) = '+';
                    return;
                }
            }
            for(int i=0;i<3;i++){
                for(int j=Mx;j<3;j++){
                    if(i!=My&&j!=Mx){
                        if(VALIDAPOS(i,j)){
                            *(*(MRAYA + My)+Mx) = '*';
                            My=i,Mx=j;*(*(MRAYA + My)+Mx) = '+';return;
                        }
                    }
                }
            }
        }
        if(DIR==3){
            for(int i=1;i<=2;i++){
                if(VALIDAPOS(My-i,Mx)){
                    *(*(MRAYA + My)+Mx) = '*';
                    My-=i;
                    *(*(MRAYA + My)+Mx) = '+';
                    return;
                }
            }
            for(int i=My;i>=0;i--){
                for(int j=0;j<3;j++){
                    if(i!=My&&j!=Mx){
                        if(VALIDAPOS(i,j)){
                            *(*(MRAYA + My)+Mx) = '*';
                            My=i,Mx=j;*(*(MRAYA + My)+Mx) = '+';return;
                        }
                    }
                }
            }
        }
        if(DIR==4){
            for(int i=1;i<=2;i++){
                if(VALIDAPOS(My+i,Mx)){
                    *(*(MRAYA + My)+Mx) = '*';
                    My+=i;
                    *(*(MRAYA + My)+Mx) = '+';
                    return;
                }
            }
            for(int i=My;i<3;i++){
                for(int j=0;j<3;j++){
                    if(i!=My&&j!=Mx){
                        if(VALIDAPOS(i,j)){
                            *(*(MRAYA + My)+Mx) = '*';
                            My=i,Mx=j;*(*(MRAYA + My)+Mx) = '+';return;
                        }
                    }
                }
            }
        }
        if(VALIDAEXCEPC()){
            *(*(MRAYA + My)+Mx) = '*';
            My=1,Mx=1;
            *(*(MRAYA + My)+Mx) = '+';
            return;
        }
        return;
    }
    bool CURSORDISPONIBLE(){
        for(int i=0;i<3;i++){
            for(int j=0;j<3;j++){
                if(VALIDAPOS(i,j)){My=i,Mx=j;*(*(MRAYA + My)+Mx) = '+';return 1;}
            }
        }
        return 0;
    }
    void CURSOR(int x,int y,int e,int color){
        if(PLAYER){
            X(x,y,e*0.3,color);
        }else{
            O(x,y,e*0.3,color);
        }
    }
    void X(int x,int y,int e,int color){
        setcolor(color);
        setlinestyle(SOLID_LINE,1,TAM/8);
        line(x-e,y-e,x+e,y+e);
        line(x-e,y+e,x+e,y-e);
    }
    void O(int x,int y,int e,int color){
        setcolor(color);
        setlinestyle(SOLID_LINE,1,TAM/8);
        circle(x,y,e);
    }
    void MAPA(int x,int y,int e,int color){
        setcolor(color);
        setlinestyle(SOLID_LINE,1,TAM/8);
        line(x-e,y-3*e,x-e,y+3*e);
        line(x+e,y-3*e,x+e,y+3*e);
        line(x-3*e,y-e,x+3*e,y-e);
        line(x-3*e,y+e,x+3*e,y+e);
    }
    void VISUAL(){
        MAPA(VPOSX,VPOSY,TAM,4);
        if(VCURSOR){
            CURSOR(VPOSX-TAM*4+((Mx+1)*TAM*2),VPOSY-TAM*4+((My+1)*TAM*2),TAM,14);
        }
        for(int i=0;i<3;i++){
            for(int j=0;j<3;j++){
                if(*(*(MRAYA + i)+j)=='X'){
                    X(VPOSX-TAM*2+j*TAM*2,VPOSY-TAM*2+i*TAM*2,TAM*0.5,11);
                }
                if(*(*(MRAYA + i)+j)=='O'){
                    O(VPOSX-TAM*2+j*TAM*2,VPOSY-TAM*2+i*TAM*2,TAM*0.5,10);
                }
            }
        }
    }
    void VISUALWIN(int *WIN){
        char *CAD2,*CAD3;
        settextstyle(2, HORIZ_DIR, 15);
        if(*WIN == 1){
            outtextxy(VPOSX-200,VPOSY-100,"GANA PLAYER 2");
        }else if(*WIN == 2){
            outtextxy(VPOSX-200,VPOSY-100,"GANA PLAYER 1");
        }else{
            outtextxy(VPOSX-120,VPOSY-100,"EMPATE!!");
        }

        settextstyle(2, HORIZ_DIR, 5);
        if(CONTPLAYER1){
            CONVERTIR_INT_A_CAD(&CAD3,CONTPLAYER1);
            CONCATENAR("S C O R E   P L A Y E R 2:   ",CAD3,&CAD2); //PLAYER2
            outtextxy(VPOSX-80,VPOSY+250,"S C O R E   P L A Y E R 1:   0");
            outtextxy(VPOSX-80,VPOSY+265,CAD2);
        }else if(CONTPLAYER2){
            CONVERTIR_INT_A_CAD(&CAD3,CONTPLAYER2);
            CONCATENAR("S C O R E   P L A Y E R 1:    ",CAD3,&CAD2);
            outtextxy(VPOSX-80,VPOSY+250,CAD2);
            outtextxy(VPOSX-80,VPOSY+265,"S C O R E   P L A Y E R 2:   0");
        }
        outtextxy(VPOSX-180,VPOSY+350,"PRESIONE UNA TECLA PARA CONTINUAR O ESC PARA SALIR");
    }
    bool CONTROL(){
        int WIN = 0;
        while(1){

            VISUAL();
            if(!VCURSOR){
                settextstyle(2, HORIZ_DIR, 5);
                outtextxy(VPOSX-170,VPOSY+350,"PRESIONE ENTRAR PARA CONTINUAR O ESC PARA SALIR");
            }
            switch(LMAYUS(getch())){

                case IZQUIERDA:
                    AVANCE(1);
                    break;
                case DERECHA:
                    AVANCE(2);
                    break;
                case ARRIBA:
                    AVANCE(3);
                    break;
                case ABAJO:
                    AVANCE(4);
                    break;
                case INTRO:
                    if(VCURSOR){
                        if(PLAYER){
                            *(*(MRAYA + My)+Mx) = 'X';PLAYER = 0;
                            VCURSOR = CURSORDISPONIBLE();
                        }else{
                            *(*(MRAYA + My)+Mx) = 'O';PLAYER = 1;
                            VCURSOR = CURSORDISPONIBLE();
                        }
                    }else{
                        cleardevice();

                        VISUALWIN(&WIN);
                        return 1;
                    }
                    if(!GANADOR(&WIN)){VCURSOR = 0;}
                    break;
                case ESC:
                    return 0;
            }
            cleardevice();
        }
    }
    bool GANADOR(int *WIN){
        char PLYS[2] = {'O','X'};
        for(int M=0;M<2;M++){
            bool V1=1,V2=1,V3=1,V4=1;
            for(int i=0;i<3;i++){
                for(int j=0;j<3;j++){
                    if(V1){
                        if(MRAYA[j][i]!=PLYS[M]){
                            V1 = 0;
                        }
                    }
                    if(V2){
                        if(*(*(MRAYA + i)+j)!=PLYS[M]){
                            V2 = 0;
                        }
                    }
                    if(i==j){
                        if(*(*(MRAYA + i)+j)!=PLYS[M]){
                            V3 = 0;
                        }
                    }
                    if(i+j==2){
                        if(*(*(MRAYA + i)+j)!=PLYS[M]){
                            V4 = 0;
                        }
                    }
                }
                if(V1||V2){
                    *WIN = M+1;
                    if(*WIN==1){
                        CONTPLAYER1++;
                        CONTPLAYER2=0;
                    }
                    else if(*WIN==2){
                        CONTPLAYER2++;
                        CONTPLAYER1=0;
                    }
                    if(CONTPLAYER1>12||CONTPLAYER2>12){
                        PLAYWIN(12);
                    }else{
                        if(CONTPLAYER1){
                            PLAYWIN(CONTPLAYER1);
                        }
                        else if(CONTPLAYER2){
                            PLAYWIN(CONTPLAYER2);
                        }
                    }

                    return 0;
                }
                V1 = V2 = 1;
            }
            if(V3||V4){
                *WIN = M+1;
                if(*WIN==1){
                    CONTPLAYER1++;
                    CONTPLAYER2=0;
                }
                else if(*WIN==2){
                    CONTPLAYER2++;
                    CONTPLAYER1=0;
                }
                if(CONTPLAYER1>12||CONTPLAYER2>12){
                    PLAYWIN(12);
                }else{
                    if(CONTPLAYER1){
                        PLAYWIN(CONTPLAYER1);
                    }
                    else if(CONTPLAYER2){
                        PLAYWIN(CONTPLAYER2);
                    }
                }
                return 0;
            }
        }
        if(!VCURSOR){PlaySound(TEXT("0.wav"), NULL,SND_ASYNC );}
        return 1;
    }
    void PLAYWIN(int PLAYM){
        char *CAD2,*CAD3;
        CONVERTIR_INT_A_CAD(&CAD3,PLAYM);
        CONCATENAR(CAD3,".wav",&CAD2);
        PlaySound(TEXT(CAD2), NULL,SND_ASYNC );
    }

}A;

int main(){

    printf("DIRECCIONES : { A , D , W , S }\n");
    printf("ACCION      : { ENTRAR }\n");
    printf("SALIR       : { ESC }\n");

    A.DEFINEVISUAL(350,350,110);
    A.INICIALIZACION();

    char *CAD2,*CAD3;
    int PLAYSOUND = 2;
    PlaySound(TEXT("1M.wav"), NULL,SND_ASYNC|SND_LOOP);

    initwindow(710,730);

    while(A.CONTROL()){

        if(PLAYSOUND>4){PLAYSOUND = 1;}
        CONVERTIR_INT_A_CAD(&CAD3,PLAYSOUND);PLAYSOUND++;
        CONCATENAR(CAD3,"M.wav",&CAD2);
        PlaySound(TEXT(CAD2), NULL,SND_ASYNC|SND_LOOP);

        switch(getch()){
            case ESC:
                closegraph();
                return 0;
            default:
                cleardevice();
                A.INICIALIZACION();
        }
    }
}
