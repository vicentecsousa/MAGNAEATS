## Grupo 006
## Pedro trindade [NUMERO AQUI JA] 
## Vicente Sousa 55386
## João Anjos 54476

## Define vars

INCLUDEDIR = include
OBJDIR = obj
SRCDIR = src
BINDIR = bin
OUTNAME = MAGNAEATS

## Define objects needed for compilation

REQUIREDOBJ = client.o driver.o main.o memory.o process.o restaurant.o

## Create flags var
FLAGS = 

## Main target

all: clean compile

## add debug flag then proceed to do a full compilation
debug: FLAGS +=-g -Wall
debug: all

## create obj files
%.o: $(SRCDIR)/%.c
	$(CC) $(FLAGS) -o $(addprefix $(OBJDIR)/,$@) -c $< -I $(INCLUDEDIR)

## compiles the obj files to an executable
compile: $(REQUIREDOBJ)
	$(CC) $(FLAGS) $(addprefix $(OBJDIR)/,$^) -o $(OUTNAME)

## clean folders
clean:
	rm -rf $(OBJDIR)/*
	rm -rf $(BINDIR)/*

## find stuff marked to do in the project
wegucci:
	find . | grep -R TODO
