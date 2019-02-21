/*	
	Módulo para encontrar basura
		-> Solo funciona en modo Debug, y debe incluirse en todos los módulos en los que 
		se desee encontrar basura sin eliminar.
		-> Para activarlo, escribir la siguente línea al inicio de la función main: 
		_CrtSetDbgFlag ( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
*/
#ifdef _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#ifndef DBG_NEW
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#define new DBG_NEW
#endif
#endif
