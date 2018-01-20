#include "Parser.h"

Parser::Parser()
{
}


Parser::~Parser()
{
}

void Parser::Lectura(const char * NombreArchivo)
{
	ifstream Archivo(NombreArchivo);
	if (Archivo.is_open())
	{
		while (getline(Archivo, LineaActual))
		{
			if (LineaActual == "xof 0303txt 0032")
			{
				cout << LineaActual << '\n';
			}
			int findVertex = LineaActual.find("Mesh mesh");
			if (findVertex != -1)
			{
				Archivo >> iNumVertex >> character;
				cout << "Vertices: " << iNumVertex << endl;
				for (int i = 0; i < iNumVertex; i++)
				{
					Archivo >> x >> character >> y >> character >> z >> character >> character;
					cout << x << ", " << y << ", " << z << endl;
				}
			}
		}
	}
}