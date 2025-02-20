; Motion signal pin usage: Grove base port J16, Tiva C PC4
;******************************************************************************

; Declaring a field to store GPIO_PORTC_BASE (32-bit) in program memory

                  .cdecls "motion_h.h"


                  .text
                  .ref motion_sensor
_motion_sensor    .field motion_sensor
_GPIO_PORTC_BASE  .field  GPIO_PORTC_BASE
;******************************************************************************
; Motion Detection Function: Written by Akbar Aman
;******************************************************************************
  .global MotionDetected
.asmfunc
MotionDetected
        PUSH    {LR}                    ; Save the link register
        LDR     r1, _motion_sensor      ; Load the address of motion_sensor
        LDRB    r0, [r1, #8]            ; Load motion_sensor.new_input into r0
        CMP     r0, #0                   ; Compare r0 with 0 (no motion detected)
        BEQ     end                      ; If no motion, jump to end (return 0)

        MOV     r0, #0                   ; Prepare to reset motion_sensor.new_input
        STRB    r0, [r1, #8]             ; Reset motion_sensor.new_input to 0
        LDR     r0, [r1, #4]             ; Load motion_sensor.pin_value into r0

end
        POP     {PC}                    ; Restore the link register and return with the result in r0
.endasmfunc

