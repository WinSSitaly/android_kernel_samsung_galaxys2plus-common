/*
 * PCI / PCI-X / PCI-Express support for 4xx parts
 *
 * Copyright 2007 Ben. Herrenschmidt <benh@kernel.crashing.org>, IBM Corp.
 *
 * Bits and pieces extracted from arch/ppc support by
 *
 * Matt Porter <mporter@kernel.crashing.org>
 *
 * Copyright 2002-2005 MontaVista Software Inc.
 */
#ifndef __PPC4XX_PCI_H__
#define __PPC4XX_PCI_H__

/*
 * 4xx PCI-X bridge register definitions
 */
#define PCIX0_VENDID		0x000
#define PCIX0_DEVID		0x002
#define PCIX0_COMMAND		0x004
#define PCIX0_STATUS		0x006
#define PCIX0_REVID		0x008
#define PCIX0_CLS		0x009
#define PCIX0_CACHELS		0x00c
#define PCIX0_LATTIM		0x00d
#define PCIX0_HDTYPE		0x00e
#define PCIX0_BIST		0x00f
#define PCIX0_BAR0L		0x010
#define PCIX0_BAR0H		0x014
#define PCIX0_BAR1		0x018
#define PCIX0_BAR2L		0x01c
#define PCIX0_BAR2H		0x020
#define PCIX0_BAR3		0x024
#define PCIX0_CISPTR		0x028
#define PCIX0_SBSYSVID		0x02c
#define PCIX0_SBSYSID		0x02e
#define PCIX0_EROMBA		0x030
#define PCIX0_CAP		0x034
#define PCIX0_RES0		0x035
#define PCIX0_RES1		0x036
#define PCIX0_RES2		0x038
#define PCIX0_INTLN		0x03c
#define PCIX0_INTPN		0x03d
#define PCIX0_MINGNT		0x03e
#define PCIX0_MAXLTNCY		0x03f
#define PCIX0_BRDGOPT1		0x040
#define PCIX0_BRDGOPT2		0x044
#define PCIX0_ERREN		0x050
#define PCIX0_ERRSTS		0x054
#define PCIX0_PLBBESR		0x058
#define PCIX0_PLBBEARL		0x05c
#define PCIX0_PLBBEARH		0x060
#define PCIX0_POM0LAL		0x068
#define PCIX0_POM0LAH		0x06c
#define PCIX0_POM0SA		0x070
#define PCIX0_POM0PCIAL		0x074
#define PCIX0_POM0PCIAH		0x078
#define PCIX0_POM1LAL		0x07c
#define PCIX0_POM1LAH		0x080
#define PCIX0_POM1SA		0x084
#define PCIX0_POM1PCIAL		0x088
#define PCIX0_POM1PCIAH		0x08c
#define PCIX0_POM2SA		0x090
#define PCIX0_PIM0SAL		0x098
#define PCIX0_PIM0SA		PCIX0_PIM0SAL
#define PCIX0_PIM0LAL		0x09c
#define PCIX0_PIM0LAH		0x0a0
#define PCIX0_PIM1SA		0x0a4
#define PCIX0_PIM1LAL		0x0a8
#define PCIX0_PIM1LAH		0x0ac
#define PCIX0_PIM2SAL		0x0b0
#define PCIX0_PIM2SA		PCIX0_PIM2SAL
#define PCIX0_PIM2LAL		0x0b4
#define PCIX0_PIM2LAH		0x0b8
#define PCIX0_OMCAPID		0x0c0
#define PCIX0_OMNIPTR		0x0c1
#define PCIX0_OMMC		0x0c2
#define PCIX0_OMMA		0x0c4
#define PCIX0_OMMUA		0x0c8
#define PCIX0_OMMDATA		0x0cc
#define PCIX0_OMMEOI		0x0ce
#define PCIX0_PMCAPID		0x0d0
#define PCIX0_PMNIPTR		0x0d1
#define PCIX0_PMC		0x0d2
#define PCIX0_PMCSR		0x0d4
#define PCIX0_PMCSRBSE		0x0d6
#define PCIX0_PMDATA		0x0d7
#define PCIX0_PMSCRR		0x0d8
#define PCIX0_CAPID		0x0dc
#define PCIX0_NIPTR		0x0dd
#define PCIX0_CMD		0x0de
#define PCIX0_STS		0x0e0
#define PCIX0_IDR		0x0e4
#define PCIX0_CID		0x0e8
#define PCIX0_RID		0x0ec
#define PCIX0_PIM0SAH		0x0f8
#define PCIX0_PIM2SAH		0x0fc
#define PCIX0_MSGIL		0x100
#define PCIX0_MSGIH		0x104
#define PCIX0_MSGOL		0x108
#define PCIX0_MSGOH		0x10c
#define PCIX0_IM		0x1f8

