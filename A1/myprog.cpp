#include <iostream>
#include<fstream>
#include <sstream>
using namespace std;

int main(){

string fname;
string line;
ifstream ifs;
int Counter=0;
int RowCount=0;
int ColumnCount=0;
cout << "Enter file name : " ;

	while(getline(cin,fname)){
	string filename = "";	
	string prefix = "";		

		for(int i=8; i<fname.length();i++){
				filename+= fname[i];
				}
		 for(int i=0; i<fname.length()-(filename.length()+1); i++){
                                prefix += fname[i];
                              }
				ifs.open(filename.c_str());	
			
			if(ifs.fail()){
					if(fname == "exit"|| fname =="bye" || fname=="quit"){
                                         break;
                                    }
		
				cerr <<"ERROR. Cannot open the file "<<fname << endl
				     <<" >  Allowed Syntax for opening- numcols <Name of the file>"<<endl
				     << " >  or numrows <Name of the file>"<<endl
				     << " >  or to close type exit/quit/bye" <<endl;  
				ifs.clear();
			      }	            	      	     
				else {cout<< "Reaching"<<endl;
					
					while(getline(ifs,line)){
						if(prefix == "numcols"){
        		               			for(int i=0;i<line.length();i++){
								if((line[i]!=' ' && (line[i+1] ==' ' || line[i+1] == '\n'))) {
									Counter +=1;	
							}	
	                					if(ColumnCount<Counter){
									ColumnCount = Counter;
							}
				    	 	}	
                                                        Counter=0;	
						}
							if(prefix == "numrows"){	
								RowCount+=1;	
						}	
						}
						
						if(prefix == "numcols"){
						 cout << " > Columns : " << ColumnCount+1 <<endl;
                                            }
						if(prefix == "numrows"){
						cout << "> Rows : " << RowCount<<endl;		
						}
					 ifs.close();
				    	}
					RowCount=0;
}	
}
