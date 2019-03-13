;-------------------------------------------------------------------------------
include '../include/library.inc'
;-------------------------------------------------------------------------------

library 'FATDRVCE',0

;-------------------------------------------------------------------------------
; no dependencies
;-------------------------------------------------------------------------------

;-------------------------------------------------------------------------------
; v0 functions (not final, subject to change!)
;-------------------------------------------------------------------------------
	export fat_Init
	export fat_Deinit
	export fat_Find
	export fat_Select
	export fat_Open
	export fat_Close
	export fat_GetFileSize
	export fat_SetFileSize
	export fat_ReadSector
	export fat_WriteSector
	export fat_Tell
	export fat_Seek
	export fat_SetBuffer
	export fat_Delete
	export fat_Create
	export fat_GetAttrib
	export fat_SetAttrib
	export fat_DirList
	export msd_Init
	export msd_Find
	export msd_Select
	export msd_KeepAlive
	export msd_ReadSector
	export msd_WriteSector
	export msd_SetJmpBuf
	export msd_Deinit
;-------------------------------------------------------------------------------

include 'host.inc'
include 'msd.inc'

;-------------------------------------------------------------------------------
; Copyright (c) 2015 Steven Arnow <s@rdw.se>
; 'fat.c' - This file is part of µCFAT
;
; This software is provided 'as-is', without any express or implied
; warranty. In no event will the authors be held liable for any damages
; arising from the use of this software.
;
; Permission is granted to anyone to use this software for any purpose,
; including commercial applications, and to alter it and redistribute it
; freely, subject to the following restrictions:
;
; 	1. The origin of this software must not be misrepresented; you must not
; 	claim that you wrote the original software. If you use this software
; 	in a product, an acknowledgment in the product documentation would be
; 	appreciated but is not required.
;
; 	2. Altered source versions must be plainly marked as such, and must not be
; 	misrepresented as being the original software.
;
; 	3. This notice may not be removed or altered from any source
; 	distribution.
;-------------------------------------------------------------------------------
; (2) Notes:
; The orginal µCFAT source was used to create many of the fat functions here,
; hand-optimized for speed in some areas. Some parts of this file are direct
; algorithmic implementations of the functions available in µCFAT. µCFAT is a 
; pretty awesome library, just throwing that out there too.
;-------------------------------------------------------------------------------

struc fatstate			; fat state structure
	label .: 25
	.valid			rb 1	; valid fat state
	.cluster_size		rb 1	; size of cluster
	.root_directory_size	rw 1	; root directory size
	.clusters		rd 1	; clusters
	.fat_size		rl 1	; 
	.padding		rb 1	; 
	.fat_pos		rd 1	; 
	.root_dir_pos		rd 1	; 
	.data_region		rd 1	; 
	.type			rb 1	;
end struc
fatstate fatstate
_fat_state := fatstate

fat.partitionlba:
	db	0,0,0,0
fat.sectorbuffer:
	db	0,0,0
fat.setjmpbuf:
	db	0,0,0

_fat_fd:
	rb	94
_fat_key:
	db	0

MAX_OPEN_FD  := 3
FD_SIZE      := 23
FAT_DIR      := 16
FAT_O_WRONLY := 2
FAT_O_RDONLY := 1

;-------------------------------------------------------------------------------
fat_ReadSector:
	jp	_fat_read_sect

;-------------------------------------------------------------------------------
fat_WriteSector:
	jp	_fat_write_sect

;-------------------------------------------------------------------------------
fat_Init:
	ld	b,3				; for i < max_fd_open
	ld	hl,_fat_fd
	ld	de,23
.setkeys:
	ld	(hl),-1				; fat_fd[i].key = -1
	add	hl,de
	djnz	.setkeys
	xor	a,a
	sbc	hl,hl
	call	fat.readsectora			; readsector(0)
	ld	iy,(fat.sectorbuffer)
	ld	hl,(iy + 11)
	ld	a,h
	sub	a,512 shr 8
	or	a,l				; if sect[11] != 512
	jr	z,.validsectorsize
	ld	a,1				; return 1
	ret
