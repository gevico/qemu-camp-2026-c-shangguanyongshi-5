CC = gcc
CFLAGS = -Wall -I../../include

TARGET := mybash
BINDIR ?= ./bin
OBJDIR ?= ./obj
LINKLIBS ?= -L../../obj/mysed -L../../obj/mywc -L../../obj/mytrans -L../../obj/myfile

SRCS := main.c
OBJS := $(SRCS:.c=.o)
OBJS := $(patsubst %.o,$(OBJDIR)/%.o,$(OBJS))

TARGET_PATH := $(BINDIR)/$(TARGET)

all: $(TARGET_PATH)

$(TARGET_PATH): $(OBJS)
	@mkdir -p $(BINDIR)
	@$(CC) $(CFLAGS) -o $@ $^ $(LINKLIBS) -lmysed -lmywc -lmytrans -lmyfile

$(OBJDIR)/%.o: %.c
	@mkdir -p $(OBJDIR)
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -rf $(OBJDIR)/*.o $(TARGET_PATH)
