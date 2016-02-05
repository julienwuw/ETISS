
code.bin:     file format elf32-littlearm


Disassembly of section .init:

00008000 <_init>:
    8000:	b5f8      	push	{r3, r4, r5, r6, r7, lr}
    8002:	46c0      	nop			; (mov r8, r8)
    8004:	bcf8      	pop	{r3, r4, r5, r6, r7}
    8006:	bc08      	pop	{r3}
    8008:	469e      	mov	lr, r3
    800a:	4770      	bx	lr

Disassembly of section .text:

0000800c <exit>:
    800c:	b510      	push	{r4, lr}
    800e:	2100      	movs	r1, #0
    8010:	1c04      	adds	r4, r0, #0
    8012:	f000 f935 	bl	8280 <__call_exitprocs>
    8016:	4b04      	ldr	r3, [pc, #16]	; (8028 <exit+0x1c>)
    8018:	6818      	ldr	r0, [r3, #0]
    801a:	6bc3      	ldr	r3, [r0, #60]	; 0x3c
    801c:	2b00      	cmp	r3, #0
    801e:	d000      	beq.n	8022 <exit+0x16>
    8020:	4798      	blx	r3
    8022:	1c20      	adds	r0, r4, #0
    8024:	f000 fa3c 	bl	84a0 <_exit>
    8028:	000084b4 			; <UNDEFINED> instruction: 0x000084b4

0000802c <register_fini>:
    802c:	b508      	push	{r3, lr}
    802e:	4b03      	ldr	r3, [pc, #12]	; (803c <register_fini+0x10>)
    8030:	2b00      	cmp	r3, #0
    8032:	d002      	beq.n	803a <register_fini+0xe>
    8034:	4802      	ldr	r0, [pc, #8]	; (8040 <register_fini+0x14>)
    8036:	f000 f9a7 	bl	8388 <atexit>
    803a:	bd08      	pop	{r3, pc}
    803c:	00000000 	andeq	r0, r0, r0
    8040:	00008399 	muleq	r0, r9, r3

00008044 <__do_global_dtors_aux>:
    8044:	b510      	push	{r4, lr}
    8046:	4c06      	ldr	r4, [pc, #24]	; (8060 <__do_global_dtors_aux+0x1c>)
    8048:	7823      	ldrb	r3, [r4, #0]
    804a:	2b00      	cmp	r3, #0
    804c:	d107      	bne.n	805e <__do_global_dtors_aux+0x1a>
    804e:	4b05      	ldr	r3, [pc, #20]	; (8064 <__do_global_dtors_aux+0x20>)
    8050:	2b00      	cmp	r3, #0
    8052:	d002      	beq.n	805a <__do_global_dtors_aux+0x16>
    8054:	4804      	ldr	r0, [pc, #16]	; (8068 <__do_global_dtors_aux+0x24>)
    8056:	e000      	b.n	805a <__do_global_dtors_aux+0x16>
    8058:	bf00      	nop
    805a:	2301      	movs	r3, #1
    805c:	7023      	strb	r3, [r4, #0]
    805e:	bd10      	pop	{r4, pc}
    8060:	0001090c 	andeq	r0, r1, ip, lsl #18
    8064:	00000000 	andeq	r0, r0, r0
    8068:	000084c0 	andeq	r8, r0, r0, asr #9

0000806c <frame_dummy>:
    806c:	b508      	push	{r3, lr}
    806e:	4b08      	ldr	r3, [pc, #32]	; (8090 <frame_dummy+0x24>)
    8070:	2b00      	cmp	r3, #0
    8072:	d003      	beq.n	807c <frame_dummy+0x10>
    8074:	4807      	ldr	r0, [pc, #28]	; (8094 <frame_dummy+0x28>)
    8076:	4908      	ldr	r1, [pc, #32]	; (8098 <frame_dummy+0x2c>)
    8078:	e000      	b.n	807c <frame_dummy+0x10>
    807a:	bf00      	nop
    807c:	4807      	ldr	r0, [pc, #28]	; (809c <frame_dummy+0x30>)
    807e:	6803      	ldr	r3, [r0, #0]
    8080:	2b00      	cmp	r3, #0
    8082:	d100      	bne.n	8086 <frame_dummy+0x1a>
    8084:	bd08      	pop	{r3, pc}
    8086:	4b06      	ldr	r3, [pc, #24]	; (80a0 <frame_dummy+0x34>)
    8088:	2b00      	cmp	r3, #0
    808a:	d0fb      	beq.n	8084 <frame_dummy+0x18>
    808c:	4798      	blx	r3
    808e:	e7f9      	b.n	8084 <frame_dummy+0x18>
    8090:	00000000 	andeq	r0, r0, r0
    8094:	000084c0 	andeq	r8, r0, r0, asr #9
    8098:	00010910 	andeq	r0, r1, r0, lsl r9
    809c:	000104d0 	ldrdeq	r0, [r1], -r0	; <UNPREDICTABLE>
    80a0:	00000000 	andeq	r0, r0, r0

000080a4 <_mainCRTStartup>:
    80a4:	4b16      	ldr	r3, [pc, #88]	; (8100 <_mainCRTStartup+0x5c>)
    80a6:	2b00      	cmp	r3, #0
    80a8:	d100      	bne.n	80ac <_mainCRTStartup+0x8>
    80aa:	4b14      	ldr	r3, [pc, #80]	; (80fc <_mainCRTStartup+0x58>)
    80ac:	469d      	mov	sp, r3
    80ae:	2240      	movs	r2, #64	; 0x40
    80b0:	0292      	lsls	r2, r2, #10
    80b2:	1a9a      	subs	r2, r3, r2
    80b4:	4692      	mov	sl, r2
    80b6:	2100      	movs	r1, #0
    80b8:	468b      	mov	fp, r1
    80ba:	460f      	mov	r7, r1
    80bc:	4813      	ldr	r0, [pc, #76]	; (810c <_mainCRTStartup+0x68>)
    80be:	4a14      	ldr	r2, [pc, #80]	; (8110 <_mainCRTStartup+0x6c>)
    80c0:	1a12      	subs	r2, r2, r0
    80c2:	f000 f897 	bl	81f4 <memset>
    80c6:	4b0f      	ldr	r3, [pc, #60]	; (8104 <_mainCRTStartup+0x60>)
    80c8:	2b00      	cmp	r3, #0
    80ca:	d000      	beq.n	80ce <_mainCRTStartup+0x2a>
    80cc:	4798      	blx	r3
    80ce:	4b0e      	ldr	r3, [pc, #56]	; (8108 <_mainCRTStartup+0x64>)
    80d0:	2b00      	cmp	r3, #0
    80d2:	d000      	beq.n	80d6 <_mainCRTStartup+0x32>
    80d4:	4798      	blx	r3
    80d6:	2000      	movs	r0, #0
    80d8:	2100      	movs	r1, #0
    80da:	0004      	movs	r4, r0
    80dc:	000d      	movs	r5, r1
    80de:	480d      	ldr	r0, [pc, #52]	; (8114 <_mainCRTStartup+0x70>)
    80e0:	2800      	cmp	r0, #0
    80e2:	d002      	beq.n	80ea <_mainCRTStartup+0x46>
    80e4:	480c      	ldr	r0, [pc, #48]	; (8118 <_mainCRTStartup+0x74>)
    80e6:	f000 f94f 	bl	8388 <atexit>
    80ea:	f000 f85f 	bl	81ac <__libc_init_array>
    80ee:	0020      	movs	r0, r4
    80f0:	0029      	movs	r1, r5
    80f2:	f000 f847 	bl	8184 <main>
    80f6:	f7ff ff89 	bl	800c <exit>
    80fa:	46c0      	nop			; (mov r8, r8)
    80fc:	00080000 	andeq	r0, r8, r0
	...
    810c:	0001090c 	andeq	r0, r1, ip, lsl #18
    8110:	00010928 	andeq	r0, r1, r8, lsr #18
    8114:	00008389 	andeq	r8, r0, r9, lsl #7
    8118:	00008399 	muleq	r0, r9, r3

0000811c <isqrt2>:
    811c:	b580      	push	{r7, lr}
    811e:	b086      	sub	sp, #24
    8120:	af00      	add	r7, sp, #0
    8122:	6078      	str	r0, [r7, #4]
    8124:	687b      	ldr	r3, [r7, #4]
    8126:	2b00      	cmp	r3, #0
    8128:	da01      	bge.n	812e <isqrt2+0x12>
    812a:	2300      	movs	r3, #0
    812c:	e025      	b.n	817a <isqrt2+0x5e>
    812e:	2380      	movs	r3, #128	; 0x80
    8130:	05db      	lsls	r3, r3, #23
    8132:	617b      	str	r3, [r7, #20]
    8134:	687b      	ldr	r3, [r7, #4]
    8136:	613b      	str	r3, [r7, #16]
    8138:	2300      	movs	r3, #0
    813a:	60fb      	str	r3, [r7, #12]
    813c:	e019      	b.n	8172 <isqrt2+0x56>
    813e:	697a      	ldr	r2, [r7, #20]
    8140:	68fb      	ldr	r3, [r7, #12]
    8142:	431a      	orrs	r2, r3
    8144:	693b      	ldr	r3, [r7, #16]
    8146:	429a      	cmp	r2, r3
    8148:	d80d      	bhi.n	8166 <isqrt2+0x4a>
    814a:	697a      	ldr	r2, [r7, #20]
    814c:	68fb      	ldr	r3, [r7, #12]
    814e:	4313      	orrs	r3, r2
    8150:	693a      	ldr	r2, [r7, #16]
    8152:	1ad3      	subs	r3, r2, r3
    8154:	613b      	str	r3, [r7, #16]
    8156:	68fb      	ldr	r3, [r7, #12]
    8158:	085b      	lsrs	r3, r3, #1
    815a:	60fb      	str	r3, [r7, #12]
    815c:	68fa      	ldr	r2, [r7, #12]
    815e:	697b      	ldr	r3, [r7, #20]
    8160:	4313      	orrs	r3, r2
    8162:	60fb      	str	r3, [r7, #12]
    8164:	e002      	b.n	816c <isqrt2+0x50>
    8166:	68fb      	ldr	r3, [r7, #12]
    8168:	085b      	lsrs	r3, r3, #1
    816a:	60fb      	str	r3, [r7, #12]
    816c:	697b      	ldr	r3, [r7, #20]
    816e:	089b      	lsrs	r3, r3, #2
    8170:	617b      	str	r3, [r7, #20]
    8172:	697b      	ldr	r3, [r7, #20]
    8174:	2b00      	cmp	r3, #0
    8176:	d1e2      	bne.n	813e <isqrt2+0x22>
    8178:	68fb      	ldr	r3, [r7, #12]
    817a:	1c18      	adds	r0, r3, #0
    817c:	46bd      	mov	sp, r7
    817e:	b006      	add	sp, #24
    8180:	bd80      	pop	{r7, pc}
    8182:	46c0      	nop			; (mov r8, r8)

00008184 <main>:
    8184:	b580      	push	{r7, lr}
    8186:	b082      	sub	sp, #8
    8188:	af00      	add	r7, sp, #0
    818a:	2000      	movs	r0, #0
    818c:	f7ff ffc6 	bl	811c <isqrt2>
    8190:	1c03      	adds	r3, r0, #0
    8192:	607b      	str	r3, [r7, #4]
    8194:	2380      	movs	r3, #128	; 0x80
    8196:	061b      	lsls	r3, r3, #24
    8198:	603b      	str	r3, [r7, #0]
    819a:	683b      	ldr	r3, [r7, #0]
    819c:	687a      	ldr	r2, [r7, #4]
    819e:	601a      	str	r2, [r3, #0]
    81a0:	687b      	ldr	r3, [r7, #4]
    81a2:	1c18      	adds	r0, r3, #0
    81a4:	46bd      	mov	sp, r7
    81a6:	b002      	add	sp, #8
    81a8:	bd80      	pop	{r7, pc}
    81aa:	46c0      	nop			; (mov r8, r8)

000081ac <__libc_init_array>:
    81ac:	b570      	push	{r4, r5, r6, lr}
    81ae:	4e0d      	ldr	r6, [pc, #52]	; (81e4 <__libc_init_array+0x38>)
    81b0:	4d0d      	ldr	r5, [pc, #52]	; (81e8 <__libc_init_array+0x3c>)
    81b2:	2400      	movs	r4, #0
    81b4:	1bad      	subs	r5, r5, r6
    81b6:	10ad      	asrs	r5, r5, #2
    81b8:	d005      	beq.n	81c6 <__libc_init_array+0x1a>
    81ba:	00a3      	lsls	r3, r4, #2
    81bc:	58f3      	ldr	r3, [r6, r3]
    81be:	3401      	adds	r4, #1
    81c0:	4798      	blx	r3
    81c2:	42a5      	cmp	r5, r4
    81c4:	d1f9      	bne.n	81ba <__libc_init_array+0xe>
    81c6:	f7ff ff1b 	bl	8000 <_init>
    81ca:	4e08      	ldr	r6, [pc, #32]	; (81ec <__libc_init_array+0x40>)
    81cc:	4d08      	ldr	r5, [pc, #32]	; (81f0 <__libc_init_array+0x44>)
    81ce:	2400      	movs	r4, #0
    81d0:	1bad      	subs	r5, r5, r6
    81d2:	10ad      	asrs	r5, r5, #2
    81d4:	d005      	beq.n	81e2 <__libc_init_array+0x36>
    81d6:	00a3      	lsls	r3, r4, #2
    81d8:	58f3      	ldr	r3, [r6, r3]
    81da:	3401      	adds	r4, #1
    81dc:	4798      	blx	r3
    81de:	42a5      	cmp	r5, r4
    81e0:	d1f9      	bne.n	81d6 <__libc_init_array+0x2a>
    81e2:	bd70      	pop	{r4, r5, r6, pc}
    81e4:	000104c4 	andeq	r0, r1, r4, asr #9
    81e8:	000104c4 	andeq	r0, r1, r4, asr #9
    81ec:	000104c4 	andeq	r0, r1, r4, asr #9
    81f0:	000104cc 	andeq	r0, r1, ip, asr #9

000081f4 <memset>:
    81f4:	b570      	push	{r4, r5, r6, lr}
    81f6:	0783      	lsls	r3, r0, #30
    81f8:	d03f      	beq.n	827a <memset+0x86>
    81fa:	1e54      	subs	r4, r2, #1
    81fc:	2a00      	cmp	r2, #0
    81fe:	d03b      	beq.n	8278 <memset+0x84>
    8200:	b2ce      	uxtb	r6, r1
    8202:	1c03      	adds	r3, r0, #0
    8204:	2503      	movs	r5, #3
    8206:	e003      	b.n	8210 <memset+0x1c>
    8208:	1e62      	subs	r2, r4, #1
    820a:	2c00      	cmp	r4, #0
    820c:	d034      	beq.n	8278 <memset+0x84>
    820e:	1c14      	adds	r4, r2, #0
    8210:	3301      	adds	r3, #1
    8212:	1e5a      	subs	r2, r3, #1
    8214:	7016      	strb	r6, [r2, #0]
    8216:	422b      	tst	r3, r5
    8218:	d1f6      	bne.n	8208 <memset+0x14>
    821a:	2c03      	cmp	r4, #3
    821c:	d924      	bls.n	8268 <memset+0x74>
    821e:	25ff      	movs	r5, #255	; 0xff
    8220:	400d      	ands	r5, r1
    8222:	022a      	lsls	r2, r5, #8
    8224:	4315      	orrs	r5, r2
    8226:	042a      	lsls	r2, r5, #16
    8228:	4315      	orrs	r5, r2
    822a:	2c0f      	cmp	r4, #15
    822c:	d911      	bls.n	8252 <memset+0x5e>
    822e:	1c26      	adds	r6, r4, #0
    8230:	3e10      	subs	r6, #16
    8232:	0936      	lsrs	r6, r6, #4
    8234:	3601      	adds	r6, #1
    8236:	0136      	lsls	r6, r6, #4
    8238:	1c1a      	adds	r2, r3, #0
    823a:	199b      	adds	r3, r3, r6
    823c:	6015      	str	r5, [r2, #0]
    823e:	6055      	str	r5, [r2, #4]
    8240:	6095      	str	r5, [r2, #8]
    8242:	60d5      	str	r5, [r2, #12]
    8244:	3210      	adds	r2, #16
    8246:	4293      	cmp	r3, r2
    8248:	d1f8      	bne.n	823c <memset+0x48>
    824a:	220f      	movs	r2, #15
    824c:	4014      	ands	r4, r2
    824e:	2c03      	cmp	r4, #3
    8250:	d90a      	bls.n	8268 <memset+0x74>
    8252:	1f26      	subs	r6, r4, #4
    8254:	08b6      	lsrs	r6, r6, #2
    8256:	3601      	adds	r6, #1
    8258:	00b6      	lsls	r6, r6, #2
    825a:	1c1a      	adds	r2, r3, #0
    825c:	199b      	adds	r3, r3, r6
    825e:	c220      	stmia	r2!, {r5}
    8260:	4293      	cmp	r3, r2
    8262:	d1fc      	bne.n	825e <memset+0x6a>
    8264:	2203      	movs	r2, #3
    8266:	4014      	ands	r4, r2
    8268:	2c00      	cmp	r4, #0
    826a:	d005      	beq.n	8278 <memset+0x84>
    826c:	b2c9      	uxtb	r1, r1
    826e:	191c      	adds	r4, r3, r4
    8270:	7019      	strb	r1, [r3, #0]
    8272:	3301      	adds	r3, #1
    8274:	42a3      	cmp	r3, r4
    8276:	d1fb      	bne.n	8270 <memset+0x7c>
    8278:	bd70      	pop	{r4, r5, r6, pc}
    827a:	1c14      	adds	r4, r2, #0
    827c:	1c03      	adds	r3, r0, #0
    827e:	e7cc      	b.n	821a <memset+0x26>

00008280 <__call_exitprocs>:
    8280:	b5f0      	push	{r4, r5, r6, r7, lr}
    8282:	4656      	mov	r6, sl
    8284:	465f      	mov	r7, fp
    8286:	464d      	mov	r5, r9
    8288:	4644      	mov	r4, r8
    828a:	b4f0      	push	{r4, r5, r6, r7}
    828c:	1c0e      	adds	r6, r1, #0
    828e:	4b3c      	ldr	r3, [pc, #240]	; (8380 <__call_exitprocs+0x100>)
    8290:	b087      	sub	sp, #28
    8292:	681b      	ldr	r3, [r3, #0]
    8294:	9001      	str	r0, [sp, #4]
    8296:	9303      	str	r3, [sp, #12]
    8298:	3349      	adds	r3, #73	; 0x49
    829a:	33ff      	adds	r3, #255	; 0xff
    829c:	9304      	str	r3, [sp, #16]
    829e:	22a4      	movs	r2, #164	; 0xa4
    82a0:	9b03      	ldr	r3, [sp, #12]
    82a2:	0052      	lsls	r2, r2, #1
    82a4:	589f      	ldr	r7, [r3, r2]
    82a6:	2f00      	cmp	r7, #0
    82a8:	d04c      	beq.n	8344 <__call_exitprocs+0xc4>
    82aa:	9b04      	ldr	r3, [sp, #16]
    82ac:	4698      	mov	r8, r3
    82ae:	2300      	movs	r3, #0
    82b0:	469b      	mov	fp, r3
    82b2:	23c4      	movs	r3, #196	; 0xc4
    82b4:	005b      	lsls	r3, r3, #1
    82b6:	469c      	mov	ip, r3
    82b8:	44bc      	add	ip, r7
    82ba:	4663      	mov	r3, ip
    82bc:	9302      	str	r3, [sp, #8]
    82be:	23c6      	movs	r3, #198	; 0xc6
    82c0:	005b      	lsls	r3, r3, #1
    82c2:	469a      	mov	sl, r3
    82c4:	687c      	ldr	r4, [r7, #4]
    82c6:	44ba      	add	sl, r7
    82c8:	00a5      	lsls	r5, r4, #2
    82ca:	197d      	adds	r5, r7, r5
    82cc:	3c01      	subs	r4, #1
    82ce:	d508      	bpl.n	82e2 <__call_exitprocs+0x62>
    82d0:	e026      	b.n	8320 <__call_exitprocs+0xa0>
    82d2:	1d6b      	adds	r3, r5, #5
    82d4:	33ff      	adds	r3, #255	; 0xff
    82d6:	681b      	ldr	r3, [r3, #0]
    82d8:	42b3      	cmp	r3, r6
    82da:	d004      	beq.n	82e6 <__call_exitprocs+0x66>
    82dc:	3d04      	subs	r5, #4
    82de:	3c01      	subs	r4, #1
    82e0:	d31e      	bcc.n	8320 <__call_exitprocs+0xa0>
    82e2:	2e00      	cmp	r6, #0
    82e4:	d1f5      	bne.n	82d2 <__call_exitprocs+0x52>
    82e6:	687b      	ldr	r3, [r7, #4]
    82e8:	686a      	ldr	r2, [r5, #4]
    82ea:	3b01      	subs	r3, #1
    82ec:	42a3      	cmp	r3, r4
    82ee:	d03a      	beq.n	8366 <__call_exitprocs+0xe6>
    82f0:	465b      	mov	r3, fp
    82f2:	606b      	str	r3, [r5, #4]
    82f4:	2a00      	cmp	r2, #0
    82f6:	d0f1      	beq.n	82dc <__call_exitprocs+0x5c>
    82f8:	687b      	ldr	r3, [r7, #4]
    82fa:	9902      	ldr	r1, [sp, #8]
    82fc:	4699      	mov	r9, r3
    82fe:	2301      	movs	r3, #1
    8300:	40a3      	lsls	r3, r4
    8302:	6809      	ldr	r1, [r1, #0]
    8304:	9105      	str	r1, [sp, #20]
    8306:	4219      	tst	r1, r3
    8308:	d123      	bne.n	8352 <__call_exitprocs+0xd2>
    830a:	4790      	blx	r2
    830c:	687b      	ldr	r3, [r7, #4]
    830e:	454b      	cmp	r3, r9
    8310:	d1c5      	bne.n	829e <__call_exitprocs+0x1e>
    8312:	4643      	mov	r3, r8
    8314:	681b      	ldr	r3, [r3, #0]
    8316:	42bb      	cmp	r3, r7
    8318:	d1c1      	bne.n	829e <__call_exitprocs+0x1e>
    831a:	3d04      	subs	r5, #4
    831c:	3c01      	subs	r4, #1
    831e:	d2e0      	bcs.n	82e2 <__call_exitprocs+0x62>
    8320:	4b18      	ldr	r3, [pc, #96]	; (8384 <__call_exitprocs+0x104>)
    8322:	2b00      	cmp	r3, #0
    8324:	d00e      	beq.n	8344 <__call_exitprocs+0xc4>
    8326:	687b      	ldr	r3, [r7, #4]
    8328:	2b00      	cmp	r3, #0
    832a:	d123      	bne.n	8374 <__call_exitprocs+0xf4>
    832c:	683b      	ldr	r3, [r7, #0]
    832e:	2b00      	cmp	r3, #0
    8330:	d024      	beq.n	837c <__call_exitprocs+0xfc>
    8332:	4642      	mov	r2, r8
    8334:	1c38      	adds	r0, r7, #0
    8336:	6013      	str	r3, [r2, #0]
    8338:	e000      	b.n	833c <__call_exitprocs+0xbc>
    833a:	bf00      	nop
    833c:	4643      	mov	r3, r8
    833e:	681f      	ldr	r7, [r3, #0]
    8340:	2f00      	cmp	r7, #0
    8342:	d1b6      	bne.n	82b2 <__call_exitprocs+0x32>
    8344:	b007      	add	sp, #28
    8346:	bc3c      	pop	{r2, r3, r4, r5}
    8348:	4690      	mov	r8, r2
    834a:	4699      	mov	r9, r3
    834c:	46a2      	mov	sl, r4
    834e:	46ab      	mov	fp, r5
    8350:	bdf0      	pop	{r4, r5, r6, r7, pc}
    8352:	4651      	mov	r1, sl
    8354:	6809      	ldr	r1, [r1, #0]
    8356:	4219      	tst	r1, r3
    8358:	d107      	bne.n	836a <__call_exitprocs+0xea>
    835a:	1c2b      	adds	r3, r5, #0
    835c:	3384      	adds	r3, #132	; 0x84
    835e:	6819      	ldr	r1, [r3, #0]
    8360:	9801      	ldr	r0, [sp, #4]
    8362:	4790      	blx	r2
    8364:	e7d2      	b.n	830c <__call_exitprocs+0x8c>
    8366:	607c      	str	r4, [r7, #4]
    8368:	e7c4      	b.n	82f4 <__call_exitprocs+0x74>
    836a:	1c2b      	adds	r3, r5, #0
    836c:	3384      	adds	r3, #132	; 0x84
    836e:	6818      	ldr	r0, [r3, #0]
    8370:	4790      	blx	r2
    8372:	e7cb      	b.n	830c <__call_exitprocs+0x8c>
    8374:	683b      	ldr	r3, [r7, #0]
    8376:	46b8      	mov	r8, r7
    8378:	1c1f      	adds	r7, r3, #0
    837a:	e7e1      	b.n	8340 <__call_exitprocs+0xc0>
    837c:	2300      	movs	r3, #0
    837e:	e7fa      	b.n	8376 <__call_exitprocs+0xf6>
    8380:	000084b4 			; <UNDEFINED> instruction: 0x000084b4
    8384:	00000000 	andeq	r0, r0, r0

00008388 <atexit>:
    8388:	b508      	push	{r3, lr}
    838a:	1c01      	adds	r1, r0, #0
    838c:	2200      	movs	r2, #0
    838e:	2000      	movs	r0, #0
    8390:	2300      	movs	r3, #0
    8392:	f000 f81b 	bl	83cc <__register_exitproc>
    8396:	bd08      	pop	{r3, pc}

00008398 <__libc_fini_array>:
    8398:	b538      	push	{r3, r4, r5, lr}
    839a:	4b09      	ldr	r3, [pc, #36]	; (83c0 <__libc_fini_array+0x28>)
    839c:	4c09      	ldr	r4, [pc, #36]	; (83c4 <__libc_fini_array+0x2c>)
    839e:	1ae4      	subs	r4, r4, r3
    83a0:	10a4      	asrs	r4, r4, #2
    83a2:	d009      	beq.n	83b8 <__libc_fini_array+0x20>
    83a4:	4a08      	ldr	r2, [pc, #32]	; (83c8 <__libc_fini_array+0x30>)
    83a6:	18a5      	adds	r5, r4, r2
    83a8:	00ad      	lsls	r5, r5, #2
    83aa:	18ed      	adds	r5, r5, r3
    83ac:	682b      	ldr	r3, [r5, #0]
    83ae:	3c01      	subs	r4, #1
    83b0:	4798      	blx	r3
    83b2:	3d04      	subs	r5, #4
    83b4:	2c00      	cmp	r4, #0
    83b6:	d1f9      	bne.n	83ac <__libc_fini_array+0x14>
    83b8:	f000 f874 	bl	84a4 <_fini>
    83bc:	bd38      	pop	{r3, r4, r5, pc}
    83be:	46c0      	nop			; (mov r8, r8)
    83c0:	000104cc 	andeq	r0, r1, ip, asr #9
    83c4:	000104d0 	ldrdeq	r0, [r1], -r0	; <UNPREDICTABLE>
    83c8:	3fffffff 	svccc	0x00ffffff

000083cc <__register_exitproc>:
    83cc:	b5f8      	push	{r3, r4, r5, r6, r7, lr}
    83ce:	4644      	mov	r4, r8
    83d0:	465f      	mov	r7, fp
    83d2:	4656      	mov	r6, sl
    83d4:	464d      	mov	r5, r9
    83d6:	469b      	mov	fp, r3
    83d8:	4b2f      	ldr	r3, [pc, #188]	; (8498 <__register_exitproc+0xcc>)
    83da:	b4f0      	push	{r4, r5, r6, r7}
    83dc:	681c      	ldr	r4, [r3, #0]
    83de:	23a4      	movs	r3, #164	; 0xa4
    83e0:	005b      	lsls	r3, r3, #1
    83e2:	1c05      	adds	r5, r0, #0
    83e4:	58e0      	ldr	r0, [r4, r3]
    83e6:	1c0e      	adds	r6, r1, #0
    83e8:	4690      	mov	r8, r2
    83ea:	2800      	cmp	r0, #0
    83ec:	d04b      	beq.n	8486 <__register_exitproc+0xba>
    83ee:	6843      	ldr	r3, [r0, #4]
    83f0:	2b1f      	cmp	r3, #31
    83f2:	dc0d      	bgt.n	8410 <__register_exitproc+0x44>
    83f4:	1c5c      	adds	r4, r3, #1
    83f6:	2d00      	cmp	r5, #0
    83f8:	d121      	bne.n	843e <__register_exitproc+0x72>
    83fa:	3302      	adds	r3, #2
    83fc:	009b      	lsls	r3, r3, #2
    83fe:	6044      	str	r4, [r0, #4]
    8400:	501e      	str	r6, [r3, r0]
    8402:	2000      	movs	r0, #0
    8404:	bc3c      	pop	{r2, r3, r4, r5}
    8406:	4690      	mov	r8, r2
    8408:	4699      	mov	r9, r3
    840a:	46a2      	mov	sl, r4
    840c:	46ab      	mov	fp, r5
    840e:	bdf8      	pop	{r3, r4, r5, r6, r7, pc}
    8410:	4b22      	ldr	r3, [pc, #136]	; (849c <__register_exitproc+0xd0>)
    8412:	2b00      	cmp	r3, #0
    8414:	d03c      	beq.n	8490 <__register_exitproc+0xc4>
    8416:	20c8      	movs	r0, #200	; 0xc8
    8418:	0040      	lsls	r0, r0, #1
    841a:	e000      	b.n	841e <__register_exitproc+0x52>
    841c:	bf00      	nop
    841e:	2800      	cmp	r0, #0
    8420:	d036      	beq.n	8490 <__register_exitproc+0xc4>
    8422:	22a4      	movs	r2, #164	; 0xa4
    8424:	2300      	movs	r3, #0
    8426:	0052      	lsls	r2, r2, #1
    8428:	58a1      	ldr	r1, [r4, r2]
    842a:	6043      	str	r3, [r0, #4]
    842c:	6001      	str	r1, [r0, #0]
    842e:	50a0      	str	r0, [r4, r2]
    8430:	3240      	adds	r2, #64	; 0x40
    8432:	5083      	str	r3, [r0, r2]
    8434:	3204      	adds	r2, #4
    8436:	5083      	str	r3, [r0, r2]
    8438:	2401      	movs	r4, #1
    843a:	2d00      	cmp	r5, #0
    843c:	d0dd      	beq.n	83fa <__register_exitproc+0x2e>
    843e:	009a      	lsls	r2, r3, #2
    8440:	4691      	mov	r9, r2
    8442:	4481      	add	r9, r0
    8444:	4642      	mov	r2, r8
    8446:	2188      	movs	r1, #136	; 0x88
    8448:	464f      	mov	r7, r9
    844a:	507a      	str	r2, [r7, r1]
    844c:	22c4      	movs	r2, #196	; 0xc4
    844e:	0052      	lsls	r2, r2, #1
    8450:	4690      	mov	r8, r2
    8452:	4480      	add	r8, r0
    8454:	4642      	mov	r2, r8
    8456:	3987      	subs	r1, #135	; 0x87
    8458:	4099      	lsls	r1, r3
    845a:	6812      	ldr	r2, [r2, #0]
    845c:	468a      	mov	sl, r1
    845e:	430a      	orrs	r2, r1
    8460:	4694      	mov	ip, r2
    8462:	4642      	mov	r2, r8
    8464:	4661      	mov	r1, ip
    8466:	6011      	str	r1, [r2, #0]
    8468:	2284      	movs	r2, #132	; 0x84
    846a:	4649      	mov	r1, r9
    846c:	465f      	mov	r7, fp
    846e:	0052      	lsls	r2, r2, #1
    8470:	508f      	str	r7, [r1, r2]
    8472:	2d02      	cmp	r5, #2
    8474:	d1c1      	bne.n	83fa <__register_exitproc+0x2e>
    8476:	1c02      	adds	r2, r0, #0
    8478:	4655      	mov	r5, sl
    847a:	328d      	adds	r2, #141	; 0x8d
    847c:	32ff      	adds	r2, #255	; 0xff
    847e:	6811      	ldr	r1, [r2, #0]
    8480:	430d      	orrs	r5, r1
    8482:	6015      	str	r5, [r2, #0]
    8484:	e7b9      	b.n	83fa <__register_exitproc+0x2e>
    8486:	1c20      	adds	r0, r4, #0
    8488:	304d      	adds	r0, #77	; 0x4d
    848a:	30ff      	adds	r0, #255	; 0xff
    848c:	50e0      	str	r0, [r4, r3]
    848e:	e7ae      	b.n	83ee <__register_exitproc+0x22>
    8490:	2001      	movs	r0, #1
    8492:	4240      	negs	r0, r0
    8494:	e7b6      	b.n	8404 <__register_exitproc+0x38>
    8496:	46c0      	nop			; (mov r8, r8)
    8498:	000084b4 			; <UNDEFINED> instruction: 0x000084b4
    849c:	00000000 	andeq	r0, r0, r0

000084a0 <_exit>:
    84a0:	e7fe      	b.n	84a0 <_exit>
    84a2:	46c0      	nop			; (mov r8, r8)

Disassembly of section .fini:

000084a4 <_fini>:
    84a4:	b5f8      	push	{r3, r4, r5, r6, r7, lr}
    84a6:	46c0      	nop			; (mov r8, r8)
    84a8:	bcf8      	pop	{r3, r4, r5, r6, r7}
    84aa:	bc08      	pop	{r3}
    84ac:	469e      	mov	lr, r3
    84ae:	4770      	bx	lr

Disassembly of section .rodata:

000084b0 <_global_impure_ptr-0x4>:
    84b0:	00000043 	andeq	r0, r0, r3, asr #32

000084b4 <_global_impure_ptr>:
    84b4:	000104e0 	andeq	r0, r1, r0, ror #9

Disassembly of section .ARM.exidx:

000084b8 <.ARM.exidx>:
    84b8:	7ffffbec 	svcvc	0x00fffbec
    84bc:	00000001 	andeq	r0, r0, r1

Disassembly of section .eh_frame:

000084c0 <__EH_FRAME_BEGIN__>:
    84c0:	00000000 	andeq	r0, r0, r0

Disassembly of section .init_array:

000104c4 <__init_array_start>:
   104c4:	0000802d 	andeq	r8, r0, sp, lsr #32

000104c8 <__frame_dummy_init_array_entry>:
   104c8:	0000806d 	andeq	r8, r0, sp, rrx

Disassembly of section .fini_array:

000104cc <__do_global_dtors_aux_fini_array_entry>:
   104cc:	00008045 	andeq	r8, r0, r5, asr #32

Disassembly of section .jcr:

000104d0 <__JCR_END__>:
   104d0:	00000000 	andeq	r0, r0, r0

Disassembly of section .data:

000104d8 <__data_start>:
	...

000104e0 <impure_data>:
   104e0:	00000000 	andeq	r0, r0, r0
   104e4:	000107cc 	andeq	r0, r1, ip, asr #15
   104e8:	00010834 	andeq	r0, r1, r4, lsr r8
   104ec:	0001089c 	muleq	r1, ip, r8
	...
   10514:	000084b0 			; <UNDEFINED> instruction: 0x000084b0
	...
   10588:	00000001 	andeq	r0, r0, r1
   1058c:	00000000 	andeq	r0, r0, r0
   10590:	abcd330e 	blge	ff35d1d0 <_stack+0xff2dd1d0>
   10594:	e66d1234 			; <UNDEFINED> instruction: 0xe66d1234
   10598:	0005deec 	andeq	sp, r5, ip, ror #29
   1059c:	0000000b 	andeq	r0, r0, fp
	...

00010908 <_impure_ptr>:
   10908:	000104e0 	andeq	r0, r1, r0, ror #9

Disassembly of section .bss:

0001090c <__bss_start>:
   1090c:	00000000 	andeq	r0, r0, r0

00010910 <object.8024>:
	...

Disassembly of section .comment:

00000000 <.comment>:
   0:	3a434347 	bcc	10d0d24 <_stack+0x1050d24>
   4:	4e472820 	cdpmi	8, 4, cr2, cr7, cr0, {1}
   8:	6f542055 	svcvs	0x00542055
   c:	20736c6f 	rsbscs	r6, r3, pc, ror #24
  10:	20726f66 	rsbscs	r6, r2, r6, ror #30
  14:	204d5241 	subcs	r5, sp, r1, asr #4
  18:	65626d45 	strbvs	r6, [r2, #-3397]!	; 0xd45
  1c:	64656464 	strbtvs	r6, [r5], #-1124	; 0x464
  20:	6f725020 	svcvs	0x00725020
  24:	73736563 	cmnvc	r3, #415236096	; 0x18c00000
  28:	2973726f 	ldmdbcs	r3!, {r0, r1, r2, r3, r5, r6, r9, ip, sp, lr}^
  2c:	392e3420 	stmdbcc	lr!, {r5, sl, ip, sp}
  30:	3220332e 	eorcc	r3, r0, #-1207959552	; 0xb8000000
  34:	31343130 	teqcc	r4, r0, lsr r1
  38:	20393131 	eorscs	r3, r9, r1, lsr r1
  3c:	6c657228 	sfmvs	f7, 2, [r5], #-160	; 0xffffff60
  40:	65736165 	ldrbvs	r6, [r3, #-357]!	; 0x165
  44:	415b2029 	cmpmi	fp, r9, lsr #32
  48:	652f4d52 	strvs	r4, [pc, #-3410]!	; fffff2fe <_stack+0xfff7f2fe>
  4c:	6465626d 	strbtvs	r6, [r5], #-621	; 0x26d
  50:	2d646564 	cfstr64cs	mvdx6, [r4, #-400]!	; 0xfffffe70
  54:	2d395f34 	ldccs	15, cr5, [r9, #-208]!	; 0xffffff30
  58:	6e617262 	cdpvs	2, 6, cr7, cr1, cr2, {3}
  5c:	72206863 	eorvc	r6, r0, #6488064	; 0x630000
  60:	73697665 	cmnvc	r9, #105906176	; 0x6500000
  64:	206e6f69 	rsbcs	r6, lr, r9, ror #30
  68:	32383132 	eorscc	r3, r8, #-2147483636	; 0x8000000c
  6c:	005d3837 	subseq	r3, sp, r7, lsr r8

Disassembly of section .debug_aranges:

00000000 <.debug_aranges>:
   0:	0000001c 	andeq	r0, r0, ip, lsl r0
   4:	00000002 	andeq	r0, r0, r2
   8:	00040000 	andeq	r0, r4, r0
   c:	00000000 	andeq	r0, r0, r0
  10:	0000811c 	andeq	r8, r0, ip, lsl r1
  14:	0000008e 	andeq	r0, r0, lr, lsl #1
	...

Disassembly of section .debug_info:

00000000 <.debug_info>:
   0:	000000ba 	strheq	r0, [r0], -sl
   4:	00000004 	andeq	r0, r0, r4
   8:	01040000 	mrseq	r0, (UNDEF: 4)
   c:	0000006f 	andeq	r0, r0, pc, rrx
  10:	00000d01 	andeq	r0, r0, r1, lsl #26
  14:	00002900 	andeq	r2, r0, r0, lsl #18
  18:	00811c00 	addeq	r1, r1, r0, lsl #24
  1c:	00008e00 	andeq	r8, r0, r0, lsl #28
  20:	00000000 	andeq	r0, r0, r0
  24:	00220200 	eoreq	r0, r2, r0, lsl #4
  28:	03010000 	movweq	r0, #4096	; 0x1000
  2c:	00000075 	andeq	r0, r0, r5, ror r0
  30:	0000811c 	andeq	r8, r0, ip, lsl r1
  34:	00000066 	andeq	r0, r0, r6, rrx
  38:	00759c01 	rsbseq	r9, r5, r1, lsl #24
  3c:	78030000 	stmdavc	r3, {}	; <UNPREDICTABLE>
  40:	7c030100 	stfvcs	f0, [r3], {-0}
  44:	02000000 	andeq	r0, r0, #0
  48:	62046491 	andvs	r6, r4, #-1862270976	; 0x91000000
  4c:	01007469 	tsteq	r0, r9, ror #8
  50:	00007505 	andeq	r7, r0, r5, lsl #10
  54:	74910200 	ldrvc	r0, [r1], #512	; 0x200
  58:	00006a05 	andeq	r6, r0, r5, lsl #20
  5c:	75050100 	strvc	r0, [r5, #-256]	; 0x100
  60:	02000000 	andeq	r0, r0, #0
  64:	16057091 			; <UNDEFINED> instruction: 0x16057091
  68:	01000000 	mrseq	r0, (UNDEF: 0)
  6c:	00007505 	andeq	r7, r0, r5, lsl #10
  70:	6c910200 	lfmvs	f0, 4, [r1], {0}
  74:	07040600 	streq	r0, [r4, -r0, lsl #12]
  78:	00000000 	andeq	r0, r0, r0
  7c:	69050407 	stmdbvs	r5, {r0, r1, r2, sl}
  80:	0800746e 	stmdaeq	r0, {r1, r2, r3, r5, r6, sl, ip, sp, lr}
  84:	00000065 	andeq	r0, r0, r5, rrx
  88:	007c1e01 	rsbseq	r1, ip, r1, lsl #28
  8c:	81840000 	orrhi	r0, r4, r0
  90:	00260000 	eoreq	r0, r6, r0
  94:	9c010000 	stcls	0, cr0, [r1], {-0}
  98:	000000b7 	strheq	r0, [r0], -r7
  9c:	01006904 	tsteq	r0, r4, lsl #18
  a0:	00007c20 	andeq	r7, r0, r0, lsr #24
  a4:	74910200 	ldrvc	r0, [r1], #512	; 0x200
  a8:	00001b05 	andeq	r1, r0, r5, lsl #22
  ac:	b72c0100 	strlt	r0, [ip, -r0, lsl #2]!
  b0:	02000000 	andeq	r0, r0, #0
  b4:	09007091 	stmdbeq	r0, {r0, r4, r7, ip, sp, lr}
  b8:	00007c04 	andeq	r7, r0, r4, lsl #24
	...

Disassembly of section .debug_abbrev:

00000000 <.debug_abbrev>:
   0:	25011101 	strcs	r1, [r1, #-257]	; 0x101
   4:	030b130e 	movweq	r1, #45838	; 0xb30e
   8:	110e1b0e 	tstne	lr, lr, lsl #22
   c:	10061201 	andne	r1, r6, r1, lsl #4
  10:	02000017 	andeq	r0, r0, #23
  14:	193f012e 	ldmdbne	pc!, {r1, r2, r3, r5, r8}	; <UNPREDICTABLE>
  18:	0b3a0e03 	bleq	e8382c <_stack+0xe0382c>
  1c:	19270b3b 	stmdbne	r7!, {r0, r1, r3, r4, r5, r8, r9, fp}
  20:	01111349 	tsteq	r1, r9, asr #6
  24:	18400612 	stmdane	r0, {r1, r4, r9, sl}^
  28:	01194297 			; <UNDEFINED> instruction: 0x01194297
  2c:	03000013 	movweq	r0, #19
  30:	08030005 	stmdaeq	r3, {r0, r2}
  34:	0b3b0b3a 	bleq	ec2d24 <_stack+0xe42d24>
  38:	18021349 	stmdane	r2, {r0, r3, r6, r8, r9, ip}
  3c:	34040000 	strcc	r0, [r4], #-0
  40:	3a080300 	bcc	200c48 <_stack+0x180c48>
  44:	490b3b0b 	stmdbmi	fp, {r0, r1, r3, r8, r9, fp, ip, sp}
  48:	00180213 	andseq	r0, r8, r3, lsl r2
  4c:	00340500 	eorseq	r0, r4, r0, lsl #10
  50:	0b3a0e03 	bleq	e83864 <_stack+0xe03864>
  54:	13490b3b 	movtne	r0, #39739	; 0x9b3b
  58:	00001802 	andeq	r1, r0, r2, lsl #16
  5c:	0b002406 	bleq	907c <__EH_FRAME_BEGIN__+0xbbc>
  60:	030b3e0b 	movweq	r3, #48651	; 0xbe0b
  64:	0700000e 	streq	r0, [r0, -lr]
  68:	0b0b0024 	bleq	2c0100 <_stack+0x240100>
  6c:	08030b3e 	stmdaeq	r3, {r1, r2, r3, r4, r5, r8, r9, fp}
  70:	2e080000 	cdpcs	0, 0, cr0, cr8, cr0, {0}
  74:	03193f01 	tsteq	r9, #1, 30
  78:	3b0b3a0e 	blcc	2ce8b8 <_stack+0x24e8b8>
  7c:	1113490b 	tstne	r3, fp, lsl #18
  80:	40061201 	andmi	r1, r6, r1, lsl #4
  84:	19429618 	stmdbne	r2, {r3, r4, r9, sl, ip, pc}^
  88:	00001301 	andeq	r1, r0, r1, lsl #6
  8c:	0b000f09 	bleq	3cb8 <_init-0x4348>
  90:	0013490b 	andseq	r4, r3, fp, lsl #18
	...

Disassembly of section .debug_line:

00000000 <.debug_line>:
   0:	00000053 	andeq	r0, r0, r3, asr r0
   4:	001f0002 	andseq	r0, pc, r2
   8:	01020000 	mrseq	r0, (UNDEF: 2)
   c:	000d0efb 	strdeq	r0, [sp], -fp
  10:	01010101 	tsteq	r1, r1, lsl #2
  14:	01000000 	mrseq	r0, (UNDEF: 0)
  18:	00010000 	andeq	r0, r1, r0
  1c:	72717369 	rsbsvc	r7, r1, #-1543503871	; 0xa4000001
  20:	632e3274 	teqvs	lr, #116, 4	; 0x40000007
  24:	00000000 	andeq	r0, r0, r0
  28:	02050000 	andeq	r0, r5, #0
  2c:	0000811c 	andeq	r8, r0, ip, lsl r1
  30:	02004d14 	andeq	r4, r0, #20, 26	; 0x500
  34:	3c060104 	stfccs	f0, [r6], {4}
  38:	2f3d3006 	svccs	0x003d3006
  3c:	67682230 			; <UNDEFINED> instruction: 0x67682230
  40:	033e5c3d 	teqeq	lr, #15616	; 0x3d00
  44:	0e033c74 	mcreq	12, 0, r3, cr3, cr4, {3}
  48:	3d5c213c 	ldfcce	f2, [ip, #-240]	; 0xffffff10
  4c:	3d580c03 	ldclcc	12, cr0, [r8, #-12]
  50:	0402213e 	streq	r2, [r2], #-318	; 0x13e
  54:	Address 0x00000054 is out of bounds.


Disassembly of section .debug_frame:

00000000 <.debug_frame>:
   0:	0000000c 	andeq	r0, r0, ip
   4:	ffffffff 			; <UNDEFINED> instruction: 0xffffffff
   8:	7c020001 	stcvc	0, cr0, [r2], {1}
   c:	000d0c0e 	andeq	r0, sp, lr, lsl #24
  10:	0000001c 	andeq	r0, r0, ip, lsl r0
  14:	00000000 	andeq	r0, r0, r0
  18:	0000811c 	andeq	r8, r0, ip, lsl r1
  1c:	00000066 	andeq	r0, r0, r6, rrx
  20:	87080e41 	strhi	r0, [r8, -r1, asr #28]
  24:	41018e02 	tstmi	r1, r2, lsl #28
  28:	0d41200e 	stcleq	0, cr2, [r1, #-56]	; 0xffffffc8
  2c:	00000007 	andeq	r0, r0, r7
  30:	0000001c 	andeq	r0, r0, ip, lsl r0
  34:	00000000 	andeq	r0, r0, r0
  38:	00008184 	andeq	r8, r0, r4, lsl #3
  3c:	00000026 	andeq	r0, r0, r6, lsr #32
  40:	87080e41 	strhi	r0, [r8, -r1, asr #28]
  44:	41018e02 	tstmi	r1, r2, lsl #28
  48:	0d41100e 	stcleq	0, cr1, [r1, #-56]	; 0xffffffc8
  4c:	00000007 	andeq	r0, r0, r7
  50:	0000000c 	andeq	r0, r0, ip
  54:	ffffffff 			; <UNDEFINED> instruction: 0xffffffff
  58:	7c020001 	stcvc	0, cr0, [r2], {1}
  5c:	000d0c0e 	andeq	r0, sp, lr, lsl #24
  60:	00000014 	andeq	r0, r0, r4, lsl r0
  64:	00000050 	andeq	r0, r0, r0, asr r0
  68:	0000800c 	andeq	r8, r0, ip
  6c:	00000020 	andeq	r0, r0, r0, lsr #32
  70:	84080e41 	strhi	r0, [r8], #-3649	; 0xe41
  74:	00018e02 	andeq	r8, r1, r2, lsl #28
  78:	0000000c 	andeq	r0, r0, ip
  7c:	ffffffff 			; <UNDEFINED> instruction: 0xffffffff
  80:	7c020001 	stcvc	0, cr0, [r2], {1}
  84:	000d0c0e 	andeq	r0, sp, lr, lsl #24
  88:	00000018 	andeq	r0, r0, r8, lsl r0
  8c:	00000078 	andeq	r0, r0, r8, ror r0
  90:	000081ac 	andeq	r8, r0, ip, lsr #3
  94:	00000048 	andeq	r0, r0, r8, asr #32
  98:	84100e41 	ldrhi	r0, [r0], #-3649	; 0xe41
  9c:	86038504 	strhi	r8, [r3], -r4, lsl #10
  a0:	00018e02 	andeq	r8, r1, r2, lsl #28
  a4:	0000000c 	andeq	r0, r0, ip
  a8:	ffffffff 			; <UNDEFINED> instruction: 0xffffffff
  ac:	7c020001 	stcvc	0, cr0, [r2], {1}
  b0:	000d0c0e 	andeq	r0, sp, lr, lsl #24
  b4:	00000018 	andeq	r0, r0, r8, lsl r0
  b8:	000000a4 	andeq	r0, r0, r4, lsr #1
  bc:	000081f4 	strdeq	r8, [r0], -r4
  c0:	0000008c 	andeq	r0, r0, ip, lsl #1
  c4:	84100e41 	ldrhi	r0, [r0], #-3649	; 0xe41
  c8:	86038504 	strhi	r8, [r3], -r4, lsl #10
  cc:	00018e02 	andeq	r8, r1, r2, lsl #28
  d0:	0000000c 	andeq	r0, r0, ip
  d4:	ffffffff 			; <UNDEFINED> instruction: 0xffffffff
  d8:	7c020001 	stcvc	0, cr0, [r2], {1}
  dc:	000d0c0e 	andeq	r0, sp, lr, lsl #24
  e0:	00000014 	andeq	r0, r0, r4, lsl r0
  e4:	000000d0 	ldrdeq	r0, [r0], -r0	; <UNPREDICTABLE>
  e8:	0000802c 	andeq	r8, r0, ip, lsr #32
  ec:	00000018 	andeq	r0, r0, r8, lsl r0
  f0:	83080e41 	movwhi	r0, #36417	; 0x8e41
  f4:	00018e02 	andeq	r8, r1, r2, lsl #28
  f8:	00000028 	andeq	r0, r0, r8, lsr #32
  fc:	000000d0 	ldrdeq	r0, [r0], -r0	; <UNPREDICTABLE>
 100:	00008280 	andeq	r8, r0, r0, lsl #5
 104:	00000108 	andeq	r0, r0, r8, lsl #2
 108:	84140e41 	ldrhi	r0, [r4], #-3649	; 0xe41
 10c:	86048505 	strhi	r8, [r4], -r5, lsl #10
 110:	8e028703 	cdphi	7, 0, cr8, cr2, cr3, {0}
 114:	240e4501 	strcs	r4, [lr], #-1281	; 0x501
 118:	08890988 	stmeq	r9, {r3, r7, r8, fp}
 11c:	068b078a 	streq	r0, [fp], sl, lsl #15
 120:	00400e43 	subeq	r0, r0, r3, asr #28
 124:	0000000c 	andeq	r0, r0, ip
 128:	ffffffff 			; <UNDEFINED> instruction: 0xffffffff
 12c:	7c020001 	stcvc	0, cr0, [r2], {1}
 130:	000d0c0e 	andeq	r0, sp, lr, lsl #24
 134:	00000014 	andeq	r0, r0, r4, lsl r0
 138:	00000124 	andeq	r0, r0, r4, lsr #2
 13c:	00008388 	andeq	r8, r0, r8, lsl #7
 140:	00000010 	andeq	r0, r0, r0, lsl r0
 144:	83080e41 	movwhi	r0, #36417	; 0x8e41
 148:	00018e02 	andeq	r8, r1, r2, lsl #28
 14c:	0000000c 	andeq	r0, r0, ip
 150:	ffffffff 			; <UNDEFINED> instruction: 0xffffffff
 154:	7c020001 	stcvc	0, cr0, [r2], {1}
 158:	000d0c0e 	andeq	r0, sp, lr, lsl #24
 15c:	00000018 	andeq	r0, r0, r8, lsl r0
 160:	0000014c 	andeq	r0, r0, ip, asr #2
 164:	00008398 	muleq	r0, r8, r3
 168:	00000034 	andeq	r0, r0, r4, lsr r0
 16c:	83100e41 	tsthi	r0, #1040	; 0x410
 170:	85038404 	strhi	r8, [r3, #-1028]	; 0x404
 174:	00018e02 	andeq	r8, r1, r2, lsl #28
 178:	0000000c 	andeq	r0, r0, ip
 17c:	ffffffff 			; <UNDEFINED> instruction: 0xffffffff
 180:	7c020001 	stcvc	0, cr0, [r2], {1}
 184:	000d0c0e 	andeq	r0, sp, lr, lsl #24
 188:	00000028 	andeq	r0, r0, r8, lsr #32
 18c:	00000178 	andeq	r0, r0, r8, ror r1
 190:	000083cc 	andeq	r8, r0, ip, asr #7
 194:	000000d4 	ldrdeq	r0, [r0], -r4
 198:	83180e41 	tsthi	r8, #1040	; 0x410
 19c:	85058406 	strhi	r8, [r5, #-1030]	; 0x406
 1a0:	87038604 	strhi	r8, [r3, -r4, lsl #12]
 1a4:	47018e02 	strmi	r8, [r1, -r2, lsl #28]
 1a8:	0a88280e 	beq	fe20a1e8 <_stack+0xfe18a1e8>
 1ac:	088a0989 	stmeq	sl, {r0, r3, r7, r8, fp}
 1b0:	0000078b 	andeq	r0, r0, fp, lsl #15
 1b4:	0000000c 	andeq	r0, r0, ip
 1b8:	ffffffff 			; <UNDEFINED> instruction: 0xffffffff
 1bc:	7c020001 	stcvc	0, cr0, [r2], {1}
 1c0:	000d0c0e 	andeq	r0, sp, lr, lsl #24
 1c4:	0000000c 	andeq	r0, r0, ip
 1c8:	000001b4 			; <UNDEFINED> instruction: 0x000001b4
 1cc:	000084a0 	andeq	r8, r0, r0, lsr #9
 1d0:	00000002 	andeq	r0, r0, r2

Disassembly of section .debug_str:

00000000 <.debug_str>:
   0:	69736e75 	ldmdbvs	r3!, {r0, r2, r4, r5, r6, r9, sl, fp, sp, lr}^
   4:	64656e67 	strbtvs	r6, [r5], #-3687	; 0xe67
   8:	746e6920 	strbtvc	r6, [lr], #-2336	; 0x920
   c:	71736900 	cmnvc	r3, r0, lsl #18
  10:	2e327472 	mrccs	4, 1, r7, cr2, cr2, {3}
  14:	6f720063 	svcvs	0x00720063
  18:	6c00746f 	cfstrsvs	mvf7, [r0], {111}	; 0x6f
  1c:	6567676f 	strbvs	r6, [r7, #-1903]!	; 0x76f
  20:	73690072 	cmnvc	r9, #114	; 0x72
  24:	32747271 	rsbscc	r7, r4, #268435463	; 0x10000007
  28:	6f682f00 	svcvs	0x00682f00
  2c:	672f656d 	strvs	r6, [pc, -sp, ror #10]!
  30:	73373961 	teqvc	r7, #1589248	; 0x184000
  34:	772f6861 	strvc	r6, [pc, -r1, ror #16]!
  38:	2f6b726f 	svccs	0x006b726f
  3c:	73697465 	cmnvc	r9, #1694498816	; 0x65000000
  40:	2e302f73 	mrccs	15, 1, r2, cr0, cr3, {3}
  44:	5f332e34 	svcpl	0x00332e34
  48:	6574696c 	ldrbvs	r6, [r4, #-2412]!	; 0x96c
  4c:	726f435f 	rsbvc	r4, pc, #2080374785	; 0x7c000001
  50:	4d786574 	cfldr64mi	mvdx6, [r8, #-464]!	; 0xfffffe30
  54:	57532f30 	smmlarpl	r3, r0, pc, r2	; <UNPREDICTABLE>
  58:	7365742f 	cmnvc	r5, #788529152	; 0x2f000000
  5c:	52415f74 	subpl	r5, r1, #116, 30	; 0x1d0
  60:	4d36764d 	ldcmi	6, cr7, [r6, #-308]!	; 0xfffffecc
  64:	69616d00 	stmdbvs	r1!, {r8, sl, fp, sp, lr}^
  68:	6572006e 	ldrbvs	r0, [r2, #-110]!	; 0x6e
  6c:	47007473 	smlsdxmi	r0, r3, r4, r7
  70:	4320554e 	teqmi	r0, #327155712	; 0x13800000
  74:	392e3420 	stmdbcc	lr!, {r5, sl, ip, sp}
  78:	3220332e 	eorcc	r3, r0, #-1207959552	; 0xb8000000
  7c:	31343130 	teqcc	r4, r0, lsr r1
  80:	20393131 	eorscs	r3, r9, r1, lsr r1
  84:	6c657228 	sfmvs	f7, 2, [r5], #-160	; 0xffffff60
  88:	65736165 	ldrbvs	r6, [r3, #-357]!	; 0x165
  8c:	415b2029 	cmpmi	fp, r9, lsr #32
  90:	652f4d52 	strvs	r4, [pc, #-3410]!	; fffff346 <_stack+0xfff7f346>
  94:	6465626d 	strbtvs	r6, [r5], #-621	; 0x26d
  98:	2d646564 	cfstr64cs	mvdx6, [r4, #-400]!	; 0xfffffe70
  9c:	2d395f34 	ldccs	15, cr5, [r9, #-208]!	; 0xffffff30
  a0:	6e617262 	cdpvs	2, 6, cr7, cr1, cr2, {3}
  a4:	72206863 	eorvc	r6, r0, #6488064	; 0x630000
  a8:	73697665 	cmnvc	r9, #105906176	; 0x6500000
  ac:	206e6f69 	rsbcs	r6, lr, r9, ror #30
  b0:	32383132 	eorscc	r3, r8, #-2147483636	; 0x8000000c
  b4:	205d3837 	subscs	r3, sp, r7, lsr r8
  b8:	70636d2d 	rsbvc	r6, r3, sp, lsr #26
  bc:	6f633d75 	svcvs	0x00633d75
  c0:	78657472 	stmdavc	r5!, {r1, r4, r5, r6, sl, ip, sp, lr}^
  c4:	20306d2d 	eorscs	r6, r0, sp, lsr #26
  c8:	68746d2d 	ldmdavs	r4!, {r0, r2, r3, r5, r8, sl, fp, sp, lr}^
  cc:	20626d75 	rsbcs	r6, r2, r5, ror sp
  d0:	Address 0x000000d0 is out of bounds.


Disassembly of section .ARM.attributes:

00000000 <_stack-0x80000>:
   0:	00002741 	andeq	r2, r0, r1, asr #14
   4:	61656100 	cmnvs	r5, r0, lsl #2
   8:	01006962 	tsteq	r0, r2, ror #18
   c:	0000001d 	andeq	r0, r0, sp, lsl r0
  10:	2d533605 	ldclcs	6, cr3, [r3, #-20]	; 0xffffffec
  14:	0c06004d 	stceq	0, cr0, [r6], {77}	; 0x4d
  18:	01094d07 	tsteq	r9, r7, lsl #26
  1c:	01140412 	tsteq	r4, r2, lsl r4
  20:	03170115 	tsteq	r7, #1073741829	; 0x40000005
  24:	011a0118 	tsteq	sl, r8, lsl r1
