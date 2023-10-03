/**
 * Santiago Vázquez Villarreal - A01177850
 * Adrian Gómez - A008
 * Saúl Ortega Figueroa - A01252717
 * 
 * Fecha de creación: 28/09/2023
 * Fecha de modificación: 2/10/2023
 * V1
 * 
 * Este programa tienen como objetivo procesar un archivo llamado "bitacoraelb.txt", el cual contiene registros 
 * con direcciones IP y otros datos. El programa realiza lo siguiente:
 * 1. 
 * 
 * Notas:
 * 
 * 
*/

#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;

class Linea{
    private: 
        int year;
        string month;
        int monthDigit;
        int day;
        int hour;
        int minute;
        int second;
        string ip;
        string message;
    public:
        
        Linea(){
            year = 0;
            month = "";
            day = 0;
            hour = 0;
            minute = 0;
            second = 0;
            ip = "";
            message = "";
        }

        Linea(int year, string month, int day, int hour, int minute, int second, string ip, string message){
            this->year = year;
            this->month = month;
            this->day = day;
            this->hour = hour;
            this->minute = minute;
            this->second = second;
            this->ip = ip;
            this->message = message;
            
            //Digitos para cada mes
            if(month == "Jan"){
                monthDigit = 01;
            }
            else if(month == "Feb"){
                monthDigit = 02;
            }
            else if(month == "Mar"){
                monthDigit = 03;
            }
            else if(month == "Apr"){
                monthDigit = 4;
            }
            else if(month == "May"){
                monthDigit = 5;
            }
            else if(month == "Jun"){
                monthDigit = 6;
            }
            else if(month == "Jul"){
                monthDigit = 7;
            }
            else if(month == "Aug"){
                monthDigit = 8;
            }
            else if(month == "Sep"){
                monthDigit = 9;
            }
            else if(month == "Oct"){
                monthDigit = 10;
            }
            else if(month == "Nov"){
                monthDigit = 11;
            }
            else if(month == "Dec"){
                monthDigit = 12;
            }
        } 

        //getters
        int getYear(){
            return year;
        }
        string getMonth() {
            return month;
        }
        int getDay(){
            return day;
        }
        int getHour(){
            return hour;
        }
        int getMinute(){
            return minute;
        }
        int getSecond(){
            return second;
        }
        string getIp(){
            return ip;
        }
        string getMessage(){
            return message;
        }

        //Sobrecarga para operador <=
        bool operator<=(const Linea& linea){
            if(this->year < linea.year){
                return true;
            }
            else if(this->year == linea.year){
                if(this->monthDigit < linea.monthDigit){
                    return true;
                }
                else if(this->monthDigit == linea.monthDigit){
                    if(this->day < linea.day){
                        return true;
                    }
                    else if(this->day == linea.day){
                        if(this->hour < linea.hour){
                            return true;
                        }
                        else if(this->hour == linea.hour){
                            if(this->minute < linea.minute){
                                return true;
                            }
                            else if(this->minute == linea.minute){
                                if(this->second <= linea.second){
                                    return true;
                                }
                            }
                        }
                    }
                }
            }
            return false;
        }

};

template <class T> 
class Node{
    public:
        T linea;
        Node<T>* next;
        Node<T>* prev;
        
        Node(Linea linea){
            this->linea = linea;
            this->next = nullptr;
            this->prev = nullptr;
        }
};

//Doubly linked list
template <class T>
class List{
    private:
        Node<T>* head;
        Node<T>* tail;
    public:
        //Constructor por default
        List(){
            head = nullptr;
            tail = nullptr;
        }

        //Destructor 
        ~List(){
            Node<T>* current = head;
            while(current != nullptr){
                Node<T>* next = current->next;
                delete current;
                current = next;
            }
            head = nullptr;
            tail = nullptr;
        }

        //Insertar al final
        void insertEnd(T linea){
            Node<T>* newNode = new Node<T>(linea);
            if(head == nullptr){
                head = newNode;
                tail = newNode;
            }
            else{
                tail->next = newNode;
                newNode->prev = tail;
                tail = newNode;
            }
        }

