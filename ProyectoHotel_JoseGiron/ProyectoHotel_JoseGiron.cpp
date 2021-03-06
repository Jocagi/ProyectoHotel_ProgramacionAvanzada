// Proyecto_Hoteles.cpp : Defines the entry point for the console application.
//

#include "pch.h"
#include <iostream>

#include <stdio.h>
#include <stdlib.h>
#include <string>

#include <conio.h>

#include <fstream>
#include <cctype>
#include <iomanip>

using namespace std;

//****************************************************************************
//                   CLASE TARJETA
//****************************************************************************

class Tarjeta {

public:
	string Nombre; // Nombre de la tarjeta
	string Numero; //Numero de la tarjeta
	string Expiracion; //Fecha de vencimiento de la tarjeta
	string Seguridad; //Codigo de seguridad de la tarjeta 

	void Borrar() {
		Nombre = "";
		Numero = "";
		Expiracion = "";
		Seguridad = "";
	}
};

//************************************************************************************
//                   CLASE PERSONA
//************************************************************************************
class Persona {

public:

	string Nombre; // Nombre de la persona
	string Documento; //Numero de DPI o Pasaporte
	Tarjeta TarjetaDeCredito; //Acceso a numero de la tarjeta, expiración, seguridad y nombre

	void Borrar() {
		Nombre = "";
		Documento = "";
		TarjetaDeCredito.Borrar();
	}
};

//************************************************************************************
//                   Inventario (Lista)
//************************************************************************************
class Articulo {
public:
	string Nombre;
	int Cantidad;
	double Precio;

};

//************************************************************************************
//                   CLASE HABITACION
//************************************************************************************

class Habitacion {

public:
	Persona Huesped;
	Articulo ListaInicial[10];
	Articulo ListaFinal[10];
	int Elementos_lista;

	int Dias;

	int Cama;
	int NumCuarto;
	bool PetFriendly;
	bool AC;
	double Precio;

	bool Disponible;
	string CheckIn;
	string CheckOut;

	void Inicializar(Habitacion*); //Insertar valores por defecto
	void Configurar(Habitacion*, int, int, bool, bool, double, bool); //Ingresar configuración del cuarto
	void BuscarPersona(Habitacion*, string, string); //Buscar Huesped
	void MostrarOcupado(Habitacion*); //Mostrar Cuartos Ocupados
	void MostrarDisponible(Habitacion*); //Mostrar Cuartos Disponibles
	void HacerCheckIn(Habitacion*); //Check In
	void HacerCheckOut(Habitacion*); //Check Out (Diferencias de Inventario)
	void MostrarInventario(Habitacion*); //Mostrar Inventario (Inicio vs Final)
	void MostrarHuespedes(Habitacion*);
};

//***************************************************************************************************************************************************
//***************************************************************************************************************************************************

void Habitacion::Inicializar(Habitacion* vector) {

	for (int i = 0; i < 25; i++)
	{
		vector[i].Huesped.Borrar();
		vector[i].Cama = 1;
		vector[i].NumCuarto = i + 1;
		vector[i].PetFriendly = false;
		vector[i].AC = true;
		vector[i].Precio = 100;
		vector[i].Disponible = true;
		vector[i].CheckIn = "No disponible";
		vector[i].CheckOut = "No disponible";
		vector[i].Dias = 0;
	}
}

void Habitacion::Configurar(Habitacion* vector, int NumeroCuarto, int NumeroCamas, bool Mascotas, bool Aire, double NuevoPrecio, bool Disponibilidad) {

	//Configuracion de la habitacion
	vector[NumeroCuarto - 1].Cama = NumeroCamas;
	vector[NumeroCuarto - 1].PetFriendly = Mascotas;
	vector[NumeroCuarto - 1].AC = Aire;
	vector[NumeroCuarto - 1].Precio = NuevoPrecio;

	string Ingresar;
	int Elementos;
	bool salir;

	//Ingresar inventario
	do {
		salir = true;
		try
		{
			cout << "\nDesea ingresar un elemento al inventario? (Escribe Si o No...)\n";
			cin >> Ingresar;
			if (Ingresar == "Si" || Ingresar == "si" || Ingresar == "S" || Ingresar == "s")
			{
				cout << "Cuantos elementos desea ingresar?\n ";
				cin >> Elementos;

				if (Elementos <= 10 && Elementos >= 1)
				{
					vector[NumeroCuarto - 1].Elementos_lista = Elementos;

					for (int i = 0; i < Elementos; i++)
					{
						cout << "\nIngrese el nombre del articulo: ";
						cin >> vector[NumeroCuarto - 1].ListaInicial[i].Nombre;
						cout << "Ingrese la cantidad: ";
						cin >> vector[NumeroCuarto - 1].ListaInicial[i].Cantidad;
						cout << "Ingrese el precio: ";
						cin >> vector[NumeroCuarto - 1].ListaInicial[i].Precio;
					}
				}
				else {
					cout << "Rango fuera de los limites... \n";
					salir = false;
				}
			}
		}
		catch (const std::exception&)
		{
			cout << "No se ha podido configurar el inventario debido a un dato invalido...";
			salir = false;
		}
	} while (salir == false);


	cout << "\nSe ha configurado exitosamente el cuarto.\n";
};

