  
; ////////////////////////////////////
; // SOURCE FILE   delay.s          //
; ////////////////////////////////////
  
;/**************************************************************************
; *  Eingebettete Betriebssystem    (EBSy)                                 *                                                                                                  *
; **************************************************************************
; *  PROJECT       Basisproject                                            *
; *  MODULE        delay.s                                                 *
; *  REVISION      2.0                                                     *
; *  LAST AUTHOR                                                           *
; *  LAST MODIFIED                                                         *
; *  RESPONSIBLE   Peter Raab                                              *
; **************************************************************************
; *  PURPOSE:                                                              *
; *   Delay of CPU execution; implements an exact time deley of R0 * 1ms   *
; *                                                                        *
; **************************************************************************
; *  REMARKS:                                                              *
; *   SYSCLK = 48 MHz                                                      *
; *                                                                        *
; **************************************************************************
; *  CHANGE HISTORY:                                                       *
; *  Revision   Date          Author      Description                      *
; *     1.0      06.09.2019    P. Raab     creation                        *
; *     2.0      09.09.2021    P. Raab     port to STM32G4                 *
; *                                                                        *
; *************************************************************************/
  
  
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
		

	