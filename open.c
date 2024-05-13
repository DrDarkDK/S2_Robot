#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdio.h>
#include <string.h>
#include <string.h> // For strcmp function
#include "motorfile.h" // Motor control
#include "millis.h" // Timing function 

#define BAUD 9600
#define MYUBRR F_CPU/16/BAUD-1

void timer1_init() {
    // Set timer 1 for CTC mode
    TCCR1B |= (1 << WGM12);

    // Prescaler of 64 for 8 MHz to generate a 1 ms tick:
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

void ADC_Init() {
    ADMUX = (1 << REFS0);  // AVCC with external capacitor at AREF pin
    ADCSRA = (1 << ADEN) | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);
}

uint16_t ADC_Read(uint8_t channel) {
    ADMUX = (ADMUX & 0xF0) | (channel & 0x0F);
    ADCSRA |= (1 << ADSC);
    while (ADCSRA & (1 << ADSC));
    return ADC;
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
             motorRunDuration = 3000;
             motorActive = 1; // Set motor as active
             USART_putstring("Loosening the grip.\r\n");
             
        } else if (strcmp(buffer, "CLOSE") == 0) {
            USART_putstring("Motor operation started!\r\n");
            PORTD |= (1 << PD5);  
            PORTC |= (1 << PC2);  
            motorStartTime = millis(); 
            motorRunDuration = 6000;
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
    ADC_Init();  // Initialize ADC for current sensing
    char buffer[128];
    uint16_t adc_value;
    uint32_t current_mA;
    DDRB |= (1 << PB1); 

    while (1) {
	 if (motorActive && (millis() - motorStartTime >= motorRunDuration)) {
            PORTD &= ~(1 << PD5); // Turn off the motor
            motorActive = 0; // Clear the active flag
    }
    static unsigned long lastRead = 0;
        if (millis() - lastRead >= 1000) {
            PORTB ^= (1 << PB1); // LED for testing
            lastRead = millis();
            adc_value = ADC_Read(0);
            current_mA = (uint32_t)adc_value * 5000 / 1023 / 25;  // Current calculation: 5 volts, shunt resisotr 25 milliohms
            sprintf(buffer, "Current: %lu mA\r\n", current_mA);  // Long unsigned specifier
            USART_putstring(buffer);
        }
}
}
