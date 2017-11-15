#include <iostream>
#include <cmath>
using namespace std;

// �ӵ㣺 
// 

bool isPalindrome(int x) {
	if (x < 0)  return false;
	int size = 0;
	int value = x;
	while (value != 0) {
		value /= 10;
		size++;
	} 
	
	if (size == 0 || size == 1)  return false;
	
	value = x;
	
	while (size > 1) {
		if (value / (int)pow(10, size - 1) != value % 10)  return false;
		
		value = value % (int)pow(10, size - 1) / 10;
		size -= 2;
	}
	
	return true;
}

int main() {
	int x = -2147447412;
	cout << isPalindrome(x);
}
