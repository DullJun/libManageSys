ifdef ARM
CC = arm-linux-gcc
else
CC = gcc
endif
export CC

TOPDIR :=$(shell pwd)
INCDIR :=$(TOPDIR)/inc
SRCDIR :=$(TOPDIR)/src

CPPFLAGS :=-I$(INCDIR)
CFLAGS :=-fno-builtin -Wall -O2
export CC TOPDIR INCDIR SRCDIR CPPFLAGS CFLAGS

TARGET = main
SRCS := $(wildcard *.c)
SRCS += $(foreach dir,$(SRCDIR),$(wildcard $(dir)/*.c))
OBJS := $(patsubst %.c,%.o,$(SRCS))

#$(warning src-->$(SRCS),objs-->$(OBJS))

all:$(TARGET) debug
$(TARGET):$(OBJS)
	$(CC) $^ -o $@
	
%.o:%.c
	$(CC) -c $^ -o $@ $(CPPFLAGS) $(CFLAGS)
	
.PHONY:clean
clean:
	rm -rf *.o $(TARGET)
	
.PHONY:debug
debug:
	@echo "src=$(SRCS),objs=$(OBJS)."
	

	