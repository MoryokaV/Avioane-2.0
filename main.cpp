#include <iostream>
#include <stdlib.h>
#include <conio.h>
#include <iomanip>
#include <ctime>
#include <bits/stdc++.h>
#include <stdio.h>

using namespace std;

char planesTable[11][11];
char attackTable[11][11];
char pcTable[11][11];

struct nod {
    int x, y;
    char symbol;
    nod* leg;
};

void initCMD() {
    #ifdef _WIN32
        system("@chcp 65001>nul");
    #endif
}

bool isInside(int x, int y) {
    return (x <= 10 && x >= 1 && y >= 1 && y <= 10);
}

bool isEmptyCell(int x, int y, char table[][11]){
    return (table[y][x] == '_');
}

bool isShooted(int x, int y, char table[][11]){
    return (table[y][x] == '*' || table[y][x] == 'x');
}

void appendPlane(nod* a, char table[][11]) {
    while(a){
        table[a -> y][a -> x] = a -> symbol;
        a = a -> leg;
    }
}

void clearTable(char table[][11]) {
    for(int i = 1; i <= 10; i++){
        for(int j = 1; j <= 10; j++){
            table[i][j] = '_';
        }
    }
}

void pushBlock(int x, int y, nod* a, char table[][11]) {
    if(!isInside(x, y) || !isEmptyCell(x, y, table)){
        return;
    }

    nod* block = new nod;

    block -> x = x;
    block -> y = y;
    block -> symbol = '|';
    block -> leg = NULL;

    if(a == NULL){
        a = block;
    }else{
        nod* q = a;

        while(q -> leg){
            q = q -> leg;
        }

        q -> leg = block;
    }
}

void buildNorth(int x, int y, nod* a, char table[][11]) {
    pushBlock(x, y + 1, a, table);
    pushBlock(x - 1, y + 1, a, table);
    pushBlock(x - 2, y + 1, a, table);
    pushBlock(x + 1, y + 1, a, table);
    pushBlock(x + 2, y + 1, a, table);
    pushBlock(x, y + 2, a, table);
    pushBlock(x, y + 3, a, table);
    pushBlock(x - 1, y + 3, a, table);
    pushBlock(x + 1, y + 3, a, table);
}

void buildSouth(int x, int y, nod* a, char table[][11]) {
    pushBlock(x, y - 1, a, table);
    pushBlock(x - 1, y - 1, a, table);
    pushBlock(x - 2, y - 1, a, table);
    pushBlock(x + 1, y - 1, a, table);
    pushBlock(x + 2, y - 1, a, table);
    pushBlock(x, y - 2, a, table);
    pushBlock(x, y - 3, a, table);
    pushBlock(x - 1, y - 3, a, table);
    pushBlock(x + 1, y - 3, a, table);
}

void buildEast(int x, int y, nod* a, char table[][11]) {
    pushBlock(x - 1, y, a, table);
    pushBlock(x - 1, y + 1, a, table);
    pushBlock(x - 1, y + 2, a, table);
    pushBlock(x - 1, y - 1, a, table);
    pushBlock(x - 1, y - 2, a, table);
    pushBlock(x - 2, y, a, table);
    pushBlock(x - 3, y, a, table);
    pushBlock(x - 3, y - 1, a, table);
    pushBlock(x - 3, y + 1, a, table);
}

void buildWest(int x, int y, nod* a, char table[][11]) {
    pushBlock(x + 1, y, a, table);
    pushBlock(x + 1, y + 1, a, table);
    pushBlock(x + 1, y + 2, a, table);
    pushBlock(x + 1, y - 1, a, table);
    pushBlock(x + 1, y - 2, a, table);
    pushBlock(x + 2, y, a, table);
    pushBlock(x + 3, y, a, table);
    pushBlock(x + 3, y - 1, a, table);
    pushBlock(x + 3, y + 1, a, table);
}

nod* buildPlane(int x, int y, char orient, char table[][11]) {
    if(!isInside(x, y) || !isEmptyCell(x, y, table)){
        return NULL;
    }

    nod* a = new nod;

    a -> x = x;
    a -> y = y;
    a -> leg = NULL;

    switch(orient) {
        case 'N':
            a -> symbol = 'k';
            buildNorth(x, y, a, table);
            break;
        case 'S':
            a -> symbol = 'j';
            buildSouth(x, y, a, table);
            break;
        case 'E':
            a -> symbol = 'l';
            buildEast(x, y, a, table);
            break;
        case 'V':
            a -> symbol = 'h';
            buildWest(x, y, a, table);
            break;
        default:
            return NULL;
    }

    nod* temp = a;
    int nodes = 0;

    while(temp) {
        nodes++;
        temp = temp -> leg;
    }

    if(nodes != 10){
        return NULL;
    }

    return a;
}

