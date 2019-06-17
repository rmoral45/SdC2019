obj-m += pin-control.o

all:
	make M=$(PWD) -C /lib/modules/$(shell uname -r)/build  modules

clean:
	make M=$(PWD) -C /lib/modules/$(shell uname -r)/build  clean