.validsectorsize:
	ld	a,(iy + 13)			; fatstate.cluster_size = sect[13]
	ld	(_fat_state + 1),a
	ld	a,(iy + 16)
	cp	a,2				; if (sect[16] != 2)
	jr	z,.validfatnum
	ld	a,3				; return 3
	ret
.validfatnum:
	ld	de,(iy + 19)
	ex.s	de,hl				; if (sect[19]) (16 bits)
	add	hl,de
	or	a,a
	sbc	hl,de
	jr	z,.nobits
	ld	e,0				; fatstate.clusters = sect[19] / fatstate.cluster_size
	jr	.dodivision
.nobits:
	ld	hl,(iy + 32)
	ld	e,(iy + 35)			; fatstate.clusters = sect[32] / fatstate.cluster_size
.dodivision:
	ld	a,(iy + 13)
	ld	bc,0
	ld	c,a
	xor	a,a
	call	__ldivu
	ld	a,e
	ld	(_fat_state + 4),hl
	ld	(_fat_state + 7),a
	xor	a,a
	ld	bc,65525			; fatstate.clusters < 65525
	call	__lcmpu
	jr	nc,.fat32
.fat16:
	xor	a,a				; fatstate.type = FAT_TYPE_FAT16
	ld	c,(iy + 38)			; u8 = sect[38]
	ld	de,(iy + 22)
	ex.s	de,hl				; fatstate.fat_size = sect[22]
	jr	.fattype
.fat32:
	ld	c,(iy + 66)			; u8 = sect[66]
	ld	hl,(iy + 36)			; fatstate.fat_size = sect[36]
	ld	a,(iy + 39)
	or	a,a
	ld	a,1				; fatstate.type = FAT_TYPE_FAT32
	jr	z,.fattype			; can't support really really big drives
	inc	a				; return 2
	ret
.fattype:
	ld	(_fat_state + 24),a
	ld	a,c
	cp	a,$28				; check fat signature
	jr	z,.goodsig
	cp	a,$29
	jr	z,.goodsig
	ld	a,4				; return 4
	ret
.goodsig:
	ld	(_fat_state + 8),hl		; fatstate.fat_size
	push	hl
	xor	a,a
	ld	hl,(iy + 14)			; reserved_sectors = sect[14]
	ex.s	de,hl
	ld	(_fat_state + 12),de
	ld	(_fat_state + 15),a		; fatstate.fat_pos = reserved_sectors
	pop	hl
	push	de
	ld	e,0
	add	hl,hl
	rl	e				; euhl = fatstate.fat_size * 2
	pop	bc
	add	hl,bc
	adc	a,e
	ld	(_fat_state + 16),hl
	ld	(_fat_state + 19),a		; fatstate.root_dir_pos = fatstate.fat_pos + fatstate.fat_size * 2
	push	hl
	ld	de,(iy + 17)
	ld	hl,_fat_state + 2
	ld	(hl),e
	inc	hl
	ld	(hl),d				; fatstate.root_directory_size = sect[17] (16 bits)
	ex.s	de,hl
	srl	h
	rr	l
	srl	h
	rr	l
	srl	h
	rr	l
	srl	h
	rr	l				; fat_state.root_directory_size * 32 / 512;
	ld	e,0
	pop	bc				; fatstate.data_region = fatstate.root_dir_pos + fatstate.root_directory_size * 32 / 512;
	add	hl,bc
	adc	a,e
	ld	(_fat_state + 20),hl
	ld	(_fat_state + 23),a

	ld	a,(_fat_state + 24)		; if fat32
	or	a,a
	jp	z,.done
	ld	hl,(_fat_state + 16)
	ld	a,(_fat_state + 19)
	ld	(_fat_state + 20),hl
	ld	(_fat_state + 23),a		; fatstate.data_region = fatstate.root_dir_pos
	ld	hl,(iy + 44)
	ld	e,(iy + 47)
	xor	a,a
	ld	bc,2
	call	__lsub
	ld	a,(_fat_state + 1)
	ld	bc,0
	ld	c,a
	xor	a,a
	call	__lmulu
	ld	bc,(_fat_state + 16)
	ld	a,(_fat_state + 19)
	add	hl,bc
	adc	a,e
	ld	(_fat_state + 16),hl
	ld	(_fat_state + 19),a		; fatstate.root_dir_pos += fatstate.cluster_size * (sect[44] - 2)
	ld	de,(iy + 48)			; fsinfo = sect[48] (16 bits)
	ex.s	de,hl
	ld	(.fsinfo),hl
	xor	a,a
	call	fat.readsectora			; readsector(fsinfo)
	ld	hl,(iy + 0)			; if (sect[0] == 0x41615252 && sect[510] == 0xaa55)
	ld	e,(iy + 3)
	ld	bc,$615252
	ld	a,$41
	call	__lcmpu
	jr	nz,.done
	ld	bc,510
	lea	hl,iy
	add	hl,bc
	call	fat.checksectormagic
	jr	nz,.done
	ld	bc,488				; sect[488] = 0xffffffff
	lea	hl,iy
	add	hl,bc
	ld	a,255
	ld	(hl),a
	inc	hl
	ld	(hl),a
	inc	hl
	ld	(hl),a
	inc	hl
	ld	(hl),a
	xor	a,a
	ld	hl,0
