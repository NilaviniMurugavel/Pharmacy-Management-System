//PROGRAM BY NILAVINI B.M 21PD22 AND VARSHA S 21PD39

#include<iostream>
#include<conio.h>
#include<stdlib.h>
#include<fstream>
#include<cstring>
#include<iomanip>


class order;
using namespace std;


class user
{

protected :
    char name[30];
    char dob[10];
    char mobile_no[15];


public :
    void get_data()
    {
        cout<<"Enter your name  : ";
        cin>>name;
        cout<<"Enter your date of birth  : ";
        cin>>dob;
        cout<<"Enter your mobile number   : ";
        cin>>mobile_no;
    }
};


class admin:public user
{

    char ad_id[10];
    char ad_pwd[10];


public :
    int login();
    void add_stock();
    void display_stock();
    void modify_stock(int);
    void delete_stock(int);
    void viewBill();
    void mod_order(int,int);
};


class customer:public user
{

    char idno[10];
    char password[10];


public :
    void read();
    void display();
    void modify(char t[]);
    void del_elt(char m[]);
    int search_elt(char m[],char t[]);
    void make_order(char id[]);
    void view_bill(char id[]);
    void cancel_order();
};


void customer::read()
{
    customer c1;

    ofstream f;
    f.open("customerData2.dat",ios::app|ios::binary);
    if(!f)
    {
        cerr<<"error in opening the file"<<endl;
        return ;
    }
    c1.get_data();
    cout<<"Enter your username : ";
    cin>>c1.idno;
    cout<<"Enter your password : ";
    cin>>c1.password;
    f.write((char *)&c1,sizeof(c1));
    f.close();
}


void customer::display()
{
    ifstream f;

    f.open("customerData2.dat",ios::binary);
    customer c1;
    f.read((char *)&c1,sizeof(c1));
    cout<<endl;
    cout<<setw(12)<<"IDNO"<<setw(15)<<"NAME"<<setw(15)<<"D.O.B."<<setw(15)<<"MOB.no"<<endl;
    cout<<"____________________________________________________________________"<<endl;
    cout<<endl;

    while(!f.eof())
    {
        cout<<setw(12)<<c1.idno<<setw(15)<<c1.name<<setw(20)<<c1.dob<<setw(20)<<c1.mobile_no<<endl;
        f.read((char *)&c1,sizeof(c1));
    }

    f.close();
}


class stock
{

    int stock_id;
    char stock_name[50];
    int quantity;
    int md,mm,my;
    int ed,em,ey;
    float price;


public :
    void get_stock()
    {
        cout<<"Enter the stock id : ";
        cin>>stock_id;
        cout<<"Enter the stock name : ";
        cin>>stock_name;
        cout<<"Enter quantity : ";
        cin>>quantity;
        cout<<"Enter manufacture date : ";
        cin>>md>>mm>>my;
        cout<<"Enter expiry date : ";
        cin>>ed>>em>>ey;
        cout<<"Enter price : ";
        cin>>price;
    }

    void put_stock()
    {
        cout<<setw(10)<<stock_id<<setw(20)<<stock_name<<setw(10)<<quantity<<setw(10)<<md<<"/"<<mm<<"/"<<my<<setw(5)<<ed<<"/"<<em<<"/"<<ey<<setw(10)<<price<<endl;
    }

    int getid()
    {
        return stock_id;
    }

    void get_specific_data()
    {
        cout<<"Enter new quantity : ";
        cin>>quantity;
        cout<<"Enter the new price : ";
        cin>>price;
    }

    float get_stock_price()
    {
        return price;
    }

    void get_specific_num(int n)
    {
        quantity=quantity-n;
    }

};


int admin::login()
{
    int cnt=0;
    string id;
    string pwd;
    while(cnt<3)
    {
        cout<<"Enter your id : ";
        cin>>id;
        cout<<"Enter your password : ";
        char temp;

                    while(temp != '\r')
                    {
                        temp = getch();
                        if(temp == '0')
                        {
                            switch(getch())
                            {
                                default:
                                    break;
                            };
                        }
                        else if(temp == '\b')
                        {
                            if(pwd.size() != 0)
                            {
                                cout << "\b \b";
                                pwd.erase(pwd.size() - 1, 1);
                            }
                            continue;
                        }
                        else if(temp <= '9' && temp >= '0' || temp >= 'a' && temp <= 'z' || temp >= 'A' && temp <= 'Z')
                        {
                            pwd += temp;
                            cout << "*";
                        }
                        else
                            continue;
                    }

        if(id=="AP1")
        {
            if(pwd=="AP1")
            {
                cout<<"\nLOGIN SUCCESSFUL"<<endl;
                return 1;
            }
            else
            {
                cout<<"\nINCORRECT PASSWORD OR ID"<<endl;
            }
        }
        else
        {
            cout<<"\nINCORRECT PASSWORD OR ID"<<endl;
        }
        cnt++;

    }
    if(cnt==3)
    {
        cout<<"\n\n\n"<<endl;
        cout<<"YOU HAVE ENTER THE WRONG PASSWORD OR ID FOR MANY TIMES TRY LATER!!!"<<endl;
        return 0;
    }
    return 0;
}


