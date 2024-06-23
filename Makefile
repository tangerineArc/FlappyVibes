arc: arc.c
	gcc -I sdlMain/include -L sdlMain/lib -L sdlImage/lib -L sdlTTF/lib -o arc arc.c -l mingw32 -l SDL2main -l SDL2 -l SDL2_image -l SDL2_ttf