#include<iostream>
#include<ctime>
#include<fstream>
#include<string>
using namespace std;
char spots[5][5]; 	
void Check(int a){
	if(a >= 25 ){
		throw"Parking is full";
	}
}
void Check(bool a){         
	if(a == true){
		throw"No such file exist";
	}
}
class Time{
	public:
		int h, m, s;
		void DisplayTime(){ 
			get_time();
			cout<<"---------hrs  min  sec"<<endl;
			cout<<"Time is : "<<h<<" : "<<m<<" : "<<s<<endl<<endl;
		}
	private:
		void get_time(){    
			time_t currenttime;                    
			currenttime = time(NULL);              
			tm nowLocal = *localtime(&currenttime);    
			h = nowLocal.tm_hour;           
			m = nowLocal.tm_min;
			s = nowLocal.tm_sec;
		}};
class Parking{ 
	public:	
		Parking(){		
			for (int a = 1; a <= 5; a++){
				for (int b = 1; b <= 5; b++){
				spots[a][b]='0';
				}
			}
		}
		void DisplayParking(int US){
			system("CLS");
			system("color 70");	
			cout<< " \t\t\t\t   ********************************\n";
			cout<< " \t\t\t\t   ********************************\n";
			cout<< " \t\t\t\t   *** Automated Parking System ***\n";		
			cout<< " \t\t\t\t   ********************************\n";
			cout<< " \t\t\t\t   ********************************\n";		
			cout<<"  \t\t\t\t             y "<<1<<" "<<2<<" "<<3<<" "<<4<<" "<<5<<endl;	
			cout<<"  \t\t\t\t            x"<<endl;
			for (int i = 1; i <= 5; i++){  
				cout<<"\t\t\t\t            "<<i<<"  ";
				for (int j = 1; j <= 5; j++){			
					cout<<spots[i][j]<<" ";
				}
				cout<<endl;	
			}
			cout<<"\n\t\t\t\t\tAvailable Spots : "<<25-US<<endl<<endl;
			cout<<"\t\t\t\t           Used Spots : "<<US<<endl;
		}	

};
class File : public Parking, public Time{   
	static const int totalSpots = 25;
	int enterTime[25][5];
    float tm, rs;
	public:
		int i;
		int j;
		int usedSpots;	                
		fstream tRecordIn;  
		File(){
			i = 1;
			j = 0;
			usedSpots = 0;
			tRecordIn.open("TimeIn.txt", ios_base::in);
			for (int l = 1; l <= 25; l++){												
				tRecordIn>>enterTime[l][1]>>enterTime[l][2]>>enterTime[l][3]>>enterTime[l][4]>>enterTime[l][5];
				for(int h = 1; h <= 5; h++){
					for(int t = 1; t <= 5; t++){
						if ((enterTime[l][1] == h) && (enterTime[l][2] == t)){
							usedSpots++;
							spots[h][t] = '1';
							break;
						} 
					} 
				} 
			}
			tRecordIn.close();}
		void Set_Entry(){
			i = 1;
			j = 0;       
			try{Check(usedSpots); 
				Gamma:
				j++;
				if(j>5){
					j = 1;
					i++;
				}if(spots[i][j] == '0'){
					tRecordIn.open("TimeIn.txt", ios_base::app);
					spots[i][j] = '1';
					usedSpots++;							
					DisplayParking(usedSpots);
					DisplayTime();   
					cout<<"Please Remember Your Time Of Entry"<<endl;
					cout<<"Parking spot ("<<i<<", "<<j<<") has been alloted\n"<<endl;
					tRecordIn<<i<<endl;
					tRecordIn<<j<<endl;
					tRecordIn<<h<<endl;
					tRecordIn<<m<<endl;
					tRecordIn<<s<<endl;  
					tRecordIn.close();
				}else{
					goto Gamma;
				}
			}catch(const char*c){
				cout<<c<<endl;
			}	
		}	
		void Get_Entry(){	
			int l = 1;
			DisplayParking(usedSpots);
			tRecordIn.open("TimeIn.txt", ios_base::in);
			while (l <= usedSpots){				
				tRecordIn>>enterTime[l][1]>>enterTime[l][2]>>enterTime[l][3]>>enterTime[l][4]>>enterTime[l][5];
				l++;
			}tRecordIn.close();
			tRecordIn.open("TimeIn.txt", ios_base::out);
			for(int l = 1; l <= usedSpots; l++){																	
				if ((enterTime[l][1] == i) && (enterTime[l][2] == j)){  				
					DisplayTime(); 
					tm = (((h - (enterTime[l][3]))*3600)+((m - (enterTime[l][4]))*60)+(s - (enterTime[l][5])));
					rs = 250*(tm/3600);
					goto e;
				}
				tRecordIn<<enterTime[l][1]<<endl;
				tRecordIn<<enterTime[l][2]<<endl;
				tRecordIn<<enterTime[l][3]<<endl;
				tRecordIn<<enterTime[l][4]<<endl;
				tRecordIn<<enterTime[l][5]<<endl;
			e:;
			}spots[i][j] = '0';
			if(usedSpots > 0){
				usedSpots--;
			}DisplayParking(usedSpots);
			DisplayTime();
			cout<<"Time Period : "<<tm<<" s"<<endl;
			cout<<"Total Cost Calculated : "<<rs<<" Rs"<<"( 250 Rs per hour)"<<endl<<endl;	
			tRecordIn.close();
		}
};
class Parker : public File{
	int age;
	char name[30];
	public:
	string plate;
		fstream Tdata;
		fstream ListData;
		friend istream &operator >> (istream &input, Parker &p){                        // Operator Overloading
			Name:;
			cout<<"* Enter The Name : ";
			input.getline(p.name, 30);
			input.getline(p.name, 30);
			cout<<"* Enter The Car's Number Plate : ";
			input>>p.plate;
			cout<<"* Enter Age : ";
			input>>p.age;
			return input;	
		} 
		friend ostream &operator << (ostream &output, const Parker &p){
			output<<"--> Parker Name : "<<p.name<<endl;
			output<<"--> Parker Car Number Plate : "<<p.plate<<endl;
			output<<"--> Parker Age : "<<p.age<<endl<<endl;
		}
		void DataIn(){
			DisplayTime();DisplayParking(usedSpots);
			Tdata.open(plate.c_str(), ios_base::out);
			ListData.open("List.txt", ios_base::app);
			ListData<<plate<<endl;
			ListData.close();
			Tdata<<name<<endl;
			Tdata<<plate<<endl;
			Tdata<<age<<endl;
			Set_Entry();
			Tdata<<i<<endl;
			Tdata<<j<<endl;
			Tdata.close();
		}                                   																
		bool DataOut(){
			DisplayParking(usedSpots);
			cout<<"Enter The Number Plate : ";
			cin>>plate;
			Tdata.open(plate.c_str(), ios_base::in);
			try{Check(Tdata.fail());
				Tdata.getline(name, 30);
				Tdata>>plate>>age>>i>>j;
				Get_Entry();
				Tdata.close();
				remove(plate.c_str());
			}catch(const char*c){
				cout<<c<<endl;
				Tdata.close();
			}
			return Tdata.fail();
		}	
};
main(){
	int num;
	bool b;
	Parker p;
	fstream tRecordIn;
	Alpha:
		p.DisplayParking(p.usedSpots);
		cout<<endl<<endl;
		cout<<"1 : Set Entry Of A Car."<<endl;
		cout<<"2 : Exiting A Car From Slots."<<endl;
		cout<<"3 : Only Exit The Program."<<endl;
		cout<<"4 : Reset Every Thing And Exit."<<endl<<endl;
		cout<<"Please Enter Your Choice : ";
		cin>>num;
		switch(num){
			case(1):{    
				p.DisplayParking(p.usedSpots);
				cin>>p;
				tRecordIn.open(p.plate.c_str(), ios_base::in);
				if(tRecordIn.fail()){
					p.DataIn();
					cout<<"Entry has been saved"<<endl;
					system("pause");
					tRecordIn.close();
					goto Alpha; 
				}
				else{
					cout<<"Number plate already exist"<<endl;
					system("pause");
					tRecordIn.close();
					goto Alpha;
				}
			}case(2):{
			    b = p.DataOut();
			    if(b == false){
					cout<<p;
				}
				system("pause");         
				goto Alpha;   
			}case(3):{
				cout<<"\n\nProgram will exit but the \'TimeIn.txt\' and \'List.txt\' will remain"<<endl;
				return 0;	
			}case(4):{  
				tRecordIn.open("List.txt", ios_base::in);
				while(!tRecordIn.eof()){
					tRecordIn>>p.plate;
					remove(p.plate.c_str());
				} 
				tRecordIn.close();
				remove("List.txt");
				remove("TimeIn.txt");
				cout<<"\n\n\'TimeIn.txt\' and \'List.txt\' files has been deleted and the program will be Terminated"<<endl;
				return 0;
			}
		}
	}
	