.fsinfo := $ - 3
	call	fat.writesectora		; writesector(fsinfo)
.done:
	ld	a,1
	ld	(_fat_state + 0),a		; fatstate.valid = true
	dec	a				; return 0
	ret

;-------------------------------------------------------------------------------
fat_Deinit:
	ret

;-------------------------------------------------------------------------------
fat_Find:
	ld	iy,0
	add	iy,sp
	ld	hl,(iy + 3)			; fat_partition_t
	ld	a,(iy + 6)			; maximum partitions to locate
	ld	(fat.partitionptrs),hl
	ld	(fat.maxpartitions),a
	xor	a,a
	ld	(fat.partitionnum),a
	sbc	hl,hl
	ld	(scsiRead10Lba),hl
	ld	(scsiRead10Lba + 3),a
	call	scsiRequestDefaultRead		; read sector
	ld	hl,(xferDataPtrDefault)
	ld	de,($90 shl 16) or ($58 shl 8) or ($eb shl 0)
	or	a,a
	sbc	hl,de
   	add	hl,de				; check if boot sector
	jq	z,fat.onlypartition		; this should only happen on the first one
	call	fat.find
	ld	a,0
fat.partitionnum := $ - 1
	ret

;-------------------------------------------------------------------------------
fat_Select:
	ld	iy,0
	add	iy,sp
	ld	e,(iy + 6)
	ld	d,8
	mlt	de
	ld	hl,(iy + 3)
	add	hl,de
	ld	de,fat.partitionlba
	ld	bc,4
	ldir
;	ld	hl,fat.partitionlba
;	call	debugHexBlockHL
;	db	4
;	call    debugNewLine
	ret

;-------------------------------------------------------------------------------
fat_Open:
	jp	_fat_open

;-------------------------------------------------------------------------------
fat_Close:
	pop	de
	ex	(sp),hl
	push	de
	call	fat.findfd
	ld	(hl),-1				; fat_fd[i].key = -1;
	ret

;-------------------------------------------------------------------------------
fat_GetFileSize:
	pop	de
	ex	(sp),hl
	push	de
	call	fat.findfd
	ld	hl,(iy + 18)
	ld	e,(iy + 21)			; return fat_fd[i].file_size;
	ret

;-------------------------------------------------------------------------------
fat_SetFileSize:
	call	fat.locate
	ret	z
	ld	bc,28				; set32(sector_buff + (index * 32 + 28), size)
	add	hl,bc
	ld	bc,(iy + 6)
	ld	a,(iy + 9)
	ld	(hl),bc
	inc	hl
	inc	hl
	inc	hl
	ld	(hl),a
	jp	fat.record.write		; writesector(sector)

