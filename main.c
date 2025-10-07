#include <stdio.h>

/* --Project Information--
 * Developer: Simon Murray
 * Date: 2024-06-15



 * Plan:
 *  Initialize:
 *  - Read a Config File
 *  - Should change how the shell behaves in some way
 *  Interpret:
 * - Read user input
 * - execute commands if present
 * - loop
 *  Cleanup:
 *  - Free any allocated memory
*/

int main() {
    
    int running = 1;
    char* inputBuffer = NULL;
    size_t bufferSize = 0;
    while (running) {
        printf("Enter a new number to set the running variable (0 to stop): ");
        getline(&inputBuffer, &bufferSize, stdin);
        
        int newValue = atoi(inputBuffer);
        if (newValue == 0) {
            running = 0;
        }
    }

    // Cleanup
    free(inputBuffer);




}