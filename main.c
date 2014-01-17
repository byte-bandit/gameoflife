
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char* argv[])
{

	int intWorldSize = 16;
	int world[intWorldSize][intWorldSize];


	//Initialize the world
	int i,j;
	for(i=0; i < intWorldSize; i++)
	{
		for(j=0; j < intWorldSize; j++)
		{
			if (i+j % 3 == 0)
			{
				world[i][j] = 1;
			}
			//world[i][j] = 0;
		}
	}

	/*world[4][4] = 1;
	world[5][4] = 1;
	world[6][4] = 1;
	world[6][3] = 1;
	*/
	world[5][2] = 1;
	//Game loop
	int quit = 0;
	while (quit == 0)
	{
		usleep(50000);

		//Calculate next step
		int newWorld[intWorldSize][intWorldSize];
		int x,y;
		int border = intWorldSize - 1;

		//Initialize new world
		for(x=0; x < intWorldSize; x ++)
		{
			for(y=0; y < intWorldSize; y++)
			{
				newWorld[x][y] = 0;
			}
		}

		for(x=0; x < intWorldSize; x ++)
		{
			for(y=0; y < intWorldSize; y ++)
			{
				int livingNext = 0;
				
				//UL
				if(x != 0 && y != 0)
				{
					if (world[x-1][y-1] == 1)
					{
						livingNext ++;
					}
				}

				//U
				if (y != 0)
				{
					if (world[x][y-1] == 1)
					{
						livingNext ++;
					}
				}

				//UR
				if (x < border && y != 0)
				{
					if (world[x+1][y-1] == 1)
					{
						livingNext ++;
					}
				}

				//L
				if (x != 0)
				{
					if (world[x-1][y] == 1)
					{
						livingNext ++;
					}
				}

				//R
				if (x < border)
				{
					if (world[x+1][y] == 1)
					{
						livingNext ++;
					}
				}

				//BL
				if (x != 0 && y < border)
				{
					if (world[x-1][y+1] == 1)
					{
						livingNext ++;
					}
				}

				//B
				if (y < border)
				{
					if (world[x][y+1] == 1)
					{
						livingNext ++;
					}
				}

				//BR
				if (x < border && y < border)
				{
					if (world[x+1][y+1] == 1)
					{
						livingNext ++;
					}
				}

				//Apply rules
				if (world[x][y] == 0)
				{
					//Dead cell
					if (livingNext == 3)
					{
						newWorld[x][y] = 1;
					}
				}
				else
				{
					//living cell
					if (livingNext < 2)
					{
						newWorld[x][y] = 0;
					}
					else
					{
						if (livingNext == 2 || livingNext == 3)
						{
							newWorld[x][y] = 1;
						}
						else
						{
							if (livingNext > 3)
							{
								newWorld[x][y] = 0;
							}
						}
					}
				}
			}
		}
		// Switch worlds
		for(x=0; x < intWorldSize; x++)
		{
			for(y=0; y < intWorldSize; y++)
			{
				world[x][y] = newWorld[x][y];
			}
		}

		//CLS
		system("clear");

		// Redraw world
		for(x=0; x < intWorldSize; x++)
		{
			for(y=0; y < intWorldSize; y++)
			{
				if (world[x][y] == 1)
				{
					printf("x");
				}
				else
				{
					printf(" ");
				}
			}
			printf("\n");
		}

		
	}
}
