;
; $Id: lib32.asm,v 1.5 2013/02/03 18:37:05 david Exp $
;
; Copyright 2006-2012 by David Martins de Matos
; Based on lib.asm (by Pedro Reis Santos, c. 2005)
;
; $Log: lib32.asm,v $
; Revision 1.5  2013/02/03 18:37:05  david
; *** empty log message ***
;
; Revision 1.4  2012/04/10 18:54:34  david
; Added return comment to _main.
;
; Revision 1.3  2012/02/18 19:39:27  david
; Minor cleanup work.
;

section .data
	$_env	dd	0

section .text
	global argc, argv, envp
	global _start, _exit, end

argc:
	mov	eax, [_env]
	mov	eax, [eax]
	ret

argv:
	mov	eax, [_env]
	add	eax, 4
	mov	ebx, [esp+4]
	lea	eax, [eax+ebx*4]
	mov	eax, [eax]
	ret

envp:
	mov	ebx, [_env]
	mov	edx, [ebx]
	lea	eax, [ebx+edx*4]
	add	eax, 8	; argc+argv
	mov	ebx, [esp+4]
	lea	eax, [eax+ebx*4]
	mov	eax, [eax]
	ret

extern	_main
_start:
	mov	[$_env], esp
	mov	eax, [esp]	     ; argc
	lea	ebx, [esp+4]	   ; argv
	lea	edx, [ebx+eax*4] ; &(argv[argc])
	add	edx, 4		       ; envp
	;; arguments to _main
	push	dword edx      ; envp
	push	dword ebx      ; argv
	push	dword eax      ; argc
	call	_main
	;; recover return value
	push	eax
	call	_exit

_exit:
	mov	ebx, [esp+4]
.L0:
	mov	eax, 1
	int	0x80
	jmp	.L0

extern	_end
end:
	mov	eax, $_end
	ret
