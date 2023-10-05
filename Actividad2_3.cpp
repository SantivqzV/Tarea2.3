/**
 * Santiago Vázquez Villarreal - A01177850
 * Adrian Gómez - A00835254
 * Saúl Ortega Figueroa - A01252717
 * 
 * Fecha de creación: 03/10/2023
 * 
 * V1
 * 
 * @brief Programa de procesamiento de registros de bitácora.
 * 
 * Este programa lee registros de un archivo de bitácora, los almacena en una lista doblemente enlazada,
 * permite al usuario especificar un rango de fechas y hora, y luego guarda las líneas de registro que
 * caen dentro de ese rango en un nuevo archivo.
 * 
 * El programa consta de tres clases principales:
 * 
 * 1. La clase Linea representa una línea de datos con información de fecha, hora, IP y mensaje.
 *    Proporciona métodos para comparar y acceder a los atributos de la línea.
 * 
 * 2. La clase Node representa un nodo en una estructura de datos tipo linked list doblemente enlazada.
 *    Cada nodo contiene un valor (en este caso, objetos Linea) y punteros al nodo siguiente y anterior.
 * 
 * 3. La clase List es una linked list doblemente enlazada que almacena objetos Linea.
 *    Ofrece funciones para leer datos desde un archivo de bitácora, ordenar la lista y filtrar líneas
 *    que caen dentro de un rango de fechas y hora especificado.
 * 
 * La función principal 'main' del programa interactúa con el usuario para ingresar las fechas y horas del rango,
 * realiza todas las operaciones necesarias utilizando las clases mencionadas y guarda los resultados en un archivo
 * llamado 'ResultadosOrdenados.txt'.
 * 
 * Referencias:
 * Merge Sort for Doubly Linked List. (2015, May 2). GeeksforGeeks; GeeksforGeeks. https://www.geeksforgeeks.org/merge-sort-for-doubly-linked-list/
 * De la Cueva, V (2020). Estructuras de datos y algoritmos fundamentales. Editorial Digital Tecnológico de Monterrey. 
 */

#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;

/**
 * @class Linea
 * 
 * @brief Representa una línea de datos con información de fecha, hora, IP y mensaje.
 * 
 * La clase Linea proporciona una estructura para almacenar 
 * y manipular datos relacionados con líneas de información. 
 * Cada objeto Linea contiene información como el año, mes, 
 * día, hora, minuto, segundo, dirección IP y mensaje. 
 * Además, la clase proporciona constructores para inicializar 
 * objetos con estos datos y getters para acceder a ellos.
*/

class Linea{
    private: 
        int year;           ///< Año de la línea de datos.
        string month;       ///< Mes de la línea de datos en formato de tres letras (por ejemplo, "Jan" para enero).
        int monthDigit;     ///< Representación numérica del mes.
        int day;            ///< Día de la línea de datos.
        int hour;           ///< Hora de la línea de datos.
        int minute;         ///< Minuto de la línea de datos.
        int second;         ///< Segundo de la línea de datos.
        string ip;          ///< Dirección IP asociada a la línea de datos.
        string message;     ///< Mensaje contenido en la línea de datos.
    public:
        /**
         * @brief Constructor por defecto de la clase Linea.
         * 
         * Inicializa todos los atributos de la clase con valores predeterminados.
        */
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
        
