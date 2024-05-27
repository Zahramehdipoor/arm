#include "LPC17xx.h"

#define PWM_FREQUENCY 1000 // ????? ?????? PWM ?? ?? ????? (????)
#define PWM_PIN 0          // ??? ????? ?? PWM (P2.0)

void PWM_Init(uint32_t frequency)
{
    uint32_t pclk, pwmClock;
    uint32_t matchValue;

    // Enable power to PWM1
    LPC_SC->PCONP |= (1 << 6);

    // Set PCLK for PWM1
    LPC_SC->PCLKSEL0 &= ~(3 << 12); // Clear previous setting
    LPC_SC->PCLKSEL0 |= (1 << 12);  // PCLK = CCLK

    // Set PWM1 function on PWM_PIN
    LPC_PINCON->PINSEL4 &= ~(3 << 0);
    LPC_PINCON->PINSEL4 |= (1 << 0);

    // Set PWM1 to single edge control
    LPC_PWM1->PCR = (1 << 9);

    // Set PWM1 mode
    LPC_PWM1->TCR = (1 << 1); // Reset PWM1 counter and prescaler

    // Get the peripheral clock frequency
    pclk = SystemCoreClock / 4;

    // Calculate the PWM clock frequency and match value
    pwmClock = pclk / 4;
    matchValue = pwmClock / frequency;

    // Set the match value for PWM1
    LPC_PWM1->MR0 = matchValue - 1;

    // Load the match value
    LPC_PWM1->LER = (1 << 0);

    // Enable the counter and PWM mode
    LPC_PWM1->TCR = (1 << 0) | (1 << 3);
}

void setLEDIntensity(uint32_t dutyCycle)
{
    // Set duty cycle for PWM1
    LPC_PWM1->MR1 = dutyCycle;
    LPC_PWM1->LER = (1 << 1); // Load new match value
}

int main()
{
    SystemInit();

    // Initialize PWM with desired frequency
    PWM_Init(PWM_FREQUENCY);

    // Start with LED off (0% duty cycle)
    setLEDIntensity(0);

    while(1)
    {
        // Increase duty cycle gradually to increase LED brightness
        for(uint32_t dutyCycle = 0; dutyCycle <= 1023; dutyCycle++)
        {
            // Update duty cycle
            setLEDIntensity(dutyCycle);

            // Delay for a short period to observe brightness change
            for(uint32_t i = 0; i < 10000; i++);
        }
    }

    return 0;
}