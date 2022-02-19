#include<windows.h>
#include<iostream>
#include<conio.h>
#include<stdlib.h>
#include<stdio.h>

using namespace std;

#define ARRIBA     72     //numeros asociados al teclado
#define IZQUIERDA  75
#define DERECHA    77
#define ABAJO      80
#define ESC        27
#define ENTER      13

int cuerpo[400][2];
int n=1;
int tam=3;
int x=10;
int y=12;
int dir=3;
int xc=30,yc=15;
int velocidad,h=1;
int score=0;
int largo,ancho;
int tama;
int dificu;
int incre;
int confirmar;
int asd=13;
int perso;
int velo;


char tecla;


void gotoxy(int x,int y){        //funcion que posiciona  IMPORTANTE GOTOXY POSICION GRAFICA

		HANDLE hCon;
		COORD dwPos;

		dwPos.X= x;
		dwPos.Y= y;
		hCon =GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleCursorPosition(hCon, dwPos);
	}

void pintar(){             ///tamaño de cancha
	///lineas orizontales
    for(int i=2;i<ancho;i++)
    	{
    		gotoxy(i,3); printf("%c",223);
    		gotoxy(i,largo);printf("%c",223);

    	}
	///lineas verticales
    for(int i=4;i<largo;i++)
	    {
    		gotoxy(2,i); printf("%c",219);
    		gotoxy(ancho,i);printf("%c",219);

     	}
	///esquinas
	gotoxy(2,3);     printf("%c",219);
	gotoxy(2,largo);    printf("%c",223);
	gotoxy(ancho,3);    printf("%c",219);
	gotoxy(ancho,largo);   printf("%c",223);
}
void guardar_posicion(){
	cuerpo[n][0]=x;
	cuerpo[n][1]=y;
	n++;
	if(n==tam) n=1;
}
void dibujar_cuerpo(){
	for(int i=1;i<tam;i++){
		gotoxy(cuerpo[i][0],cuerpo[i][1]); printf("%c",velo);
	}
}
void borrar_cuerpo(){
		gotoxy(cuerpo[n][0],cuerpo[n][1]); printf(" ");
}
void carga()
{
    for(int i=35,j=0;j<=100;i++,j++)
    {
        gotoxy(i,48);cout<<"\262";
        gotoxy(i,49);cout<<"\262";
        gotoxy(68,52);cout<<"  ESPERE MIENTRAS CARGA  "<<j<<"%";

        Sleep(30);
    }
    gotoxy(68,52);cout<<"        CARGA COMPLETADA ";
    gotoxy(70,54);cout<<"";
    system("pause");
}
void teclear(){                 ///teclado
		if(kbhit()){
			tecla=getch();
			switch(tecla){
				case ARRIBA:{
					if(dir !=2)
				    dir=1;
					break;
				}
				case ABAJO:{
					if(dir !=1)
					dir=2;
					break;
				}
				case DERECHA:{
					if(dir !=4)
					dir=3;
					break;
				}
				case IZQUIERDA:{
					if(dir !=3)
					dir=4;
					break;
				}
			}
		}
}

void cambiar_velocidad(){
	if(score==h*1){
			velocidad=velocidad-5;
			if(velocidad==5){
                velocidad=10;
			}
			h++;
	}
}

void comida(){          ///comida xy
		if(x==xc && y==yc){
			xc=(rand()%(ancho-10))+4;
			yc=(rand()%(largo-10))+4;

			tam++;
			score+=1;
			gotoxy(xc,yc);printf("%c",223);
		}
}
void comida_incremento(){          ///comida xy
		if(x==xc && y==yc){
			xc=(rand()%(ancho-10))+4;
			yc=(rand()%(largo-10))+4;
			tam++;
			score+=1;
			cambiar_velocidad();
			gotoxy(xc,yc);printf("%c",223);
		}
}
void incremento_guar(){
    switch(incre)
    {
        case 1:{
            comida();
           break;
        }
        case 2:{
            comida_incremento();
           break;
        }
    }
}
bool game_over(){       ///choque XD
	if(y==3 || y==largo || x==2 || x==ancho) return false;

	for(int j=tam-1;j>0;j--){
		  if(cuerpo[j][0] == x && cuerpo[j][1] == y){
		     return false;
	      	}

    	}
	return true;
}
void puntos(){
	gotoxy(11,1);printf("%d",score);
}