/*
 * 4xx PCI bridge register definitions
 */
#define PCIL0_PMM0LA		0x00
#define PCIL0_PMM0MA		0x04
#define PCIL0_PMM0PCILA		0x08
#define PCIL0_PMM0PCIHA		0x0c
#define PCIL0_PMM1LA		0x10
#define PCIL0_PMM1MA		0x14
#define PCIL0_PMM1PCILA		0x18
#define PCIL0_PMM1PCIHA		0x1c
#define PCIL0_PMM2LA		0x20
#define PCIL0_PMM2MA		0x24
#define PCIL0_PMM2PCILA		0x28
#define PCIL0_PMM2PCIHA		0x2c
#define PCIL0_PTM1MS		0x30
#define PCIL0_PTM1LA		0x34
#define PCIL0_PTM2MS		0x38
#define PCIL0_PTM2LA		0x3c

/*
 * 4xx PCIe bridge register definitions
 */

/* DCR offsets */
#define DCRO_PEGPL_CFGBAH		0x00
#define DCRO_PEGPL_CFGBAL		0x01
#define DCRO_PEGPL_CFGMSK		0x02
#define DCRO_PEGPL_MSGBAH		0x03
#define DCRO_PEGPL_MSGBAL		0x04
#define DCRO_PEGPL_MSGMSK		0x05
#define DCRO_PEGPL_OMR1BAH		0x06
#define DCRO_PEGPL_OMR1BAL		0x07
#define DCRO_PEGPL_OMR1MSKH		0x08
#define DCRO_PEGPL_OMR1MSKL		0x09
#define DCRO_PEGPL_OMR2BAH		0x0a
#define DCRO_PEGPL_OMR2BAL		0x0b
#define DCRO_PEGPL_OMR2MSKH		0x0c
#define DCRO_PEGPL_OMR2MSKL		0x0d
#define DCRO_PEGPL_OMR3BAH		0x0e
#define DCRO_PEGPL_OMR3BAL		0x0f
#define DCRO_PEGPL_OMR3MSKH		0x10
#define DCRO_PEGPL_OMR3MSKL		0x11
#define DCRO_PEGPL_REGBAH		0x12
#define DCRO_PEGPL_REGBAL		0x13
#define DCRO_PEGPL_REGMSK		0x14
#define DCRO_PEGPL_SPECIAL		0x15
#define DCRO_PEGPL_CFG			0x16
#define DCRO_PEGPL_ESR			0x17
#define DCRO_PEGPL_EARH			0x18
#define DCRO_PEGPL_EARL			0x19
#define DCRO_PEGPL_EATR			0x1a

/* DMER mask */
#define GPL_DMER_MASK_DISA	0x02000000

/*
 * System DCRs (SDRs)
 */
#define PESDR0_PLLLCT1			0x03a0
#define PESDR0_PLLLCT2			0x03a1
#define PESDR0_PLLLCT3			0x03a2

/*
 * 440SPe additional DCRs
 */
