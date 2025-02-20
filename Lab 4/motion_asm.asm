;******************************************************************************
; Lab 4 motion_asm code
; ECE 266, Fall 2024
; Created by Akbar Aman
; Assembly function for motion sensor
;
;******************************************************************************

        ; To include name declared in C file
        .cdecls "motion_h.h"

        .text
;******************************************************************************
; Motion signal pin usage: Grove base port J16, Tiva C PC4
;******************************************************************************

; Declaring a field to store GPIO_PORTC_BASE (32-bit) in program memory
_GPIO_PORTC_BASE     .field  GPIO_PORTC_BASE

;******************************************************************************
; Motion Detection Function
;******************************************************************************
        .global MotionDetected
        .asmfunc

MotionDetected
        PUSH    {LR}            ; save the return address
        LDR     r0, _GPIO_PORTC_BASE ; Load GPIO Port C base address
        MOV     r1, #GPIO_PIN_4      ; Use Pin 4 (PC4) for motion sensor
        BL      GPIOPinRead          ; Read the value at PC4
        CMP     r0, #0               ; Compare the result to 0 (no motion)
        BEQ     no_motion            ; If 0, no motion is detected
        MOV     r0, #1               ; Motion detected, set return value to true (1)
        B       end
no_motion:
        MOV     r0, #0               ; No motion detected, set return value to false (0)
end:
        POP     {PC}                 ; return
        .endasmfunc


