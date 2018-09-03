/*
 * This FSM waits for a either 4-digit code to start UPDATE on the RPi
 * or a double press on a key (actually HASH - Could be changed below) to start RECOGNITION on the RPi
 */

#ifndef KEYPAD_FSM_H
#define KEYPAD_FSM_H

#include <stdio.h>

#include "config.h"
#include "fsm.h"
#include "adc.h"


/* CLASS KEYPAD **********************************************************************************/
typedef struct _Keypad Keypad;
struct _Keypad{
	Fsm super_;	// To extend the FSM super-class. ("Inheritance")
};

void KeypadConstructor(Keypad *this);
void Keypad_START(Keypad *this, Event const *event);

// Add states below to suit your needs.
void Keypad_STATE_WAITING_FOR_A_OR_HASH(Keypad *this, Event const *event);  // Wait for either 1st code digit or 1st press on HASH
void Keypad_STATE_WAITING_FOR_B(Keypad *this, Event const *event);  // Wait for 2nd digit press
void Keypad_STATE_WAITING_FOR_C(Keypad *this, Event const *event);  // Wait for 3rd digit press
void Keypad_STATE_WAITING_FOR_D(Keypad *this, Event const *event);  // Wait for 4th digit press

void Keypad_STATE_WAITING_FOR_STAR(Keypad *this, Event const *event);
/*************************************************************************************************/


/* CLASS KEYPAD EVENT ****************************************************************************/
typedef struct _KeypadEvent KeypadEvent;
struct _KeypadEvent{
	Event super_;	// To extend the EVENT super-class. ("Inheritance")
	unsigned char code;
};

// Signals used by the Keypad FSM
enum{
	KEY_A_PRESSED,
	KEY_B_PRESSED,
	KEY_C_PRESSED,
	KEY_D_PRESSED,
    KEY_HASH_PRESSED,
    KEY_STAR_PRESSED,
	OTHER_KEY_PRESSED,
    TIMEOUT
};
/*************************************************************************************************/


/* METHODS-LIKE IMPLEMENTATION *******************************************************************/
void KeypadConstructor(Keypad *me){
	FsmConstructor(& me->super_, & Keypad_START);
}

void Keypad_START(Keypad *this, Event const *event){
	FsmSetState((Fsm *) this, & Keypad_STATE_WAITING_FOR_A_OR_HASH);
}

void Keypad_STATE_WAITING_FOR_A_OR_HASH(Keypad *this, Event const *event){
	switch(event->eventSignal){
        // This IDLE state. No need for TIMEOUT check
		case KEY_A_PRESSED:
			FsmSetState((Fsm *) this, & Keypad_STATE_WAITING_FOR_B);
			break;
        case KEY_HASH_PRESSED:
            FsmSetState((Fsm *) this, & Keypad_STATE_WAITING_FOR_STAR);
            break;
		default:
			break;
	}
}

void Keypad_STATE_WAITING_FOR_B(Keypad *this, Event const *event){
	switch(event->eventSignal){
        case TIMEOUT:
            FsmSetState((Fsm *) this, & Keypad_STATE_WAITING_FOR_A_OR_HASH);
			break;
		case KEY_B_PRESSED:
			FsmSetState((Fsm *) this, & Keypad_STATE_WAITING_FOR_C);
			break;
		case KEY_A_PRESSED:
			break;
        case KEY_HASH_PRESSED:
            FsmSetState((Fsm *) this, & Keypad_STATE_WAITING_FOR_STAR);
            break;
		default:
			FsmSetState((Fsm *) this, & Keypad_STATE_WAITING_FOR_A_OR_HASH);
			break;
	}
}

void Keypad_STATE_WAITING_FOR_C(Keypad *this, Event const *event){
	switch(event->eventSignal){
        case TIMEOUT:
            FsmSetState((Fsm *) this, & Keypad_STATE_WAITING_FOR_A_OR_HASH);
			break;
		case KEY_C_PRESSED:
			FsmSetState((Fsm *) this, & Keypad_STATE_WAITING_FOR_D);
			break;
		case KEY_A_PRESSED:
			FsmSetState((Fsm *) this, & Keypad_STATE_WAITING_FOR_B);
			break;
        case KEY_HASH_PRESSED:
            FsmSetState((Fsm *) this, & Keypad_STATE_WAITING_FOR_STAR);
            break;
		default:
			FsmSetState((Fsm *) this, & Keypad_STATE_WAITING_FOR_A_OR_HASH);
			break;
	}
}

void Keypad_STATE_WAITING_FOR_D(Keypad *this, Event const *event){
	switch(event->eventSignal){
        case TIMEOUT:
            FsmSetState((Fsm *) this, & Keypad_STATE_WAITING_FOR_A_OR_HASH);
			break;
		case KEY_D_PRESSED:
			SIGNAL_START_UPDATE = 1;
            __delay_ms(1000);                // Tune according to the RPi's response speed. (A high val is for debugging with LEDs, ...)
            SIGNAL_START_UPDATE = 0;
            
            FsmSetState((Fsm *) this, & Keypad_STATE_WAITING_FOR_A_OR_HASH);
			break;
        case KEY_HASH_PRESSED:
            FsmSetState((Fsm *) this, & Keypad_STATE_WAITING_FOR_STAR);
            break;
		default:
            FsmSetState((Fsm *) this, & Keypad_STATE_WAITING_FOR_A_OR_HASH);
			break;
	}
}

void Keypad_STATE_WAITING_FOR_STAR(Keypad *this, Event const *event){
	switch(event->eventSignal){
        case TIMEOUT:
            FsmSetState((Fsm *) this, & Keypad_STATE_WAITING_FOR_A_OR_HASH);
			break;
		case KEY_STAR_PRESSED:
			SIGNAL_START_RECOGNITION = 1;
            __delay_ms(1000);                // Tune according to the RPi's response speed. (A high val is for debugging with LEDs, ...)
            SIGNAL_START_RECOGNITION = 0;
            
            FsmSetState((Fsm *) this, & Keypad_STATE_WAITING_FOR_A_OR_HASH);
			break;
		case KEY_A_PRESSED:
			FsmSetState((Fsm *) this, & Keypad_STATE_WAITING_FOR_B);
			break;
		default:
            FsmSetState((Fsm *) this, & Keypad_STATE_WAITING_FOR_A_OR_HASH);
			break;
	}
}
/*************************************************************************************************/


#endif /*KEYPAD_FSM_H*/
