# compiler variables
CC	= gcc

# directory variables
SRCDIR	= src
OBJDIR	= obj

# file variables
SRCS  	= $(wildcard $(SRCDIR)/*.c)
OBJS  	= $(SRCS:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

# executable
EXEC	= zeckendorf

# targets and dependencies
.PHONY: all mkdirs clean

all: mkdirs $(OBJS) $(EXEC)

mkdirs:
	mkdir -p $(OBJDIR)

$(OBJS): $(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(COMPILE.c) $(OUTPUT_OPTION) $<

$(EXEC): $(OBJS)
	$(CC) -o $@ $^

# clean-up
clean:
	rm -rf $(OBJDIR) $(EXEC)
