		/* <fel_memcpy_up>: */
		htole32(0x000302b7), /*    0:  lui   t0,0x30                 */
		htole32(0x0132829b), /*    4:  addiw t0,t0,19                */
		htole32(0x7c22a073), /*    8:  csrs  0x7c2,t0                */
		htole32(0x00030337), /*    c:  lui   t1,0x30                 */
		htole32(0x0103031b), /*   10:  addiw t1,t1,16                */
		/* <wait_flush_cache_up>: */
		htole32(0x7c2022f3), /*   14:  csrr  t0,0x7c2                */
		htole32(0x0062f2b3), /*   18:  and   t0,t0,t1                */
		htole32(0xfe029ce3), /*   1c:  bnez  t0,14 <wait_flush_cache_up> */
		htole32(0x00000297), /*   20:  auipc t0,0x0                  */
		htole32(0x0882a283), /*   24:  lw    t0,136(t0)              */
		htole32(0x00000317), /*   28:  auipc t1,0x0                  */
		htole32(0x08432303), /*   2c:  lw    t1,132(t1)              */
		htole32(0x00000397), /*   30:  auipc t2,0x0                  */
		htole32(0x0803a383), /*   34:  lw    t2,128(t2)              */
		htole32(0x40530e33), /*   38:  sub   t3,t1,t0                */
		htole32(0x003e7e93), /*   3c:  andi  t4,t3,3                 */
		htole32(0x040e9463), /*   40:  bnez  t4,88 <copyup_tail>     */
		/* <copyup_head>: */
		htole32(0x00337e93), /*   44:  andi  t4,t1,3                 */
		htole32(0x020e8063), /*   48:  beqz  t4,68 <copyup_loop>     */
		htole32(0x00030e03), /*   4c:  lb    t3,0(t1)                */
		htole32(0x00130313), /*   50:  addi  t1,t1,1                 */
		htole32(0x01c28023), /*   54:  sb    t3,0(t0)                */
		htole32(0x00128293), /*   58:  addi  t0,t0,1                 */
		htole32(0xfff38393), /*   5c:  addi  t2,t2,-1                */
		htole32(0xfe03d2e3), /*   60:  bgez  t2,44 <copyup_head>     */
		htole32(0x00008067), /*   64:  ret                           */
		/* <copyup_loop>: */
		htole32(0xffc38393), /*   68:  addi  t2,t2,-4                */
		htole32(0x0003cc63), /*   6c:  bltz  t2,84 <copyup_loop_end> */
		htole32(0x00032e03), /*   70:  lw    t3,0(t1)                */
		htole32(0x00430313), /*   74:  addi  t1,t1,4                 */
		htole32(0x01c2a023), /*   78:  sw    t3,0(t0)                */
		htole32(0x00428293), /*   7c:  addi  t0,t0,4                 */
		htole32(0xfe9ff06f), /*   80:  j     68 <copyup_loop>        */
		/* <copyup_loop_end>: */
		htole32(0x00438393), /*   84:  addi  t2,t2,4                 */
		/* <copyup_tail>: */
		htole32(0xfff38393), /*   88:  addi  t2,t2,-1                */
		htole32(0x0003cc63), /*   8c:  bltz  t2,a4 <copyup_ret>      */
		htole32(0x00030e03), /*   90:  lb    t3,0(t1)                */
		htole32(0x00130313), /*   94:  addi  t1,t1,1                 */
		htole32(0x01c28023), /*   98:  sb    t3,0(t0)                */
		htole32(0x00128293), /*   9c:  addi  t0,t0,1                 */
		htole32(0xfe9ff06f), /*   a0:  j     88 <copyup_tail>        */
		/* <copyup_ret>: */
		htole32(0x00008067), /*   a4:  ret                           */
		/* <fel_memcpy_down>: */
		htole32(0x000302b7), /*   b4:  lui   t0,0x30                 */
		htole32(0x0132829b), /*   b8:  addiw t0,t0,19                */
		htole32(0x7c22a073), /*   bc:  csrs  0x7c2,t0                */
		htole32(0x00030337), /*   c0:  lui   t1,0x30                 */
		htole32(0x0103031b), /*   c4:  addiw t1,t1,16                */
		/* <wait_flush_cache_down>: */
		htole32(0x7c2022f3), /*   c8:  csrr  t0,0x7c2                */
		htole32(0x0062f2b3), /*   cc:  and   t0,t0,t1                */
		htole32(0xfe029ce3), /*   d0:  bnez  t0,c8 <wait_flush_cache_down> */
		htole32(0x00000297), /*   d4:  auipc t0,0x0                  */
		htole32(0x0902a283), /*   d8:  lw    t0,144(t0)              */
		htole32(0x00000317), /*   dc:  auipc t1,0x0                  */
		htole32(0x08c32303), /*   e0:  lw    t1,140(t1)              */
		htole32(0x00000397), /*   e4:  auipc t2,0x0                  */
		htole32(0x0883a383), /*   e8:  lw    t2,136(t2)              */
		htole32(0x007282b3), /*   ec:  add   t0,t0,t2                */
		htole32(0x00730333), /*   f0:  add   t1,t1,t2                */
		htole32(0x40530e33), /*   f4:  sub   t3,t1,t0                */
		htole32(0x003e7e93), /*   f8:  andi  t4,t3,3                 */
		htole32(0x040e9463), /*   fc:  bnez  t4,144 <copydn_tail>    */
		/* <copydn_head>: */
		htole32(0x00337e93), /*  100:  andi  t4,t1,3                 */
		htole32(0x020e8063), /*  104:  beqz  t4,124 <copydn_loop>    */
		htole32(0xfff30313), /*  108:  addi  t1,t1,-1                */
		htole32(0x00030e03), /*  10c:  lb    t3,0(t1)                */
		htole32(0xfff28293), /*  110:  addi  t0,t0,-1                */
		htole32(0x01c28023), /*  114:  sb    t3,0(t0)                */
		htole32(0xfff38393), /*  118:  addi  t2,t2,-1                */
		htole32(0xfe03d2e3), /*  11c:  bgez  t2,100 <copydn_head>    */
		htole32(0x00008067), /*  120:  ret                           */
		/* <copydn_loop>: */
		htole32(0xffc38393), /*  124:  addi  t2,t2,-4                */
		htole32(0x0003cc63), /*  128:  bltz  t2,140 <copydn_loop_end> */
		htole32(0xffc30313), /*  12c:  addi  t1,t1,-4                */
		htole32(0x00032e03), /*  130:  lw    t3,0(t1)                */
		htole32(0xffc28293), /*  134:  addi  t0,t0,-4                */
		htole32(0x01c2a023), /*  138:  sw    t3,0(t0)                */
		htole32(0xfe9ff06f), /*  13c:  j     124 <copydn_loop>       */
		/* <copydn_loop_end>: */
		htole32(0x00438393), /*  140:  addi  t2,t2,4                 */
		/* <copydn_tail>: */
		htole32(0xfff38393), /*  144:  addi  t2,t2,-1                */
		htole32(0x0003cc63), /*  148:  bltz  t2,160 <copydn_ret>     */
		htole32(0xfff30313), /*  14c:  addi  t1,t1,-1                */
		htole32(0x00030e03), /*  150:  lb    t3,0(t1)                */
		htole32(0xfff28293), /*  154:  addi  t0,t0,-1                */
		htole32(0x01c28023), /*  158:  sb    t3,0(t0)                */
		htole32(0xfe9ff06f), /*  15c:  j     144 <copydn_tail>       */
		/* <copydn_ret>: */
		htole32(0x00008067), /*  160:  ret                           */
