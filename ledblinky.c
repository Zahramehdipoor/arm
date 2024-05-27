#include "LPC17xx.h"

void Delay()
{
    for(uint32_t count = 0; count < 1000000; count++) {
        // Loop for delay
    }
}

int main()
{  
    // Set P1.16 as output for LED
    LPC_GPIO1->FIODIR |= (1 << 16);
    // Set P1.18 as input for button
    LPC_GPIO1->FIODIR &= ~(1 << 18);

    while (1) {
        // Check if button is pressed
        if (!(LPC_GPIO1->FIOPIN & (1 << 18))) { // Active low button
            // Button is pressed, blink LED three times
            for (int i = 0; i < 3; i++) {
                LPC_GPIO1->FIOSET = (1 << 16); // Turn on LED
                Delay();                       // Delay
                LPC_GPIO1->FIOCLR = (1 << 16); // Turn off LED
                Delay();                       // Delay
            }
            // Ensure LED is off after blinking
            LPC_GPIO1->FIOCLR = (1 << 16); 
        }
    }
}