tokend	macro	ch
	defb	(ch << 1) | 1
	endm

toklet	macro	ch
	defb	ch << 1
	endm

token	macro	str
	local	prev
	prev = 0
	irpc	x,str
		if '&x' == '"'
			if prev > 0
				tokend	prev
			endif
		else
			if prev > 0
				toklet	prev
			endif
			if '&x' == ';'
				prev = 39
			else
				prev = '&x'
			endif
		endif
	endm
	endm
