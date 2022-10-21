#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include<fstream>


using namespace std;

bool esSigno(char caracter)//Comprueba si el carácter dado es un signo o no
{
    if (caracter == ' ' || caracter == '+' || caracter == '-' || caracter == '*' || 
        caracter == '/' || caracter == ',' || caracter == ';' || caracter == '>' || 
        caracter == '<' || caracter == '=' || caracter == '(' || caracter == ')' || 
        caracter == '[' || caracter == ']' || caracter == '{' || caracter == '}' || 
        caracter == '&' || caracter == '|'){
        return true;
    }
    return false;
}

bool esIdentificador(char* cad)//Comprueba si el identificador dado es válido o no
{
    if (cad[0] == '0' || cad[0] == '1' || cad[0] == '2' || cad[0] == '3' || 
        cad[0] == '4' || cad[0] == '5' || cad[0] == '6' || cad[0] == '7' || 
        cad[0] == '8' || cad[0] == '9' || esSigno(cad[0]) == true){
        return false;
    }//Si el primer carácter de la cad es un dígito o un carácter especial, el identificador no es válido

    int i,longitud = strlen(cad);

    if (longitud == 1){//Si la longitud es uno, la validación ya se ha completado, por lo que devuelve true
        return true;
    }else{
        for (i = 1 ; i < longitud ; i++){//el identificador no puede contener caracteres especiales
            if (esSigno(cad[i]) == true){
                return false;
            }
        }
    }
    return true;
}

bool esOperador(char caracter){//Comprueba si el carácter dado es un operador o no
    if (caracter == '+' || caracter == '-' || caracter == '*' ||
        caracter == '/' || caracter == '>' || caracter == '<' ||
        caracter == '=' || caracter == '|' || caracter == '&'){
        return true;
    }
    return false;
}

bool esReservada(char *cad){//Comprueba si la subcadena dada es una palabra clave o no
    if (!strcmp(cad, "if") || !strcmp(cad, "else") ||
        !strcmp(cad, "while") || !strcmp(cad, "do") ||
        !strcmp(cad, "break") ||  !strcmp(cad, "continue")
        || !strcmp(cad, "int") || !strcmp(cad, "double")
        || !strcmp(cad, "float") || !strcmp(cad, "return")
        || !strcmp(cad, "char") || !strcmp(cad, "case")
        || !strcmp(cad, "long") || !strcmp(cad, "short")
        || !strcmp(cad, "typedef") || !strcmp(cad, "switch")
        || !strcmp(cad, "unsigned") || !strcmp(cad, "void")
        || !strcmp(cad, "static") || !strcmp(cad, "struct")
        || !strcmp(cad, "sizeof") || !strcmp(cad,"long")
        || !strcmp(cad, "volatile") || !strcmp(cad, "typedef")
        || !strcmp(cad, "enum") || !strcmp(cad, "const")
        || !strcmp(cad, "union") || !strcmp(cad, "extern")
        || !strcmp(cad,"bool")){
        return true;
    }else{
       return false;
    }
}

bool esNumero(char* cad){//Comprueba si la subcadena dada es un número o no
    int longitud = strlen(cad), numOfDecimal = 0;

    if (longitud == 0){
        return false;
    }

    for (int i = 0 ; i < longitud ; i++){

        if (numOfDecimal > 1 && cad[i] == '.'){
            return false;
        } else if (numOfDecimal <= 1){
            numOfDecimal++;
        }

        if (cad[i] != '0' && cad[i] != '1' && cad[i] != '2' && cad[i] != '3' && 
            cad[i] != '4' && cad[i] != '5' && cad[i] != '6' && cad[i] != '7' && 
            cad[i] != '8' && cad[i] != '9' || (cad[i] == '-' && i > 0)){
            return false;
        }
    }
    return true;
}

char* subCad(char* cadInicial, int l, int r){//extrae la subcadena requerida de la cadena principal

    char* cad = (char*) malloc(sizeof(char) * (r - l + 2));

    for (int i = l; i <= r; i++){
        cad[i - l] = cadInicial[i];
        cad[r - l + 1] = '\0';
    }
    return cad;
}


void analisisLexico(char* cad){//Analiza la expresión
    int izq = 0, der = 0;
    int longitud = strlen(cad);

    while (der <= longitud && izq <= der) {
        if (esSigno(cad[der]) == false){//Comprueba que no sea un signo
                der++;
                // cout << "IZQUIERDA: " << izq <<endl;
                // cout << "DERECHA: " << der <<endl;
        }

        if (esSigno(cad[der]) == true && izq == der){//Si es carácter es un signo
            if (esOperador(cad[der]) == true){
                cout<< cad[der] <<" \t==> Es un Operador\n";
            }
            der++;
            izq = der;
        } else if (esSigno(cad[der]) == true && izq != der || (der == longitud && izq != der)){//Comprueba si la subcadena analizada es una palabra clave, un identificador o un número
            // cout << "derecha: " << der <<endl;
            char* sub = subCad(cad, izq, der - 1);//Extrae la subcadena

            if (esReservada(sub) == true){
                cout<< sub <<" \t==> Es una Palabra Reservada\n";
            }else if (esNumero(sub) == true){
                cout<< sub <<" \t==> Es un Numero\n";
            }else if (esIdentificador(sub) == true && esSigno(cad[der - 1]) == false){
                cout<< sub <<" \t==> Es un Identificador Valido\n";
            }else if (esIdentificador(sub) == false && esSigno(cad[der - 1]) == false){
                cout<< sub <<" \t==> No es un Identificador Valido\n";
            }
            izq = der;
        }
    }
    return;
}

int main()
{
	FILE *pf;
	int r;
	char cadena[300];
	
	if((pf=fopen("texto.txt","r"))!=NULL){
		while(!feof(pf)){
			fgets(cadena,50,pf);
		}
		fclose(pf);
	}

    //char c[100] = "8.54 int m = n + 3p + 8";
    system("pause");
    analisisLexico(cadena);
    system("pause");
    return 0;
}
