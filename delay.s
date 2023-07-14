; file: 	SchedulerASM.s
; author:	Simon Hoffmann
; brief: 	Delay of CPU execution; implements an exact time deley of R0 * 1ms

  AREA  DELAY, CODE, READONLY    

  THUMB


delayms FUNCTION        ; start of function 
    EXPORT delayms 
    PUSH {R1}           ; store used registers

    ALIGN  4             ; following instruction to be 32Bit aligned
    MOV    R1, #12000    ; = 0.001 s / (4 * 1/48000000Hz)
    MUL    R0, R0, R1
    
loop_delayms 
    SUB    R0, R0, #1
    CMP    R0, #0
    BNE    loop_delayms
    NOP

    POP    {R1}
    BX     lr


    ENDFUNC  ; end of function
    END
		

	