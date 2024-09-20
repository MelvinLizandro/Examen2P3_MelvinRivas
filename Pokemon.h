#pragma once
#include <iostream>
using namespace std;
#include <string>

class Pokemon
{
private:
	string nombre;
	int nivel;
	int puntos_vida;
	string tipo;
	int estadistica_especial;
public:
	Pokemon();
	Pokemon(string,int,int,string,int);
	string get_nombre();
	int get_nivel();
	int get_puntos_vida();
	string get_tipo();
	int get_estadistica_especia();
	void mostrarinfo();
	void guardarEnBinario(std::ofstream& archivo);
	void cargarDeBinario(std::ifstream& archivo);
};

