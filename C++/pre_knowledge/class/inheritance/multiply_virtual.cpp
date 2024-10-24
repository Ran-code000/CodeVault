# include <iostream>
# include <string>

class Person
{
public:
    explicit Person(std::string theName);

    virtual void introduce() const;

protected:
    std::string name;
};

class Teacher : virtual public Person
{
public:
    Teacher(std::string theName,std::string teachingClass);

    void teach();
    virtual void introduce() const override;

protected:
    std::string teachingClass;
};

class Student : virtual public Person
{
public:
    Student(std::string theName,std::string attendingClass);

    void attendclass();
    virtual void introduce() const override;

protected:
    std::string attendingClass;
};

class TeachingStudent : public Student ,public Teacher
{
public:
    TeachingStudent(std::string theName,std::string teachingClass,std::string attendingClass);

    void introduce() const override;
};

Person::Person(std::string theName)
{
    name = theName;
}

void Person::introduce() const 
{
    std::cout << "Hello everyone,I'm " << name << "\n";
}

Teacher::Teacher(std::string theName,std::string teachingClass) : Person(theName)
{
    this -> teachingClass = teachingClass;
}

void Teacher::teach()
{
    std::cout << name << " teach " << teachingClass << "\n";
}

void Teacher::introduce() const
{
    std::cout << name << "teach " << teachingClass << "class" << "\n";
}

Student::Student(std::string theName,std::string attendingClass) : Person(theName)
{
    this ->attendingClass = attendingClass;
}

void Student::introduce() const
{
    std::cout << name << " attending" << attendingClass << "\n";
}

void Student::attendclass()
{
    std::cout << name << " join the " << attendingClass << " class" << "\n";
}

TeachingStudent::TeachingStudent(std::string theName,std::string teachingClass ,std::string attendingClass) :
 Teacher(theName,teachingClass),Student(theName,attendingClass),Person(theName)
{

}

void TeachingStudent::introduce() const
{
    std::cout << name << " teaching " << teachingClass << " and learning " << attendingClass <<"\n";
}

int main()
{
    Teacher teacher("Sandy","maths");
    Student student("Lili","maths");
    TeachingStudent teachingstudent("Mark","English","History");

    teacher.introduce();
    teacher.teach();
    student.introduce();
    student.attendclass();
    teachingstudent.introduce();
    teachingstudent.teach();
    teachingstudent.attendclass();


    return 0;
}