PWD := $(shell pwd)

SUBDIRS := 	mysed 	myfile 	mywc 	mytrans

all: mybash

$(SUBDIRS):
	$(MAKE) -C src/$@ OBJDIR=$(PWD)/obj/$@

mybash: $(SUBDIRS)
	$(MAKE) -C src/mybash 		OBJDIR=$(PWD)/obj/mybash 		BINDIR=$(PWD)/bin 		LINKLIBS="-L$(PWD)/obj/mysed -L$(PWD)/obj/mywc -L$(PWD)/obj/mytrans -L$(PWD)/obj/myfile"

clean:
	for d in $(SUBDIRS); do $(MAKE) -C src/$$d clean OBJDIR=$(PWD)/obj/$$d; done
	$(MAKE) -C src/mybash clean OBJDIR=$(PWD)/obj/mybash BINDIR=$(PWD)/bin
	@rm -rf $(PWD)/obj $(PWD)/bin

.PHONY: all $(SUBDIRS) mybash clean
