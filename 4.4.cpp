#include "sdt.h"
//������� ��� ������ 4.2
bool err = true;
void proverka(char* name)
{
    //�������� �� ������� *,",<,>,?,|
   if (strpbrk(name,"*<>?|\"")!= 0) //strpbrk - c�������� ������ name �� ����������� �������� �� ������ ������
    {
        cout <<"Unknown symbol (*<>?|\""<<endl;
        err=true;
    }
    if (strchr(name,':')!=0) //strchr - ���� ������ ��������� c (���������������� � char) � ������
    {
        if (strchr(name,':')!=&name[1])
        {
            cout<<"Wrong applying the symbol : "<<endl;
            err=true;
        }
        else
        {
            if(!isalpha(name[0]))
            {
                cout <<"Before : not a letter"<<endl;
                err=true;
            }
            if(name[2]!= '\\')
            {
                cout <<"After : not \\"<<endl;
                err=true;
            }
        }
    }
//�������� �� ����������
strrev(name); //strrev(char *s) - ������������ ������� � ������ � �������� �������
if ( strncmp(name, "txt.", 4 ) != 0 && strncmp( name, "TXT.", 4 ) != 0) //strncmp-���������� ������
{
    cout<<"Wrong format! (.txt or .TXT)"<<endl;
    err=true;
}
strrev(name);
}

int main()
{
    char file_name[20];
    while (err)
    {
    err=false;
    cout <<"Enter a file name with text (.txt):  ";
    cin >>file_name;
    proverka(file_name);
    }
    //����� 4.3: ��������� ���������� �����
    FILE * file = fopen(file_name, "a+"); //������ � �����
    fseek(file,0,SEEK_END);  //��������� � ����� �����
    int size_ = ftell(file);  //������ � ������
    fseek(file,0,SEEK_SET);
    char *mass = new char[ size_ +1 ];//
    memset(mass, 0, size_ +1); //��������� (size_+1) ������ ����� ������ ��������� ��������
    unsigned long result = fread(mass, sizeof(char), size_, file); //������� fread() ��������� size_ �������� � ������ ������ �� sizeof(char) �������� � ����� � �� ������ file � �������� �� � ���������� ������, ��������� � mass.
    if (ferror(file)) //�������� �� �������� ������
    {
        cout<<"File error\n";
        exit (1);
    }
    cout <<"\nThe contents of the file:"<<endl;
    puts(mass);
    //����� 4.4: ������ ������� ������ � ������
    cout <<"\nEnter a search string:  ";
    char str[20];
    cin >>str;

    //����� 4.5: ����� ��������� ������ (���������� ����������� �������)
    char *cp = (char *) mass;
    char *s1, *s2;
    while(*cp)
    {
        s1 = cp;
        s2 = (char *) str;
        while ( *s1 && *s2 && !(*s1-*s2) )
            s1++, s2++;
        if (!*s2)
            cout<<"Position of the string: "<<(cp-mass+1)<<endl;
        cp++;
    }
    //����� 4.6: ������� ���� �� �����������, �������� �� � char**
    int * pred=new int [20];
    int n=0;
    pred[0]=-1;
for(int i=0; i<size_; ++i)
            if(mass[i] == '.' || mass[i] == '?' || mass[i] == '!')
            {
                ++n;
                pred[n]=i;
            }
    cout <<"\nThe number of proposals: "<<n<<endl;
    char ** massPred=new char*[n];
        for(int i=0; i<n; ++i)
        {
            fseek(file, pred[i]+1,SEEK_SET);
            char *mass1 = new char[pred[i+1]]; //��������� ������
            fread(mass1,sizeof(char),pred[i+1],file);
            char *mass2 = new char[pred[i+1]];
            massPred[i]= strncpy(mass2, mass1, (pred[i+1]-pred[i])*sizeof(char));
            delete [] mass1; //������������ ���������� ������
        }
        fclose (file);
        cout<<endl;
        for(int i=0; i<n; ++i)
           cout<<"("<<strlen(massPred[i])<<") : "<<massPred[i]<<endl;;
    //����� 4.7: ����������� ����������� �� �����������
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (strlen(massPred[j]) > strlen(massPred[j+1]))
                swap(massPred[j],massPred[j+1]);
        }
    }
    cout<<"\nSorting proposal:\n";
    for(int i=0; i<n; ++i)
           cout<<strlen(massPred[i])<<") : "<<massPred[i]<<endl;

    //����� 4.8: �������� ����������� � ����� ����
    char file2_name[20];
    err=true;
    while (err)
    {
        err=false;
        cout << "\nEnter a new file name for the record (.txt)\n";
        cin >> file2_name;
        proverka(file2_name);
        cout <<endl;
    }
    FILE * file2 = fopen(file2_name, "a+");
    fseek(file2,0,SEEK_SET);  //��������� � ������ �����
    for(int i=0; i<n; ++i)
        fputs(massPred[i], file2);
        fclose (file2);

    //����� 4.9: ���������� ��� ���������� ����� ������
    for(int i=0; i<n; ++i)
    {
       delete[] massPred;
    }
    delete [] mass, pred, cp, massPred;
    delete s1, s2;
}

