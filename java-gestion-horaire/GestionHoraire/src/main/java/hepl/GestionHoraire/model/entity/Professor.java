package hepl.GestionHoraire.model.entity;

import java.io.Serializable;
public class Professor extends Schedulable implements Identifiable, Serializable
{
    //? fait partie des attributs et a quoi ca sert?
    private static final long serialVersionUID = 1L;
    //---------------attributs---------------

    private String lastName;
    private String firstName;


    //---------------constructeur---------------

    // Constructeur defaut
    public Professor() {
        super();
        lastName="";
        firstName="";

    }

    // Constructeur init
    public Professor(int id, String lastName, String firstName)
    {
        super(id);
        this.lastName = lastName;
        this.firstName = firstName;
    }


    //---------------accesseurs---------------

    //get

    public String getlastName() {
        return lastName;
    }

    public String getfirstName() {
        return firstName;
    }


    //set

    public void setlastName(String lastName) {
        this.lastName = lastName;
    }

    public void setfirstName(String firstName) {
        this.firstName = firstName;
    }


    //---------------methode---------------

    @Override
    public int getId() {
        return super.getId();
    }

    @Override
    public String toString() {
        return "Professor [id=" + getId() + ", lastName=" + lastName + ", firstName=" + firstName + "]";
    }

    @Override
    public boolean equals(Object obj) {
        if (this == obj) return true;
        if (obj == null || getClass() != obj.getClass()) return false;

        Professor other = (Professor) obj;
        return getId() == other.getId() &&
                lastName.equals(other.lastName) &&
                firstName.equals(other.firstName);
    }

}