#define PESDR0_440SPE_UTLSET1		0x0300
#define PESDR0_440SPE_UTLSET2		0x0301
#define PESDR0_440SPE_DLPSET		0x0302
#define PESDR0_440SPE_LOOP		0x0303
#define PESDR0_440SPE_RCSSET		0x0304
#define PESDR0_440SPE_RCSSTS		0x0305
#define PESDR0_440SPE_HSSL0SET1		0x0306
#define PESDR0_440SPE_HSSL0SET2		0x0307
#define PESDR0_440SPE_HSSL0STS		0x0308
#define PESDR0_440SPE_HSSL1SET1		0x0309
#define PESDR0_440SPE_HSSL1SET2		0x030a
#define PESDR0_440SPE_HSSL1STS		0x030b
#define PESDR0_440SPE_HSSL2SET1		0x030c
#define PESDR0_440SPE_HSSL2SET2		0x030d
#define PESDR0_440SPE_HSSL2STS		0x030e
#define PESDR0_440SPE_HSSL3SET1		0x030f
#define PESDR0_440SPE_HSSL3SET2		0x0310
#define PESDR0_440SPE_HSSL3STS		0x0311
#define PESDR0_440SPE_HSSL4SET1		0x0312
#define PESDR0_440SPE_HSSL4SET2		0x0313
#define PESDR0_440SPE_HSSL4STS	       	0x0314
#define PESDR0_440SPE_HSSL5SET1		0x0315
#define PESDR0_440SPE_HSSL5SET2		0x0316
#define PESDR0_440SPE_HSSL5STS		0x0317
#define PESDR0_440SPE_HSSL6SET1		0x0318
#define PESDR0_440SPE_HSSL6SET2		0x0319
#define PESDR0_440SPE_HSSL6STS		0x031a
#define PESDR0_440SPE_HSSL7SET1		0x031b
#define PESDR0_440SPE_HSSL7SET2		0x031c
#define PESDR0_440SPE_HSSL7STS		0x031d
#define PESDR0_440SPE_HSSCTLSET		0x031e
#define PESDR0_440SPE_LANE_ABCD		0x031f
#define PESDR0_440SPE_LANE_EFGH		0x0320

#define PESDR1_440SPE_UTLSET1		0x0340
#define PESDR1_440SPE_UTLSET2		0x0341
#define PESDR1_440SPE_DLPSET		0x0342
#define PESDR1_440SPE_LOOP		0x0343
#define PESDR1_440SPE_RCSSET		0x0344
#define PESDR1_440SPE_RCSSTS		0x0345
#define PESDR1_440SPE_HSSL0SET1		0x0346
#define PESDR1_440SPE_HSSL0SET2		0x0347
#define PESDR1_440SPE_HSSL0STS		0x0348
#define PESDR1_440SPE_HSSL1SET1		0x0349
#define PESDR1_440SPE_HSSL1SET2		0x034a
#define PESDR1_440SPE_HSSL1STS		0x034b
#define PESDR1_440SPE_HSSL2SET1		0x034c
#define PESDR1_440SPE_HSSL2SET2		0x034d
#define PESDR1_440SPE_HSSL2STS		0x034e
#define PESDR1_440SPE_HSSL3SET1		0x034f
#define PESDR1_440SPE_HSSL3SET2		0x0350
#define PESDR1_440SPE_HSSL3STS		0x0351
#define PESDR1_440SPE_HSSCTLSET		0x0352
#define PESDR1_440SPE_LANE_ABCD		0x0353

#define PESDR2_440SPE_UTLSET1		0x0370
#define PESDR2_440SPE_UTLSET2		0x0371
#define PESDR2_440SPE_DLPSET		0x0372
#define PESDR2_440SPE_LOOP		0x0373
#define PESDR2_440SPE_RCSSET		0x0374
#define PESDR2_440SPE_RCSSTS		0x0375
#define PESDR2_440SPE_HSSL0SET1		0x0376
#define PESDR2_440SPE_HSSL0SET2		0x0377
#define PESDR2_440SPE_HSSL0STS		0x0378
#define PESDR2_440SPE_HSSL1SET1		0x0379
#define PESDR2_440SPE_HSSL1SET2		0x037a
#define PESDR2_440SPE_HSSL1STS		0x037b
#define PESDR2_440SPE_HSSL2SET1		0x037c
#define PESDR2_440SPE_HSSL2SET2		0x037d
#define PESDR2_440SPE_HSSL2STS		0x037e
#define PESDR2_440SPE_HSSL3SET1		0x037f
#define PESDR2_440SPE_HSSL3SET2		0x0380
#define PESDR2_440SPE_HSSL3STS		0x0381
#define PESDR2_440SPE_HSSCTLSET		0x0382
#define PESDR2_440SPE_LANE_ABCD		0x0383

