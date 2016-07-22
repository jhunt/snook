all: driver
driver: driver.o read.o write.o sym.o
clean:
	rm *.o
