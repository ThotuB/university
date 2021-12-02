#include <iostream>
#include <time.h>

using namespace std;

void sort(){

}

unsigned CountTripletsSum(int Arr[], int val){
    unsigned trips = 0;

    unsigned size = (sizeof(Arr)/sizeof(Arr[0]));
    unsigned right, left;

    for (int i = 0; i < size - 1 ; i++) {
        for ( left = i+1, right=size-1 ; left < right ; ) { 
            if ( Arr[left] + Arr[i] + Arr[right] == val ) { 
                trips++;
            } 
            
            if ( Arr[left] + Arr[i] + Arr[right] < val ){
                left++;
            }
            else {
                right--;
            }
        }
    }
}

int main(){
    int Arr[] = {24, 10, -7, 13, 21, 3, 4, -5, -16, 0};
    int val = 0;
}