/*
 * 405EX additional DCRs
 */
#define PESDR0_405EX_UTLSET1		0x0400
#define PESDR0_405EX_UTLSET2		0x0401
#define PESDR0_405EX_DLPSET		0x0402
#define PESDR0_405EX_LOOP		0x0403
#define PESDR0_405EX_RCSSET		0x0404
#define PESDR0_405EX_RCSSTS		0x0405
#define PESDR0_405EX_PHYSET1		0x0406
#define PESDR0_405EX_PHYSET2		0x0407
#define PESDR0_405EX_BIST		0x0408
#define PESDR0_405EX_LPB		0x040B
#define PESDR0_405EX_PHYSTA		0x040C

#define PESDR1_405EX_UTLSET1		0x0440
#define PESDR1_405EX_UTLSET2		0x0441
#define PESDR1_405EX_DLPSET		0x0442
#define PESDR1_405EX_LOOP		0x0443
#define PESDR1_405EX_RCSSET		0x0444
#define PESDR1_405EX_RCSSTS		0x0445
#define PESDR1_405EX_PHYSET1		0x0446
#define PESDR1_405EX_PHYSET2		0x0447
#define PESDR1_405EX_BIST		0x0448
#define PESDR1_405EX_LPB		0x044B
#define PESDR1_405EX_PHYSTA		0x044C

/*
 * 460EX additional DCRs
 */
#define PESDR0_460EX_L0BIST		0x0308
#define PESDR0_460EX_L0BISTSTS		0x0309
#define PESDR0_460EX_L0CDRCTL		0x030A
#define PESDR0_460EX_L0DRV		0x030B
#define PESDR0_460EX_L0REC		0x030C
#define PESDR0_460EX_L0LPB		0x030D
#define PESDR0_460EX_L0CLK		0x030E
#define PESDR0_460EX_PHY_CTL_RST	0x030F
#define PESDR0_460EX_RSTSTA		0x0310
#define PESDR0_460EX_OBS		0x0311
#define PESDR0_460EX_L0ERRC		0x0320

#define PESDR1_460EX_L0BIST		0x0348
#define PESDR1_460EX_L1BIST		0x0349
#define PESDR1_460EX_L2BIST		0x034A
#define PESDR1_460EX_L3BIST		0x034B
#define PESDR1_460EX_L0BISTSTS		0x034C
#define PESDR1_460EX_L1BISTSTS		0x034D
#define PESDR1_460EX_L2BISTSTS		0x034E
#define PESDR1_460EX_L3BISTSTS		0x034F
#define PESDR1_460EX_L0CDRCTL		0x0350
#define PESDR1_460EX_L1CDRCTL		0x0351
#define PESDR1_460EX_L2CDRCTL		0x0352
#define PESDR1_460EX_L3CDRCTL		0x0353
#define PESDR1_460EX_L0DRV		0x0354
#define PESDR1_460EX_L1DRV		0x0355
#define PESDR1_460EX_L2DRV		0x0356
#define PESDR1_460EX_L3DRV		0x0357
#define PESDR1_460EX_L0REC		0x0358
#define PESDR1_460EX_L1REC		0x0359
#define PESDR1_460EX_L2REC		0x035A
#define PESDR1_460EX_L3REC		0x035B
#define PESDR1_460EX_L0LPB		0x035C
#define PESDR1_460EX_L1LPB		0x035D
#define PESDR1_460EX_L2LPB		0x035E
#define PESDR1_460EX_L3LPB		0x035F
#define PESDR1_460EX_L0CLK		0x0360
#define PESDR1_460EX_L1CLK		0x0361
#define PESDR1_460EX_L2CLK		0x0362
#define PESDR1_460EX_L3CLK		0x0363
#define PESDR1_460EX_PHY_CTL_RST	0x0364
#define PESDR1_460EX_RSTSTA		0x0365
#define PESDR1_460EX_OBS		0x0366
#define PESDR1_460EX_L0ERRC		0x0368
#define PESDR1_460EX_L1ERRC		0x0369
#define PESDR1_460EX_L2ERRC		0x036A
#define PESDR1_460EX_L3ERRC		0x036B
#define PESDR0_460EX_IHS1		0x036C
#define PESDR0_460EX_IHS2		0x036D

