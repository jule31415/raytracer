CC=g++
CFLAGS=-I /usr/include/opencv4 -O3 

ODIR=obj
#LDIR =/usr/local/lib

LIBS=-lopencv_core -lopencv_imgproc -lopencv_highgui -lopencv_imgcodecs

DEPS = CSzene.h zylinder.h Kugel.h rectyz.h rectxz.h quadrat.h formen.h ray.h lightsource.h
#DEPS = $(patsubst %,$(_DEPS))

_OBJ = main.o CSzene.o zylinder.o Kugel.o rectyz.o rectxz.o quadrat.o quadrat.o formen.o ray.o lightsource.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))


$(ODIR)/%.o: %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

dreide: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~ dreide


#all: main.cpp CSzene.h CSzene.cpp zylinder.h zylinder.cpp Kugel.h Kugel.cpp rectyz.h rectyz.cpp rectxz.h rectxz.cpp quadrat.h quadrat.cpp formen.h formen.cpp

#	g++ -I/usr/local/include/opencv2 -I/usr/local/include/opencv -L/usr/local/lib/ -g -Wall -Wextra -pedantic-errors main.cpp CSzene.h CSzene.cpp zylinder.h zylinder.cpp Kugel.h Kugel.cpp rectyz.h rectyz.cpp rectxz.h rectxz.cpp quadrat.h quadrat.cpp formen.h formen.cpp -o geometrietest -lopencv_core -lopencv_imgproc -lopencv_highgui
