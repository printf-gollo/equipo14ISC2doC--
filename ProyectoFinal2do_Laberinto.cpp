#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <limits>

using namespace std;

int REN, COL;
int posF = -1, posC = -1;

int** llenar();
void mostrar(int **mat);
int suma(int **mat);
void liberar(int **mat);
void dimension();

int main(){
    int sumTot=0;
    srand(time(NULL)); // semilla del rand

    dimension(); // Pedir el tamaño al usuario

    int **mat = llenar(); // Llenar la matriz

    mostrar(mat); // Mostrar la matriz

    sumTot = suma(mat); // Sumar y buscar chacales (proceso general)
    
    cout << "\nSuma total: " << sumTot<< endl;

    if(posF != -1 && posC != -1){
        cout << "Ultima posicion antes de detenerse:\n";
        cout << "Renglon: " << posF << "\tColumna: " << posC << endl;
    }

    liberar(mat); // Liberar la memoria

    return 0;
}

int **llenar(){
    int **aux = new int*[REN];
    for(int i=0; i<REN; ++i){
        aux[i] = new int[COL];
    }

    for(int i=0; i<REN; i++){
        for(int j = 0; j < COL; j++){
            aux[i][j] = rand() % 10;
        }
    }

    return aux;
}

void mostrar(int **mat){
    for(int i=0; i<REN; i++){
        for(int j=0; j<COL; j++){
            cout << mat[i][j] << "\t";
        }
        cout << endl;
    }
    cout << endl;
}

void dimension(){
    FILE *archivo;

    // 2. Crear el archivo de texto en el almacenamiento
    archivo = fopen("proLiz.txt", "w"); // Con w crea y sobreescribe, con a no sobreescribe

    // true para repetir el ciclo las veces que sean necesarias 
    while(true){
        cout << "Ingresa numero de renglones (minimo 5, maximo 15): ";
        cin >> REN;

        // 3. grabar informacion en el archivo
        fprintf(archivo, "%d\n",REN);

        // Validar si no es numero
        if(cin.fail()){
            cin.clear(); // Limpiar error
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Limpiar buffer
            cout << "Entrada no valida, debes ingresar solo numeros" << endl << endl;
            continue;
        }

        cout << "Ingresa numero de columnas (minimo 5, maximo 15): ";
        cin >> COL;

        if(cin.fail()){
            cin.clear(); // Limpiar error
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Limpiar buffer
            cout << "Entrada no valida, debes ingresar solo numeros " << endl << endl;
            continue;
        }

        if(REN != COL){
            cout << "Error, la matriz debe ser cuadrada (REN y COL deben ser iguales)" << endl;
            continue;
        }

        if(REN < 5 || REN > 15 || COL < 5 || COL > 15){
            cout << "Error, valores fuera de rango (mínimo 5, maximo 15)" << endl << endl;
            continue;
        }

        break; // Si todo esta bien, salimos del ciclo
    }
}

int suma(int **mat){
    int sumTot = 0;
    int chacales = 0;

    // Recorre diagonal principal
    for(int i=0; i<REN; i++){
        if(mat[i][i] == 0){
            chacales++;
            cout << "\nChacal encontrado en la posicion [" << i << "," << i << "]   Total: " << chacales << endl;
            if(chacales == 3){
                posF = i;
                posC = i;
                cout << "\nTe encontraste 3 chacales!!!\n";
                break;
            }
        }
        sumTot += mat[i][i];
    }

    // Si aun no hay 3 chacales recorre la ultima columna
    if(chacales < 3){
        for(int i = 0; i < REN; i++){
            if(mat[i][COL-1] == 0){
                chacales++;
                cout << "\nChacal encontrado en la posicion [" << i << "," << COL-1 << "]   Total: " << chacales << endl;
                if(chacales == 3){
                    posF = i;
                    posC = COL-1;
                    cout << "\nTe encontraste 3 chacales!!!\n";
                    break;
                }
            }
            sumTot += mat[i][COL-1];
        }
    }

    sumTot = sumTot - mat[REN-1][COL - 1];
    cout << "Chacales encontrados: " << chacales << endl;
    return sumTot;
}

void liberar(int **mat){
    for(int i = 0; i < REN; i++){
        delete[] mat[i];
    }
    delete[] mat;
}
