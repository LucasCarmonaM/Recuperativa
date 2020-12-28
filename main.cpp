#include <iostream>
#include <cstdlib>
#include <cmath>
#include <ctime>
#include <mpi.h>
#include <string>
#include <vector>
#include <fstream>

using namespace std;


int pos_anio(int anio){
    return(1990-anio);
}


int main(int argc, char** argv ){


    // Salario minimo a dolar
    vector<float> smi_dolar;

    // Codigo para obtener los datos del archivo smi.csv
    string linea="";
    string path = "/home/lucasACM/Desktop/Recuperativa_paralela/smi.csv";
    ifstream archivoEntrada(path);
    std::vector<int> valores_smi, year_smi;
    for(linea; getline(archivoEntrada, linea);){
        if(!linea.empty()){
            if(linea[0]!='y'){
                string value="";
                // For para sacar el value de la linea
                for(int i=8;i<9999;i++){
                    if(linea[i]=='"'||linea[i]=='.'){
                        valores_smi.push_back(stoi(value));
                        break;
                    }
                    value += linea[i];
                }

                string year="";
                // For para sacar el año de la linea
                for(int i=1;i<9999;i++){
                    if(linea[i]=='"'){
                        year_smi.push_back(stoi(year));
                        break;
                    }
                    year += linea[i];
                }
            }
        }
    }



    // Codigo para obtener los datos del archivo dollars.csv
    string linea2="";
    string path2 = "/home/lucasACM/Desktop/Recuperativa_paralela/dollars.csv";
    ifstream archivoEntrada2(path2);

    // estos vectores contienen los dolares y años en misma posicion como corresponda
    std::vector<float> promedio_dollars, anio_dollars;

    // Se inicializa anio como hola para que al realizar primera comparacion se cumpla y se calcule el promoedio ya que obviamente no existe un año antes del primero
    string anio="hola",anio2="";
    string dolar = "";
    int cont = 0;
    float dolares = 0;
    for(linea2; getline(archivoEntrada2, linea2);){
        if(!linea2.empty()){
            if(linea2[0]!='d'){
                for(int i=1;i<5;i++){
                    anio2 += linea2[i];
                }
                if(anio2==anio||anio[0]=='h'){

                    for(int i=14;i<9999;i++){
                        if(linea2[i]=='"'){
                            dolares += stof(dolar);
                            cont += 1;
                            break;
                        }
                        dolar += linea2[i];
                    } 
                }else{
                    // Realizar division, obtener promedio y añadirlo al vector con los promedios correspondientes
                    promedio_dollars.push_back(dolares/cont);
                    anio_dollars.push_back(stoi(anio));
                    if(stoi(anio)>1994){
                        smi_dolar.push_back(valores_smi[stoi(anio)-1995]/(dolares/cont));
                    }
                    
                    cont = 0;
                    dolares = 0;
                    dolar = "";
                }
                anio="";
                // obtenemos el año de la linea
                for(int i=1;i<5;i++){
                    anio += linea2[i];
                }
            }
            anio2="";

        }
    }

    // For para imprimir el promedio dolar y el año correspondiente
    for(int i = 0;i<year_smi.size();i++){
        cout << "Salario minimo para el año: " << year_smi[i] << " en dolares es: " << smi_dolar[i] << endl;
    }

}

