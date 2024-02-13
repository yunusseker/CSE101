#include <stdio.h>

// Function prototypes
float add(float num1, float num2);
float subtract(float num1, float num2);
float multiply(float num1, float num2);
float divide(float num1, float num2);
float power(float base, int exponent);
float average();
float findMaximum();

int main() {
    int choice;
    float num1, num2;
    
    // Display welcome message
    printf("%% WELCOME TO GTU CALCULATOR MACHINE %%\n");
    printf("%% STUDENT NAME: Yunus Seker %%\n");
    
    // Main menu loop
    do {
        printf("\n%% MENU : %%\n");
        printf("(1) ADD TWO NUMBERS\n");
        printf("(2) SUBTRACT TWO NUMBERS\n");
        printf("(3) MULTIPLY TWO NUMBERS\n");
        printf("(4) DIVIDE TWO NUMBERS\n");
        printf("(5) TAKE THE NTH POWER OF A NUMBER\n");
        printf("(6) FIND AVERAGE OF NUMBERS INPUTTED\n");
        printf("(7) FIND THE MAXIMUM OF NUMBERS INPUTTED\n");
        printf("(0) EXIT\n");
        printf("PLEASE SELECT: "); 
        
        // Get user choice
        scanf("%d", &choice);
        
        // Switch case to perform the selected operation
        switch(choice) {
            case 1:
                // Addition
                printf("Enter two numbers: ");
                scanf("%f %f", &num1, &num2);
                printf("Result: %.2f\n", add(num1, num2));// calling add function and sending our first and second value
                break;
            case 2:
                // Subtraction
                printf("Enter two numbers: ");
                scanf("%f %f", &num1, &num2);
                printf("Result: %.2f\n", subtract(num1, num2));// calling subtract function and sending our first and second value
                break;
            case 3:
                // Multiplication
                printf("Enter two numbers: ");
                scanf("%f %f", &num1, &num2);
                printf("Result: %.2f\n", multiply(num1, num2));// calling add multiply function and sending our first and second value
                break;
            case 4:
                // Division
                printf("Enter two numbers: ");
                scanf("%f %f", &num1, &num2);
                if(num2 != 0)
                    printf("Result: %.2f\n", divide(num1, num2));// calling divide function and sending our first and second value
                else
                    printf("Error: Cannot divide by zero\n");
                break;
            case 5:
                // Power
                printf("Enter base and exponent: ");
                scanf("%f %d", &num1, &choice);
                printf("Result: %.2f\n", power(num1, choice)); // calling power function and sending our first and second value
                break;
            case 6:
                // Average
                printf("Result: %.2f\n", average()); // calling average function
                break;
            case 7:
                // Maximum
                printf("Result: %.2f\n", findMaximum());// calling findMaximum function
                break;
            case 0:
                // Exit
                printf("Exiting program. Goodbye!\n"); // exiting the program if user enter 0
                break;
            default:
                // Invalid choice
                printf("Invalid choice. Please try again.\n"); // if user enter except these value warning the user
        }
    } while (choice != 0); // if user cahoice not equal 0 program will continue to work
    
    return 0;
}

// Function to add two numbers
float add(float num1, float num2) {
    return num1 + num2;
}

// Function to subtract two numbers
float subtract(float num1, float num2) {
    return num1 - num2;
}

// Function to multiply two numbers
float multiply(float num1, float num2) {
    return num1 * num2;
}

// Function to divide two numbers
float divide(float num1, float num2) {
    return num1 / num2;
}

// Function to calculate power of a number
float power(float base, int exponent) {
    float result = 1;
    // Compute power using a loop
    for (int i = 0; i < exponent; ++i) { // taking exponent as a control value in for loop and multiply base value each time
        result *= base;
    }
    
    return result;
}


// Function to find average of numbers inputted
float average() {
    float sum = 0;
    int count = 0;
    float num;
    int exit = 1;
    do {
        printf("Enter numbers (enter a non-numeric character to finish): ");
        if (scanf("%f", &num)==1) { // if user enter a number scanf function will return 1 because operation will success
            if (num != 0) {
                sum += num;
                count++;
            }
        }
        else {
            char a = getchar(); // if its not then the chrahter goes to buffer with help of getchar function we are cleaning the buffer
            exit = 0; // and assing exit value to 0 for exit the loop
        }
    } while (exit!=0);

    // Avoid division by zero
    if (count == 0) {
        printf("No numbers entered.\n");
        return 0;
    }

    return sum / count; // returning the value
}

// Function to find the maximum of numbers inputted
float findMaximum() {
    int count;
    float max, num;
    char a;
    int exit=1;

    printf("Enter numbers (enter a non-numeric character to finish): ");
    // Check if no numbers are entered then return 0
    if (scanf("%f", &num) != 1) {
        printf("No numbers entered.\n");
        a=getchar();
        return 0;
    }

    max=num; // if number entered then assing that number to max 
    count = 1; // and assing counter to 1

    while (exit!=0){ // if exit value is not zero loop will work            
        printf("Enter numbers (enter a non-numeric character to finish): ");
        if (scanf("%f", &num)==1) { 
            if (num > max) // if entered number is bigger then max number then assign the num to max
                max = num;
            count++; // and increment the number 
        }
        else {
            char a = getchar(); // if its not number then clean the buffer
            exit = 0; // for exiting the program assign exit 0
        }
    }
    
    // Check if only one number is entered
    if (count == 1) {
        printf("Only one number entered.\n");
        return max;
    } else {
        return max;
    }
}
