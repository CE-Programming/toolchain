; helpful macros for working with structures

macro compare_hl_zero?
	add	hl,de
	or	a,a
	sbc	hl,de
end macro

macro compare_auhl_zero?
	compare_hl_zero
	jr	nz,$+3
	or	a,a
end macro

macro compare_hl_de?
	or	a,a
	sbc	hl,de
	add	hl,de
end macro

macro compare_bc_zero?
	push	hl
	sbc	hl,hl
	adc	hl,bc
	pop	hl
end macro

macro ?!
 macro assertpo2? value*
  local val
  val = value
  if ~val | val <> 1 shl bsr val
   err '"', `value, '" is not a power of two'
  end if
 end macro

 iterate op, bit, res, set
  macro op#msk? index*, value
   local idx, val, rest
   idx = index
   assertpo2 idx
   match @, value
    val equ value
   else
    val equ
    rest equ index
    while 1
     match car.cdr, rest
      match any, val
       val equ any.car
      else
       val equ car
      end match
      rest equ cdr
     else
      val equ (val)
      break
     end match
    end while
   end match
   match v, val
	op	bsr idx,v
   end match
  end macro
 end iterate

 macro struct? name*, parameters&
  macro end?.struct?!
    end namespace
   end struc
   iterate <base,prefix>, 0,, ix-name,x, iy-name,y
    virtual at base
	prefix#name	name
    end virtual
   end iterate
   purge end?.struct?
  end macro
  struc name parameters
   namespace .
 end macro

 ; copied from ez80.alm
 macro calminstruction?.isindirect? argument*
  unique done
  local isindirect
  match ( isindirect ), argument
  bno done
  match isindirect, isindirect, ()
  label done
 end macro

 calminstruction ld? lhs*, mhs*, rhs
  match , rhs
  jyes plain
  isindirect lhs
  jyes store
  isindirect rhs
  jno errarguments
 load:
  execute =ld? mhs, (rhs)
  check mhs metadata 1 element 1 eq @ez80.wreg
  jyes loadword
 loadbyte:
  execute =ld? lhs, (rhs + =byte?)
  exit
 loadword:
  execute =ld? lhs, (rhs + =@ez80.=ws)
  exit
 store:
  execute =ld? (lhs), rhs
  check rhs metadata 1 element 1 eq @ez80.wreg
  jyes storeword
 storebyte:
  execute =ld? (lhs + =byte?), mhs
  exit
 storeword:
  execute =ld? (lhs + =@ez80.=ws), mhs
  exit
 plain:
  execute =ld? lhs, mhs
  exit
 errarguments:
  err 'invalid arguments'
 end calminstruction

 purge calminstruction?.isindirect?

 purge ?
end macro
