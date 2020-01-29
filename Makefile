CFLAGS= -Wall -Wextra -g -c 
CCPP= g++
SRC = src
LIB = lib
OBJ = obj
BIN = bin
OBJECTS=$(OBJ)/erreur.o $(OBJ)/affichage.o $(OBJ)/automate.o $(OBJ)/date.o $(OBJ)/lang.o $(OBJ)/fonctions.o $(OBJ)/transition.o
MAINOBJECTS= $(OBJ)/main.o
TESTOBJECTS= $(OBJ)/unittest.o $(OBJ)/testvalue.o $(OBJ)/rapport.o  
TESTMAINOBJECTS= $(OBJ)/maintest.o $(OBJ)/lexique.o $(OBJ)/transition.test.o $(OBJ)/test.o $(OBJ)/test2.o
TESTHEADER=$(SRC)/Erreur/Erreur.hpp  $(SRC)/TestClass/lib/UnitTest.hpp $(SRC)/TestClass/lib/TestValue.hpp $(SRC)/TestClass/lib/Rapport.hpp
HEADER= $(SRC)/Date/Date.hpp $(SRC)/affichage/affichage.hpp $(SRC)/lang/lang.hpp $(SRC)/Cellule/Cellule.hpp $(SRC)/fonctions/fonctions.hpp $(SRC)/Transition/Transition.hpp
do : app
$(OBJ)/test.o: $(SRC)/TestClass/TestClass.cpp
	$(CCPP) $(CFLAGS) $(SRC)/TestClass/TestClass.cpp  -o $(OBJ)/test.o
$(OBJ)/test2.o: $(SRC)/TestClass/lib/UnitTest.cpp
	$(CCPP) $(CFLAGS)  $(SRC)/test/test.cpp  -o $(OBJ)/test2.o
$(OBJ)/unittest.o: $(TESTHEADER) $(SRC)/TestClass/lib/UnitTest.cpp
	$(CCPP) $(CFLAGS) $(SRC)/TestClass/lib/UnitTest.cpp -o $(OBJ)/unittest.o
$(OBJ)/testvalue.o: $(TESTHEADER) $(SRC)/TestClass/lib/TestValue.cpp
	$(CCPP) $(CFLAGS) $(SRC)/TestClass/lib/TestValue.cpp -o $(OBJ)/testvalue.o
$(OBJ)/rapport.o: $(TESTHEADER) $(SRC)/TestClass/lib/Rapport.cpp
	$(CCPP) $(CFLAGS) $(SRC)/TestClass/lib/Rapport.cpp -o $(OBJ)/rapport.o 
$(OBJ)/automate.o: ${HEADER} $(SRC)/Automate/Automate.cpp
	$(CCPP) $(CFLAGS) $(SRC)/Automate/Automate.cpp -o $(OBJ)/automate.o $(OBJ)
$(OBJ)/date.o: ${HEADER} $(SRC)/Date/Date.cpp 
	$(CCPP) $(CFLAGS) $(SRC)/Date/Date.cpp -o $(OBJ)/date.o $(OBJ)
$(OBJ)/main.o: $(HEADER) $(SRC)/main/main.cpp $(SRC)/fonctions/fonctions.cpp
	$(CCPP) $(CFLAGS) $(SRC)/main/main.cpp -o $(OBJ)/main.o
$(OBJ)/maintest.o: $(HEADER) $(SRC)/test/main.cpp $(SRC)/fonctions/fonctions.cpp
	$(CCPP) $(CFLAGS) $(SRC)/test/main.cpp  -o $(OBJ)/maintest.o
$(OBJ)/lang.o: $(HEADER) $(SRC)/lang/lang.cpp $(SRC)/fonctions/fonctions.cpp
	$(CCPP) $(CFLAGS) $(SRC)/lang/lang.cpp  -o $(OBJ)/lang.o
$(OBJ)/transition.o: $(HEADER) $(SRC)/Transition/Transition.cpp  $(SRC)/fonctions/fonctions.cpp
	$(CCPP) $(CFLAGS) $(SRC)/Transition/Transition.cpp  -o $(OBJ)/transition.o
$(OBJ)/transition.test.o: $(HEADER) $(TESTHEADER) $(SRC)/Transition/transition.test.cpp $(SRC)/fonctions/fonctions.cpp
	$(CCPP) $(CFLAGS) $(SRC)/Transition/transition.test.cpp  -o $(OBJ)/transition.test.o	

$(OBJ)/fonctions.o: $(HEADER) $(SRC)/fonctions/fonctions.cpp
	$(CCPP) $(CFLAGS) $(SRC)/fonctions/fonctions.cpp  -o $(OBJ)/fonctions.o -lm
$(OBJ)/Cellule.o: $(HEADER) $(SRC)/Cellule/Cellule.cpp 
	$(CCPP) $(CFLAGS) $(SRC)/Cellule/Cellule.cpp -o $(OBJ)/Cellule.o
$(OBJ)/affichage.o: $(HEADER) $(SRC)/affichage/affichage.cpp $(SRC)/affichage/affichage.cpp
	$(CCPP) $(CFLAGS) $(SRC)/affichage/affichage.cpp  -o $(OBJ)/affichage.o
$(OBJ)/erreur.o: $(HEADER) $(SRC)/Erreur/Erreur.cpp
	$(CCPP) $(CFLAGS) $(SRC)/Erreur/Erreur.cpp -o $(OBJ)/erreur.o
$(OBJ)/lexique.o: $(HEADER) $(SRC)/Lexique/Parse.cpp
	$(CCPP) $(CFLAGS) $(SRC)/Lexique/Parse.cpp -o $(OBJ)/lexique.o 
app: ${OBJECTS} ${MAINOBJECTS}
	g++ -o $(BIN)/app ${OBJECTS} ${MAINOBJECTS}

clean: 
	rm -rf $(OBJ)/*.o
	rm -rf $(BIN)/test
	rm -rf $(BIN)/app

empty: 
	del /F /Q $(OBJ)\*
	del /F /Q $(BIN)\test.exe
	del /F /Q $(BIN)\app.exe
run: app
	./$(BIN)/app
test: ${OBJECTS} $(TESTMAINOBJECTS) $(TESTHEADER) ${TESTOBJECTS}   
	g++ -o $(BIN)/test ${OBJECTS} $(TESTMAINOBJECTS) ${TESTOBJECTS}
runtest: test
	./$(BIN)/test	