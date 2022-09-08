CC=g++
MAIN=main
AUX=funz
COMP=comprex


all: $(MAIN)

$(MAIN): $(MAIN).cpp $(AUX).cpp
	$(CC) -o $(MAIN) $(MAIN).cpp $(AUX).cpp

clean: $(MAIN)
	rm -rf $(MAIN)
	rm -rf $(COMP).txt
	
.PHONY: clean