#include <stdio.h>
#include <stdlib.h>
#include <iostream>
using namespace std;
char array[200];
char salida[200];
char resultado;
struct pila{
	char operacion;
	pila *siguente;
};
void llenarEspacios(){
	for(int i=0;i<200;i++){
		array[i]=' ';
		salida[i]=' ';
	}
}
void crear_elemento(pila *&data,char ope){
	pila *aux;
	pila *aux2;
	if (data==NULL){
		aux=new pila();
		aux->operacion=ope;
		data=aux;
	}else{
		aux= new pila();
		aux->operacion=ope;
		aux2=data;
		aux->siguente=aux2;
		data=aux;
	}
}
void imprimirPila(pila *&data){
	pila *aux=data;
	while (aux!=NULL){
		cout<<"PILA:"<<aux->operacion<<endl;
		aux=aux->siguente;
	}
}
int evaluarJerarquia(char a){
	switch (a){
		case '^':
			return 3;
			break;
		case '*':
			return 2;
			break;
		case '/':
			return 2;
			break;
		case '-':
			return 1;
			break;
		case '+':
			return 1;
			break;
		case '(':
			return 0;
			break;
		default:
			return -1;
	}
}
void eliminarOperaciones(pila *&oper){
	pila *aux;
	aux=oper;
	oper=oper->siguente;
	delete aux;
}
void imprimirArray(int aux){
	for (int i=0;i<aux;i++){
		if (salida[i]!=' '){
			cout<<salida[i];
		}
	}
}
int main(){
	pila *operaciones= NULL;int cont=0,aux=0;bool flag=true;int jerarquiaActual;
	cout<<"INGRESE LA OPERACION INFIJA"<<endl;
	llenarEspacios();
	gets(array);
	while (flag){
		if (array[cont]==' '){
			flag=false;
		}
		if (array[cont]!=')'){
			jerarquiaActual=evaluarJerarquia(array[cont]);
			if (jerarquiaActual!=-1){
				if (jerarquiaActual!=0){
					if (operaciones==NULL){
						cout<<"EMPILANDO OPERACION"<<endl;
						crear_elemento(operaciones,array[cont]);
					}else{
						int jer2= evaluarJerarquia(operaciones->operacion);
						if (jer2!=0){
							if (jerarquiaActual>jer2){
								crear_elemento(operaciones,array[cont]);
							}else if (jer2>jerarquiaActual){
									cout<<"SACAR OPERADORES"<<endl;
									while ((operaciones!=NULL)&&(aux!='(')){
											pila *ayu;
											cout<<"WHILE SACAR OPERADORES"<<endl;
											salida[aux]=operaciones->operacion;
											ayu=operaciones;
											operaciones=operaciones->siguente;
											aux++;
											delete ayu;
											}
									crear_elemento(operaciones,array[cont]);
								}else if (jer2==jerarquiaActual){
										salida[aux]=operaciones->operacion;
										eliminarOperaciones(operaciones);
										aux++;
										crear_elemento(operaciones,array[cont]);
									}
						}else{
							cout<<"EMPILAR OPERACION CASO EN QUE EXISTA UN ("<<endl;
							crear_elemento(operaciones,array[cont]);
						}
					}	
				}else{
					cout<<"EMPILAR OPERACION ("<<endl;
					crear_elemento(operaciones,array[cont]);
				}
			}else{
				salida[aux]=array[cont];
				aux++;
			}
		}else{
			while (operaciones!=NULL){
				if (operaciones->operacion=='('){
					pila *aux=operaciones;
					operaciones=operaciones->siguente;
					delete aux;
					break;
				}else{
					salida[aux]=operaciones->operacion;
					aux++;
					operaciones=operaciones->siguente;
				}
			}
		}
		cont++;
	}
	while (operaciones!=NULL){
		salida[aux]=operaciones->operacion;
		operaciones=operaciones->siguente;
		aux++;
	}
	imprimirPila(operaciones);
	imprimirArray(aux);
	cout<<endl;
	system("pause");
}
