CFLAGS= -Wall -Wextra -g -c 
CCPP= g++
SRC = ./src
LIB = ./lib
OBJ = ./obj
BIN = ./bin
OBJECTS=$(OBJ)/erreur.o $(OBJ)/affichage.o $(OBJ)/automate.o $(OBJ)/date.o $(OBJ)/lang.o $(OBJ)/fonctions.o $(OBJ)/transition.o
MAINOBJECTS= $(OBJ)/main.o
TESTOBJECTS= $(OBJ)/unittest.o $(OBJ)/testvalue.o $(OBJ)/rapport.o  
TESTMAINOBJECTS= $(OBJ)/maintest.o $(OBJ)/transition.test.o $(OBJ)/test.o $(OBJ)/test2.o
TESTHEADER=$(SRC)/Erreur/Erreur.hpp  $(SRC)/Test/lib/UnitTest.hpp $(SRC)/Test/lib/TestValue.hpp $(SRC)/Test/lib/Rapport.hpp
HEADER= $(SRC)/Date/Date.hpp $(SRC)/affichage/affichage.hpp $(SRC)/lang/lang.hpp $(SRC)/Cellule/Cellule.hpp $(SRC)/fonctions/fonctions.hpp $(SRC)/Transition/Transition.hpp
do : app
$(OBJ)/test.o:
	$(CCPP) $(CFLAGS) $(SRC)/Test/Test.cpp  -o $(OBJ)/test.o
$(OBJ)/test2.o:
	$(CCPP) $(CFLAGS)  $(SRC)/test/test.cpp  -o $(OBJ)/test2.o
$(OBJ)/unittest.o: $(TESTHEADER)
	$(CCPP) $(CFLAGS) $(SRC)/Test/lib/UnitTest.cpp -o $(OBJ)/unittest.o
$(OBJ)/testvalue.o: $(TESTHEADER)
	$(CCPP) $(CFLAGS) $(SRC)/Test/lib/TestValue.cpp -o $(OBJ)/testvalue.o
$(OBJ)/rapport.o: $(TESTHEADER)
	$(CCPP) $(CFLAGS) $(SRC)/Test/lib/Rapport.cpp -o $(OBJ)/rapport.o 
$(OBJ)/automate.o: ${HEADER}
	$(CCPP) $(CFLAGS) $(SRC)/Automate/Automate.cpp -o $(OBJ)/automate.o $(OBJ)
$(OBJ)/date.o: ${HEADER} 
	$(CCPP) $(CFLAGS) $(SRC)/Date/Date.cpp -o $(OBJ)/date.o $(OBJ)
$(OBJ)/main.o: $(HEADER)
	$(CCPP) $(CFLAGS) $(SRC)/main/main.cpp -o $(OBJ)/main.o
$(OBJ)/maintest.o: $(HEADER)
	$(CCPP) $(CFLAGS) $(SRC)/test/main.cpp  -o $(OBJ)/maintest.o
$(OBJ)/lang.o: $(HEADER)
	$(CCPP) $(CFLAGS) $(SRC)/lang/lang.cpp  -o $(OBJ)/lang.o
$(OBJ)/transition.o: $(HEADER)
	$(CCPP) $(CFLAGS) $(SRC)/Transition/Transition.cpp  -o $(OBJ)/transition.o
$(OBJ)/transition.test.o: $(HEADER) $(TESTHEADER)
	$(CCPP) $(CFLAGS) $(SRC)/Transition/transition.test.cpp  -o $(OBJ)/transition.test.o	

$(OBJ)/fonctions.o: $(HEADER)
	$(CCPP) $(CFLAGS) $(SRC)/fonctions/fonctions.cpp  -o $(OBJ)/fonctions.o -lm
$(OBJ)/Cellule.o: $(HEADER) 
	$(CCPP) $(CFLAGS) $(SRC)/Cellule/Cellule.cpp -o $(OBJ)/Cellule.o
$(OBJ)/affichage.o: $(HEADER)
	$(CCPP) $(CFLAGS) $(SRC)/affichage/affichage.cpp  -o $(OBJ)/affichage.o
$(OBJ)/erreur.o: $(HEADER)
	$(CCPP) $(CFLAGS) $(SRC)/Erreur/Erreur.cpp -o $(OBJ)/erreur.o 
app: ${OBJECTS} ${MAINOBJECTS}
	g++ -o $(BIN)/app ${OBJECTS} ${MAINOBJECTS}

clean: 
	rm -rf $(OBJ)/*.o
	rm -rf $(BIN)/test
	rm -rf $(BIN)/app
run: app
	./$(BIN)/app
test: ${OBJECTS} $(TESTMAINOBJECTS) $(TESTHEADER) ${TESTOBJECTS}   
	g++ -o $(BIN)/test ${OBJECTS} $(TESTMAINOBJECTS) ${TESTOBJECTS}
runtest: test
	./$(BIN)/test	