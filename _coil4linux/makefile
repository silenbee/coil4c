INCLUDESLIB = -lfftw3

INCLUDESH = -I/usr/local/fftw/include

LIBS = -L/usr/local/fftw/lib

main: readData.o coil4c.cpp
	g++ -o coil4c coil4c.cpp readData.o $(INCLUDESH) $(INCLUDESLIB) $(LIBS)
readData.o: readData.cpp
	g++ -c readData.cpp
clean:
	rm -f *.o
.PHONY:
	clean
