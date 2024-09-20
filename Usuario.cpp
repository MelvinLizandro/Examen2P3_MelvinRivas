#include "Usuario.h"

Usuario::Usuario(string nombre_, string contrasenia_, int pokemonequipo_) {
	nombre = nombre_;
	contrasenia = contrasenia_;
	pokemonequipo = pokemonequipo_;
}

string Usuario::get_usario() {
	return nombre;
}

string Usuario::get_contrasenia() {
	return contrasenia;
}

void Usuario::mostrarinfo() {
	cout << "Nombre de usario: " << nombre << endl
		<< "Contrasenia: " << contrasenia << endl;
    if (poke.empty())
    {
        cout << "Aun no tienes ningun pokemon en tu equipo..." << endl;
    }
    else
    {
        cout << "---- Tu equipo ----" << endl;
        for (size_t i = 0; i < poke.size(); i++)
        {
            cout << i << ". ";
            poke[i].mostrarinfo();
            cout << endl;
        }
        cout << endl;
    }
}

void Usuario::agregarpokemon(const Pokemon& p) {
	poke.push_back(p);
}

void Usuario::eliminarPokemonDelEquipo(int indice) {
    poke.erase(poke.begin() + indice);
}