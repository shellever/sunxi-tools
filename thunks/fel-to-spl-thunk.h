	/* <entry_point>: */
	0x0140006f, /*        0:    j          14 <setup_stack>             */
	0x00000013, /*        4:    nop                                     */
	/* <saved_sp>: */
	0x00000013, /*        8:    nop                                     */
	0x00000013, /*        c:    nop                                     */
	/* <swap_all_buffers>: */
	0x00008067, /*       10:    ret                                     */
	/* <setup_stack>: */
	0x00000597, /*       14:    auipc      a1,0x0                       */
	0x1145e583, /*       18:    lwu        a1,276(a1)                   */
	0x00000397, /*       1c:    auipc      t2,0x0                       */
	0xfec38393, /*       20:    addi       t2,t2,-20                    */
	0x0023b023, /*       24:    sd         sp,0(t2)                     */
	0xf7810113, /*       28:    addi       sp,sp,-136                   */
	0x00113023, /*       2c:    sd         ra,0(sp)                     */
	0x00313423, /*       30:    sd         gp,8(sp)                     */
	0x00413823, /*       34:    sd         tp,16(sp)                    */
	0x00813c23, /*       38:    sd         s0,24(sp)                    */
	0x02913023, /*       3c:    sd         s1,32(sp)                    */
	0x03213423, /*       40:    sd         s2,40(sp)                    */
	0x03313823, /*       44:    sd         s3,48(sp)                    */
	0x03413c23, /*       48:    sd         s4,56(sp)                    */
	0x05513023, /*       4c:    sd         s5,64(sp)                    */
	0x05613423, /*       50:    sd         s6,72(sp)                    */
	0x05713823, /*       54:    sd         s7,80(sp)                    */
	0x05813c23, /*       58:    sd         s8,88(sp)                    */
	0x07913023, /*       5c:    sd         s9,96(sp)                    */
	0x07a13423, /*       60:    sd         s10,104(sp)                  */
	0x07b13823, /*       64:    sd         s11,112(sp)                  */
	0x300023f3, /*       68:    csrr       t2,mstatus                   */
	0x06713c23, /*       6c:    sd         t2,120(sp)                   */
	0x304023f3, /*       70:    csrr       t2,mie                       */
	0x08713023, /*       74:    sd         t2,128(sp)                   */
	0x00000393, /*       78:    li         t2,0                         */
	0x3043a073, /*       7c:    csrs       mie,t2                       */
	0xf91ff0ef, /*       80:    jal        ra,10 <swap_all_buffers>     */
	0x4c4543b7, /*       84:    lui        t2,0x4c454                   */
	0x62e3839b, /*       88:    addiw      t2,t2,1582                   */
	0x0075a423, /*       8c:    sw         t2,8(a1)                     */
	0x000303b7, /*       90:    lui        t2,0x30                      */
	0x0133839b, /*       94:    addiw      t2,t2,19                     */
	0x7c23a073, /*       98:    csrs       0x7c2,t2                     */
	0x00030e37, /*       9c:    lui        t3,0x30                      */
	0x010e0e1b, /*       a0:    addiw      t3,t3,16                     */
	/* <wait_flush_cache>: */
	0x7c2023f3, /*       a4:    csrr       t2,0x7c2                     */
	0x01c3f3b3, /*       a8:    and        t2,t2,t3                     */
	0xfe039ce3, /*       ac:    bnez       t2,a4 <wait_flush_cache>     */
	0x000580e7, /*       b0:    jalr       a1                           */
	0x0040006f, /*       b4:    j          b8 <return_to_fel>           */
	/* <return_to_fel>: */
	0xf59ff0ef, /*       b8:    jal        ra,10 <swap_all_buffers>     */
	/* <return_to_fel_noswap>: */
	0x00000397, /*       bc:    auipc      t2,0x0                       */
	0xf4c38393, /*       c0:    addi       t2,t2,-180                   */
	0x0003b103, /*       c4:    ld         sp,0(t2)                     */
	0xf7810113, /*       c8:    addi       sp,sp,-136                   */
	0x00013083, /*       cc:    ld         ra,0(sp)                     */
	0x00813183, /*       d0:    ld         gp,8(sp)                     */
	0x01013203, /*       d4:    ld         tp,16(sp)                    */
	0x01813403, /*       d8:    ld         s0,24(sp)                    */
	0x02013483, /*       dc:    ld         s1,32(sp)                    */
	0x02813903, /*       e0:    ld         s2,40(sp)                    */
	0x03013983, /*       e4:    ld         s3,48(sp)                    */
	0x03813a03, /*       e8:    ld         s4,56(sp)                    */
	0x04013a83, /*       ec:    ld         s5,64(sp)                    */
	0x04813b03, /*       f0:    ld         s6,72(sp)                    */
	0x05013b83, /*       f4:    ld         s7,80(sp)                    */
	0x05813c03, /*       f8:    ld         s8,88(sp)                    */
	0x06013c83, /*       fc:    ld         s9,96(sp)                    */
	0x06813d03, /*      100:    ld         s10,104(sp)                  */
	0x07013d83, /*      104:    ld         s11,112(sp)                  */
	0x07813383, /*      108:    ld         t2,120(sp)                   */
	0x3003a073, /*      10c:    csrs       mstatus,t2                   */
	0x08013383, /*      110:    ld         t2,128(sp)                   */
	0x3043a073, /*      114:    csrs       mie,t2                       */
	0x00000397, /*      118:    auipc      t2,0x0                       */
	0xef038393, /*      11c:    addi       t2,t2,-272                   */
	0x0003b103, /*      120:    ld         sp,0(t2)                     */
	0x00008067, /*      124:    ret                                     */
