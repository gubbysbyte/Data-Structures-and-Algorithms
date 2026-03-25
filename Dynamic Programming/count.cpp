#include<iostream>
using namespace std;

/**
 * @brief Program entry point that executes ten iterations updating a counter, prints the final counter value to standard output, and exits.
 *
 * The function initializes an integer counter to 0, performs ten loop iterations that update the counter, writes the resulting counter value to stdout using `cout`, and returns an exit status.
 *
 * @return int Exit status code; `0` indicates successful termination.
 */
int main(){
    int count = 0;
    for(int i = 0; i < 10; i++){
        count = count++;
    }
    cout<<count;
    return 0;
}