#include <iostream>
#include <cstdlib>

void Assert( bool val, std::string s )
{
	if( !( val ) )
	{
		std::cout << "Falla: " << s << std::endl;
		exit( -1 );
	}
}

