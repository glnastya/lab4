#include "sdt.h"
//функци€ дл€ пункта 4.2
bool err = true;
void proverka(char* name)
{
    //проверка на символы *,",<,>,?,|
   if (strpbrk(name,"*<>?|\"")!= 0) //strpbrk - cканирует строку name на присутствие символов из второй строки
    {
        cout <<"Unknown symbol (*<>?|\""<<endl;
        err=true;
    }
    if (strchr(name,':')!=0) //strchr - ищет первое по€вление c (преобразованного в char) в строке
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
//проверка на расширение
strrev(name); //strrev(char *s) - переписывает символы в строке в обратном пор€дке
if ( strncmp(name, "txt.", 4 ) != 0 && strncmp( name, "TXT.", 4 ) != 0) //strncmp-сравнивает строки
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
    //пункт 4.3: загрузить сожержимое файла
    FILE * file = fopen(file_name, "a+"); //доступ к файлу
    fseek(file,0,SEEK_END);  //положение в конец файла
    int size_ = ftell(file);  //размер в байтах
    fseek(file,0,SEEK_SET);
    char *mass = new char[ size_ +1 ];//
    memset(mass, 0, size_ +1); //запол€нем (size_+1) байтов блока пам€ти указанным символом
    unsigned long result = fread(mass, sizeof(char), size_, file); //‘ункци€ fread() считывает size_ объектов Ч каждый объект по sizeof(char) символов в длину Ч из потока file и помещает их в символьный массив, указанный в mass.
    if (ferror(file)) //проверка на файловые ошибки
    {
        cout<<"File error\n";
        exit (1);
    }
    cout <<"\nThe contents of the file:"<<endl;
    puts(mass);
    //пункт 4.4: ввести искомую строку в тексте
    cout <<"\nEnter a search string:  ";
    char str[20];
    cin >>str;

    //пункт 4.5: найти введенную строку (реализаци€ стандартной функции)
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
    //пункт 4.6: разбить файл на предложени€, поместив их в char**
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
            char *mass1 = new char[pred[i+1]]; //выделение пам€ти
            fread(mass1,sizeof(char),pred[i+1],file);
            char *mass2 = new char[pred[i+1]];
            massPred[i]= strncpy(mass2, mass1, (pred[i+1]-pred[i])*sizeof(char));
            delete [] mass1; //освобождение выделенной пам€ти
        }
        fclose (file);
        cout<<endl;
        for(int i=0; i<n; ++i)
           cout<<"("<<strlen(massPred[i])<<") : "<<massPred[i]<<endl;;
    //пункт 4.7: упор€дочить предложени€ по возрастанию
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

    //пункт 4.8: записать предложени€ в новый файл
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
    fseek(file2,0,SEEK_SET);  //положение в начало файла
    for(int i=0; i<n; ++i)
        fputs(massPred[i], file2);
        fclose (file2);

    //пункт 4.9: освободить все выделенные блоки пам€ти
    for(int i=0; i<n; ++i)
    {
       delete[] massPred;
    }
    delete [] mass, pred, cp, massPred;
    delete s1, s2;
}

