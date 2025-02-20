;
; clockupdate.asm: ECE 266 Lab 3 Starter code, fall 2024
;
; Assembly code for updating the 7-seg to show a running clock.
;
; Created by Zhao Zhang
; Edited by Akbar Aman and David Mendoza

; include C header file
        .cdecls "clockupdate.h"
        .text

; Declaration fields (pointers) to seg7 and ClockUpdate
_seg7           .field  seg7
_ClockUpdate    .field  ClockUpdate

;************************************************************************************
; Task 1: Update the clock
;
; C prototype: void ClockUpdate(uint32_t time)
;
; This is the ClockUpdate callback function in assembly. It replaces the
; same function in your lab2_main.c.
;
; This is the STARTER CODE. At this time it only flashes the colon of the 7-seg.
; Complete the code so that it updates all the four clock digits.
;************************************************************************************
        .global ClockUpdate
        .asmfunc
ClockUpdate     
        PUSH    {LR, r0}        	; push return the address and the event

        ; check seg7.colon_on and turn it on/off
        LDR     r0, _seg7           ; load the address of seg7 to register r0
        LDRB    r1, [r0, #4]        ; r1 = seg7.colon_on
        CMP     r1, #0              ; compare register r1 and 0
        BEQ     turn_on_colon       ; if the colon is turned off, jump to the code turning it on
        MOVS    r1, #0              ; now the colon must have been turned on, so turn it off!
        STRB    r1, [r0, #4]        ; store 0 to seg7.colon_on
        B       update_seg7_and_return   ; jump to return

turn_on_colon
        MOV     r1, #1              ; r1 = 1
        STRB    r1, [r0, #4]        ; store 1 to seg7.colon_on

        ;**************************************************************
        ; YOUR CODE STARTS HERE
        ;**************************************************************
		;increment digit 0
		LDRB	r1, [r0, #0]		;loads the value of r0 into r1
		ADD		r1, #1				;adds 1 to r1
		STRB 	r1, [r0, #0]		;stores the updated value of r1 into r0
		CMP		r1, #10				;compares the value of r1 to 10
		BNE		update_seg7_and_return;updates seg7 if r1 is not equal to 10
		MOV 	r1, #0				;moves r1 to 0 again
		STRB	r1, [r0, #0]		;stores 0 back into r0

		;increment digit 1
		LDRB	r1, [r0, #1]		;loads the value of r0+1 into r1
		ADD 	r1, #1				;adds 1 to r1
		STRB	r1, [r0, #1]		;stores the updated value of r1 into r0+1
		CMP		r1, #6				;compares the value of r1 to 6
		BNE		update_seg7_and_return;updates seg7 if r1 is not equal to 6
		MOV		r1, #0				;moves r1 to 0 again
		STRB	r1, [r0, #1]		;stores 0 back into r0

		;increment digit 2
		LDRB	r1, [r0, #2]		;loads the value of r0+2 into r1
		ADD 	r1, #1				;adds 1 to r1
		STRB	r1, [r0, #2]		;stores the updated value of r1 into r0+2
		CMP		r1, #10				;compares the value of r1 to 10
		BNE		update_seg7_and_return;updates seg7 if r1 is not equal to 6
		MOV		r1, #0				;moves r1 to 0 again
		STRB	r1, [r0, #2]		;stores 0 back into r0

		;increment digit 3
		LDRB	r1, [r0, #3]		;loads the value of r0+3 into r1
		ADD 	r1, #1				;adds 1 to r1
		STRB	r1, [r0, #3]		;stores the updated value of r1 into r0+3
		CMP		r1, #6				;compares the value of r1 to 6
		BNE		update_seg7_and_return;updates seg7 if r1 is not equal to 6
		MOV		r1, #0				;moves r1 to 0 again
		STRB	r1, [r0, #3]		;stores 0 back into r0


        ;**************************************************************
        ; YOUR CODE ENDS HERE
        ;**************************************************************

update_seg7_and_return
        ; Physically update the 7-seg
        ;    Call Seg7Update(&seg)
        BL      Seg7Update          ; note that r0 = &seg7 at this time

        ; Schedule a callback after 0.5 seconds:
        ;   Call ScheduleCallback(event, event->time + 500);
        POP     {r0}                ; restore event and time
        LDR     r1, [r0, #8]        ; r1 = event->time
        ADD     r1, #500            ; time += 500
        BL      EventSchedule

        POP     {PC}                ; return
        .end
