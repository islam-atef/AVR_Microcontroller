#ifndef EXTI_PRIVATE_H
#define EXTI_PRIVATE_H

/* GICR */
#define INT1 7
#define INT0 6
#define INT2 5
#define IVSEL 1
#define IVCE 0

/* GIFR */
#define INTF1 7
#define INTF0 6
#define INTF2 5

/* MCUCR */
#define SE 7
#define SM2 6
#define SM1 5
#define SM0 4
#define ISC11 3
#define ISC10 2
#define ISC01 1
#define ISC00 0

/* MCUCSR */
#define JTD 7
#define ISC2 6
/* bit 5 reserved */
#define JTRF 4
#define WDRF 3
#define BORF 2
#define EXTRF 1
#define PORF 0

/*				Registers' Address */
#define GICR ((volatile u8 *)(0x5B))
#define GIFR ((volatile u8 *)(0x5A))
#define MCUCR ((volatile u8 *)(0x55))
#define MCUCSR ((volatile u8 *)(0x54))

#define sei() __asm__ __volatile__("sei" ::: "memory")
#define cli() __asm__ __volatile__("cli" ::: "memory")
#endif