void tamano_guar_score(){
    switch(tama){
        case 1:{
            cout<<"PANTALLA: CHICO";
            break;
        }
        case 2:{
            cout<<"PANTALLA: NORMAL";
            break;
        }
        case 3:{
            cout<<"PANTALLA: GRANDE";
            break;
        }
        case 4:{
            cout<<"PANTALLA: COMPLETA";
            break;
        }
    }
}
void dificultad_guar_score(){
    switch(dificu){
           case 1:{
               cout<<"DIFICULTAD: FACIL";
               break;
           }
           case 2:{
               cout<<"DIFICULTAD: MEDIA";
               break;
           }
           case 3:{
               cout<<"DIFICULTAD: DIFICIL";
               break;
           }
           case 4:{
               cout<<"DIFICULTAD: EXTREMA";
               break;
           }
    }
}
void incremento_guar_score(){
    switch(incre){
        case 1:{
            cout<<"INCREMENTO: NO";
            break;
        }
        case 2:{
            cout<<"INCREMENTO: SI";
            break;
        }
    }
}
void game_over_imagen(){
        gotoxy(50,13);printf(" *************    *************   ********     ********  **************");
        gotoxy(50,14); cout<<"***************  ***************  *********   *********  ***************";
        gotoxy(50,15); cout<<"****             ****       ****  **** ***** ***** ****  ****";
        gotoxy(50,16); cout<<"****             ****       ****  ****   *******   ****  ****";
        gotoxy(50,17); cout<<"****   *******   ***************  ****    *****    ****  *************";
        gotoxy(50,18); cout<<"****   ********  ***************  ****             ****  *************";
        gotoxy(50,19); cout<<"****   **  ****  ****       ****  ****             ****  ****";
        gotoxy(50,20); cout<<"****       ****  ****       ****  ****             ****  ****";
        gotoxy(50,21); cout<<"***************  ****       ****  ****             ****  ***************";
        gotoxy(50,22); cout<<" *************   ****       ****  ****             ****  **************";
        gotoxy(54,25);cout<<"   *******     *****         *****  ************   ***********";
        gotoxy(54,26);cout<<" ***********   *****         *****  *************  ************";
        gotoxy(54,27);cout<<"*****   *****  *****         *****  ****           ****    ****";
        gotoxy(54,28);cout<<"****     ****   *****       *****   ****           ****   *****";
        gotoxy(54,29);cout<<"****     ****    *****     *****    *************  ***********";
        gotoxy(54,30);cout<<"****     ****     *****   *****     *************  *********";
        gotoxy(54,31);cout<<"****     ****      ***** *****      ****           **** ****";
        gotoxy(54,32);cout<<"*****   *****       *********       ****           ****  ****";
        gotoxy(54,33);cout<<" ***********         *******        *************  ****   ****";
        gotoxy(54,34);cout<<"   *******            *****         ************   ****    *****\n\n\n\n\n\n\n\n\n\n\n\n\n";
}
int az=0,ve=600;
void perdio(){
    game_over_imagen();
    while(az<2){
          system("color 47");
          Sleep(ve);
          system("color 4a");
          Sleep(ve);
          az++;ve=ve-10;
          if(ve==10)
          {ve=20;}
    }
    az=0,ve=200;
    gotoxy(67,39);cout<<"CONTINUAR:   PRESIONE CUALQUIER TECLA";
    gotoxy(67,41);cout<<"SALIR:       PRESIONE 2  VECES ALT+F4 \n\n\n\n\n\n";

}
void error_image(){
        gotoxy(50,18);printf("************    **********    **********     ***********    **********");
        gotoxy(50,19); cout<<"*************   ***********   ***********   *************   ***********";
        gotoxy(50,20); cout<<"****            ****   ****   ****   ****   ****     ****   ****   ****";
        gotoxy(50,21); cout<<"****            ****   ****   ****   ****   ****     ****   ****   ****";
        gotoxy(50,22); cout<<"***********     **********    **********    ****     ****   **********";
        gotoxy(50,23); cout<<"***********     *******       *******       ****     ****   *******";
        gotoxy(50,24); cout<<"****            **** ****     **** ****     ****     ****   **** ****";
        gotoxy(50,25); cout<<"****            ****  ****    ****  ****    ****     ****   ****  ****";
        gotoxy(50,26); cout<<"*************   ****   ****   ****   ****   *************   ****   ****";
        gotoxy(50,27); cout<<"************    ****    ****  ****    ****   ***********    ****    ****";
}
void snake_image(){
        gotoxy(105,10);cout<<"              **";
        gotoxy(105,11);cout<<"              **";
        gotoxy(105,12);cout<<"           ********";
        gotoxy(105,13);cout<<"          **********";
        gotoxy(105,14);cout<<"          **********";
        gotoxy(105,15);cout<<"            ******";
        gotoxy(105,16);cout<<"            ******";
        gotoxy(105,17);cout<<"            ********************";
        gotoxy(105,18);cout<<"            *********************";
        gotoxy(105,19);cout<<"             ********************";
        gotoxy(105,20);cout<<"                           ******";
        gotoxy(105,21);cout<<"                           ******";
        gotoxy(105,22);cout<<" ********************************";
        gotoxy(105,23);cout<<"*********************************";
        gotoxy(105,24);cout<<"********************************";
        gotoxy(105,25);cout<<"******";
        gotoxy(105,26);cout<<"******";
        gotoxy(105,27);cout<<"********************************";
        gotoxy(105,28);cout<<"*********************************";
        gotoxy(105,29);cout<<" ********************************";
        gotoxy(105,30);cout<<"                           ******";
        gotoxy(105,31);cout<<"                           ******";
        gotoxy(105,32);cout<<"             ********************";
        gotoxy(105,33);cout<<"            *********************";
        gotoxy(105,34);cout<<"            ********************";
        gotoxy(105,35);cout<<"            ******";
        gotoxy(105,36);cout<<"            ******";
        gotoxy(105,37);cout<<"             ****";
        gotoxy(117,13);printf("%c",223);
        gotoxy(122,13);printf("%c",223);
        gotoxy(120,11);printf("%c",219);
        gotoxy(120,10);printf("%c",219);
        gotoxy(119,11);printf("%c",219);
        gotoxy(119,10);printf("%c",219);

}
void juego(){     ///juego snak

        system("color 9a");
        pintar();
		gotoxy(3,1);cout<<"PUNTOS: ";
		gotoxy(79,1);cout<<"SNAKE BY:Alex";
		gotoxy(24,1);tamano_guar_score();
		gotoxy(50,1);dificultad_guar_score();
		gotoxy(120,1);incremento_guar_score();
		gotoxy(xc,yc);printf("%c",223);
    	while(tecla!=ESC && game_over() && ARRIBA && ABAJO && IZQUIERDA && DERECHA)
	{
		borrar_cuerpo();
		guardar_posicion();
		dibujar_cuerpo();
		puntos();
		gotoxy(160,1);cout<<velocidad;
		incremento_guar();
		teclear();
		teclear();
		teclear();
		teclear();
		if(dir==1) y--;
		if(dir==2) y++;
		if(dir==3) x++;
		if(dir==4) x--;
		Sleep(velocidad);
    }
    system("cls");
    perdio();
    system("pause>nul");

}
void presentacion(){
     gotoxy(78,5);cout<<"SNAKE by:Alex\n";
}

