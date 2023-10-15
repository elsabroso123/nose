#include <iostream>
#include <string>
#include <fstream>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "listaLigada.h"

#define TAM 100
using namespace std;


template < typename E >
void mostrar( ListaLigada< E > &L );


class IndiceSecundario
{
	public:
		char nombre[ 35 ] ;
		int enlace;
};

class Ligada
{
	public:
		int id;
		int enlace;
};


ListaLigada< string > arregloIndices;
ListaLigada< int > nrrs;
ListaLigada< int > listaLigada;

class Empleado
{
	private:
		char id[ 10 ];
		char nombre[ 35 ];
		char direccion[ 40 ];
		char ciudad[ 40 ];
		char sueldo[ 10 ];

		int buscarEnIndice( const string & );
		int existeId( const int );
		int buscarEnLigado( const int );
		Empleado eliminarEnArchDatos( const int );
		void eliminarEnNrrs( const int );
		void eliminarEnIndiceLigado( const int, const int );
		void eliminarEnIndiceEmpleados( const string & );
		Empleado modificarEnArchDatos( const int, const Empleado & );
		void modificarEnNrrs( const int, const int );
		void modificarEnIndiceEmpleados(  const string &nombreAnterior, const string &nuevoNombre, const int idViejo, const int nuevoId );
		void modificarEnIndiceLigado( const string &, const int );
	public:
		Empleado( void ){}
		Empleado( const Empleado & );
		void setNombre( const string & );
		void setDireccion( const string & );
		void setCiudad( const string & );
		void setSueldo( const string & );
		void setId( const string & );
		Empleado pedirRegistro( void );
		void agregar( const Empleado & );
		void mostrarTodo( void );
		void inicializar( void );
		void buscarPorNombre( const string & );
		void guardar( void );
		bool buscarId( const int, Empleado & );
        bool eliminar( const int, Empleado & );
        void modificar( const int, const Empleado & );
        friend ostream &operator<<( ostream &, const Empleado & );
        void mostrarLista( void );
};


void Empleado::mostrarLista( void ) 
{
	mostrar( listaLigada );
	mostrar( nrrs );
	mostrar( arregloIndices );
}

Empleado Empleado::pedirRegistro( void )
{
	string cadena;
	Empleado empleadoARetornar;

	cout << "Ingresa el ID: ";
	fflush( stdin );
	getline( cin, cadena );
	while( existeId( atoi( cadena.c_str() ) ) != -1 )
	{
		cout << "Ese ID ya existe Ingresa otro: ";
		fflush( stdin );
		getline( cin, cadena );
	}
	empleadoARetornar.setId( cadena );

	cout << "Ingrese el nombre del empleado: ";
    fflush( stdin );
    getline( cin, cadena );
    empleadoARetornar.setNombre( cadena );

    cout << "Ingrese la direccion: ";
    fflush( stdin );
    getline( cin, cadena );
    empleadoARetornar.setDireccion( cadena );

    cout << "Ingrese la ciudad: ";
    fflush( stdin );
    getline( cin, cadena );
    empleadoARetornar.setCiudad( cadena );

    cout << "Ingrese el sueldo del empleado: ";
    fflush( stdin );
    getline( cin, cadena );
    empleadoARetornar.setSueldo( cadena );

    return empleadoARetornar;
}

Empleado::Empleado( const Empleado &origen )
{
	strcpy( id, origen.id );
	strcpy( nombre, origen.nombre );
	strcpy( direccion, origen.direccion );
	strcpy( ciudad, origen.ciudad );
	strcpy( sueldo, origen.sueldo );
}

void Empleado::setId( const string &valorId )
{
	int longitud = valorId.size();
	longitud = ( longitud < 10 ? longitud : 9 );
	valorId.copy( id, longitud );
	id[ longitud ] = '\0';
}

void Empleado::setSueldo( const string &valorSueldo )
{
	int longitud = valorSueldo.size();
	longitud = ( longitud < 10 ? longitud : 9 );
	valorSueldo.copy( sueldo, longitud );
	sueldo[ longitud ] = '\0';
}

void Empleado::setNombre( const string &valorNombre )
{
	int longitud = valorNombre.size();
	longitud = ( longitud < 35 ? longitud : 34 );
	valorNombre.copy( nombre, longitud );
	nombre[ longitud ] = '\0';
}

