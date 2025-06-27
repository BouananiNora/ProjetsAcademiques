package hepl.GestionHoraire.model.entity;
import java.io.Serializable;
public abstract class Schedulable  implements Identifiable, Serializable
{
    private static final long serialVersionUID = 1L;
    private int id;


    //---------------constructeur---------------

    // Constructeur defaut
    public Schedulable() {
        id=0;
    }

    // Constructeur init
    public Schedulable(int id) {
        this.id = id;
    }


    //---------------accesseurs---------------
    public int getId() {
        return id;
    }

    public void setId(int id) {
        this.id = id;
    }


    //---------------methode---------------

    //permet d'obtenir une représentation textuelle de l'objet
    @Override
    public abstract String toString();



    //permet de comparer deux objets
    @Override
    public abstract boolean equals(Object obj);


}
