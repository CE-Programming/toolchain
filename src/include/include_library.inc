macro include_library? file*
	local usedfunc, usedlib, offset
	usedfunc = 0
	offset = 0
	macro library?! name*, version: 0
		end if
			if usedlib
				db $C0, name, 0, version
			end if
		if 0
	end macro
	iterate each, export, export_pointer
		macro each?! symbol*
			end if
				if used symbol
					usedfunc = 1
					symbol := $ + %-1
					jp offset
				end if
				offset = offset + @ez80.ws
			if 0
		end macro
	end iterate
	if 0
		esc include! file
	end if
	purge library?, export?, export_pointer?
	usedlib = usedfunc
end macro
