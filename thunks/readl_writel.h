		/* <fel_readl_n>: */
		htole32(0x000302b7), /*    0:  lui   t0,0x30                 */
		htole32(0x0132829b), /*    4:  addiw t0,t0,19                */
		htole32(0x7c22a073), /*    8:  csrs  0x7c2,t0                */
		htole32(0x00030337), /*    c:  lui   t1,0x30                 */
		htole32(0x0103031b), /*   10:  addiw t1,t1,16                */
		/* <wait_flush_cache_readl>: */
		htole32(0x7c2022f3), /*   14:  csrr  t0,0x7c2                */
		htole32(0x0062f2b3), /*   18:  and   t0,t0,t1                */
		htole32(0xfe029ce3), /*   1c:  bnez  t0,14 <wait_flush_cache_readl> */
		htole32(0x00000297), /*   20:  auipc t0,0x0                  */
		htole32(0x0402e283), /*   24:  lwu   t0,64(t0)               */
		htole32(0x00000317), /*   28:  auipc t1,0x0                  */
		htole32(0x04030313), /*   2c:  addi  t1,t1,64                */
		htole32(0x00000397), /*   30:  auipc t2,0x0                  */
		htole32(0x0343e383), /*   34:  lwu   t2,52(t2)               */
		htole32(0x0e600e13), /*   38:  li    t3,230                  */
		htole32(0x007e5463), /*   3c:  bge   t3,t2,44 <read_loop>    */
		htole32(0x01c003b3), /*   40:  add   t2,zero,t3              */
		/* <read_loop>: */
		htole32(0xfff38393), /*   44:  addi  t2,t2,-1                */
		htole32(0x0002ee03), /*   48:  lwu   t3,0(t0)                */
		htole32(0x01c32023), /*   4c:  sw    t3,0(t1)                */
		htole32(0x00428293), /*   50:  addi  t0,t0,4                 */
		htole32(0x00430313), /*   54:  addi  t1,t1,4                 */
		htole32(0xfe0396e3), /*   58:  bnez  t2,44 <read_loop>       */
		htole32(0x00008067), /*   5c:  ret                           */
		/* <fel_writel_n>: */
		htole32(0x000302b7), /*   6c:  lui   t0,0x30                 */
		htole32(0x0132829b), /*   70:  addiw t0,t0,19                */
		htole32(0x7c22a073), /*   74:  csrs  0x7c2,t0                */
		htole32(0x00030337), /*   78:  lui   t1,0x30                 */
		htole32(0x0103031b), /*   7c:  addiw t1,t1,16                */
		/* <wait_flush_cache_writel>: */
		htole32(0x7c2022f3), /*   80:  csrr  t0,0x7c2                */
		htole32(0x0062f2b3), /*   84:  and   t0,t0,t1                */
		htole32(0xfe029ce3), /*   88:  bnez  t0,80 <wait_flush_cache_writel> */
		htole32(0x00000297), /*   8c:  auipc t0,0x0                  */
		htole32(0x0402e283), /*   90:  lwu   t0,64(t0)               */
		htole32(0x00000317), /*   94:  auipc t1,0x0                  */
		htole32(0x04030313), /*   98:  addi  t1,t1,64                */
		htole32(0x00000397), /*   9c:  auipc t2,0x0                  */
		htole32(0x0343e383), /*   a0:  lwu   t2,52(t2)               */
		htole32(0x0e600e13), /*   a4:  li    t3,230                  */
		htole32(0x007e5463), /*   a8:  bge   t3,t2,b0 <write_loop>   */
		htole32(0x01c003b3), /*   ac:  add   t2,zero,t3              */
		/* <write_loop>: */
		htole32(0xfff38393), /*   b0:  addi  t2,t2,-1                */
		htole32(0x00036e03), /*   b4:  lwu   t3,0(t1)                */
		htole32(0x01c2a023), /*   b8:  sw    t3,0(t0)                */
		htole32(0x00428293), /*   bc:  addi  t0,t0,4                 */
		htole32(0x00430313), /*   c0:  addi  t1,t1,4                 */
		htole32(0xfe0396e3), /*   c4:  bnez  t2,b0 <write_loop>      */
		htole32(0x00008067), /*   c8:  ret                           */
