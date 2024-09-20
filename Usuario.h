#pragma once
#include <iostream>
using namespace std;
#include <string>
#include "Pokemon.h"
#include <vector>

class Usuario
{
private:
	string nombre;
	string contrasenia;
	vector <Pokemon> poke{};
	int pokemonequipo;
public:
	Usuario(string,string,int);
	string get_usario();
	string get_contrasenia();
	void mostrarinfo();
	void agregarpokemon(const Pokemon& p);
	void eliminarPokemonDelEquipo(int indice);
	void guardarEnBinario(std::ofstream& archivo);
	void cargarDeBinario(std::ifstream& archivo);
};

