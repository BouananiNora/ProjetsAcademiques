.SILENT:


CLS = Classes/
OBJ= $(CLS)ImageNG.o  
COMP= g++ -I $(CLS) -D DEBUG

all:	Test1

Test1:	Test1.cpp $(OBJ) 
		$(COMP) Test1.cpp  -o Test1 $(OBJ)
		echo --- Creation de Test1 ---

$(CLS)ImageNG.o:	$(CLS)ImageNG.cpp $(CLS)ImageNG.h 
		$(COMP) $(CLS)ImageNG.cpp -c -o $(CLS)ImageNG.o
		echo --- Creation de ImageNG.o ---


clean:
	rm -f $(CLS)*.o core
	echo --- supp objet ---

clobber:	clean
	rm -f  Test1
	echo --- supp des executables ---		