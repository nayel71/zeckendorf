# compiler variables
CC      = gcc
LDLIBS  =
CFLAGS  = -Wall -MMD -MP -Werror=vla

ifeq ($(enable_asan),1)
ASFLAGS =
CFLAGS += $(ASFLAGS) -g -O3
endif

# directory variables
SRCDIR  = src
OBJDIR  = obj
DEPDIR  = dep
INCDIR  = include

CFLAGS += -I$(INCDIR)

# file variables
SRCS    = $(wildcard $(SRCDIR)/*.c)
OBJS    = $(SRCS:$(SRCDIR)/%.c=$(OBJDIR)/%.o)
DEPS    = $(OBJS:.o=.d)

# executable
EXEC    = zeckendorf

# targets and dependencies
.PHONY: all mkdirs clean

all: mkdirs $(OBJS) $(EXEC)

mkdirs:
	mkdir -p $(OBJDIR) $(DEPDIR)

$(OBJS): $(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(COMPILE.c) $(OUTPUT_OPTION) $<

$(EXEC): $(OBJS)
	$(CC) $(ASFLAGS) $(LDLIBS) -o $@ $^
	mv $(OBJDIR)/*.d $(DEPDIR)/

-include $(DEPS)

# clean-up
clean:
	rm -rf $(OBJDIR) $(DEPDIR) $(EXEC) $(EXEC).dSYM/
