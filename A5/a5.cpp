/*======================================================
 * @author Amey S. Mahajan
 *
========================================================*/

// Iterative function to find number of negative numbers in a stack 
size_t iterative_num_negatives(stack<int> int_stack)
{
int answer=0;
	while(!int_stack.empty()){
		if(int_stack.top()<0){
			answer+=1;
		}
		int_stack.pop();
	}
return answer;
}

// Recursive function to find number of negatives in a stack
size_t recursive_num_negatives(stack<int> int_stack)
{
int counter=0;
	if(!int_stack.empty()){
		if(int_stack.top()<0){	
			counter+=1;
		}
		int_stack.pop();
		counter+=recursive_num_negatives(int_stack);
	}
	return counter;
}

// Iterative function to find whether one vector is a sub-vector of the other
bool iterative_sub_vector(vector<int>&a, vector<int>b)
{
vector<int>::iterator ita=a.begin();
vector<int>::iterator itb=b.begin();
	
	if(a.begin()!=a.end()){
		while(ita!=a.end() || itb!= b.end()){
			if(*ita == *itb){
				if((ita+1)==a.end()){
					return true;
				}	
				else{
					ita++;
					itb++;
				}
			}
			else{
				if(ita+1 == a.end()){
					return true;
				}
				ita = a.begin();
				if(itb==b.end()){
					return false;
				}
				if(*itb!=*ita){
					itb++;	
				}
			}	
		}
	}
return true;
}

//Recursive function to find whether one vector is a sub-vector of the other

bool recursive_sub_vector(vector<int>&a,vector<int>b, size_t k)
{
	if(k<b.size()){
		if(a[k]==b[k]){
			if(k+1 == a.size()) {
				return true;
			}
			k++;
		}
		else {
			if(k+1 == a.size()){
				return true;
			}
			if(b[k]!=a[k]){
				b.erase(b.begin(),b.begin()+(k-1));
				k=0;
			}
			if(k+1==b.size()){
				return false;
			}
		}
		return true && (recursive_sub_vector(a,b,k+1));
	}
return false;
}

//returns true if there is a subset of integers in int_vec that sums up to the target

bool sum_to_target(vector<int> int_vec,int target,int addition,size_t k)
{
	vector<int> addition_Vector;
	addition+=int_vec[k];
	addition_Vector.push_back(addition);	
	if(target==0){
		return true;
	}
	if(k>= int_vec.size()){
		return false;
	}
		return (target==addition)||
			sum_to_target(int_vec,target,addition, k+1) || 
			sum_to_target(int_vec,target,addition+int_vec[k],k+1);
return false;
} 