void tamano(){
    gotoxy(25,10);cout<<"SALIR = Alt + F4";
    gotoxy(20,15);cout<<"1 <=   TAMANO   >= 5";
    gotoxy(20,17);cout<<"INTRODUCE MAGENES DE CANCHA:";gotoxy(70,17);cin>>tama;
}
void dificultad(){
    gotoxy(20,21);cout<<"1 <= DIFICULTAD >= 4";
    gotoxy(20,23);cout<<"INTRODUCE DIFICULTAD:";gotoxy(70,23);cin>>dificu;
}
void personaje(){
    gotoxy(20,27);cout<<"1 <= PERSONAJE  >= 4";
    gotoxy(20,29);cout<<"1=NORMAL 2=INCREMENTO INTRODUCIR NUMERO:";gotoxy(70,29);cin>>perso;
    switch(perso){
        case 1:{
            velo=111;
            break;
        }
        case 2:{
            velo=42;
            break;
        }
        case 3:{
            velo=223;
            break;
        }
        case 4:{
            velo=219;
            break;
        }
    }
}
void incremento(){
    gotoxy(20,33);cout<<"1 <= INCREMENTO >= 2";
    gotoxy(20,35);cout<<"1=NORMAL 2=INCREMENTO INTRODUCIR NUMERO:";gotoxy(70,35);cin>>incre;
}

