#include <iostream>
#include <cstring>
#include <fstream>
#include <cmath>
#include <utility>
#include <iomanip>
#include <limits>
#include <cctype>  // for isdigit and isalpha
using namespace std;

ifstream a1("Figure.txt");
ifstream b1("Dimens.txt");

int n; 

const string RESET = "\033[0m";
const string BLACK = "\033[30m";
const string RED = "\033[31m";
const string GREEN = "\033[32m";
const string YELLOW = "\033[33m";
const string BLUE = "\033[34m";
const string MAGENTA = "\033[35m";
const string CYAN = "\033[36m";
const string WHITE = "\033[37m";
const string BOLD = "\033[1m";
const string UNDERLINE = "\033[4m";

struct sphere {
    
    //a1
    int id_sphere;
    string color;
    string material;

    //b1
    int coordonate;
    int radius;

    float volume;
    float area;
    
} a[99];

void readData(){

    while (a1 >> a[n].id_sphere >> a[n].color >> a[n].material) {
        n++;
    }

    int i = 0;
    while (b1 >> a[i].id_sphere >> a[i].coordonate >> a[i].radius) {
        i++;
    }

    a1.close();
    b1.close();
}

void writeData(){
    ofstream a2("Figure.txt");
    ofstream b2("Dimens.txt");

    
    for(int i = 0; i < n; i++){
        a2 << a[i].id_sphere << " " << a[i].color << " " << a[i].material << endl;
        b2 << a[i].id_sphere << " " << a[i].coordonate << " " << a[i].radius << endl;
    }
}

void clear(){
    system("cls");
}

void space(){
    cout << "                                       ";
}

void waitForEnter() {
    cout << "Apasati Enter pentru a continua...";
    cin.ignore(numeric_limits<int>::max(), '\n');
    while (cin.get() != '\n') {
        cout << "Va rog apasati doar enter...";
        cin.ignore(numeric_limits<int>::max(), '\n');

    }
}

void volumeCalc(){
    const float PI = 3.14159265359;
    for (int i = 0; i < n; i++) {
        a[i].volume = 4 * PI * pow(a[i].radius, 3) / 3;
        a[i].area = 4 * PI * pow(a[i].radius, 2);
    }
}

void volumeAverage_by_color(){

    volumeCalc();
    clear();

    char color_n[20];
    
    cout << "Introduceti culoarea: ";

    bool found = false;
    while(true){
        cin >> color_n;

        for(int i = 0; i < n; i++){
            if (a[i].color == color_n){
                found = true;
                break;
            }
        }

        if(found == true)
            break;
        
        
        cout << "Reintroduceti culoarea: ";

    }

    float sum = 0;
    int k = 0;
    for(int i = 0; i < n; i++){
        if(a[i].color == color_n){
            sum += a[i].volume;
            k++;
        }
    }

    float volumeAverage = sum / k;
    
    cout << "Media volumului sferelor de culoarea " << color_n << " este " << volumeAverage << endl;

    waitForEnter();
}

void volumeDisplay() {

    clear();
    volumeCalc();
    
    ofstream fout("Volume.txt");

    for (int i = 0; i < n; i++) {
        
        fout << "ID: " << a[i].id_sphere << " Volum: " << a[i].volume << " Arie: " << a[i].area << endl;
    }

    fout.close();

    waitForEnter();
}

void showInfo_Figure(sphere a[], int n){
    clear();
    for (int i = 0; i < n; i++){
        
        cout << a[i].id_sphere << " " << a[i].color << " " << a[i].material << endl;
    }
    waitForEnter();
}

void showInfo_Dimens(sphere a[], int n){
    clear();

    for (int i = 0; i < n; i++){
        
        cout << a[i].id_sphere << " " << a[i].coordonate << " " << a[i].radius << endl;
    }
    waitForEnter();
}

bool valid_number(const string& str){
    for (char ch : str){
        if(!isdigit(ch))
            return false;
    }
    return true;
}