        //Leer archivo bitacoraelb.txt
        void read(){
            ifstream file;
            file.open("bitacoraelb.txt");
            string line;
            while(getline(file, line)){
                stringstream ss(line);
                string year, month, day, hour, minute, second, ip, message;
                ss >> year; // Leer el año
                ss >> month;   // Leer el mes
                ss >> day;   // Leer el día
                getline(ss, hour, ':');  // Leer la hora
                getline(ss, minute, ':'); // leer el minuto
                getline(ss, second, ' '); // leer el segundo
                ss.ignore(6); // Ignorar " | IP: "
                ss >> ip;     // Leer la IP
                ss.ignore(8); // Ignorar " | INFO: "
                getline(ss, message, '\n'); // Fix: use '\n' instead of ' '
                Linea linea(stoi(year), month, stoi(day), stoi(hour), stoi(minute), stoi(second), ip, message);
                insertEnd(linea);
            }
            file.close();
        }

        void imprimirRango(Linea fechaInicio, Linea fechaFinal){
            Node<T>* current = head;
            while(current != nullptr){
                //Imprimir Fecha
                cout << current->linea.getYear() << " " << current->linea.getMonth() << " " << setw(2) << setfill('0') << current->linea.getDay() << " ";

                //Imprimir Hora
                cout << setw(2) << setfill('0') << current->linea.getHour() << ":"<< setw(2) << setfill('0')  << current->linea.getMinute() << ":" ;

                //Imprimir IP y mensaje
                cout << setw(2) << setfill('0')  << current->linea.getSecond() << " | IP: " << current->linea.getIp() << " | INFO: " << current->linea.getMessage() << endl;
                current = current->next;
            }
        }

        Node<T> *split(Node<T> *head){
            Node<T> *slow = head;
            Node<T> *fast = head -> next;

            while(fast != nullptr){
                fast = fast -> next;
                if(fast != nullptr){
                    slow = slow -> next;
                    fast = fast -> next;
                }
            }

            Node<T> *temp = slow -> next;
            slow -> next = nullptr;
            if(temp != nullptr){
                temp -> prev = nullptr;
            }

            return temp;
        }

        Node<T> *merge(Node<T> *first, Node<T> *second){
            if(first == nullptr){
                return second;
            }
            if(second == nullptr){
                return first;
            }

            if(first -> linea <= second -> linea){
                first -> next = merge(first -> next, second);
                first -> next -> prev = first;
                first -> prev = nullptr;
                return first;
            }
            else{
                second -> next = merge(first, second -> next);
                second -> next -> prev = second;
                second -> prev = nullptr;
                return second;
            }
        }

        Node<T> *mergeSort(Node<T> *head){
            if(head == nullptr || head -> next == nullptr){
                return head;
            }

            Node<T> *second = split(head);

            head = mergeSort(head);
            second = mergeSort(second);

            return merge(head, second);
        }

        void sortList(){
            head = mergeSort(head);
            Node<T> *temp = head;
            while(temp -> next != nullptr){
                temp = temp -> next;
            }
            tail = temp;
        }

};

int main(){
    List<Linea>* lista = new List<Linea>();

    int year;
    string month;
    int day;
    int hour;
    int minute;
    int second;

    cout << "Ingresa la fecha de inicio de rango" << endl;
   
    cout << "Ingrese el año" << endl;
    cin >> year;
    
    cout << "Ingrese el mes" << endl;
    cin >> month;

    cout << "Ingrese el día" << endl;
    cin >> day;

    cout << "Ingrese la hora" << endl;
    cin >> hour;

    cout << "Ingrese el minuto" << endl;
    cin  >> minute;

    cout << "Ingrese el segundo" << endl;
    cin >> second;

    //Objeto de inicio
    Linea fechaInicio(year, month, day, hour, minute, second, "", "");

    int yearFin;
    string monthFin;
    int dayFin;
    int hourFin;
    int minuteFin;
    int secondFin;

    cout << "Ingresa la fecha final del rango" << endl;
   
    cout << "Ingrese el año" << endl;
    cin >> yearFin;
    
    cout << "Ingrese el mes" << endl;
    cin >> monthFin;

    cout << "Ingrese el día" << endl;
    cin >> dayFin;

    cout << "Ingrese la hora" << endl;
    cin >> hourFin;

    cout << "Ingrese el minuto" << endl;
    cin  >> minuteFin;

    cout << "Ingrese el segundo" << endl;
    cin >> secondFin;

    //Objeto de inicio
    Linea fechaFin(yearFin, monthFin, dayFin, hourFin, minuteFin, secondFin, "", "");
    
    lista -> read();
    lista -> sortList();
    lista -> imprimirRango(fechaInicio, fechaFin);
    return 0;
}
