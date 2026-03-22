	.assume	adl=1

	.section	.rodata._NULL_ptr

	.global	_NULL_ptr
_NULL_ptr:
	db	$00, $00, $00

;-------------------------------------------------------------------------------

	.section	.text

	.global	_T_malloc
	.global	_T_calloc
	.global	_T_bzero
	.global	_T_memccpy
	.global	_T_memchr
	.global	_T_memcmp
	.global	_T_memcpy
	.global	_T_memmem
	.global	_T_memmove
	.global	_T_mempcpy
	.global	_T_memrchr
	.global	_T_memrmem
	.global	_T_memset
	.global	_T_stpcpy
	.global	_T_stpncpy
	.global	_T_strcat
	.global	_T_strchr
	.global	_T_strchrnul
	.global	_T_strcmp
	.global	_T_strcpy
	.global	_T_strlcat
	.global	_T_strlen
	.global	_T_strncat
	.global	_T_strncmp
	.global	_T_strncpy
	.global	_T_strnlen
	.global	_T_strrchr
	.global	_T_strrstr
	.global	_T_strstr
	.global	_T_strtok
	.global	_T_strtok_r

;-------------------------------------------------------------------------------

_T_malloc:
	jp	_malloc

_T_calloc:
	jp	_calloc

_T_bzero:
	jp	_bzero

_T_memccpy:
	jp	_memccpy

_T_memchr:
	jp	_memchr

_T_memcmp:
	jp	_memcmp

_T_memcpy:
	jp	_memcpy

_T_memmem:
	jp	_memmem

_T_memmove:
	jp	_memmove

_T_mempcpy:
	jp	_mempcpy

_T_memrchr:
	jp	_memrchr

_T_memrmem:
	jp	_memrmem

_T_memset:
	jp	_memset

_T_stpcpy:
	jp	_stpcpy

_T_stpncpy:
	jp	_stpncpy

_T_strcat:
	jp	_strcat

_T_strchr:
	jp	_strchr

_T_strchrnul:
	jp	_strchrnul

_T_strcmp:
	jp	_strcmp

_T_strcpy:
	jp	_strcpy

_T_strlcat:
	jp	_strlcat

_T_strlen:
	jp	_strlen

_T_strncat:
	jp	_strncat

_T_strncmp:
	jp	_strncmp

_T_strncpy:
	jp	_strncpy

_T_strnlen:
	jp	_strnlen

_T_strrchr:
	jp	_strrchr

_T_strrstr:
	jp	_strrstr

_T_strstr:
	jp	_strstr

_T_strtok:
	jp	_strtok

_T_strtok_r:
	jp	_strtok_r

;-------------------------------------------------------------------------------

	.extern	_malloc
	.extern	_calloc
	.extern	_bzero
	.extern	_memccpy
	.extern	_memchr
	.extern	_memcmp
	.extern	_memcpy
	.extern	_memmem
	.extern	_memmove
	.extern	_mempcpy
	.extern	_memrchr
	.extern	_memrmem
	.extern	_memset
	.extern	_stpcpy
	.extern	_stpncpy
	.extern	_strcat
	.extern	_strchr
	.extern	_strchrnul
	.extern	_strcmp
	.extern	_strcpy
	.extern	_strlcat
	.extern	_strlen
	.extern	_strncat
	.extern	_strncmp
	.extern	_strncpy
	.extern	_strnlen
	.extern	_strrchr
	.extern	_strrstr
	.extern	_strstr
	.extern	_strtok
	.extern	_strtok_r