void Empleado::setDireccion( const string &valorDireccion )
{
	int longitud = valorDireccion.size();
	longitud = ( longitud < 40 ? longitud : 39 );
	valorDireccion.copy( direccion, longitud );
	direccion[ longitud ] = '\0';
}

void Empleado::setCiudad( const string &valorCiudad )
{
	int longitud = valorCiudad.size();
	longitud = ( longitud < 40 ? longitud : 39 );
	valorCiudad.copy( ciudad, longitud );
	ciudad[ longitud ] = '\0';
}

ostream &operator<<( ostream &salida, const Empleado &empleado )
{
    salida << "ID:        "  << empleado.id << endl
           << "Nombre:    "  << empleado.nombre << endl
           << "Direccion: "  << empleado.direccion << endl
           << "Ciudad:    "  << empleado.ciudad << endl
           << "Sueldo:    "  << empleado.sueldo << endl;

    return salida;
}

void Empleado::mostrarTodo( void )
{
	Empleado empleado;
	ifstream archivo( "empleados.txt", ios::in );
	if( !archivo )
		cout << "No existe el archivo" << endl;
	else
	{
		cout << endl;
		while( !archivo.eof() )
		{
			archivo.read( ( char * ) &empleado, sizeof( Empleado ) );
			if( !archivo.eof() )
				cout << empleado << endl << endl;
		}
	}
	archivo.close();
}

int Empleado::existeId( const int idABuscar )
{
	nrrs.irAlInicio();
	for( int i = 0; i < nrrs.obtenerTamanio(); i++ )
		if( nrrs.obtenerElemento() == idABuscar )
			return nrrs.obtenerEnlace();
		else
			nrrs.siguiente();
	return -1;
}

int Empleado::buscarEnIndice( const string &nombreABuscar )
{
	arregloIndices.irAlInicio();
	for( int i = 0; i < arregloIndices.obtenerTamanio(); i++ )
		if( arregloIndices.obtenerElemento() == nombreABuscar )
			return arregloIndices.posicionActual();
		else
			arregloIndices.siguiente();
	return -1;
}

int Empleado::buscarEnLigado( const int idABuscar )
{
	listaLigada.irAlInicio();
	for( int i = 0; i < listaLigada.obtenerTamanio(); i++ )
		if( listaLigada.obtenerElemento() == idABuscar )
			return listaLigada.posicionActual();
		else
			listaLigada.siguiente();
	return -1;
}

Empleado Empleado::eliminarEnArchDatos( const int idAEliminar )
{
	ifstream datos( "empleados.txt", ios::in );
	ofstream temporal( "temporal.txt", ios::out );
	Empleado registro;
	Empleado registroARetornar;

	while( !datos.eof() )
	{
		datos.read( ( char * ) &registro, sizeof( Empleado ) );
		if( atoi( registro.id ) != idAEliminar )
			temporal.write( ( char * ) &registro, sizeof( Empleado ) );
		else
			registroARetornar = registro;
	}
	datos.close();
	temporal.close();
	remove( "empleados.txt" );
	rename( "temporal.txt", "empleados.txt" );

	return registroARetornar;
}

void Empleado::eliminarEnNrrs( const int idAEliminar )
{
	int posicion = existeId( idAEliminar );
	nrrs.irAPosicion( posicion );
	//cout << "posicion = " << posicion << endl;
	nrrs.eliminar();
	for( int i = posicion; i < nrrs.obtenerTamanio(); i++ )
	{
		nrrs.modificar( nrrs.obtenerElemento(), nrrs.obtenerEnlace() - 1 );
		nrrs.siguiente();
	}
	//mostrar( nrrs );
}

void Empleado::eliminarEnIndiceEmpleados( const string &nombreAEliminar )
{
	int posicion = buscarEnIndice( nombreAEliminar );
	arregloIndices.irAPosicion( posicion );
	listaLigada.irAPosicion( arregloIndices.obtenerEnlace() );
	if( listaLigada.obtenerEnlace() == -1 )
		arregloIndices.eliminar();
}

