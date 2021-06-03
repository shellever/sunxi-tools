/*
 * Thunk code for buffered 'long' (i.e. 32-bit) read and write operations
 */

.equ	MAX_WORDS, 0x100 - 26

fel_readl_n:
	li	t0, 0x30013
	csrs	0x7c2, t0
	li	t1, 0x30010
wait_flush_cache_readl:
	csrr	t0, 0x7c2
	and	t0, t0, t1
	bnez	t0, wait_flush_cache_readl

	lwu	t0, 1f	/* read_addr */
	la	t1, 3f	/* read_data */
	lwu	t2, 2f	/* read_count */
	/* limit word count to a maximum value */
	addi	t3, zero, MAX_WORDS
	ble	t2, t3, read_loop
	add	t2, zero, t3
read_loop:
	addi	t2, t2, -1
	lwu	t3, 0(t0)
	sw	t3, 0(t1)
	addi	t0, t0, 4
	addi	t1, t1, 4
	bne	t2, zero, read_loop
	ret

1:	.word	0	/* read_addr */
2:	.word	0	/* read_count */
3:	.word	0	/* read_data */

fel_writel_n:
	li	t0, 0x30013
	csrs	0x7c2, t0
	li	t1, 0x30010
wait_flush_cache_writel:
	csrr	t0, 0x7c2
	and	t0, t0, t1
	bnez	t0, wait_flush_cache_writel

	lwu	t0, 1f	/* write_addr */
	la	t1, 3f	/* write_data */
	lwu	t2, 2f	/* write_count */
	/* limit word count to a maximum value */
	addi	t3, zero, MAX_WORDS
	ble	t2, t3, write_loop
	add	t2, zero, t3
write_loop:
	addi	t2, t2, -1
	lwu	t3, 0(t1)
	sw	t3, 0(t0)
	addi	t0, t0, 4
	addi	t1, t1, 4
	bne	t2, zero, write_loop
	ret

1:	.word	0	/* write_addr */
2:	.word	0	/* write_count */
3:	.word	0	/* write_data */
