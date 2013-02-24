all::

NOTESAPI=$(HOME)/Downloads/Lotus_CAPITkt_Dom853/notesapi

obj-test = main.o
TARGETS = test

test: ALL_CFLAGS  += -I$(NOTESAPI)/include
test: ALL_LDFLAGS += -lnotes

include base.mk
