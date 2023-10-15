template < typename E > class Eslabon
{
	public:
		E elemento;
		int enlace;
		Eslabon *siguiente;
		Eslabon( const E &valorElemento, const int valorEnlace, Eslabon *valorSiguiente = NULL );
		Eslabon( Eslabon *valorSiguiente = NULL );
};

template < typename E >
Eslabon< E >::Eslabon( const E &valorElemento, const int valorEnlace, Eslabon *valorSiguiente )
{
	enlace = valorEnlace;
	elemento = valorElemento;
	siguiente = valorSiguiente;
}

template < typename E >
Eslabon< E >::Eslabon( Eslabon *valorSiguiente )
{
	siguiente = valorSiguiente;
}
