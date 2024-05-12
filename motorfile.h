#include <avr/io.h>
#include <util/delay.h>

void motor_control_init() {
    // Set PD5 as output for motor PWM control
    DDRD |= (1 << DDD5);
    // Set PC2 as output for direction control
    DDRC |= (1 << DDC2);

    // Initialize PD5 and PC2 to low
    PORTD &= ~(1 << PD5);
    PORTC &= ~(1 << PC2);
}

void set_motor_direction(uint8_t direction) {
    if (direction) {
        PORTC |= (1 << PC2);  // Set direction to high for one direction
    } else {
        PORTC &= ~(1 << PC2); // Set direction to low for the opposite direction
    }
}

