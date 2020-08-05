// Sensor/Input device pins
const uint8_t btn_pin = PD2;
const uint8_t ptr_pin = PD3;
const uint8_t pir_pin = PB1;


// LED pin variables
const uint8_t led_pin1 = PD5;
const uint8_t led_pin2 = PD7;
const uint8_t led_pin3 = PB4;
const uint8_t led_pin4 = PB5;

// Counter and compare values
const uint16_t t1_load = 0;
const uint16_t t1_comp = 62500; // Timer interrupt set for every 4 seconds using prescaler 1024


void setup()
{
  // For button interrupt on INT0
  
  //Set button pin to be input with pullup
  DDRD &= ~(1 << btn_pin);
  PORTD |= (1 << btn_pin);
  
  // Set LED1 pin to be output
  DDRD |= (1 << led_pin1);
  
  // Falling edge of INT0 generates interrupt
  EICRA |= (1 << ISC01);
  EICRA &= ~(1 << ISC00);
  
  // Enable Interrupts for INT0  
  EIMSK |= (1 << INT0);
  
  
  // For Photoresistor interrupt on INT1  

  // Set Photoresistor pin to be input with pullup
  DDRD &= ~(1 << ptr_pin);
  PORTD |= (1 << ptr_pin);
  
  // Set LED3 pin to be output
  DDRD |= (1 << led_pin2);
  
  // Any logical change of INT1 generates interrupt
  EICRA |= (1 << ISC10);
  EICRA &= ~(1 << ISC11);
  
  // Enable interrupts for INT1
  EIMSK |= (1 << INT1);

  
  // For PIR sensor interrupt on PCINT0

  // Set PIR sensor pin to be input with pullup
  DDRB &= ~(1 << pir_pin);
  PORTB |= (1 << pir_pin);
  
  // Set LED3 pin to be output
  DDRB |= (1 << led_pin3);
  
  // Any logical change to PCINT0 generates interrupt  
  PCICR |= (1 << PCIE0);
  PCICR &= ~(1 << PCIE1);
  PCICR &= ~(1 << PCIE2);
  
  // Enable interrupts for Pin 9 (PCINT1)
  PCMSK0 |= (1 << PCINT1);
    
  
  // For Timer Interrupt
  
  // Set LED3 pin to be output
  DDRB |= (1 << led_pin4);
  
  // Reset Timer1 Control Register A
  TCCR1A = 0;
  
  // Set CTC mode
  TCCR1B &= ~(1 << WGM13);
  TCCR1B |= (1 << WGM12);
  
  // Set to prescaler of 1024
  TCCR1B |= (1 << CS12);
  TCCR1B &= ~(1 << CS11);
  TCCR1B |= (1 << CS10);
  
  // Reset Timer1 and set compare values
  TCNT1 = t1_load;
  OCR1A = t1_comp;
  
  // Enable Timer1 compare interrupt
  TIMSK1 = (1 << OCIE1A);
  sei();

}

void loop()
{
  delay(500);
}

ISR(INT0_vect)
{
  PORTD ^= (1 << led_pin1);
}

ISR (INT1_vect)
{
  PORTD ^= (1 << led_pin2);
}

ISR(PCINT0_vect)
{
  PORTB ^= (1 << led_pin3);
}

ISR(TIMER1_COMPA_vect)
{
  
  PORTB ^= (1 << led_pin4);
}
