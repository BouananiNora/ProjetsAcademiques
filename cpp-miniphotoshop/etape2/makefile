#commentaire

.SILENT:

CLS = Classes/
OBJ= $(CLS)ImageNG.o  $(CLS)Dimension.o
COMP= g++ -I $(CLS) -D DEBUG



all:	Test2

Test2:	Test2.cpp $(OBJ) 
		$(COMP) Test2.cpp  -o Test2 $(OBJ)
		echo --- Creation de Test2 ---

$(CLS)ImageNG.o:	$(CLS)ImageNG.cpp $(CLS)ImageNG.h 
		$(COMP) $(CLS)ImageNG.cpp -c -o $(CLS)ImageNG.o
		echo --- Creation de ImageNG.o ---

$(CLS)Dimension.o:	$(CLS)Dimension.cpp $(CLS)Dimension.h 
		$(COMP) $(CLS)Dimension.cpp -c -o $(CLS)Dimension.o
		echo --- Creation de Dimension.o ---



clean:
	rm -f $(CLS)*.o core
	echo --- supp objet ---

clobber:	clean
	rm -f  Test2
	echo --- supp des executables ---		