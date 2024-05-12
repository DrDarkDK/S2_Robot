#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <util/atomic.h>

volatile unsigned long motorStartTime = 0;  // Record start time globally
volatile uint8_t motorActive = 0;  // Set motor as active globally
volatile unsigned long motorRunDuration = 0;  // Duration for which the motor should run


volatile unsigned long timer1_millis;

unsigned long millis() {
    unsigned long millis_return;

    ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
        millis_return = timer1_millis;
    }

    return millis_return;
}

