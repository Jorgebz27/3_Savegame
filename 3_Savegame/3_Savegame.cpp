#include <iostream>
#include <fstream>

#define MAXNAMESIZE 16

enum EWeapon
{
    none, sword, lance, bow
};

//estructura de datos que deben persistir
struct SGameData
{
    char name[MAXNAMESIZE]; 
    EWeapon  currentWeapon;
    unsigned int  enemysKilled;
};


void Log(const char* msg)
{
    std::cout << msg << "\n";
}

const char* QueWeapon(EWeapon weapon)
{
    if (weapon == none)
    {
        return "ninguna";
    }else if(weapon == sword)
    {
        return "sword";
    }
    else if (weapon == lance)
    {
        return "lance";
    }
    else if (weapon == bow)
    {
        return "bow";
    }
    else 
    {

    }
}

int main()
{
    //leer el archivo de savegame
    std::fstream savefile("data.sav", std::ios::in | std::ios::out);

    if (savefile.is_open())
    {
        Log("savefile abierto");

        //leer datos del archivo
        SGameData data;
        savefile.read(data.name, MAXNAMESIZE);
        savefile.read((char*)&data.currentWeapon, 4);
        savefile.read((char*)&data.enemysKilled, 4);

        std::cout << "hola " << data.name;
        std::cout << ", tienes arma " << QueWeapon(data.currentWeapon) << " y has matado a " << data.enemysKilled << " enemigos.";

        Log("Te despiertas en un lugar desconocido, estas desconcertado.");
        Log("Avanzas un poco y a lo lejo ves tres caminos diferentes.");
        Log("¿Cual eliges?.");
        Log("Presiona 1 para izquierda, 2 para de frente y 3 para derecha.");

        std::string respuesta;
        std::cin >> respuesta;

        if (respuesta == "1")
        {
            Log("Avanzas por el camino rocoso y encuentras una lanza abandonda.");
            savefile.close();
            savefile.open("data.sav", std::ios::out);
            data.currentWeapon = EWeapon::lance;
            Log("La tomas y continuas tu camino.");
            Log("Has caminado mucho, estas cansado y hambriento.");
            Log("Ves un arbusto con frutos y por otro camino, un cofre.");
            Log("Presiona 1 para ir por los frutos o 2 para ir por el cofre.");

            std::cin >> respuesta;

            if (respuesta== "1")
            {
                Log("Comes los frutos y te comienzas a sentir mal, al parecer eran venenosos");
                Log("Bueno, fue bueno mientras duro");
            }
            else if (respuesta == "2") 
            {
                Log("¡Era una trampa! Te rodean 3 enemigos con apariencia inhumana");
                Log("¿Intentas atacar?");
                Log("Presiona 1 para si o 2 para no");

                savefile.close();
                std::cin >> respuesta;

                if (respuesta == "1")
                {
                    Log("Sin esfuerzo, logras derrotarlos, solo eran unos novatos");
                    savefile.open("data.sav", std::ios::out);
                    data.enemysKilled += 3;
                    if (savefile.is_open())
                    {
                        //dumpear la estructura data
                        savefile.seekp(0, std::ios::beg);
                        savefile.write((const char*)&data, sizeof(SGameData));
                    }
                    else
                    {
                        Log("no se pudo crear el archivo");
                    }
                }
                else if (respuesta == "2") 
                {
                    Log("No se como esperas resolver los problemas quedadnte quieto.");
                    Log("Evidentemente moriste :D.");
                }

            }
        }
        else if (respuesta == "2") 
        {
            Log("Te encuentras un arco, lo tomas?");
            Log("1. Si");
            Log("2. No");

            savefile.close();
            std::cin >> respuesta;

            if (respuesta == "1")
            {
                savefile.open("data.sav", std::ios::out);
                data.currentWeapon = EWeapon::bow;
            }
            else {
                data.currentWeapon = EWeapon::none;
            }



        }
        else 
        {

        }

    }
    else
    {
        Log("crear savefile vacio e inicial");
        SGameData data;
        Log("Escribe tu nombre, aventurero");
        std::cin >> data.name;
        data.currentWeapon = EWeapon::none;
        data.enemysKilled = 0;
        savefile.open("data.sav", std::ios::out);
        if (savefile.is_open())
        {
            //dumpear la estructura data
            savefile.seekp(0, std::ios::beg);
            savefile.write((const char*)&data, sizeof(SGameData));
        }
        else
        {
            Log("no se pudo crear el archivo");
        }

    }

    savefile.close();

    return 0;
}