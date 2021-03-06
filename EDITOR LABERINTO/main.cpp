#include <iostream>
#include <windowsx.h>
#include <windows.h>
#include <commctrl.h>
#include <stdio.h>
#include "resource.h"
#include<conio.h>
#include<stdlib.h>
#include <fstream>

using namespace std;

HINSTANCE hInst;
HBRUSH brush;
HPEN greenPen;
COLORREF actual;

double XPOSTM,YPOSTM;
int X_MATRIZ=0,Y_MATRIZ=0;
char MAPA[300][300];
bool XXX=1;
char CHARR_IM='E';

double ADELANTE=0.0;
double ATRAS=0.0;
double IZQUIERDA=0.0;
double DERECHA=0.0;

void DIBUJAR_TABLA_COORD(HDC);

void PINTAR_POSITION(HDC hdc){
    double XINI,XFIN,YINI,YFIN;
    for(int i=0;i<300;i++){
        for(int j=0;j<300;j++){
            if(MAPA[i][j]=='E'){
                greenPen=CreatePen(PS_SOLID, 1, RGB(255, 255, 0));
                SelectObject(hdc,greenPen);
                brush=CreateSolidBrush(RGB(255, 255, 0));
                SelectObject(hdc,brush);
                XINI=i*5.7466+1;XFIN=XINI+5.7466,YINI=j*3.08+1,YFIN=YINI+3.08;
                Rectangle(hdc,XINI,YINI,XFIN,YFIN);
                DeleteObject(brush);DeleteObject(greenPen);
            }
            if(MAPA[i][j]=='I'){
                greenPen=CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
                SelectObject(hdc,greenPen);
                brush=CreateSolidBrush(RGB(255, 0, 0));
                SelectObject(hdc,brush);
                XINI=i*5.7466+1;XFIN=XINI+5.7466,YINI=j*3.08+1,YFIN=YINI+3.08;
                Rectangle(hdc,XINI,YINI,XFIN,YFIN);
                DeleteObject(brush);DeleteObject(greenPen);
            }
            if(MAPA[i][j]=='F'){
                greenPen=CreatePen(PS_SOLID, 1, RGB(0, 0, 255));
                SelectObject(hdc,greenPen);
                brush=CreateSolidBrush(RGB(0, 0, 255));
                SelectObject(hdc,brush);
                XINI=i*5.7466+1;XFIN=XINI+5.7466,YINI=j*3.08+1,YFIN=YINI+3.08;
                Rectangle(hdc,XINI,YINI,XFIN,YFIN);
                DeleteObject(brush);DeleteObject(greenPen);
            }
        }
    }
}

void DIBUJAR_TABLA_COORD(HDC hdc){                                  ///GRAFICAR LINEAS TABLA
    for(double i=1,j=0;j<300;j++,i+=5.7466){///1724
        MoveToEx(hdc,i,1,NULL);
        LineTo(hdc,i,925);
    }
    for(double i=1,j=0;j<300;j++,i+=3.08){///924
        MoveToEx(hdc,1,i,NULL);
        LineTo(hdc,1725,i);
    }
}

void LLENAR_MAPA(){
    for(int i=0;i<300;i++){
        for(int j=0;j<300;j++){
            MAPA[i][j]='X';
        }
    }
}

