	.globl	_Z8test_refRK4Test
	.type	_Z8test_refRK4Test, @function
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