;-------------------------------------------------------------------------------
fat_Tell:
	pop	de
	pop	hl
	push	hl
	push	de
	call	fat.findfd
	ld	hl,(iy + 14)
	ld	e,(iy + 17)			; return fat_fd[i].fpos
	ret

;-------------------------------------------------------------------------------
fat_SetBuffer:
	pop	de
	ex	(sp),hl				; hl -> buffer
	push	de
	ld	(fat.sectorbuffer),hl
	ret

;-------------------------------------------------------------------------------
fat_Seek:
	jp  _fat_seek

;-------------------------------------------------------------------------------
fat_Delete:
	jp	_delete_file

;-------------------------------------------------------------------------------
fat_Create:
	jp	_create_file

;-------------------------------------------------------------------------------
fat_GetAttrib:
	call	fat.locate
	jr	nz,.valid
	ld	a,255
	ret
.valid:
	ld	bc,11
	add	hl,bc
	ld	a,(hl)
	ret

;-------------------------------------------------------------------------------
fat_SetAttrib:
	call	fat.locate
	ret	z
	ld	bc,11
	add	hl,bc
	ld	a,(iy + 6)
	ld	(hl),a
	jp	fat.record.write		; writesector(sector)

;-------------------------------------------------------------------------------
fat_DirList:
	jp	_fat_dirlist

;-------------------------------------------------------------------------------
fat.getentrycluster:
; return (((GET16(sector_buff + ((e) * 32 + 20)) << 16) |
;        (GET16(sector_buff + ((e) * 32 + 26)))) &
;        (fat_state.type != FAT_TYPE_FAT32 ? 0xFFFF : ~0))
	pop	de
	ex	(sp),hl
	push	de
fat.getentrycluster.asm:
	add	hl,hl
	add	hl,hl
	add	hl,hl
	add	hl,hl
	add	hl,hl
	ld	bc,(fat.sectorbuffer)
	add	hl,bc
	push	iy,hl
	pop	iy
	ld	de,(iy + 26)
	ld	(.entclus + 0),de
	ld	e,(iy + 20)
	ld	a,(iy + 21)
	pop	iy
	ld	(.entclus + 2),a
	ld	hl,0
.entclus := $ - 3
	ld	a,(_fat_state + 24)
	or	a,a
	ret	nz
.fat16:
	ld	e,0
	ex.s	de,hl
	ex	de,hl
	ret

;-------------------------------------------------------------------------------
fat.locate:
	ld	iy,3
	add	iy,sp
	push	iy
	or	a,a
	sbc	hl,hl
	ld	de,.index
	ld	bc,(iy + 3)
	push	hl,de,bc
	call	_locate_record
	pop	bc,bc,bc
	call	__lcmpzero			; if (!(sector = locate_record(path,&index,null)))
	pop	iy
	ret	z
	ld	a,e
	ld	(fat.record.sector.low),hl
	ld	(fat.record.sector.high),a
	call	fat.readsector
	ld	hl,0
.index := $ - 3
	add	hl,hl
	add	hl,hl
	add	hl,hl
	add	hl,hl
	add	hl,hl
	ld	bc,(fat.sectorbuffer)		; return sector_buffer[(index << 5) + 11];
	add	hl,bc
	xor	a,a
	inc	a
	ret
fat.record.write:
	ld	hl,0
fat.record.sector.low := $ - 3
	ld	a,0
fat.record.sector.high := $ - 1
	jp	fat.writesectora		; writesector(sector)

;-------------------------------------------------------------------------------
fat.cluster2sector:
	pop	de
	pop	hl
	dec	sp
	pop	af
	dec	sp
	dec	sp
	push	hl
	push	de
	ld	de,-2
	add	hl,de
	adc	a,d
	ld	c,a
	ld	a,(_fat_state + 1)
	jr	c,enter
	sbc	hl,hl
	ld	e,l
	ret
loop:
	add	hl,hl
	rl	c
enter:
	rrca
	jr	nc,loop
	ld	de,(_fat_state + 20)
	ld	a,(_fat_state + 20 + 3)
	add	hl,de
	adc	a,c
	ld	e,a
	ret

