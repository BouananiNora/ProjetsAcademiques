package hepl.GestionHoraire.model.entity;

import java.util.HashSet;
import java.util.Set;
import java.io.Serializable;
public class Course extends Event implements Identifiable, Serializable
{
    private static final long serialVersionUID = 1L;
    //---------------attributs---------------

    private int professorId;
    private int classroomId;
    private Set<Integer> groupsIds;

    //---------------constructeur---------------

    // Constructeur defaut
    public Course() {
        super();
        professorId = 0;
        classroomId = 0;
        groupsIds=new HashSet<>();
    }

    // Constructeur init
    public Course(int code, String title, Timing timing, int professorId, int classroomId,Set<Integer> groupsIds)
    {
        super(code, title);
        setTiming(timing);
        this.professorId = professorId;
        this.classroomId = classroomId;
        this.groupsIds = groupsIds;
    }


    //---------------accesseurs---------------

    //get
    public int getProfessorId() {
        return professorId;
    }

    public int getClassroomId() {
        return classroomId;
    }


    //set
    public void setProfessorId(int id) {
        professorId = id;
    }

    public void setClassroomId(int id) {
        classroomId = id;
    }


    //------------------------------

    public void addGroupId(int id) {
        groupsIds.add(id);
    }


    public Set<Integer> getGroupsIds()
    {
        return groupsIds;
    }

    public void setGroupsIds(Set<Integer> groupsIds) {
        this.groupsIds = groupsIds;
    }


    //---------------methode---------------

    @Override
    public boolean equals(Object obj)
    {
        if (this == obj) return true;
        if (obj == null || getClass() != obj.getClass()) return false;
        if (!super.equals(obj)) return false;

        Course other = (Course) obj;
        return getTiming().equals(other.getTiming());
    }


    @Override
    public String toString() {
        return "Course [code=" + getCode() + ", title=" + getTitle() + ", timing=" + getTiming() + ", professorId=" + professorId + ", classroomId=" + classroomId + ", groupsIds=" + groupsIds +"]";
    }

}