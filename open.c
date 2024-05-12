#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <string.h> // For strcmp function
#include "motorfile.h" // Motor control
#include "millis.h" // Timing function 

#define BAUD 9600
#define MYUBRR F_CPU/16/BAUD-1

void timer1_init() {
    // Set timer 1 for CTC mode
    TCCR1B |= (1 << WGM12);

    // Choose a prescaler that will fit and calculate the compare match value accordingly.
    // A prescaler of 64 is a good balance for 8 MHz to generate a 1 ms tick:
    // Formula: Compare Match Value = (Clock Speed / (Prescaler * Target Frequency)) - 1
    // Example: (8000000 / (64 * 1000)) - 1 = 124
    TCCR1B |= (1 << CS11) | (1 << CS10);  // Set prescaler to 64

    OCR1A = 124;  // Set the compare match register for 1ms tick

    // Enable the compare match interrupt
    TIMSK1 |= (1 << OCIE1A);

    // Initialize counter
    TCNT1 = 0;
}

ISR(TIMER1_COMPA_vect) {
    timer1_millis++; // Increment millis counter
}

void USART_Init(unsigned int ubrr) {
    UBRR1H = (unsigned char)(ubrr >> 8);
    UBRR1L = (unsigned char)ubrr;
    UCSR1B = (1 << RXEN1) | (1 << TXEN1) | (1 << RXCIE1); // Enable receiver, transmitter, and RX interrupt
    UCSR1C = (1 << UCSZ11) | (1 << UCSZ10); // Set frame: 8-data bits, no parity
}

void USART_putstring(const char* StringPtr) {
    while (*StringPtr != 0x00) {
        while (!(UCSR1A & (1 << UDRE1)));  // Wait for empty transmit buffer
        UDR1 = *StringPtr++;  // Put data into buffer, sends the data
    }
}

ISR(USART1_RX_vect) {
    static char buffer[100];
    static uint8_t i = 0;
    char c = UDR1; // Read the data received
    if (c == '\n' || c == '\r') {
        buffer[i] = '\0';
        i = 0;
        // Process the command
        if (strcmp(buffer, "OPEN") == 0) {
            USART_putstring("Motor operation started!\r\n");
             PORTD |= (1 << PD5);  // Turn on the motor
             PORTC &= ~(1 << PC2); // Set direction
             motorStartTime = millis(); // Record start time
             motorRunDuration = 1000;
             motorActive = 1; // Set motor as active
             USART_putstring("Loosening the grip.\r\n");
             
        } else if (strcmp(buffer, "CLOSE") == 0) {
            USART_putstring("Motor operation started!\r\n");
            PORTD |= (1 << PD5);  
            PORTC |= (1 << PC2);  
            motorStartTime = millis(); 
            motorRunDuration = 1000;
            motorActive = 1; 
            USART_putstring("Gripping!!!\r\n");
        }
    } else if (i < sizeof(buffer) - 1) {
        buffer[i++] = c;
    }
}

int main(void) {
    USART_Init(MYUBRR);
    sei();  // Enable global interrupts
    motor_control_init();  // Initialize motor control
    timer1_init(); // Timing function


    while (1) {
	 if (motorActive && (millis() - motorStartTime >= motorRunDuration)) {
            PORTD &= ~(1 << PD5); // Turn off the motor
            motorActive = 0; // Clear the active flag
    }
}
}

















