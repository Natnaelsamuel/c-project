#include<iostream>
#include<fstream>
#include<iomanip>//a library that contains the keyword setw (set width)
#include<string>
using namespace std;

void menu();
//Structure containing the attributes of the products in the store
struct Product{
	string Name; //product name
	double Price; //product price
	int Quantity; //product quantity
}enter;
//Structure containing the attributes of the users 
struct User{
	string name;//username
	string password;//user password
	int ItemsBought;//total items bought
	double TotalExp;//total expenditure
}reg;
//A fuction to add new products to the store
void NewProduct(){
	system("cls");
	
    int count;
    cout<<"enter product name"<<endl;
    cin>>enter.Name; //to receive the product name from the admin
    cout<<"enter the price of a single "<<enter.Name<<endl;
    cin>>enter.Price; //to receive the product price from the admin
    cout<<"enter product quantity"<<endl;
    cin>>enter.Quantity; //to receive the product quantity from the admin
    
    ifstream rf("count1.txt");
	rf>>count;
	rf.close();
	count++;
	
	ofstream wf;
    wf.open("s.txt",ios::app);
    wf<<left<<setw(30)<< enter.Name << setw(20) << enter.Price <<setw(20)<<enter.Quantity<<endl;
    wf.close();
    cout<<"YOU HAVE SUCCESSFULLY ADDED A NEW PRODUCT"<<endl;
    
    wf.open("count1.txt");
	wf<<count;
	wf.close();
//To ask the admin if he wants to add another product or not
    char op;
    cout<<endl<<"Do you want to store another product [Y/N]: ";
    cin>>op;
    if (op=='Y' || op=='y'){
        NewProduct();
    }else{
        menu();
    }
}
//A function to add new users to the system
void AddUser(){
	system("cls");
	
	int countuser;
	ifstream rf;
	rf.open("count2.txt");
	rf>>countuser;
	rf.close();
      
	cout<<"Enter User name"<<endl;
    cin>>reg.name; //to receive the username from the user
    N:
    cout<<"Add a new password "<<reg.name<<endl;
    cin>>reg.password; //to receive the password from the user
    reg.TotalExp=0; //sets the total expenditure of the user to 0
    reg.ItemsBought=0; //sets the total items bought by the user to 0
    
    User data1[100];
    string check;
    rf.open("users.txt");
    rf>>check;
    rf.close();
    if(check==""){ //ckecks if the file called "users.txt" is empty or not
	    data1[1].password="0";	
	}else{
		rf.open("users.txt");
        while(!rf.eof()){ //a loop that stores all the user data in the file to the structure array called data1
		    for(int i=1;i<=countuser;i++){
			    rf>>data1[i].name;
			    rf>>data1[i].password;
			    rf>>data1[i].ItemsBought;
			    rf>>data1[i].TotalExp;
		    }
	    }
	    rf.close();
	}
    
   for(int i=1;i<=countuser;i++){ //a loop that checks if a password is unique of not
    	if(reg.password==data1[i].password){
    		cout<<"PASSWORD IS ALREADY TAKEN"<<endl;
    		cout<<"PLEASE ENTER ANOTHER PASSWORD"<<endl;
    		goto N;
		}
	}
    
    ofstream wf;
	wf.open("users.txt",ios::app);
    wf<<setw(30) << left << reg.name << setw(20) << reg.password << setw(20) << reg.ItemsBought << setw(20) << reg.TotalExp <<endl;
    countuser++;
    cout<<"YOU HAVE SUCCESSFULLY ADDED A NEW USER"<<endl;
    wf.close();
    
    wf.open("count2.txt");
    wf<<countuser;
    wf.close();
    
    system("pause");
    menu();
}
//A function that displays all the available products in the store
void DisplayAllProduct(){
    system("cls");
    
    ifstream rf;
    string line[100];
    int Countline=0,i=1,j=1;
    
    rf.open("s.txt");
    while(!rf.eof()){ //a loop to gets every line in the file and store it in a temporary string array called line
       getline(rf,line[i]);
       Countline++;
       i++;
    }
    cout << setw(33) << left << "ProductName" << setw(20) << "Price" << setw(22) << "Quantity" << endl;
    while(j<Countline){ //a loop to display all lines in the temporary string array called line
        cout<<j<<". "<<line[j]<<endl;
        j++;
    }
    rf.close();
    
    system("pause");
    menu();
}
//A function to display all registered users in the system
void DisplayUsers(){
	system("cls");
	
    string line[100];
    int Countuser=0,i=1,j=1;
    ifstream rf;
    rf.open("users.txt");
    cout << setw(30) << left << "Username" << setw(20) << "Password" << setw(20) << "ItemsBought" << setw(20) << "TotalExp" <<endl;
    while(!rf.eof()){ //a loop the gets every line in the file and stores it in a temporary string array called line 
       getline(rf,line[i]);
       Countuser++;
       i++;
    }
	while(j<Countuser){ //a loop to display all lines in the temporary string array called line
    cout<<j<<". "<<line[j]<<endl;
    j++;
	}
    rf.close();
    
    system("pause");
    menu();
}

