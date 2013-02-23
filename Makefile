all::

LOTUS=/opt/lotus
NOTESAPI=$(LOTUS)/notesapi
NOTESDIR=$(Notes_ExecDirectory) # FIXME: this is bogus

obj-test = main.o
TARGETS = test

test: CFLAGS  += -I$(NOTESAPI)/include
test: LDFLAGS += -L$(NOTESDIR)

include base.mk
