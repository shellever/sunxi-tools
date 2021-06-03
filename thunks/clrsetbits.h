		/* <fel_clrsetbits_le32>: */
		htole32(0x00000297), /*    0:  auipc t0,0x0                  */
		htole32(0x0302e283), /*    4:  lwu   t0,48(t0)               */
		htole32(0x0002e303), /*    8:  lwu   t1,0(t0)                */
		htole32(0x00000397), /*    c:  auipc t2,0x0                  */
		htole32(0x0283e383), /*   10:  lwu   t2,40(t2)               */
		htole32(0xfff3c393), /*   14:  not   t2,t2                   */
		htole32(0x00737333), /*   18:  and   t1,t1,t2                */
		htole32(0x00000397), /*   1c:  auipc t2,0x0                  */
		htole32(0x01c3e383), /*   20:  lwu   t2,28(t2)               */
		htole32(0x0063e3b3), /*   24:  or    t2,t2,t1                */
		htole32(0x0072a023), /*   28:  sw    t2,0(t0)                */
		htole32(0x00008067), /*   2c:  ret                           */