        /**
         * @brief Constructor de la clase Linea con parámetros.
         * 
         * Este constructor permite inicializar un objeto Linea con valores específicos para cada atributo.
         * 
         * @param year Año de la línea de datos.
         * @param month Mes de la línea de datos en formato de tres letras (por ejemplo, "Jan" para enero).
         * @param day Día de la línea de datos.
         * @param hour Hora de la línea de datos.
         * @param minute Minuto de la línea de datos.
         * @param second Segundo de la línea de datos.
         * @param ip Dirección IP asociada a la línea de datos.
         * @param message Mensaje contenido en la línea de datos.
        */
        Linea(int year, string month, int day, int hour, int minute, int second, string ip, string message){
            this->year = year;
            this->month = month;
            this->day = day;
            this->hour = hour;
            this->minute = minute;
            this->second = second;
            this->ip = ip;
            this->message = message;
            
            // Asignando el valor numérico correspondiente al mes.
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

        // Getters para acceder a los atributos de la clase.
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

        /**
         * @brief Compara dos objetos de la clase Linea para determinar si son iguales. Sobrecarga de ""=="
         * 
         * Esta función verifica si dos objetos de la clase Linea son iguales comparando
         * sus atributos de fecha y hora (year, monthDigit, day, hour, minute y second).
         * Si todos los atributos coinciden, la función devuelve true; de lo contrario, devuelve false.
         * 
         * @param[in] linea El objeto Linea con el que se va a comparar.
         * 
         * @return true si los objetos Linea son iguales en cuanto a fecha y hora, false en caso contrario.
         * 
         * @note Complejidad de tiempo: O(1) - La comparación de los atributos toma tiempo constante.
         * @note Complejidad de espacio: O(1) - No se asignan nuevos recursos ni se utiliza memoria adicional.
        */
       bool operator==(const Linea& linea) const {
            // Compara el atributo 'year' de este objeto con el atributo 'year' de 'linea'
            return this->year == linea.year &&
                // Compara el atributo 'monthDigit' de este objeto con el atributo 'monthDigit' de 'linea'
                this->monthDigit == linea.monthDigit &&
                // Compara el atributo 'day' de este objeto con el atributo 'day' de 'linea'
                this->day == linea.day &&
                // Compara el atributo 'hour' de este objeto con el atributo 'hour' de 'linea'
                this->hour == linea.hour &&
                // Compara el atributo 'minute' de este objeto con el atributo 'minute' de 'linea'
                this->minute == linea.minute &&
                // Compara el atributo 'second' de este objeto con el atributo 'second' de 'linea'
                this->second == linea.second;
        }

        /**
         * @brief Compara dos objetos de la clase Linea para determinar si el objeto actual es mayor o igual al objeto dado. Sobrecarga de >=
         * 
         * Esta función compara dos objetos de la clase Linea para verificar si el objeto actual es mayor o igual
         * al objeto dado en términos de su fecha y hora. La comparación se realiza en orden, primero comparando el año,
         * luego el mes, el día, la hora, el minuto y finalmente el segundo.
         * 
         * @param[in] linea El objeto Linea con el que se va a comparar.
         * 
         * @return true si el objeto actual es mayor o igual al objeto dado en cuanto a fecha y hora, false en caso contrario.
         * 
         * @note Complejidad de tiempo: O(1) - La comparación de los atributos toma tiempo constante y la función devuelve tan pronto como se determina el resultado.
         * @note Complejidad de espacio: O(1) - No se asignan nuevos recursos ni se utiliza memoria adicional.
        */
        bool operator>=(const Linea& linea) const {
            // Compara el atributo 'year' de este objeto con el atributo 'year' de 'linea'
            if (this->year > linea.year) {
                return true;
            }
            // Si los años son iguales, compara el atributo 'monthDigit'
            else if (this->year == linea.year) {
                if (this->monthDigit > linea.monthDigit) {
                    return true;
                }
                // Si los meses son iguales, compara el atributo 'day'
                else if (this->monthDigit == linea.monthDigit) {
                    if (this->day > linea.day) {
                        return true;
                    }
                    // Si los días son iguales, compara el atributo 'hour'
                    else if (this->day == linea.day) {
                        if (this->hour > linea.hour) {
                            return true;
                        }
                        // Si las horas son iguales, compara el atributo 'minute'
                        else if (this->hour == linea.hour) {
                            if (this->minute > linea.minute) {
                                return true;
                            }
                            // Si los minutos son iguales, compara el atributo 'second'
                            else if (this->minute == linea.minute) {
                                if (this->second >= linea.second) {
                                    return true;
                                }
                            }
                        }
                    }
                }
            }
            // Si ninguno de los casos anteriores se cumple, retorna false
            return false;
        }


        /**
         * @brief Compara dos objetos de la clase Linea para determinar si el objeto actual es menor o igual al objeto dado. Sobrecarga de <=
         * 
         * Esta función compara dos objetos de la clase Linea para verificar si el objeto actual es menor o igual
         * al objeto dado en términos de su fecha y hora. La comparación se realiza en orden, primero comparando el año,
         * luego el mes, el día, la hora, el minuto y finalmente el segundo.
         * 
         * @param[in] linea El objeto Linea con el que se va a comparar.
         * 
         * @return true si el objeto actual es menor o igual al objeto dado en cuanto a fecha y hora, false en caso contrario.
         * 
         * @note Complejidad de tiempo: O(1) - La comparación de los atributos toma tiempo constante y la función devuelve tan pronto como se determina el resultado.
         * @note Complejidad de espacio: O(1) - No se asignan nuevos recursos ni se utiliza memoria adicional.
        */
        bool operator<=(const Linea& linea) {
            // Compara el atributo 'year' de este objeto con el atributo 'year' de 'linea'
            if (this->year < linea.year) {
                return true;
            }
            // Si los años son iguales, compara el atributo 'monthDigit'
            else if (this->year == linea.year) {
                if (this->monthDigit < linea.monthDigit) {
                    return true;
                }
                // Si los meses son iguales, compara el atributo 'day'
                else if (this->monthDigit == linea.monthDigit) {
                    if (this->day < linea.day) {
                        return true;
                    }
                    // Si los días son iguales, compara el atributo 'hour'
                    else if (this->day == linea.day) {
                        if (this->hour < linea.hour) {
                            return true;
                        }
                        // Si las horas son iguales, compara el atributo 'minute'
                        else if (this->hour == linea.hour) {
                            if (this->minute < linea.minute) {
                                return true;
                            }
                            // Si los minutos son iguales, compara el atributo 'second'
                            else if (this->minute == linea.minute) {
                                if (this->second <= linea.second) {
                                    return true;
                                }
                            }
                        }
                    }
                }
            }
            // Si ninguno de los casos anteriores se cumple, retorna false
            return false;
        }


};

/**
 * @class Node
 * Representa un nodo en una estructura de datos tipo linked list doblemente enlazada.
 * 
 * Esta clase proporciona una estructura básica para representar un nodo en una linked list doblemente enlazada.
 * Cada nodo contiene un valor de tipo 'T', y punteros al nodo siguiente y al nodo anterior en la lista.
 * La clase también incluye un constructor para inicializar el nodo con un valor.
 * 
 * @tparam T El tipo de datos que se almacenará en el nodo.
*/
template <class T> 
class Node {
public:
    T linea;          /// Almacena el valor de tipo 'T' del nodo.
    Node<T>* next;    /// Puntero al siguiente nodo en la lista.
    Node<T>* prev;    /// Puntero al nodo anterior en la lista.
    
