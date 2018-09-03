/*
 * Are defined below basic C++ -like classes to implement an FSM.
 * Do not change unless you know what you are doing.
 */

#ifndef FSM_H
#define FSM_H


typedef unsigned char Signal;
typedef struct _Event Event;
typedef struct _Fsm Fsm;
typedef void (*State)(Fsm *, Event const *);	//"State" is a function pointer


// 'Event' base class
struct _Event{
	Signal eventSignal;
};


// 'FSM' base class
struct _Fsm{
	State fsmState;
};



// "inlined" methods of FSM class
#define FsmConstructor(this_, initialState)	((this_)->fsmState = (State) initialState)
#define FsmSetState(this_, dest)			((this_)->fsmState = (State) dest)

#define FsmTransitOnEvent(this_, event)		(* (this_)->fsmState)(this_, event)


#endif	/*FSM_H*/
