/*
 * Copyright (c) 2018 Leon Urbas <leon.urbas@tu-dresden.de>
 * Copyright (c) 2019 Chris Iatrou <chris_paul.iatrou@tu-dresden.de>
 *
 * Hiermit wird unentgeltlich jeder Person, die eine Kopie der
 * Software und der zugehörigen Dokumentationen (die "Software")
 * erhält, die Erlaubnis erteilt, sie uneingeschränkt zu nutzen,
 * inklusive und ohne Ausnahme mit dem Recht, sie zu verwenden,
 * zu kopieren, zu verändern, zusammenzufügen, zu veröffentlichen,
 * zu verbreiten, zu unterlizenzieren und/oder zu verkaufen, und
 * Personen, denen diese Software überlassen wird, diese Rechte
 * zu verschaffen, unter den folgenden Bedingungen:
 *
 * Der obige Urheberrechtsvermerk und dieser Erlaubnisvermerk
 * sind in allen Kopien oder Teilkopien der Software beizulegen.
 *
 * DIE SOFTWARE WIRD OHNE JEDE AUSDRÜCKLICHE ODER IMPLIZIERTE
 * GARANTIE BEREITGESTELLT, EINSCHLIEẞLICH DER GARANTIE ZUR
 * BENUTZUNG FÜR DEN VORGESEHENEN ODER EINEM BESTIMMTEN ZWECK
 * SOWIE JEGLICHER RECHTSVERLETZUNG, JEDOCH NICHT DARAUF
 * BESCHRÄNKT. IN KEINEM FALL SIND DIE AUTOREN ODER
 * COPYRIGHTINHABER FÜR JEGLICHEN SCHADEN ODER SONSTIGE
 * ANSPRÜCHE HAFTBAR ZU MACHEN, OB INFOLGE DER ERFÜLLUNG EINES
 * VERTRAGES, EINES DELIKTES ODER ANDERS IM ZUSAMMENHANG MIT
 * DER SOFTWARE ODER SONSTIGER VERWENDUNG DER SOFTWARE ENTSTANDEN.
 */

.equ BCM2836_SPI0_BASEOFFSET, 0x204000
.equ BCM2836_SPI1_BASEOFFSET, 0x215000
.equ BCM2836_SPI2_BASEOFFSET, 0x215080

.equ BCM2836_SPI0_CS_OFFSET,   0x00 // SPI Master Control and Status
.equ BCM2836_SPI0_FIFO_OFFSET, 0x04 // SPI Master TX and RX FIFOs
.equ BCM2836_SPI0_CLK_OFFSET,  0x08 // SPI Master Clock Divider
.equ BCM2836_SPI0_DLEN_OFFSET, 0x0c // SPI Master Data Length
.equ BCM2836_SPI0_LTOH_OFFSET, 0x10 // SPI LOSSI mode TOH
.equ BCM2836_SPI0_DC_OFFSET,   0x14 // SPI DMA DREQ Controls

.equ BCM2836_SPI0_CS_LEN_LONG, 0x02000000 // Enable Long data word in Lossi mode if DMA_LEN is set
.equ BCM2836_SPI0_CS_DMA_LEN,  0x01000000 // Enable DMA mode in Lossi mode
.equ BCM2836_SPI0_CS_CSPOL2,   0x00800000 // Chip Select 2 Polarity
.equ BCM2836_SPI0_CS_CSPOL1,   0x00400000 // Chip Select 1 Polarity
.equ BCM2836_SPI0_CS_CSPOL0,   0x00200000 // Chip Select 0 Polarity
.equ BCM2836_SPI0_CS_RXF, 	   0x00100000 // RXF - RX FIFO Full
.equ BCM2836_SPI0_CS_RXR,      0x00080000 // RXR RX FIFO needs Reading (full)
.equ BCM2836_SPI0_CS_TXD,      0x00040000 // TXD TX FIFO can accept Data
.equ BCM2836_SPI0_CS_RXD,      0x00020000 // RXD RX FIFO contains Data


.equ BCM2836_SPI0_CS_DONE,     0x00010000 // Done transfer Done
.equ BCM2836_SPI0_CS_TE_EN,    0x00008000 // Unused
.equ BCM2836_SPI0_CS_LMONO,    0x00004000 // Unused
.equ BCM2836_SPI0_CS_LEN,      0x00002000 // LEN LoSSI enable
.equ BCM2836_SPI0_CS_REN,      0x00001000 // REN Read Enable
.equ BCM2836_SPI0_CS_ADCS,     0x00000800 // ADCS Automatically Deassert Chip Select
.equ BCM2836_SPI0_CS_INTR,     0x00000400 // INTR Interrupt on RXR
.equ BCM2836_SPI0_CS_INTD,     0x00000200 // INTD Interrupt on Done
.equ BCM2836_SPI0_CS_DMAEN,    0x00000100 // DMAEN DMA Enable
.equ BCM2836_SPI0_CS_TA,       0x00000080 // Transfer Active
.equ BCM2836_SPI0_CS_CSPOL,    0x00000040 // Chip Select Polarity
.equ BCM2836_SPI0_CS_CLEAR,    0x00000030 // Clear FIFO Clear RX and TX
.equ BCM2836_SPI0_CS_CLEAR_RX, 0x00000020 // Clear FIFO Clear RX
.equ BCM2836_SPI0_CS_CLEAR_TX, 0x00000010 // Clear FIFO Clear TX
.equ BCM2836_SPI0_CS_CPOL,     0x00000008 // Clock Polarity
.equ BCM2836_SPI0_CS_CPHA,     0x00000004 // Clock Phase
.equ BCM2836_SPI0_CS_CS,       0x00000003 // Chip Select

// Aliases, a bit more descriptive
.equ BCM2836_SPI0_CS_TXD_FIFO_FULL, BCM2836_SPI0_CS_TXD
.equ BCM2836_SPI0_CS_RXD_FIFO_NOTEMPTY, BCM2836_SPI0_CS_RXD
