/*Intento de crear la Inteligencia artificial por medio de un metodo de
aprendizaje complejo y no tipico en el aprendizaje humano
inicio del proyecto: 11/07/04
Primera parte Inestable
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <conio.h>
//definicion de constantes
#define NOMBRE "ADAN"
#define CREADOR "DANIEL ALFONSI"
#define true  1
#define false  0
typedef int bool;

//definicion de variables globales
char explica[80],
	respuesta[80],
	sinonimo[50],
	otraPregunta[80];
FILE *ARCHIVO, *IMGARCHIVO;
//prototipos de Funciones
int preguntar(char *pregunta);
int responder(char *text,bool tipo);
void Upcase(char *text);
void buscaRespuesta(FILE *A,bool tipo);
void analiza_pregunta(char *pregunta);
int  interrogante(char *text);

//funcion principal
int main(){
	char texto[80];

	printf("\n..\n..Bienvenido al Sistema\n");
	do{
		printf("-Invitado>");
		gets(texto);
		Upcase(texto);
		if(interrogante(texto)==1){
			analiza_pregunta(texto);
		}
		else{
			responder(texto,true);
		}
	}while(!strcmp(texto,"EXIT")==0);
	return 0;
}
//analiza la pregunta segun los parametros
int  interrogante(char *text){
#define fila 4
	int ok=0;
	int i;
	char textTemp[2][80];
	char matriz[fila][80] = {{"QUE"},
				 {"EXPLICAME"},
				 {"SABES"},
				 {"CONOCES"}};
	strcpy(textTemp[0],text);
	for(i=0;i<=(int)strlen(text);i++){
		if(textTemp[0][i]==' ')break;
		textTemp[1][i] = textTemp[0][i];
	}
	textTemp[1][i] = '\0';
	for(i=0;i<fila;i++)if(strcmp(matriz[i],textTemp[1])==0){
	 ok = 1;
	 break;
	}
	return ok;
}
//analiza una pregunta y busca la respuesta
void analiza_pregunta(char *pregunta){
	char textTemp[3][80];
	int c=0;
	int i;
	strcpy(textTemp[0],pregunta);
	for(i=(int)strlen(pregunta);i>=0;i--){
		if(textTemp[0][i]==' ')break;
		textTemp[1][c] = textTemp[0][i-1];
		c++;
	}
	textTemp[1][c-1] = '\0';
	c=0;
	for(i=(int)strlen(textTemp[1]);i>=0;i--){
		textTemp[2][c] = textTemp[1][i-1];
		c++;
	}
	textTemp[2][c-1] = '\0';
	responder(textTemp[2],false);
}

//hace una pregunta y la guarda en memoria
int preguntar(char *pregunta){
	int ok=0;
	int opcion;
	printf("\nQue es eso, No lo conozco por Favor\nQuieres Explicarmelo?\nAdan(S/N)>");
	do{
		opcion=getch();
	}while(toupper(opcion)!='S'&& toupper(opcion)!='N');
	putchar('\n');
	if(toupper(opcion)=='S'){
		printf("\n..\n..\nQue es %s? (Se Breve):\n",pregunta);
		Upcase(pregunta);
		ARCHIVO = fopen(pregunta,"wt");
		gets(explica);
		if(strlen(explica)>0)ok=1;
		printf("\nDame una posible Respuesta:\n");
		gets(respuesta);
		printf("\nAhora algo que yo deba preguntar?:\n");
		gets(otraPregunta);
		fprintf(ARCHIVO,"%s\n%s\n%s",explica,respuesta,otraPregunta);
		printf("\nPor Favor y un Sinonimo de (%s)\n"\
			"Si no Conoces Escribe el Mismo:\n",pregunta);
		gets(sinonimo);
		printf("----Adan>Gracias por tu ayuda..\n");
		Upcase(sinonimo);
		IMGARCHIVO=fopen(sinonimo,"rt");
		if(IMGARCHIVO==NULL){
			IMGARCHIVO=fopen(sinonimo,"wt");
			fprintf(IMGARCHIVO,"%s\n%s\n%s",explica,respuesta,otraPregunta);
		}
		fclose(ARCHIVO);
		fclose(IMGARCHIVO);
	}
	return ok;
}

//responde auna peticion de informacion
int responder(char *text,bool tipo){
	int ok;
	ARCHIVO = fopen(text,"rt");
	if(ARCHIVO==NULL){
		IMGARCHIVO=fopen(text,"rt");
		if(IMGARCHIVO==NULL){
			preguntar(text);
		}
		else{
			if(tipo==true){
				buscaRespuesta(IMGARCHIVO,true);
				fclose(IMGARCHIVO);
			}
			else{
				buscaRespuesta(IMGARCHIVO,false);
				fclose(IMGARCHIVO);
			}
		}
	}
	else{
			if(tipo==true){
				buscaRespuesta(ARCHIVO,true);
				fclose(ARCHIVO);
			}
			else{
				buscaRespuesta(ARCHIVO,false);
				fclose(ARCHIVO);
			}
	}
	return ok;
}

//Busca una respuesta posible
void buscaRespuesta(FILE *A,bool tipo){
	char line[3][80];
	int i=0;
	rewind(A);
	while(!feof(A)){
		fgets(line[i],79,A);
		i++;
	}
	for(i=0;i<2;i++)if(strlen(line[i])<=0)line[i][0]='.';
	strcpy(explica,line[0]);
	strcpy(respuesta,line[1]);
	strcpy(otraPregunta,line[2]);
	if(tipo == true){
		printf("-----Adan>%s\n%s\n",respuesta,otraPregunta);
	}
	else{
		printf("-----Adan>%s\n%s\n",explica,otraPregunta);
	}
}

//transforma las letras todas en mayusculas
void Upcase(char *text){
	int c;
	char textTemp[80];
	for(c=0;c<(strlen(text));c++)
		textTemp[c]=toupper(text[c]);
	textTemp[strlen(text)]='\0';
	strcpy(text,textTemp);
}
