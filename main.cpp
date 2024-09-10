#include <time.h>
#include <locale>

void startProgram();

int main() {
    setlocale(LC_ALL, "Russian"); 
    srand(time(NULL)); 
    
    startProgram();

    return 0; 
}
