#include "LPC17xx.h"

void Delay()
{
    for(uint32_t count = 0; count < 1000000; count++) {
        // Loop for delay
    }
}

int main()
{  
    // Set P1.16 - P1.20 as output for LEDs
    LPC_GPIO1->FIODIR |= ((1 << 16) | (1 << 17) | (1 << 18) | (1 << 19) | (1 << 20));
    // Set P1.21 - P1.25 as input for buttons
    LPC_GPIO1->FIODIR &= ~((1 << 21) | (1 << 22) | (1 << 23) | (1 << 24) | (1 << 25));

    while (1) {
        // Check if button 1 is pressed
        if (!(LPC_GPIO1->FIOPIN & (1 << 21))) { // Active low button
            LPC_GPIO1->FIOSET = (1 << 16); // Turn on LED 1
        } else {
            LPC_GPIO1->FIOCLR = (1 << 16); // Turn off LED 1
        }
        
        // Check if button 2 is pressed
        if (!(LPC_GPIO1->FIOPIN & (1 << 22))) { // Active low button
            LPC_GPIO1->FIOSET = (1 << 17); // Turn on LED 2
        } else {
            LPC_GPIO1->FIOCLR = (1 << 17); // Turn off LED 2
        }

        // Check if button 3 is pressed
        if (!(LPC_GPIO1->FIOPIN & (1 << 23))) { // Active low button
            LPC_GPIO1->FIOSET = (1 << 18); // Turn on LED 3
        } else {
            LPC_GPIO1->FIOCLR = (1 << 18); // Turn off LED 3
        }

        // Check if button 4 is pressed
        if (!(LPC_GPIO1->FIOPIN & (1 << 24))) { // Active low button
            LPC_GPIO1->FIOSET = (1 << 19); // Turn on LED 4
        } else {
            LPC_GPIO1->FIOCLR = (1 << 19); // Turn off LED 4
        }

        // Check if button 5 is pressed
        if (!(LPC_GPIO1->FIOPIN & (1 << 25))) { // Active low button
            LPC_GPIO1->FIOSET = (1 << 20); // Turn on LED 5
        } else {
            LPC_GPIO1->FIOCLR = (1 << 20); // Turn off LED 5
        }
    }
}