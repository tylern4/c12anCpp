.PHONY: all

list = Core Hipo Root
all: 
	for i in $(list); do	$(MAKE) -C $$i ; done
