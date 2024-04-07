#include<iostream>
#include<fstream>
#include <iomanip>
#include <conio.h>
#include <string.h>
#include <windows.h>
#define WINWIDTH 113
#define WINHEIGHT 15
using namespace std;

void NewProduct();
void DisplayAllProducts();
void ModifyProduct();

struct Product{
	string name;
	double Price;
	string Quantity;
}item;

void menu(){
	int op;
    cout<<"********** -WELCOME TO ELECTRONICS STORE- ***********"<<endl;
    cout<<"*****************************************************"<<endl;
    cout<<"***** Enter 1 to add new product ********************"<<endl;
    cout<<"***** Enter 2 to display available products *********"<<endl;
    cout<<"***** Enter 3 to modify products in the store *******"<<endl;
    cout<<"***** Enter any other key to exit the menu **********"<<endl;
    cout<<"*****************************************************"<<endl;
    cout<<"*****************************************************"<<endl;
    cin>>op;
    
    if(op==1){
       NewProduct();
    }else if(op==2){
        DisplayAllProducts();
    }else if(op==3){
        ModifyProduct();
    }else{
        return;
    }
}

void NewProduct(){
	system("cls");
	cin.ignore();
	int count;
	cout<<"Enter the name of the product you want to store"<<endl;
	getline(cin,item.name);
	cout<<"Enter the price of a single "<<item.name<<endl;
	cin>>item.Price;
	cin.ignore();
	cout<<"How many "<<item.name<<" do you want to store"<<endl;
	getline(cin,item.Quantity);
	ifstream rf("count.txt");
	rf>>count;
	rf.close();
	count++;
	ofstream wf;
	wf.open("store.txt",ios::app);
	wf<<count<<". "<<"Item: "<<item.name<<endl;
	wf<<"   "<<"Price: "<<item.Price<<" Birr"<<endl;
	wf<<"   "<<"Quantity: "<<item.Quantity<<endl;
	wf.close();
	wf.open("count.txt");
	wf<<count;
	wf.close();
	
	cout<<"YOU HAVE SUCCESSFULLY ADDED AN ITEM TO THE STORE"<<endl<<endl;
	char opt;
	system("cls");
	cout<<"Do you want to add another item[Y/N]: ";
    cin>>opt;
	if (opt=='Y' || opt=='y'){
		NewProduct();
	}else{
		system("pause");
	    menu();	
	}
}

void DisplayAllProducts(){
	system("cls");
	int itemsno;
	ifstream rf;
	rf.open("count.txt");
	rf>>itemsno;
	rf.close();
	string display[3];
	rf.open("store.txt");
	for(int i=1;i<=itemsno;i++){
		getline(rf,display[0]);
		getline(rf,display[1]);
		getline(rf,display[2]);
		cout<<display[0]<<endl;
		cout<<display[1]<<endl;
		cout<<display[2]<<endl;
	}
	cout<<endl;
	rf.close();
	menu();
}

void ModifyProduct(){
	system("cls");
	string search,x[100],y[3];
	string n,p,q;
	cout<<"Enter the name of the product you want to modify: ";
	cin>>search;
	fstream f;
	f.open("store.txt");
	int i=0,j=0;
	while(i<100){
		f>>x[i];
		if (x[i]==search){
			int opt;
		    cout<<"Enter 1 to modify item price"<<endl;
		    cout<<"Enter 2 to modify item quantity"<<endl;
		    cin>>opt;
		    if(opt==1){
		        cout<<"Enter the new price of the item"<<endl;
				cin>>p;   
				f<<"  "<<"Price: "<<p<<" Birr";
				cout<<"YOU SUCCESSFULLY MODIFIED THE PRICE"<<endl;
				goto A;
			}
			else if(opt==2){
				cout<<"Enter the new quantity of the item"<<endl;
				cout<<"!!!Enter soldout if the item is out of stock!!!"<<endl;
				cin>>q;
				while(j<5){
					f>>y[j];
					if(y[j]=="Birr"){
						if(q=="soldout" || q=="SOLDOUT" || q=="Soldout" || q=="SoldOut"){
						    f<<"   "<<q<<"     ";
						    cout<<"YOU SUCCESSFULLY MODIFIED THE QUANTITY"<<endl;
						    goto A;
						}else{
							f<<"   "<<"Quantity: "<<q;
							cout<<"YOU SUCCESSFULLY MODIFIED THE QUANTITY"<<endl;
							goto A;
						}
					}
				}
			}
		}
	}
	A:
	f.close();
	menu();
}
void filler()
{
    for(int i = 0 ; i < WINWIDTH ; i++)
    {
        cout << "*";
    }
    cout << "\a" << endl;
}
void liner()
{
    for(int i = 0 ; i < WINHEIGHT ; i++)
        cout << endl;
}
void welcome()
{
    liner();
    cout << "Loading..." << endl;
    Sleep(500);
    char msg[] = "WELCOME TO ELECTRONIC STORE MANAGEMENT SYSTEM";
    int len = strlen(msg);
    int x;
    x = (WINWIDTH/2) - (len/2);
    for(int i = 0 ; i < WINWIDTH ; i++)
    {
        printf("%c",177);
        Sleep(55);
    }
    cout << endl;
    system("CLS");
    liner();
    filler();
    cout << setw(len+x) << msg << endl;
    filler();
}

int main(){
	welcome();
	menu();
	return 0;
}
