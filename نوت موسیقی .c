#include "LPC17xx.h"

void PWM1_Init(uint32_t frequency)
{
    uint32_t pclk, pwmClock;
    uint32_t matchValue;

    // Enable power to PWM1
    LPC_SC->PCONP |= (1 << 6);

    // Set PCLK for PWM1
    LPC_SC->PCLKSEL0 &= ~(3 << 12); // Clear previous setting
    LPC_SC->PCLKSEL0 |= (1 << 12);  // PCLK = CCLK

    // Set PWM1 function on P2.0 (PWM1.1)
    LPC_PINCON->PINSEL4 &= ~(3 << 0);
    LPC_PINCON->PINSEL4 |= (1 << 0);

    // Set PWM1 to single edge control and enable PWM1 output
    LPC_PWM1->PCR = (1 << 9);

    // Set PWM1 mode
    LPC_PWM1->TCR = (1 << 1); // Reset PWM1 counter and prescaler

    // Get the peripheral clock frequency
    pclk = SystemCoreClock / 4;

    // Calculate the PWM clock frequency and match value
    pwmClock = pclk / 4;
    matchValue = pwmClock / frequency;

    // Set the match value for PWM1
    LPC_PWM1->MR0 = matchValue;
    LPC_PWM1->MR1 = matchValue / 2; // 50% duty cycle

    // Load the match values
    LPC_PWM1->LER = (1 << 0) | (1 << 1);

    // Enable the counter and PWM mode
    LPC_PWM1->TCR = (1 << 0) | (1 << 3);
}

void Delay(uint32_t delay)
{
    for(uint32_t i = 0; i < delay; i++)
    {
        for(uint32_t j = 0; j < 1000; j++)
        {
            // Delay loop
        }
    }
}

void PlayNote(uint32_t frequency, uint32_t duration)
{
    PWM1_Init(frequency);
    Delay(duration);
    LPC_PWM1->TCR = 0;
    Delay(100);
}

int main()
{
    SystemInit();

    while(1)
    {
        // Melody: Twinkle Twinkle Little Star
        PlayNote(262, 500); // C4
        PlayNote(262, 500); // C4
        PlayNote(392, 500); // G4
        PlayNote(392, 500); // G4
        PlayNote(440, 500); // A4
        PlayNote(440, 500); // A4
        PlayNote(392, 1000); // G4

        PlayNote(349, 500); // F4
        PlayNote(349, 500); // F4
        PlayNote(330, 500); // E4
        PlayNote(330, 500); // E4
        PlayNote(294, 500); // D4
        PlayNote(294, 500); // D4
        PlayNote(262, 1000); // C4

        PlayNote(392, 500); // G4
        PlayNote(392, 500); // G4
        PlayNote(349, 500); // F4
        PlayNote(349, 500); // F4
        PlayNote(330, 500); // E4
        PlayNote(330, 500); // E4
        PlayNote(294, 1000); // D4

        PlayNote(392, 500); // G4
        PlayNote(392, 500); // G4
        PlayNote(349, 500); // F4
        PlayNote(349, 500); // F4
        PlayNote(330, 500); // E4
        PlayNote(330, 500); // E4
        PlayNote(294, 1000); // D4

        PlayNote(262, 500); // C4
        PlayNote(262, 500); // C4
        PlayNote(392, 500); // G4
        PlayNote(392, 500); // G4
        PlayNote(440, 500); // A4
        PlayNote(440, 500); // A4
        PlayNote(392, 1000); // G4

        PlayNote(349, 500); // F4
        PlayNote(349, 500); // F4
        PlayNote(330, 500); // E4
        PlayNote(330, 500); // E4
        PlayNote(294, 500); // D4
        PlayNote(294, 500); // D4
        PlayNote(262, 1000); // C4

        Delay(2000); // Wait before repeating the melody
    }

    return 0;
}