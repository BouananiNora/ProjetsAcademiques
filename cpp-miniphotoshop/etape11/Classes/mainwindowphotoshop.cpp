#include "mainwindowphotoshop.h"
#include "ui_mainwindowphotoshop.h"

#include <QMessageBox>
#include <QInputDialog>
#include <QFileDialog>
#include <QScreen>
#include <QRect>
#include <QPixmap>
#include <QColorDialog>

#include <QApplication>
#include <QCloseEvent>

#include "ImageNG.h"
#include "ImageRGB.h"
#include "ImageB.h"
#include "PhotoShop.h"
#include "Iterateur.h"
#include "Traitements.h"
#include "Exception.h"
#include "XYException.h"
#include "RGBException.h"
using namespace std;

MainWindowPhotoShop::MainWindowPhotoShop(QWidget *parent) : QMainWindow(parent),ui(new Ui::MainWindowPhotoShop)
{
    ui->setupUi(this);
    setTitre("Mini-PhotoShop  en C++");

    // Centrage de la fenetre
    QScreen *screen = QGuiApplication::primaryScreen();
    QRect screenGeometry = screen->availableGeometry();
    int x = (screenGeometry.width() - width()) / 2;
    int y = (screenGeometry.height() - height()) / 2;
    move(x, y);
    setFixedSize(1021,845);

    // Configuration de la table des images
    ui->tableWidgetImages->setColumnCount(4);
    ui->tableWidgetImages->setRowCount(0);
    QStringList labelsTableOptions;
    labelsTableOptions << "Id" << "Type" << "Dimension" << "Nom";
    ui->tableWidgetImages->setHorizontalHeaderLabels(labelsTableOptions);
    ui->tableWidgetImages->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableWidgetImages->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidgetImages->horizontalHeader()->setVisible(true);
    ui->tableWidgetImages->horizontalHeader()->setDefaultSectionSize(100);
    ui->tableWidgetImages->horizontalHeader()->setStretchLastSection(true);
    ui->tableWidgetImages->verticalHeader()->setVisible(false);
    ui->tableWidgetImages->horizontalHeader()->setStyleSheet("background-color: lightyellow");

    // Intialisation des scrollArea
    
    setImageNG("selection");
    setImageNG("operande1");
    setImageNG("operande2");
    setImageNG("resultat");
    

    // ComboBox des traitements disponibles
    ajouteTraitementDisponible("Eclaircir (+ val)");
    ajouteTraitementDisponible("Eclaircir (++)");
    ajouteTraitementDisponible("Assombrir (- val)");
    ajouteTraitementDisponible("Assombrir (--)");
    ajouteTraitementDisponible("Différence");
    ajouteTraitementDisponible("Comparaison (==)");
    ajouteTraitementDisponible("Comparaison (<)");
    ajouteTraitementDisponible("Comparaison (>)");
    ajouteTraitementDisponible("Seuillage");
    ajouteTraitementDisponible("Filtre moyenneur");
    ajouteTraitementDisponible("Filtre médian");
    ajouteTraitementDisponible("Erosion");
    ajouteTraitementDisponible("Dilatation");
    ajouteTraitementDisponible("Négatif");

    // Etape 14 (TO DO)
    // Restauration bibliothèque via fichier de sauvegarde
    

    PhotoShop& photoshop = PhotoShop::getInstance();
    photoshop.Load("sauvegarde.dat");
    maj();
    
}