void admin::add_stock()
{
    stock s;
    int n;
    cout<<"Enter the number of stocks : ";
    cin>>n;

    ofstream f;
    f.open("stocksDATA3.dat",ios::app|ios::binary);
    if(!f)
    {
        cerr<<"error in opening the file"<<endl;
        return ;
    }
    for(int i=0;i<n;i++)
    {
        s.get_stock();
        f.write((char *)&s,sizeof(s));
    }
    f.close();

}


void admin::modify_stock(int id)
{
    ifstream f1;
    ofstream f2;
    f1.open("stocksDATA3.dat",ios::binary);
    f2.open("stocksDATA3.dat",ios::in|ios::binary);
    stock s;
    int found=0,pos;
    while(!f1.eof())
    {
        f1.read((char*)&s,sizeof(s));
        if(id == s.getid())
        {
            found=1;
            pos=f1.tellg();

            f2.seekp(pos-sizeof(s),ios::beg);

            s.get_specific_data();
            f2.write((char*)&s,sizeof(s));
            break;
        }
    }

        f1.close();
        f2.close();

}

void admin::mod_order(int id,int num)
{

    ifstream f1;
    ofstream f2;
    f1.open("stocksDATA3.dat",ios::binary);
    f2.open("stocksDATA3.dat",ios::in|ios::binary);
    stock s;
    int found=0,pos;

    while(!f1.eof())
    {

        f1.read((char*)&s,sizeof(s));
        if(id == s.getid())
        {
            found=1;
            pos=f1.tellg();

            f2.seekp(pos-sizeof(s),ios::beg);

            s.get_specific_num(num);
            f2.write((char*)&s,sizeof(s));
            break;
        }
    }

    f1.close();
    f2.close();

}


void  admin::delete_stock (int id)
{
    ifstream d;
    ofstream e;

    d.open("stocksDATA3.dat",ios::binary);
    e.open("tempSTOCK1.dat",ios::binary);
    stock s;
    int found=0,pos;
    d.read((char*)&s,sizeof(s));
    while(!d.eof())
    {

        if(s.getid()!=id)
        {
            e.write((char*)&s,sizeof(s));
        }
        else
        {
            found =1;
        }
        d.read((char*)&s,sizeof(s));
    }

    d.close();
    e.close();
    if(found==0)
    {
        cout<<"NOT FOUND"<<endl;
        return;
    }
    if(remove("stocksDATA3.dat")!=0)
    {
        cout<<"ERROR"<<endl;
    }
    if(rename("tempSTOCK1.dat","stocksDATA3.dat")!=0)
    {
        cout<<"ERROR"<<endl;
    }

}


void admin::display_stock()
{
    stock s;
    ifstream f;

    f.open("stocksDATA3.dat",ios::binary);
    f.read((char *)&s,sizeof(s));

    while(!f.eof())
    {
        s.put_stock();
        f.read((char *)&s,sizeof(s));
    }

    f.close();
}

int customer::search_elt(char m[],char t[])
{
    ifstream in;
    int check=1;
    customer c1;
    int found=0;

    in.open("customerData2.dat",ios::binary);
    in.read((char *)&c1,sizeof(c1));

    while(!in.eof())
    {

        if(strcmp(m,c1.idno)==0)
        {
            while(check<3)
            {

            if(strcmp(t,c1.password)==0)
            {
                cout<<"LOGIN SUCCESSFULL"<<endl;
                return 1;
                break;
            }
            else
            {
                cout<<"WRONG PASSWORD ! TRY AGAIN "<<endl;
                check++;
            }
            cout<<"Enter your password : ";
            cin>>t;
            }
            found = 1;

        }
        in.read((char*)&c1,sizeof(c1));
    }

    if(check==2)
    {
        cout<<"You have entered the wrong password to many times try later"<<endl;
    }

    if(found==0)
    {
        cout<<"USER NOT FOUND !"<<endl;
    }

    return 0;
}

class order
{

