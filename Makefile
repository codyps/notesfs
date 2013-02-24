all::

LOTUS=/opt/lotus
NOTESAPI=$(LOTUS)/notesapi
NOTESDIR=$(Notes_ExecDirectory) # FIXME: this is bogus


obj-test = main.o
TARGETS = test

test: ALL_CFLAGS  += -I$(NOTESAPI)/include
test: ALL_LDFLAGS += -L$(NOTESDIR)

include base.mk