void Empleado::eliminarEnIndiceLigado( const int idAEliminar, const int posDeRegistro )
{
	int posicion = buscarEnLigado( idAEliminar );
	listaLigada.irAPosicion( posicion );
	int aux = listaLigada.posicionActual();
	int posNueva = listaLigada.obtenerEnlace();
	arregloIndices.irAPosicion( posDeRegistro );
	if( listaLigada.obtenerEnlace() == -1 )
		listaLigada.modificar( -1, -1 );
	else
	{
		if( arregloIndices.obtenerEnlace() == listaLigada.posicionActual() )
		{
			arregloIndices.modificar( arregloIndices.obtenerElemento(), listaLigada.obtenerEnlace() );
			listaLigada.modificar( -1, -1 );
		}
		else
		{
			listaLigada.irAPosicion( arregloIndices.obtenerEnlace() );
			while( listaLigada.obtenerEnlace() != aux )
				listaLigada.irAPosicion( listaLigada.obtenerEnlace() );
			listaLigada.modificar( listaLigada.obtenerElemento(), posNueva );
			listaLigada.irAPosicion( posicion );
			listaLigada.modificar( -1, -1 );
		}
	}
}

bool Empleado::eliminar( const int idAEliminar, Empleado &valor )
{
	string cadenaNombre;
	if( existeId( idAEliminar ) != -1 )
	{
		valor = eliminarEnArchDatos( idAEliminar );
		eliminarEnNrrs( idAEliminar );
		cadenaNombre = valor.nombre;
		eliminarEnIndiceEmpleados( cadenaNombre ); // debe ir antes que eliminarEnIndiceLigado
		eliminarEnIndiceLigado( idAEliminar, arregloIndices.posicionActual() );
		return true;
	}
	else
		cout << "EL id no existe" << endl;
	return false;
}

bool Empleado::buscarId( const int idABuscar, Empleado &resultado )
{
	long int posByte;
	ifstream datos( "empleados.txt", ios::in );

	if( !datos )
		cout << "No existe el archivo" << endl;
	else
	{
		nrrs.irAlInicio();
		for( int i = 0; i < nrrs.obtenerTamanio(); i++ )
		{
			if( nrrs.obtenerElemento() == idABuscar )
			{
				posByte = nrrs.obtenerEnlace() * sizeof( Empleado );
				datos.seekg( posByte, ios::beg );
				datos.read( ( char * ) &resultado, sizeof( Empleado ) );
				datos.close();
				return true;
			}
			nrrs.siguiente();
		}
	}
	datos.close();
	return false;
}

void Empleado::buscarPorNombre( const string & nombreABuscar )
{
	ifstream datos( "empleados.txt", ios::in );
	int indiceRegistro;
	long int posByte;
	Empleado temporal;
	bool yaTermino = false;

	if( !datos )
		cout << "No existe el archivo" << endl;
	else
	{
		int posEncontrado = buscarEnIndice( nombreABuscar );
		if( !( posEncontrado == -1 ) )
		{
			cout << endl;
			arregloIndices.irAPosicion( posEncontrado );
			listaLigada.irAPosicion( arregloIndices.obtenerEnlace() );
			do
			{
				indiceRegistro = existeId( listaLigada.obtenerElemento() );
				posByte = indiceRegistro * sizeof( Empleado );
				datos.seekg( posByte, ios::beg );
				datos.read( ( char * ) &temporal, sizeof( temporal ) );
				cout << temporal << endl << endl;
				if( listaLigada.obtenerEnlace() == -1  )
					yaTermino = true;
				else
					listaLigada.irAPosicion( listaLigada.obtenerEnlace() );
			}while( yaTermino == false );
		}
		else
			cout << "No se encontraron resultados" << endl;
	}
	datos.close();
}

