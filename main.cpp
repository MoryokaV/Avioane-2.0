#include <iostream>

using namespace std;

char planesTable[11][11];
char attackTable[11][11];

struct nod {
    int x, y;
    nod* leg;
};

bool isInside(int x, int y) {
    return (x <= 10 && x >= 1 && y >= 1 && y <= 10);
}

bool isEmptyCell(int x, int y){
    return planesTable[x][y] == '_';
} 

void pushBlock(int x, int y, nod* a) {
    if(!isInside(x, y) && !isEmptyCell(x, y)){
        return;
    }

    nod* block = new nod;

    block -> x = x;
    block -> y = y;
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

nod* buildPlane(int x, int y) {
    nod* a = new nod;

    a -> x = x;
    a -> y = y;
    a -> leg = NULL; 

    buildNorth(x, y, a);

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
        planesTable[a -> y][a -> x] = '|';
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
    for(int i = 1; i <= 10; i++){
        for(int j = 1; j <= 10; j++){
            cout<<table[i][j];
        }
        cout<<endl;
    }
}

int main() {
    nod* avioane[3];

    clearTable(planesTable);
    clearTable(attackTable);

    for(int i = 0; i < 1; i++){
        int x, y;

        cout<<"Avion "<<i + 1<<" (x, y): ";
        cin>>x>>y;

        avioane[i] = buildPlane(x, y);

        if(avioane[i] == NULL) {
            cout<<"Valorile introduse sunt invalide!"<<endl;
            i--;
        }
    }

    appendPlane(avioane[0]);
    displayTable(planesTable);

    return 0;
}
