#ifndef LCD_CONFIG_H
#define LCD_CONFIG_H

/////////////////////////////////////////////////////////////////////////////////////
#define _4_PIN_MODE_ 0
#define _8_PIN_MODE_ 1
#define LCD_MODE _4_PIN_MODE_
/////////////////////////////////////////////////////////////////////////////////////

/* This Part Is Configurable */

/* Output Part */
// Data Pins :
#define DB_7 0

#define DB_6 0

#define DB_5 0

#define DB_4 0
#if LCD_MODE == _8_PIN_MODE_
#define DB_3 0

#define DB_2 0

#define DB_1 0

#define DB_0 0
#endif

// control Pin :
#define Enable_Pin 0
#define R_W_Pin 0
#define RS_Pin 0

#endif
