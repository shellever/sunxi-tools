/*
 * Thunk code to assist with bitwise operations (set/clear) via FEL
 */

fel_clrsetbits_le32:
	lwu	t0, 1f		/* address */
	lwu	t1, 0(t0)	/* load value */
	lwu	t2, 2f		/* clrbits mask */
	xori	t2, t2, -1	/* revert clrbits mask */
	and	t1, t1, t2	/* clear bits (logical "and") */
	lwu	t2, 3f		/* setbits mask */
	or	t2, t2, t1	/* set bits (logical "or") */
	sw	t2, 0(t0)	/* store result */
	ret

1:	.word	0	/* addr */
2:	.word	0	/* clrbits (= bits to clear) */
3:	.word	0	/* setbits (= bits to set) */