void SearchProduct(){
	system("cls");
	
	int count,i=0;
	string search,c[100],result;
	ifstream rf;
	rf.open("count1.txt");
	rf>>count;
	rf.close();
	count*=3; //multiplies the number of items by 3 because there is 3 properties for each item
	
	cout<<"Enter the name of the item you want to search: ";
	cin>>search;
	system("cls");
	rf.open("s.txt");
	while(!rf.eof()){
		while(i<count){
			rf>>c[i];
		    if(c[i]==search){ //searches for the item required by name
		    	cout<<"The item you searched for has been found"<<endl;
		    	system("pause");
		    	system("cls");
		    	cout << setw(30) << left << "ProductName" << setw(20) << "Price" << setw(20) << "Quantity" << endl;
		    	cout<<c[i]; 
		    	cin.ignore();
		    	getline(rf,result); //gets the line that is found after the name of the item(i.e the price and quantity)
		    }
		    i++;
		}
	}
	cout<<result<<endl;	
	rf.close();
//To ask the user if he wants to search for another product or not
	char op;
    cout<<endl<<"Do you want to search for another item[Y/N]: ";
    cin>>op;
    if (op=='Y' || op=='y'){
        SearchProduct();
    }else{
        menu();
    }
}
//A function to purchase an item from the store
void PurchaseProduct(){
	system("cls");
	
	fstream f;
	int countuser, countproduct;
    f.open("count1.txt");
    f>>countproduct;
    f.close();
    f.open("count2.txt");
    f>>countuser;
    f.close();
    
    User data1[100];
    f.open("users.txt");
    while(!f.eof()){ //a loop to store all the users info in the structure array
		for(int i=1;i<=countuser;i++){
			f>>data1[i].name;
			f>>data1[i].password;
			f>>data1[i].ItemsBought;
			f>>data1[i].TotalExp;
		}
	}
	f.close();
	
	string name,password;
	int checkuser=0;
	cout<<"Enter your username: ";
	cin>>name;
	cout<<"Enter your Password: ";
	cin>>password;
	for (int i=1;i<=countuser;i++){ // a loop to check if the password inserted matchs that of the users
		if(data1[i].password==password){
			checkuser=i;
		}
	}
    
    Product data2[100];
	f.open("s.txt");
	while(!f.eof()){ //a loop to store all the product info to a structure array
		for(int i=1;i<=countproduct;i++){
			f>>data2[i].Name;
			f>>data2[i].Price;
			f>>data2[i].Quantity;
		}
	}
	f.close();
	
	N:
	system("cls");
	string search;
	int checkproduct=0;
	cout<<"\t\t\t\t\t\tHello "<<data1[checkuser].name<<endl;
	cout<<"what item do you want to purchse from the store: ";
	cin>>search;
	for(int i=1;i<=countproduct;i++){ //a loop to search for the item required
		if(search==data2[i].Name){
			checkproduct=i;
		}
	}
	int quantity;
	cout<<"How much quantity of "<<data2[checkproduct].Name<<" you want?"<<endl;
	cin>>quantity;
//An if else statement to check the amount of quantity and do the neccessary calculations of the purchase
	if(quantity>data2[checkproduct].Quantity){
		cout<<"SORRY, the amount of quantity you entered is not availabe at the moment"<<endl;
		system("pause");
		menu();
	}else{
		system("cls");
		cout.setf(ios::fixed);
		char opt;
		cout<<"Are you willing to pay "<<quantity*data2[checkproduct].Price<<" Birr [Y/N]"<<endl;
        cin>>opt;
        if(opt=='Y' || opt=='y'){
        	data2[checkproduct].Quantity-=quantity;
		    data1[checkuser].ItemsBought+=quantity;
		    data1[checkuser].TotalExp+=(quantity*data2[checkproduct].Price);
		}else{
			menu();
		}
	}
	cin.ignore();
	cout<<"YOU HAVE SUCCESSFULLY PURCHASED "<<quantity<<" "<<data2[checkproduct].Name<<endl;
	system("pause");
	f.open("s.txt");
	for(int i=1;i<=countproduct;i++){ //a loop to overwrite all product info back to the file
		f<<left<<setw(30)<< data2[i].Name << setw(20) << data2[i].Price <<setw(20)<<data2[i].Quantity<<endl;
	}
	f.close();
	
	f.open("users.txt");
	for(int i=1;i<=countuser;i++){ //a loop to overwrite all user info back to the file
		f<<setw(30) << left << data1[i].name << setw(20) << data1[i].password << setw(20) << data1[i].ItemsBought << setw(20) << data1[i].TotalExp <<endl;
	}
	f.close();	
//To ask the user if he wants to purchase another product or not	
	system("cls");
	char op;
    cout<<endl<<"Do you want to purchase another product [Y/N]: ";
    cin>>op;
    if (op=='Y' || op=='y'){
        goto N;
    }else{
        menu();
    }
}

