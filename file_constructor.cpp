#include <iostream> 
#include <cstring> 
using namespace std;

class Student {
private:
    int* m_pID;
    string m_name;
public:
    Student(); //Constructor 1
    Student(int, string); //Constructor2
    ~Student(); //Destructor
    int GetID();
    string GetName();
    //int GetID() {
    //    return id; 
    //}
};
//Constructor 1 implementation
Student::Student() {

    m_pID = new int(0); //Heap allocation
    m_name = "Alice";
    cout << "Constructor 1: " << m_name << endl;
}
//Constructor 2 implementation
Student::Student(int id, string name) {

    m_pID = new int(id);
    m_name = name;
    cout << "Constructor 2: " << m_name << endl;
}
//Destructor implementation
Student::~Student() {
    cout << "Destructor: " << m_name << endl;
    delete m_pID; //Deallocate Heap
}
int Student::GetID() {
    return *m_pID; //Dereferencing
}
string Student::GetName() {
    return m_name;
}

int main() {
    cout << "==Place 1==" << endl;
    Student student1; //Stack
    Student student2(2000, "Jenny"); //Stack
    cout << "==Place 2==" << endl;
    Student* student3; //Stack
    cout << "==Place 3==" << endl;
    student3 = new Student(3000, "Tom"); //Heap alloc
    cout << "==Place 4==" << endl;
    delete student3; //Heal deallocation
    cout << "==Place 5==" << endl;
    /*
    Student* student1;
    cout << "==Place 1==" << endl;
    student1 = new Student(201911999, "John"); //Heap allocation (constructor 2 사용)
    cout << "==Place 2==" << endl;
    delete student1; //Heap deallocation
    cout << "==Place 3==" << endl;
    */
    /*
    Student* student1;
    cout << "==Place 1==" << endl;
    Student* student2;
    cout << "==Place 2==" << endl;
    student1 = new Student(201911999, "John"); //Heap allocation
    cout << "==Place 3==" << endl;
    student2 = new Student(); //Heap
    cout << "==Place 4==" << endl;
    Student student3; //Stack allocation
    cout << "==Place 5==" << endl;
    Student student4(12345, "Tom");
    cout << "==Place 6==" << endl;
    Student many_students[3]; //Array inside stack
    cout << "==Place 7==" << endl;
    Student* ptr_many_students2;
    cout << "==Place 8==" << endl;
    ptr_many_students2 = new Student[5]; //Array inside Heap
    cout << "==Place 9==" << endl;
    for (int i = 0; i < 5; i++) {
        cout << (ptr_many_students2 + i)->GetName() << endl;
        cout << (ptr_many_students2[i]).GetName() << endl;
    }
    cout << "==Place 10==" << endl;
    Student* ptr_manystudent3[10]; //Array of Student pointer
    cout << "==Place 11==" << endl;
    for (int i = 0; i < 10; i++) {
        string t_name = "Student";
        ptr_manystudent3[i] = new Student(2000 + i, t_name); //Heap allocation
    }
    cout << "==Place 12==" << endl;
    for (int i = 0; i < 10; i++) {
        cout << ptr_manystudent3[i]->GetID() << "\t" << ptr_manystudent3[i]->GetName() << endl;
    }
    cout << "==Place 13==" << endl;
    */
    //Student* student1;
    //student1 = new Student{ 2019, "John" };
    //cout << (*student1).GetID() << endl;
    //cout << student1->GetID() << endl;
    return 0;
}

/*int main()
{
    char str[20] = "Hello";
    char str2[] = "World";
    cout << strlen(str) << endl;
    cout << sizeof(str) << endl;
    cout << strlen(str2) << endl;
    cout << sizeof(str2) << endl;
    strncat_s(str, str2, 4);
    cout << str << endl;
    //if (strcmp(str, "HelloWorld") == 0)
    if (strcmp(str, "HelloWorl") == 0)
        cout << "OK" << endl;
    else
        cout << "Fail" << endl;

    char str01[] = "10";
    char str02[] = "20";
    //cout << str01 * str02 << endl; //error
    cout << atoi(str01) * atof(str02) << endl;


    return 0;
}
*/
