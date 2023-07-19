/**
*	@file 	event.c
*	@author Simon Hoffmann
*	@brief	Event implementation
*
* Events for OS, enabling suspension of threads on Waiting event
*/

/*-------------------------- I N C L U D E S ----------------------------*/

#include "event.h"

/* ------------- F u n c t i o n  P r o t o t y p e s  ----------------- */

/* ----------------------- F U N C T I O N S  -------------------------- */

/**
* Creates a new event group and initializes its semaphore
*
*	@param 	none
*	@return event_group
*/
event_group event_create_event_group(void){
	event_group group;
	group.bits = 0;
	semaphore_init(&group.mutex, 0);
	return group;
}

/**
* Read bits in an event group and waits until all or one bit is set, this function should not be called from an ISR
*
*	@param 	eventGroup			-	The event group in which the bits are being tested, must have been previously created with event_create_event_group
*					bitsToWaitFor		-	A bitwise value that indicates the bit or bits to test inside the event group
*					clearOnExit			-	If set true, then the any bits set in the bitsToWaitFor will be cleared before function return. If set false, bits are left as is.
*					waitForAllBits	-	Sets if all bits must be set or if any bit set returns the function
*	@return none
*/
void event_group_wait_bits(event_group eventGroup, uint8_t bitsToWaitFor, bool clearOnExit, bool waitForAllBits){
	if(bitsToWaitFor == 0) return;
	bool canExit = false;
	
	if(waitForAllBits){
		while(!canExit){
			if((eventGroup.bits & bitsToWaitFor) != eventGroup.bits){
				semaphore_wait(&eventGroup.mutex);
			}else{
				canExit = true;
			}
		}
		if(clearOnExit){
			eventGroup.bits &= ~(bitsToWaitFor);
		}
	}else{
		while(!canExit){
			if((eventGroup.bits & bitsToWaitFor) == 0){
				semaphore_wait(&eventGroup.mutex);
			}else{
				canExit = true;
			}
		}
		if(clearOnExit){
			eventGroup.bits &= ~(eventGroup.bits & bitsToWaitFor);
		}
	}
}

/**
* Set bits in an event group, this function can be called from an ISR
*
*	@param 	eventGroup	-	The event group in which the bits are being Set, must have been previously created with event_create_event_group
*					bitsToSet		-	A bitwise value that indicates the bit or bits to set inside the event group
*	@return none
*/
void event_group_set_bits(event_group eventGroup, uint8_t bitsToSet){
	eventGroup.bits = bitsToSet;
	semaphore_signal(&eventGroup.mutex);
}

/**
* Clears bits in an event group, this function can be called from an ISR
*
*	@param 	eventGroup	-	The event group in which the bits are being cleared, must have been previously created with event_create_event_group
*					bitsToSet		-	A bitwise value that indicates the bit or bits to clear inside the event group
*	@return none
*/
void event_group_clear_bits(event_group eventGroup, uint8_t bitsToClear){
	eventGroup.bits &= ~(bitsToClear);
}
