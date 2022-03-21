
#include <SDL.h>
#include <Game.h>
#include <time.h>

int main(int argc, char *argv[])
{
	time(NULL); // Atsitiktinio skaicio generavimo iniciavimas
	new Game(); // Pradedam zaidima, visa logika yra Game.h/.cpp

	return 0;
}