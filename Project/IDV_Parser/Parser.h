#pragma once

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class Parser
{
public:
	Parser();
	~Parser();

	string LineaActual;
	char character;
	int iNumVertex;
	float x, y, z;
	char separator;

	void Lectura(const char* NombreArchivo);
};

