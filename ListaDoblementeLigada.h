#include "lista.h"
#include "Assert.cpp"
#include "Eslabon.h"

template < typename E > class ListaDoblementeLigada
{
	private:
		Eslabon< E > *cabeza;
		Eslabon< E > *cola;
		Eslabon< E > *actual;
		int tamanio;
		void inicializar( void );
		void eliminarTodo( void );
	public:
		ListaDoblementeLigada( void );
		~ListaDoblementeLigada( void );
		void vaciar( void );
		void insertar( const E &item, const int enlace );
		void ponAlFinal( const E &item, const int enlace );
		E eliminar( void );
		void irAlInicio(void );
		void irAlFinal( void );
		void anterior( void );
		void siguiente( void );
		int obtenerTamanio( void ) const;
		int posicionActual( void ) const;
		void irAPosicion( int posicion );
		const E &obtenerElemento( void ) const;
		const int obtenerEnlace( void ) const;
};

template < typename E >
void ListaDoblementeLigada< E >::inicializar( void )
{
	actual = cabeza = new Eslabon< E >;
	cabeza -> siguiente = cola = new Eslabon< E >( cabeza );
	tamanio = 0;
}

template < typename E >
void ListaDoblementeLigada< E >::eliminarTodo( void )
{
	while( cabeza != NULL )
	{
		actual = cabeza;
		cabeza = cabeza -> siguiente;
		delete actual;
	}
}

template < typename E >
ListaDoblementeLigada< E >::ListaDoblementeLigada( void )
{
	inicializar();
}

template < typename E >
ListaDoblementeLigada< E >::~ListaDoblementeLigada( void )
{
	eliminarTodo();
}

template < typename E >
void ListaDoblementeLigada< E >::vaciar( void )
{
	eliminarTodo();
	inicializar();
}

template < typename E >
void ListaDoblementeLigada< E >::insertar( const E &item, const int enlace )
{
	actual = actual -> siguiente = actual -> siguiente -> anterior = new Eslabon< E >( item, enlace, actual, actual -> siguiente );
	tamanio++;
}

template < typename E >
void ListaDoblementeLigada< E >::ponAlFinal( const E &item, const int enlace )
{
	actual = cola -> anterior = cola -> anterior -> siguiente = new Eslabon< E >( item, enlace, cola -> anterior, cola );
	tamanio++;
}

template < typename E >
E ListaDoblementeLigada< E >::eliminar( void )
{
	Assert( tamanio != 0, "Lista vacia" );

	E item = actual -> elemento;
	Eslabon< E > *temporal = actual;
	actual -> siguiente -> anterior = actual -> anterior;
	actual -> anterior -> siguiente = actual -> siguiente;
	actual = actual -> anterior;
	delete temporal;
	tamanio--;
	return item;
}

template < typename E >
void ListaDoblementeLigada< E >::irAlInicio( void )
{
	if( tamanio != 0 )
		actual = cabeza -> siguiente;
}

template < typename E >
void ListaDoblementeLigada< E >::irAlFinal( void )
{
	if( tamanio != 0 )
		actual = cola -> anterior;
}

template < typename E >
void ListaDoblementeLigada< E >::anterior( void )
{
	if( actual != cabeza )
		actual = actual -> anterior;

}

template < typename E >
void ListaDoblementeLigada< E >::siguiente( void )
{
	if( tamanio != 0 )
		actual = actual -> siguiente;
}

template < typename E >
int ListaDoblementeLigada< E >::obtenerTamanio( void ) const
{
	return tamanio;
}

template < typename E >
int ListaDoblementeLigada< E >::posicionActual( void ) const
{
	Eslabon< E > *temporal;
	temporal = cabeza;
	int i;

	for( i = 0; temporal != actual; i++ )
		temporal = temporal -> siguiente;

	return i;
}

template < typename E >
void ListaDoblementeLigada< E >::irAPosicion( int posicion )
{
	Assert( ( posicion >= 0 ) && ( posicion < tamanio ), "Posicion fuera de rango" );

	actual = cabeza;

	for( int i = 0; i < posicion; i++ )
		actual = actual -> siguiente;
}

template < typename E >
const E &ListaDoblementeLigada< E >::obtenerElemento( void ) const
{
	Assert( tamanio != 0, "Lista vacia" );
	return actual -> elemento;
}

template < typename E >
const int ListaDoblementeLigada< E >::obtenerEnlace( void ) const
{
	Assert( tamanio != 0, "Lista vacia" );
	return actual -> enlace;
}
