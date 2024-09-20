#include "Pokemon.h"

Pokemon::Pokemon(){}

Pokemon::Pokemon(string nombre_, int nivel_, int puntos_vida_,
	string tipo_, int estadistica_especial_) {
	nombre = nombre_;
	nivel = nivel_;
	puntos_vida = puntos_vida_;
	tipo = tipo_;
	estadistica_especial = estadistica_especial_;
}

string Pokemon::get_nombre() {
	return nombre;
}
int Pokemon::get_nivel() {
	return nivel;
}

int Pokemon::get_puntos_vida() {
	return puntos_vida;
}

string Pokemon::get_tipo() {
	return tipo;
}

int Pokemon::get_estadistica_especia() {
	return estadistica_especial;
}

void Pokemon::mostrarinfo() {
	cout << "Nombre: " << nombre << endl
		<< "Nivel: " << nivel << endl
		<< "Puntos de vida: " << puntos_vida << endl
		<< "Tipo: " << tipo << endl
		<< "Estadisticas especiales: " << estadistica_especial << endl;
}
