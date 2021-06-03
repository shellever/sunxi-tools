/*
 * copy "upwards", increasing destination and source addresses
 */
fel_memcpy_up:
	li	t0, 0x30013
	csrs	0x7c2, t0
	li	t1, 0x30010
wait_flush_cache_up:
	csrr	t0, 0x7c2
	and	t0, t0, t1
	bnez	t0, wait_flush_cache_up

	lw	t0, 1f		/* dst_addr */
	lw	t1, 2f		/* src_addr */
	lw	t2, 3f		/* bytes */
	sub	t3, t1, t0
	andi	t4, t3, 3	/* test LSB for word alignment */
	bnez	t4, copyup_tail	/* unaligned access, copy byte-wise */
copyup_head:
	andi	t4, t1, 3	/* word boundary? */
	beqz	t4, copyup_loop
	lb	t3, 0(t1)	/* load */
	addi	t1, t1, 1	/* post-inc */
	sb	t3, 0(t0)	/* store */
	addi	t0, t0, 1	/* post-inc */
	addi	t2, t2, -1	/* t2 -= 1 */
	bgez	t2, copyup_head
	ret			/* early return on small byte count (t2 < 0) */
copyup_loop:
	addi	t2, t2, -4	/* t2 -= 4 */
	bltz	t2, copyup_loop_end /* while t2 >= 0 */
	lw	t3, 0(t1)	/* load */
	addi	t1, t1, 4	/* post-inc */
	sw	t3, 0(t0)	/* store */
	addi	t0, t0, 4	/* post-inc */
	j	copyup_loop
copyup_loop_end:
	addi	t2, t2, 4	/* t2 = remaining byte count */
copyup_tail:
	addi	t2, t2, -1	/* t2 -= 1 */
	bltz	t2, copyup_ret	/* return on (t2 < 0) */
	lb	t3, 0(t1)	/* load */
	addi	t1, t1, 1	/* post-inc */
	sb	t3, 0(t0)	/* store */
	addi	t0, t0, 1	/* post-inc */
	j	copyup_tail
copyup_ret:
	ret

1:	.word	0	/* dst_addr */
2:	.word	0	/* src_addr */
3:	.word	0	/* bytes */

/*
 * copy "downwards", decreasing destination and source addresses
 */
fel_memcpy_down:
	li	t0, 0x30013
	csrs	0x7c2, t0
	li	t1, 0x30010
wait_flush_cache_down:
	csrr	t0, 0x7c2
	and	t0, t0, t1
	bnez	t0, wait_flush_cache_down

	lw	t0, 1f		/* dst_addr */
	lw	t1, 2f		/* src_addr */
	lw	t2, 3f		/* bytes */
	add	t0, t0, t2
	add	t1, t1, t2
	sub	t3, t1, t0
	andi	t4, t3, 3	/* test LSB for word alignment */
	bnez	t4, copydn_tail	/* unaligned access, copy byte-wise */
copydn_head:
	andi	t4, t1, 3	/* word boundary? */
	beqz	t4, copydn_loop
	addi	t1, t1, -1	/* pre-dec */
	lb	t3, 0(t1)	/* load */
	addi	t0, t0, -1	/* pre-dec */
	sb	t3, 0(t0)	/* store */
	addi	t2, t2, -1	/* t2 -= 1 */
	bgez	t2, copydn_head
	ret			/* early return on small byte count (t2 < 0) */
copydn_loop:
	addi	t2, t2, -4	/* t2 -= 4 */
	bltz	t2, copydn_loop_end /* while t2 >= 0 */
	addi	t1, t1, -4	/* pre-dec */
	lw	t3, 0(t1)	/* load */
	addi	t0, t0, -4	/* pre-dec */
	sw	t3, 0(t0)	/* store */
	j	copydn_loop
copydn_loop_end:
	addi	t2, t2, 4	/* t2 = remaining byte count */
copydn_tail:
	addi	t2, t2, -1	/* t2 -= 1 */
	bltz	t2, copydn_ret	/* return on (t2 < 0) */
	addi	t1, t1, -1	/* pre-dec */
	lb	t3, 0(t1)	/* load */
	addi	t0, t0, -1	/* pre-dec */
	sb	t3, 0(t0)	/* store */
	j	copydn_tail
copydn_ret:
	ret

1:	.word	0	/* dst_addr */
2:	.word	0	/* src_addr */
3:	.word	0	/* bytes */