    /**
     * @brief Constructor de Node
     * @param linea El valor de tipo 'T' que se asignará al nodo.
     * @param next, puntero al siguiente nodo
     * @param prev, puntero al nodo anterior
     */
    Node(T lineaVal){
        linea = lineaVal;
        next = nullptr;
        prev = nullptr;
    }
};

/**
 * @class List
 * @brief Representa una linked list doblemente enlazada.
 * 
 * Esta clase proporciona una estructura para crear, leer, actualizar y eliminar elementos en una linked list doblemente enlazada.
 * Los elementos se almacenan como nodos que contienen valores de tipo 'T'.
 * 
 * @tparam T El tipo de datos que se almacenará en la linked list.
*/
template <class T>
class List{
    private:
        Node<T>* head; // Apuntador al primer nodo de la lista.
        Node<T>* tail; // Apuntador al último nodo de la lista.
    public:
        /**
         * @brief constructor por default de List.
         * 
         * Inicializa la linked list como vacía al establecer los punteros 'head' y 'tail' en nullptr.
         * 
         * @param head, puntero al siguiente nodo de la lista
         * @param tail, puntero al nodo anterior de la lista
        */
        List(){
            head = nullptr;
            tail = nullptr;
        }

        /**
         * @brief Destructor de List.
         * 
         * Libera la memoria de todos los nodos de la linked list y establece los punteros 'head' y 'tail' en nullptr.
        */ 
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

        /**
         * @brief Inserta un nuevo elemento al final de la lista doblemente enlazada.
         * 
         * Esta función crea un nuevo nodo con el valor especificado como 'linea' y lo inserta al final de la lista.
         * Si la lista está vacía, el nuevo nodo se convierte tanto en la cabeza (head) como en la cola (tail) de la lista.
         * Si la lista no está vacía, el nuevo nodo se enlaza con el último nodo existente y se actualiza la cola (tail).
         * 
         * @param[in] linea El valor que se va a insertar al final de la lista.
         * 
         * @return Nada se devuelve explícitamente ya que la función modifica la lista en su lugar.
         * 
         * @note Complejidad de tiempo: O(1) - La inserción al final de la lista siempre toma tiempo constante.
         * @note Complejidad de espacio: O(1) - Se crea un nuevo nodo, pero no se asignan nuevos recursos ni se utiliza memoria adicional.
        */
        void insertarFinal(T linea) {
            // Crear un nuevo nodo con el valor 'linea'
            Node<T>* newNode = new Node<T>(linea);
            // Si la lista está vacía, 'head' y 'tail' apuntan al nuevo nodo
            if (head == nullptr) {
                head = newNode;
                tail = newNode;
            } 
            else {
                // Si la lista no está vacía, enlazar el nuevo nodo al final de la lista
                tail->next = newNode;
                newNode->prev = tail;
                tail = newNode;
            }
        }

