#include <iostream>
#include <cstdlib>
 
int main()
{
  double pi=0;
  double item=1;
  for (int n=1,sign=1;item>1e-11;++n,sign*=-1)
  {
    item = 1/double(2*n-1);
    pi += sign*item;
  }
  pi *= 4;
  std::cout.precision(20);
  std::cout<<"Pi:"<<pi<<"\n";
  system("pause");
}
