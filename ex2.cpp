#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

#define TAM 100  

//Implementación del nivel físico de un ABB
template <class T>
class NodoArbol
{ public:
	T info;
	NodoArbol<T> *izq, *der;
	NodoArbol() { izq = der = NULL; }
	NodoArbol(T dato) { info = dato; izq = der = NULL; }
};

template <class T>
class ABB
{
private:
		NodoArbol<T> *raiz;
		bool converso;
public:
		ABB() { raiz = NULL; converso = false; }
		ABB(bool es_converso) { raiz = NULL; converso = es_converso; }
		NodoArbol<T>* getRaiz() { return raiz; } 
		void inserta (T dato);
		void despliega() { inorden(raiz); }
		int cuenta () { return contar(raiz); }
		int altura () { return niveles(raiz); }
		bool busqueda (T dato);
		~ABB() { libera(raiz); }
};

template <class T>
void libera (NodoArbol<T>* raiz)
{
	if (raiz != NULL)
	{ 
		libera(raiz->izq);
		libera(raiz->der);
		delete(raiz);
	}
}

template <class T>
void inorden (NodoArbol<T>* raiz)
{
	if (raiz != NULL)
	{ 
		inorden(raiz->izq);
		cout << raiz->info <<" ";
		inorden(raiz->der);
	}
}

template <class T>
int contar (NodoArbol<T>* raiz)
{
	if (raiz == NULL)
		return 0;
	return(1+contar(raiz->izq)+contar(raiz->der));
}

template <class T>
int niveles (NodoArbol<T>* raiz)
{
	int altizq, altder;
	if (raiz == NULL)  return 0;
	altizq = niveles(raiz->izq);
	altder = niveles(raiz->der);
	return(1 + (altizq>altder? altizq : altder));
}

template <class T>
void ABB<T>::inserta (T valor)
{
	NodoArbol<T> *NuevoNodo = new NodoArbol<T>(valor);
	NodoArbol<T> *actual = raiz, *anterior = NULL;
	while (actual != NULL)
	{
		anterior=actual;
		if (converso) {
			actual=(actual->info<valor? actual->izq: actual->der);
		}else{
			actual=(actual->info>valor? actual->izq: actual->der);
		}
	}
	if (anterior==NULL){
		raiz = NuevoNodo;
	}else{
		if (converso) {
			if (anterior->info < valor)
				anterior->izq = NuevoNodo;
			else
				anterior->der = NuevoNodo;

		}else{
			if (anterior->info > valor)
				anterior->izq = NuevoNodo;
			else
				anterior->der = NuevoNodo;
		}
	}
}

template <class T>
bool ABB<T>::busqueda (T valor)
{
	NodoArbol<T> *aux = raiz; 
	int comparaciones = 1;
	while(aux != NULL && aux->info!=valor){
		if(converso){
			if(aux->info < valor){
				aux = aux->izq;
			}else{
				aux = aux->der;
			}
		}else{
			if(aux->info > valor){
				aux = aux->izq;
			}else{
				aux = aux->der;
			}

		}
	}
	if(aux==NULL){
		cout<<"Tomaron "<<comparaciones<<" para averiguar que el dato "<<valor<< " no existe en el arbol."<<endl;
		return false;
	}else{
		cout<<"Tomaron "<<comparaciones<<" para encontrar el dato "<<valor<<" ."<<endl;
		return true;
	}
}

// Implementación del nivel físico de una Tabla de Hash

template <class T>
class tablaHash
{
private:
	ABB<T> tabla[TAM];
	int cantidad;
	
public:
	tablaHash() {cantidad = 0;}
	void inserta (T dato);
	void despliega ();
};

template <class T>
void tablaHash<T>::inserta (T dato)
{
	int posicion = dato / 100 % TAM;
	tabla[posicion].inserta(dato);
	cantidad++;
}

template <class T>
void tablaHash<T>::despliega()
{
	cout << "Cantidad de datos: "<<cantidad<<"\n";
	for (int i = 0; i < TAM; i++)
	{
   	   cout << "Posicion "<<i<<": "<<tabla[i].cuenta()<<" datos en "<<tabla[i].altura()<<" niveles ";
	   tabla[i].despliega();
	   cout << "\n";
	}
}

// Implemetación del programa de aplicación
int main()
{
	ifstream arch;
	string nomarch;
	int dato;
	cout << "Ingrese el nombre del archivo a cargar: ";
	cin >> nomarch;

	arch.open(nomarch.c_str());

	ABB<int> arbolNormal;
	ABB<int> arbolConverso(true);
	while (!arch.eof())
	{
		arch >> dato;
		// aqui se inserta el dato en la estructura de datos que se desee.
		arbolNormal.inserta(dato);
		arbolConverso.inserta(dato);
	}
	arch.close();
	// cin>>nomarch;
	
	//PROBLEMA 1 =============================
	cout<<"ARBOL NORMAL"<<endl;
	arbolNormal.despliega();
	cout<<endl;
	
	cout<<"ARBOL CONVERSO"<<endl;
	arbolConverso.despliega();
	cout<<endl;

	cout<<"ARBOL NORMAL"<<endl;
	cout<<"La altura del arbol normal es de: "<<arbolNormal.altura()<<endl;
	cout<<"La raiz del arbol normal es: "<<arbolNormal.getRaiz()->info<<endl;
	arbolNormal.busqueda(143012);
	cout<<endl;

	cout<<"ARBOL CONVERSO"<<endl;
	cout<<"La altura del arbol converso es de: "<<arbolConverso.altura()<<endl;
	cout<<"La raiz del arbol converso es: "<<arbolConverso.getRaiz()->info<<endl;
	arbolConverso.busqueda(143012);
	cout<<endl;

	return 0;
}