MainWindowPhotoShop::~MainWindowPhotoShop()
{
    delete ui;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///// Méthodes de la fenêtre (ne pas modifier) ///////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MainWindowPhotoShop::setTitre(string titre)
{
  this->setWindowTitle(titre.c_str());
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MainWindowPhotoShop::setNomImage(string nom)
{
  ui->lineEditNom->setText(QString::fromStdString(nom));
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
string MainWindowPhotoShop::getNomImage() const
{
  return ui->lineEditNom->text().toStdString();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MainWindowPhotoShop::setParametresImageNG(int max,int min,int luminance,float contraste)
{
  if (max == -1)
  {
    ui->lineEditMax->setText("");
    ui->lineEditMin->setText("");
    ui->lineEditLuminance->setText("");
    ui->lineEditContraste->setText("");
    return;
  }
  char tmp[20];
  sprintf(tmp,"%d",max);
  ui->lineEditMax->setText(tmp);
  sprintf(tmp,"%d",min);
  ui->lineEditMin->setText(tmp);
  sprintf(tmp,"%d",luminance);
  ui->lineEditLuminance->setText(tmp);
  sprintf(tmp,"%f",contraste);
  ui->lineEditContraste->setText(tmp);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////

void MainWindowPhotoShop::setImageNG(string destination,const ImageNG* imageng)
{
    QPixmap * pixmap = NULL;
    if (imageng != NULL)
    {
      // Creation du QPixmap
      int largeur = imageng->getDimension().getLargeur();
      int hauteur = imageng->getDimension().getHauteur();
      QImage im1(largeur,hauteur,QImage::Format_RGB32);
      for(int x=0 ; x<largeur ; x++)
        for(int y=0 ; y<hauteur ; y++)
        {
          int valeur = imageng->getPixel(x,y);
          im1.setPixel(x,y,qRgb(valeur,valeur,valeur));
        }
     pixmap = new QPixmap(QPixmap::fromImage(im1));
    }

    // Mise en place du QPixmap
    QLabel* label = new QLabel();
    label->setAlignment(Qt::AlignCenter);
    if (pixmap) label->setPixmap(*pixmap);
    else label->setText("vide");
    if (destination == "selection") ui->scrollAreaSelection->setWidget(label);
    if (destination == "operande1") ui->scrollAreaOperande1->setWidget(label);
    if (destination == "operande2") ui->scrollAreaOperande2->setWidget(label);
    if (destination == "resultat") ui->scrollAreaResultat->setWidget(label);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////

void MainWindowPhotoShop::setImageRGB(string destination,const ImageRGB* imagergb)
{
    QPixmap * pixmap = NULL;
    if (imagergb != NULL)
    {
      // Creation du QPixmap
      int largeur = imagergb->getDimension().getLargeur();
      int hauteur = imagergb->getDimension().getHauteur();
      QImage im1(largeur,hauteur,QImage::Format_RGB32);
      for(int x=0 ; x<largeur ; x++)
        for(int y=0 ; y<hauteur ; y++)
        {
          Couleur valeur = imagergb->getPixel(x,y);
          im1.setPixel(x,y,qRgb(valeur.getRouge(),valeur.getVert(),valeur.getBleu()));
        }
     pixmap = new QPixmap(QPixmap::fromImage(im1));
    }

    // Mise en place du QPixmap
    QLabel* label = new QLabel();
    label->setAlignment(Qt::AlignCenter);
    if (pixmap) label->setPixmap(*pixmap);
    else label->setText("vide");
    if (destination == "selection") ui->scrollAreaSelection->setWidget(label);
    if (destination == "operande1") ui->scrollAreaOperande1->setWidget(label);
    if (destination == "operande2") ui->scrollAreaOperande2->setWidget(label);
    if (destination == "resultat") ui->scrollAreaResultat->setWidget(label);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////

void MainWindowPhotoShop::setImageB(string destination,const ImageB* imageb)
{
    QPixmap * pixmap = NULL;
    if (imageb != NULL)
    {
      // Creation du QPixmap
      int largeur = imageb->getDimension().getLargeur();
      int hauteur = imageb->getDimension().getHauteur();
      QImage im1(largeur,hauteur,QImage::Format_RGB32);
      for(int x=0 ; x<largeur ; x++)
        for(int y=0 ; y<hauteur ; y++)
        {
          bool valeur = imageb->getPixel(x,y);
          if (valeur) im1.setPixel(x,y,qRgb(ImageB::couleurTrue.getRouge(),ImageB::couleurTrue.getVert(),ImageB::couleurTrue.getBleu()));
          else im1.setPixel(x,y,qRgb(ImageB::couleurFalse.getRouge(),ImageB::couleurFalse.getVert(),ImageB::couleurFalse.getBleu()));
        }
     pixmap = new QPixmap(QPixmap::fromImage(im1));
    }

    // Mise en place du QPixmap
    QLabel* label = new QLabel();
    label->setAlignment(Qt::AlignCenter);
    if (pixmap) label->setPixmap(*pixmap);
    else label->setText("vide");
    if (destination == "selection") ui->scrollAreaSelection->setWidget(label);
    if (destination == "operande1") ui->scrollAreaOperande1->setWidget(label);
    if (destination == "operande2") ui->scrollAreaOperande2->setWidget(label);
    if (destination == "resultat") ui->scrollAreaResultat->setWidget(label);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MainWindowPhotoShop::setResultatBoolean(int val)
{
  if (val == 1) // vrai
  {
    ui->checkBoxResultat->setChecked(true);
    ui->checkBoxResultat->setText("VRAI");
    ui->checkBoxResultat->setStyleSheet("background-color: lightgreen;border: 1px solid black;");
    return;
  }
  if (val == 0) // faux
  {
    ui->checkBoxResultat->setChecked(false);
    ui->checkBoxResultat->setText("FAUX");
    ui->checkBoxResultat->setStyleSheet("background-color: red;border: 1px solid black;");
    return;
  }
  // ni vrai, ni faux
  ui->checkBoxResultat->setChecked(false);
  ui->checkBoxResultat->setText("Résultat");
  ui->checkBoxResultat->setStyleSheet("background-color: lightyellow;border: 1px solid black;");
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///// Fonctions utiles Table des Images (ne pas modifier) ////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MainWindowPhotoShop::ajouteTupleTableImages(int id,string type,string dimension,string nom)
{
    char Id[20];
    sprintf(Id,"%d",id);

    char Type[20];
    strcpy(Type,type.c_str());

    char Dimension[20];
    strcpy(Dimension,dimension.c_str());

    char Nom[80];
    strcpy(Nom,nom.c_str());

    // Ajout possible
    int nbLignes = ui->tableWidgetImages->rowCount();
    nbLignes++;
    ui->tableWidgetImages->setRowCount(nbLignes);
    ui->tableWidgetImages->setRowHeight(nbLignes-1,20);

    QTableWidgetItem *item = new QTableWidgetItem;
    item->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
    item->setTextAlignment(Qt::AlignCenter);
    item->setText(Id);
    ui->tableWidgetImages->setItem(nbLignes-1,0,item);

    item = new QTableWidgetItem;
    item->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
    item->setTextAlignment(Qt::AlignCenter);
    item->setText(Type);
    ui->tableWidgetImages->setItem(nbLignes-1,1,item);

    item = new QTableWidgetItem;
    item->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
    item->setTextAlignment(Qt::AlignCenter);
    item->setText(Dimension);
    ui->tableWidgetImages->setItem(nbLignes-1,2,item);

    item = new QTableWidgetItem;
    item->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
    item->setText(Nom);
    ui->tableWidgetImages->setItem(nbLignes-1,3,item);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MainWindowPhotoShop::videTableImages()
{
    ui->tableWidgetImages->setRowCount(0);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
int MainWindowPhotoShop::getIndiceImageSelectionnee()
{
    QModelIndexList liste = ui->tableWidgetImages->selectionModel()->selectedRows();
    if (liste.size() == 0) return -1;
    QModelIndex index = liste.at(0);
    int indice = index.row();
    return indice;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///// Combox des traitements disponibles (ne pas modifier) ///////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MainWindowPhotoShop::ajouteTraitementDisponible(string operation)
{
    ui->comboBoxTraitements->addItem(operation.c_str());
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MainWindowPhotoShop::videTraitementsDisponibles()
{
    ui->comboBoxTraitements->clear();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
string MainWindowPhotoShop::getTraitementSelectionne() const
{
    return ui->comboBoxTraitements->currentText().toStdString();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///// Fonctions permettant d'afficher des boites de dialogue (ne pas modifier) ///////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MainWindowPhotoShop::dialogueMessage(const char* titre,const char* message)
{
   QMessageBox::information(this,titre,message);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MainWindowPhotoShop::dialogueErreur(const char* titre,const char* message)
{
   QMessageBox::critical(this,titre,message);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
string MainWindowPhotoShop::dialogueDemandeTexte(const char* titre,const char* question)
{
    QString chaine = QInputDialog::getText(this,titre,question);
    return chaine.toStdString();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
int MainWindowPhotoShop::dialogueDemandeInt(const char* titre,const char* question)
{
    return QInputDialog::getInt(this,titre,question);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
float MainWindowPhotoShop::dialogueDemandeFloat(const char* titre,const char* question)
{
    return QInputDialog::getDouble(this,titre,question);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
string MainWindowPhotoShop::dialogueDemandeFichierOuvrir(const char* question)
{
  QString fileName = QFileDialog::getOpenFileName(this,question, "", "Tous les fichiers (*.*)");
  return fileName.toStdString();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
string MainWindowPhotoShop::dialogueDemandeFichierEnregistrer(const char* question)
{
  QString fileName = QFileDialog::getSaveFileName(this,question, "", "Tous les fichiers (*.*)");
  return fileName.toStdString();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MainWindowPhotoShop::dialogueDemandeCouleur(const char* message,int* pRouge,int* pVert,int* pBleu)
{
  QColor color = QColorDialog::getColor(Qt::red,this,message);
  *pRouge = color.red();
  *pVert = color.green();
  *pBleu = color.blue();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///// Clic sur la croix de la fenêtre ////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MainWindowPhotoShop::closeEvent(QCloseEvent *event)
{
  if (event == NULL) {} // pour éviter le warning à la compilation
  // Etape 14 (TO DO)

  if (QMessageBox::question(this, "Quitter", "Voulez-vous sauvegarder l'état de la bibliothèque avant de quitter?", QMessageBox::Yes | QMessageBox::No) == QMessageBox::Yes) 
  {        
      PhotoShop& photoshop = PhotoShop::getInstance();
      photoshop.Save("sauvegarde.dat");
  }
  event->accept();

  QApplication::exit();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///// Fonctions clics sur les items de menu //////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MainWindowPhotoShop::on_actionQuitter_triggered()
{
  // Etape 14 (TO DO)

  if (QMessageBox::question(this, "Quitter", "Voulez-vous sauvegarder l'état de la bibliothèque avant de quitter?", QMessageBox::Yes | QMessageBox::No) == QMessageBox::Yes) 
  {        
        PhotoShop& photoshop = PhotoShop::getInstance();
        photoshop.Save("sauvegarde.dat");
  }

  QApplication::exit();
}

// /////////////////////////////////////////////////////////////////////////////////////////////////////////////

void MainWindowPhotoShop::on_actionCharger_ImageNB_triggered()
{
   // Etape 11 (TO DO)
    string nomFichier = dialogueDemandeFichierOuvrir("Veuillez sélectionner le fichier de l'image NG à charger");

    ImageNG* pImage = new ImageNG(nomFichier);
    pImage->importFromFile(nomFichier);
    pImage->setNom(nomFichier);

    PhotoShop& photoshop = PhotoShop::getInstance();
    photoshop.ajouteImage(pImage);

    maj();

}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
 void MainWindowPhotoShop::on_actionCharger_ImageRGB_triggered()
 {
  // Etape 11 (TO DO)

  string nomFichier = dialogueDemandeFichierOuvrir("Veuillez sélectionner le fichier de l'image RGB à charger");

    ImageRGB* pImage = new ImageRGB(nomFichier);
    pImage->importFromFile(nomFichier);
     pImage->setNom(nomFichier);

    PhotoShop& photoshop = PhotoShop::getInstance();
    photoshop.ajouteImage(pImage);

    maj();
 }

// /////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MainWindowPhotoShop::on_actionEnregistrer_ImageNB_triggered()
{
  // Etape 11 (TO DO)
    int indice = getIndiceImageSelectionnee();
    
    if (indice == -1) 
    {
        dialogueErreur("(enreg ImageNG)Erreur", "Aucune image sélectionnée.");
        return;
    }

    PhotoShop& photoshop = PhotoShop::getInstance();
    Image* image = photoshop.getImageParIndice(indice);

    
    
    if (!image) 
    {
        dialogueErreur("Erreur", "Image invalide.");
        return;
    }
    if (!dynamic_cast<ImageNG*>(image)) {
        dialogueErreur("Erreur", "L'image sélectionnée n'est pas de type ImageNG.");
        return;
    }

    string nomFichier = dialogueDemandeFichierEnregistrer("Veuillez entrer le nom de l'image.");
    string formatFichier = dialogueDemandeTexte("Choisir le format", "Veuillez entrer le format du fichier (JPG, BMP, PNG).");

    

    if (formatFichier != "JPG" && formatFichier != "BMP" && formatFichier != "PNG") {
        dialogueErreur("Erreur", "Format de fichier non valide. Les formats acceptés sont JPG, BMP ou PNG.");
        return;
    }

    // // Ajout extension au nom du fichier
    // string extension;
    // if (formatFichier == "JPG") 
    // {
    //     extension = ".jpg";
    // } 
    // else if (formatFichier == "BMP") 
    // {
    //     extension = ".bmp";
    // } 
    // else if (formatFichier == "PNG") 
    // {
    //     extension = ".png";
    // }

    // nomFichier = nomFichier+ extension;

    image->exportToFile(nomFichier, formatFichier);
}
  
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MainWindowPhotoShop::on_actionEnregistrer_ImageRGB_triggered()
{
  // Etape 11 (TO DO)

  int indice = getIndiceImageSelectionnee();
    
    if (indice == -1) 
    {
        dialogueErreur("(enreg ImageRGB)Erreur", "Aucune image sélectionnée.");
        return;
    }

    PhotoShop& photoshop = PhotoShop::getInstance();
    Image* image = photoshop.getImageParIndice(indice);

    if (!image) 
    {
        dialogueErreur("Erreur", "Image invalide.");
        return;
    }
    if (!dynamic_cast<ImageRGB*>(image)) {
        dialogueErreur("Erreur", "L'image sélectionnée n'est pas de type ImageRGB.");
        return;
    }

    string nomFichier = dialogueDemandeFichierEnregistrer("Veuillez sélectionner le fichier pour enregistrer l'image.");
    string formatFichier = dialogueDemandeTexte("Choisir le format", "Veuillez entrer le format du fichier (JPG, BMP, PNG).");

    

    if (formatFichier != "JPG" && formatFichier != "BMP" && formatFichier != "PNG") {
        dialogueErreur("Erreur", "Format de fichier non valide. Les formats acceptés sont JPG, BMP ou PNG.");
        return;
    }

    // // Ajout extension au nom du fichier
    // string extension;
    // if (formatFichier == "JPG") 
    // {
    //     extension = ".jpg";
    // } 
    // else if (formatFichier == "BMP") 
    // {
    //     extension = ".bmp";
    // } 
    // else if (formatFichier == "PNG") 
    // {
    //     extension = ".png";
    // }

    // nomFichier = nomFichier+ extension;

    image->exportToFile(nomFichier, formatFichier);

}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MainWindowPhotoShop::on_actionEnregistrer_ImageB_triggered()
{
  // Etape 11 (TO DO)

  int indice = getIndiceImageSelectionnee();
    
    if (indice == -1) 
    {
        dialogueErreur("(enreg ImageB)Erreur", "Aucune image sélectionnée.");
        return;
    }

    PhotoShop& photoshop = PhotoShop::getInstance();
    Image* image = photoshop.getImageParIndice(indice);

    
    
    if (!image) 
    {
        dialogueErreur("Erreur", "Image invalide.");
        return;
    }
    if (!dynamic_cast<ImageB*>(image)) {
        dialogueErreur("Erreur", "L'image sélectionnée n'est pas de type ImageB.");
        return;
    }

    string nomFichier = dialogueDemandeFichierEnregistrer("Veuillez sélectionner le fichier pour enregistrer l'image.");
    string formatFichier = dialogueDemandeTexte("Choisir le format", "Veuillez entrer le format du fichier (JPG, BMP, PNG).");

    

    if (formatFichier != "JPG" && formatFichier != "BMP" && formatFichier != "PNG") {
        dialogueErreur("Erreur", "Format de fichier non valide. Les formats acceptés sont JPG, BMP ou PNG.");
        return;
    }

    // // Ajout extension au nom du fichier
    // string extension;
    // if (formatFichier == "JPG") 
    // {
    //     extension = ".jpg";
    // } 
    // else if (formatFichier == "BMP") 
    // {
    //     extension = ".bmp";
    // } 
    // else if (formatFichier == "PNG") 
    // {
    //     extension = ".png";
    // }

    // nomFichier = nomFichier+ extension;

    image->exportToFile(nomFichier, formatFichier);

}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MainWindowPhotoShop::on_actionImage_selectionn_e_triggered()
{
  // Etape 11 (TO DO)

  int id = getIndiceImageSelectionnee();

  if (id == -1)
  {
    dialogueErreur("(SUPP SELECT) Erreur", "Aucune image sélectionnée.");
    return;
  }
  else
  {
    PhotoShop& photoshop = PhotoShop::getInstance();
    photoshop.supprimeImageParIndice(id);
    maj();
  }



}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MainWindowPhotoShop::on_actionImage_par_id_triggered()
{
  // Etape 11 (TO DO)

    int id = dialogueDemandeInt("Supprimer une image", "Veuillez entrer l'ID de l'image à supprimer.");

    PhotoShop& photoshop = PhotoShop::getInstance();
    Image* imageToDelete = photoshop.getImageParId(id);

    if (imageToDelete)
    {
        photoshop.supprimeImageParId(id);
    }
    else
    {
        dialogueErreur("(supp id)Erreur", "Aucune image trouvée avec cet ID.");
        return;
    }
  
    maj();

    
         
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MainWindowPhotoShop::on_actionCouleur_TRUE_pour_ImageB_triggered()
{
  // Etape 12 (TO DO)

  int red,green,blue;

  dialogueDemandeCouleur("Entrez une couleur pour TRUE",&red,&green,&blue);

  ImageB::couleurTrue.setRouge(red);
  ImageB::couleurTrue.setVert(green);
  ImageB::couleurTrue.setBleu(blue);

}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MainWindowPhotoShop::on_actionCouleur_FALSE_pour_imageB_triggered()
{
  // Etape 12 (TO DO)

  int red,green,blue;

  dialogueDemandeCouleur("Entrez une couleur pour FALSE",&red,&green,&blue);

  ImageB::couleurFalse.setRouge(red);
  ImageB::couleurFalse.setVert(green);
  ImageB::couleurFalse.setBleu(blue);

}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MainWindowPhotoShop::on_actionImporterCSV_triggered()
{
  // Etape 13 (TO DO)

  string nomFichierCSV = dialogueDemandeFichierOuvrir("Entrez le nom du fichier CSV");

  if (nomFichierCSV.empty()) 
  {
        cerr << "Aucun fichier spécifié. Opération annulée." << endl;
        return;
  }
  PhotoShop& photoshop = PhotoShop::getInstance();
  int nombreImagesImportees = photoshop.importeImages(nomFichierCSV);

  maj();

  char phrase[50];
  sprintf(phrase, "Nombre d'images importées :%d \n", nombreImagesImportees);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MainWindowPhotoShop::on_actionReset_triggered()
{
  // Etape 14 (TO DO)
  PhotoShop& photoshop = PhotoShop::getInstance();
  photoshop.reset();
  maj();

}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///// Fonctions selection sur la table des images ////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MainWindowPhotoShop::on_tableWidgetImages_itemSelectionChanged()
{
  // Etape 11 (TO DO)


    int indice = getIndiceImageSelectionnee();

    if (indice == -1) 
    {
        dialogueErreur("(select)Erreur", "Aucune image sélectionnée.");
        return;
    }

    PhotoShop& photoshop = PhotoShop::getInstance();
    Image* image = photoshop.getImageParIndice(indice);

    if (!image)
    {
        dialogueErreur("Erreur", "L'image sélectionnée est invalide.");
        return;
    }

    string nomImage = image->getNom();
    setNomImage(nomImage);

    if (dynamic_cast<ImageNG*>(image))
    {
        ImageNG* imageNG = static_cast<ImageNG*>(image);
        int max = imageNG->getMaximum();
        int min = imageNG->getMinimum();
        int luminance = imageNG->getLuminance();
        float contraste = imageNG->getContraste();
        
        setParametresImageNG(max, min, luminance, contraste);
    }
    // else
    // {
    //     setParametresImageNG();
    // }

    string destination = "selection";
    
    if (dynamic_cast<ImageRGB*>(image))
    {
        setImageRGB(destination, static_cast<ImageRGB*>(image));
    }
    else 
    {
      if (dynamic_cast<ImageB*>(image))
      {
          setImageB(destination, static_cast<ImageB*>(image));
      }
      else
      {
          setImageNG(destination, static_cast<ImageNG*>(image));
      }
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///// Fonctions clics sur les boutons ////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MainWindowPhotoShop::on_pushButtonModifierNom_clicked()
{
  // Etape 11 (TO DO)
  string nouveauNom = getNomImage();

  int indice = getIndiceImageSelectionnee();
  
  if (indice == -1)
  {
      dialogueErreur("(modif nom)Erreur", "Aucune image sélectionnée.");
      return;
  }

  PhotoShop& photoshop = PhotoShop::getInstance();
  Image* image = photoshop.getImageParIndice(indice);

  if (!image) 
  {
      dialogueErreur("Erreur", "Image invalide.");
      return;
  }

  image->setNom(nouveauNom);
  
  maj();
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MainWindowPhotoShop::on_pushButtonOperande1_clicked()
{
    // Etape 12 (TO DO)
    
    int indice = getIndiceImageSelectionnee();
    
    if (indice == -1) 
    {
        dialogueErreur("(btn op1)Erreur", "Aucune image sélectionnée.");
        return;
    }

    PhotoShop& photoshop = PhotoShop::getInstance();
    Image* image = photoshop.getImageParIndice(indice);
    photoshop.operande1 = image;

    if(dynamic_cast<ImageNG*>(image))
    {
      setImageNG("operande1",(ImageNG*)image);
    }
    else
    {
      if(dynamic_cast<ImageRGB*>(image))
      {
        setImageRGB("operande1",(ImageRGB*)image);
      }
      else
      {
        setImageB("operande1",(ImageB*)image);
      }
    }
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MainWindowPhotoShop::on_pushButtonSupprimeOperande1_clicked()
{
    // Etape 12 (TO DO)

    PhotoShop::operande1 = NULL;
    setImageNG("operande1", NULL);
    

}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MainWindowPhotoShop::on_pushButtonOperande2_clicked()
{
    // Etape 12 (TO DO)

    int indice = getIndiceImageSelectionnee();
    
    if (indice == -1) 
    {
        dialogueErreur("(btn op2)Erreur", "Aucune image sélectionnée.");
        return;
    }

    PhotoShop& photoshop = PhotoShop::getInstance();
    Image* image = photoshop.getImageParIndice(indice);
    photoshop.operande2 = image;

    if(dynamic_cast<ImageNG*>(image))
    {
      setImageNG("operande2",(ImageNG*)image);
    }
    else
    {
      if(dynamic_cast<ImageRGB*>(image))
      {
        setImageRGB("operande2",(ImageRGB*)image);
      }
      else
      {
        setImageB("operande2",(ImageB*)image);
      }
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MainWindowPhotoShop::on_pushButtonSupprimerOperande2_clicked()
{
    // Etape 12 (TO DO)

    PhotoShop::operande2 = NULL;
    setImageNG("operande2", NULL);

}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MainWindowPhotoShop::on_pushButtonResultat_clicked()
{
    // Etape 12 (TO DO)

    if(PhotoShop::resultat!=NULL)
    {
      PhotoShop& photoshop = PhotoShop::getInstance();
      photoshop.ajouteImage(PhotoShop::resultat);

      maj();

      PhotoShop::resultat=NULL;

      setImageNG("resultat",NULL);
    }

}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MainWindowPhotoShop::on_pushButtonSupprimerResultat_clicked()
{
    // Etape 12 (TO DO)

    if(PhotoShop::resultat!=NULL)
    {
      delete PhotoShop::resultat;

      PhotoShop::resultat=NULL;

      setImageNG("resultat",NULL);

      setResultatBoolean(-1);
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////


void MainWindowPhotoShop::on_pushButtonTraitement_clicked() 
{
  
    string traitement = getTraitementSelectionne();
    int valeur;
    
    if (PhotoShop::operande1 == NULL) 
    {
        dialogueErreur("Erreur", "L'opérande 1 est manquante.");
        return;
    }

    if ((traitement == "Différence" || traitement == "Comparaison (==)" || traitement == "Comparaison (<)" || traitement == "Comparaison (>)") && PhotoShop::operande2 == NULL) 
    {
        dialogueErreur("Erreur", "L'opérande 2 est manquante pour ce traitement.");
        return;
    }

    try 
    {
        
        if (traitement == "Eclaircir (+ val)") 
        {
            valeur = dialogueDemandeInt("Eclaircir", "Entrez la valeur d'éclaircissement :");
            PhotoShop::resultat = new ImageNG;
            *(ImageNG*)PhotoShop::resultat = *((ImageNG*)(PhotoShop::operande1))+ valeur;
            setImageNG("resultat",(ImageNG*)PhotoShop::resultat);
        }

        else if(traitement=="Eclaircir (++)")
        {
          PhotoShop::resultat=new ImageNG; 

          *(ImageNG*)PhotoShop::resultat = ++(*(ImageNG*)PhotoShop::operande1);
          setImageNG("resultat",(ImageNG*)PhotoShop::resultat);
        }
        else if(traitement=="Assombrir (- val)")
        {
          PhotoShop::resultat=new ImageNG; 

          valeur=dialogueDemandeInt("Assombrissement","Entrez la valeur d'Assombrissement");

          *(ImageNG*)PhotoShop::resultat = *((ImageNG*)(PhotoShop::operande1))-valeur;
          setImageNG("resultat",(ImageNG*)PhotoShop::resultat);
        }
        else if(traitement=="Assombrir (--)")
        {
          PhotoShop::resultat=new ImageNG; 

          *(ImageNG*)PhotoShop::resultat = --(*(ImageNG*)PhotoShop::operande1);
          setImageNG("resultat",(ImageNG*)PhotoShop::resultat);
        }
        else if (traitement=="Différence")
        {
          PhotoShop::resultat=new ImageNG; 

          if(PhotoShop::operande2!=NULL && dynamic_cast<ImageNG*>(PhotoShop::operande2))
          {
            *(ImageNG*)PhotoShop::resultat = (*(ImageNG*)PhotoShop::operande1)-(*(ImageNG*)PhotoShop::operande2);
            setImageNG("resultat",(ImageNG*)PhotoShop::resultat);
          }
          else
          {
            dialogueErreur("Erreur de traitement","Veuillez insérer une image NG dans l'opérande2");
          }
        }
        else if (traitement=="Comparaison (==)")
        {
          if(PhotoShop::operande2!=NULL && dynamic_cast<ImageNG*>(PhotoShop::operande2))
          {
            setResultatBoolean((*(ImageNG*)PhotoShop::operande1) == (*(ImageNG*)PhotoShop::operande2));
          }
          else
          {
            dialogueErreur("Erreur de traitement","Veuillez insérer une image NG dans l'opérande2");
          }
        }
        else if (traitement=="Comparaison (<)")
        {
          if(PhotoShop::operande2!=NULL && dynamic_cast<ImageNG*>(PhotoShop::operande2))
          {
            setResultatBoolean((*(ImageNG*)PhotoShop::operande1) < (*(ImageNG*)PhotoShop::operande2));
          }
          else
          {
            dialogueErreur("Erreur de traitement","Veuillez insérer une image NG dans l'opérande2");
          }
        }
        else if (traitement=="Comparaison (>)")
        {
          if(PhotoShop::operande2!=NULL && dynamic_cast<ImageNG*>(PhotoShop::operande2))
          {
            setResultatBoolean((*(ImageNG*)PhotoShop::operande1) > (*(ImageNG*)PhotoShop::operande2));
          }
          else
          {
            dialogueErreur("Erreur de traitement","Veuillez insérer une image NG dans l'opérande2");
          }
        }
        else if (traitement=="Seuillage")
        {
          PhotoShop::resultat=new ImageB; 
          valeur=dialogueDemandeInt("Seuillage","Veuillez entrer une valeur pour le seuillage");
          *(ImageB*)PhotoShop::resultat = Traitements::Seuillage((*(ImageNG*)PhotoShop::operande1), valeur);
          setImageB("resultat",(ImageB*)PhotoShop::resultat);
        }
        else if (traitement=="Filtre moyenneur")
        {
          PhotoShop::resultat=new ImageNG; 
          valeur=dialogueDemandeInt("Filtre moyenneur","Veuillez entrer la taille pour le filtre moyenneur");
          *(ImageNG*)PhotoShop::resultat = Traitements::FiltreMoyenneur((*(ImageNG*)PhotoShop::operande1), valeur);
          setImageNG("resultat",(ImageNG*)PhotoShop::resultat);
        }
        else if (traitement=="Filtre médian")
        {
          PhotoShop::resultat=new ImageNG; 
          valeur=dialogueDemandeInt("Filtre médian","Veuillez entrer la taille pour le filtre médian");
          *(ImageNG*)PhotoShop::resultat = Traitements::FiltreMedian((*(ImageNG*)PhotoShop::operande1), valeur);
          setImageNG("resultat",(ImageNG*)PhotoShop::resultat);
        }
        else if (traitement=="Erosion")
        {
          PhotoShop::resultat=new ImageNG; 
          valeur=dialogueDemandeInt("Erosion","Veuillez entrer la taille pour l'érosion");
          *(ImageNG*)PhotoShop::resultat = Traitements::Erosion((*(ImageNG*)PhotoShop::operande1), valeur);
          setImageNG("resultat",(ImageNG*)PhotoShop::resultat);
        }
        else if (traitement=="Dilatation")
        {
          PhotoShop::resultat=new ImageNG; 
          valeur=dialogueDemandeInt("Dilatation","Veuillez entrer la taille pour la dilatation");
          *(ImageNG*)PhotoShop::resultat = Traitements::Dilatation((*(ImageNG*)PhotoShop::operande1), valeur);
          setImageNG("resultat",(ImageNG*)PhotoShop::resultat);
        }
        else if (traitement=="Négatif")
        {
          PhotoShop::resultat=new ImageNG;
          *(ImageNG*)PhotoShop::resultat = Traitements::Negatif((*(ImageNG*)PhotoShop::operande1));
          setImageNG("resultat",(ImageNG*)PhotoShop::resultat);
        }
        
        
    }
    
      catch(RGBException e)
      {
        dialogueErreur("Erreur de traitement",(e.getMsg() + " " + to_string(e.getVal())).c_str());
      }
      catch(XYException e)
      {
        dialogueErreur("Erreur de traitement",(e.getMsg() + " " + e.getCrd()).c_str());
      }
      catch(Exception e)
      {
        dialogueErreur("Erreur de traitement",(e.getMsg()).c_str());
      }
}


void MainWindowPhotoShop::maj()
{
   PhotoShop& photoshop = PhotoShop::getInstance();
  videTableImages(); 

    int nombreElements = 0;

    while (true) 
    {
        try 
        {
            Image* image = photoshop.getImageParIndice(nombreElements);
            if (!image) 
            {
              break; 
            
            }
            else
            {
              nombreElements++;
            }
        } 
        catch (...) 
        {
            break; 
        }
    }

    for (int i = 0; i < nombreElements; i++)
    {
        Image* image = photoshop.getImageParIndice(i); 

        int id = image->getId();

        string type;
        if (dynamic_cast<ImageRGB*>(image))
            type = "RGB";
        else if (dynamic_cast<ImageNG*>(image))
            type = "NG";
        else if (dynamic_cast<ImageB*>(image))
            type = "B"; 

        Dimension dim = image->getDimension();
        string dimension = to_string(dim.getLargeur()) + "x" + to_string(dim.getHauteur());
        string nom = image->getNom();
        
        ajouteTupleTableImages(id, type, dimension, nom);
        
    }
}
