OFILES = htv.o
TARGET = htv
# root-config --cxx >>Makefile
CC = c++
# root-config --cflags >>Makefile
CFLAGS = -pthread -std=c++11 -m64 -I/usr/local/include
# root-config --glibs >>Makefile
LIBS = -L/usr/local/lib -lGui -lCore -lRIO -lNet -lHist -lGraf -lGraf3d -lGpad -lTree -lRint \
-lPostscript -lMatrix -lPhysics -lMathCore -lThread -lMultiProc -pthread -lm -ldl -rdynamic
$(TARGET): $(OFILES)
	$(CC) $(OFILES) $(LIBS) -o $@

clean:
	rm -f $(OFILES) $(TARGET)

# below this is the output of "gcc -MM datroot.C ... >>Makefile":
htv.o: htv.C
