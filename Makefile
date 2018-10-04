.PHONY: all

list = Core Hipo
all: 
	for i in $(list); do	$(MAKE) -C $$i ; done
