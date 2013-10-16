all::

NO_LTO=1
NOTESAPI=$(HOME)/notesapi-853

obj-test = main.o
TARGETS = test

test: ALL_CFLAGS  += -I$(NOTESAPI)/include
test: ALL_LDFLAGS += -lnotes

include base.mk