    char c_id[10];
    int med_id;
    int quantity;
    float t_price;
    float amount;


public :
    void read_med_data(char id[])
    {
        int found=0;
        admin a;
        order o;
        float p=1;
        for(int i=0;i<10;i++)
        {
            o.c_id[i]=id[i];
        }

        cout<<"Enter the medicine id : ";
        cin>>o.med_id;
        cout<<"Enter quantity : ";
        cin>>o.quantity;

        stock s;
        ifstream f;
        f.open("stocksDATA3.dat",ios::binary);
        f.read((char *)&s,sizeof(s));

        while(!f.eof())
        {
             if(o.med_id==s.getid())
             {
                 found=1;
                 p=s.get_stock_price();
                 o.t_price=o.quantity*p;
             }
            f.read((char *)&s,sizeof(s));
        }

        if(found==0)
        {
            cout<<"ITEM NOT FOUND "<<endl;
            return;
        }
        f.close();

        ofstream f1;
        f1.open("orderDATA3.dat",ios::app|ios::binary);

        if(!f1)
        {
            cerr<<"error in opening the file"<<endl;
            return ;
        }

        f1.write((char *)&o,sizeof(o));

        f1.close();
        a.mod_order(o.med_id,o.quantity);


    }

    float get_order_price()
    {

        return t_price;
    }

    void set_amount(float a)
    {
        order o;
        amount =a;

    }

    void view_bill(char id[]);
    void disp_report();
    void cancel_order(char id[]);
};

void order::view_bill(char id[])
{

    ifstream in;
    order o;
    float a=0;
    int found=0;
    in.open("orderDATA3.dat",ios::binary);
    in.read((char *)&o,sizeof(o));

    while(!in.eof())
    {

        if(strcmp(id,o.c_id)==0)
        {
             cout<<o.med_id<<"\t"<<o.quantity<<"\t\t"<<o.t_price<<"\t"<<endl;
             a=a+o.t_price;
             found = 1;

        }
        in.read((char*)&o,sizeof(o));
    }

    if(found==1)
      cout<<"total amount to be paid : "<<a<<endl;

    if(found==0)
    {
        cout<<"NO ORDERS YET"<<endl;
    }
}

void order::disp_report()
{
    ifstream f;
    f.open("orderDATA3.dat",ios::binary);
    order o;
    f.read((char *)&o,sizeof(o));

    while(!f.eof())
    {
        cout<<o.c_id<<"\t"<<o.med_id<<"\t"<<o.quantity<<"\t\t"<<o.t_price<<endl;
        f.read((char *)&o,sizeof(o));
    }

    f.close();
}

