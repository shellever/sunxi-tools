/*
 * Copyright © 2015 Siarhei Siamashka <siarhei.siamashka@gmail.com>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice (including the next
 * paragraph) shall be included in all copies or substantial portions of the
 * Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 */

/*************************************************************************/
/* Usage instructions: "ruby -x fel-to-spl-thunk.S > fel-to-spl-thunk.h" */
/*************************************************************************/

/* Open a comment for gas.

   Do not close the comment until after the Ruby code terminator (__END__).
   Write the '*' '/' sequence of characters as "\x2a/" in string literals to
   avoid doing so.

#!/usr/bin/env ruby

def tool_exists(tool_name)
    `which #{tool_name} > /dev/null 2>&1`
    return $?.to_i == 0
end

toolchains = [
  "arm-none-eabi-",
  "arm-linux-gnueabihf-",
  "arm-none-linux-gnueabi-",
  "armv7a-hardfloat-linux-gnueabi-",
]

toolchain = toolchains.find { |toolchain| tool_exists("#{toolchain}as") }
abort "Can't find any ARM crosscompiler\n" unless toolchain

system("#{toolchain}as -o #{$PROGRAM_NAME}.o #{$PROGRAM_NAME}")
exit($?.to_i) if $?.to_i != 0

`#{toolchain}objdump -d #{$PROGRAM_NAME}.o`.each_line {|l|
    next unless l =~ /(\h+)\:\s+(\h+)\s+(\S+)\s+([^;]*)/
    printf("\t0x%s, /* %8s:    %-10s %-28s \x2a/\n", $2, $1, $3, $4.strip)
}

__END__
*/

/*************************************************************************/

#define BUF1		t0
#define	BUF2		t1
#define	TMP1		t2
#define	TMP2		t3
#define	SWAPTBL		t4
#define	FULLSIZE	t5
#define	BUFSIZE		t6
#define	CHECKSUM	a0
#define	SPL_ADDR	a1

entry_point:
	j	setup_stack

.align 3
saved_sp:
	nop
	nop

	/* A function, which walks the table and swaps all buffers */
swap_all_buffers:
	ret	/* TODO: on D1 nothing should be swapped now */

setup_stack:
	lwu	SPL_ADDR, appended_data

	/* save SP to memory */
	la	TMP1, saved_sp
	sd	sp, 0(TMP1)

	/* Reserve stack space */
	addi	sp, sp, -136

	/* save a bunch of registers according to RISC-V psABI */
	sd	ra, 0(sp)
	sd	gp, 8(sp)
	sd	tp, 16(sp)
	sd	s0, 24(sp)
	sd	s1, 32(sp)
	sd	s2, 40(sp)
	sd	s3, 48(sp)
	sd	s4, 56(sp)
	sd	s5, 64(sp)
	sd	s6, 72(sp)
	sd	s7, 80(sp)
	sd	s8, 88(sp)
	sd	s9, 96(sp)
	sd	s10, 104(sp)
	sd	s11, 112(sp)

	/* save mstatus */
	csrr	TMP1, mstatus
	sd	TMP1, 120(sp)
	
	/* save mie */
	csrr	TMP1, mie
	sd	TMP1, 128(sp)

	/* Disable IRQ */
	li	TMP1, 0
	csrs	mie, TMP1

	jal	swap_all_buffers

	/* Change 'eGON.BT0' -> 'eGON.FEL' */
	li	TMP1, (('L' << 24) + ('E' << 16) + ('F' << 8) + '.')
	sw	TMP1, 8(SPL_ADDR)

	/* Flush the cache */
	li	TMP1, 0x30013
	csrs	0x7c2, TMP1
	li	TMP2, 0x30010
wait_flush_cache:
	csrr	TMP1, 0x7c2
	and	TMP1, TMP1, TMP2
	bnez	TMP1, wait_flush_cache

	/* Call the SPL code */
	jalr	SPL_ADDR

	/* Return back to FEL */
	j	return_to_fel

return_to_fel:
	jal	swap_all_buffers
return_to_fel_noswap:
	/* load SP from memory */
	la	TMP1, saved_sp
	ld	sp, 0(TMP1)

	/* Restore reserved stack space */
	addi	sp, sp, -136

	/* reload a bunch of registers according to RISC-V psABI */
	ld	ra, 0(sp)
	ld	gp, 8(sp)
	ld	tp, 16(sp)
	ld	s0, 24(sp)
	ld	s1, 32(sp)
	ld	s2, 40(sp)
	ld	s3, 48(sp)
	ld	s4, 56(sp)
	ld	s5, 64(sp)
	ld	s6, 72(sp)
	ld	s7, 80(sp)
	ld	s8, 88(sp)
	ld	s9, 96(sp)
	ld	s10, 104(sp)
	ld	s11, 112(sp)

	/* reload mstatus */
	ld	TMP1, 120(sp)
	csrs	mstatus, TMP1
	
	/* reload mie */
	ld	TMP1, 128(sp)
	csrs	mie, TMP1

	/* reload SP from memory */
	la	TMP1, saved_sp
	ld	sp, 0(TMP1)

	ret

appended_data:
/*
 * The appended data uses the following format:
 *
 *     struct {
 *         uint32_t          spl_addr;
 *         sram_swap_buffers swaptbl[];
 *     };
 *
 * More details about the 'spl_addr' variable and the 'sram_swap_buffers'
 * struct can be found in the 'fel.c' source file.
 */