;-------------------------------------------------------------------------------
fat.sector2cluster:
; return (sector - fat_state.data_region) / fat_state.cluster_size + 2
; this isn't really a critical routine
	ld	iy,0
	add	iy,sp
	ld	hl,(iy + 3)
	ld	e,(iy + 6)
	call	__lcmpzero
	ret	z
	ld	bc,(_fat_state + 20)
	ld	a,(_fat_state + 23)
	call	__lsub
	ld	bc,0
	ld	a,(_fat_state + 1)
	ld	c,a
	xor	a,a
	call	__ldivu
	xor	a,a
	ld	bc,2
	add	hl,bc
	adc	a,e
	ld	e,a
	ret

;-------------------------------------------------------------------------------
fat.doallocentry:
	ld	iy,0
	add	iy,sp
	xor	a,a
	ld	l,(iy + 15)
	ld	h,a
	push	hl
	ld	hl,(iy + 12)
	push	hl
	ld	l,(iy + 9)
	ld	h,a
	push	hl
	ld	l,(iy + 6)
	push	hl
	ld	hl,(iy + 3)
	push	hl
	call	fat.alloc_cluster
	pop	bc, bc, bc, bc, bc
	push	de, hl
	call	fat.cluster2sector	; sector = cluster_to_sector(alloc_cluster(entry_sector, entry_index, prev_cluster))
	pop	bc, bc
	ld	iy,(fat.sectorbuffer)
	ld	(iy +  0),$e5
	ld	(iy + 11),$00
	ld	(iy + 32),$00
	ld	(iy + 43),$00
	push	hl,de
	call	fat.writesectora	; write_sector(sector, sector_buff)
	pop	de,hl			; return sector
	ret

;-------------------------------------------------------------------------------
fat.fname2fatname:
	ld	iy,0
	add	iy,sp
	ld	de,(iy + 3)		; de = name
	ld	hl,(iy + 6)		; hl = fname
	ld	b,0			; for (i = 0; i < 8 && name[i] != '.' && name[i]; i++)
.loop1:
	ld	a,b
	cp	a,8
	jr	nc,.done1
	ld	a,(de)
	cp	a,46			; '.'
	jr	z,.done1
	ld	a,(de)
	or	a,a
	jr	z,.done1
	ld	(hl),a
	inc	de			; i++
	inc	hl
	inc	b
	jr	.loop1
.done1:
	ld	a,b			; if (i < 8 && name[i])
	cp	a,8
	jr	nc,.elseif
	ld	a,(de)
	or	a,a
	jr	z,.elseif

	ld	a,8			; for (j = i; j < 8; j++)
.loop2:
	cp	a,b
	jr	z,.fillremaining
	ld	(hl),32		; fname[j] = ' ';
	inc	hl
	inc	b
	jr	.loop2
.fillremaining:
	inc	de			; i++;

.loop3456:				; for (; j < 11 && name[i]; j++,i++)
	ld	a,b
	cp	a,11
	ret	nc
	ld	a,(de)
	or	a,a
	jr	z,.other
	inc	de
.store:
	ld	(hl),a			; fname[j] = name[i];
	inc	hl
	inc	b
	jr	.loop3456
.other:
	ld	a,32			; ' '
	jr	.store

.elseif:
	ld	a,b			; else if (i == 8 && name[i] == '.')
	cp	a,8
	jr	nz,.spacefill
	ld	a,(de)
	cp	a,46			; '.'
	jr	nz,.spacefill
	jr	.fillremaining

.spacefill:
	ld	a,11
.spacefillloop:				; for (; j < 11; j++)
	cp	a,b
	ret	z
	ld	(hl),32		; fname[j] = ' '
	inc	hl
	inc	b
	jr	.spacefillloop

;-------------------------------------------------------------------------------
fat.nextcluster:
	ld	hl,3
	add	hl,sp
	ld	a,(_fat_state + 24)
	or	a,a
	ld	a,(hl)
	inc	hl
	ld	hl,(hl)
	jr	z,.fat16.1
	add	a,a
	adc	hl,hl
