#include <stdio.h>
#include <stdlib.h>

int main (int argc, char *argv[])
{
	FILE *arquivo[5];
	int i;
	
	arquivo[0]=fopen("../Saves/slot0.bin","w+");
	arquivo[1]=fopen("../Saves/slot1.bin","w+");
	arquivo[2]=fopen("../Saves/slot2.bin","w+");
	arquivo[3]=fopen("../Saves/slot3.bin","w+");
	arquivo[4]=fopen("../Saves/slot4.bin","w+");

	
	return 0;
}
