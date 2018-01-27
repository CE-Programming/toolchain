include 'ez80.inc'
include 'ti84pceg.inc'
include 'tiformat.inc'

macro library? name*,version*

	local lib
	element lib.base

	macro dependencies?
		irpv export, lib.exports
			dw export
		end irpv
		lib.dependencies = $
		lib.base_offset = $%
		org lib.base
	end macro

	macro export? function*
		lib.exports equ function-lib.base
		lib.numfunctions = lib.numfunctions + 1
	end macro

	macro @ez80.word @value*
		local value, address
		value = @value
		address = $
		if value relativeto lib.base
			lib.relocations equ address-lib.base
			@ez80.word value-lib.base
		else
			@ez80.word value
		end if
	end macro

	format ti archived appvar name
	lib.numfunctions = 0
	org 0
	lib.init = $
	db 192,193,version

	postpone
		lib.end = $% - lib.base_offset
		irpv relocation, lib.relocations
			dw relocation
		end irpv
		dl lib.dependencies
		dl lib.end

	end postpone

	purge library?
end macro
