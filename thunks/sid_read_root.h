		/* <sid_read_root_key>: */
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
		htole32(0x05c2e283), /*   24:  lwu   t0,92(t0)               */
		htole32(0x00000313), /*   28:  li    t1,0                    */
		htole32(0x00000e17), /*   2c:  auipc t3,0x0                  */
		htole32(0x054e0e13), /*   30:  addi  t3,t3,84                */
		/* <sid_read_loop>: */
		htole32(0x01031393), /*   34:  slli  t2,t1,0x10              */
		htole32(0x0000beb7), /*   38:  lui   t4,0xb                  */
		htole32(0xc00e8e9b), /*   3c:  addiw t4,t4,-1024             */
		htole32(0x01d3e3b3), /*   40:  or    t2,t2,t4                */
		htole32(0x0023e393), /*   44:  ori   t2,t2,2                 */
		htole32(0x0472a023), /*   48:  sw    t2,64(t0)               */
		/* <sid_read_wait>: */
		htole32(0x0402e383), /*   4c:  lwu   t2,64(t0)               */
		htole32(0x0023fe93), /*   50:  andi  t4,t2,2                 */
		htole32(0xfe0e9ce3), /*   54:  bnez  t4,4c <sid_read_wait>   */
		htole32(0x0602e383), /*   58:  lwu   t2,96(t0)               */
		htole32(0x006e0eb3), /*   5c:  add   t4,t3,t1                */
		htole32(0x007ea023), /*   60:  sw    t2,0(t4)                */
		htole32(0x00430313), /*   64:  addi  t1,t1,4                 */
		htole32(0x01000e93), /*   68:  li    t4,16                   */
		htole32(0xfdd344e3), /*   6c:  blt   t1,t4,34 <sid_read_loop> */
		htole32(0x00000393), /*   70:  li    t2,0                    */
		htole32(0x0472a023), /*   74:  sw    t2,64(t0)               */
		htole32(0x00008067), /*   78:  ret                           */
		/* <sid_base>: */
