#include<windows.h>
#include<iostream>
#include<conio.h>
#include<stdlib.h>
#include<stdio.h>

using namespace std;
int x=10,y=12,xc=30,yc=15,velocidad=100,i,j,k,l,xs,ys;
char tecla[3][3],tecla2[3][3];

void gotoxy(int x,int y){
		HANDLE hCon;
		COORD dwPos;

		dwPos.X= x;
		dwPos.Y= y;
		hCon =GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleCursorPosition(hCon, dwPos);
	}
void eliminar_arreglo(){
        for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            tecla[i][j]='a';
        }
    }
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            tecla2[i][j]='v';
        }
    }
}
void gana(){
   gotoxy(60,15);cout<<"********    *********    *****    ***    *********";
   gotoxy(60,16);cout<<"********   ***********   *****    ***   ***********";
   gotoxy(60,17);cout<<"***        ****   ****   ******   ***   ****   ****";
   gotoxy(60,18);cout<<"***  ***   ***********   *** ***  ***   ***********";
   gotoxy(60,19);cout<<"***  ***   ***********   ***  *** ***   ***********";
   gotoxy(60,20);cout<<"********   ****   ****   ***   ******   ****   ****";
   gotoxy(60,21);cout<<"********   ****   ****   ***    *****   ****   ****";
   gotoxy(47,24);cout<<"      ***   ***   ***   ********    *******    ******     *******    *******";
   gotoxy(47,25);cout<<"      ***   ***   ***   ********   *********   *******   *********   ********";
   gotoxy(47,26);cout<<"      ***   ***   ***   ***        ***   ***   ***  ***  ***   ***   ***  ***";
   gotoxy(47,27);cout<<"***   ***   ***   ***   ***  ***   *********   ***  ***  ***   ***   *******";
   gotoxy(47,28);cout<<"***   ***   ***   ***   ***  ***   *********   ***  ***  ***   ***   *******";
   gotoxy(47,29);cout<<"*********   *********   ********   ***   ***   *******   *********   ***  ***";
   gotoxy(47,30);cout<<"*********   *********   ********   ***   ***   ******     *******    ***   ***";
}
void image_gana_j1(){
    gotoxy(80,33);cout<<"  *****";
    gotoxy(80,34);cout<<" ******";
    gotoxy(80,35);cout<<"*** ***";
    gotoxy(80,36);cout<<"    ***";
    gotoxy(80,37);cout<<"    ***";
    gotoxy(80,38);cout<<"    ***";
    gotoxy(80,39);cout<<"    ***";
    gotoxy(1,55);cout<<"";
}
void image_gana_j2(){
    gotoxy(80,33);cout<<" ******";
    gotoxy(80,34);cout<<"********";
    gotoxy(80,35);cout<<"**   ***";
    gotoxy(80,36);cout<<"    ***";
    gotoxy(80,37);cout<<"   ***";
    gotoxy(80,38);cout<<" *******";
    gotoxy(80,39);cout<<" *******";
    gotoxy(1,55);cout<<"";
}
void equis(){

   gotoxy(xs,ys);cout<<"****   ****";
   gotoxy(xs,ys+1);cout<<" **** ****";
   gotoxy(xs,ys+2);cout<<"  *******";
   gotoxy(xs,ys+3);cout<<"   *****";
   gotoxy(xs,ys+4);cout<<"  *******";
   gotoxy(xs,ys+5);cout<<" **** ****";
   gotoxy(xs,ys+6);cout<<"****   ****";
}
void cero(){
   gotoxy(xs,ys);cout<<" ********";
   gotoxy(xs,ys+1);cout<<"**********";
   gotoxy(xs,ys+2);cout<<"***    ***";
   gotoxy(xs,ys+3);cout<<"***    ***";
   gotoxy(xs,ys+4);cout<<"***    ***";
   gotoxy(xs,ys+5);cout<<"**********";
   gotoxy(xs,ys+6);cout<<" ********";
}
void pintar(){

        for(int i=35,j=0;j<100;j++,i++)
    	{
    		gotoxy(i,18); printf("%c",219);
    		gotoxy(i,19); printf("%c",219);
    		gotoxy(i,20); printf("%c",219);

    		gotoxy(i,38);printf("%c",219);
    		gotoxy(i,39);printf("%c",219);
    		gotoxy(i,40);printf("%c",219);
    	}
    	for(int i=4,j=0;j<50;j++,i++)
	    {
    		gotoxy(65,i); printf("%c",219);
    		gotoxy(66,i); printf("%c",219);
    		gotoxy(67,i); printf("%c",219);
    		gotoxy(68,i); printf("%c",219);
    		gotoxy(69,i); printf("%c",219);

    		gotoxy(100,i);printf("%c",219);
    		gotoxy(101,i);printf("%c",219);
    		gotoxy(102,i);printf("%c",219);
    		gotoxy(103,i);printf("%c",219);
    		gotoxy(104,i);printf("%c",219);
     	}
     	gotoxy(50,2);cout<<"0";
     	gotoxy(84,2);cout<<"1";
     	gotoxy(120,2);cout<<"2";

     	gotoxy(30,11);cout<<"0";
     	gotoxy(30,29);cout<<"1";
     	gotoxy(30,47);cout<<"2";
}
void ganaj1(){
    system("cls");
      gana();
      image_gana_j1();
      system("pause");
      system("cls");
      eliminar_arreglo();
      pintar();
}
void imprimir_jugador1(){

    if(i==0&&j==0){
       xs=45;ys=8;
       equis();
    }
    if(i==0&&j==1){
       xs=80;ys=8;
       equis();
    }
    if(i==0&&j==2){
        xs=115;ys=8;
        equis();
    }
    if(i==1&&j==0){
        xs=45;ys=26;
        equis();
    }
    if(i==1&&j==1){
        xs=80;ys=26;
        equis();
    }
    if(i==1&&j==2){
        xs=115;ys=26;
        equis();
    }
    if(i==2&&j==0){
        xs=45;ys=44;
        equis();
    }
    if(i==2&&j==1){
        xs=80;ys=44;
        equis();
    }
    if(i==2&&j==2){
        xs=115;ys=44;
        equis();
    }

}
void jugador1_compro(){
    if(i==0&&j==0){gotoxy(3,15);cout<<"X";}
    if(i==0&&j==1){gotoxy(5,15);cout<<"X";}
    if(i==0&&j==2){gotoxy(7,15);cout<<"X";}
    if(i==1&&j==0){gotoxy(3,17);cout<<"X";}
    if(i==1&&j==1){gotoxy(5,17);cout<<"X";}
    if(i==1&&j==2){gotoxy(7,17);cout<<"X";}
    if(i==2&&j==0){gotoxy(3,19);cout<<"X";}
    if(i==2&&j==1){gotoxy(5,19);cout<<"X";}
    if(i==2&&j==2){gotoxy(7,19);cout<<"X";}
}
void jugador1_gana(){

    ///horizontal
    if(tecla[0][0]=='x'&&tecla[0][1]=='x'&&tecla[0][2]=='x'){
      ganaj1();
    }
    if(tecla[1][0]=='x'&&tecla[1][1]=='x'&&tecla[1][2]=='x'){
      ganaj1();
    }
    if(tecla[2][0]=='x'&&tecla[2][1]=='x'&&tecla[2][2]=='x'){
      ganaj1();
    }
    ///en X
    if(tecla[2][0]=='x'&&tecla[1][1]=='x'&&tecla[0][2]=='x'){
      ganaj1();
    }
    if(tecla[0][0]=='x'&&tecla[1][1]=='x'&&tecla[2][2]=='x'){
      ganaj1();
    }
    ///vertical
    if(tecla[0][0]=='x'&&tecla[1][0]=='x'&&tecla[2][0]=='x'){
      ganaj1();
    }
    if(tecla[0][1]=='x'&&tecla[1][1]=='x'&&tecla[2][1]=='x'){
      ganaj1();
    }
    if(tecla[0][2]=='x'&&tecla[1][2]=='x'&&tecla[2][2]=='x'){
      ganaj1();
    }
}
void introdu_j1(){
    gotoxy(3,2);cout<<"INGRESE JUGADOR  1:";
    gotoxy(3,4);cout<<"COORDENADA  "<<(char)25<<":   "<<(char)26<<":";
    gotoxy(3,6);cout<<"INGRESE JUGADOR  2:";
    gotoxy(3,8);cout<<"COORDENADA  "<<(char)25<<":   "<<(char)26<<":";
    gotoxy(140,2);cout<<"JUGADOR 1= X";
    gotoxy(140,4);cout<<"JUGADOR 2= O";
    gotoxy(18,4);cin>>i;gotoxy(23,4);cin>>j;
    tecla[i][j]='x';
}
void ganaj2(){
      system("cls");
      gana();
      image_gana_j2();
      system("pause");
      system("cls");
      eliminar_arreglo;
      pintar();
}
void imprimir_jugador2(){
    if(k==0&&l==0){
        xs=45;ys=8;
        cero();
    }
    if(k==0&&l==1){
        xs=80;ys=8;
        cero();
    }
    if(k==0&&l==2){
        xs=115;ys=8;
        cero();
    }
    if(k==1&&l==0){
        xs=45;ys=26;
        cero();
    }
    if(k==1&&l==1){
        xs=80;ys=26;
        cero();
    }
    if(k==1&&l==2){
        xs=115;ys=26;
        cero();
    }
    if(k==2&&l==0){
        xs=45;ys=44;
        cero();
    }
    if(k==2&&l==1){
        xs=80;ys=44;
        cero();
    }
    if(k==2&&l==2){
        xs=115;ys=44;
        cero();
    }
}
void jugador2_compro(){
    if(k==0&&l==0){gotoxy(3,23);cout<<"O";}
    if(k==0&&l==1){gotoxy(5,23);cout<<"O";}
    if(k==0&&l==2){gotoxy(7,23);cout<<"O";}
    if(k==1&&l==0){gotoxy(3,25);cout<<"O";}
    if(k==1&&l==1){gotoxy(5,25);cout<<"O";}
    if(k==1&&l==2){gotoxy(7,25);cout<<"O";}
    if(k==2&&l==0){gotoxy(3,27);cout<<"O";}
    if(k==2&&l==1){gotoxy(5,27);cout<<"O";}
    if(k==2&&l==2){gotoxy(7,27);cout<<"O";}
}
void jugador2_gana(){

    ///horizontal
    if(tecla2[0][0]=='x'&&tecla2[0][1]=='x'&&tecla2[0][2]=='x'){
      ganaj2();
    }
    if(tecla2[1][0]=='x'&&tecla2[1][1]=='x'&&tecla2[1][2]=='x'){
       ganaj2();
    }
    if(tecla2[2][0]=='x'&&tecla2[2][1]=='x'&&tecla2[2][2]=='x'){
       ganaj2();
    }
    ///en X
    if(tecla2[2][0]=='x'&&tecla2[1][1]=='x'&&tecla2[0][2]=='x'){
       ganaj2();
    }
    if(tecla2[0][0]=='x'&&tecla2[1][1]=='x'&&tecla2[2][2]=='x'){
       ganaj2();
    }
    ///vertical
    if(tecla2[0][0]=='x'&&tecla2[1][0]=='x'&&tecla2[2][0]=='x'){
       ganaj2();
    }
    if(tecla2[0][1]=='x'&&tecla2[1][1]=='x'&&tecla2[2][1]=='x'){
       ganaj2();
    }
    if(tecla2[0][2]=='x'&&tecla2[1][2]=='x'&&tecla2[2][2]=='x'){
       ganaj2();
    }
}
void introdu_j2(){
    gotoxy(3,2);cout<<"INGRESE JUGADOR  1:";
    gotoxy(3,4);cout<<"COORDENADA  "<<(char)25<<":   "<<(char)26<<":";
    gotoxy(3,6);cout<<"INGRESE JUGADOR  2:";
    gotoxy(3,8);cout<<"COORDENADA  "<<(char)25<<":   "<<(char)26<<":";
    gotoxy(140,2);cout<<"JUGADOR 1= X";
    gotoxy(140,4);cout<<"JUGADOR 2= O";
    gotoxy(18,8);cin>>k;gotoxy(23,8);cin>>l;
    tecla2[k][l]='x';
}
void cordenadas_llenas(){
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            tecla[i][j]='h';
        }
    }
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            tecla2[i][j]='g';
        }
    }
}
void validacion_de_cordenadas1(){
    string s;
    for(int i=0;i<=3;i++){
        for(int j=0;j<=3;j++){
            if(tecla[i][j]=='x'&&tecla2[i][j]=='x'){
              s="no";
            }

        }
    }
    if(s=="no"){
        gotoxy(18,4);cout<<"  ";gotoxy(23,4);cout<<"  ";
        gotoxy(18,4);cin>>i;gotoxy(23,4);cin>>j;
        validacion_de_cordenadas1();
    }
}
void validacion_de_cordenadas2(){
    string m;
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            if(tecla[i][j]=='x'&&tecla2[i][j]=='x'){
              m="si";
            }
        }
    }
    if(m=="si"){
        gotoxy(18,8);cout<<"  ";gotoxy(23,8);cout<<"  ";
        gotoxy(18,8);cin>>k;gotoxy(23,8);cin>>l;
    }
}
bool fin_juego(){
}
void AltEnter(){           ///pantalla completa

    keybd_event(VK_MENU,
                0x38,
                0,
                0);
    keybd_event(VK_RETURN,
                0x1c,
                0,
                0);
    keybd_event(VK_RETURN,
                0x1c,
                KEYEVENTF_KEYUP,
                0);
    keybd_event(VK_MENU,
                0x38,
                KEYEVENTF_KEYUP,
                0);
    return;
}
void pr(){
    for(int i=0,j=67;i<40;i++,j++){
        gotoxy(j,8);cout<<(char)219;
        gotoxy(j,17);cout<<(char)219;
    }
    for(int i=0,j=2;i<22;i++,j++){
        gotoxy(78,j);cout<<(char)219;
        gotoxy(79,j);cout<<(char)219;
        gotoxy(93,j);cout<<(char)219;
        gotoxy(94,j);cout<<(char)219;
    }
}
void presentacion(){
     gotoxy(40,28);cout<<" *******       ********   *****     ***      *********   *********  ****    ****  *********";
     gotoxy(40,29);cout<<"*********      *********  *****     ***      **********  *********  ****    ****  *********";
     gotoxy(40,30);cout<<"      ***      ***        ******    ***      ***   ****  ***   ***   ****  ****   ***   ***";
     gotoxy(40,31);cout<<"      ***      ***        *******   ***      ***   ****  ***   ***    ********    ***   ***";
     gotoxy(40,32);cout<<"********       *********  *** ****  ***      *********   *********     ******     *********";
     gotoxy(40,33);cout<<"********       *********  ***  **** ***      *******     *********      ****      *********";
     gotoxy(40,34);cout<<"      ***      ***        ***   *******      *******     ***   ***      ****      ***   ***";
     gotoxy(40,35);cout<<"      ***      ***        ***    ******      *** ****    ***   ***      ****      ***   ***";
     gotoxy(40,36);cout<<"*********      *********  ***     *****      ***  ****   ***   ***      ****      ***   ***";
     gotoxy(40,37);cout<<" *******       ********   ***     *****      ***   ****  ***   ***      ****      ***   ***";
}
void alex(){
        gotoxy(55,40);printf("********   ***  ***   ***    ******   ***     ******  ***  ***");
        gotoxy(55,41); cout<<"**    **   ***  ***   ***   ********  ***     **       ******";
        gotoxy(55,42); cout<<"*******     ******          ***  ***  ***     ****      ****";
        gotoxy(55,43); cout<<"**    **     ****     ***   ********  ******  **       ******";
        gotoxy(55,44); cout<<"********     ****     ***   ***  ***  ******  ******  ***  ***\n\n\n";
}
void carga(){
    for(int i=36,j=0;j<=100;i++,j++)
    {
        gotoxy(i,48);cout<<"\262";
        gotoxy(i,49);cout<<"\262";
        gotoxy(69,52);cout<<"  ESPERE MIENTRAS CARGA  "<<j<<"%";

        Sleep(60);
    }
    gotoxy(69,52);cout<<"        CARGA COMPLETADA ";
    gotoxy(70,54);cout<<"";
    system("pause");
}
void inicio(){
    AltEnter();
    system("color f4");
    presentacion();alex();pr();carga();
    system("cls");
}
void juego(){
    	while(true){
            introdu_j1();
            ///validacion_de_cordenadas1();
            imprimir_jugador1();
            jugador1_gana();
            jugador1_compro();
            gotoxy(23,4);cout<<"    ";
            introdu_j2();
            ///validacion_de_cordenadas2();
            imprimir_jugador2();
            jugador2_gana();
            jugador2_compro();
            gotoxy(23,8);cout<<"    ";
    	}
        system("pause>null");

}
int main(){
    inicio();
    system("color f9");
    cordenadas_llenas();
    pintar();
    juego();
    return 0;
}
