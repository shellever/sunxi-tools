		/* <fel_get_stackinfo>: */
		htole32(0x000302b7), /*    0:  lui   t0,0x30                 */
		htole32(0x0132829b), /*    4:  addiw t0,t0,19                */
		htole32(0x7c22a073), /*    8:  csrs  0x7c2,t0                */
		htole32(0x00030337), /*    c:  lui   t1,0x30                 */
		htole32(0x0103031b), /*   10:  addiw t1,t1,16                */
		/* <wait_flush_cache>: */
		htole32(0x7c2022f3), /*   14:  csrr  t0,0x7c2                */
		htole32(0x0062f2b3), /*   18:  and   t0,t0,t1                */
		htole32(0xfe029ce3), /*   1c:  bnez  t0,14 <wait_flush_cache> */
		htole32(0x00000297), /*   20:  auipc t0,0x0                  */
		htole32(0x02428293), /*   24:  addi  t0,t0,36                */
		htole32(0x00200333), /*   28:  add   t1,zero,sp              */
		htole32(0x0062a023), /*   2c:  sw    t1,0(t0)                */
		htole32(0x00000297), /*   30:  auipc t0,0x0                  */
		htole32(0x01828293), /*   34:  addi  t0,t0,24                */
		htole32(0x34002373), /*   38:  csrr  t1,mscratch             */
		htole32(0x0062a023), /*   3c:  sw    t1,0(t0)                */
		htole32(0x00008067), /*   40:  ret                           */
