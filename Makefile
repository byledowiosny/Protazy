OFILES = main.o tv.o vmm.o w.o m.o scale.o scalebis.o rm.o 
TARGET = protazy

SHELL = /bin/sh

CC := $(shell root-config --cxx)                          # root-config --cxx >> Makefile
CFLAGS := -I./ -I./include $(shell root-config --cflags)  # root-config --cflags >> Makefile
#CFLAGS = -pthread -std=c++11 -m64 -I/usr/local/include
LIBS := -L./ -L./lib/cspice.a $(shell root-config --libs) # root-config --glibs >> Makefile
#GLIBS	:= $(shell root-config --glibs)

$(TARGET): $(OFILES)
	$(CC) $(OFILES) $(LIBS) -o $@ #./cspice/lib/cspice.a

clean:
	rm -f $(OFILES) $(TARGET)

# below this is the output of "gcc -MM csvds.C ... >> Makefile":
main.o: main.C tv.hpp
tv.o: tv.C tv.hpp
vmm.o: vmm.C tv.hpp
w.o: w.C tv.hpp
m.o: m.C tv.hpp
scale.o: scale.C tv.hpp
scalebis.o: scalebis.C tv.hpp
rm.o: rm.C tv.hpp
