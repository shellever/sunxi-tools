/*
 * Thunk code to assist with bitwise operations (set/clear) via FEL
 */

fel_get_stackinfo:
	li	t0, 0x30013
	csrs	0x7c2, t0
	li	t1, 0x30010
wait_flush_cache:
	csrr	t0, 0x7c2
	and	t0, t0, t1
	bnez	t0, wait_flush_cache

	la	t0, 1f
	add	t1, zero, sp	/* load sp */
	sw	t1, 0(t0)
	la	t0, 2f
	csrr	t1, mscratch
	sw	t1, 0(t0)
	ret

1:	.word	0	/* sp */
2:	.word	0	/* mscratch */
