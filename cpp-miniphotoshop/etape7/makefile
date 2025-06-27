#commentaire

.SILENT:

CLS = Classes/
OBJ = $(CLS)ImageNG.o  $(CLS)Dimension.o $(CLS)MyQT.o	$(CLS)ImageRGB.o  $(CLS)ImageB.o 	$(CLS)Image.o	$(CLS)Couleur.o	$(CLS)Exception.o  $(CLS)RGBException.o	$(CLS)XYException.o $(CLS)ArrayList.o $(CLS)Iterateur.o
COMP = g++ -I $(CLS) -D DEBUG

all:  Test7

 Test7:  Test7.cpp $(OBJ)
	$(COMP)  Test7.cpp -o  Test7 $(OBJ) -lSDL -lpthread -Wl,-O1 -pipe -O2 -std=gnu++11 -Wall -W -D_REENTRANT -fPIC -DQT_DEPRECATED_WARNINGS -DQT_NO_DEBUG -DQT_WIDGETS_LIB -DQT_GUI_LIB -DQT_CORE_LIB -I. -isystem /usr/include/qt5 -isystem /usr/include/qt5/QtWidgets -isystem /usr/include/qt5/QtGui -isystem /usr/include/qt5/QtCore -I. -I. -L/usr/lib64/qt5 -lQt5Widgets -lQt5Gui -lQt5Core -lGL
	echo --- Creation de  Test7 ---

$(CLS)ImageNG.o: $(CLS)ImageNG.cpp $(CLS)ImageNG.h
	$(COMP) $(CLS)ImageNG.cpp -c -o $(CLS)ImageNG.o
	echo --- Creation de ImageNG.o ---

$(CLS)Dimension.o: $(CLS)Dimension.cpp $(CLS)Dimension.h
	$(COMP) $(CLS)Dimension.cpp -c -o $(CLS)Dimension.o
	echo --- Creation de Dimension.o ---

$(CLS)MyQT.o: $(CLS)MyQT.cpp $(CLS)MyQT.h
	$(COMP) -c $(CLS)MyQT.cpp -o $(CLS)MyQT.o -pipe -O2 -std=gnu++11 -Wall -W -D_REENTRANT -fPIC -DQT_DEPRECATED_WARNINGS -DQT_NO_DEBUG -DQT_WIDGETS_LIB -DQT_GUI_LIB -DQT_CORE_LIB -I. -isystem /usr/include/qt5 -isystem /usr/include/qt5/QtWidgets -isystem /usr/include/qt5/QtGui -isystem /usr/include/qt5/QtCore -I. -I/usr/lib64/qt5/mkspecs/linux-g++
	echo --- Creation de MyQT.o ---

$(CLS)ImageRGB.o: $(CLS)ImageRGB.cpp $(CLS)ImageRGB.h
	$(COMP) $(CLS)ImageRGB.cpp -c -o $(CLS)ImageRGB.o
	echo --- Creation de ImageRGB.o ---

$(CLS)ImageB.o: $(CLS)ImageB.cpp $(CLS)ImageB.h
	$(COMP) $(CLS)ImageB.cpp -c -o $(CLS)ImageB.o
	echo --- Creation de ImageB.o ---

$(CLS)Image.o: $(CLS)Image.cpp $(CLS)Image.h
	$(COMP) $(CLS)Image.cpp -c -o $(CLS)Image.o
	echo --- Creation de Image.o ---

$(CLS)Couleur.o: $(CLS)Couleur.cpp $(CLS)Couleur.h
	$(COMP) $(CLS)Couleur.cpp -c -o $(CLS)Couleur.o
	echo --- Creation de Couleur.o ---

$(CLS)Exception.o: $(CLS)Exception.cpp $(CLS)Exception.h
	$(COMP) $(CLS)Exception.cpp -c -o $(CLS)Exception.o
	echo --- Creation de Exception.o ---

$(CLS)RGBException.o: $(CLS)RGBException.cpp $(CLS)RGBException.h
	$(COMP) $(CLS)RGBException.cpp -c -o $(CLS)RGBException.o
	echo --- Creation de RGBException.o ---

$(CLS)XYException.o: $(CLS)XYException.cpp $(CLS)XYException.h
	$(COMP) $(CLS)XYException.cpp -c -o $(CLS)XYException.o
	echo --- Creation de XYException.o ---

$(CLS)ArrayList.o: $(CLS)ArrayList.cpp $(CLS)ArrayList.h
	$(COMP) $(CLS)ArrayList.cpp -c -o $(CLS)ArrayList.o
	echo --- Creation de ArrayList.o ---

$(CLS)Iterateur.o: $(CLS)Iterateur.cpp $(CLS)Iterateur.h
	$(COMP) $(CLS)Iterateur.cpp -c -o $(CLS)Iterateur.o
	echo --- Creation de Iterateur.o ---

clean:
	rm -f $(CLS)*.o core
	echo --- supp objet ---

clobber: clean
	rm -f  Test7
	echo --- supp des executables ---
