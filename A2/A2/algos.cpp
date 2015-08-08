// ============================================================================
// algos.cpp
// ~~~~~~~~~~~~~~~~
// author: Amey S. Mahajan 
// - this is the ONLY file you can modify
// - feel free to include more headers if you need to
// ============================================================================

#include <iostream>

#include <stdexcept> // to throw exceptions if you need to

#include <fstream>   // to open & read from input file
#include <cstdlib>   // for atoi() if you want to use it

#include <set>       // for sba algorithm
#include <vector>    // for vba algorithm
#include <algorithm> // for vba algorithm

#include "algos.h"
using namespace std; // BAD PRACTICE
typedef int* MYTYPE;

void printVector(vector<pair<int, int> > & myVec)
{
    // traverse the vector
    vector<pair<int, int> >::iterator i;
    for (i = myVec.begin(); i != myVec.end(); ++i) {
        cout << "(" << i->first << ", " <<  i->second << ") ";
    }
    cout << endl;
}

void swap(MYTYPE a, MYTYPE b){
	int temp = *a; *a = *b; *b = temp;
}

int vba(string filename)
{
vector<pair<int,int> > EdgeVector;
ifstream ifs;
string line;
string s1="";
string s2="";
int initial=0; 
int final=0;
int CountTab=0;
int Count=0;
ifs.open(filename.c_str());
	if(ifs.fail()){
	cerr <<"Cannot open the file "<<filename<<endl;
	ifs.clear();
	}	
	else{
		while(getline(ifs,line)){
				for(int i=0;i<line.length();i++){
					if(line[i]=='#'){
						break;
					}	
						
					if(line[i]=='\t'){
                       	                	CountTab+=1;
                                        }
					
					if(line[i]!='\t' || line[i]!='\n'||line[i]!=' '){
						if(CountTab==0){	
							s1+=line[i];
						}	
						else{
							s2+=line[i];
						}	
					}		
					 if(s1=="" || s2==""){
					 Count++;
					 }

					if(Count!=0){
					 initial = atoi(s1.c_str());
					 final = atoi(s2.c_str());
				 	}
			      }
					 MYTYPE p1 = &initial;
					 MYTYPE p2 = &final; 	
					 if(initial<final){
						swap(p1,p2);
				     	 }
					
					if(initial!=0 && final!=0){	 
						EdgeVector.push_back(make_pair(initial,final));					
					}
					else if((initial==0 && final!=0)||(initial!=0 && final==0)){
						EdgeVector.push_back(make_pair(initial,final));
                                         }
						
					sort(EdgeVector.begin(), EdgeVector.end());
							
					for(vector<pair<int,int> > ::iterator iter=EdgeVector.begin();iter!=EdgeVector.end();iter++){
								vector<pair<int, int> >::iterator j = iter+1;
								if (j != EdgeVector.end() && *j == *iter){
									EdgeVector.erase(iter);
									break;
								}
					}
	
	s1 = "";
	s2 = "";
	CountTab=0;
	Count =0;
		}
	ifs.close();
}	
	return EdgeVector.size();
}
int sba(string filename)
{
set<pair<int,int> > EdgeSet;
ifstream ifs;
string line;
string s1;
string s2;
int CountTab=0;
int Count=0;
int initial=0;
int final=0;
ifs.open(filename.c_str());

        if(ifs.fail()){
          cerr <<"Cannot open the file "<<filename<<endl;
          ifs.clear();
          }

          else{
                  while(getline(ifs,line)){
                          for(int i=0;i<line.length();i++){
                                  if(line[i]=='#'){
                                          break;
                                  }
					
				if(line[i]=='\t'){
                                                  CountTab+=1;
                                          }
  
                                          if(line[i]!='\t' || line[i]!='\n'||line[i]!=' '){
                                                  if(CountTab==0){
                                                          s1+=line[i];
                                                  }      
                                                  else{
                                                          s2+=line[i];
                                                  }      
                                          }
			
                                          if(s1=="" || s2==""){
                                           Count++;
                                           }                                        
                 
                                           if(Count!=0){
					   initial = atoi(s1.c_str());
                                           final = atoi(s2.c_str());
                                           }	
		         }			
					   MYTYPE p1 = &initial;
                                           MYTYPE p2 = &final;
                                           if(initial<final){
                                           	swap(p1,p2);
                                           }
					if(initial!=0 && final!=0){   
						EdgeSet.insert(make_pair(initial,final));
					}	
					else if((initial==0 && final!=0)||(initial!=0 && final==0)){
						EdgeSet.insert(make_pair(initial,final));
					}	
s1="";
s2="";
CountTab=0;
Count=0;
		}	
    ifs.close();
}
	return EdgeSet.size(); 
}
