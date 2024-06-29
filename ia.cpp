/*Intento de crear la Inteligencia artificial por medio de un metodo de
aprendizaje complejo y no tipico en el aprendizaje humano
inicio del proyecto: 11/07/04
Primera parte Inestable

solo lenguaje español
*/
#include <iostream>
#include <cstdio> // Para usar funciones como printf y getchar
#include <cstdlib>
#include <cstring> // Para usar funciones como strtok y strcpy
#include <cctype> // Para usar la función toupper
#include <ctime>

//definicion de constantes
const char* NOMBRE = "ADAN";
const char* CREADOR = "DANIEL ALFONSI";
using namespace std;

//definicion de variables globales
char explica[100];
char respuesta[100];
char sinonimo[100];
char otraPregunta[100];
FILE* ARCHIVO = nullptr;
FILE* IMGARCHIVO = nullptr;
//prototipos de Funciones
int preguntar(char* pregunta);
int responder(char* text, bool tipo);
void Upcase(char* text);
void buscaRespuesta(FILE* A, bool tipo);
void analiza_pregunta(char* pregunta,bool tipo);
bool interrogante(char* text);
bool randomBoolean();

//funcion principal
int main(){
	
    char texto[100];
    char nombre_invitado[80];

    std::cout << "\n..\n..Bienvenido Mi nombre es ADAN\n";
	strcpy(nombre_invitado,"INVITADO");
	
    do {
        std::cout << "-" << nombre_invitado << ">";
		memset(texto, 0, sizeof(texto));
		cin.clear();
		fflush(stdin);
        std::cin.getline(texto, sizeof(texto));
        Upcase(texto);
		std::size_t longitud = std::strlen(texto);
        char* resultado = strstr(texto, "MI NOMBRE ES");
        if (resultado != nullptr) {
            const char* delimitador = " ";
            int parada = 0;
            char* token = strtok(texto, delimitador);
            while (token != nullptr) {
                if (strcmp(token, "ES") == 0) {
                    parada++;
                }
                token = strtok(nullptr, delimitador);
                if (parada == 1) {
                    strcpy(nombre_invitado, token);
                    break;
                }
            }
        }
		if(longitud > 0)
        if (interrogante(texto)) {
            analiza_pregunta(texto,true);
        } else {
			bool resultado = randomBoolean();
            responder(texto, resultado);
        }
    } while (strcmp(texto, "EXIT") != 0);

    return 0;
}

bool randomBoolean() {
    srand(static_cast<unsigned int>(time(nullptr)));
    int randomval = rand() % 2;
    return randomval == 1;
}

bool interrogante(char* text){
    const int fila = 8;
    int ok = false;
    int i;
    char textTemp[100];
    const char matriz[fila][100] = {{"QUE"},
									{"SOBRE"},
									{"QUIEN"},
									{"DIME"},
                                    {"EXPLICAME"},
                                    {"SABES"},
                                    {"HABLAME"},
                                    {"CONOCES"}};	
		strcpy(textTemp, text);
       if (textTemp != nullptr) {
            const char* delimitador = " ";
            char* token = strtok(textTemp, delimitador);
            while (token != nullptr) {				
				for (i = 0; i < fila; i++) {
					if (strcmp(token, matriz[i]) == 0) {
						ok = true;
						break;
					}
				}
                token = strtok(nullptr, delimitador);
                if (ok == true) {
                    break;
                }
            }
        }
		return ok;
}

//analiza una pregunta y busca la respuesta
void analiza_pregunta(char* pregunta,bool tipo) {
    char textTemp[3][100];
    int c = 0;
    int i;
    strcpy(textTemp[0], pregunta);
    for (i = static_cast<int>(strlen(pregunta)); i >= 0; i--) {
        if (textTemp[0][i] == ' ')
            break;
        textTemp[1][c] = textTemp[0][i - 1];
        c++;
    }
    textTemp[1][c - 1] = '\0';
    c = 0;
    for (i = static_cast<int>(strlen(textTemp[1])); i >= 0; i--) {
        textTemp[2][c] = textTemp[1][i - 1];
        c++;
    }
    textTemp[2][c - 1] = '\0';
    responder(textTemp[2], tipo);
}

