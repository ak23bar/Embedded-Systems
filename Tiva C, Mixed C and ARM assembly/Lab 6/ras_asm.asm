; ras_asm.asm
; Lab 6 Bonus, ECE 266, Fall 2024
;
; Assembly code for the Rotary Angle Sensor ISR
;******************************************************************************

 ; To include names declared in C
        .cdecls "ras.h"

		; Reference to RA_sensor in ras.c, with the
		; following data structure:
		; typedef struct {
    	;	  Event *callback_event;
    	;     uint32_t raw_data;
    	;     bool new_input;
    	; } RotaryAngleState;

             .text
             .ref RA_sensor
_RA_sensor   .field RA_sensor
_ADC0_BASE   .field ADC0_BASE

;******************************************************************************
; Edited by: James Patel, Akbar Aman, and David Mendoza
;******************************************************************************

RASSensorISR
.asmfunc

        PUSH   {LR}                 ; Save the link register

        ; Read the ADC data
        ; Call ADCSequenceDataGet(ADC0_BASE, 1 /* sequencer */, &RA_sensor.raw_data /* pointer to data buffer */);

        LDR    r0, _ADC0_BASE       ; Load the address of ADC0_BASE into r0
        MOV    r1, #1;
        LDR    r2, _RA_sensor       ; Load the address of RA_sensor into r2
        ADD	   r2, r2, #4;
        BL     ADCSequenceDataGet   ; Call ADCSequenceDataGet function

        ; Set the flag for new data ready
        ; RA_sensor.new_input = true;

        LDR    r0, _RA_sensor       ; Load the address of RA_sensor into r0
        MOV    r1, #1;
        STRB   r1, [r0, #8];

        ; Schedule a data processing event
        ; Call EventSchedule(RA_sensor.callback_event, EventGetCurrentTime());

        BL	   EventGetCurrentTime  ; Call EventGetCurrentTime function to get the current time
        MOV	   r1, r0;
        LDR	   r0, _RA_sensor       ; Load the address of RA_sensor into r0
        LDR	   r0, [r0];
        BL	   EventSchedule;       ; Call EventSchedule function


        ; Call ADCIntClear(ADC0_BASE, 1 /* sequencer */);

        LDR    r0, _ADC0_BASE;      ; Load the address of ADC0_BASE into r0
        MOV    r1, #1;
        BL     ADCIntClear          ; Call ADCIntClear function

        pop    {pc}
        .endasmfunc