void Empleado::agregar( const Empleado &nuevoValor )
{
	string cadenaNombre;

    ofstream archivo( "empleados.txt", ios::app );
    if( existeId( atoi( nuevoValor.id ) ) == -1 )
    {
	    archivo.write( ( char * ) &nuevoValor, sizeof( Empleado ) );
	    nrrs.ponAlFinal( atoi( nuevoValor.id ), nrrs.obtenerTamanio() );

	    cadenaNombre = nuevoValor.nombre;
	    int posEncontrado = buscarEnIndice( cadenaNombre );
	    if( posEncontrado != -1 ) // si ya existe el nombre
	    {
	    	arregloIndices.irAPosicion( posEncontrado );
	    	listaLigada.ponAlFinal( atoi( nuevoValor.id ), arregloIndices.obtenerEnlace() );
	    	arregloIndices.modificar( arregloIndices.obtenerElemento(), listaLigada.obtenerTamanio() - 1 );
	    }
	    else // si no existe el nombre
	    {
	    	listaLigada.ponAlFinal( atoi( nuevoValor.id ), -1 );
	    	arregloIndices.ponAlFinal( cadenaNombre, listaLigada.obtenerTamanio() - 1 );
	    }
	    mostrar( listaLigada );
	    mostrar( nrrs );
	    mostrar( arregloIndices );
	}
	else
		cout << "No se agrego, el ID ya existe" << endl;
    archivo.close();
}

void Empleado::modificar( const int idAModificar, const Empleado &reemplazo ) 
{
	string cadenaNombre, cad;
	Empleado empleadoModificado;
	if( existeId( idAModificar ) != -1 && existeId( atoi( reemplazo.id ) ) == -1 ) // si existe el id
	{
		empleadoModificado = modificarEnArchDatos( idAModificar, reemplazo );
		modificarEnNrrs( idAModificar, atoi( reemplazo.id ) );
		cadenaNombre = reemplazo.nombre;
		cad = empleadoModificado.nombre;
		modificarEnIndiceEmpleados( cad, cadenaNombre, atoi( empleadoModificado.id ), atoi( reemplazo.id ) );
		cadenaNombre = empleadoModificado.nombre;
		if( !( strcmp( empleadoModificado.nombre, reemplazo.nombre ) == 0 ) )
			modificarEnIndiceLigado( cadenaNombre, atoi( empleadoModificado.id ) );
	}
	else
		cout << "El registro no existe o el id ya existe" << endl;

	mostrar( listaLigada );
	mostrar( nrrs );
	mostrar( arregloIndices );
}

void Empleado::modificarEnIndiceLigado( const string &nombreAModificar, const int idViejo )
{
	int posicion = buscarEnIndice( nombreAModificar );
	int a, b, c;
	bool bandera = false;
	arregloIndices.irAPosicion( posicion );
	listaLigada.irAPosicion( arregloIndices.obtenerEnlace() );
	a = c = listaLigada.posicionActual();
	if( listaLigada.obtenerElemento() == idViejo && listaLigada.obtenerEnlace() == -1 )
	{
		arregloIndices.eliminar();
		listaLigada.modificar( -1, -1 );
	}
	else
	{
		while( listaLigada.obtenerElemento() != idViejo )
		{
			a = listaLigada.posicionActual();
			listaLigada.irAPosicion( listaLigada.obtenerEnlace() );
			c = listaLigada.posicionActual();
			bandera = true;
		}
		b = listaLigada.obtenerEnlace();
		if( bandera == true )
			arregloIndices.modificar( arregloIndices.obtenerElemento(), a );
		else
			arregloIndices.modificar( arregloIndices.obtenerElemento(), b );
		
		listaLigada.irAPosicion( a );
		listaLigada.modificar( listaLigada.obtenerElemento(), b );
		listaLigada.irAPosicion( c );
		listaLigada.modificar( -1, -1 );
	}
}

void Empleado::modificarEnIndiceEmpleados( const string &nombreAnterior, const string &nuevoNombre, const int idViejo, const int nuevoId )
{
	int posicion = buscarEnIndice( nuevoNombre );
	if( posicion == -1 ) // si nuevoNombre NO existe en el archivo
	{
		listaLigada.ponAlFinal( nuevoId, -1 );
	    arregloIndices.ponAlFinal( nuevoNombre, listaLigada.obtenerTamanio() - 1 );
	}
	else // si nuevoNombre YA existe
	{
		if( nombreAnterior == nuevoNombre )
		{
			arregloIndices.irAPosicion( posicion );
			listaLigada.irAPosicion( arregloIndices.obtenerEnlace() );
			while( listaLigada.obtenerElemento() != idViejo )
				listaLigada.irAPosicion( listaLigada.obtenerEnlace() );
			listaLigada.modificar( nuevoId, listaLigada.obtenerEnlace() );
		}
		else
		{
			arregloIndices.irAPosicion( posicion );
	    	listaLigada.ponAlFinal( nuevoId, arregloIndices.obtenerEnlace() );
	    	arregloIndices.modificar( arregloIndices.obtenerElemento(), listaLigada.obtenerTamanio() - 1 );
	    }
	}
}

