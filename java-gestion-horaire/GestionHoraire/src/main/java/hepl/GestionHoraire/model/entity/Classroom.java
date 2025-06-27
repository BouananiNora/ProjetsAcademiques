package hepl.GestionHoraire.model.entity;

import java.io.Serializable;

public class Classroom extends Schedulable implements Identifiable, Serializable
{
    private static final long serialVersionUID = 1L;
    //---------------attributs---------------

    private String name;
    private int seatingCapacity;



    //---------------constructeur---------------

    // Constructeur defaut
    public Classroom() {
        super();
        name="";
        seatingCapacity = 0;

    }

    // Constructeur init
    public Classroom(int id, String name,int seatingCapacity)
    {
        super(id);
        this.name = name;
        this.seatingCapacity=seatingCapacity;
    }

    //---------------accesseurs---------------

    //get

    public String getName() {
        return name;
    }

    public int getSeatingCapacity() {
        return seatingCapacity;
    }

    //set

    public void setName(String name) {
        this.name = name;
    }

    public void setSeatingCapacity(int seatingCapacity) {
        this.seatingCapacity = seatingCapacity;
    }

    //---------------methode---------------

    @Override
    public int getId() {
        return super.getId();
    }

    @Override
    public String toString() {
        return "Classroom [id=" + getId() + ", name=" + name + ", seatingCapacity=" + seatingCapacity + "]";
    }


    @Override
    public boolean equals(Object obj) {
        if (this == obj) return true;
        if (obj == null || getClass() != obj.getClass()) return false;

        Classroom other = (Classroom) obj;
        return getId() == other.getId() &&
                name.equals(other.name) &&
                seatingCapacity == other.seatingCapacity;
    }

}
