#include <stdio.h>
#define PI 3.141592

int main (void){
 float height,base,area;
 printf("Height?\n");
 scanf("%f",&height);
 printf("Base?\n");
 scanf("%f",&base);
 printf("A Right-angled triangle of height %4.2f and base %4.2f, has an area of %6.2f\n\n\n",height,base,base*height/2);
 
 return 0;
}