void order::cancel_order (char id[])
{
    ifstream d;
    ofstream e;

    d.open("orderDATA3.dat",ios::binary);
    e.open("temporder.dat",ios::binary);
    order o;
    int found=0,pos;
    d.read((char*)&o,sizeof(o));

     while(!d.eof())
    {

        if(strcmp(id,o.c_id)!=0)
        {
            e.write((char*)&o,sizeof(o));
        }
        else
        {
            found =1;
        }
        d.read((char*)&o,sizeof(o));
    }

        d.close();
        e.close();
        if(found==0)
        {
            cout<<"not found"<<endl;
            return;
        }
        if(remove("orderDATA3.dat")!=0)
        {
            cout<<"error"<<endl;
        }
        if(rename("temporder.dat","orderDATA3.dat")!=0)
        {
            cout<<"error"<<endl;
        }

}
int main()
{
    char id[10];
    char pwd[10];
    float amt=0;
    int choice1,choice2,choice3,ch,ch1,ch2,ch3;
    int sid;
    int check=0,check2=0;
    int num;
    customer c;
    admin a;
    order o;
    do
    {
        system("cls");
        cout<<"\n\n\n"<<endl;
        cout<<"       ______________________________________________________"<<endl;
        cout<<"      |                                                      |"<<endl;
        cout<<"      |                    PSG PHARMACY                      |"<<endl;
        cout<<"      |----------------------------------------------------- |"<<endl;
        cout<<"      |                                                      |"<<endl;
        cout<<"      |      1 . ADMIN                                       |"<<endl;
        cout<<"      |      2 . CUSTOMER                                    |"<<endl;
        cout<<"      |      3 . EXIT                                        |"<<endl;
        cout<<"      |______________________________________________________|"<<endl;
        cout<<endl;
        cout<<"             \xdb Enter your choice : ";
        cin>>choice1;
        switch(choice1)
        {
        case 1:
                       system("cls");
                       cout<<"\n\n\n"<<endl;
                       cout<<"          ____ ADMIN LOGIN PAGE ______\n"<<endl;
                       check=a.login();
                       getch();
                       if(check)
                       {
                           do
                           {
                             system("cls");
                             cout<<"\n\n\n\t\t\t______MENU______"<<endl;
                             cout<<"\t\t\t 1. ADD STOCK"<<endl;
                             cout<<"\t\t\t 2. MODIFY STOCK"<<endl;
                             cout<<"\t\t\t 3. DELETE STOCK"<<endl;
                             cout<<"\t\t\t 4. VIEW STOCK REPORT"<<endl;
                             cout<<"\t\t\t 5. VIEW SALES REPORT"<<endl;
                             cout<<"\t\t\t 6. VIEW CUSTOMER DATA"<<endl;
                             cout<<"\t\t\t 7. RETURN TO HOME PAGE"<<endl;
                             cout<<"Enter your choice : ";
                             cin>>ch1;
                             switch(ch1)
                             {
                             case 1:
                                a.add_stock();
                                cout<<"\n\n\t\tADDED SUCCESSFULLY"<<endl;
                                getch();
                                break;
                             case 2:
                                 cout<<"Enter the id of the stock :";
                                 cin>>sid;
                                 a.modify_stock(sid);
                                 cout<<"\n\n\t\t MODIFIED SUCCESSFULLY"<<endl;
                                 getch();
                                break;
                             case 3:
                                 cout<<"Enter the id of the stock : ";
                                 cin>>sid;
                                 a.delete_stock(sid);
                                 cout<<"\n\n\t\t DELETED SUCCESSFULLY"<<endl;
                                 getch();
                                 break;
                             case 4:
                                cout<<setw(10)<<"STOCK ID"<<setw(20)<<"DRUG NAME"<<setw(10)<<"QUANTITY"<<setw(15)<<"MANF.DATE"<<setw(10)<<"EXP.DATE"<<setw(10)<<"PRICE"<<endl;
                                a.display_stock();
                                getch();
                                break;
                             case 5:
                                 cout<<"CUST.ID"<<"\t\t"<<"MED.ID"<<"\t"<<"QUANTITY"<<"\t"<<"PRICE"<<endl;
                                 o.disp_report();
                                 getch();
                                break;
                             case 6:
                                   system("cls");
                                   c.display();
                                   getch();
                                   break;
                             case 7:
                                 ch1=0;
                                 break;
                             }
                         }while(ch1);
                       }

                       getch();
                       break;
                case 2:
                        do
                        {
                             system("cls");
                             cout<<"\n\n\n"<<endl;
                             cout<<"         _____ USER LOGIN PAGE ______\n"<<endl;
                             cout<<"            \xdb 1. SIGN IN\n"<<endl;
                             cout<<"            \xdb 2. SIGN UP\n"<<endl;
                             cout<<"            \xdb 3. RETURN TO HOME PAGE"<<endl;
                             cout<<"            \xdb Enter your choice : ";
                             cin>>ch2;

                            switch(ch2)
                             {

                             case 1 :
                                       cout<<"Enter your id : ";
                                       cin>>id;
                                       cout<<"Enter your pass : ";
                                       cin>>pwd;
                                       check2=c.search_elt(id,pwd);
                                       getch();
                                       if(check2)
                                       {
                                           do
                                           {
                                                system("cls");
                                                cout<<"\n\n\t\t_________MENU__________"<<endl;
                                                cout<<"\t\t 1. ORDER MEDICINE"<<endl;
                                                cout<<"\t\t 2. CANCEL ORDER"<<endl;
                                                cout<<"\t\t 3. VIEW BILL"<<endl;
                                                cout<<"\t\t 4. RETURN LOGIN PAGE"<<endl;
                                                cout<<"Enter your choice : ";
                                                cin>>ch3;
                                                switch(ch3)
                                                {
                                                case 1:
                                                    cout<<"Enter the number of medicines : ";
                                                    cin>>num;
                                                    for(int i=0;i<num;i++)
                                                    {
                                                       o.read_med_data(id);
                                                       amt=amt+o.get_order_price();

                                                    }
                                                    o.set_amount(amt);
                                                    cout<<"order recieved successfully"<<endl;
                                                    getch();
                                                    break;
                                                case 2 :
                                                    o.cancel_order(id);
                                                    cout<<" YOUR ORDER HAS BEEN CANCELLED"<<endl;
                                                    getch();
                                                    break;
                                                case 3 :
                                                    cout<<"MED ID"<<"\t"<<"QUANTITY"<<"\t"<<"PRICE"<<endl;
                                                    o.view_bill(id);
                                                    getch();
                                                    break;
                                                case 4 :
                                                    ch3=0;
                                                    break;
                                                }

                                           }while(ch3);
                                       }
                                       getch();
                                        break;
                                      case 2 :
                                            c.read();
                                            cout<<"\n\n\t\t\xdb\tADDED SUCCESSFULLY\t\xdb"<<endl;
                                            getch();
                                            break;

                                      case 3:
                                            ch2=0;
                                        break;}
                        }while(ch2);
                        break;

                        case 3 :
                                cout<<"EXITING..."<<endl;
                                choice1=0;
                                break;






    }

}while(choice1);
}
