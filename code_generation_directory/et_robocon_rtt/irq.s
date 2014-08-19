@
@  IRQ wrappers.
@
@  These call a C function.
@  We switch to supervisor mode and reenable interrupts to allow nesting.
@
@
	.extern debug
	.extern ecrobot_debug1

	.text
	.code 32
	.align   4

@
@  Macros
@

@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
.macro	irq_wrapper_nested, C_function

	@ Save registers on stack
	sub	r14, r14, #4 @ fix up for return
	stmfd	r13!, {r14}
	mrs	r14, spsr
	stmfd	r13!, {r14}

	@ Acknowledge the IVR for debugging to support Protected Mode
	ldr	r14, =0xFFFFF100
	str	r14, [r14]

	@ swich to system mode and enable IRQ, but not FIQ
	msr	cpsr_c, #0x5F

	@push stack
	stmfd	r13!, {r0-r12,r14}

	@ Call the function
	ldr	r0, =\C_function
	mov	lr, pc
	bx	r0

	@ pop stack
	ldmfd	r13!, {r0-r12,r14}

	@ switch to interrupt mode and disable IRQs and FIQs
	msr	cpsr_c, #0xD2

	@ end of interrupt by doing a write to AIC_EOICR
	ldr	r14, =0xFFFFF130
	str	r14, [r14]

	@ unstack the saved spsr
	ldmfd	r13!, {r14}
	msr	spsr_all, r14

	@ return from interrupt (unstacking the modified r14)
	ldmfd	r13!, {pc}^

.endm

 @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
 @ The following macro, irq_wrpper_type2, is to  route the specified
 @ interrupt (isr) to the function (C_function) defined outside leJos
 @ The macro is used to link leJos to Toppers OSEK, by making the 
 @ specified handler an OSEK type2 interrupt handler
 @  
 @  The following registers temporarily store  context values
 @		R8: runisr of the interrupted context
 @		R9: sp of the interrputed context
 @		R10: callevel of the interrputed context
 @		R11: the address of the high-level (in C) interrput handler to call
 @
 @  Copyright  2007, Masaaki Mizuno (masaaki@cis.ksu.edu)
 @ 		Departmet of Computing and Information Sciences
 @  	Kansas State University
 @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ 
 .macro	irq_wrapper_type2, C_function, isr

	.align 4
	@ switch to the system stack and save destructive (r0-r3, ip) and value holding registers (r8-r11)
	msr	cpsr, #0XDF
	stmfd	sp!, {r0-r3, r8-r11,  ip, lr}
		
	@switch to the irq stack to get  spsr (in r0) and lr (in r1)
	msr	cpsr, #0xD2
	sub	r1, lr, #4	@fix up the link register value for return
	mrs	r0, spsr
		
	@switch back to the system stack and save spsr  and lr there
	msr	cpsr, #0XDF
	stmfd	sp!, {r0-r1}
	
	@ Acknowledge the IVR for debugging to support Protected Mode
	@ just following the leJos convention
	ldr	r0, =0xFFFFF100
	str	r0, [r0]

	@ save runisr in R8 and update it with the current isr value
 	ldr	r0, =runisr
 	ldrb	r8, [r0]	@ save runisr in R8
 	mov	r1, #\isr
 	strb	r1, [r0]
 
 	@ save the C_function address in r11
 	ldr	r11, =\C_function
 	b	_interrupt

.endm


@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
.macro	irq_wrapper_not_nested, C_function

	@ Save registers on stack
	sub	r14, r14, #4 @ fix up for return
	stmfd	r13!, {r0-r12,r14}

	@ Acknowledge the IVR for debugging to support Protected Mode
	ldr	r14, =0xFFFFF100
	str	r14, [r14]

	@ Call the function
	ldr	r0, =\C_function
	mov	lr, pc
	bx	r0

	@End of interrupt by doing a write to AIC_EOICR
	ldr	r14, =0xFFFFF130
	str	r14, [r14]

	@ Return from interrupt (unstacking the modified r14)
	ldmfd	r13!, {r0-r12,pc}^

.endm


@
@	ISRs
@
@
	.global spurious_isr
	.global default_isr
	.global default_fiq
default_fiq:
spurious_isr:
default_isr:
	b default_isr

	.extern systick_isr_C
	.global systick_isr_entry
systick_isr_entry:
@	irq_wrapper_nested systick_isr_C
	irq_wrapper_type2  systick_isr_C 1
 
@	.extern systick_low_priority_C
	.extern systick_isr_C1
	.global systick_low_priority_entry
systick_low_priority_entry:
@	irq_wrapper_nested systick_low_priority_C
	irq_wrapper_type2 systick_isr_C1 2

	.extern udp_isr_C
	.global udp_isr_entry
udp_isr_entry:
@	irq_wrapper_nested udp_isr_C
	irq_wrapper_type2 udp_isr_C 3

	.extern spi_isr_C
	.global spi_isr_entry
spi_isr_entry:
@	irq_wrapper_nested spi_isr_C
	irq_wrapper_type2 spi_isr_C 4

	.extern twi_isr_C
	.global twi_isr_entry
twi_isr_entry:
@	irq_wrapper_nested twi_isr_C
  	irq_wrapper_type2 twi_isr_C 5
  	
  	.extern sound_isr_C
  	.global sound_isr_entry
sound_isr_entry:
@	irq_wrapper_nested sound_isr_C
	irq_wrapper_type2 sound_isr_C 6

  	.extern uart_isr_C_0
  	.global uart_isr_entry_0
uart_isr_entry_0:
@	irq_wrapper_nested uart_isr_C_0
	irq_wrapper_type2 uart_isr_C_0 7

	.extern uart_isr_C_1
	.global uart_isr_entry_1
uart_isr_entry_1:
@	irq_wrapper_nested uart_isr_C_1
	irq_wrapper_type2 uart_isr_C_1 8

	.extern nxt_motor_isr_C
	.global nxt_motor_isr_entry
nxt_motor_isr_entry:
@	irq_wrapper_nested nxt_motor_isr_C
	irq_wrapper_type2 nxt_motor_isr_C 9
	
	.extern i2c_timer_isr_C
	.global i2c_timer_isr_entry
i2c_timer_isr_entry:
@	irq_wrapper_nested i2c_timer_isr_C
	irq_wrapper_type2 i2c_timer_isr_C 10