.fat16.1:
	ex	de,hl
	sbc	hl,hl
	ld	l,a
	add	hl,hl
	push	hl
	ld	hl,(_fat_state + 12)
	add	hl,de
	ld	a,(_fat_state + 12 + 3)
	ld	e,a
	call	fat.readsector
	pop	de
	ld	hl,(fat.sectorbuffer)
	add	hl,de
	ld	a,(_fat_state + 24)
	or	a,a
	jr	z,.fat16.2
	ld	de,(hl)
	inc	hl
	inc	hl
	inc	hl
	ld	a,(hl)
	and	a,$0f
	ld	hl,8
	add	hl,de
	ex	de,hl
	ld	e,a
	adc	a,$f0
	ret	nc
	ld	e,a
	ex	de,hl
	ld	e,a
	ret

.fat16.2:
	ld	e,(hl)
	inc	hl
	ld	d,(hl)
	ld	hl,$ff0008
	add	hl,de
	ex	de,hl
	ld	e,a
	ret	nc
	ex	de,hl
	ld	e,a
	ret

;-------------------------------------------------------------------------------
fat.endofchainmark:
	pop	de
	pop	hl
	pop	bc
	push	bc
	push	hl
	push	de
	ld	de,8
	ld	a,(_fat_state + 24)
	or	a,a
	jr	nz,.fat32
	add.s	hl,de
	sbc	a,a
	ret
.fat32:
	add	hl,de
	ld	a,c
	adc	a,$f0
	sbc	a,a
	ret

;-------------------------------------------------------------------------------
fat.findfd:
	ld	a,l
	or	a,a
	jp	p,.valid
.ret0:
	pop	de			; pop return
	xor	a,a
	sbc	hl,hl			; if (fd < 0) return 0;
	ld	e,0
	ret
.valid:
	ld	b,3			; for (i = 0; i < max_fd_open; i++)
	ld	hl,_fat_fd
	ld	de,23
.find:
	cp	a,(hl)			; if (fat_fd[i].key == fd)
	jr	z,.found
	add	hl,de
	djnz	.find
	jr	.ret0
.found:
	push	hl
	pop	iy
	ret

;-------------------------------------------------------------------------------
; auhl = sector lba
fat.readsectora:
	ld	e,a
;	jr	fat.readsector

;-------------------------------------------------------------------------------
; euhl = sector lba
fat.readsector:
	ld	bc,scsiRead10Lba
	call	fat.addpartitionlba
	ld	de,(fat.sectorbuffer)
	jp	scsiRequestRead

;-------------------------------------------------------------------------------
; auhl = sector lba
fat.writesectora:
	ld	e,a
;	jr	fat.writesector

;-------------------------------------------------------------------------------
; euhl = sector lba
fat.writesector:
	ld	bc,scsiWrite10Lba
	call	fat.addpartitionlba
	ld	de,(fat.sectorbuffer)
	jp	scsiRequestWrite

;-------------------------------------------------------------------------------
_fat_ReadSector:
	ld	iy,0
	add	iy,sp
	ld	de,(iy + 3)
	push	de
	ld	hl,(iy + 6)
	ld	e,(iy + 9)
	ld	bc,scsiRead10Lba
	call	fat.addpartitionlba
;	call	debugStr
;	db	'rd ',0
;	ld	hl,scsiRead10Lba
;	call	debugHexBlockHL
;	db	4
;	call    debugNewLine
	pop	de
	call	scsiRequestRead
	xor	a,a
	ret

;-------------------------------------------------------------------------------
_fat_WriteSector:
	ld	iy,0
	add	iy,sp
	ld	de,(iy + 3)
	push	de
	ld	hl,(iy + 6)
	ld	e,(iy + 9)
	ld	bc,scsiWrite10Lba
	call	fat.addpartitionlba
;	call	debugStr
;	db	'wr ',0
;	ld	hl,scsiWrite10Lba
;	call	debugHexBlockHL
;	db	4
;	call    debugNewLine
	pop	de
	call	scsiRequestWrite
	xor	a,a
	ret

