#include <iostream>
#include <errno.h>

using namespace std;

template <size_t N>
class Stack {
    private:
        int data[N];
        unsigned size = 0;

    public:
        bool full(){
            return ( size == N );
        }

        bool empty(){
            return ( size == 0 );
        }

        void push(int nr){
            if ( !full() ){
                cout << "Push -> " << nr << "\n";
                data[size] = nr;
                size++;
            }
            else {
                cerr << "Error: Stack Full\n";
                exit(1);
            }
        }

        int pop(){
            if ( !empty() ){
                size--;
                cout << "Pop -> " << data[size] << "\n";
                return data[size];
            }
            else {
                cerr << "Error: Stack Empty\n";
                exit(2);
            }
        }

        void print(){
            cout << "Stack: ";
            for (unsigned index = 0 ; index < size ; index++){
                cout << data[index] << " ";
            }
            cout << "\n";
        }
};

template <size_t N>
class Queue {
    private:
        int data[N];
        unsigned size = 0;

        void reorder(){
            for (int index = 0 ; index < size ; index++){
                data[index] = data[index+1];
            }
        }

    public:
        bool full(){
            return ( size == N );
        }

        bool empty(){
            return ( size == 0 );
        }

        void push(int nr){
            if ( !full() ){
                cout << "Push -> " << nr << "\n";
                data[size] = nr;
                size++;
            }
            else {
                cerr << "ERROR: QUEUE FULL\n";
                exit(3);
            }
        }

        int pop(){
            if ( !empty() ){
                int nr = data[0];
                size--;
                reorder();
                cout << "Pop -> " << nr << "\n";
                return nr;
            }
            else {
                cerr << "ERROR: QUEUE EMPTY\n";
                exit(4);
            }
        }

        void print(){
            cout << "Queue: ";
            for (unsigned index = size ; index > 0 ; index--){
                cout << data[index-1] << " ";
            }
            cout << "\n";
        }
};

int main(){
    cout << "STACK\n";
    Stack<3> s;
    s.push(5);  // Size: 1/3
    s.push(7);  // Size: 2/3
    s.push(3);  // Size: 3/3
    s.print();
    s.pop();    // Size: 2/3
    s.print();
    s.push(2);  // Size: 3/3
    s.print();

    cout << "\nQUEUE\n";
    Queue<4> q;
    q.push(5);  // Size: 1/4
    q.push(7);  // Size: 2/4
    q.push(3);  // Size: 3/4
    q.print();
    q.pop();    // Size: 2/4
    q.print();
    q.push(2);  // Size: 3/4
    q.push(3);  // Size: 4/4
    q.print();
    q.push(3); // Queue should be full -> ERROR

    cout << "THIS SHOULD NOT BE PRINTED";

    return 0;
}
