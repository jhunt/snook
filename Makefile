all: driver
driver: driver.o read.o write.o
clean:
	rm *.o
