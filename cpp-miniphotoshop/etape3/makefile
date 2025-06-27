#commentaire

.SILENT:

CLS = Classes/
OBJ = $(CLS)ImageNG.o  $(CLS)Dimension.o $(CLS)MyQT.o
COMP = g++ -I $(CLS) -D DEBUG

all: Test3

Test3: Test3.cpp $(OBJ)
	$(COMP) Test3.cpp -o Test3 $(OBJ) -lSDL -lpthread -Wl,-O1 -pipe -O2 -std=gnu++11 -Wall -W -D_REENTRANT -fPIC -DQT_DEPRECATED_WARNINGS -DQT_NO_DEBUG -DQT_WIDGETS_LIB -DQT_GUI_LIB -DQT_CORE_LIB -I. -isystem /usr/include/qt5 -isystem /usr/include/qt5/QtWidgets -isystem /usr/include/qt5/QtGui -isystem /usr/include/qt5/QtCore -I. -I. -L/usr/lib64/qt5 -lQt5Widgets -lQt5Gui -lQt5Core -lGL
	echo --- Creation de Test3 ---

$(CLS)ImageNG.o: $(CLS)ImageNG.cpp $(CLS)ImageNG.h
	$(COMP) $(CLS)ImageNG.cpp -c -o $(CLS)ImageNG.o
	echo --- Creation de ImageNG.o ---

$(CLS)Dimension.o: $(CLS)Dimension.cpp $(CLS)Dimension.h
	$(COMP) $(CLS)Dimension.cpp -c -o $(CLS)Dimension.o
	echo --- Creation de Dimension.o ---

$(CLS)MyQT.o: $(CLS)MyQT.cpp $(CLS)MyQT.h
	$(COMP) -c $(CLS)MyQT.cpp -o $(CLS)MyQT.o -pipe -O2 -std=gnu++11 -Wall -W -D_REENTRANT -fPIC -DQT_DEPRECATED_WARNINGS -DQT_NO_DEBUG -DQT_WIDGETS_LIB -DQT_GUI_LIB -DQT_CORE_LIB -I. -isystem /usr/include/qt5 -isystem /usr/include/qt5/QtWidgets -isystem /usr/include/qt5/QtGui -isystem /usr/include/qt5/QtCore -I. -I/usr/lib64/qt5/mkspecs/linux-g++
	echo --- Creation de MyQT.o ---

clean:
	rm -f $(CLS)*.o core
	echo --- supp objet ---

clobber: clean
	rm -f Test3
	echo --- supp des executables ---
