ALL:
	gcc main.c -o gameoflife -lSDL_image -lSDL_ttf `sdl-config --cflags --libs`