void displayTable(char table[][11]) {
    cout<<"\n";

    cout<<"   ";
    for(int i = 1; i <= 10; i++){
        cout<<i<<" ";
    }

    cout<<endl;
    for(int i = 1; i <= 10; i++){
        if(i == 10){
            cout<<i<<" ";
        }else{
            cout<<i<<"  ";
        }

        for(int j = 1; j <= 10; j++){
             switch(table[i][j]) {
                case 'k':
                    cout<<"▲";
                    break;
                case 'j':
                    cout<<"▼";
                    break;
                case 'l':
                    cout<<"▶";
                    break;
                case 'h':
                    cout<<"◀";
                    break;
                case '|':
                    cout<<"▮";
                    break;
                default:
                    cout<<table[i][j];
            }
            cout<<" ";
        }
        cout<<endl;
    }

    cout<<"\n";
}

void choosePlanes(nod* avioane[]) {
    clearTable(planesTable);
    clearTable(attackTable);

    cout<<"\nPozitioneaza-ti avioanele\n";
    displayTable(planesTable);
    for(int i = 0; i < 3; i++){
        int x, y;
        char orient;

        cout<<"Avion "<<i + 1<<" (x, y, N/S/E/V): ";
        cin>>x>>y>>orient;

        avioane[i] = buildPlane(x, y, orient, planesTable);

        if(avioane[i] == NULL) {
            cout<<"Valorile introduse sunt invalide!"<<endl;
            i--;
        }else {
            appendPlane(avioane[i], planesTable);
            system("cls");
            cout<<"\nPozitioneaza-ti avioanele\n";
            displayTable(planesTable);
        }
    }
}

void generatePC(nod* pc[]) {
    clearTable(pcTable);
    char orientations[] = {'N', 'S', 'E', 'V'};

    srand(time(NULL));
    for(int i = 0; i < 3; i++){
        int x, y;
        int orient;

        x = rand() % 10 + 1;
        y = rand() % 10 + 1;
        orient = rand() % 4;

        pc[i] = buildPlane(x, y, orientations[orient], pcTable);

        if(pc[i] == NULL) {
            i--;
        }else{
            appendPlane(pc[i], pcTable);
        }
    }
}

bool isHead(int x, int y, nod* list[], char table[][11]){
   for(int i = 0; i < 3; i++){
        if(list[i] -> x == x && list[i] -> y == y){
            nod* plane = list[i] -> leg;

            while(plane){
                table[plane -> y][plane -> x] = '*';
                plane = plane -> leg;
            }

            return true;
        }
    }

    return false;
}

void sleep() {
    cout<<"\nApasa orice tasta pentru a continua...";
    getch();
}

void win() {
    sleep();
    system("cls");
    cout<<"\n -- Ai castigat! :) -- \n\n\n\n";
    sleep();
}

void lose() {
    sleep();
    system("cls");
    cout<<"\n -- Ai pierdut! ;( -- \n\n\n\n";
    sleep();
}

void attack(nod* avioane[], nod* pc[]) {
    int my_planes = 3;
    int pc_planes = 3;

    int totalAttacks[3] = {0};
    int shootsTaken[3] = {0};

    srand(time(NULL));
    while(my_planes > 0 && pc_planes > 0){
        system("cls");

        cout<<"Tabla defensiva - "<<my_planes<<" avioane"<<endl;
        displayTable(planesTable);

        cout<<"Tabla ofensiva - "<<pc_planes<<" avioane"<<endl;
        displayTable(attackTable);

        int x, y;

        //PLAYER
        cout<<endl<<"Ataca pozitie (x, y): ";
        cin>>x>>y;

        if(!isInside(x, y)){
            cout<<"\nValorile introduse sunt invalide\n";
            sleep();

            continue;
        }

        if(isShooted(x, y, attackTable)){
            cout<<"\nPozitie deja lovita\n";
            sleep();

            continue;
        }

        if(!isEmptyCell(x, y, pcTable)){
            attackTable[y][x] = '*';
            if(isHead(x, y, pc, attackTable)){
                pc_planes--;
            }
        }else{
            attackTable[y][x] = 'x';
        }

        if(pc_planes == 0){
            break;
        }

        //PC
        do{
            x = rand() % 10 + 1;
            y = rand() % 10 + 1;
        }while(isShooted(x, y, planesTable));

        if(!isEmptyCell(x, y, planesTable)){
            planesTable[y][x] = '*';
            if(isHead(x, y, avioane, planesTable)){
                my_planes--;
            }
        }else{
            planesTable[y][x] = '*';
        }

        cout<<"Ai fost lovit in ("<<x<<", "<<y<<")\n";
        sleep();
    }

    if(pc_planes == 0){
        win();
    }

    if(my_planes == 0){
        lose();
    }
}

