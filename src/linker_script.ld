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
    ___data_low = .;
    .data :
    {
        *(.data .data.* .gnu.linkonce.d.*)
        SORT(CONSTRUCTORS)
        *(.data1)

        /* For running programs */
        ___runprgm_reloc_start = .;
        *(.runprgm.reloc)
        ___runprgm_reloc_end = .;
    } >prgm
    ___data_high = .;
    ___data_len = ___data_high - ___data_low;

    . = BSSHEAP_LOW;
    ___bss_low = .;
    .bss (NOLOAD) :
    {
        *(.dynbss)
        *(.bss .bss.* .gnu.linkonce.b.*)
        *(COMMON)
    } >bss
    ___bss_high = .;
    ___bss_len = ___bss_high - ___bss_low;

    ASSERT(. <= BSSHEAP_HIGH, "Error: BSS exceed BSSHEAP_HIGH limit")

    ___heap_low = .;
    . = BSSHEAP_HIGH;
    ___heap_high = .;

    /* For running programs */
    .runprgm 0xE30800 : AT(___runprgm_reloc_start) {
        KEEP(*(.runprgm.reloc))
    }

    /DISCARD/ : 
    { 
        *(.comment) 
        *(.note*) 
    }
}

PROVIDE(___runprgm_reloc_len = ___runprgm_reloc_end - ___runprgm_reloc_start);