/*
 * 460SX additional DCRs
 */
#define PESDRn_460SX_RCEI		0x02

#define PESDR0_460SX_HSSL0DAMP		0x320
#define PESDR0_460SX_HSSL1DAMP		0x321
#define PESDR0_460SX_HSSL2DAMP		0x322
#define PESDR0_460SX_HSSL3DAMP		0x323
#define PESDR0_460SX_HSSL4DAMP		0x324
#define PESDR0_460SX_HSSL5DAMP		0x325
#define PESDR0_460SX_HSSL6DAMP		0x326
#define PESDR0_460SX_HSSL7DAMP		0x327

#define PESDR1_460SX_HSSL0DAMP		0x354
#define PESDR1_460SX_HSSL1DAMP		0x355
#define PESDR1_460SX_HSSL2DAMP		0x356
#define PESDR1_460SX_HSSL3DAMP		0x357

#define PESDR2_460SX_HSSL0DAMP		0x384
#define PESDR2_460SX_HSSL1DAMP		0x385
#define PESDR2_460SX_HSSL2DAMP		0x386
#define PESDR2_460SX_HSSL3DAMP		0x387

#define PESDR0_460SX_HSSL0COEFA		0x328
#define PESDR0_460SX_HSSL1COEFA		0x329
#define PESDR0_460SX_HSSL2COEFA		0x32A
#define PESDR0_460SX_HSSL3COEFA		0x32B
#define PESDR0_460SX_HSSL4COEFA		0x32C
#define PESDR0_460SX_HSSL5COEFA		0x32D
#define PESDR0_460SX_HSSL6COEFA		0x32E
#define PESDR0_460SX_HSSL7COEFA		0x32F

#define PESDR1_460SX_HSSL0COEFA		0x358
#define PESDR1_460SX_HSSL1COEFA		0x359
#define PESDR1_460SX_HSSL2COEFA		0x35A
#define PESDR1_460SX_HSSL3COEFA		0x35B

#define PESDR2_460SX_HSSL0COEFA		0x388
#define PESDR2_460SX_HSSL1COEFA		0x389
#define PESDR2_460SX_HSSL2COEFA		0x38A
#define PESDR2_460SX_HSSL3COEFA		0x38B

#define PESDR0_460SX_HSSL1CALDRV	0x339
#define PESDR1_460SX_HSSL1CALDRV	0x361
#define PESDR2_460SX_HSSL1CALDRV	0x391

#define PESDR0_460SX_HSSSLEW		0x338
#define PESDR1_460SX_HSSSLEW		0x360
#define PESDR2_460SX_HSSSLEW		0x390

#define PESDR0_460SX_HSSCTLSET		0x31E
#define PESDR1_460SX_HSSCTLSET		0x352
#define PESDR2_460SX_HSSCTLSET		0x382

#define PESDR0_460SX_RCSSET		0x304
#define PESDR1_460SX_RCSSET		0x344
#define PESDR2_460SX_RCSSET		0x374
/*
 * Of the above, some are common offsets from the base
 */
#define PESDRn_UTLSET1			0x00
#define PESDRn_UTLSET2			0x01
#define PESDRn_DLPSET			0x02
#define PESDRn_LOOP			0x03
#define PESDRn_RCSSET			0x04
#define PESDRn_RCSSTS			0x05

/* 440spe only */
#define PESDRn_440SPE_HSSL0SET1		0x06
#define PESDRn_440SPE_HSSL0SET2		0x07
#define PESDRn_440SPE_HSSL0STS		0x08
#define PESDRn_440SPE_HSSL1SET1		0x09
#define PESDRn_440SPE_HSSL1SET2		0x0a
#define PESDRn_440SPE_HSSL1STS		0x0b
#define PESDRn_440SPE_HSSL2SET1		0x0c
#define PESDRn_440SPE_HSSL2SET2		0x0d
#define PESDRn_440SPE_HSSL2STS		0x0e
#define PESDRn_440SPE_HSSL3SET1		0x0f
#define PESDRn_440SPE_HSSL3SET2		0x10
#define PESDRn_440SPE_HSSL3STS		0x11