//hace una pregunta y la guarda en memoria
int preguntar(char* pregunta) {
    int ok = 0;
    char opcion;
	char textPregunta[100];	
	strcpy(textPregunta, pregunta);
    std::cout << "\nQue es " << textPregunta << "? No lo conozco, por favor explicamelo. (S/N)\n";
    do {
        opcion = std::cin.get();
    } while (std::toupper(opcion) != 'S' && std::toupper(opcion) != 'N');
    std::cout << '\n';
    if (std::toupper(opcion) == 'S') {
        std::cout << "\n..\n..Que Debo Responder a: " << textPregunta << "? (Se breve):\n";				
        Upcase(const_cast<char*>(textPregunta)); // Quitamos la constante para usar Upcase
        FILE* ARCHIVO = std::fopen(textPregunta, "wt");
        char explica[100];
		cin.clear();
		fflush(stdin);
        std::cin.getline(explica, sizeof(explica));
        if (std::strlen(explica) > 0) {
            ok = 1;
        }
        char respuesta[100];
        std::cout << "\nDame una explicacion un poco detallada:\n";
		cin.clear();
		fflush(stdin);		
        std::cin.getline(respuesta, sizeof(respuesta));
        char otraPregunta[100];
        std::cout << "\nAhora algo que yo deba preguntar o responder:\n";
        std::cin.getline(otraPregunta, sizeof(otraPregunta));
        std::fprintf(ARCHIVO, "%s\n%s\n%s", explica, respuesta, otraPregunta);
        char sinonimo[100];
        std::cout << "\nPor favor, un sinonimo de (" << pregunta << ")\n"
                  << "Si no lo conoces, escribe el mismo:\n";
		cin.clear();
		fflush(stdin);				  
        std::cin.getline(sinonimo, sizeof(sinonimo));
        std::cout << "-ADAN> Gracias por tu ayuda...\n";
        Upcase(sinonimo);
        FILE* IMGARCHIVO = std::fopen(sinonimo, "rt");
        if (IMGARCHIVO == nullptr) {
            IMGARCHIVO = std::fopen(sinonimo, "wt");
            std::fprintf(IMGARCHIVO, "%s\n%s\n%s", explica, respuesta, otraPregunta);
        }
        std::fclose(ARCHIVO);
        std::fclose(IMGARCHIVO);
    }
    return ok;
}

//responde auna peticion de informacion
int responder(char* text, bool tipo) {
	char textTemp[100];
	strcpy(textTemp, text);
    FILE* ARCHIVO = std::fopen(textTemp, "rt");
    if (ARCHIVO == nullptr) {
        FILE* IMGARCHIVO = std::fopen(textTemp, "rt");
        if (IMGARCHIVO == nullptr) {
            // Si no se encuentra el archivo, preguntar al usuario.
            preguntar(textTemp);
        } else {
            if (tipo) {
                buscaRespuesta(IMGARCHIVO, true);
            } else {
                buscaRespuesta(IMGARCHIVO, false);
            }
            std::fclose(IMGARCHIVO);
        }
    } else {
        if (tipo) {
            buscaRespuesta(ARCHIVO, true);
        } else {
            buscaRespuesta(ARCHIVO, false);
        }
        std::fclose(ARCHIVO);
    }
    // Aquí podrías asignar un valor a 'ok' si es necesario.
    int ok = 0;
    return ok;
}

//Busca una respuesta posible
void buscaRespuesta(FILE* A, bool tipo) {
    char line[3][100];
    int i = 0;
    std::rewind(A);
    while (!std::feof(A)) {
        std::fgets(line[i], 99, A);
        i++;
    }
    for (i = 0; i < 2; i++) {
        if (std::strlen(line[i]) <= 0) {
            line[i][0] = '.';
        }
    }
    char explica[100];
    char respuesta[100];
    char otraPregunta[100];
    std::strcpy(explica, line[0]);
    std::strcpy(respuesta, line[1]);
    std::strcpy(otraPregunta, line[2]);
    if (tipo) {
        std::cout << "-ADAN> " << respuesta << '\n' << otraPregunta << '\n';
    } else {
        std::cout << "-ADAN> " << explica << '\n' << otraPregunta << '\n';
    }
}

//transforma las letras todas en mayusculas
void Upcase(char* str) {
    while (*str) {
        *str = std::toupper(*str);
        str++;
    }
}
