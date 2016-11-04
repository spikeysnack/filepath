#!/bin/make

# AUTHOR:  Chris Reid <spikeysnack@gmail.com> #
# LICENSE: Free for all purposes              #
# COPYRIGHT: 2016- Chris Reid                 #


# modification allowed 
# but original attribution stays, add your name to any mods 
# no guarantees implied or inferred
# standard C 
# to build: "just type make"

DEBUG = 1

SHELL=/bin/sh

PROGRAM="filepath"
VER="1.3"
TARBALL=$(PROGRAM)-$(VER).tgz

CC=gcc
BASE_CFLAGS = -fstrict-aliasing -fpic  -Wno-unused-function
OPTIMIZE_FLAGS = -mtune=native  -foptimize-strlen
CFLAGS = $(BASE_CFLAGS) $(OPTIMIZE_FLAGS)
DEBUGCFLAGS = -O0 -ggdb3 -fomit-frame-pointer

#CFLAGS= -O0 -ggdb3 -fomit-frame-pointer

#prefix= $HOME  # set to home dir if you can't use sudo
prefix = /usr/local
bindir = $(prefix)/bin
mandir = $(prefix)/share/man
manext = 1
docdir = $(prefix)/share/doc/filepath
TAR = $(shell which tar)
ARCHIVER = $(TAR)
INSTALL = $(shell which install)
INSTALL_PROGRAM = $(INSTALL)

.PHONY:	all install install-bin install-man install-doc uninstall dist distclean test clean


all:	filepath 


filepath:	options.h filepath.c
	$(CC) $(CFLAGS) -o filepath filepath.c

debug:	options.h filepath.c
	$(CC) $(DEBUGCFLAGS) -DDEBUG -o filepath filepath.c

test:	filepath
	ln -sf doc/filepath.html  .
	./filepath  -v
	@echo  "\n"
	./filepath -h
	@echo  "\n"
	./filepath 
	@echo  "\n"
	./filepath  -w non-existent-file
	@echo  "\n"
	./filepath  -W non-existent-file
	@echo  "\n"
	./filepath  /root/.profile
	@echo  "\n"
	./filepath  -w /root/.profile
	@echo  "\n"
	./filepath  -W /root/.profile
	@echo  "\n"
	./filepath  -W  http://www.google.com
	@echo  "\n"
	./filepath  -w *.html
	@echo  "\n"
	./filepath  -d *
	@echo  "\n"
	./filepath  -D"-&-" *
	@echo  "\n"
	./filepath  -w -d  *.c *.h doc/*  
	@echo  "\n"
	./filepath  -w -d  -c *.c *.h doc/*  
	@echo  "\n"
	./filepath  -W -d  *.c *.h doc/*  
	@echo  "\n"
	./filepath  -W -d  -c *.c *.h doc/*  
	@echo  "\n"


help:	
	@echo  "make options:"
	@echo  "\t make"
	@echo  "\t make test"
	@echo  "\t sudo make install"


clean:	
	rm -f -- *~ \#* core  filepath filepath.html

distclean:      clean
	rm -f *.tgz 

# make tarball for distribution
dist:   distclean
	cd .. ; $(TAR) czf $(TARBALL)  filepath;  mv $(TARBALL) filepath/ 


install:        install-bin	install-man	install-doc
        @sensible-browser "file:///usr/local/share/doc/filepath.html"

install-bin:	filepath
	$(INSTALL_PROGRAM) --mode=0755 filepath $(bindir)/filepath

install-man:	doc/filepath.1
	$(INSTALL_PROGRAM) --mode=0644 doc/filepath.1 $(mandir)/man$(manext)/filepath.1

install-doc:
	$(INSTALL_PROGRAM) -d -g users --mode=0755 $(docdir)/
	cp -a doc/* $(docdir)/ 


uninstall:
	rm  $(bindir)/filepath
	rm  $(mandir)/filepath.1
	rm  -rf $(docdir)



#END