/* 440spe port 0 only */
#define PESDRn_440SPE_HSSL4SET1		0x12
#define PESDRn_440SPE_HSSL4SET2		0x13
#define PESDRn_440SPE_HSSL4STS	       	0x14
#define PESDRn_440SPE_HSSL5SET1		0x15
#define PESDRn_440SPE_HSSL5SET2		0x16
#define PESDRn_440SPE_HSSL5STS		0x17
#define PESDRn_440SPE_HSSL6SET1		0x18
#define PESDRn_440SPE_HSSL6SET2		0x19
#define PESDRn_440SPE_HSSL6STS		0x1a
#define PESDRn_440SPE_HSSL7SET1		0x1b
#define PESDRn_440SPE_HSSL7SET2		0x1c
#define PESDRn_440SPE_HSSL7STS		0x1d

/* 405ex only */
#define PESDRn_405EX_PHYSET1		0x06
#define PESDRn_405EX_PHYSET2		0x07
#define PESDRn_405EX_PHYSTA		0x0c

/*
 * UTL register offsets
 */
#define PEUTL_PBCTL		0x00
#define PEUTL_PBBSZ		0x20
#define PEUTL_OPDBSZ		0x68
#define PEUTL_IPHBSZ		0x70
#define PEUTL_IPDBSZ		0x78
#define PEUTL_OUTTR		0x90
#define PEUTL_INTR		0x98
#define PEUTL_PCTL		0xa0
#define PEUTL_RCSTA		0xB0
#define PEUTL_RCIRQEN		0xb8

/*
 * Config space register offsets
 */
#define PECFG_ECRTCTL		0x074

#define PECFG_BAR0LMPA		0x210
#define PECFG_BAR0HMPA		0x214
#define PECFG_BAR1MPA		0x218
#define PECFG_BAR2LMPA		0x220
#define PECFG_BAR2HMPA		0x224

#define PECFG_PIMEN		0x33c
#define PECFG_PIM0LAL		0x340
#define PECFG_PIM0LAH		0x344
#define PECFG_PIM1LAL		0x348
#define PECFG_PIM1LAH		0x34c
#define PECFG_PIM01SAL		0x350
#define PECFG_PIM01SAH		0x354

#define PECFG_POM0LAL		0x380
#define PECFG_POM0LAH		0x384
#define PECFG_POM1LAL		0x388
#define PECFG_POM1LAH		0x38c
#define PECFG_POM2LAL		0x390
#define PECFG_POM2LAH		0x394

<<<<<<< HEAD
/* 460sx only */
#define PECFG_460SX_DLLSTA     0x3f8

/* 460sx Bit Mappings */
#define PECFG_460SX_DLLSTA_LINKUP	 0x00000010
#define DCRO_PEGPL_460SX_OMR1MSKL_UOT	 0x00000004

/* PEGPL Bit Mappings */
#define DCRO_PEGPL_OMRxMSKL_VAL	 0x00000001
#define DCRO_PEGPL_OMR1MSKL_UOT	 0x00000002
#define DCRO_PEGPL_OMR3MSKL_IO	 0x00000002

/* 476FPE */
#define PCCFG_LCPA			0x270
#define PECFG_TLDLP			0x3F8
#define PECFG_TLDLP_LNKUP		0x00000008
#define PECFG_TLDLP_PRESENT		0x00000010
#define DCRO_PEGPL_476FPE_OMR1MSKL_UOT	 0x00000004

=======
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
/* SDR Bit Mappings */
#define PESDRx_RCSSET_HLDPLB	0x10000000
#define PESDRx_RCSSET_RSTGU	0x01000000
#define PESDRx_RCSSET_RDY       0x00100000
#define PESDRx_RCSSET_RSTDL     0x00010000
#define PESDRx_RCSSET_RSTPYN    0x00001000

enum
{
	PTYPE_ENDPOINT		= 0x0,
	PTYPE_LEGACY_ENDPOINT	= 0x1,
	PTYPE_ROOT_PORT		= 0x4,

	LNKW_X1			= 0x1,
	LNKW_X4			= 0x4,
	LNKW_X8			= 0x8
};


#endif /* __PPC4XX_PCI_H__ */
