#include<stdio.h>
#include<math.h>
#include<stdlib.h>

int Quad_equa(double a,double b,double c,double& s1,double& s2);

//----------------------------

int main(){
  double a,b,c;
  double s1 = 0,s2 = 0;
  
  printf("Type in the a,b,c of a quadrtic equation. \n\n ax^2+bx+c=0 \n\n");

  printf("a:");
  scanf("%lf",&a);
  printf("b:");
  scanf("%lf",&b);
  printf("c:");
  scanf("%lf",&c);

  if(Quad_equa(a,b,c,s1,s2)){
    printf("\n\nSolvtion\n------\nx1:%f , x2:%f\n\n",s1,s2);
  }else{
    printf("\n\nNo solvtion.\n\n");
  }

  system("pause");
}

int Quad_equa(double a,double b,double c,double& s1,double& s2){
  double delta = 0;

  delta = pow(b,2)-4*a*c;
  if(delta >= 0){
    s1 = (-b+sqrt(delta))/(2*a);
    s2 = (-b-sqrt(delta))/(2*a);
    return 1;
  }else{
    return 0;
  }

}

