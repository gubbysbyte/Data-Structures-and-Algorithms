#include<iostream>
using namespace std;

int main(){
    int count = 0;
    for(int i = 0; i < 10; i++){
        count = count++;
    }
    cout<<count;
    return 0;
}