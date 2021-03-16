#pragma once
#ifdef LIBRARYEXPORTS
#	define LIBRARY_API __declspec(dllexport)
#else
#	define LIBRARY_API __declspec(dllimport)
#endif

class ExporterClass
{


public:

	ExporterClass();
	~ExporterClass();

	void ExportedFunction(int a);
};

void ExporterClass::ExportedFunction(int a){

	int temp = 10;
	a += temp;

}


