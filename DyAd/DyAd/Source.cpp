
#include <iostream>
#include <time.h>		// para sembrar el random y el chrono
#include <chrono>
#include <conio.h>		// para poder usar el _getch() al final para poder leer la última pg.
#include <limits>		// para poder usar el cin.ignore(numeric_limits.....

using namespace std;

class Timer
{
private:
	// Type aliases to make accessing nested type easier
	using clock_t = std::chrono::high_resolution_clock;
	using second_t = std::chrono::duration<double, std::ratio<1, 1000000> >;

	std::chrono::time_point<clock_t> m_beg;

public:
	Timer() : m_beg(clock_t::now())
	{
	}

	void reset()
	{
		m_beg = clock_t::now();
	}

	double elapsed() const
	{
		return std::chrono::duration_cast<second_t>(clock_t::now() - m_beg).count();
	}
};

struct Intento
{
	short digitos[4] = { 0,0,0,0 };
	short dYa[2] = { 0,0 };
	short ordinal = 0;
	double  tint;
};

void inicia(void);
void generaincognito(short*);
Intento entrarintento(Intento array[], short);

Timer t;
short  incognito[4];	// array donde guargar los dígitos del incognito
Intento intento[15];	// se reserva espacio para 15 intentos

int main()
{
	inicia();
	_getch();
	generaincognito(incognito);
	short i = 0;
	do {
		// cout << &intento <<"\t";
		intento[i] = entrarintento(intento, i);		// ha estado fallando  porque me deje el void delante!!!
		i++;
	} while (intento[i - 1].dYa[0] < 4 && i < 15);
	system("cls");
	cout << endl;
	for (short j = 0; j < i; j++)
	{
		cout << "\t" << intento[j].digitos[0] << " " << intento[j].digitos[1] << " " << intento[j].digitos[2]
			<< " " << intento[j].digitos[3] << "\t" << " " << intento[j].dYa[0] << " D \t" <<
			intento[j].dYa[1] << " A \t\t";
		cout.width(2);
		cout << intento[j].ordinal << "  elapsed time :";
		cout.width(14); cout.precision(6); cout.fixed;
		cout << fixed << intento[j].tint << " seconds" << endl;
	}
	_getch();
	/* queda guardar datos para file de partidas (incognito, intentos, tiempo) en otra parte
	   leer  el file, ordenarla y presentar los mejores */
}

void generaincognito(short* incognito)
{
	bool nr;
	for (short i = 0; i < 4; i++)
	{
		srand(time(NULL));
		do
		{
			nr = false;
			incognito[i] = rand() % 10;
			if (i > 0)
			{
				for (short j = 0; j < i; j++)
				{
					if (incognito[j] == incognito[i])
					{
						nr = true;
						break;
					}
					else
					{
						nr = false;
					}
				}
			}

		} while (nr);
	}
	/* for (short i = 0; i < 4; i++)
		cout << "\n\t" << i + 1 << ": " << incognito[i] ; */
}

Intento  entrarintento(Intento  intent[], short ind)
{
	// primero limpia consola y escribe las soluciones anteriores si las hay
	system("CLS");
	Intento local[15];
	for (short h = 0; h < 15; h++)
	{
		local[h] = intent[h];
	}
	bool OK;
	short a[4]{ 0 };
	do
	{
		system("cls");
		if (ind > 0)
		{
			cout << endl;
			/*for (short i = 0; i < 4; i++)
			{
				cout << "\t" << i + 1 << ": " << incognito[i];
			}*/
			cout << endl;
			cout << endl;
			for (short j = 0; j < ind; j++)
			{
				cout << "\t" << local[j].digitos[0] << " " << local[j].digitos[1] << " " << local[j].digitos[2]
					<< " " << local[j].digitos[3] << "\t" << "   ->  " << local[j].dYa[0] << " D \t" <<
					local[j].dYa[1] << " A \t\t";
				cout.width(2);
				cout << local[j].ordinal << "  elapsed time :";
				cout.width(14); cout.precision(6); cout.fixed;
				cout << fixed <<intento[j].tint << " seconds" << endl;
			}
		}
		cin.clear();    // resetea errores flags 
		cin.ignore(numeric_limits<streamsize>::max(), '\n');  // vacía mierda potencial
		char rend{ NULL };
		cin.get(rend);
		if (rend == 'R')
		{
			for (short i = 0; i < 4; i++)
			{
				cout << "\t" << i + 1 << ": " << incognito[i];
			}
		}
		cout << "\n\tentre cuatro digitos distintos separados por espacios ";
		OK = false;
		cin >> a[0] >> a[1] >> a[2] >> a[3];

		// comprueba que las entradas son todo dígitos del 0 al 9
		for (short v = 0; v < 4; v++)
		{
			for (short w = 0; w < v; w++)
			{
				if (a[v] == a[w] || a[v] < 0 || a[v]> 9)
					OK = true;
			}
		}
	} while (OK);
	for (short w = 0; w < 4; w++)
	{
		intent[ind].digitos[w] = a[w];
	}
	// cuenta dianas
	short dianas{ 0 };
	for (short w = 0; w < 4; w++)
	{
		if (intent[ind].digitos[w] == incognito[w])
		{
			dianas++;
		}
	}
	intent[ind].dYa[0] = dianas;
	// cuenta aproximaciones
	short  aprox{ 0 };
	for (short w = 0; w < 4; w++)
	{
		for (short v = 0; v < 4; v++)
		{
			if (intent[ind].digitos[v] == incognito[w] && (w != v))
			{
				aprox++;
			}
		}
	}
	intent[ind].dYa[1] = aprox;
	double et = t.elapsed() / 1000000;
	if (ind > 0)
	{
		intent[ind].ordinal = intent[ind - 1].ordinal + 1;
		intent[ind].tint = et;
	}
	else
	{
		intent[ind].ordinal = 1;
		intent[ind].tint = et;
	}
	return intent[ind];
}

void inicia()
{
	cout << "\n\t DIANAS Y APROXIMACIONES" << endl;
	cout << "\n El objetivo de esta aplicacion es encontrar la clave, una serie de 4 digitos" << endl;
	cout << "\n como 2 3 0 7 todos distintos teniendo como pistas la respuesta que da el " << endl;
	cout << "\n programa en forma de dianas (cuando el digito ocupa el mismo espacio  por ejemplo" << endl;
	cout << "\n 2 3 0 7 y 5 1 0 8 seria una diana por el cero) o aproximaciones (cuando el digito" << endl;
	cout << "\n esta pero ocupa otra posicion por ejemplo 2 3 0 7  y 3 7 4 1 serian dos " << endl;
	cout << "\n aproximaciones por el 3 y el 7." << endl;
	cout << "\n en total hay 5040 posibilidades, cada tentativa excluye opciones, hay que " << endl;
	cout << "\n analizar que nos queda seguro." << endl;
	cout << "\n entre entradas para tener otro intento pulsar INTRO, ENTER" << endl;
	cout << "\n o la tecla esa de siempre ... a veces mas de una vez, se puede corregir " << endl;
	cout << "\n usando back-space o la tecla con la flecha que indica a la iquierda sobre el intro" << endl;
	cout << "\n Si entra numeros mayores que nueve o caracteres o cosas raras le volvera a" << endl;
	cout << "\n pedir de nuevo que entre un intento valido" << endl;
}
