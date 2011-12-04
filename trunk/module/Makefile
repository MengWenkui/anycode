obj-m := module_list.o

//KERNELDIR := /lib/modules/$(shell uname -r)/build
KERNELDIR := /home/ydzhang/linux-2.6.19

PWD := $(shell pwd)

all:
	$(MAKE) -C $(KERNELDIR) M=$(PWD)

clean:
	rm -rf *.o *~ core .depend .*.cmd *.ko *.mod.c .tmp_versions


