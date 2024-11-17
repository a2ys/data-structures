#include <stdio.h>

void moveDisk(int n, char source, char destination) {
    printf("Move disk %d from %c to %c\n", n, source, destination);
}

void towerOfHanoi(int n, char source, char destination, char auxiliary) {
    if (n == 1) {
        moveDisk(1, source, destination); // Base case: move a single disk
        return;
    }
    
    towerOfHanoi(n - 1, source, auxiliary, destination);
    
    moveDisk(n, source, destination);
    
    towerOfHanoi(n - 1, auxiliary, destination, source);
}

int main() {
    int n;
    printf("Enter the number of disks: ");
    scanf("%d", &n);
    
    towerOfHanoi(n, 'A', 'C', 'B');
    
    return 0;
}

