PCA9555: PCA9555.o
		arm-linux-gnueabihf-gcc -o $@ $^

%.o : %.S
		arm-linux-gnueabihf-gcc -g -c -O0 -o $@ $^ -Wall

%.o : %.c
		arm-linux-gnueabihf-gcc -g -c -O0 -o $@ $^ -Wall

clean:
		rm *.o *.elf *.bin *.dis *~ PCA9555 -rf
