#include <iostream>
using namespace std;
#include <string>
#include <vector>
#include "Usuario.h"
#include "Pokemon.h"
#include <fstream>

vector <Pokemon*> poke_sin{};
vector <Pokemon*> poke_asignado{};
vector <Usuario*> usa{};
Usuario* usuario;
Pokemon* poke;


int cuenta = 0;

void menu_principal();

void registro() {
   //creando el usario
    string usario = "";
    string contrasena = "";
    int pokemon_conseguidos = 0;

    cout << "Ingrese su usuario: ";
    cin >> usario;
    cout << "Ingrese la contrasenia: ";
    cin >> contrasena;

    if (usa.empty())
    {
        //lo añade al archivo .bin
        ofstream archivo_usuarios("Usuarios.bin", ios::binary);
        Usuario* usuario = new Usuario(usario, contrasena, pokemon_conseguidos);
        usa.push_back(usuario);
        menu_principal();
        //indice
        int indice = usa.size() - 1;
        //agregar usario
        archivo_usuarios.write(usa[indice]->get_usario().c_str(), 100);
        //agregar contrasenia
        archivo_usuarios.write(usa[indice]->get_contrasenia().c_str(), 100);
        archivo_usuarios.close();
        menu_principal();
    }
    else
    {
        //revisa que no el usario no exista
        bool cuenta_econtrada = false;
        for (size_t i = 0; i < usa.size(); i++)
        {
            //si existe lo habre 
            if (usario == usa[i]->get_usario() && usario == usa[i]->get_contrasenia())
            {
                cuenta_econtrada = true;
                cuenta = i;
                cout << "Ya tienes una seccion creada, iniciado con ella" << endl;
                menu_principal();
                break;
            }
        }
        //si no lo crea si no es el primero
        if (cuenta_econtrada == false)
        {
            ofstream archivo_usuarios("Usuarios.bin", ios::binary);
            usuario = new Usuario(usario, contrasena, pokemon_conseguidos);
            usa.push_back(usuario);
            //indice
            int indice = usa.size() - 1;
            //agregar usario
            archivo_usuarios.write(usa[indice]->get_usario().c_str(), 100);
            //agregar contrasenia
            archivo_usuarios.write(usa[indice]->get_contrasenia().c_str(), 100);
            archivo_usuarios.close();
            menu_principal();
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
    
    bool cuenta_econtrada = false;
    for (size_t i = 0; i < usa.size(); i++)
    {
        if ((usario == usa[i]->get_usario()) && (contrasena == usa[i]->get_contrasenia()))
        {
            cuenta_econtrada = true;
            cuenta = i;
            cout << "Cuenta encontrada iniciado en ella" << endl;
            menu_principal();
            break;
        } 
    }
    if (cuenta_econtrada == false)
    {
        cout << "Cuenta no encontrada, vuelva a intentar o cree una cuenta" << endl;
    }
}

void crear_pokemon(){
    ofstream archivo_pokemon("Pokemon.bin", ios::binary);
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
    //indice
    int indice = poke_sin.size() - 1;
    //agregar nombre
    archivo_pokemon.write(poke_sin[indice]->get_nombre().c_str(), 100);
    //agregar nivel
    int nivel_copia = poke_sin[indice]->get_nivel();
    archivo_pokemon.write(reinterpret_cast<const char*>(&nivel_copia), sizeof(int));
    //agregar puntos de vida
    int puntos_vida_copia = poke_sin[indice]->get_puntos_vida();
    archivo_pokemon.write(reinterpret_cast<const char*>(&puntos_vida_copia), sizeof(int));
    //agregar tipos
    archivo_pokemon.write(poke_sin[indice]->get_tipo().c_str(), 100);
    // agregar estadisticas especiales
    int estadisticas_especiales_copia = poke_sin[indice]->get_estadistica_especia();
    archivo_pokemon.write(reinterpret_cast<const char*>(&estadisticas_especiales_copia), sizeof(int));
    archivo_pokemon.close();
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

void captura_pokemon() {
    if (poke_sin.empty())
    {
        cout << "No hay pokemones para atrapar, crear una para comenzar esta epica batalla" << endl;
    }
    else
    {
        int rango = poke_sin.size();
        int cap = rand() % rango + 0;
        int locaptura =  rand() % 2 + 1;
        if (locaptura == 1)
        {
            cout << "Lo sentimos no pudistes atrapar al pokemon..." << endl;
        }
        else if (locaptura == 2)
        {
            cout << "Enhorabuena has capturado al pokemon" << endl;
            usa[cuenta]->agregarpokemon(*poke_sin[cap]);
            poke_asignado.push_back(poke_sin[cap]);
        }
    }
}

void Dejar_pokemon() {
    
    if (poke_asignado.empty())
    {
        cout << "No puedes liberar ningun pokemon ya que no tienes ninguno en tu posecion" << endl;
    }
    else
    {
        int liberar_a = 0;
        cout << "----- Tus pokemones ----" << endl;
        for (size_t i = 0; i < poke_asignado.size(); i++)
        {
            cout << i << ". ";
            poke_asignado[i]->mostrarinfo();
            cout << endl;
        }
        cout << endl;
        cout << "Coloque el indice del pokemon a liberar: ";
        cin >> liberar_a;
        if (liberar_a >= 0 && liberar_a < poke_asignado.size())
        {
            usa[cuenta]->eliminarPokemonDelEquipo(liberar_a);
            poke_asignado.erase(poke_asignado.begin() + liberar_a);
            cout << "Su pokemon ah sido liberado exitosamente..." << endl;
        }
        else
        {
            cout << "El indice brindado excede su limite de pokemones..." << endl;
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
            cout << "Regresando..." << endl;
            break;
        }
        case 1: {
            usa[cuenta]->mostrarinfo();
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
            Dejar_pokemon();
            break;
        }
        default:
            cout << "Caracter invalido, porfavor vuelve a intentarlo..." << endl;
            break;
        }
    }
}

void cargar_info() {
    ifstream cantidad("cantidad.bin", ios::binary);
    int cantidad_usarios = 0;
    int cantidad_pokemon = 0;
    cantidad.read(reinterpret_cast<char*>(&cantidad_usarios), sizeof(cantidad_usarios));
    cantidad.read(reinterpret_cast<char*>(&cantidad_pokemon), sizeof(cantidad_pokemon));
    ifstream archivo_usuarios_leer("Usuarios.bin", ios::binary);
    usa.clear();
    for (size_t i = 0; i < cantidad_usarios; i++)
    {
        char user[100]{};
        char contrasenia[100]{};
        int contiene = 0;
        archivo_usuarios_leer.read(user, sizeof(user));
        archivo_usuarios_leer.read(contrasenia, sizeof(contrasenia));
        string user_copia = "";
        string contrasenia_copia = "";
        Usuario* usua = new Usuario(user, contrasenia, contiene);
        usa.push_back(usua);
    }
    ifstream archivo_pokemon_leer("Pokemon.bin", ios::binary);
    for (size_t i = 0; i < cantidad_pokemon; i++)
    {
        char nombre[100]{};
        int nivel = 0;
        int puntos_vida = 0;
        char tipo[100]{};
        int estadistica_especial = 0;
        // leer nombre
        archivo_pokemon_leer.read(nombre, sizeof(nombre));
        archivo_pokemon_leer.read(reinterpret_cast<char*>(&nivel), sizeof(nivel));
        archivo_pokemon_leer.read(reinterpret_cast<char*>(&puntos_vida), sizeof(puntos_vida));
        archivo_pokemon_leer.read(tipo, sizeof(tipo));
        archivo_pokemon_leer.read(reinterpret_cast<char*>(&estadistica_especial), sizeof(estadistica_especial));
        Pokemon* pokem = new Pokemon(nombre, nivel, puntos_vida, tipo, estadistica_especial);
        poke_sin.push_back(pokem);
    }
    archivo_usuarios_leer.close();
    archivo_pokemon_leer.close();
}

void menu()
{
    cargar_info();
    int opciones = 1;
    while (opciones != 0)
    {
        cout << "---- Menu ----" << endl
            << "1. Registro" << endl
            << "2. Iniciar seccion" << endl
            << "0. Salir" << endl
            << "Cual desea elegir: ";
        cin >> opciones;
        cout << endl;
        switch (opciones)
        {
        case 0: {
            ofstream cantidad("cantidad.bin", ios::binary);
            int cantidad_usarios = usa.size();
            int cantidad_pokemon = poke_sin.size();
            cantidad.write(reinterpret_cast<const char*>(&cantidad_usarios), sizeof(int));
            cantidad.write(reinterpret_cast<const char*>(&cantidad_pokemon), sizeof(int));
            cantidad.close();
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
        default:
            cout << "Caracter invalido, porfavor vuelve a intentarlo..." << endl;
            break;
        }
    }
}

int main()
{
    menu();
}
