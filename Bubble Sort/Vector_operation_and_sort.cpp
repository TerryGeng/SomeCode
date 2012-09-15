#include<iostream>
#include<vector>
#include<cstdlib>
#include<ctime>
using namespace std;
//---------------------------
void sort(vector<int>& vec);
//---------------------------
int main(){
	cout<<"The contains of this vector are:\n";
	
	srand(time(NULL)); //Take notes of the start time. 
	
	vector<int> vec(10);
	 
	for(int i=0;i<vec.size();i++) // Generate some rand int. 
		vec[i]=rand() % 100;
	
    for(int s=0;s<vec.size();s++) // Output the vector before sorting. 
		cout<<vec[s]<<"\n"; 

	cout<<"\nAfter sorting:\n";
	sort(vec);

	for(int s=0;s<vec.size();s++) // Output after sorting. 
		cout<<vec[s]<<"\n";
		
		
	cin.ignore(); 
	return 0;
}
void sort(vector<int>& vec){
	for(int sorted=1;sorted<vec.size();sorted++)
		for(int i=0;i<vec.size()-sorted;i++) // Reduce the number of the int which need to keep sorting. 
			if(vec[i]>vec[i+1]) swap(vec[i],vec[i+1]);
}