void dificultad_guar(){
    switch(dificu)
    {
        case 1:{
            velocidad=200;
            break;
        }
        case 2:{
            velocidad=100;
            break;
        }
        case 3:{
            velocidad=60;
            break;
        }
        case 4:{
            velocidad=30;
            break;
        }
    }

}

void tamano_guar(){
    switch(tama){
        case 1:{
            largo =20,ancho=40;
            dificultad_guar();
            incremento_guar();
            juego();
            break;
        }
        case 2:{
            largo=30,ancho=50;
            dificultad_guar();
            incremento_guar();
            juego();
            break;
        }
        case 3:{
            largo=57,ancho=75;
            dificultad_guar();
            incremento_guar();
            juego();
            break;
        }
        case 4:{
            largo=57,ancho=165;
            dificultad_guar();
            incremento_guar();
            juego();
            break;
        }
        case 5:{
            gotoxy(67,12);cout<<"INTRODUCIR  COLUMNAS    &&   FILAS";
            gotoxy(53,18);cout<<"RECOMENDADO MAX: 57    COLUMNAS  :";gotoxy(100,18);cin>>largo;
            gotoxy(53,20);cout<<"RECOMENDADO MAX: 165   FILAS     :";gotoxy(100,20);cin>>ancho;
            system("cls");
            dificultad_guar();
            incremento_guar();
            juego();
            break;
        }
    }
}
int aq=0,vq=300;
void snake()
{
    system("color 4f");
    snake_image();
    presentacion();tamano();dificultad();personaje();incremento();
    system("cls");
    if(tama<6&&tama>0&&dificu<5&&dificu>0&&incre<3&&incre>0){
        tamano_guar();

    }else{
         error_image();
         gotoxy(71,30);cout<<"NO INTRODUJO BIEN LOS DATOS XD\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
         while(aq<2){
          system("color 47");
          Sleep(vq);
          system("color 4a");
          Sleep(vq);
          aq++;
          }
          aq=0,vq=200;
          gotoxy(66,32);cout<<"PRECIONE CUALQUIER LETRA PARA CONTINUAR\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
         system("pause>nul");
        }

}

