OFILES = main.o bind.o m.o
TARGET = bind
# root-config --cxx >>Makefile
CC = c++
# root-config --cflags >>Makefile
CFLAGS = -pthread -std=c++11 -m64 -I/usr/local/include
# root-config --glibs >>Makefile
# for system(): -lstdc++
LIBS = -L/usr/local/lib -lGui -lCore -lRIO -lNet -lHist -lGraf -lGraf3d -lGpad -lTree -lRint \
-lPostscript -lMatrix -lPhysics -lMathCore -lThread -lMultiProc -pthread -lm -ldl -rdynamic
$(TARGET): $(OFILES)
	$(CC) $(OFILES) $(LIBS) -o $@

clean:
	rm -f $(OFILES) $(TARGET)

# below this is the output of "gcc -MM datroot.C ... >>Makefile":
main.o: main.C bind.hpp
bind.o: bind.C bind.hpp
m.o: m.C bind.hpp
