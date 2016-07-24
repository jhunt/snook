all: driver
driver: driver.o read.o write.o sym.o box.o cons.o predicate.o interpreter.o
clean:
	rm *.o
