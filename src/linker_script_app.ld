MEMORY
{
    prgm : ORIGIN = LOAD_ADDR, LENGTH = 0x400000
    bss  : ORIGIN = BSSHEAP_LOW, LENGTH = BSSHEAP_HIGH - BSSHEAP_LOW
}

SECTIONS
{
    . = LOAD_ADDR;

    .header :
    {
        KEEP (*(.header))
        PROVIDE_HIDDEN (___icon_optional = .);
        KEEP (*(.header.icon))
    } >prgm
    
    .init :
    {
        *(.init)
    } >prgm
    
    .text :
    {
        *(.text.unlikely .text.*_unlikely .text.unlikely.*)
        *(.text.exit .text.exit.*)
        *(.text.startup .text.startup.*)
        *(.text.hot .text.hot.*)
        *(SORT(.text.sorted.*))
        *(.text .stub .text.* .gnu.linkonce.t.*)
        *(.gnu.warning)
    } >prgm
    
    .rodata :
    {
        *(.rodata .rodata.* .gnu.linkonce.r.*)
    } >prgm

    .init_array :
    {
        PROVIDE_HIDDEN (__init_array_start = .);
        KEEP (*(.preinit_array))
        KEEP (*(SORT_BY_INIT_PRIORITY(.init_array.*)))
        KEEP (*(.init_array))
        PROVIDE_HIDDEN (__init_array_end = .);
    } >prgm
    
    .fini_array :
    {
        PROVIDE_HIDDEN (__fini_array_start = .);
        KEEP (*(SORT_BY_INIT_PRIORITY(.fini_array.*)))
        KEEP (*(.fini_array))
        PROVIDE_HIDDEN (__fini_array_end = .);
    } >prgm

    .data :
    {
        ___data_vma = .;
        ___data_lma = . + (LOADADDR(.data) - ADDR(.data));
        *(.data .data.* .gnu.linkonce.d.*)
        SORT(CONSTRUCTORS)
        *(.data1)
        ___data_vma_end = .;
    } >bss AT>prgm
    ___data_len = ___data_vma_end - ___data_vma;

    .bss (NOLOAD) :
    {
        ___bss_low = .;
        *(.dynbss)
        *(.bss .bss.* .gnu.linkonce.b.*)
        *(COMMON)
        ___bss_high = .;
    } >bss :NONE
    ___bss_len = ___bss_high - ___bss_low;

    ASSERT(. <= BSSHEAP_HIGH, "Error: BSS exceed BSSHEAP_HIGH limit")

    ___heap_low = .;
    . = BSSHEAP_HIGH;
    ___heap_high = .;

    /DISCARD/ : 
    { 
        *(.runprgm.reloc)
        *(.comment) 
        *(.note*) 
    }
}
