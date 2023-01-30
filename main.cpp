#include <iostream>
#include <stdlib.h>

using namespace std;

char planesTable[11][11];
char attackTable[11][11];

struct nod {
    int x, y;
    char symbol;
    nod* leg;
};

bool isInside(int x, int y) {
    return (x <= 10 && x >= 1 && y >= 1 && y <= 10);
}

bool isEmptyCell(int x, int y){
    return (planesTable[y][x] == '_');
}

void pushBlock(int x, int y, nod* a) {
    if(!isInside(x, y) || !isEmptyCell(x, y)){
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

void buildNorth(int x, int y, nod* a) {
    pushBlock(x, y + 1, a);
    pushBlock(x - 1, y + 1, a);
    pushBlock(x - 2, y + 1, a);
    pushBlock(x + 1, y + 1, a);
    pushBlock(x + 2, y + 1, a);
    pushBlock(x, y + 2, a);
    pushBlock(x, y + 3, a);
    pushBlock(x - 1, y + 3, a);
    pushBlock(x + 1, y + 3, a);
}

void buildSouth(int x, int y, nod* a) {
    pushBlock(x, y - 1, a);
    pushBlock(x - 1, y - 1, a);
    pushBlock(x - 2, y - 1, a);
    pushBlock(x + 1, y - 1, a);
    pushBlock(x + 2, y - 1, a);
    pushBlock(x, y - 2, a);
    pushBlock(x, y - 3, a);
    pushBlock(x - 1, y - 3, a);
    pushBlock(x + 1, y - 3, a);
}

void buildEast(int x, int y, nod* a) {
    pushBlock(x - 1, y, a);
    pushBlock(x - 2, y, a);
    pushBlock(x - 2, y + 1, a);
    pushBlock(x - 2, y + 2, a);
    pushBlock(x - 2, y - 1, a);
    pushBlock(x - 2, y - 2, a);
    pushBlock(x - 3, y, a);
    pushBlock(x - 4, y, a);
    pushBlock(x - 4, y - 1, a);
    pushBlock(x - 4, y + 1, a);
}

void buildWest(int x, int y, nod* a) {
    pushBlock(x + 1, y, a);
    pushBlock(x + 2, y, a);
    pushBlock(x + 2, y + 1, a);
    pushBlock(x + 2, y + 2, a);
    pushBlock(x + 2, y - 1, a);
    pushBlock(x + 2, y - 2, a);
    pushBlock(x + 3, y, a);
    pushBlock(x + 4, y, a);
    pushBlock(x + 4, y - 1, a);
    pushBlock(x + 4, y + 1, a);
}

nod* buildPlane(int x, int y, char orient) {
    if(!isInside(x, y) || !isEmptyCell(x, y)){
        return NULL;
    }

    nod* a = new nod;

    a -> x = x;
    a -> y = y;
    a -> leg = NULL;

    switch(orient) {
        case 'N':
            a -> symbol = 'k';
            buildNorth(x, y, a);
            break;
        case 'S':
            a -> symbol = 'j';
            buildSouth(x, y, a);
            break;
        case 'E':
            a -> symbol = 'l';
            buildEast(x, y, a);
            break;
        case 'V':
            a -> symbol = 'h';
            buildWest(x, y, a);
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

    if(nodes < 10){
        return NULL;
    }

    return a;
}

void appendPlane(nod* a) {
    while(a){
        planesTable[a -> y][a -> x] = a -> symbol;
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

void initCMD() {
    #ifdef _WIN32
        system("@chcp 65001>nul");
    #endif
}

int main() {
    initCMD();

    nod* avioane[3];

    clearTable(planesTable);
    clearTable(attackTable);

    displayTable(planesTable);
    for(int i = 0; i < 3; i++){
        int x, y;
        char orient;

        cout<<"Avion "<<i + 1<<" (x, y, N/S/E/V): ";
        cin>>x>>y>>orient;

        avioane[i] = buildPlane(x, y, orient);

        if(avioane[i] == NULL) {
            cout<<"Valorile introduse sunt invalide!"<<endl;
            i--;
        }else {
            appendPlane(avioane[i]);
            displayTable(planesTable);
        }
    }


    return 0;
}
