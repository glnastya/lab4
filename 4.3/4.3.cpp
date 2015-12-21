#include "sdt.h"
#include "print.h"

struct Student
{
    char Name[6];
    short Year;
    short MeanScore;
    short Gender: 1;
    short Course;
    Student* Starosta;
};
int main()
{
    //пункт 3.2 объ€вить и заполнить массив
    Student stud[3]=
    {
        {"Arina", 2013, 5, 0, 2, nullptr},
        {"Dima", 2013, 4, 1, 2, &stud[0]},
        {"Anton",2013, 3, 1, 2, &stud[0]}
    };
    //пункт 3.3
    //1)адрес и размер массива
    cout <<"Address massiva stud: " << &stud <<endl;
    cout <<"Razmer massiva stud: " << sizeof(stud) <<endl;
    cout <<"\nStud \t\t  Address stud \t\t Size"<<endl;
    //2)адреса и размеры элементов массива
    for (int i = 0; i < 3; ++i)
    {
        cout <<stud[i].Name<<":"<< i <<"\t\t"<<&stud[i]<<"\t\t"<<sizeof(stud[i]) <<endl;
    }
    //3) дл€ полей одного элемента массива:

    cout <<"\nField Name:";
    cout <<"\nAddress stud[1]: " <<&stud[1].Name;
    cout <<"\nOffset stud[1]: " <<offsetof(struct Student, Name);
    cout <<"\nSize stud[1]: " <<sizeof(stud[1].Name);
    cout <<"\nIn binary: ";
    print_in_binaryAll(&stud[1].Name, sizeof(stud[1].Name));
    cout <<"\nIn hex: ";
    print_in_hexAll(&stud[1].Name, sizeof(stud[1].Name));

    cout <<"\n\nField Year:";
    cout <<"\nAddress stud[1]: " <<&stud[1].Year;
    cout <<"\nOffset stud[1]: " <<offsetof(struct Student, Year);
    cout <<"\nSize stud[1]: " <<sizeof(stud[1].Year);
    cout <<"\nIn binary: ";
    print_in_binaryAll(&stud[1].Year, sizeof(stud[1].Year));
    cout <<"\nIn hex: ";
    print_in_hexAll(&stud[1].Year, sizeof(stud[1].Year));

    cout <<"\n\nField MeanScore:";
    cout <<"\nAddress stud[1]: " <<&stud[1].MeanScore;
    cout <<"\nOffset stud[1]: " <<offsetof(struct Student, MeanScore);
    cout <<"\nSize stud[1]: " <<sizeof(stud[1].MeanScore);
    cout <<"\nIn binary: ";
    print_in_binaryAll(&stud[1].MeanScore, sizeof(stud[1].MeanScore));
    cout <<"\nIn hex: ";
    print_in_hexAll(&stud[1].MeanScore, sizeof(stud[1].MeanScore));

    cout <<"\n\nField Course:";
    cout <<"\nAddress stud[1]: " <<&stud[1].Course;
    cout <<"\nOffset stud[1]: " <<offsetof(struct Student, Course);
    cout <<"\nSize stud[1]: " <<sizeof(stud[1].Course);
    cout <<"\nIn binary: ";
    print_in_binaryAll(&stud[1].Course, sizeof(stud[1].Course));
    cout <<"\nIn hex: ";;
    print_in_hexAll(&stud[1].Course, sizeof(stud[1].Course));

    cout <<"\n\nField Starosta:";
    cout <<"\nAddress stud[1]: " <<stud[1].Starosta;
    cout <<"\nOffset stud[1]: " <<offsetof(struct Student, Starosta);
    cout <<"\nSize stud[1]: " <<sizeof(stud[1].Starosta);
    cout <<"\nIn binary: ";
    print_in_binaryAll(stud[1].Starosta, sizeof(stud[1].Starosta));
    cout <<"\nIn hex: ";
    print_in_hexAll(stud[1].Starosta, sizeof(stud[1].Starosta));

    //4) элементы массива в шестнадцатеричном виде
    cout <<endl;
    cout <<"\nName\t\t  Year  MeanS Gend  Course  Starosta\n";
    for(int i=0; i<3; ++i)
    {
        print_in_hexAll(&stud[i], sizeof(stud[i]));
        cout <<endl;
    }
}