void max_min_radius(){
    clear();

    int max = -999, max_i = 0;
    int min = 999, min_i = 0;

    for(int i = 0; i < n; i++){
        if (a[i].radius < min){
            min = a[i].radius;
            min_i = i;
        } else if (a[i].radius > max){
            max = a[i].radius;
            max_i = i;
        }
    }

    
    cout << "Sfera cu raza cea mai mica: " << a[min_i].id_sphere << ", cu raza de " << a[min_i].radius << endl; 
    cout << "Sfera cu raza cea mai mare: " << a[max_i].id_sphere << ", cu raza de " << a[max_i].radius << endl;

    waitForEnter();
}

int  ID_verifcation(){

    clear();

    int id_n, index = 0;
    string input;

    
    cout << "Introduceti ID-ul: ";
    
    bool found = false;

    while(true){

        cin >> input;

        if(valid_number(input)){

            id_n = stoi(input);

            for(int i = 0; i < n; i++){
                if(a[i].id_sphere == id_n){
                    index = i;
                    found = true;
                }
            }

            if (found == true)
                break;

        }

        
        cout << "Reintroduceti ID-ul: ";

    }

    return index;
    waitForEnter();
}

void changeInfo(sphere a[], int n);

void exclude_sphere(sphere a[], int&n){

    clear();

    int id_n;
    string input; 
    
    cout << "Introduceti ID-ul sferei: ";

    bool found = false;
    
    int j = -1;

    while(true){

        cin >> input;

        if(valid_number(input)){

            id_n = stoi(input);

            for(int i = 0 ; i < n; i++){
                if(a[i].id_sphere == id_n){
                    j = i;
                    found = true;
                    break;
                }
            }

            if (found)
                break;

        }

        
        cout << "Introduceti un ID valid: ";
    }

    for (int i = j; i < n - 1; i++) {
        a[i] = a[i + 1];
    }
    
    
    cout << "Sfera a fost eliminata cu succes\n";
    n--;

    writeData();
    waitForEnter();

}

void new_dimension(sphere a[], int& n){

    clear();

    int x;

    string input;
    
    cout << "Introduceti ID-ul sferei: ";

    bool found = false, leave = false;

    while(true){

        cin >> input;

        if(valid_number(input)){
            int id_n = stoi(input); // transformam in int

            if  (id_n == 0){
                leave = true;
                break;
            }

            found = false;

            for (int i = 0; i < n; i++){
                if (a[i].id_sphere == id_n){
                    x = i;  
                    found = true;
                    break;  
                }
            }

            if (found)
                break;

        }
        
        
        cout << "ID gresit, reintroduceti sau tastati 0 pentru a iesi: ";

    }

    if(leave == true)
        return;
    

    string radius;

    
    cout << "Introduceti noua raza: ";

    int rad_n;

    while(true){

        cin >> radius;

        if (valid_number(radius)){

            rad_n = stoi(radius);

            if(rad_n > 0 && rad_n < 100){
                break;
            }

        }

        
        cout << "Introduceti o marime valida: ";
    }

    a[x].radius = rad_n;

    writeData();
    waitForEnter();
}

string getColor(){

    clear();

    char culoare_n[20];
    
    cout << "Introduceti culoarea: ";

    bool valid_input = false;

    while (!valid_input) { //mai intai verificam daca ceia ce am introdus este string

        cin >> culoare_n;

        valid_input = true;
        for (char c : culoare_n) { //for each-loop pentru fiecare caracter
            if (isdigit(c)) {
                valid_input = false;
                cout << "Introduceti o culoare valabila: ";
                break;
            }
        }
    }

    return culoare_n;
}

string getMaterial(){

    clear();

    char material_n[20];
    
    cout << "Introduceti materialul: ";

    bool valid_input = false;

    while (!valid_input) { //mai intai verificam daca ceia ce am introdus este string

        cin >> material_n;

        valid_input = true;
        for (char c : material_n) { //for each-loop pentru fiecare caracter
            if (isdigit(c)) {
                valid_input = false;
                
                cout << "Introduceti un material valabil: ";
                break;
            }
        }
    }

    return material_n;
}

int getRadius(){

    clear();

    string input;
    int rad_n;
    
    cout << "Introduceti raza: ";
    
    while(true){
        cin >> input;

        if(valid_number(input)){
            rad_n = stoi(input);

            if(rad_n > 0 && rad_n < 100){
                break;
            }
        }

        
        cout << "Reintroduceti o marime valabila: ";
    }

    return rad_n;
}

