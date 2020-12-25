include 'ez80.inc'
include 'ti84pceg.inc'
include 'tiformat.inc'

macro library? name*, version*, magic: <192,193>
	local lib
	element lib.base
	virtual
		lib.exports.area::
	end virtual
	virtual as 'lib'
		lib.exports.file::
		repeat 1, string: version
			db 'library', 9, '"', name, '", ', `string, 10
		end repeat
	end virtual
	virtual
		lib.relocations.area::
	end virtual

	format ti archived appvar name
	org 0
	db magic,version
	dw lib.exports
	lib.dependencies:
	lib.base_offset := $%

	macro disable_relocations?
		org $% - lib.base_offset + lib.dependencies
	end macro
	macro enable_relocations?
		org $% - lib.base_offset + lib.base
	end macro
	enable_relocations?

	iterate each, export, export_pointer
		macro each? function*
			local offset
			virtual lib.exports.area
				dw function-lib.base
				offset = $-$$
			end virtual
			virtual lib.exports.file
				repeat 1, string: ((offset - 2) / 2) * 3
					db 9, `each, 9, `function, ' ; ', `string, 10
				end repeat
			end virtual
		end macro
	end iterate

	macro @ez80.word @size*, @value*
		local value, address
		value = @value
		address = $
		if value relativeto lib.base
			virtual lib.relocations.area
				dw address-lib.base
			end virtual
			@ez80.word @size, value-lib.base
		else
			@ez80.word @size, value
		end if
	end macro

	postpone
		virtual lib.exports.area
			load lib.exports: $-$$ from $$
		end virtual
		virtual lib.relocations.area
			load lib.relocations: $-$$ from $$
		end virtual

		lib.end_offset := $%
		dw lib.relocations
		dl lib.dependencies
		dl lib.end_offset - lib.base_offset
	end postpone

	purge library?
end macro