void ModifyProduct(){
	system("cls");
	
	fstream f;
	int countproduct;
    f.open("count1.txt");
    f>>countproduct;
    f.close();
    
    Product data2[100];
	f.open("s.txt");
	while(!f.eof()){ //a loop to store all the product info to a structure array
		for(int i=1;i<=countproduct;i++){
			f>>data2[i].Name;
			f>>data2[i].Price;
			f>>data2[i].Quantity;
		}
	}
	f.close();
	
    string search;
	int checkproduct=0;
	cout<<"Enter the name of the item you want to modify from the store: ";
	cin>>search;
	for(int i=1;i<=countproduct;i++){
		if(search==data2[i].Name){ //a loop to search for the product in the srtucture array by name
			checkproduct=i;
		}
	}
	
	system("cls");
	int opt;
	cout<<"\t\t\t\t\tEnter 1 to modify the item name"<<endl;
	cout<<"\t\t\t\t\tEnter 2 to modify the item price"<<endl;
	cout<<"\t\t\t\t\tEnter 3 to modify the item quantity"<<endl;
	cin>>opt;
	if(opt==1){
		string newname;
		cout<<"Enter the new name of the product"<<endl;
		cin>>newname;
		data2[checkproduct].Name=newname;
		cout<<"You have successfully modified the name"<<endl;
	}else if(opt==2){
		double newprice;
		cout<<"Enter the new price of the product"<<endl;
		cin>>newprice;
		data2[checkproduct].Price=newprice;
		cout<<"You have successfully modified the price"<<endl;
	}else if(opt==3){
		int newquantity;
		cout<<"Enter the new quantity of the product"<<endl;
		cin>>newquantity;
		data2[checkproduct].Quantity=newquantity;
		cout<<"You have successfully modified the quantity"<<endl;
	}
	
	f.open("s.txt");
	for(int i=1;i<=countproduct;i++){ //a loop to overwrite all product info back to the file
		f<<left<<setw(30)<< data2[i].Name << setw(20) << data2[i].Price <<setw(20)<<data2[i].Quantity<<endl;
	}
	f.close();
//To ask the user if he wants to search for another product or not	
	char op;
    cout<<endl<<"Do you want to modify another item [Y/N]: ";
    cin>>op;
    if (op=='Y' || op=='y'){
        ModifyProduct();
    }else{
        menu();
    }
}

