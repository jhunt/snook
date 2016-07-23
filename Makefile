all: driver
driver: driver.o read.o write.o sym.o cons.o verify.o
clean:
	rm *.o