int getID(){

    clear();

    string input;
    int id_n;
    
    cout << "Introduceti noul ID-ul: ";

    bool valid = true;
    
    while(true){

        cin >> input;

        if(valid_number(input)){

            id_n = stoi(input);

            valid = true;

            for(int i = 0; i < n; i++){
                if(a[i].id_sphere == id_n){
                    valid = false;
                }
            }

            if(valid)
                break;
        }

        
        cout << "Reintroduceti noul ID-ul: ";
    }

    return id_n;
}

bool verifyChar(const string& character) {
    for (char c : character) {
        if (!isalpha(c)) {
            return false;
        }
    }
    return true;
}

void new_sphere(sphere a[], int& n){
    
    clear();

    sphere newSphere;

    int id_n;

    bool found = false, leave = false;

    while(true){
        
        id_n = getID();
  

        for(int i = 0; i < n; i++){
            if (a[i].id_sphere == id_n){
                found = true;
            }
        }

        if (!found)
            break;
        
        
        cout << "ID deja existent, reintroduceti: ";
    }

    newSphere.id_sphere = id_n;
    
    newSphere.color = getColor();

    newSphere.material= getMaterial();

    a[n].material = newSphere.material; 
    a[n].color = newSphere.color;
    a[n].id_sphere = newSphere.id_sphere;
    a[n].coordonate = 0;
    a[n].radius = 0;

    n++;

    writeData();

    waitForEnter();
}

bool checkMaterial(const string& material_n, sphere a[], int n){

    for(int i = 0; i < n; i++){
        if(a[i].material == material_n)
            return true;
    }
    return false;
}

string verification_material(){

    clear();

    char material_n[20];
    
    cout << "Introduceti materialul: ";

    bool valid_input = false, found = false;

    while (!valid_input) { //mai intai verificam daca ceia ce am introdus este string

        cin >> material_n;

        valid_input = verifyChar(material_n);

        if(valid_input){ //daca este validat continua spre baza de date
            
            found = checkMaterial(material_n, a, n); // parcurgem baza de date

            if(found)
                valid_input = true;
            else
                valid_input = false; //in caz contrar while-ul se repeta
        }

        
        cout << "Reintroduceti un material valabil: ";
    }

    return material_n;
}

void find_the_material(sphere a[], int n) {

    string material_n = verification_material();
    
    clear();

    for (int i = 0; i < n; i++) {
        if (a[i].material == material_n) {
            
            cout << "ID-ul: " << a[i].id_sphere << " Culoarea: " << a[i].color << endl;

        }
    }

    waitForEnter();
}

void meniu(){
    
    space();
    cout << CYAN << BOLD << "=================================================================\n" << RESET; space();
    cout << YELLOW << BOLD << setw(41) << left << "                              Meniu" << RESET << endl; space();
    cout << CYAN << BOLD << "=================================================================\n" << RESET; space();
    cout << YELLOW << "|  0  |   " << RESET << "Iesire" << endl; space();
    cout << YELLOW << "|  1  |   " << RESET << "Afiseaza informatia din " << BLUE << BOLD << "Figure.txt" << RESET << endl; space();
    cout << YELLOW << "|  2  |   " << RESET << "Afiseaza informatia din " << BLUE << BOLD << "Dimens.txt" << RESET << endl; space();
    cout << YELLOW << "|  3  |   " << RESET << "Inregistreaza o sfera noua" << endl; space();
    cout << YELLOW << "|  4  |   " << RESET << "Inregistreaza o dimensiune noua" << endl; space();
    cout << YELLOW << "|  5  |   " << RESET << "Exclude o sfera" << endl; space();
    cout << YELLOW << "|  6  |   " << RESET << "Actualizeaza datele sferei" << endl; space();
    cout << YELLOW << "|  7  |   " << RESET << "Creaza fisierul " << BLUE << BOLD << "Volume.txt" << RESET << endl; space();
    cout << YELLOW << "|  8  |   " << RESET << "Afiseaza sferele dintr-un material specific" << endl; space();
    cout << YELLOW << "|  9  |   " << RESET << "Afiseaza sferele cu raza minima si maxima" << endl; space();
    cout << YELLOW << "|  10 |   " << RESET << "Afiseaza volumul mediu al sferelor de o culoare specifica" << endl; space();
    cout << CYAN << BOLD << "=================================================================\n" << RESET; space();
}