void Habitacion::BuscarPersona(Habitacion* vector, string NombrePersona, string DPI) {

	for (int i = 0; i <= 25; i++) {
		if (i != 25) {
			if (vector[i].Huesped.Nombre == NombrePersona && vector[i].Huesped.Documento == DPI) {
				cout << "La persona se encuentra en el cuarto numero : " << i + 1;
				i += 26; //Terminar el ciclo, por haber encontrado la persona.
			}
		}
		else {
			cout << "La persona no fue encontrada";
		}
	}
}

void Habitacion::MostrarOcupado(Habitacion* vector) {
	bool verf = false;

	cout << "\nMOSTRAR CUARTOS OCUPADOS\n";
	for (int i = 0; i < 25; i++)
	{
		if (vector[i].Disponible == false)
		{
			verf = true;
			cout << vector[i].NumCuarto << ". ";
		}
	}
	if (verf == false)
	{
		cout << "No se han encontrado cuartos\n";
	}
	cout << "\n";
}

void Habitacion::MostrarDisponible(Habitacion* vector) {
	bool verf = false;

	cout << "\nMOSTRAR CUARTOS DISPONIBLES\n";
	for (int i = 0; i < 25; i++)
	{
		if (vector[i].Disponible == true)
		{
			verf = true;
			cout << vector[i].NumCuarto << ". ";
		}
	}
	if (verf == false)
	{
		cout << "No se han encontrado cuartos\n";
	}
	cout << "\n";
}

