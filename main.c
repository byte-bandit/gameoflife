#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

SDL_Surface *screen;
SDL_Surface *i_0;
SDL_Surface *i_1;

void drawPic(SDL_Surface *surface, int x, int y);

void drawPic(SDL_Surface *surface, int x, int y)
{
	SDL_Rect rect;
	rect.x = x;
	rect.y = y;
	rect.w = surface -> w;
	rect.h = surface -> h;

	SDL_BlitSurface(surface, NULL, screen, &rect);
}

int main(int argc, char* argv[])
{

	int intWorldSize = 32;
	int world[intWorldSize][intWorldSize];
	int tilesize = 12;

	i_0 = IMG_Load("0.png");
	i_1 = IMG_Load("1.png");

	SDL_Event event;
	
	if (SDL_Init(SDL_INIT_VIDEO) == -1)
	{
		printf("Can't into SDL");
		exit(1);
	}

	atexit(SDL_Quit);
	screen = SDL_SetVideoMode(640,480, 16, SDL_HWSURFACE);
	if (screen == NULL)
	{
		printf("Can't into video mode.");
		exit(1);
	}

	//Initialize the world
	int i,j;
	for(i=0; i < intWorldSize; i++)
	{
		for(j=0; j < intWorldSize; j++)
		{
			world[i][j] = 0;
			if ((i+j) % 3 == 0)
			{
				world[i][j] = 1;
			}
		}
	}

	world[4][4] = 1;
	world[5][4] = 1;
	world[6][4] = 1;
	world[6][3] = 1;
	world[5][2] = 1;

	//Game loop
	int quit = 0;
	int gen = 0;
	while (quit == 0)
	{
		usleep(100000);
		gen ++;

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
				else
				{
					int newx, newy;
					newx = x;
					newy = y;
					if(x == 0)
					{
						newx = intWorldSize;
					}
					if(y == 0)
					{
						newy = intWorldSize;
					}
					if (world[newx][newy] == 1)
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
				else
				{
					int newx, newy;
					newx = x;
					newy = y;
					if(x == 0)
					{
						newx = intWorldSize;
					}
					if(y == 0)
					{
						newy = intWorldSize;
					}
					if (world[newx][newy] == 1)
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
				else
				{
					int newx, newy;
					newx = x;
					newy = y;
					if(x == 0)
					{
						newx = intWorldSize;
					}
					if(y == 0)
					{
						newy = intWorldSize;
					}
					if (world[newx][newy] == 1)
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
		//system("clear");

		// Redraw world
		for(x=0; x < intWorldSize; x++)
		{
			for(y=0; y < intWorldSize; y++)
			{
				if (world[x][y] == 1)
				{
					//printf("x");
					drawPic(i_1, x * tilesize, y * tilesize);
				}
				else
				{
					//printf("_");
					drawPic(i_0, x * tilesize, y * tilesize);
				}
			}
			//printf("\n");
		}
		printf("\n%i. Generation\n", gen);

		SDL_Flip(screen);

		while(SDL_PollEvent (&event))
		{
			switch(event.type)
			{
				case SDL_QUIT:
					quit = 1;
					break;
			}
		}
		
	}
}