void program() {

    int option;

    volumeCalc();
    
    do {
        system("cls");
        
        readData();
        
        meniu();

        
        cout << CYAN << BOLD << "Optiune: " << RESET;
        
        while (!(cin >> option)) {
            cin.clear(); 
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
            clear();
            meniu();
            
            cout << CYAN << BOLD << "Introduceti un numar valabil: " << RESET;
        }

        switch (option){

           case 0 : {
                clear();
                
                cout << CYAN << BOLD << "La revedere" << RESET << endl;
            }
                break;
            case 1 : {
                showInfo_Figure(a, n);
            }
                break;
            case 2 : {
                showInfo_Dimens(a, n);
            }
                break;
            case 3 : {
                new_sphere(a, n);
            }
                break;
            case 4 : {
                new_dimension(a, n);
            }
                break;
            case 5 : {
                exclude_sphere(a, n);
            }
                break;
            case 6 : {
                changeInfo(a, n);
            }
                break;
            case 7 : {
                volumeDisplay();
            }
                break;
            case 8 : {
                find_the_material(a, n);
            }
                break;
            case 9 : {
                max_min_radius();
            }
                break;
            case 10 : {
                  volumeAverage_by_color();
            }
                break;

            default: {
                
                cout << "Optiune invalida" << endl;
            }
                break;
        }
        
    } while (option != 0);
    

}
  
void changeID(sphere a[], int n, int index){

    clear();

    int id_n;

    bool found = false;

    while(true){

        id_n = getID();

        for(int i = 0; i < n; i++){
            if (a[i].id_sphere == id_n){
                found = true;
            }
        }

        if (found == false)
            break;

        
        cout << "ID deja existent, reintroduceti: ";
    }

    a[index].id_sphere = id_n;

    writeData();

}

void changeColor(sphere a[], int n, int index){

    string color_n;

    while(true){
        
        color_n = getColor();

        if (a[index].color != color_n)
            break;

        
        cout << "Introduceti alta culoare: ";

    }  

    a[index].color = color_n; 
    writeData();

}

void changeMaterial(sphere a[], int n, int index){

    string material_n;

    while(true){
        
        material_n = getMaterial();

        if (a[index].material != material_n) 
            break;

        
        cout << "Introduceti alt material: ";

    }  

    a[index].material = material_n;
    writeData();
}

void changeRadium(sphere a[], int n, int index){

    int rad_n;

    while(true){

        rad_n = getRadius();


        if (rad_n != a[index].radius)
            break;

        
        cout << "Introduceti alta raza: ";

    }  

    a[index].radius = rad_n;
    writeData();
}

void changeInfo(sphere a[], int n){

    int userIndex = ID_verifcation();
    
    int op;

    do {
 
        clear();

        space();
        cout << CYAN << BOLD << "=========================================\n" << RESET; space();
        cout << YELLOW << setw(41) << left << "            Meniul schimbarilor:" << RESET << endl; space();
        cout << CYAN << BOLD << "=========================================\n" << RESET; space();
        cout << YELLOW << " 1. " << RESET << BLUE << BOLD << " ID-ul" << RESET << endl; space();
        cout << YELLOW << " 2. " << RESET << BLUE << BOLD << "Culoarea" << RESET << endl; space();
        cout << YELLOW << " 3. " << RESET << BLUE << BOLD << "Materialul" << RESET << endl; space();
        cout << YELLOW << " 4. " << RESET << BLUE << BOLD << "Raza" << RESET << endl; space();
        cout << YELLOW << " 5. " << RESET << BLUE << BOLD << "Revenire la meniul principal" << RESET << endl; space();
        cout << CYAN << BOLD << "=========================================\n" << RESET; space();
        
        cin >> op;

        switch(op){
            case 1 : {
                changeID(a, n, userIndex);
            }
                break;
            case 2 : {
                changeColor(a, n, userIndex);
            }
                break;
            case 3 : {
                changeMaterial(a, n, userIndex);
            }
                break;
            case 4 : {
                changeRadium(a, n, userIndex);
            }
                break;
            case 5 : {
                //exit
                break;
            }
                break;
        }


    } while(op != 5);

}


