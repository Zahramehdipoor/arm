#include <LPC17xx.h>

void delay_ms(unsigned int x){
    unsigned int j, k;
    for(j = 0; j < x; j++)
        for(k = 0; k < 10000; k++); // Adjust this loop for the desired delay
}

int main(void){
    LPC_GPIO0->FIODIR = 0xffff;
    LPC_GPIO1->FIODIR &= ~(1 << 18); // Configure P1.18 as input for the button
    
    int x = 180;
    int d = x / 60;
    int buttonPressed = 0; // Flag to indicate whether the button is pressed or not
    int motorRunning = 0; // Flag to indicate whether the motor is running or not
    
    while(1){
        if(LPC_GPIO1->FIOPIN & (1 << 18)){ // Check if the button is not pressed
            buttonPressed = 0; // Set the button flag to indicate it's not pressed
        }
        else { // If the button is pressed
            buttonPressed = 1; // Set the button flag to indicate it's pressed
        }
        
        if(buttonPressed && !motorRunning){ // If the button is pressed and the motor is not running
            motorRunning = 1; // Set the motor running flag to indicate it's running
            
            // Rotate the motor 180 degrees
            while(d >= 0){
                LPC_GPIO0->FIOPIN = 1;
                delay_ms(1000);
                LPC_GPIO0->FIOPIN = 2;
                delay_ms(1000);
                LPC_GPIO0->FIOPIN = 4;
                delay_ms(1000);
                LPC_GPIO0->FIOPIN = 8;
                delay_ms(1000);
                d--;
            }
            
            motorRunning = 0; // Reset the motor running flag
        }
    }
}