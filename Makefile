CFLAGS= -Wall -Wextra -g -c 
CCPP= g++
SRC = ./src
LIB = ./lib
OBJ = ./obj
BIN = ./bin
OBJECTS=$(OBJ)/affichage.o $(OBJ)/date.o $(OBJ)/lang.o $(OBJ)/fonctions.o $(OBJ)/transition.o
MAINOBJECTS= $(OBJ)/main.o
TESTOBJECTS= $(OBJ)/test.o
HEADER= $(SRC)/Date/Date.hpp $(SRC)/affichage/affichage.hpp $(SRC)/lang/lang.hpp $(SRC)/Cellule/Cellule.hpp $(SRC)/fonctions/fonctions.hpp $(SRC)/Transition/Transition.hpp
do : app
$(OBJ)/date.o: ${HEADER} 
	$(CCPP) $(CFLAGS) $(SRC)/Date/Date.cpp -o $(OBJ)/date.o $(OBJ)
$(OBJ)/main.o: $(HEADER)
	$(CCPP) $(CFLAGS) $(SRC)/main/main.cpp -o $(OBJ)/main.o
$(OBJ)/test.o: $(HEADER)
	$(CCPP) $(CFLAGS) $(SRC)/test/main.cpp  -o $(OBJ)/test.o
$(OBJ)/lang.o: $(HEADER)
	$(CCPP) $(CFLAGS) $(SRC)/lang/lang.cpp  -o $(OBJ)/lang.o
$(OBJ)/transition.o: $(HEADER)
	$(CCPP) $(CFLAGS) $(SRC)/Transition/Transition.cpp  -o $(OBJ)/transition.o
$(OBJ)/fonctions.o: $(HEADER)
	$(CCPP) $(CFLAGS) $(SRC)/fonctions/fonctions.cpp  -o $(OBJ)/fonctions.o -lm
$(OBJ)/Cellule.o: $(HEADER) 
	$(CCPP) $(CFLAGS) $(SRC)/Cellule/Cellule.cpp -o $(OBJ)/Cellule.o
$(OBJ)/affichage.o: $(HEADER)
	$(CCPP) $(CFLAGS) $(SRC)/affichage/affichage.cpp  -o $(OBJ)/affichage.o	
app: ${OBJECTS} ${MAINOBJECTS}
	g++ -o $(BIN)/app ${OBJECTS} ${MAINOBJECTS}
clean: 
	rm -rf $(OBJ)/*.o
	rm -rf $(BIN)/test
	rm -rf $(BIN)/app
run: app
	./$(BIN)/app
test: ${OBJECTS} ${TESTOBJECTS}   
	g++ -o $(BIN)/test ${OBJECTS} ${TESTOBJECTS}
runtest: test
	./$(BIN)/test	