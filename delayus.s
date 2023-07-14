; file: 	SchedulerASM.s
; author:	Simon Hoffmann
; brief: 	Delay of CPU execution; implements an exact time delay of 1us

  
  AREA  DELAY, CODE, READONLY    

  THUMB

delayus FUNCTION        ; start of function 
    EXPORT delayus 
    PUSH {R1}           ; store used registers

    ALIGN  4             ; following instruction to be 32Bit aligned
    MOV    R1, #12		 ; = 0.001 s / (4 * 1/48000000Hz)
    MUL    R0, R0, R1
    
loop_delayus 
    SUB    R0, R0, #1
    CMP    R0, #0
    BNE    loop_delayus
    NOP

    POP    {R1}
    BX     lr


    ENDFUNC  ; end of function
    END