void menu(){
	system("cls");
    int op;
    cout<<"\t\t\t\t\t*****-WELCOME TO ELECTRONICS STORE-******"<<endl;
    cout<<"\t\t\t\t\t*****************************************"<<endl;
    cout<<"\t\t\t\t\t* ENTER 1 TO ADD NEW PRODUCT            *"<<endl;
    cout<<"\t\t\t\t\t* ENTER 2 TO DISPLAY AVAILABLE PRODUCTS *"<<endl;
    cout<<"\t\t\t\t\t* ENTER 3 TO MODIFY A PRODUCT           *"<<endl;
    cout<<"\t\t\t\t\t* ENTER 4 TO REGISTER AS NEW USER        *"<<endl;
    cout<<"\t\t\t\t\t* ENTER 5 TO DISPLAY ALL USERS          *"<<endl;
    cout<<"\t\t\t\t\t* ENTER 6 TO SEARCH FOR A PRODUCT       *"<<endl;
    cout<<"\t\t\t\t\t* ENTER 7 TO PURCHASE A PRODUCT         *"<<endl;
    cout<<"\t\t\t\t\t* ENTER ANY OTHER KEY TO EXIT THE MENU  *"<<endl;
    cout<<"\t\t\t\t\t*****************************************"<<endl;
    cout<<"\t\t\t\t\t*****************************************"<<endl;
    cin>>op;
    
    if(op==1){ // ONLY ADMIN ACCESSIBLE FUNCTION!!!
    	string password,check,name;
    	cout<<"Enter admin username"<<endl;
    	cin>>name;
    	cout<<"Enter your Password: ";
    	cin>>password;
    	ifstream rf("admin.txt");
    	rf>>check;
    	rf.close();
    	if(check==password){
    		system("cls");
            cout<<"\t\t\t\t\t\tHELLO ADMIN"<<endl;
	        system("pause");
    		NewProduct();
		}else{
			cout<<"!Wrong password!"<<endl;
		}
    }else if(op==2){
        DisplayAllProduct();
    }else if(op==3){ // ONLY ADMIN ACCESSIBLE FUNCTION!!!
    	string password,check,name;
    	cout<<"Enter admin username: ";
    	cin>>name;
    	cout<<"HELLO "<<name<<" Enter your Password: ";
    	cin>>password;
    	ifstream rf("admin.txt");
    	rf>>check;
    	rf.close();
    	if(check==password){
    		system("cls");
	        cout<<"\t\t\t\t\t\tHELLO ADMIN"<<endl;
	        system("pause");
    		ModifyProduct();
		}else{
			cout<<"!Wrong password!"<<endl;
		}
    }else if(op==4){
    	AddUser();
	}else if(op==5){ // ONLY ADMIN ACCESSIBLE FUNCTION!!!
		string password,check,name;
    	cout<<"Enter admin username: ";
    	cin>>name;
    	cout<<"HELLO "<<name<<" Enter your Password: ";
    	cin>>password;
    	ifstream rf("admin.txt");
    	rf>>check;
    	rf.close();
    	if(check==password){
    		system("cls");
    		cout<<"\t\t\t\t\t\tHELLO ADMIN"<<endl;
	        cout<<"The users that are registered at the moment are"<<endl;
        	system("pause");
    		DisplayUsers();
		}else{
			cout<<"!Wrong password!"<<endl;
		}
    }else if(op==6){
    	SearchProduct();
	}else if(op==7){
		PurchaseProduct();
	}else{
		return;
	}
}

int main(){
	string name,password,check;
	ifstream rf("admin.txt");
	rf>>check;
	rf.close();
	if(check==""){ // An if statement to check if the file called "admin.txt" if empty or not
	    cout<<"An admin is required to start the system\n\n";
		cout<<"Enter admin username"<<endl;
		cin>>name;
		cout<<"Enter admin password"<<endl;
		cin>>password;
		
		ofstream wf("admin.txt");
		wf<<password;
		wf.close();
		cout<<"You have successfully added adminstrator"<<endl;
		system("pause");
	}
    menu();
    return 0;
}
