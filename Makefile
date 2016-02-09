linker: tlinker.cc tlinker.h linker.cc
	g++ -g tlinker.cc tlinker.h linker.cc -o linker
clean:
	rm -rf linker
