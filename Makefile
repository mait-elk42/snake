lib = src/lib/libgfx_nsx.a

all: compilelink
	cd ./executable/Windows && start release.exe
debug: compiledebug
	cd ./executable/Windows && start debug.exe
compilelink: lib manifest
	g++ -Isrc/include main.cpp resources/manifest.res -o executable/Windows/release -DSFML_STATIC -Lsrc/lib -lgfx_nsx -lws2_32 -lopengl32 -lgdi32 -lwinmm -static -mwindows
compiledebug: lib manifest
	g++ -Isrc/include main.cpp resources/manifest.res -o executable/Windows/debug -DSFML_STATIC -Lsrc/lib -lgfx_nsx -lws2_32 -lopengl32 -lgdi32 -lwinmm -static
manifest:
	windres.exe -J rc -O coff -i resources/manifest.rc -o resources/manifest.res
lib:
	cd src/srcs && g++ -I../include -c *.cpp -D SFML_STATIC
	ar -crs $(lib) src/lib/objects/*.o src/srcs/*.o