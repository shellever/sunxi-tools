/*
 * Copyright (C) 2021 Icenowy Zheng <icenowy@aosc.io>
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

/*
 * ARM thunk code to read the SID root key using register-based access.
 *
 * This is necessary for certain SoCs (e.g. H3), as the values read via
 * memory mapping might not be consistent. For background information see
 * https://groups.google.com/forum/#!topic/linux-sunxi/ynyIP8c61Qs
 */

#define SID_BASE	t0
#define SID_KEY_INDEX	t1

#define SID_PRCTL	0x40	/* SID program/read control register */
#define SID_PRKEY	0x50	/* SID program key value register */
#define SID_RDKEY	0x60	/* SID read key value register */

#define SID_OP_LOCK	0xAC	/* Efuse operation lock value */
#define SID_READ_START	(1 << 1) /* bit 1 of SID_PRCTL, Software Read Start */
#define SID_PG_START	(1 << 0) /* bit 0 of SID_PRCTL, Software Program Start */

sid_read_root_key:
	li	t0, 0x30013
	csrs	0x7c2, t0
	li	t1, 0x30010
wait_flush_cache:
	csrr	t0, 0x7c2
	and	t0, t0, t1
	bnez	t0, wait_flush_cache

	lwu	SID_BASE, sid_base
	li	SID_KEY_INDEX, 0
	la	t3, sid_result			/* result pointer */
sid_read_loop:
	slli	t2, SID_KEY_INDEX, 16		/* PG_INDEX value */
	li	t4, (SID_OP_LOCK << 8)
	or	t2, t2, t4			/* OP_LOCK to enable SID_READ_START */
	ori	t2, t2, SID_READ_START
	sw	t2, SID_PRCTL(SID_BASE)		/* write SID_PRCTL */
sid_read_wait:
	lwu	t2, SID_PRCTL(SID_BASE)		/* read SID_PRCTL */
	andi	t4, t2, SID_READ_START		/* check if read operation completed */
	bnez	t4, sid_read_wait		/* loop while bit 1 still set */

	lwu	t2, SID_RDKEY(SID_BASE)		/* read SID key value */
	add	t4, t3, SID_KEY_INDEX
	sw	t2, 0(t4)			/* store SID value */

	addi	SID_KEY_INDEX, SID_KEY_INDEX, 4
	li	t4, 16
	blt	SID_KEY_INDEX, t4, sid_read_loop /* loop while (SID_KEY_INDEX < 0x10) */

	li	t2, 0
	sw	t2, SID_PRCTL(SID_BASE)		/* clear SID_PRCTL */
	ret

sid_base:	.word 0
sid_result:	.word 0 /* receives the four "root key" 32-bit words */
		.word 0
		.word 0
		.word 0
