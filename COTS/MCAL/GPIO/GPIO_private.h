/************************************************************************/
#ifndef GPIO_PRIVATE_H
#define GPIO_PRIVATE_H
/************************************************************************/
typedef union {
  struct {
    u8 Bit_0 : 1;
    u8 Bit_1 : 1;
    u8 Bit_2 : 1;
    u8 Bit_3 : 1;
    u8 Bit_4 : 1;
    u8 Bit_5 : 1;
    u8 Bit_6 : 1;
    u8 Bit_7 : 1;
  } BITS;
  u8 Port;
} _PORT_;

#define PORTA ((volatile _PORT_ *)(0x3B))
#define DDRA ((volatile _PORT_ *)(0x3A))
#define PINA ((volatile _PORT_ *)(0x39))

#define PORTB ((volatile _PORT_ *)(0x38))
#define DDRB ((volatile _PORT_ *)(0x37))
#define PINB ((volatile _PORT_ *)(0x36))

#define PORTC ((volatile _PORT_ *)(0x35))
#define DDRC ((volatile _PORT_ *)(0x34))
#define PINC ((volatile _PORT_ *)(0x32))

#define PORTD ((volatile _PORT_ *)(0x32))
#define DDRD ((volatile _PORT_ *)(0x31))
#define PIND ((volatile _PORT_ *)(0x30))
/************************************************************************/
#endif