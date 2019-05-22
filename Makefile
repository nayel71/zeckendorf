.PHONY: all rename
  
all: main rename

main: zeckadd.o zeckmult.o zeckpal.o zecksqr.o zeckstr.o

rename:
        mv main zeckendorf