BOOL CALLBACK DlgMain(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    HDC hdc;
    PAINTSTRUCT ps;
    static COLORREF color;
    RECT re;

    switch(uMsg)
    {
    case WM_INITDIALOG:
        {
            color = GetSysColor(COLOR_BACKGROUND);
            RegisterHotKey(hwndDlg, ID_VERDE, 0, 'V');
            RegisterHotKey(hwndDlg, ID_ADELANTE, 0, 'W');
            RegisterHotKey(hwndDlg, ID_ATRAS, 0, 'S');
            RegisterHotKey(hwndDlg, ID_IZQUIERDA, 0, 'A');
            RegisterHotKey(hwndDlg, ID_DERECHA, 0, 'D');
            RegisterHotKey(hwndDlg, ID_ROJO, MOD_ALT, 'R');
            RegisterHotKey(hwndDlg, ID_AZUL, MOD_CONTROL, 'A');

            string valor;
            ofstream salida;
            ifstream leer("Salida.txt");
            int N_FILAS=0,N_COL=0;

            while(!leer.eof()){
                leer >> valor;
                if(leer){
                    for(N_COL=0;valor[N_COL];N_COL++){
                        MAPA[N_FILAS][N_COL]=valor[N_COL];
                    }
                }N_FILAS++;
            }

            for(int i=0;i<N_FILAS-1;i++){
                for(int j=0;j<N_COL;j++){
                    //cout<<MAPA[i][j]<<" ";
                }//cout<<"\n";
            }
            leer.close();

        }
        return TRUE;
    case WM_HOTKEY:
           switch((int)wParam) {
              case ID_VERDE:
                 color = RGB(0,255,0);
                 break;
              case ID_ADELANTE:
                if(MAPA[X_MATRIZ][Y_MATRIZ-1]){
                    Y_MATRIZ-=1;
                    MAPA[X_MATRIZ][Y_MATRIZ]='E';
                }
                 break;
              case ID_ATRAS:
                if(MAPA[X_MATRIZ][Y_MATRIZ+1]){
                    Y_MATRIZ+=1;
                    MAPA[X_MATRIZ][Y_MATRIZ]='E';
                }
                 break;
              case ID_IZQUIERDA:
                if(MAPA[X_MATRIZ-1][Y_MATRIZ]){
                    X_MATRIZ-=1;
                    MAPA[X_MATRIZ][Y_MATRIZ]='E';
                }
                 break;
              case ID_DERECHA:
                if(MAPA[X_MATRIZ+1][Y_MATRIZ]){
                    X_MATRIZ+=1;
                    MAPA[X_MATRIZ][Y_MATRIZ]='E';
                }
                 break;
              case ID_ROJO:
                 color = RGB(255,0,0);
                 break;
              case ID_AZUL:
                 color = RGB(0,0,255);
                 break;
           }
           InvalidateRect(hwndDlg, NULL, FALSE);
           break;
    case WM_MOUSEMOVE:{
        long xpos=GET_X_LPARAM(lParam);
        long ypos=GET_Y_LPARAM(lParam);
        char cade[20];
        ltoa(xpos,cade,10);
        SetDlgItemText(hwndDlg,EDITX,cade);
        ltoa(ypos,cade,10);
        SetDlgItemText(hwndDlg,EDITY,cade);
        }
        return TRUE;
    case WM_PAINT:
        {
            hdc=BeginPaint(hwndDlg,&ps);
            GetClientRect(hwndDlg, &re);
            FillRect(hdc, &re, CreateSolidBrush(color));
            SetBkMode(hdc, TRANSPARENT);

            if(XXX){
                ///LLENAR_MAPA();
                XXX=0;
            }

            greenPen=CreatePen(PS_SOLID, 1, RGB(51, 204, 255 ));
            brush=CreateSolidBrush(RGB(0, 0, 0));
            SelectObject(hdc,greenPen);
            SelectObject(hdc,brush);
            //Rectangle(hdc,1,1,1725,925);
            DeleteObject(brush);
            DeleteObject(greenPen);

            PINTAR_POSITION(hdc);

            greenPen=CreatePen(PS_SOLID, 1, RGB(51, 204, 255 ));
            SelectObject(hdc,greenPen);
            //DIBUJAR_TABLA_COORD(hdc);
            DeleteObject(greenPen);
            /*
            TextOut(hdc, 10, 10, "Pulsa 'V' para verde", 20);
            TextOut(hdc, 10, 30, "Pulsa 'ALT+R' para rojo", 23);
            TextOut(hdc, 10, 50, "Pulsa 'CTRL+A' para azul", 24);
            */
            EndPaint(hwndDlg,&ps);
        }
        return TRUE;
        case WM_DESTROY:
           UnregisterHotKey(hwndDlg, ID_VERDE);
           UnregisterHotKey(hwndDlg, ID_ROJO);
           UnregisterHotKey(hwndDlg, ID_AZUL);
           PostQuitMessage(0);    /* env?a un mensaje WM_QUIT a la cola de mensajes */
           break;
        case WM_LBUTTONDOWN:{
            PAINTSTRUCT ps;
            hdc=BeginPaint(hwndDlg,&ps);
            long xpos=GET_X_LPARAM(lParam);
            long ypos=GET_Y_LPARAM(lParam);
            XPOSTM=xpos;YPOSTM=ypos;
            X_MATRIZ=XPOSTM/5.7466;Y_MATRIZ=YPOSTM/3.08;
            if(MAPA[X_MATRIZ][Y_MATRIZ]=='X'){
                if(CHARR_IM=='I'){
                    MAPA[X_MATRIZ][Y_MATRIZ]='I';CHARR_IM='E';
                }else if(CHARR_IM=='F'){
                    MAPA[X_MATRIZ][Y_MATRIZ]='F';CHARR_IM='E';
                }else{
                    MAPA[X_MATRIZ][Y_MATRIZ]='E';
                }
            }else if(MAPA[X_MATRIZ][Y_MATRIZ]=='E'){
                MAPA[X_MATRIZ][Y_MATRIZ]='X';
            }
               InvalidateRect(hwndDlg,NULL,true);
            }
        return TRUE;

        case WM_CLOSE:
        {   EndDialog(hwndDlg, 0);
        }
        return TRUE;

        case WM_COMMAND:
        {   switch(LOWORD(wParam))
            {
                case BTN_INSERTAR:
                    char CadONE[10];
                    GetDlgItemText(hwndDlg,EDIT1,CadONE,10);
                    CHARR_IM=CadONE[0];
                    SetDlgItemText(hwndDlg,EDIT1," ");
                return TRUE;
                case BTN_NUEVO:
                    LLENAR_MAPA();
                    InvalidateRect(hwndDlg,NULL,true);
                return TRUE;
                case BTN_EXPORTAR:
                    ofstream salida;
                    salida.open("Salida.txt");
                    for(int i=0;i<300;i++){
                        for(int j=0;j<300;j++){

                            salida<<MAPA[i][j];

                        }salida<<"\n";
                    }
                    salida.close();
                return TRUE;
            }
        }
        return TRUE;
        }
    return FALSE;
}

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
    hInst=hInstance;
    InitCommonControls();
    return DialogBox(hInst, MAKEINTRESOURCE(DLG_MAIN), NULL, (DLGPROC)DlgMain);
}
