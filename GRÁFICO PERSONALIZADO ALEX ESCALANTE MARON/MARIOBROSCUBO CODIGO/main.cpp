#include <iostream>
#include <fstream>
#include <winbgim.h>

using namespace std;

void MARIOSORPRESA(int x,int y,int e,int R,int G,int B){

    setfillstyle(1,COLOR(R,G,B));//CUBO BASE
    bar(x-6*e,y-6*e,x+6*e,y+6*e);

    setfillstyle(1,COLOR(255,100,0));//BORDE NARANJA
    bar(x-6*e,y-7*e,x+6*e,y-6*e);
    bar(x-7*e,y-6*e,x-6*e,y+6*e);

    setfillstyle(1,0);//BORDE NEGRO
    bar(x-7*e,y+7*e,x+6*e,y+6*e);
    bar(x+7*e,y-6*e,x+6*e,y+7*e);

    setfillstyle(1,0);//PUNTOS
    bar(x-5*e,y-5*e,x-4*e,y-4*e);
    bar(x+5*e,y+5*e,x+4*e,y+4*e);
    bar(x+5*e,y-5*e,x+4*e,y-4*e);
    bar(x-5*e,y+5*e,x-4*e,y+4*e);

    setfillstyle(1,0);//PREGUNTA SOMBRA
    bar(x-e*1.5,y-4*e,x,y-e);
    bar(x,y-e*3,x+e*2.5,y-e*2);
    bar(x+e*1.5,y-e*2,x+e*3.2,y+e*0.75);
    bar(x,y,x+e*1.5,y+e*2);
    bar(x,y+e*2.5,x+e*1.5,y+e*4);

    setfillstyle(1,COLOR(255,100,0));//PREGUNTA
    bar(x,y-e,x+e*2.5,y);
    bar(x+e,y,x+e*2.5,y-3*e);
    bar(x-e*1.5,y-4*e,x+2*e,y-3*e);
    bar(x-2*e,y-3*e,x-e*0.75,y-e*1.5);

    bar(x-e*0.75,y,x+e*0.75,y+1.5*e);
    bar(x-e*0.75,y+e*2,x+e*0.75,y+3.5*e);
}


int main(){

    initwindow(1100,450);
    bar(0,0,1100,450);

    MARIOSORPRESA(100,200,5,255,150,250);
    MARIOSORPRESA(250,200,10,255,250,0);
    MARIOSORPRESA(500,200,15,255,200,0);
    MARIOSORPRESA(850,200,20,255,150,0);

    getch();
    closegraph();
    return 0;
}
