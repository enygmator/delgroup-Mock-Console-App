run.exe : Main.o delgroup.o
	gcc $? -o delgroup.exe
Main.o : Main.c
	gcc -c $? -o $@
delgroup.o : delgroup.c
	gcc -c $? -o $@
# This make file can be run using > make -f build.mk