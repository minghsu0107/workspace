// Demo of shallow copy, with double deletions
// double deletions happen when two object shares same memory address
// this leads to double calls of destructor
#include <cstdlib>
#include <iostream>
using namespace std;

class myVec {
	public:
		myVec(int n=10){size=n; data=new int[size];};
		~myVec(){delete [] data;};
		void print();	// Print data
		int *data;
		int size;
};

void myVec::print(){
	cout << "[";
	for (int i=0; i<size; i++)
		cout << data[i] << " ";
	cout << "]" << endl;
}

int main(){
	// Default copy constructor invoked, 
	// Shared memory & double deletion
	myVec a(5);
	myVec b=a;	// Copy constructor, same as "myVec b(a);".
    
    // Default assignment operator invoked, (covering the original data)
    // Shared memory, memory leak(lost the pointer), and double deletion
	myVec c;
	c = a;

	// shares same address
	cout << "Address of a.data: " << a.data << endl;
	cout << "Address of c.data: " << c.data << endl;
    
    // shares same address
	cout << "Address of a.data: " << a.data << endl;
	cout << "Address of b.data: " << b.data << endl;
    
	a.data[0]=2;
	cout << "a.data[0]=2 ==>" << endl; 
	cout << "a: "; a.print();
	cout << "b: "; b.print();
	cout << "c: "; c.print();
	b.data[1]=4;
	cout << "b.data[1]=4 ==>" << endl;
	cout << "a: "; a.print();
	cout << "b: "; b.print();
	cout << "c: "; c.print();
	c.data[2]=5;
	cout << "c.data[2]=5 ==>" << endl;
	cout << "a: "; a.print();
	cout << "b: "; b.print();
	cout << "c: "; c.print();

	cout << "Last line of code..." << endl;
	return EXIT_SUCCESS;
}