;-------------------------------------------------------------------------------
fat.addpartitionlba:
	push	bc
	ld	bc,(fat.partitionlba)
	ld	a,(fat.partitionlba + 3)
	add	hl,bc			; __ladd
	adc	a,e			; big endian
	pop	de
	ld	(de),a
	dec	sp
	push	hl
	inc	sp
	pop	af			; hlu
	inc	de
	ld	(de),a
	ld	a,h
	inc	de
	ld	(de),a
	ld	a,l
	inc	de
	ld	(de),a
	ret

;-------------------------------------------------------------------------------
fat.find:
	call	scsiRequestDefaultRead		; read sector
	call	fat.checkdefaultmagic
	ret	nz
	ld	hl,-64
	add	hl,sp
	ld	sp,hl
	ex	de,hl
	ld	hl,xferDataPtrDefault + 446 + 4
	ld	bc,64
	ldir					; copy the current partition table to the stack
	xor	a,a
	sbc	hl,hl
	add	hl,sp
	ld	a,4
.loop:
	push	af
	push	hl
	ld	a,(hl)
;	call	debugHexA
	cp	a,$0b				; fat32 partition?
	call	z,fat.found
	cp	a,$0c				; fat32 partition?
	call	z,fat.found
	cp	a,$0f				; extended partition?
	call	z,ebr.found
	cp	a,$05				; extended partition? (chs)
	call	z,ebr.found
	pop	hl
	ld	bc,16
	add	hl,bc

;	push	hl
;	call	debugStr
;	db	'next loop',0
;	call	debugNewLine
;	ld	a,200
;	call	_DelayTenTimesAms
;	pop	hl

	pop	af
	dec	a
	jr	nz,.loop
;	call	debugStr
;	db	'exited loop.',0
;	call	debugNewLine
	ld	hl,64
	add	hl,sp
	ld	sp,hl
	ret

;-------------------------------------------------------------------------------
fat.onlypartition:
	call	fat.checkdefaultmagic
	ld	a,0
	ret	nz
	inc	a
	ld	(fat.partitionnum),a
	ld	hl,(fat.partitionptrs)
	push	hl
	pop	de
	ld	(hl),0
	ld	bc,7
	inc	de
	ldir
	ret

;-------------------------------------------------------------------------------
fat.found:
	push	af
;	call	debugStr
;	db	'found fat',0
;	call	debugNewLine
	ld	a,(fat.partitionnum)
	cp	a,0
fat.maxpartitions := $ - 1
	jr	z,.found_max
	ld	bc,4				; hl -> end of lba
	add	hl,bc
	push	hl
	ld	c,8
	ld	de,0
fat.partitionptrs := $ - 3
	ldir
	ld	(fat.partitionptrs),de
	pop	hl
	ld	de,scsiRead10Lba + 3
	call	util.revcopy
;	call	scsiRequestDefaultRead		; read sector
;	ld	hl,xferDataPtrDefault
;	call	debugHexBlockHL
;	db	16
;	call	debugNewLine

.found_max:
	ld	hl,fat.partitionnum
	inc	(hl)
	pop	af
	ret

;-------------------------------------------------------------------------------
ebr.found:
	push	af
;	call	debugStr
;	db	'found ebr',0
;	call	debugNewLine
	ld	bc,4				; hl -> end of lba
	add	hl,bc
	ld	de,scsiRead10Lba + 3
	call	util.revcopy
	call	fat.find			; recursively locate fat32 partitions
	pop	af
	ret

;-------------------------------------------------------------------------------
util.revcopy:
	ld	b,4
.copy:
	ld	a,(hl)
	ld	(de),a
	inc	hl
	dec	de
	djnz	.copy
	ret

;-------------------------------------------------------------------------------
fat.checkdefaultmagic:
	ld	hl,xferDataPtrDefault + 510	; offset = signature
fat.checksectormagic:
	ld	a,(hl)
	cp	a,$55
	ret	nz
	inc	hl
	ld	a,(hl)
	cp	a,$aa
	ret

include 'fat.zds'

