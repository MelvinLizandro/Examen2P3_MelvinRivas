#include <iostream>
using namespace std;
#include <string>
#include <vector>
#include "Usuario.h"

vector <Pokemon*> poke_sin{};
vector <Pokemon*> poke_asignado{};
vector <Usuario*> usa{};
Usuario* usuario;
Pokemon* poke;

int cuenta = 0;

void registro() {
    string usario = "";
    string contrasena = "";
    int pokemon_conseguidos = 0;

    cout << "Ingrese su usuario: ";
    cin >> usario;
    cout << "Ingrese la contrasenia: ";
    cin >> contrasena;

    if (usa.empty())
    {
        Usuario* usuario = new Usuario(usario, contrasena, pokemon_conseguidos);
        usa.push_back(usuario);
    }
    else {
        bool cuenta_econtrada = false;
        for (size_t i = 0; i < usa.size(); i++)
        {
            if (usario == usa[i]->get_usario() && usario == usa[i]->get_contrasenia())
            {
                cuenta_econtrada = true;
                cuenta = i;
                cout << "Ya tienes una seccion creada, iniciado con ella" << endl;
                break;
            }
        }
        if (cuenta_econtrada == false)
        {
            usuario = new Usuario(usario, contrasena, pokemon_conseguidos);
            usa.push_back(usuario);
        }
    }
}

void iniciar_seccion() {
    string usario = "";
    string contrasena = "";
    int pokemon_conseguidos = 0;

    cout << "Ingrese su usuario: ";
    cin >> usario;
    cout << "Ingrese la contrasenia: ";
    cin >> contrasena;

    for (size_t i = 0; i < usa.size(); i++)
    {
        bool cuenta_econtrada = false;
        if (usario == usa[i]->get_usario() && usario == usa[i]->get_contrasenia())
        {
            cuenta_econtrada = true;
            cuenta = i;
            cout << "Cuenta creada iniciado en ella" << endl;
            break;
        }
        if (cuenta_econtrada == false)
        {
            cout << "Cuenta no encontrada, vuelva a intentar o cree una cuenta" << endl;
        }
    }
}

void crear_pokemon(){
    string nombre;
    int nivel;
    int puntos_vida;
    string tipo;
    int estadistica_especial;
    cout << "Ingrese el nombre del pokemon: ";
    cin >> nombre;
    cout << "Ingrese el nivel del pokemon: ";
    cin >> nivel;
    cout << "Ingrese sus puntos de vida: ";
    cin >> puntos_vida;
    cout << "Ingrese el tipo del pokemon: ";
    cin >> tipo;
    cout << "Ingrese las estadisticas especiales: ";
    cin >> estadistica_especial;

    poke = new Pokemon(nombre, nivel, puntos_vida, tipo, estadistica_especial);
    poke_sin.push_back(poke);
}

void listar_inagsignados() {
    if (poke_sin.empty())
    {
        cout << "No hay nada que listar" << endl;
    }
    else
    {
        cout << "---- Pokemones sin asignacion ----" << endl;
        for (size_t i = 0; i < poke_sin.size(); i++)
        {
            cout << i << ". ";
            poke_sin[i]->mostrarinfo();
            cout << endl;
        }
        cout << endl;
    }
}

/*void listar_asignados() {
    if (poke_asignado.empty())
    {
        cout << "Aun no tienes ningun pokemon en tu equipo..." << endl;
    }
    else
    {
        cout << "---- Tu equipo ----" << endl;
        for (size_t i = 0; i < poke_asignado.size(); i++)
        {
            cout << i << ". ";
            poke_asignado[i]->mostrarinfo();
            cout << endl;
        }
        cout << endl;
    }
}
*/

void captura_pokemon() {
    if (poke_sin.empty())
    {
        cout << "No hay pokemones para atrapar, crear una para comenzar esta epica batalla" << endl;
    }
    else
    {
        int rango = poke_sin.size() - 1;
        int cap = rand() % rango + 0;
        int locaptura =  rand() % 2 + 1;
        if (locaptura == 1)
        {
            cout << "Lo sentimos no pudistes atrapar al pokemon..." << endl;
        }
        else if (locaptura == 2)
        {
            cout << "Enhorabuena has capturado al pokemon";
            usa[cuenta]->agregarpokemon(*poke_sin[cap]);
        }
    }
}

void menu_principal() {
    int opciones = 1;
    while (opciones != 0)
    {
        cout << "---- Menu principal ----" << endl
            << "1. Ver equipo" << endl
            << "2. Crear pokemon" << endl
            << "3. Capturar pokemon" << endl
            << "4. Listar pokemon" << endl
            << "5. Dejar pokemon" << endl
            << "0. Salir" << endl
            << "Cual desea seleccionar: ";
        cin >> opciones;
        cout << endl;
        switch (opciones)
        {
        case 0: {

            break;
        }
        case 1: {
            listar_asignados();
            break;
        }
        case 2: {
            crear_pokemon();
            break;
        }
        case 3: {
            captura_pokemon();
            break;
        }
        case 4: {
            listar_inagsignados();
            break;
        }
        case 5: {

            break;
        }
        case 6: {

            break;
        }
        default:
            break;
        }
    }
}

void menu()
{
    int opciones = 1;
    while (opciones != 0)
    {
        cout << "---- Menu ----" << endl
            << "1. Registro" << endl
            << "2. Iniciar seccion" << endl
            << "3. Menu principal" << endl
            << "4. Gestio pokemon" << endl
            << "0. Salir" << endl
            << "Cual desea elegir: ";
        cin >> opciones;
        cout << endl;
        switch (opciones)
        {
        case 0: {

            break;
        }
        case 1: {
            registro();
            break;
        }
        case 2: {
            iniciar_seccion();
            break;
        }
        case 3: {
            menu_principal();
            break;
        }
        case 4: {

            break;
        }
        default:
            break;
        }
    }
}

int main()
{
    menu();
}
