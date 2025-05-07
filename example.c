#include "max7219.h"
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

int main() {
    max7219_init(0xFF, 0x08, 0x07); // Example: BCD decode mode, medium intensity, full scan limit
    srand(time(NULL));
    
    while (1) {
        int random_number = rand() % 100000000; // Generate a random 8-digit number
        max7219_display_number(random_number);
        sleep(1);
    }
    
    return 0;
}