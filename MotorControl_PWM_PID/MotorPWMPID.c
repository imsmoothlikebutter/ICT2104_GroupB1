/* DriverLib Includes */
#include <driverlib.h>
#include <stdio.h>

/* Timer_A PWM Configuration Parameter */
Timer_A_PWMConfig pwmConfigLeftWheel =
{
        TIMER_A_CLOCKSOURCE_SMCLK,
        TIMER_A_CLOCKSOURCE_DIVIDER_3,
        250000,
        TIMER_A_CAPTURECOMPARE_REGISTER_1,
        TIMER_A_OUTPUTMODE_RESET_SET,
        50000
};

Timer_A_PWMConfig pwmConfigRightWheel =
{
        TIMER_A_CLOCKSOURCE_SMCLK,
        TIMER_A_CLOCKSOURCE_DIVIDER_3,
        250000,
        TIMER_A_CAPTURECOMPARE_REGISTER_1,
        TIMER_A_OUTPUTMODE_RESET_SET,
        50000
};


int main(void)
{
    /* Halting the watchdog */
    MAP_WDT_A_holdTimer();

    // left wheel upside down

    GPIO_setAsOutputPin(GPIO_PORT_P4, GPIO_PIN4);       // Configuring P4.4 as Output
    GPIO_setAsOutputPin(GPIO_PORT_P4, GPIO_PIN5);       // Configuring P4.5 as Output
    GPIO_setOutputLowOnPin(GPIO_PORT_P4, GPIO_PIN4);    // Setting P4.4 at a Low state
    GPIO_setOutputHighOnPin(GPIO_PORT_P4, GPIO_PIN5);   // Setting P4.5 at a High State
    GPIO_setAsPeripheralModuleFunctionOutputPin(GPIO_PORT_P2, GPIO_PIN4, GPIO_PRIMARY_MODULE_FUNCTION);     // Setting P2.4 as Peripheral Output for PWMand P1.4 for button interrupt
    GPIO_setAsInputPinWithPullUpResistor(GPIO_PORT_P1, GPIO_PIN4);      // Setting P1.4 as input with pull up resistor
    GPIO_clearInterruptFlag(GPIO_PORT_P1, GPIO_PIN4);       // Clearing P1.4 interrupt flag. Making sure no previous interrupts are handled
    GPIO_enableInterrupt(GPIO_PORT_P1, GPIO_PIN4);          // Set interrupt enable bit of P1.4

    // right wheel upside down
    GPIO_setAsOutputPin(GPIO_PORT_P4, GPIO_PIN2);       // Configuring P4.2 as Output
    GPIO_setAsOutputPin(GPIO_PORT_P4, GPIO_PIN0);       // Configuring P4.0 as Output
    GPIO_setOutputLowOnPin(GPIO_PORT_P4, GPIO_PIN2);    // Setting P4.2 at a Low state
    GPIO_setOutputHighOnPin(GPIO_PORT_P4, GPIO_PIN0);   // Setting P4.0 at a High State
    GPIO_setAsPeripheralModuleFunctionOutputPin(GPIO_PORT_P5, GPIO_PIN6, GPIO_PRIMARY_MODULE_FUNCTION);     // Setting P5.6 as Peripheral Output for PWMand P1.4 for button interrupt
    GPIO_setAsInputPinWithPullUpResistor(GPIO_PORT_P1, GPIO_PIN1);      // Setting P1.1 as input with pull up resistor
    GPIO_clearInterruptFlag(GPIO_PORT_P1, GPIO_PIN1);       // Clearing P1.1 interrupt flag. Making sure no previous interrupts are handled
    GPIO_enableInterrupt(GPIO_PORT_P1, GPIO_PIN1);          // Set interrupt enable bit of P1.1


    /* Configuring Timer_A to have a period of approximately 80ms and an initial duty cycle of 10% of that (1000 ticks)  */

    // left wheel upside down
    Timer_A_generatePWM(TIMER_A0_BASE, &pwmConfigLeftWheel);

    // right wheel upside down
    Timer_A_generatePWM(TIMER_A2_BASE, &pwmConfigRightWheel);


    Interrupt_enableInterrupt(INT_PORT1);       // Enabling the interrupt in the interrupt controller
    Interrupt_enableSleepOnIsrExit();           // Sleep mode when exiting ISR
    Interrupt_enableMaster();                   // Enable interrupts globally

    /* Sleeping when not in use */
    while (1)
    {
        PCM_gotoLPM0();
    }


}

void forwardDirection(void)
{
    //Reverse the right wheel direction
    GPIO_setOutputLowOnPin(GPIO_PORT_P4, GPIO_PIN2);    // Setting P4.0 at a Low state
    GPIO_setOutputHighOnPin(GPIO_PORT_P4, GPIO_PIN0);   // Setting P4.2 at a High State

    //Reverse the left wheel direction
    GPIO_setOutputLowOnPin(GPIO_PORT_P4, GPIO_PIN4);    // Setting P4.5 at a Low state
    GPIO_setOutputHighOnPin(GPIO_PORT_P4, GPIO_PIN5);   // Setting P4.4 at a High State

}



void reverseDirection(void)
{
    //Reverse the right wheel direction
    GPIO_setOutputLowOnPin(GPIO_PORT_P4, GPIO_PIN0);    // Setting P4.0 at a Low state
    GPIO_setOutputHighOnPin(GPIO_PORT_P4, GPIO_PIN2);   // Setting P4.2 at a High State

    //Reverse the left wheel direction
    GPIO_setOutputLowOnPin(GPIO_PORT_P4, GPIO_PIN5);    // Setting P4.5 at a Low state
    GPIO_setOutputHighOnPin(GPIO_PORT_P4, GPIO_PIN4);   // Setting P4.4 at a High State

}


void leftDirection(void)
{

    //Increase the speed of the left wheel
    pwmConfigLeftWheel.dutyCycle = 20000;

    //Decrease the speed of the right wheel
    pwmConfigRightWheel.dutyCycle = 10000;


    Timer_A_generatePWM(TIMER_A0_BASE, &pwmConfigLeftWheel);
    Timer_A_generatePWM(TIMER_A2_BASE, &pwmConfigRightWheel);
}

void rightDirection(void)
{

    //Decrease the speed of the left wheel
    pwmConfigLeftWheel.dutyCycle = 10000;

    //Increase the speed of the right wheel
    pwmConfigRightWheel.dutyCycle = 20000;
    Timer_A_generatePWM(TIMER_A0_BASE, &pwmConfigLeftWheel);
    Timer_A_generatePWM(TIMER_A2_BASE, &pwmConfigRightWheel);
}

/* Port1 ISR - This ISR will progressively step up the duty cycle of the PWM on a button press */
void PORT1_IRQHandler(void)
{
    uint32_t status = MAP_GPIO_getEnabledInterruptStatus(GPIO_PORT_P1);
    GPIO_clearInterruptFlag(GPIO_PORT_P1, status);

    if (status & GPIO_PIN4)
    {
        forwardDirection();
    }

    if (status & GPIO_PIN1)
    {
        reverseDirection();
    }

}


