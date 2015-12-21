#include "sdt.h"


void print_in_binary(uint8_t byte)
{
    for(unsigned char i=0; i<8; i++)
    {
        if ((byte<<i) &0b10000000)
            cout << '1';
        else
            cout << '0';
    }
}
void print(int a)
{
    switch (a)
    {
    case 10:
        cout <<'A';
        break;
    case 11:
        cout <<'B';
        break;
    case 12:
        cout <<'C';
        break;
    case 13:
        cout <<'D';
        break;
    case 14:
        cout <<'E';
        break;
    case 15:
        cout <<'F';
        break;
    default:
        cout<<a;
    }
}
void print_in_hex(uint8_t byte)
{
    int a1 = byte&0b00001111;
    int  a2 = (byte>>4)&0b00001111;
    print(a2);
    print(a1);
}
void print_in_binaryAll(const void* data, size_t size_)
{
    uint8_t* one=(uint8_t*)data;
    for(unsigned char i=0; i<size_; i++)
    {
        print_in_binary(*one);
        cout<<' ';
        one+=1;
    }
}
void print_in_hexAll(const void* data, size_t size_)
{
    uint8_t* one=(uint8_t*)data;
    for(unsigned char i=0; i<size_; i++)
    {
        print_in_hex(*one);
        cout<<' ';
        one+=1;
    }
}

int main()
{
    cout <<"Enter: a ? b \n";
    uint16_t a, b, result;
    bool vvod = true;
    char operat;
    cin >>a >>operat >>b;
    switch (operat)
    {
    case '&':
        result = a & b;
        break;
    case '|':
        result = a | b ;
        break;
    case '^':
        result = a ^ b;
        break;
    default:
        cout <<"Unknow operator\n";
        vvod = false;
    }
    if (vvod)
    {
        print_in_hexAll(&a, sizeof(a));
        cout <<" " << operat <<" ";
        print_in_hexAll(&b, sizeof(b));
        cout <<" = ";
        print_in_hexAll(&result, sizeof(result));
        cout <<endl;

        print_in_binaryAll(&a, sizeof(a));
        cout <<" " << operat <<" ";
        print_in_binaryAll(&b ,sizeof(b));
        cout <<" = ";
        print_in_binaryAll(&result, sizeof(result));
    }
}