void Habitacion::HacerCheckIn(Habitacion* vector) {

	int habitacion;

	cout << "CHECK IN\n ";
	cout << "Porfavor ingrese el numero de habitacion a resevar: ";
	cin >> habitacion;
	cout << "\n";

	if (vector[habitacion - 1].Disponible == true)
	{
		try
		{
			cout << "Porfavor ingrese los siguientes datos...\n";
			cout << "\nNombre del huesped: ";
			cin >> vector[habitacion - 1].Huesped.Nombre;
			cout << "\nNumero de DPI/Pasaporte del huesped: ";
			cin >> vector[habitacion - 1].Huesped.Documento;
			cout << "\nNumero de la tarjeta del huesped: ";
			cin >> vector[habitacion - 1].Huesped.TarjetaDeCredito.Numero;
			cout << "\nFecha de expiracion de la tarjeta: ";
			cin >> vector[habitacion - 1].Huesped.TarjetaDeCredito.Expiracion;
			cout << "\nCodigo de seguridad de la tarjeta: ";
			cin >> vector[habitacion - 1].Huesped.TarjetaDeCredito.Seguridad;

			cout << "\nPorfavor ingrese la cantidad de dias que el huesped permanecera en nuestro hotel: ";
			cin >> vector[habitacion - 1].Dias;

			vector[habitacion - 1].Disponible = false;

			cout << "\nSe ha realizado exitosamente el Check IN\n";
		}
		catch (const std::exception&)
		{
			cout << "Ha ingresado un valor invalido\n";
		}
	}
	else
	{
		cout << "Habitacion no disponible.\n";
	}
}
void Habitacion::HacerCheckOut(Habitacion* vector) {
	int precio = 0;
	int precioFinal;
	int cuarto;
	int tmp;

	cout << "\nCHECK OUT\n";

	cout << "\nHuesped, de que numero de habitacion desea retirase?\n";
	cin >> cuarto;
	if (cuarto > 25 || cuarto < 1)
	{
		cout << "Habitacion fuera de los limites\n";
	}
	else {
		cout << "Inventario: \n";
		for (int i = 0; i < vector[cuarto - 1].Elementos_lista; i++)
		{
			//Buscar objetos del inventario
			try
			{
				cout << "Cuantos " << vector[cuarto - 1].ListaInicial[i].Nombre << " quedan en el cuarto? ";
				cin >> tmp;

				if (tmp <= vector[cuarto - 1].ListaInicial[i].Cantidad && tmp >= 0)
				{
					vector[cuarto - 1].ListaFinal[i].Nombre = vector[cuarto - 1].ListaInicial[i].Nombre;
					vector[cuarto - 1].ListaFinal[i].Precio = vector[cuarto - 1].ListaInicial[i].Precio;
					vector[cuarto - 1].ListaFinal[i].Cantidad = tmp;
				}
				else {
					cout << "Ha ingresado un dato invalido";
					i--;
				}

			}
			catch (const std::exception&)
			{
				cout << "Ha ingresado un dato invalido";
				i--;
			}
		}

		//Precio De los objetos
		cout << "\n FACTURA\n";
		cout << "Dias ocupados: " << "Q. " << vector[cuarto - 1].Dias * vector[cuarto - 1].Precio;
		cout << "\nObjetos faltantes: \n";

		precioFinal = vector[cuarto - 1].Dias * vector[cuarto - 1].Precio;

		for (int i = 0; i < vector[cuarto - 1].Elementos_lista; i++)
		{
			precio = ((vector[cuarto - 1].ListaInicial[i].Cantidad - vector[cuarto - 1].ListaFinal[i].Cantidad)*vector[cuarto - 1].ListaInicial[i].Precio);
			precioFinal += precio;
			cout << "  " << vector[cuarto - 1].ListaFinal[i].Nombre << ": Q." << precio << "\n";
		}

		cout << "Precio Total a Pagar: " << "Q. " << precioFinal;

		vector[cuarto - 1].Disponible = true;
		vector[cuarto - 1].Huesped.Borrar();
	}
}
void Habitacion::MostrarInventario(Habitacion* vector) {

	int cuarto;

	cout << "MOSTRAR INVENTARIO\n";
	cout << "Ingrese el numero de habitacion: ";
	cin >> cuarto;
	cout << "\n";

	try
	{
		if (cuarto > 0 && cuarto <= 25)
		{
			cout << "INVENTARIO INICIO:\n";
			for (int i = 0; i < vector[cuarto - 1].Elementos_lista; i++)
			{
				cout << vector[cuarto - 1].ListaInicial[i].Cantidad << " " << vector[cuarto - 1].ListaInicial[i].Nombre << " Q." << vector[cuarto - 1].ListaInicial[i].Precio << "\n";
			}

			cout << "\nINVENTARIO FINAL:\n";
			for (int i = 0; i < vector[cuarto - 1].Elementos_lista; i++)
			{
				cout << vector[cuarto - 1].ListaFinal[i].Cantidad << " " << vector[cuarto - 1].ListaInicial[i].Nombre << " Q." << vector[cuarto - 1].ListaInicial[i].Precio << "\n";
			}
		}
		else {
			cout << "Ha ingresado un dato invalido\n";
		}
	}
	catch (const std::exception&)
	{
		cout << "Ha ingresado un dato invalido\n";
	}
}

void Habitacion::MostrarHuespedes(Habitacion* vector) {

	cout << "\nMOSTRAR HUESPEDES\n";

	bool cont = false;

	for (int i = 0; i < 25; i++)
	{
		if (vector[i].Disponible == false)
		{
			cont = true;
			cout << "  " << vector[i].Huesped.Nombre << "\n";
		}
	}
	if (cont == false)
	{
		cout << "\nNo se han encontrado huespedes. \n";
	}
}

//****************************************************************************
//                        MAIN
//****************************************************************************