void play() {
    nod* avioane[3];
    nod* pc[3];

    system("cls");

    choosePlanes(avioane);
    generatePC(pc);

    attack(avioane, pc);
}

void help();

int teme(){
    char opt;
    do{
        system("CLS");
        cout<<"\n\n\n\n\n";
        cout<<setw(87)<<"##########################"<<'\n';
        cout<<setw(87)<<"#                        #"<<'\n';
        cout<<setw(87)<<"#       Alege tema       #"<<'\n';
        cout<<setw(87)<<"#                        #"<<'\n';
        cout<<setw(87)<<"#   [1] Hacker           #"<<'\n';
        cout<<setw(87)<<"#   [2] Light Raven      #"<<'\n';
        cout<<setw(87)<<"#   [3] Minioni          #"<<'\n';
        cout<<setw(87)<<"#   [4] Dark Raven       #"<<'\n';
        cout<<setw(87)<<"#   [5] Dracula          #"<<'\n';
        cout<<setw(87)<<"#   [0] Inapoi la meniu  #"<<'\n';
        cout<<setw(87)<<"#                        #"<<'\n';
        cout<<setw(87)<<"##########################"<<'\n';

        opt = getch();

        switch(opt){
            case '1':
                system("color 0A");
                break;
            case '2':
                system("color 7D");
                break;
            case '3':
                system("color 69");
                break;
            case '4':
                system("color 0D");
                break;
            case '5':
                system("color 8C");
                break;
            default:
                break;
        }

    }while(opt != '0');
}

/*0 = Black       8 = Gray
    1 = Blue        9 = Light Blue
    2 = Green       A = Light Green
    3 = Aqua        B = Light Aqua
    4 = Red         C = Light Red
    5 = Purple      D = Light Purple
    6 = Yellow      E = Light Yellow
    7 = White       F = Bright White
*/

void cumsejoaca(){
    system("CLS");
    cout<<"Jocul avioanele se joacă în doi jucători."<<'\n'<<'\n';
    cout<<"Fiecare jucător are nevoie de o foaie de hârtie de matematică, pe care adversarul nu o poate vedea pe tot parcursul jocului."<<'\n'<<'\n';
    cout<<"Pe foaie, fiecare jucător va face trasa câte un pătrat format din 10×10 pătrățele. Latura verticală a pătratului se notează cu cifre de la 1 la 10, cea orizonatala cu litere de la A la J. \nÎn interior, jucătorii vor desena câte 3 avioane astfel: vârful avionului (1 pătrățel), aripile avionului (în total 5 pătrățele), corpul (1 pătrățel) și o coadă (3 pătrățele)."<<'\n'<<'\n';
    cout<<"Jucătorii vor trebui să identifce modul în care adversarul a  desenat avioanele. Pentru acest lucru este nevoie să noteze fiecare pe foaia sa și punctele lovite ori ratate ale celuilalt. \nPe rând, fiecare jucător încearcă să ghicească indicând coordonatele (unul de pe verticală, unul pe orizontală). \nVa primi răspunsul de la celălalt jucător, în funcție de punctul atins al avionului sau acesta va preciza că nu a fost lovit avionul, atunci când este cazul. \nAtunci când este nimerit capul avionului, răspunsul va fi „Cap lovit!”. Jocul continuă până când unul dintre copii reușește să identifice poziția celor trei avioane ale adversarului."<<'\n';
}

void menu() {
    char opt;

    do{
        system("CLS");

        cout<<"\n\n\n\n\n";
        cout<<setw(87)<<"##########################"<<'\n';
        cout<<setw(87)<<"#                        #"<<'\n';
        cout<<setw(87)<<"#        AVIOANE 2.0     #"<<'\n';
        cout<<setw(87)<<"#                        #"<<'\n';
        cout<<setw(87)<<"#          MENIU         #"<<'\n';
        cout<<setw(87)<<"#                        #"<<'\n';
        cout<<setw(87)<<"#   [1] Player vs PC     #"<<'\n';
        cout<<setw(87)<<"#   [2] Cum se joaca?    #"<<'\n';
        cout<<setw(87)<<"#   [3] Teme de culori   #"<<'\n';
        cout<<setw(87)<<"#   [0] Iesire           #"<<'\n';
        cout<<setw(87)<<"#                        #"<<'\n';
        cout<<setw(87)<<"##########################"<<'\n';

        opt = getch();

        switch(opt){
            case '1':
                play();
                break;
            case '2':
                cumsejoaca();
                sleep();
                break;
            case '3':
                teme();
                break;
            default:
                break;
        }

    }while(opt != '0');
}

int main() {
    initCMD();

    menu();

    return 0;
}
