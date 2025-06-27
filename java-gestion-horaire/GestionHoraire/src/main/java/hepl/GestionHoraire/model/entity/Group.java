package hepl.GestionHoraire.model.entity;
import java.io.Serializable;
public class Group extends Schedulable implements Identifiable, Serializable
{
    private static final long serialVersionUID = 1L;
    //---------------attributs---------------

    private String name;


    //---------------constructeur---------------

    // Constructeur defaut
    public Group() {
        super();
        name="";
    }

    // Constructeur init
    public Group(int id, String name)
    {
        super(id);
        this.name = name;
    }

    //---------------accesseurs---------------

    //get

    public String getName() {
        return name;
    }

    //set

    public void setName(String name) {
        this.name = name;
    }


    //---------------methode---------------

    @Override
    public int getId() {
        return super.getId();
    }

    @Override
    public String toString() {
        return "Group [id=" + getId() + ", name=" + name +  "]";
    }


    @Override
    public boolean equals(Object obj) {
        if (this == obj) return true;
        if (obj == null || getClass() != obj.getClass()) return false;

        Group other = (Group) obj;
        return getId() == other.getId() &&
                name.equals(other.name) ;

    }
}
