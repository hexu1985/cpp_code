	.file	"ptr_vs_ref.cpp"
	.local	_ZStL8__ioinit
	.comm	_ZStL8__ioinit,1,1
	.text
	.globl	_Z8test_ptrP4Test
	.type	_Z8test_ptrP4Test, @function
_Z8test_ptrP4Test:
.LFB1023:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$16, %esp
	movl	$0, -4(%ebp)
	movl	8(%ebp), %eax
	movl	(%eax), %eax
	addl	%eax, -4(%ebp)
	movl	8(%ebp), %eax
	movl	4(%eax), %eax
	addl	%eax, -4(%ebp)
	movl	8(%ebp), %eax
	movl	8(%eax), %eax
	addl	%eax, -4(%ebp)
	movl	8(%ebp), %eax
	movl	12(%eax), %eax
	addl	%eax, -4(%ebp)
	movl	-4(%ebp), %eax
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE1023:
	.size	_Z8test_ptrP4Test, .-_Z8test_ptrP4Test
	.globl	_Z8test_refRK4Test
	.type	_Z8test_refRK4Test, @function
_Z8test_refRK4Test:
.LFB1024:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$16, %esp
	movl	$0, -4(%ebp)
	movl	8(%ebp), %eax
	movl	(%eax), %eax
	addl	%eax, -4(%ebp)
	movl	8(%ebp), %eax
	movl	4(%eax), %eax
	addl	%eax, -4(%ebp)
	movl	8(%ebp), %eax
	movl	8(%eax), %eax
	addl	%eax, -4(%ebp)
	movl	8(%ebp), %eax
	movl	12(%eax), %eax
	addl	%eax, -4(%ebp)
	movl	-4(%ebp), %eax
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE1024:
	.size	_Z8test_refRK4Test, .-_Z8test_refRK4Test
	.globl	main
	.type	main, @function
main:
.LFB1025:
	.cfi_startproc
	leal	4(%esp), %ecx
	.cfi_def_cfa 1, 0
	andl	$-16, %esp
	pushl	-4(%ecx)
	pushl	%ebp
	.cfi_escape 0x10,0x5,0x2,0x75,0
	movl	%esp, %ebp
	pushl	%ecx
	.cfi_escape 0xf,0x3,0x75,0x7c,0x6
	subl	$36, %esp
	movl	$1, -28(%ebp)
	movl	$2, -24(%ebp)
	movl	$3, -20(%ebp)
	movl	$4, -16(%ebp)
	movl	$0, -12(%ebp)
	movl	-28(%ebp), %eax
	addl	%eax, -12(%ebp)
	movl	-24(%ebp), %eax
	addl	%eax, -12(%ebp)
	movl	-20(%ebp), %eax
	addl	%eax, -12(%ebp)
	movl	-16(%ebp), %eax
	addl	%eax, -12(%ebp)
	subl	$8, %esp
	pushl	-12(%ebp)
	pushl	$_ZSt4cout
	call	_ZNSolsEi
	addl	$16, %esp
	subl	$8, %esp
	pushl	$_ZSt4endlIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_
	pushl	%eax
	call	_ZNSolsEPFRSoS_E
	addl	$16, %esp
	subl	$12, %esp
	leal	-28(%ebp), %eax
	pushl	%eax
	call	_Z8test_ptrP4Test
	addl	$16, %esp
	addl	%eax, -12(%ebp)
	subl	$8, %esp
	pushl	-12(%ebp)
	pushl	$_ZSt4cout
	call	_ZNSolsEi
	addl	$16, %esp
	subl	$8, %esp
	pushl	$_ZSt4endlIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_
	pushl	%eax
	call	_ZNSolsEPFRSoS_E
	addl	$16, %esp
	subl	$12, %esp
	leal	-28(%ebp), %eax
	pushl	%eax
	call	_Z8test_refRK4Test
	addl	$16, %esp
	addl	%eax, -12(%ebp)
	subl	$8, %esp
	pushl	-12(%ebp)
	pushl	$_ZSt4cout
	call	_ZNSolsEi
	addl	$16, %esp
	subl	$8, %esp
	pushl	$_ZSt4endlIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_
	pushl	%eax
	call	_ZNSolsEPFRSoS_E
	addl	$16, %esp
	movl	$0, %eax
	movl	-4(%ebp), %ecx
	.cfi_def_cfa 1, 0
	leave
	.cfi_restore 5
	leal	-4(%ecx), %esp
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE1025:
	.size	main, .-main
	.type	_Z41__static_initialization_and_destruction_0ii, @function
_Z41__static_initialization_and_destruction_0ii:
.LFB1031:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$8, %esp
	cmpl	$1, 8(%ebp)
	jne	.L9
	cmpl	$65535, 12(%ebp)
	jne	.L9
	subl	$12, %esp
	pushl	$_ZStL8__ioinit
	call	_ZNSt8ios_base4InitC1Ev
	addl	$16, %esp
	subl	$4, %esp
	pushl	$__dso_handle
	pushl	$_ZStL8__ioinit
	pushl	$_ZNSt8ios_base4InitD1Ev
	call	__cxa_atexit
	addl	$16, %esp
.L9:
	nop
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE1031:
	.size	_Z41__static_initialization_and_destruction_0ii, .-_Z41__static_initialization_and_destruction_0ii
	.type	_GLOBAL__sub_I__Z8test_ptrP4Test, @function
_GLOBAL__sub_I__Z8test_ptrP4Test:
.LFB1032:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$8, %esp
	subl	$8, %esp
	pushl	$65535
	pushl	$1
	call	_Z41__static_initialization_and_destruction_0ii
	addl	$16, %esp
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE1032:
	.size	_GLOBAL__sub_I__Z8test_ptrP4Test, .-_GLOBAL__sub_I__Z8test_ptrP4Test
	.section	.init_array,"aw"
	.align 4
	.long	_GLOBAL__sub_I__Z8test_ptrP4Test
	.hidden	__dso_handle
	.ident	"GCC: (GNU) 5.2.0"
	.section	.note.GNU-stack,"",@progbits
