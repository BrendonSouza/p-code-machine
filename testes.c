#include <stdio.h>


int func1(int x) {
    int y;
    func2(y);
    return y;
}

int func2(int y) {
    return 0;
}

int main() {
    int x;
    func1(x);
    return 0;
}

