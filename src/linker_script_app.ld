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


        /* Debug info (kept out of loadable memory) */
    .debug_info 0 : { KEEP(*(.debug_info .debug_info.*)) }
    .debug_abbrev 0 : { KEEP(*(.debug_abbrev .debug_abbrev.*)) }
    .debug_line 0 : { KEEP(*(.debug_line .debug_line.*)) }
    .debug_line_str 0 : { KEEP(*(.debug_line_str .debug_line_str.*)) }
    .debug_str 0 : { KEEP(*(.debug_str .debug_str.*)) }
    .debug_str_offsets 0 : { KEEP(*(.debug_str_offsets .debug_str_offsets.*)) }
    .debug_addr 0 : { KEEP(*(.debug_addr .debug_addr.*)) }
    .debug_aranges 0 : { KEEP(*(.debug_aranges .debug_aranges.*)) }
    .debug_ranges 0 : { KEEP(*(.debug_ranges .debug_ranges.*)) }
    .debug_rnglists 0 : { KEEP(*(.debug_rnglists .debug_rnglists.*)) }
    .debug_loc 0 : { KEEP(*(.debug_loc .debug_loc.*)) }
    .debug_loclists 0 : { KEEP(*(.debug_loclists .debug_loclists.*)) }
    .debug_frame 0 : { KEEP(*(.debug_frame .debug_frame.*)) }
    .debug_macro 0 : { KEEP(*(.debug_macro .debug_macro.*)) }
    .debug_macinfo 0 : { KEEP(*(.debug_macinfo .debug_macinfo.*)) }
    .debug_names 0 : { KEEP(*(.debug_names .debug_names.*)) }
    .debug_pubnames 0 : { KEEP(*(.debug_pubnames .debug_pubnames.*)) }
    .debug_pubtypes 0 : { KEEP(*(.debug_pubtypes .debug_pubtypes.*)) }
    .debug_types 0 : { KEEP(*(.debug_types .debug_types.*)) }
    .debug_sup 0 : { KEEP(*(.debug_sup .debug_sup.*)) }
    .debug_cu_index 0 : { KEEP(*(.debug_cu_index .debug_cu_index.*)) }
    .debug_tu_index 0 : { KEEP(*(.debug_tu_index .debug_tu_index.*)) }
    .gdb_index 0 : { KEEP(*(.gdb_index)) }
    .debug_gdb_scripts 0 : { KEEP(*(.debug_gdb_scripts)) }

    .debug_abbrev.dwo 0 : { KEEP(*(.debug_abbrev.dwo .debug_abbrev.dwo.*)) }
    .debug_info.dwo 0 : { KEEP(*(.debug_info.dwo .debug_info.dwo.*)) }
    .debug_line.dwo 0 : { KEEP(*(.debug_line.dwo .debug_line.dwo.*)) }
    .debug_loclists.dwo 0 : { KEEP(*(.debug_loclists.dwo .debug_loclists.dwo.*)) }
    .debug_macro.dwo 0 : { KEEP(*(.debug_macro.dwo .debug_macro.dwo.*)) }
    .debug_rnglists.dwo 0 : { KEEP(*(.debug_rnglists.dwo .debug_rnglists.dwo.*)) }
    .debug_str.dwo 0 : { KEEP(*(.debug_str.dwo .debug_str.dwo.*)) }
    .debug_str_offsets.dwo 0 : { KEEP(*(.debug_str_offsets.dwo .debug_str_offsets.dwo.*)) }

    .eh_frame 0 : { KEEP(*(.eh_frame)) }
    .eh_frame_hdr 0 : { KEEP(*(.eh_frame_hdr)) }

    /DISCARD/ : 
    { 
        *(.runprgm.reloc)
        *(.comment) 
        *(.note*) 
    }
}