        /**
         * @brief Lee datos de un archivo de registro y los almacena en la lista doblemente enlazada.
         * 
         * Esta función abre el archivo "bitacoraelb.txt" y lee cada línea de registro. Luego, procesa y extrae
         * los datos relevantes de cada línea, como año, mes, día, hora, minuto, segundo, dirección IP y mensaje.
         * Utiliza estos datos para crear un objeto Linea y lo inserta al final de la lista doblemente enlazada.
         * 
         * @return Nada se devuelve explícitamente ya que la función modifica la lista en su lugar.
         * 
         * @note Complejidad de tiempo: O(N) - Donde N es la cantidad de líneas en el archivo de registro.
         * @note Complejidad de espacio: O(1) - Se asignan recursos para almacenar los datos de cada línea, pero no se utiliza memoria adicional significativa.
        */
        void read() {
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
                getline(ss, minute, ':'); // Leer el minuto
                getline(ss, second, ' '); // Leer el segundo
                ss.ignore(6); // Ignorar " | IP: "
                ss >> ip;     // Leer la IP
                ss.ignore(8); // Ignorar " | INFO: "
                getline(ss, message, '\n'); // Utilizar '\n' en lugar de ' ' para leer el mensaje
                Linea linea(stoi(year), month, stoi(day), stoi(hour), stoi(minute), stoi(second), ip, message);
                // Insertar la nueva línea al final de la lista doblemente enlazada
                insertarFinal(linea);
            }
            file.close();
        }

        /**
         * @brief Imprimir en terminal el registro del rango de fechas indicado por el usuario
         * 
         * Esta función recorre la lista doblemente enlazada y verifica si cada línea de registro se encuentra dentro del
         * rango de fechas especificado entre 'fechaInicio' y 'fechaFinal'. Si una línea está dentro del rango, la escribe
         * en la terminal en un formato específico que incluye año, mes, día, hora, minuto, segundo,
         * dirección IP y mensaje.
         * 
         * @param[in] fechaInicio El objeto Linea que representa la fecha de inicio del rango.
         * @param[in] fechaFinal El objeto Linea que representa la fecha final del rango.
         * 
         * @return Nada se devuelve explícitamente ya que la función escribe en el archivo 'outputFile'.
         * 
         * @note Complejidad de tiempo: O(N) - Donde N es la cantidad de nodos en la lista doblemente enlazada.
         * @note Complejidad de espacio: O(1) - No se asignan nuevos recursos ni se utiliza memoria adicional significativa.
        */
        void imprimirRango(Linea fechaInicio, Linea fechaFinal) {
            Node<T>* current = head;
            while (current != nullptr) {
                // Verificar si la línea actual está dentro del rango especificado
                if (current->linea >= fechaInicio && current->linea <= fechaFinal) {
                    // Escribe la Fecha en el archivo
                    cout << current->linea.getYear() << " " << current->linea.getMonth() << " " << setw(2) << setfill('0') << current->linea.getDay() << " ";
                    // Escribe la Hora en el archivo
                    cout << setw(2) << setfill('0') << current->linea.getHour() << ":" << setw(2) << setfill('0') << current->linea.getMinute() << ":";
                    // Escribe la IP y el mensaje en el archivo
                    cout << setw(2) << setfill('0') << current->linea.getSecond() << " | IP: " << current->linea.getIp() << " | INFO: " << current->linea.getMessage() << endl;
                }
                current = current->next;
            }
        }

