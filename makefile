GPP = g++ -m32 -Ilib -fno-stack-protector  -fpack-struct=1
GCC = gcc -m32 -fpack-struct=1
DRP_OUTFILE = "./samp-drp.so"

COMPILE_FLAGS = -g -O3 -c -fPIC -w -DLINUX

DRP = -D DRP $(COMPILE_FLAGS)

all: DRP

clean:
	-rm -f *~ *.o *.so

DRP: clean
	$(GPP) $(DRP) ./dependencies/include/SDK/*.cpp
	$(GPP) $(DRP) ./dependencies/include/raknet/BitStream.cpp
	$(GCC) $(DRP) ./dependencies/include/subhook/subhook.c
	$(GPP) $(DRP) ./server/*.cpp
	$(GCC) -g -nodefaultlibs -fshort-wchar -shared -o $(DRP_OUTFILE) *.o