int main() {

	Habitacion Cuarto[25];
	int opcion = 0;
	string tmp, tmp2;
	int o;

	Cuarto->Inicializar(Cuarto);

	cout << "Proyecto creado por Jose Carlos Giron Marquez 1064718\n\n";
	cout << "Bienvenido al sistema de manejo de Hoteles!\n\n";

	do {

		cout << " \nMenu principal\n";
		cout << "  1.	Ingresar configuracion de cuarto\n";
		cout << "  2.	Buscar huesped\n";
		cout << "  3.	Mostrar cuartos ocupados\n";
		cout << "  4.	Mostrar cuartos libres\n";
		cout << "  5.	Hacer Check in\n";
		cout << "  6.	Hacer Check out (mostrar diferencias en inventario al hacer checkout)\n";
		cout << "  7.	Inventario por Cuarto (inicial, final)\n";
		cout << "  8.	Mostrar Huespedes del hotel\n";
		cout << "  9.	Salir\n";
		cout << "  Escriba un valor para continuar: ";

		try
		{
			cin >> opcion;

			switch (opcion)
			{
			case 1:
				//Configuracion del cuarto
				cout << "\nCONFIGURACION DEL CUARTO \n";

				int NumeroCuarto, NumeroCamas;
				bool Mascotas, Aire, CambiarDisponible;
				double NuevoPrecio;

				cout << "\nIngrese el numero del cuarto a configurar: ";
				cin >> NumeroCuarto;

				cout << "\nIngrese la nueva Cantidad de Camas: ";
				cin >> NumeroCamas;
				cout << "\nEscriba el precio por dia de la habitacion: ";
				cin >> NuevoPrecio;

				cout << "\nResponda las siguientes preguntas con S para si y N para no: ";

				cout << "\n Esta habitacion es PetFriendly? ";
				cin >> tmp;
				if (tmp == "S" || tmp == "s" || tmp == "Si" || tmp == "si" || tmp == "true")
				{
					Mascotas = true;
				}
				else {
					Mascotas = false;
				}
				cout << "\nEsta habitacion posee aire acondicionado? ";
				cin >> tmp;
				if (tmp == "S" || tmp == "s" || tmp == "Si" || tmp == "si" || tmp == "true")
				{
					Aire = true;
				}
				else {
					Aire = false;
				}
				/*cout << "Esta habitacion esta disponible?\n";
				cin >> tmp;
				if (tmp == "S" || tmp == "s" || tmp == "Si" || tmp == "si" || tmp == "true")
				{
					CambiarDisponible = true;
				}
				else {
					CambiarDisponible = false;
				}
*/
				CambiarDisponible = true;

				Cuarto->Configurar(Cuarto, NumeroCuarto, NumeroCamas, Mascotas, Aire, NuevoPrecio, CambiarDisponible);

				cout << "\n";
				break;

			case 2:
				//Buscar huesped

				cout << "\nBUSCAR HUESPED \n";
				cout << "Porfavor ingrese el nombre del huesped: \n";
				cin >> tmp;
				cout << "Porfavor ingrese el DPI/Pasaporte del huesped: \n";
				cin >> tmp2;

				Cuarto->BuscarPersona(Cuarto, tmp, tmp2);

				cout << "\n";
				break;
			case 3:
				//Mostrar cuartos ocupados

				Cuarto->MostrarOcupado(Cuarto);

				cout << "\n";
				break;
			case 4:
				//Mostrar cuartos libres

				Cuarto->MostrarDisponible(Cuarto);

				cout << "\n";
				break;
			case 5:
				//Check in

				Cuarto->HacerCheckIn(Cuarto);
				cout << "\n";
				break;
	 		case 6:
				//Check out

				Cuarto->HacerCheckOut(Cuarto);
				cout << "\n";
				break;
			case 7:
				//Inventario por cuarto

				Cuarto->MostrarInventario(Cuarto);
				cout << "\n";
				break;
			case 8:
				//Mostrar huespedes

				Cuarto->MostrarHuespedes(Cuarto);
				cout << "\n";
				break;
			case 9:
				cout << "Gracias por usar el sistema de manejo de hoteles";
				break;

			case 99:
				cout << "Habitacion configuada: ";
				cin >> o;
				o--;
				cout << "\n" << Cuarto[o].Dias;
				break;

			case 100:
				cout << "\nI HATE PROGRAMMING!!!!\n";
				break;

			default:
				cout << "Ha ingresado un valor no valido\n";
				break;
			}
		}
		catch (const std::exception&)
		{
			cout << "Ha ingresado un valor no valido\n";
			opcion = 0;
		}

	} while (opcion != 9);

	return 0;
}