        /**
         * @brief Imprime en un archivo todas las líneas de registro.
         * 
         * Esta función recorre la lista doblemente enlazada y la escribe en el archivo de salida 'outputFile' en un formato 
         * específico que incluye año, mes, día, hora, minuto, segundo, dirección IP y mensaje.
         * 
         * @param[in,out] outputFile El archivo de salida donde se escribirán las líneas de registro dentro del rango.
         * 
         * @return Nada se devuelve explícitamente ya que la función escribe en el archivo 'outputFile'.
         * 
         * @note Complejidad de tiempo: O(N) - Donde N es la cantidad de nodos en la lista doblemente enlazada.
         * @note Complejidad de espacio: O(1) - No se asignan nuevos recursos ni se utiliza memoria adicional significativa.
        */
        void imprimirEnArchivo(ofstream& outputFile) {
            Node<T>* current = head;
            while (current != nullptr) {
                // Escribe la Fecha en el archivo
                outputFile << current->linea.getYear() << " " << current->linea.getMonth() << " " << setw(2) << setfill('0') << current->linea.getDay() << " ";
                // Escribe la Hora en el archivo
                outputFile << setw(2) << setfill('0') << current->linea.getHour() << ":" << setw(2) << setfill('0') << current->linea.getMinute() << ":";
                // Escribe la IP y el mensaje en el archivo
                outputFile << setw(2) << setfill('0') << current->linea.getSecond() << " | IP: " << current->linea.getIp() << " | INFO: " << current->linea.getMessage() << endl;
                current = current->next;
            }
        }

        /**
         * @brief Divide una lista doblemente enlazada en dos partes iguales.
         * 
         * Esta función divide la lista doblemente enlazada en dos partes aproximadamente iguales.
         * Utiliza el método de dos punteros, uno que se mueve a la mitad de la lista (slow) y otro que se
         * mueve al final de la lista (fast). Luego, separa las dos partes y actualiza los enlaces de los nodos.
         * 
         * @param[in] head El puntero al nodo cabeza de la lista.
         * 
         * @return Un puntero al nodo cabeza de la segunda mitad de la lista.
         * 
         * @note Complejidad de tiempo: O(N) - Donde N es la cantidad de nodos en la lista doblemente enlazada.
         * @note Complejidad de espacio: O(1) - La función no asigna nuevos recursos ni utiliza memoria adicional significativa.
        */
        Node<T> *split(Node<T> *head) {
            Node<T> *slow = head;
            Node<T> *fast = head->next;

            // Avanzar 'fast' dos nodos por cada iteración y 'slow' un nodo por cada iteración
            while (fast != nullptr) {
                fast = fast->next;
                if (fast != nullptr) {
                    slow = slow->next;
                    fast = fast->next;
                }
            }

            // Separar la segunda sublista de la primera sublista
            Node<T> *temp = slow->next;
            slow->next = nullptr;

            // Actualizar el puntero 'prev' del primer nodo de la segunda sublista
            if (temp != nullptr) {
                temp->prev = nullptr;
            }

            return temp;
        }

        /**
         * @brief Combina dos sublistas en una lista ordenada.
         * 
         * Esta función combina dos sublistas en una sola lista ordenada. Las sublistas están representadas por los punteros
         * 'first' y 'second', y la función fusiona estas sublistas en orden ascendente en función del valor de 'linea' de los nodos.
         * 
         * @param[in] first El puntero al nodo cabeza de la primera sublista.
         * @param[in] second El puntero al nodo cabeza de la segunda sublista.
         * 
         * @return Un puntero al nodo cabeza de la lista fusionada.
         * 
         * @note Complejidad de tiempo: O(N) - Donde N es la cantidad total de nodos entre ambas sublistas.
         * @note Complejidad de espacio: O(1) - La función no asigna nuevos recursos ni utiliza memoria adicional significativa.
        */
        Node<T> *merge(Node<T> *first, Node<T> *second) {
            if (first == nullptr) {
                return second;
            }
            if (second == nullptr) {
                return first;
            }
            // Comparar los valores de los nodos y enlazarlos en orden ascendente
            if (first->linea <= second->linea) {
                first->next = merge(first->next, second);
                first->next->prev = first;
                first->prev = nullptr;
                return first;
            } else {
                second->next = merge(first, second->next);
                second->next->prev = second;
                second->prev = nullptr;
                return second;
            }
        }


        /**
         * @brief Ordena una lista doblemente enlazada utilizando el algoritmo Merge Sort.
         * 
         * Esta función implementa el algoritmo Merge Sort para ordenar una lista doblemente enlazada.
         * Divide la lista en dos partes aproximadamente iguales, ordena ambas partes recursivamente y luego
         * fusiona las dos partes ordenadas en una sola lista ordenada.
         * 
         * @param[in] head El puntero al nodo cabeza de la lista a ordenar.
         * 
         * @return Un puntero al nodo cabeza de la lista ordenada.
         * 
         * @note Complejidad de tiempo: O(N log N) - Donde N es la cantidad de nodos en la lista doblemente enlazada.
         * @note Complejidad de espacio: O(1) - La función no asigna nuevos recursos ni utiliza memoria adicional significativa.
        */
        Node<T> *mergeSort(Node<T> *head) {
            // Casos base: Si la lista está vacía o tiene un solo elemento, ya está ordenada
            if (head == nullptr || head->next == nullptr) {
                return head;
            }
            // Dividir la lista en dos sublistas
            Node<T> *second = split(head);
            // Ordenar ambas sublistas recursivamente
            head = mergeSort(head);
            second = mergeSort(second);
            // Combinar las sublistas ordenadas en una sola lista ordenada
            return merge(head, second);
        }

