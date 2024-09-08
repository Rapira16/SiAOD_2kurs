#include <iostream>
#include <bitset>

void first_a_b() {
    unsigned char x = 255;
    unsigned char mask = 1;
    x = x & (~(mask << 6));
    std::cout << "x = " << (int)x << std::endl;
}

void first_c(){
    unsigned int x = 25;
    const int n = sizeof(int)*8;
    unsigned mask = (1 << n - 1);
    std::cout << "Mask at start: " << std::bitset<n>(mask) << std::endl;
    std::cout << "Result: ";
    for (int i = 1; i <= n; i++){
        std::cout << ((x & mask) >> (n - i));
        mask >>= 1;
    }
    std::cout << '\n';
}

void bit_sort(){}

int main(){
    first_a_b();
    first_c();
}