void Empleado::modificarEnNrrs( const int idAModificar, const int nuevoID )
{
	int posicion = existeId( idAModificar );
	nrrs.irAPosicion( posicion );
	nrrs.modificar( nuevoID, nrrs.obtenerEnlace() );
}

Empleado Empleado::modificarEnArchDatos( const int idAModificar, const Empleado &registroReemplazo )
{
	Empleado registroARetornar;
	fstream datos( "empleados.txt", ios::in | ios::out );
	if( datos )
	{
		int posDeRegistro = existeId( idAModificar );
		int posByte = posDeRegistro * sizeof( Empleado );
		datos.seekg( posByte, ios::beg );
		datos.read( ( char * ) &registroARetornar, sizeof( Empleado ) );
		datos.seekg( (long)datos.tellg() - sizeof( Empleado ), ios::beg );
		datos.write( ( char * ) &registroReemplazo, sizeof( Empleado ) );
	}
	else
		cout << "No existe el archivo" << endl;
	datos.close();
	return registroARetornar;
}

void Empleado::inicializar( void )
{
	IndiceSecundario indiSecundario;
	Ligada liga;
	string cadenaNombre;
	ifstream indice( "indiceEmpleados.txt", ios::in );
	ifstream indiceLigado( "ligadoEmpleados.txt", ios::in );
	ifstream indiceNrr( "indiceNrr.txt", ios::in );

	if( !indice || !indiceLigado || !indiceNrr ) // si los archivos no existen los crea
	{
		ofstream indice( "indiceEmpleados.txt", ios::out );
		ofstream indiceLigado( "ligadoEmpleados.txt", ios::out );
		ofstream indiceNrr( "indiceNrr.txt", ios::out );
	}
	else
	{
		// archivo de índices para el nombre
		arregloIndices.irAlInicio();
		while( !indice.eof() )
		{
			indice.read( ( char * ) &indiSecundario, sizeof( IndiceSecundario ) );
			if( !indice.eof() )
			{
				cadenaNombre = indiSecundario.nombre;
				arregloIndices.ponAlFinal( cadenaNombre, indiSecundario.enlace );
			}
			cadenaNombre.clear();
		}

		// archivo de indice ligado para nombre
		listaLigada.irAlInicio();
		while( !indiceLigado.eof() )
		{
			indiceLigado.read( ( char * ) &liga, sizeof( Ligada ) );
			if( !indiceLigado.eof() )
				listaLigada.ponAlFinal( liga.id, liga.enlace );
		}
		// archivo de inidice de nrr's para los datos de empleados
		nrrs.irAlInicio();
		while( !indiceNrr.eof() )
		{
			indiceNrr.read( ( char * ) &liga, sizeof( Ligada ) );
			if( !indiceNrr.eof() )
				nrrs.ponAlFinal( liga.id, liga.enlace );
		}
	}

	indice.close();
	indiceLigado.close();
	indiceNrr.close();
}

