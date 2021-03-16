#pragma once

class DeclareClass
{

private: 

	//Datos mienbros de la clase
	int a, b;

public:

	//Funciones miembros de la classe
	void Lee(int &a2, int &b2);

	void Guarda(int a2, int b2) {

		a = a2;
		b = b2;
	}
		

	DeclareClass();
	~DeclareClass();

};



void DeclareClass::Lee(int &a2, int &b2) {

	a2 = a;
	b2 = b;

}


