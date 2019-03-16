#include "VoroClient.h"

int main()
{
	VoroClient client;

	client.read_command("command.txt");
	client.initialize();
	client.modify_solutions();
	client.integrate_solutions();

	system("pause");
}