void Empleado::guardar( void )
{
	ofstream indice( "indiceEmpleados.txt", ios::out );
	ofstream indiceLigado( "ligadoEmpleados.txt", ios::out );
	ofstream indiceNrr( "indiceNrr.txt", ios::out );

	IndiceSecundario contenedor;
	arregloIndices.irAlInicio();
	for( int i = 0; i < arregloIndices.obtenerTamanio(); i++ )
	{
		for( int j = 0; j < sizeof( contenedor.nombre ); contenedor.nombre[ j++ ] = '\0' );
		strcpy( contenedor.nombre, arregloIndices.obtenerElemento().c_str() );
		contenedor.enlace = arregloIndices.obtenerEnlace();
		indice.write( ( char * ) &contenedor, sizeof( IndiceSecundario ) );
		arregloIndices.siguiente();
	}

	Ligada liga;
	listaLigada.irAlInicio();
	for( int i = 0; i < listaLigada.obtenerTamanio(); i++ )
	{
		liga.id = listaLigada.obtenerElemento();
		liga.enlace = listaLigada.obtenerEnlace();
		indiceLigado.write( ( char * ) &liga, sizeof( Ligada ) );
		listaLigada.siguiente();
	}

	nrrs.irAlInicio();
	for( int i = 0; i < nrrs.obtenerTamanio(); i++ )
	{
		liga.id = nrrs.obtenerElemento();
		liga.enlace = nrrs.obtenerEnlace();
		indiceNrr.write( ( char * ) &liga, sizeof( Ligada ) );
		nrrs.siguiente();
	}

	indice.close();
	indiceLigado.close();
	indiceNrr.close();
}

int main( void )
{
	Empleado empleado, nuevo, empleadoBuscar, empleadoEliminado;
	string respuesta;
	char opcion;
	empleado.inicializar();
	do
    {
	    system("cls");
	    cout << "Seleccione una opcion" << endl;
	    cout << "1) Agregar empleado." << endl;
	    cout << "2) Mostrar todos los empleados." << endl;
	    cout << "3) Buscar empleado por ID." << endl;
	    cout << "4) Buscar empleado por Nombre" << endl;
        cout << "5) Modificar empleado." << endl; 
        cout << "6) Eliminar empleado." << endl;
        cout << "7) Salir." << endl;
        cout << "8) mostrar listaLigada" << endl;
	    cin >> opcion;
	    switch( opcion )
	    {
	    	case '1': // agregar
	    		nuevo = empleado.pedirRegistro();
	    		empleado.agregar( nuevo );
	    		break;

	    	case '2': // mostrar
	    		empleado.mostrarTodo();
	    		break;

            case '3': // buscar
                cout << "Ingrese el ID a buscar: ";
                fflush( stdin );
                cin >> respuesta;
                if( empleado.buscarId( atoi( respuesta.c_str() ), empleadoBuscar ) )
                    cout << empleadoBuscar << endl << endl;
                else
                    cout << "El registro no existe" << endl;
                break;
            case '4':
            	cout << "Ingresa el nombre a buscar: ";
            	fflush( stdin );
            	getline( cin, respuesta );
            	empleado.buscarPorNombre( respuesta );
            	break;

            case '5': // modificar
                cout << "Ingrese el ID del empleado a modificar: ";
                fflush( stdin );
                cin >> respuesta;
                if( empleado.buscarId( atoi( respuesta.c_str() ), empleadoBuscar ) )
                {
                	nuevo = empleado.pedirRegistro();
                	empleado.modificar( atoi( respuesta.c_str() ), nuevo );
                }
                else
                    cout << "No existe el empleado" << endl;
                break;

            case '6': // eliminar
                cout << "Ingrese el ID del empleado a eliminar: ";
                fflush( stdin );
                cin >> respuesta;
                if( empleado.buscarId( atoi( respuesta.c_str() ), empleadoBuscar ) )
                {
	                if( empleado.eliminar( atoi( respuesta.c_str() ), empleadoEliminado ) )
	                {
	                	cout << empleadoEliminado << endl;
	                	cout << "EMPLEADO ELIMINADO CON EXITO" << endl;
	                }
	                else
	                    cout << "NO se elimino al empleado" << endl;
	            }
	            else
	            	cout << "No existe el empleado" << endl;
                break;
            case '8':
            	empleado.mostrarLista();
            	break;
	    }
        system( "pause" );

    }while( opcion != '7' );
	empleado.guardar();


	return 0;
}



template < typename E >
void mostrar( ListaLigada< E > &L )
{
	int posOriginal = L.posicionActual();
	L.irAlInicio();

	cout << "[";
	for( int i = 0; i < L.obtenerTamanio(); i++ )
	{
		cout << L.obtenerElemento() << "-> " << L.obtenerEnlace();
		if( !( i == ( L.obtenerTamanio() - 1 ) ) )
		{
			cout << ", ";
			L.siguiente();
		}
	}
	cout << "]" << endl;

	//L.irAPosicion( posOriginal );
}
