#include <bits/stdc++.h>
using namespace std;
#define int long long
#define vi vector<int>
#include <stdlib.h>
set<string> r; 
void print()
{
    cout << "********************  Welcome to Parking System ***********************" << endl
         << endl;
}
class filehandling
{
    char number[20];
    char i_d[20];
    int type;
    int hour ;
    int min ;

public:
    void show_data()
    {
        cout <<  "Id number is     :  " << i_d << endl<<
                 "Vechical number  : " << number <<endl << 
			     "Type of vehical  : " << type << endl <<
			     "Time             : " << hour <<":" << min << endl;
        cout << "--------------------------------------------------------------------------------------------------------------" << endl
             << endl;
    }
    void set_data(char *n , char *s , int x )  
    {
    	strcpy(i_d , n);
    	strcpy ( number , s );
    	time_t t = time(0) ;
    	tm* tmp = localtime(&t) ;
    	hour = tmp->tm_hour ;
    	min = tmp-> tm_min;
    	type = x ;
	}
    void writting_in_file()
    {
        ofstream dout;
        dout.open("information", ios::app | ios::binary);
        dout.write((char *)this, sizeof(*this));
        dout.close();
    }
    void reading_from_file(bool check)
    {
        ifstream sin;
        sin.open("information", ios::in | ios ::binary);
        bool ok = false ;
        if (sin)
        {
            sin.read((char *)this, sizeof(*this));
            while (!sin.eof())
            {    
                if(check) 
                {   
                	if(r.find(i_d) != r.end()) 
                	r.erase(i_d) ;
				}
                else
                    show_data();
                    
                ok = true ;
                sin.read((char *)this, sizeof(*this));
            }
        }
        if(ok == false && !check)
        cout << "File is empty\n";

        sin.close();
    }
    bool delete_data(char *iidd, char *num)
    {

        ofstream dout;
        ifstream sin;
        dout.open("temp_file", ios ::out | ios ::binary);
        sin.open("information", ios ::in | ios ::binary);
        bool ok = false;
        if (sin)
        {
            sin.read((char *)this, sizeof(*this));
            while (!sin.eof())
            {   
                if (!strcmp(i_d , iidd) && !strcmp(num , number))
                {
                    ok = true;
                    sin.read((char *)this, sizeof(*this));
                    continue;
                }
                dout.write((char *)this, sizeof(*this));
                sin.read((char *)this, sizeof(*this));
            }
            if (ok == false)
                cout << "Invalid id and or vehical number please try again\n";
        }
        else
            cout << "File is empty , no data found \n";

        sin.close() ;
        dout.close() ;
        remove("information") ;
        rename("temp_file", "information") ;
        return ok;
    }
};
int32_t main()
{
          
    for(int i = 1 ; i <= 1000 ; i ++ ) 
    {
    	r.insert(to_string(i)) ;
	}
	filehandling ssss ;
	ssss.reading_from_file(true) ;
	
    system("color 0E");
here:
    while (1)
    {

        system("Cls");
        print();
        cout << "1 : Status " << endl;
        cout << "2 : Allot a slot for vehical \n";
        cout << "3 : Return car to customer \n";
        cout << "4 : Exit \n"
             << endl;
        cout << "Press option " << endl;
        string  choice;
        cin >> choice;
        system("Cls");
        if (choice == "1")
        {
            print();
                cout << "** Chart :- " << endl;
            filehandling ff;
            ff.reading_from_file(false);
        }
        else if (choice == "2")
        {
            while (1)
            {
                system("Cls");
                print();
                cout << "Choose Type of vehicle :- " << endl;
                cout << "1 : Two type vehicle " << endl;
                cout << "2 : Three type vehical " << endl;
                cout << "3 : Four type  vehical " << endl;
                cout << "4 : Back " << endl;
                cout << "Press option" << endl;
                string user;
                cin >> user;
                system("Cls");
                print();
                bool ok = false;
                
                filehandling ff;
                if (user == "1" || user == "2" || user == "3")
                {
                    char s[20] ;
                    if(r.size() == 0) 
                    cout << "Not enough space \n" ;
                    else
					{
				
                       cout << "Vehical Number : \n";
                       cin >> s;
                       string temp = *r.rbegin();
                       char b[20] ;
                       strcpy(b , temp.c_str());
                       ff.set_data( b , s , user[0] - '0' + 1);
                       r.erase(r.find(temp)) ;
                       cout <<"Id is : "<< temp << endl;
                       ff.writting_in_file();
					
		             }
                    
                }
                else if(user == "4") 
                   goto here ;
                else   
				   cout << "Incorrect choice\n ";
                  
                cout << "Press enter to continue --\n";
                getchar() ;
                getchar() ;

            }
        }
        else if (choice == "3")
        {
            while (1)
            {
                system("cls");
                print();
                cout << "Please Enter Type of vehical \n";
                cout << "1 : Two type \n";
                cout << "2 : Three type\n";
                cout << "3 : Four type \n";
                cout << "For Back press 4\n";
                string s ;
                cin >> s ;
                if (s == "4")
                    goto here;
                system("cls");
                print() ;

                if (s == "1" || s == "2" || s == "3") 
                {  
                      cout << "Please Enter vehical id  ";
                      char i_d[20];
                      char v_n[20] ;
                      cin >> i_d ;
                      cout << "Please Enter vehical number  ";
                      cin >> v_n ;
                      filehandling ff;
				      if(ff.delete_data( i_d , v_n))
				      {   
				          r.insert(i_d) ;
                          cout <<"Successful \n";
                         
                      }
                }
                else
                    cout << "Incorrect choice\n ";
                getchar() ;
                getchar() ;
 
            }
        }
        else if (choice == "4")
            break;
        else
            cout << "Incorrect Choice Please Re-enter\n";
        cout << endl;
        cout << "Press enter to continue --\n";
        getchar();
        getchar() ;
    }
    cout << "Thanx For Visiting\n";
    return 0;
}
