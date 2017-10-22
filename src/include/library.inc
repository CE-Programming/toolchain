macro library_private

	local lib
	element lib.base

	postpone
		virtual
			irpv relocation, lib.relocations
				dw relocation
			end irpv
			load lib.relocation_table: $-$$ from $$
		end virtual
	end postpone

	postpone
		lib.end = $% - lib.base_offset
		dw lib.relocation_table
		dl lib.dependencies
		dl lib.end
	end postpone

	macro library? name,version
		lib.numfunctions = 0
		org 0
		lib.init = $
		db 192,193,version
	end macro

	macro dependencies?
		irpv export, lib.exports
			dw export
		end irpv
		lib.dependencies = $
		lib.base_offset = $%
		org lib.base
	end macro

	macro export? function
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

end macro
library_private
purge library_private