void snake_imagen(){    ///imagen bucle

    for(int i=63;i<=110;i++){
        for(int j=0,k=3;j<4&&k<6;j++,k++){
            gotoxy(i,k); printf("%c",169);
            gotoxy(i,k+19);printf("%c",169);
        }
}
    for(int j=3;j<25;j++){
            for(int i=0,k=62;i<7,k<68;i++,k++){
                gotoxy(k,j);printf("%c",169);
                gotoxy(k+43,j);printf("%c",169);
            }
}
    for(int i=105;i<130;i++){
            for(int j=0,k=11;j<4&&k<13;j++,k++){
                 gotoxy(i,k);printf(" ");
            }
    }
    for(int i=73;i<110;i++){
            for(int j=0,k=8;j<4&&k<11;j++,k++){
                gotoxy(i,k);printf("%c",169);
            }
    }
    for(int i=9;i<19;i++){
        for(int u=0,j=73;u<6&&j<79;u++,j++)
            {gotoxy(j,i);printf("%c",169);}
    }
    for(int i=73;i<88;i++){
            for(int u=0,j=17;u<4,j<20;u++,j++){
                gotoxy(i,j);printf("%c",169);
            }
    }
    for(int i=94;i<100;i++){
            for(int j=0,k=17;j<3&&k<20;j++,k++){
                gotoxy(i,k);printf("%c",219);
            }
    }
    /*
    for(int i=63;i<=110;i++){

        gotoxy(i,3); printf("%c",169);
        gotoxy(i,4); printf("%c",169);
        gotoxy(i,5); printf("%c",169);
        gotoxy(i,23);printf("%c",169);
        gotoxy(i,24);printf("%c",169);
        gotoxy(i,22);printf("%c",169);
    }
    for(int j=3;j<25;j++){
        gotoxy(62,j);printf("%c",169);
        gotoxy(63,j);printf("%c",169);
        gotoxy(64,j);printf("%c",169);
        gotoxy(65,j);printf("%c",169);
        gotoxy(66,j);printf("%c",169);
        gotoxy(67,j);printf("%c",169);
        gotoxy(106,j);printf("%c",169);
        gotoxy(107,j);printf("%c",169);
        gotoxy(108,j);printf("%c",169);
        gotoxy(109,j);printf("%c",169);
        gotoxy(110,j);printf("%c",169);
        gotoxy(105,j);printf("%c",169);
    }for(int i=105;i<130;i++){
        gotoxy(i,12);printf(" ");
        gotoxy(i,11);printf(" ");
        gotoxy(i,10);printf(" ");
    }
    for(int i=73;i<110;i++){
       gotoxy(i,9);printf("%c",169);
       gotoxy(i,8);printf("%c",169);
       gotoxy(i,10);printf("%c",169);
    }
    for(int i=9;i<19;i++){
        gotoxy(73,i);printf("%c",169);
        gotoxy(74,i);printf("%c",169);
        gotoxy(75,i);printf("%c",169);
        gotoxy(76,i);printf("%c",169);
        gotoxy(77,i);printf("%c",169);
        gotoxy(78,i);printf("%c",169);


    }
    for(int i=73;i<88;i++){
        gotoxy(i+1,18);printf("%c",169);
        gotoxy(i,17);printf("%c",169);
        gotoxy(i,19);printf("%c",169);

    }
    for(int i=94;i<100;i++){
        gotoxy(i,17);printf("%c",219);
        gotoxy(i,18);printf("%c",219);
        gotoxy(i,19);printf("%c",219);
    }
*/
        gotoxy(88,18);printf("%c",169);
        gotoxy(89,18);printf("%c",169);
        gotoxy(85,19);printf("%c",254);
        gotoxy(85,17);printf("%c",223);
        gotoxy(110,24);printf(" ");
        gotoxy(62,24);printf(" ");
        gotoxy(62,3);printf(" ");
        gotoxy(110,3);printf(" ");
        gotoxy(73,8);printf(" ");
        gotoxy(73,19);printf(" ");
        gotoxy(110,13);printf(" ");
        gotoxy(105,13);printf(" ");

        gotoxy(36,28);cout<<" *************      ********       ****      *************      *****    *******    **************";
        gotoxy(36,29);cout<<"***************     *********      ****     ***************     *****   ******      ***************";
        gotoxy(36,30);cout<<"****                **** *****     ****     ****       ****     *****  *****        ****";
        gotoxy(36,31);cout<<"****                ****   ****    ****     ****       ****     ***** ****          ****";
        gotoxy(36,32);cout<<"**************      ****    ****   ****     ***************     **********          *************";
        gotoxy(36,33);cout<<" **************     ****     ****  ****     ***************     **********          *************";
        gotoxy(36,34);cout<<"           ****     ****      **** ****     ****       ****     ***** *****         ****";
        gotoxy(36,35);cout<<"           ****     ****       ********     ****       ****     *****  *****        ****";
        gotoxy(36,36);cout<<"***************     ****        *******     ****       ****     *****   ******      ***************";
        gotoxy(36,37);cout<<" *************      ****         ******     ****       ****     *****    *******    **************";


}
void alex(){
        gotoxy(55,40);printf("********   ***  ***   ***    ******   ***     ******  ***  ***");
        gotoxy(55,41); cout<<"**    **   ***  ***   ***   ********  ***     **       ******";
        gotoxy(55,42); cout<<"*******     ******          ***  ***  ***     ****      ****";
        gotoxy(55,43); cout<<"**    **     ****     ***   ********  ******  **       ******";
        gotoxy(55,44); cout<<"********     ****     ***   ***  ***  ******  ******  ***  ***\n\n\n";
}
void AltEnter(){  ///pantalla completa

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
int a=0;int v=200;
void presentacion_principal(){
     snake_imagen();alex();
    system("pause>null");
}
int main()
{   AltEnter();
    system("cls");
    system("color 4f");
    presentacion_principal();carga();
    system("cls");
    do{

       snake();
       cuerpo[400][2];
       n=1;
       tam=3;
       x=10;
       y=12;
       dir=3;
       xc=30,yc=15;
       velocidad,h=1;
       score=0;
       system("cls");
       system("color 47");
       system("cls");
     }while(true);
       system("cls");
           gotoxy(78,22);cout<<"FIN DEL JUEGO\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
       system("pause>null");
       return 0;

}
