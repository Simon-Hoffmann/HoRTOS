; file: 	SchedulerASM.s
; author:	Simon Hoffmann
; brief: 	Functions for scheduling 


	AREA |.text|, CODE, READONLY, ALIGN=2
	THUMB
	REQUIRE8		;Specifies current file to preserve eight-byte alignment of the stack
	PRESERVE8

	EXTERN  RunPt            			; currently running thread
	EXPORT  schedulerASM_disableInterrupts
	EXPORT  schedulerASM_enableInterrupts
	EXPORT  schedulerASM_start_os
	EXPORT  PendSV_Handler
	IMPORT scheduler


schedulerASM_disableInterrupts
        CPSID   I
        BX      LR


schedulerASM_enableInterrupts
        CPSIE   I
        BX      LR

PendSV_Handler            	; 1) Saves R0-R3,R12,LR,PC,PSR   
    PUSH    {R4-R11}        ; 2) Save remaining regs r4-11
    LDR     R0, =RunPt 		; 3) R0=pointer to RunPt, old thread
    LDR     R1, [R0]        ;    R1 = RunPt
    STR     SP, [R1]        ; 4) Save SP into TCB
	PUSH 	{R0,LR}			   ; Registers wont be preserved by c Function call
	BL 		scheduler		   ; call Scheduler.c Scheduler function
	POP		{R0,LR}		
	LDR		R1, [R0]		; 5) R1 = RunPt, new Thread
    LDR     SP, [R1]        ; 6) new thread SP; SP = RunPt->sp;
    POP     {R4-R11}        ; 7) restore regs r4-11
    BX     LR               ; 8) restore R0-R3,R12,LR,PC,PSR

schedulerASM_start_os
    LDR     R0, =RunPt      ; currently running thread
    LDR     R2, [R0]        ; R2 = value of RunPt
    LDR     SP, [R2]        ; new thread SP; SP = RunPt->stackPointer;
    POP     {R4-R11}        ; restore regs r4-11
    POP     {R0-R3}         ; restore regs r0-3
    POP     {R12}
    POP     {LR}            ; debug LR value
	POP     {LR}            ; PC into LR
    POP     {R1}            ; discard PSR
    CPSIE   I               ; Enable interrupts at processor level
    BX      LR              ; start first thread

    ALIGN
    END
