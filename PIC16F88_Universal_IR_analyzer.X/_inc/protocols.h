#ifndef PROTOCOLS_H
#define	PROTOCOLS_H


typedef struct{
    // unsigned char streamLength;
    unsigned long UP;
    unsigned long DOWN;
} KEYS;

// Note:
// Next values are obtained, according to the clock's freq, using next formula:
// Value = F_osc * Duration_in_micro_sec / (4 * 10^6)) * 110%_or_90%
// P.S 1: The vals are adjusted by +/- 10% to compensate the freq drift of the oscillator
// P.S 2: The vals must be in range [0-255] because of Timer0's range. To extend, use instead Timer1

// NEC  ///////////////////////////////////////////////////////////////////////
#define NEC 0x02
#define NEC_STREAM_LENGTH 32
//  Start bit HIGH state is 9 ms
#define NEC_START_BIT_HIGH_MIN_DURATION     (_XTAL_FREQ * 9 / 1000) * 9 / 10  // To get the val defined by the protocol +/- 10%
#define NEC_START_BIT_HIGH_MAX_DURATION     (_XTAL_FREQ * 9 / 1000) * 11 / 10
//  Start bit LOW state is 4.5 ms
#define NEC_START_BIT_LOW_MIN_DURATION     (_XTAL_FREQ * 45 / 10000) * 9 / 10  // To get the val defined by the protocol +/- 10%
#define NEC_START_BIT_LOW_MAX_DURATION     (_XTAL_FREQ * 45 / 10000) * 11 / 10



// SAMSUNG  ///////////////////////////////////////////////////////////////////
#define SAMSUNG 0x08
#define SAMSUNG_STREAM_LENGTH 32
//  Start bit LOW state is 4.5 ms
#define SAMSUNG_START_BIT_LOW_MIN_DURATION     126
#define SAMSUNG_START_BIT_LOW_MAX_DURATION     154
//  Start bit HIGH state is 4.5 ms
#define SAMSUNG_START_BIT_HIGH_MIN_DURATION     126  
#define SAMSUNG_START_BIT_HIGH_MAX_DURATION     154
//  Digital ZERO LOW state is 560 us
#define SAMSUNG_ZERO_BIT_LOW_MIN_DURATION     15  
#define SAMSUNG_ZERO_BIT_LOW_MAX_DURATION     19
//  Digital ZERO HIGH state is 560 us
#define SAMSUNG_ZERO_BIT_HIGH_MIN_DURATION     15  
#define SAMSUNG_ZERO_BIT_HIGH_MAX_DURATION     19
//  Digital ONE LOW state is 560 us
#define SAMSUNG_ONE_BIT_LOW_MIN_DURATION     15  
#define SAMSUNG_ONE_BIT_LOW_MAX_DURATION     19
//  Digital ONE HIGH state is 1690 us
#define SAMSUNG_ONE_BIT_HIGH_MIN_DURATION     47  
#define SAMSUNG_ONE_BIT_HIGH_MAX_DURATION     58

//const KEYS SAMSUNG = { 0xE0E006F9, 0xE0E08679 };


#endif	/* PROTOCOLS_H */

