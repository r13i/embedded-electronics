#ifndef PROTOCOLS_H
#define	PROTOCOLS_H


//Add here new keys/buttons
typedef struct{
    unsigned long UP;
    unsigned long DOWN;
} KEYS;


//SAMSUNG
#define SAMSUNG_STREAM_LENGTH 32    //Bits
const KEYS SAMSUNG = { 0xE0E006F9, 0xE0E08679 };


//Add here new protocols

#endif	/* PROTOCOLS_H */