        /**
         * @brief Se manda a llamar el algoritmo de ordenamiento y actualiza tail
         * 
         * Esta función manda a llamar el algoritmo de ordenamiento para la lista doble ligada. 
         * Despues de ordenar la lista se actualiza el tail de la lista. 
         * 
         * @return Nada se devuelve explícitamente ya que la función modifica la lista en su lugar.
         * 
         * @note Complejidad de tiempo: O(N log N) - Donde N es la cantidad de nodos en la lista doblemente enlazada.
         * @note Complejidad de espacio: O(1) - La función no asigna nuevos recursos ni utiliza memoria adicional significativa.
        */
        void comenzarOrdenamiento() {
            // Aplicar Merge Sort para ordenar la lista
            head = mergeSort(head);

            // Actualizar 'tail' para que apunte al último nodo de la lista
            Node<T> *temp = head;
            while (temp->next != nullptr) {
                temp = temp->next;
            }
            tail = temp;
        }
};

int main(){
    // Crear una instancia de la clase List que almacena objetos Linea
    List<Linea>* lista = new List<Linea>();
    // Declarar variables para la fecha de inicio
    int year;
    string month;
    int day;
    int hour;
    int minute;
    int second;

    // Solicitar al usuario ingresar la fecha de inicio
    cout << "Ingresa la fecha de inicio de rango" << endl;
    cout << "Ingrese el año" << endl;
    cin >> year;
    cout << "Ingrese el mes en abreviación (Ejemplo: Jan, Oct, Dec): " << endl;
    cin >> month;
    cout << "Ingrese el día" << endl;
    cin >> day;
    cout << "Ingrese la hora" << endl;
    cin >> hour;
    cout << "Ingrese el minuto" << endl;
    cin  >> minute;
    cout << "Ingrese el segundo" << endl;
    cin >> second;

    // Crear un objeto Linea para la fecha de inicio
    Linea fechaInicio(year, month, day, hour, minute, second, "", "");

    // Declarar variables para la fecha de fin
    int yearFin;
    string monthFin;
    int dayFin;
    int hourFin;
    int minuteFin;
    int secondFin;

    // Solicitar al usuario ingresar la fecha de fin
    cout << endl << "Ingresa la fecha final del rango" << endl;
    cout << "Ingrese el año" << endl;
    cin >> yearFin;
    cout << "Ingrese el mes en abreviación (Ejemplo: Jan, Oct, Dec): " << endl;
    cin >> monthFin;
    cout << "Ingrese el día" << endl;
    cin >> dayFin;
    cout << "Ingrese la hora" << endl;
    cin >> hourFin;
    cout << "Ingrese el minuto" << endl;
    cin  >> minuteFin;
    cout << "Ingrese el segundo" << endl;
    cin >> secondFin;

    // Crear un objeto Linea para la fecha de fin
    Linea fechaFin(yearFin, monthFin, dayFin, hourFin, minuteFin, secondFin, "", "");

    // Leer datos de un archivo y almacenarlos en la lista
    lista->read();

    // Ordenar la lista
    lista -> comenzarOrdenamiento();

    // Imprimir El rango buscado en terminal
    lista->imprimirRango(fechaInicio, fechaFin);

    // Abrir un archivo de salida llamado 'ResultadosOrdenados.txt'
    ofstream outputFile("ResultadosOrdenados.txt");
    if (outputFile.is_open()) {
        // Imprimir en el archivo las líneas que caen dentro del rango de fechas especificado
        lista->imprimirEnArchivo(outputFile);
        // Cierra el archivo
        outputFile.close();
        cout << "Archivo ordenado en 'ResultadosOrdenados.txt'" << endl;
    } 
    else {
        cerr << "No se pudo abrir el archivo 'ResultadosOrdenados.txt'" << endl;
    }

    // Liberar la memoria de la instancia de la clase List
    delete lista;

    return 0;
}