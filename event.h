/**
*	@file 	event.h
*	@author Simon Hoffmann
*	@brief	Event Interface
*/

/*-------------------------- I N C L U D E S ----------------------------*/

#include <stdint.h>
#include <stdbool.h>
#include "semaphore.h"

/* ----------- V A R I A B L E S   &  C O N S T A N T S  --------------- */

typedef struct event_group{
  uint8_t bits;
	Semaphore mutex;
}event_group;	///<event group bit field

#define BIT_0 ( 1 << 0 )
#define BIT_1 ( 1 << 1 )
#define BIT_2 ( 1 << 2 )
#define BIT_3 ( 1 << 3 )
#define BIT_4 ( 1 << 4 )
#define BIT_5 ( 1 << 5 )
#define BIT_6 ( 1 << 6 )
#define BIT_7 ( 1 << 7 )

/* ----------------------- F U N C T I O N S  -------------------------- */

/**
* Creates a new event group and initializes its semaphore
*
*	@param 	none
*	@return event_group
*/
event_group event_create_event_group(void);

/**
* Read bits in an event group and waits until all or one bit is set, this function should not be called from an ISR
*
*	@param 	eventGroup			-	The event group in which the bits are being tested, must have been previously created with event_create_event_group
*					bitsToWaitFor		-	A bitwise value that indicates the bit or bits to test inside the event group
*					clearOnExit			-	If set true, then the any bits set in the bitsToWaitFor will be cleared before function return. If set false, bits are left as is.
*					waitForAllBits	-	Sets if all bits must be set or if any bit set returns the function
*	@return none
*/
void event_group_wait_bits(event_group eventGroup, uint8_t bitsToWaitFor, bool clearOnExit, bool waitForAllBits);

/**
* Set bits in an event group, this function can be called from an ISR
*
*	@param 	eventGroup	-	The event group in which the bits are being Set, must have been previously created with event_create_event_group
*					bitsToSet		-	A bitwise value that indicates the bit or bits to set inside the event group
*	@return none
*/
void event_group_set_bits(event_group eventGroup, uint8_t bitsToSet);

/**
* Clears bits in an event group, this function can be called from an ISR
*
*	@param 	eventGroup	-	The event group in which the bits are being cleared, must have been previously created with event_create_event_group
*					bitsToSet		-	A bitwise value that indicates the bit or bits to clear inside the event group
*	@return none
*/
void event_group_clear_bits(event_group eventGroup, uint8_t bitsToClear);
