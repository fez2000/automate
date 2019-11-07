 
CFLAGS= -Wall -Wextra -g -c 
CCPP= g++
SRC = ./src
LIB = ./lib
OBJ = ./obj
BIN = ./bin
OBJECTS= $(OBJ)/date.o $(OBJ)/affichage.o $(OBJ)/lang.o $(OBJ)/relations.o  $(OBJ)/Article.o $(OBJ)/Articles.o $(OBJ)/Commande.o $(OBJ)/Commandes.o $(OBJ)/Client.o $(OBJ)/Clients.o $(OBJ)/fonctions.o $(OBJ)/Livraison.o $(OBJ)/Livraisons.o 
MAINOBJECTS= $(OBJ)/main.o
TESTOBJECTS= $(OBJ)/test.o
HEADER= $(SRC)/Date/Date.h $(SRC)/affichage/affichage.h $(SRC)/lang/lang.h $(SRC)/Cellule/Cellule.h $(SRC)/relations/relations.h $(SRC)/Client/Client.h $(SRC)/Client/Clients.h  $(SRC)/Article/Article.h $(SRC)/Article/Articles.h $(SRC)/Commande/Commande.h $(SRC)/Commande/Commandes.h $(SRC)/fonctions/fonctions.h $(SRC)/Livraison/Livraison.h $(SRC)/Livraison/Livraisons.h
do : app
$(OBJ)/date.o: $(HEADER)
	$(CCPP) $(CFLAGS) $(SRC)/Date/Date.cpp -o $(OBJ)/date.o

app: ${OBJECTS} ${MAINOBJECTS}
	g++ -o $(BIN)/commerce ${OBJECTS} ${MAINOBJECTS}
clean: 
	rm -rf $(OBJ)/*.o
	rm -rf $(BIN)/test
	rm -rf $(BIN)/commerce
run: commerce
	./$(BIN)/commerce
test: ${OBJECTS} ${TESTOBJECTS}   
	g++ -o $(BIN)/test ${OBJECTS} ${TESTOBJECTS}
runtest: test
	./$(BIN)/test	