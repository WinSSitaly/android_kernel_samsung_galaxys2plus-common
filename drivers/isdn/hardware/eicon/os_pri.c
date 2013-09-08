/* $Id: os_pri.c,v 1.32 2004/03/21 17:26:01 armin Exp $ */

#include "platform.h"
#include "debuglib.h"
#include "cardtype.h"
#include "pc.h"
#include "pr_pc.h"
#include "di_defs.h"
#include "dsp_defs.h"
#include "di.h"
#include "io.h"

#include "xdi_msg.h"
#include "xdi_adapter.h"
#include "os_pri.h"
#include "diva_pci.h"
#include "mi_pc.h"
#include "pc_maint.h"
#include "dsp_tst.h"
#include "diva_dma.h"
#include "dsrv_pri.h"

/* --------------------------------------------------------------------------
   OS Dependent part of XDI driver for DIVA PRI Adapter

   DSP detection/validation by Anthony Booth (Eicon Networks, www.eicon.com)
<<<<<<< HEAD
   -------------------------------------------------------------------------- */

#define DIVA_PRI_NO_PCI_BIOS_WORKAROUND 1

extern int diva_card_read_xlog(diva_os_xdi_adapter_t *a);
=======
-------------------------------------------------------------------------- */

#define DIVA_PRI_NO_PCI_BIOS_WORKAROUND 1

extern int diva_card_read_xlog(diva_os_xdi_adapter_t * a);
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip

/*
**  IMPORTS
*/
extern void prepare_pri_functions(PISDN_ADAPTER IoAdapter);
extern void prepare_pri2_functions(PISDN_ADAPTER IoAdapter);
extern void diva_xdi_display_adapter_features(int card);

<<<<<<< HEAD
static int diva_pri_cleanup_adapter(diva_os_xdi_adapter_t *a);
static int diva_pri_cmd_card_proc(struct _diva_os_xdi_adapter *a,
				  diva_xdi_um_cfg_cmd_t *cmd, int length);
static int pri_get_serial_number(diva_os_xdi_adapter_t *a);
static int diva_pri_stop_adapter(diva_os_xdi_adapter_t *a);
static dword diva_pri_detect_dsps(diva_os_xdi_adapter_t *a);
=======
static int diva_pri_cleanup_adapter(diva_os_xdi_adapter_t * a);
static int diva_pri_cmd_card_proc(struct _diva_os_xdi_adapter *a,
				  diva_xdi_um_cfg_cmd_t * cmd, int length);
static int pri_get_serial_number(diva_os_xdi_adapter_t * a);
static int diva_pri_stop_adapter(diva_os_xdi_adapter_t * a);
static dword diva_pri_detect_dsps(diva_os_xdi_adapter_t * a);
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip

/*
**  Check card revision
*/
static int pri_is_rev_2_card(int card_ordinal)
{
	switch (card_ordinal) {
	case CARDTYPE_DIVASRV_P_30M_V2_PCI:
	case CARDTYPE_DIVASRV_VOICE_P_30M_V2_PCI:
		return (1);
	}
	return (0);
}

<<<<<<< HEAD
static void diva_pri_set_addresses(diva_os_xdi_adapter_t *a)
=======
static void diva_pri_set_addresses(diva_os_xdi_adapter_t * a)
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
{
	a->resources.pci.mem_type_id[MEM_TYPE_ADDRESS] = 0;
	a->resources.pci.mem_type_id[MEM_TYPE_CONTROL] = 2;
	a->resources.pci.mem_type_id[MEM_TYPE_CONFIG] = 4;
	a->resources.pci.mem_type_id[MEM_TYPE_RAM] = 0;
	a->resources.pci.mem_type_id[MEM_TYPE_RESET] = 2;
	a->resources.pci.mem_type_id[MEM_TYPE_CFG] = 4;
	a->resources.pci.mem_type_id[MEM_TYPE_PROM] = 3;
<<<<<<< HEAD

=======
	
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
	a->xdi_adapter.Address = a->resources.pci.addr[0];
	a->xdi_adapter.Control = a->resources.pci.addr[2];
	a->xdi_adapter.Config = a->resources.pci.addr[4];

	a->xdi_adapter.ram = a->resources.pci.addr[0];
	a->xdi_adapter.ram += MP_SHARED_RAM_OFFSET;

	a->xdi_adapter.reset = a->resources.pci.addr[2];
	a->xdi_adapter.reset += MP_RESET;

	a->xdi_adapter.cfg = a->resources.pci.addr[4];
	a->xdi_adapter.cfg += MP_IRQ_RESET;

	a->xdi_adapter.sdram_bar = a->resources.pci.bar[0];

	a->xdi_adapter.prom = a->resources.pci.addr[3];
}

/*
**  BAR0 - SDRAM, MP_MEMORY_SIZE, MP2_MEMORY_SIZE by Rev.2
**  BAR1 - DEVICES,				0x1000
**  BAR2 - CONTROL (REG), 0x2000
**  BAR3 - FLASH (REG),		0x8000
**  BAR4 - CONFIG (CFG),	0x1000
*/
<<<<<<< HEAD
int diva_pri_init_card(diva_os_xdi_adapter_t *a)
=======
int diva_pri_init_card(diva_os_xdi_adapter_t * a)
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
{
	int bar = 0;
	int pri_rev_2;
	unsigned long bar_length[5] = {
		MP_MEMORY_SIZE,
		0x1000,
		0x2000,
		0x8000,
		0x1000
	};

	pri_rev_2 = pri_is_rev_2_card(a->CardOrdinal);

	if (pri_rev_2) {
		bar_length[0] = MP2_MEMORY_SIZE;
	}
	/*
<<<<<<< HEAD
	  Set properties
	*/
	a->xdi_adapter.Properties = CardProperties[a->CardOrdinal];
	DBG_LOG(("Load %s", a->xdi_adapter.Properties.Name))

		/*
		  First initialization step: get and check hardware resoures.
		  Do not map resources and do not acecess card at this step
		*/
		for (bar = 0; bar < 5; bar++) {
			a->resources.pci.bar[bar] =
				divasa_get_pci_bar(a->resources.pci.bus,
						   a->resources.pci.func, bar,
						   a->resources.pci.hdev);
			if (!a->resources.pci.bar[bar]
			    || (a->resources.pci.bar[bar] == 0xFFFFFFF0)) {
				DBG_ERR(("A: invalid bar[%d]=%08x", bar,
					 a->resources.pci.bar[bar]))
					return (-1);
			}
		}
	a->resources.pci.irq =
		(byte) divasa_get_pci_irq(a->resources.pci.bus,
					  a->resources.pci.func,
					  a->resources.pci.hdev);
=======
	   Set properties
	 */
	a->xdi_adapter.Properties = CardProperties[a->CardOrdinal];
	DBG_LOG(("Load %s", a->xdi_adapter.Properties.Name))

	/*
	   First initialization step: get and check hardware resoures.
	   Do not map resources and do not acecess card at this step
	 */
	for (bar = 0; bar < 5; bar++) {
		a->resources.pci.bar[bar] =
		    divasa_get_pci_bar(a->resources.pci.bus,
				       a->resources.pci.func, bar,
				       a->resources.pci.hdev);
		if (!a->resources.pci.bar[bar]
		    || (a->resources.pci.bar[bar] == 0xFFFFFFF0)) {
			DBG_ERR(("A: invalid bar[%d]=%08x", bar,
				 a->resources.pci.bar[bar]))
			return (-1);
		}
	}
	a->resources.pci.irq =
	    (byte) divasa_get_pci_irq(a->resources.pci.bus,
				      a->resources.pci.func,
				      a->resources.pci.hdev);
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
	if (!a->resources.pci.irq) {
		DBG_ERR(("A: invalid irq"));
		return (-1);
	}

	/*
<<<<<<< HEAD
	  Map all BAR's
	*/
	for (bar = 0; bar < 5; bar++) {
		a->resources.pci.addr[bar] =
			divasa_remap_pci_bar(a, bar, a->resources.pci.bar[bar],
					     bar_length[bar]);
		if (!a->resources.pci.addr[bar]) {
			DBG_ERR(("A: A(%d), can't map bar[%d]",
				 a->controller, bar))
				diva_pri_cleanup_adapter(a);
=======
	   Map all BAR's
	 */
	for (bar = 0; bar < 5; bar++) {
		a->resources.pci.addr[bar] =
		    divasa_remap_pci_bar(a, bar, a->resources.pci.bar[bar],
					 bar_length[bar]);
		if (!a->resources.pci.addr[bar]) {
			DBG_ERR(("A: A(%d), can't map bar[%d]",
				 a->controller, bar))
			diva_pri_cleanup_adapter(a);
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
			return (-1);
		}
	}

	/*
<<<<<<< HEAD
	  Set all memory areas
	*/
	diva_pri_set_addresses(a);

	/*
	  Get Serial Number of this adapter
	*/
=======
	   Set all memory areas
	 */
	diva_pri_set_addresses(a);

	/*
	   Get Serial Number of this adapter
	 */
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
	if (pri_get_serial_number(a)) {
		dword serNo;
		serNo = a->resources.pci.bar[1] & 0xffff0000;
		serNo |= ((dword) a->resources.pci.bus) << 8;
		serNo += (a->resources.pci.func + a->controller + 1);
		a->xdi_adapter.serialNo = serNo & ~0xFF000000;
		DBG_ERR(("A: A(%d) can't get Serial Number, generated serNo=%ld",
			 a->controller, a->xdi_adapter.serialNo))
<<<<<<< HEAD
			}


	/*
	  Initialize os objects
	*/
=======
	}


	/*
	   Initialize os objects
	 */
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
	if (diva_os_initialize_spin_lock(&a->xdi_adapter.isr_spin_lock, "isr")) {
		diva_pri_cleanup_adapter(a);
		return (-1);
	}
	if (diva_os_initialize_spin_lock
	    (&a->xdi_adapter.data_spin_lock, "data")) {
		diva_pri_cleanup_adapter(a);
		return (-1);
	}

	strcpy(a->xdi_adapter.req_soft_isr.dpc_thread_name, "kdivasprid");

	if (diva_os_initialize_soft_isr(&a->xdi_adapter.req_soft_isr,
					DIDpcRoutine, &a->xdi_adapter)) {
		diva_pri_cleanup_adapter(a);
		return (-1);
	}

	/*
<<<<<<< HEAD
	  Do not initialize second DPC - only one thread will be created
	*/
	a->xdi_adapter.isr_soft_isr.object =
		a->xdi_adapter.req_soft_isr.object;

	/*
	  Next step of card initialization:
	  set up all interface pointers
	*/
=======
	   Do not initialize second DPC - only one thread will be created
	 */
	a->xdi_adapter.isr_soft_isr.object =
	    a->xdi_adapter.req_soft_isr.object;

	/*
	   Next step of card initialization:
	   set up all interface pointers
	 */
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
	a->xdi_adapter.Channels = CardProperties[a->CardOrdinal].Channels;
	a->xdi_adapter.e_max = CardProperties[a->CardOrdinal].E_info;

	a->xdi_adapter.e_tbl =
<<<<<<< HEAD
		diva_os_malloc(0, a->xdi_adapter.e_max * sizeof(E_INFO));
=======
	    diva_os_malloc(0, a->xdi_adapter.e_max * sizeof(E_INFO));
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
	if (!a->xdi_adapter.e_tbl) {
		diva_pri_cleanup_adapter(a);
		return (-1);
	}
	memset(a->xdi_adapter.e_tbl, 0x00, a->xdi_adapter.e_max * sizeof(E_INFO));

	a->xdi_adapter.a.io = &a->xdi_adapter;
	a->xdi_adapter.DIRequest = request;
	a->interface.cleanup_adapter_proc = diva_pri_cleanup_adapter;
	a->interface.cmd_proc = diva_pri_cmd_card_proc;

	if (pri_rev_2) {
		prepare_pri2_functions(&a->xdi_adapter);
	} else {
		prepare_pri_functions(&a->xdi_adapter);
	}

	a->dsp_mask = diva_pri_detect_dsps(a);

	/*
<<<<<<< HEAD
	  Allocate DMA map
	*/
=======
	   Allocate DMA map
	 */
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
	if (pri_rev_2) {
		diva_init_dma_map(a->resources.pci.hdev,
				  (struct _diva_dma_map_entry **) &a->xdi_adapter.dma_map, 32);
	}

	/*
<<<<<<< HEAD
	  Set IRQ handler
	*/
=======
	   Set IRQ handler
	 */
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
	a->xdi_adapter.irq_info.irq_nr = a->resources.pci.irq;
	sprintf(a->xdi_adapter.irq_info.irq_name,
		"DIVA PRI %ld", (long) a->xdi_adapter.serialNo);

	if (diva_os_register_irq(a, a->xdi_adapter.irq_info.irq_nr,
				 a->xdi_adapter.irq_info.irq_name)) {
		diva_pri_cleanup_adapter(a);
		return (-1);
	}
	a->xdi_adapter.irq_info.registered = 1;

	diva_log_info("%s IRQ:%d SerNo:%d", a->xdi_adapter.Properties.Name,
		      a->resources.pci.irq, a->xdi_adapter.serialNo);

	return (0);
}

<<<<<<< HEAD
static int diva_pri_cleanup_adapter(diva_os_xdi_adapter_t *a)
=======
static int diva_pri_cleanup_adapter(diva_os_xdi_adapter_t * a)
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
{
	int bar = 0;

	/*
<<<<<<< HEAD
	  Stop Adapter if adapter is running
	*/
=======
	   Stop Adapter if adapter is running
	 */
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
	if (a->xdi_adapter.Initialized) {
		diva_pri_stop_adapter(a);
	}

	/*
<<<<<<< HEAD
	  Remove ISR Handler
	*/
=======
	   Remove ISR Handler
	 */
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
	if (a->xdi_adapter.irq_info.registered) {
		diva_os_remove_irq(a, a->xdi_adapter.irq_info.irq_nr);
	}
	a->xdi_adapter.irq_info.registered = 0;

	/*
<<<<<<< HEAD
	  Step 1: unmap all BAR's, if any was mapped
	*/
=======
	   Step 1: unmap all BAR's, if any was mapped
	 */
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
	for (bar = 0; bar < 5; bar++) {
		if (a->resources.pci.bar[bar]
		    && a->resources.pci.addr[bar]) {
			divasa_unmap_pci_bar(a->resources.pci.addr[bar]);
			a->resources.pci.bar[bar] = 0;
			a->resources.pci.addr[bar] = NULL;
		}
	}

	/*
<<<<<<< HEAD
	  Free OS objects
	*/
=======
	   Free OS objects
	 */
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
	diva_os_cancel_soft_isr(&a->xdi_adapter.isr_soft_isr);
	diva_os_cancel_soft_isr(&a->xdi_adapter.req_soft_isr);

	diva_os_remove_soft_isr(&a->xdi_adapter.req_soft_isr);
	a->xdi_adapter.isr_soft_isr.object = NULL;

	diva_os_destroy_spin_lock(&a->xdi_adapter.isr_spin_lock, "rm");
	diva_os_destroy_spin_lock(&a->xdi_adapter.data_spin_lock, "rm");

	/*
<<<<<<< HEAD
	  Free memory accupied by XDI adapter
	*/
=======
	   Free memory accupied by XDI adapter
	 */
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
	if (a->xdi_adapter.e_tbl) {
		diva_os_free(0, a->xdi_adapter.e_tbl);
		a->xdi_adapter.e_tbl = NULL;
	}
	a->xdi_adapter.Channels = 0;
	a->xdi_adapter.e_max = 0;


	/*
<<<<<<< HEAD
	  Free adapter DMA map
	*/
=======
	   Free adapter DMA map
	 */
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
	diva_free_dma_map(a->resources.pci.hdev,
			  (struct _diva_dma_map_entry *) a->xdi_adapter.
			  dma_map);
	a->xdi_adapter.dma_map = NULL;


	/*
<<<<<<< HEAD
	  Detach this adapter from debug driver
	*/
=======
	   Detach this adapter from debug driver
	 */
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip

	return (0);
}

/*
**  Activate On Board Boot Loader
*/
static int diva_pri_reset_adapter(PISDN_ADAPTER IoAdapter)
{
	dword i;
	struct mp_load __iomem *boot;

	if (!IoAdapter->Address || !IoAdapter->reset) {
		return (-1);
	}
	if (IoAdapter->Initialized) {
		DBG_ERR(("A: A(%d) can't reset PRI adapter - please stop first",
			 IoAdapter->ANum))
<<<<<<< HEAD
			return (-1);
=======
		return (-1);
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
	}

	boot = (struct mp_load __iomem *) DIVA_OS_MEM_ATTACH_ADDRESS(IoAdapter);
	WRITE_DWORD(&boot->err, 0);
	DIVA_OS_MEM_DETACH_ADDRESS(IoAdapter, boot);

	IoAdapter->rstFnc(IoAdapter);

	diva_os_wait(10);

	boot = (struct mp_load __iomem *) DIVA_OS_MEM_ATTACH_ADDRESS(IoAdapter);
	i = READ_DWORD(&boot->live);

	diva_os_wait(10);
	if (i == READ_DWORD(&boot->live)) {
		DIVA_OS_MEM_DETACH_ADDRESS(IoAdapter, boot);
		DBG_ERR(("A: A(%d) CPU on PRI %ld is not alive!",
			 IoAdapter->ANum, IoAdapter->serialNo))
<<<<<<< HEAD
			return (-1);
=======
		return (-1);
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
	}
	if (READ_DWORD(&boot->err)) {
		DBG_ERR(("A: A(%d) PRI %ld Board Selftest failed, error=%08lx",
			 IoAdapter->ANum, IoAdapter->serialNo,
			 READ_DWORD(&boot->err)))
<<<<<<< HEAD
			DIVA_OS_MEM_DETACH_ADDRESS(IoAdapter, boot);
=======
		DIVA_OS_MEM_DETACH_ADDRESS(IoAdapter, boot);
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
		return (-1);
	}
	DIVA_OS_MEM_DETACH_ADDRESS(IoAdapter, boot);

	/*
<<<<<<< HEAD
	  Forget all outstanding entities
	*/
=======
	   Forget all outstanding entities
	 */
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
	IoAdapter->e_count = 0;
	if (IoAdapter->e_tbl) {
		memset(IoAdapter->e_tbl, 0x00,
		       IoAdapter->e_max * sizeof(E_INFO));
	}
	IoAdapter->head = 0;
	IoAdapter->tail = 0;
	IoAdapter->assign = 0;
	IoAdapter->trapped = 0;

	memset(&IoAdapter->a.IdTable[0], 0x00,
	       sizeof(IoAdapter->a.IdTable));
	memset(&IoAdapter->a.IdTypeTable[0], 0x00,
	       sizeof(IoAdapter->a.IdTypeTable));
	memset(&IoAdapter->a.FlowControlIdTable[0], 0x00,
	       sizeof(IoAdapter->a.FlowControlIdTable));
	memset(&IoAdapter->a.FlowControlSkipTable[0], 0x00,
	       sizeof(IoAdapter->a.FlowControlSkipTable));
	memset(&IoAdapter->a.misc_flags_table[0], 0x00,
	       sizeof(IoAdapter->a.misc_flags_table));
	memset(&IoAdapter->a.rx_stream[0], 0x00,
	       sizeof(IoAdapter->a.rx_stream));
	memset(&IoAdapter->a.tx_stream[0], 0x00,
	       sizeof(IoAdapter->a.tx_stream));
	memset(&IoAdapter->a.tx_pos[0], 0x00, sizeof(IoAdapter->a.tx_pos));
	memset(&IoAdapter->a.rx_pos[0], 0x00, sizeof(IoAdapter->a.rx_pos));

	return (0);
}

static int
diva_pri_write_sdram_block(PISDN_ADAPTER IoAdapter,
			   dword address,
<<<<<<< HEAD
			   const byte *data, dword length, dword limit)
=======
			   const byte * data, dword length, dword limit)
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
{
	byte __iomem *p = DIVA_OS_MEM_ATTACH_ADDRESS(IoAdapter);
	byte __iomem *mem = p;

	if (((address + length) >= limit) || !mem) {
		DIVA_OS_MEM_DETACH_ADDRESS(IoAdapter, p);
		DBG_ERR(("A: A(%d) write PRI address=0x%08lx",
			 IoAdapter->ANum, address + length))
<<<<<<< HEAD
			return (-1);
=======
		return (-1);
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
	}
	mem += address;

	/* memcpy_toio(), maybe? */
	while (length--) {
		WRITE_BYTE(mem++, *data++);
	}

	DIVA_OS_MEM_DETACH_ADDRESS(IoAdapter, p);
	return (0);
}

static int
diva_pri_start_adapter(PISDN_ADAPTER IoAdapter,
		       dword start_address, dword features)
{
	dword i;
	int started = 0;
	byte __iomem *p;
	struct mp_load __iomem *boot = (struct mp_load __iomem *) DIVA_OS_MEM_ATTACH_ADDRESS(IoAdapter);
	ADAPTER *a = &IoAdapter->a;

	if (IoAdapter->Initialized) {
		DIVA_OS_MEM_DETACH_ADDRESS(IoAdapter, boot);
		DBG_ERR(("A: A(%d) pri_start_adapter, adapter already running",
			 IoAdapter->ANum))
<<<<<<< HEAD
			return (-1);
=======
		return (-1);
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
	}
	if (!boot) {
		DIVA_OS_MEM_DETACH_ADDRESS(IoAdapter, boot);
		DBG_ERR(("A: PRI %ld can't start, adapter not mapped",
			 IoAdapter->serialNo))
<<<<<<< HEAD
			return (-1);
=======
		return (-1);
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
	}

	sprintf(IoAdapter->Name, "A(%d)", (int) IoAdapter->ANum);
	DBG_LOG(("A(%d) start PRI at 0x%08lx", IoAdapter->ANum,
		 start_address))

<<<<<<< HEAD
		WRITE_DWORD(&boot->addr, start_address);
=======
	WRITE_DWORD(&boot->addr, start_address);
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
	WRITE_DWORD(&boot->cmd, 3);

	for (i = 0; i < 300; ++i) {
		diva_os_wait(10);
		if ((READ_DWORD(&boot->signature) >> 16) == 0x4447) {
			DBG_LOG(("A(%d) Protocol startup time %d.%02d seconds",
				 IoAdapter->ANum, (i / 100), (i % 100)))
<<<<<<< HEAD
				started = 1;
=======
			started = 1;
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
			break;
		}
	}

	if (!started) {
		byte __iomem *p = (byte __iomem *)boot;
		dword TrapId;
		dword debug;
		TrapId = READ_DWORD(&p[0x80]);
		debug = READ_DWORD(&p[0x1c]);
		DBG_ERR(("A(%d) Adapter start failed 0x%08lx, TrapId=%08lx, debug=%08lx",
			 IoAdapter->ANum, READ_DWORD(&boot->signature),
			 TrapId, debug))
<<<<<<< HEAD
			DIVA_OS_MEM_DETACH_ADDRESS(IoAdapter, boot);
=======
		DIVA_OS_MEM_DETACH_ADDRESS(IoAdapter, boot);
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
		if (IoAdapter->trapFnc) {
			(*(IoAdapter->trapFnc)) (IoAdapter);
		}
		IoAdapter->stop(IoAdapter);
		return (-1);
	}
	DIVA_OS_MEM_DETACH_ADDRESS(IoAdapter, boot);

	IoAdapter->Initialized = true;

	/*
<<<<<<< HEAD
	  Check Interrupt
	*/
	IoAdapter->IrqCount = 0;
	p = DIVA_OS_MEM_ATTACH_CFG(IoAdapter);
	WRITE_DWORD(p, (dword)~0x03E00000);
=======
	   Check Interrupt
	 */
	IoAdapter->IrqCount = 0;
	p = DIVA_OS_MEM_ATTACH_CFG(IoAdapter);
	WRITE_DWORD(p, (dword) ~ 0x03E00000);
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
	DIVA_OS_MEM_DETACH_CFG(IoAdapter, p);
	a->ReadyInt = 1;
	a->ram_out(a, &PR_RAM->ReadyInt, 1);

	for (i = 100; !IoAdapter->IrqCount && (i-- > 0); diva_os_wait(10));

	if (!IoAdapter->IrqCount) {
		DBG_ERR(("A: A(%d) interrupt test failed",
			 IoAdapter->ANum))
<<<<<<< HEAD
			IoAdapter->Initialized = false;
=======
		IoAdapter->Initialized = false;
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
		IoAdapter->stop(IoAdapter);
		return (-1);
	}

	IoAdapter->Properties.Features = (word) features;

	diva_xdi_display_adapter_features(IoAdapter->ANum);

	DBG_LOG(("A(%d) PRI adapter successfully started", IoAdapter->ANum))
<<<<<<< HEAD
		/*
		  Register with DIDD
		*/
		diva_xdi_didd_register_adapter(IoAdapter->ANum);
=======
	/*
	   Register with DIDD
	 */
	diva_xdi_didd_register_adapter(IoAdapter->ANum);
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip

	return (0);
}

<<<<<<< HEAD
static void diva_pri_clear_interrupts(diva_os_xdi_adapter_t *a)
=======
static void diva_pri_clear_interrupts(diva_os_xdi_adapter_t * a)
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
{
	PISDN_ADAPTER IoAdapter = &a->xdi_adapter;

	/*
<<<<<<< HEAD
	  clear any pending interrupt
	*/
=======
	   clear any pending interrupt
	 */
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
	IoAdapter->disIrq(IoAdapter);

	IoAdapter->tst_irq(&IoAdapter->a);
	IoAdapter->clr_irq(&IoAdapter->a);
	IoAdapter->tst_irq(&IoAdapter->a);

	/*
<<<<<<< HEAD
	  kill pending dpcs
	*/
=======
	   kill pending dpcs
	 */
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
	diva_os_cancel_soft_isr(&IoAdapter->req_soft_isr);
	diva_os_cancel_soft_isr(&IoAdapter->isr_soft_isr);
}

/*
**  Stop Adapter, but do not unmap/unregister - adapter
**  will be restarted later
*/
<<<<<<< HEAD
static int diva_pri_stop_adapter(diva_os_xdi_adapter_t *a)
=======
static int diva_pri_stop_adapter(diva_os_xdi_adapter_t * a)
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
{
	PISDN_ADAPTER IoAdapter = &a->xdi_adapter;
	int i = 100;

	if (!IoAdapter->ram) {
		return (-1);
	}
	if (!IoAdapter->Initialized) {
		DBG_ERR(("A: A(%d) can't stop PRI adapter - not running",
			 IoAdapter->ANum))
<<<<<<< HEAD
			return (-1);	/* nothing to stop */
=======
		return (-1);	/* nothing to stop */
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
	}
	IoAdapter->Initialized = 0;

	/*
<<<<<<< HEAD
	  Disconnect Adapter from DIDD
	*/
	diva_xdi_didd_remove_adapter(IoAdapter->ANum);

	/*
	  Stop interrupts
	*/
=======
	   Disconnect Adapter from DIDD
	 */
	diva_xdi_didd_remove_adapter(IoAdapter->ANum);

	/*
	   Stop interrupts
	 */
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
	a->clear_interrupts_proc = diva_pri_clear_interrupts;
	IoAdapter->a.ReadyInt = 1;
	IoAdapter->a.ram_inc(&IoAdapter->a, &PR_RAM->ReadyInt);
	do {
		diva_os_sleep(10);
	} while (i-- && a->clear_interrupts_proc);

	if (a->clear_interrupts_proc) {
		diva_pri_clear_interrupts(a);
		a->clear_interrupts_proc = NULL;
		DBG_ERR(("A: A(%d) no final interrupt from PRI adapter",
			 IoAdapter->ANum))
<<<<<<< HEAD
			}
	IoAdapter->a.ReadyInt = 0;

	/*
	  Stop and reset adapter
	*/
=======
	}
	IoAdapter->a.ReadyInt = 0;

	/*
	   Stop and reset adapter
	 */
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
	IoAdapter->stop(IoAdapter);

	return (0);
}

/*
**  Process commands form configuration/download framework and from
**  user mode
**
**  return 0 on success
*/
static int
diva_pri_cmd_card_proc(struct _diva_os_xdi_adapter *a,
<<<<<<< HEAD
		       diva_xdi_um_cfg_cmd_t *cmd, int length)
=======
		       diva_xdi_um_cfg_cmd_t * cmd, int length)
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
{
	int ret = -1;

	if (cmd->adapter != a->controller) {
		DBG_ERR(("A: pri_cmd, invalid controller=%d != %d",
			 cmd->adapter, a->controller))
<<<<<<< HEAD
			return (-1);
=======
		return (-1);
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
	}

	switch (cmd->command) {
	case DIVA_XDI_UM_CMD_GET_CARD_ORDINAL:
		a->xdi_mbox.data_length = sizeof(dword);
		a->xdi_mbox.data =
<<<<<<< HEAD
			diva_os_malloc(0, a->xdi_mbox.data_length);
		if (a->xdi_mbox.data) {
			*(dword *) a->xdi_mbox.data =
				(dword) a->CardOrdinal;
=======
		    diva_os_malloc(0, a->xdi_mbox.data_length);
		if (a->xdi_mbox.data) {
			*(dword *) a->xdi_mbox.data =
			    (dword) a->CardOrdinal;
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
			a->xdi_mbox.status = DIVA_XDI_MBOX_BUSY;
			ret = 0;
		}
		break;

	case DIVA_XDI_UM_CMD_GET_SERIAL_NR:
		a->xdi_mbox.data_length = sizeof(dword);
		a->xdi_mbox.data =
<<<<<<< HEAD
			diva_os_malloc(0, a->xdi_mbox.data_length);
		if (a->xdi_mbox.data) {
			*(dword *) a->xdi_mbox.data =
				(dword) a->xdi_adapter.serialNo;
=======
		    diva_os_malloc(0, a->xdi_mbox.data_length);
		if (a->xdi_mbox.data) {
			*(dword *) a->xdi_mbox.data =
			    (dword) a->xdi_adapter.serialNo;
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
			a->xdi_mbox.status = DIVA_XDI_MBOX_BUSY;
			ret = 0;
		}
		break;

	case DIVA_XDI_UM_CMD_GET_PCI_HW_CONFIG:
		a->xdi_mbox.data_length = sizeof(dword) * 9;
		a->xdi_mbox.data =
<<<<<<< HEAD
			diva_os_malloc(0, a->xdi_mbox.data_length);
=======
		    diva_os_malloc(0, a->xdi_mbox.data_length);
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
		if (a->xdi_mbox.data) {
			int i;
			dword *data = (dword *) a->xdi_mbox.data;

			for (i = 0; i < 8; i++) {
				*data++ = a->resources.pci.bar[i];
			}
			*data++ = (dword) a->resources.pci.irq;
			a->xdi_mbox.status = DIVA_XDI_MBOX_BUSY;
			ret = 0;
		}
		break;

	case DIVA_XDI_UM_CMD_RESET_ADAPTER:
		ret = diva_pri_reset_adapter(&a->xdi_adapter);
		break;

	case DIVA_XDI_UM_CMD_WRITE_SDRAM_BLOCK:
		ret = diva_pri_write_sdram_block(&a->xdi_adapter,
						 cmd->command_data.
						 write_sdram.offset,
<<<<<<< HEAD
						 (byte *)&cmd[1],
=======
						 (byte *) & cmd[1],
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
						 cmd->command_data.
						 write_sdram.length,
						 pri_is_rev_2_card(a->
								   CardOrdinal)
						 ? MP2_MEMORY_SIZE :
						 MP_MEMORY_SIZE);
		break;

	case DIVA_XDI_UM_CMD_STOP_ADAPTER:
		ret = diva_pri_stop_adapter(a);
		break;

	case DIVA_XDI_UM_CMD_START_ADAPTER:
		ret = diva_pri_start_adapter(&a->xdi_adapter,
					     cmd->command_data.start.
					     offset,
					     cmd->command_data.start.
					     features);
		break;

	case DIVA_XDI_UM_CMD_SET_PROTOCOL_FEATURES:
		a->xdi_adapter.features =
<<<<<<< HEAD
			cmd->command_data.features.features;
		a->xdi_adapter.a.protocol_capabilities =
			a->xdi_adapter.features;
		DBG_TRC(("Set raw protocol features (%08x)",
			 a->xdi_adapter.features))
			ret = 0;
=======
		    cmd->command_data.features.features;
		a->xdi_adapter.a.protocol_capabilities =
		    a->xdi_adapter.features;
		DBG_TRC(("Set raw protocol features (%08x)",
			 a->xdi_adapter.features))
		ret = 0;
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
		break;

	case DIVA_XDI_UM_CMD_GET_CARD_STATE:
		a->xdi_mbox.data_length = sizeof(dword);
		a->xdi_mbox.data =
<<<<<<< HEAD
			diva_os_malloc(0, a->xdi_mbox.data_length);
		if (a->xdi_mbox.data) {
			dword *data = (dword *) a->xdi_mbox.data;
			if (!a->xdi_adapter.ram ||
			    !a->xdi_adapter.reset ||
=======
		    diva_os_malloc(0, a->xdi_mbox.data_length);
		if (a->xdi_mbox.data) {
			dword *data = (dword *) a->xdi_mbox.data;
			if (!a->xdi_adapter.ram ||
				!a->xdi_adapter.reset ||
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
			    !a->xdi_adapter.cfg) {
				*data = 3;
			} else if (a->xdi_adapter.trapped) {
				*data = 2;
			} else if (a->xdi_adapter.Initialized) {
				*data = 1;
			} else {
				*data = 0;
			}
			a->xdi_mbox.status = DIVA_XDI_MBOX_BUSY;
			ret = 0;
		}
		break;

	case DIVA_XDI_UM_CMD_READ_XLOG_ENTRY:
		ret = diva_card_read_xlog(a);
		break;

	case DIVA_XDI_UM_CMD_READ_SDRAM:
		if (a->xdi_adapter.Address) {
			if (
<<<<<<< HEAD
				(a->xdi_mbox.data_length =
				 cmd->command_data.read_sdram.length)) {
				if (
					(a->xdi_mbox.data_length +
					 cmd->command_data.read_sdram.offset) <
					a->xdi_adapter.MemorySize) {
					a->xdi_mbox.data =
						diva_os_malloc(0,
							       a->xdi_mbox.
							       data_length);
=======
			    (a->xdi_mbox.data_length =
			     cmd->command_data.read_sdram.length)) {
				if (
				    (a->xdi_mbox.data_length +
				     cmd->command_data.read_sdram.offset) <
				    a->xdi_adapter.MemorySize) {
					a->xdi_mbox.data =
					    diva_os_malloc(0,
							   a->xdi_mbox.
							   data_length);
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
					if (a->xdi_mbox.data) {
						byte __iomem *p = DIVA_OS_MEM_ATTACH_ADDRESS(&a->xdi_adapter);
						byte __iomem *src = p;
						byte *dst = a->xdi_mbox.data;
						dword len = a->xdi_mbox.data_length;

						src += cmd->command_data.read_sdram.offset;

						while (len--) {
							*dst++ = READ_BYTE(src++);
						}
						a->xdi_mbox.status = DIVA_XDI_MBOX_BUSY;
						DIVA_OS_MEM_DETACH_ADDRESS(&a->xdi_adapter, p);
						ret = 0;
					}
				}
			}
		}
		break;

	default:
		DBG_ERR(("A: A(%d) invalid cmd=%d", a->controller,
			 cmd->command))
<<<<<<< HEAD
			}
=======
	}
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip

	return (ret);
}

/*
**  Get Serial Number
*/
<<<<<<< HEAD
static int pri_get_serial_number(diva_os_xdi_adapter_t *a)
=======
static int pri_get_serial_number(diva_os_xdi_adapter_t * a)
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
{
	byte data[64];
	int i;
	dword len = sizeof(data);
	volatile byte __iomem *config;
	volatile byte __iomem *flash;
	byte c;

/*
 *  First set some GT6401x config registers before accessing the BOOT-ROM
 */
<<<<<<< HEAD
	config = DIVA_OS_MEM_ATTACH_CONFIG(&a->xdi_adapter);
=======
 	config = DIVA_OS_MEM_ATTACH_CONFIG(&a->xdi_adapter);
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
	c = READ_BYTE(&config[0xc3c]);
	if (!(c & 0x08)) {
		WRITE_BYTE(&config[0xc3c], c);	/* Base Address enable register */
	}
	WRITE_BYTE(&config[LOW_BOOTCS_DREG], 0x00);
	WRITE_BYTE(&config[HI_BOOTCS_DREG], 0xFF);
<<<<<<< HEAD
	DIVA_OS_MEM_DETACH_CONFIG(&a->xdi_adapter, config);
=======
 	DIVA_OS_MEM_DETACH_CONFIG(&a->xdi_adapter, config);
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
/*
 *  Read only the last 64 bytes of manufacturing data
 */
	memset(data, '\0', len);
<<<<<<< HEAD
	flash = DIVA_OS_MEM_ATTACH_PROM(&a->xdi_adapter);
	for (i = 0; i < len; i++) {
		data[i] = READ_BYTE(&flash[0x8000 - len + i]);
	}
	DIVA_OS_MEM_DETACH_PROM(&a->xdi_adapter, flash);

	config = DIVA_OS_MEM_ATTACH_CONFIG(&a->xdi_adapter);
	WRITE_BYTE(&config[LOW_BOOTCS_DREG], 0xFC);	/* Disable FLASH EPROM access */
	WRITE_BYTE(&config[HI_BOOTCS_DREG], 0xFF);
	DIVA_OS_MEM_DETACH_CONFIG(&a->xdi_adapter, config);
=======
 	flash = DIVA_OS_MEM_ATTACH_PROM(&a->xdi_adapter);
	for (i = 0; i < len; i++) {
		data[i] = READ_BYTE(&flash[0x8000 - len + i]);
	}
 	DIVA_OS_MEM_DETACH_PROM(&a->xdi_adapter, flash);

 	config = DIVA_OS_MEM_ATTACH_CONFIG(&a->xdi_adapter);
	WRITE_BYTE(&config[LOW_BOOTCS_DREG], 0xFC);	/* Disable FLASH EPROM access */
	WRITE_BYTE(&config[HI_BOOTCS_DREG], 0xFF);
 	DIVA_OS_MEM_DETACH_CONFIG(&a->xdi_adapter, config);
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip

	if (memcmp(&data[48], "DIVAserverPR", 12)) {
#if !defined(DIVA_PRI_NO_PCI_BIOS_WORKAROUND)	/* { */
		word cmd = 0, cmd_org;
		void *addr;
		dword addr1, addr3, addr4;
		byte Bus, Slot;
		void *hdev;
		addr4 = a->resources.pci.bar[4];
		addr3 = a->resources.pci.bar[3];	/* flash  */
		addr1 = a->resources.pci.bar[1];	/* unused */

		DBG_ERR(("A: apply Compaq BIOS workaround"))
<<<<<<< HEAD
			DBG_LOG(("%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x",
				 data[0], data[1], data[2], data[3],
				 data[4], data[5], data[6], data[7]))

			Bus = a->resources.pci.bus;
=======
		DBG_LOG(("%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x",
			     data[0], data[1], data[2], data[3],
			     data[4], data[5], data[6], data[7]))

		Bus = a->resources.pci.bus;
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
		Slot = a->resources.pci.func;
		hdev = a->resources.pci.hdev;
		PCIread(Bus, Slot, 0x04, &cmd_org, sizeof(cmd_org), hdev);
		PCIwrite(Bus, Slot, 0x04, &cmd, sizeof(cmd), hdev);

		PCIwrite(Bus, Slot, 0x14, &addr4, sizeof(addr4), hdev);
		PCIwrite(Bus, Slot, 0x20, &addr1, sizeof(addr1), hdev);

		PCIwrite(Bus, Slot, 0x04, &cmd_org, sizeof(cmd_org), hdev);

		addr = a->resources.pci.addr[1];
		a->resources.pci.addr[1] = a->resources.pci.addr[4];
		a->resources.pci.addr[4] = addr;

		addr1 = a->resources.pci.bar[1];
		a->resources.pci.bar[1] = a->resources.pci.bar[4];
		a->resources.pci.bar[4] = addr1;

		/*
<<<<<<< HEAD
		  Try to read Flash again
		*/
		len = sizeof(data);

		config = DIVA_OS_MEM_ATTACH_CONFIG(&a->xdi_adapter);
=======
		   Try to read Flash again
		 */
		len = sizeof(data);

 		config = DIVA_OS_MEM_ATTACH_CONFIG(&a->xdi_adapter);
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
		if (!(config[0xc3c] & 0x08)) {
			config[0xc3c] |= 0x08;	/* Base Address enable register */
		}
		config[LOW_BOOTCS_DREG] = 0x00;
		config[HI_BOOTCS_DREG] = 0xFF;
<<<<<<< HEAD
		DIVA_OS_MEM_DETACH_CONFIG(&a->xdi_adapter, config);

		memset(data, '\0', len);
		flash = DIVA_OS_MEM_ATTACH_PROM(&a->xdi_adapter);
		for (i = 0; i < len; i++) {
			data[i] = flash[0x8000 - len + i];
		}
		DIVA_OS_MEM_ATTACH_PROM(&a->xdi_adapter, flash);
		config = DIVA_OS_MEM_ATTACH_CONFIG(&a->xdi_adapter);
		config[LOW_BOOTCS_DREG] = 0xFC;
		config[HI_BOOTCS_DREG] = 0xFF;
		DIVA_OS_MEM_DETACH_CONFIG(&a->xdi_adapter, config);

		if (memcmp(&data[48], "DIVAserverPR", 12)) {
			DBG_ERR(("A: failed to read serial number"))
				DBG_LOG(("%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x",
					 data[0], data[1], data[2], data[3],
					 data[4], data[5], data[6], data[7]))
				return (-1);
		}
#else				/* } { */
		DBG_ERR(("A: failed to read DIVA signature word"))
			DBG_LOG(("%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x",
				 data[0], data[1], data[2], data[3],
				 data[4], data[5], data[6], data[7]))
			DBG_LOG(("%02x:%02x:%02x:%02x", data[47], data[46],
				 data[45], data[44]))
#endif				/* } */
			}

	a->xdi_adapter.serialNo =
		(data[47] << 24) | (data[46] << 16) | (data[45] << 8) |
		data[44];
=======
 		DIVA_OS_MEM_DETACH_CONFIG(&a->xdi_adapter, config);

		memset(data, '\0', len);
 		flash = DIVA_OS_MEM_ATTACH_PROM(&a->xdi_adapter);
		for (i = 0; i < len; i++) {
			data[i] = flash[0x8000 - len + i];
		}
 		DIVA_OS_MEM_ATTACH_PROM(&a->xdi_adapter, flash);
 		config = DIVA_OS_MEM_ATTACH_CONFIG(&a->xdi_adapter);
		config[LOW_BOOTCS_DREG] = 0xFC;
		config[HI_BOOTCS_DREG] = 0xFF;
 		DIVA_OS_MEM_DETACH_CONFIG(&a->xdi_adapter, config);

		if (memcmp(&data[48], "DIVAserverPR", 12)) {
			DBG_ERR(("A: failed to read serial number"))
			DBG_LOG(("%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x",
				     data[0], data[1], data[2], data[3],
				     data[4], data[5], data[6], data[7]))
			return (-1);
		}
#else				/* } { */
		DBG_ERR(("A: failed to read DIVA signature word"))
		DBG_LOG(("%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x",
			     data[0], data[1], data[2], data[3],
			     data[4], data[5], data[6], data[7]))
		DBG_LOG(("%02x:%02x:%02x:%02x", data[47], data[46],
			     data[45], data[44]))
#endif				/* } */
	}

	a->xdi_adapter.serialNo =
	    (data[47] << 24) | (data[46] << 16) | (data[45] << 8) |
	    data[44];
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
	if (!a->xdi_adapter.serialNo
	    || (a->xdi_adapter.serialNo == 0xffffffff)) {
		a->xdi_adapter.serialNo = 0;
		DBG_ERR(("A: failed to read serial number"))
<<<<<<< HEAD
			return (-1);
	}

	DBG_LOG(("Serial No.          : %ld", a->xdi_adapter.serialNo))
		DBG_TRC(("Board Revision      : %d.%02d", (int) data[41],
			 (int) data[40]))
		DBG_TRC(("PLD revision        : %d.%02d", (int) data[33],
			 (int) data[32]))
		DBG_TRC(("Boot loader version : %d.%02d", (int) data[37],
			 (int) data[36]))

		DBG_TRC(("Manufacturing Date  : %d/%02d/%02d  (yyyy/mm/dd)",
			 (int) ((data[28] > 90) ? 1900 : 2000) +
			 (int) data[28], (int) data[29], (int) data[30]))

		return (0);
=======
		return (-1);
	}

	DBG_LOG(("Serial No.          : %ld", a->xdi_adapter.serialNo))
	DBG_TRC(("Board Revision      : %d.%02d", (int) data[41],
		     (int) data[40]))
	DBG_TRC(("PLD revision        : %d.%02d", (int) data[33],
		     (int) data[32]))
	DBG_TRC(("Boot loader version : %d.%02d", (int) data[37],
		     (int) data[36]))

	DBG_TRC(("Manufacturing Date  : %d/%02d/%02d  (yyyy/mm/dd)",
		     (int) ((data[28] > 90) ? 1900 : 2000) +
		     (int) data[28], (int) data[29], (int) data[30]))

	return (0);
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
}

void diva_os_prepare_pri2_functions(PISDN_ADAPTER IoAdapter)
{
}

void diva_os_prepare_pri_functions(PISDN_ADAPTER IoAdapter)
{
}

/*
**  Checks presence of DSP on board
*/
static int
<<<<<<< HEAD
dsp_check_presence(volatile byte __iomem *addr, volatile byte __iomem *data, int dsp)
=======
dsp_check_presence(volatile byte __iomem * addr, volatile byte __iomem * data, int dsp)
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
{
	word pattern;

	WRITE_WORD(addr, 0x4000);
	WRITE_WORD(data, DSP_SIGNATURE_PROBE_WORD);

	WRITE_WORD(addr, 0x4000);
	pattern = READ_WORD(data);

	if (pattern != DSP_SIGNATURE_PROBE_WORD) {
		DBG_TRC(("W: DSP[%d] %04x(is) != %04x(should)",
			 dsp, pattern, DSP_SIGNATURE_PROBE_WORD))
<<<<<<< HEAD
			return (-1);
=======
		return (-1);
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
	}

	WRITE_WORD(addr, 0x4000);
	WRITE_WORD(data, ~DSP_SIGNATURE_PROBE_WORD);

	WRITE_WORD(addr, 0x4000);
	pattern = READ_WORD(data);

<<<<<<< HEAD
	if (pattern != (word)~DSP_SIGNATURE_PROBE_WORD) {
		DBG_ERR(("A: DSP[%d] %04x(is) != %04x(should)",
			 dsp, pattern, (word)~DSP_SIGNATURE_PROBE_WORD))
			return (-2);
=======
	if (pattern != (word) ~ DSP_SIGNATURE_PROBE_WORD) {
		DBG_ERR(("A: DSP[%d] %04x(is) != %04x(should)",
			 dsp, pattern, (word) ~ DSP_SIGNATURE_PROBE_WORD))
		return (-2);
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
	}

	DBG_TRC(("DSP[%d] present", dsp))

<<<<<<< HEAD
		return (0);
=======
	return (0);
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
}


/*
**  Check if DSP's are present and operating
**  Information about detected DSP's is returned as bit mask
**  Bit 0  - DSP1
**  ...
**  ...
**  ...
**  Bit 29 - DSP30
*/
<<<<<<< HEAD
static dword diva_pri_detect_dsps(diva_os_xdi_adapter_t *a)
=======
static dword diva_pri_detect_dsps(diva_os_xdi_adapter_t * a)
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
{
	byte __iomem *base;
	byte __iomem *p;
	dword ret = 0;
	dword row_offset[7] = {
		0x00000000,
		0x00000800,	/* 1 - ROW 1 */
		0x00000840,	/* 2 - ROW 2 */
		0x00001000,	/* 3 - ROW 3 */
		0x00001040,	/* 4 - ROW 4 */
		0x00000000	/* 5 - ROW 0 */
	};

	byte __iomem *dsp_addr_port;
	byte __iomem *dsp_data_port;
	byte row_state;
	int dsp_row = 0, dsp_index, dsp_num;

	if (!a->xdi_adapter.Control || !a->xdi_adapter.reset) {
		return (0);
	}

	p = DIVA_OS_MEM_ATTACH_RESET(&a->xdi_adapter);
	WRITE_BYTE(p, _MP_RISC_RESET | _MP_DSP_RESET);
	DIVA_OS_MEM_DETACH_RESET(&a->xdi_adapter, p);
	diva_os_wait(5);

	base = DIVA_OS_MEM_ATTACH_CONTROL(&a->xdi_adapter);

	for (dsp_num = 0; dsp_num < 30; dsp_num++) {
		dsp_row = dsp_num / 7 + 1;
		dsp_index = dsp_num % 7;

		dsp_data_port = base;
		dsp_addr_port = base;

		dsp_data_port += row_offset[dsp_row];
		dsp_addr_port += row_offset[dsp_row];

		dsp_data_port += (dsp_index * 8);
		dsp_addr_port += (dsp_index * 8) + 0x80;

		if (!dsp_check_presence
		    (dsp_addr_port, dsp_data_port, dsp_num + 1)) {
			ret |= (1 << dsp_num);
		}
	}
	DIVA_OS_MEM_DETACH_CONTROL(&a->xdi_adapter, base);

	p = DIVA_OS_MEM_ATTACH_RESET(&a->xdi_adapter);
	WRITE_BYTE(p, _MP_RISC_RESET | _MP_LED1 | _MP_LED2);
	DIVA_OS_MEM_DETACH_RESET(&a->xdi_adapter, p);
	diva_os_wait(5);

	/*
<<<<<<< HEAD
	  Verify modules
	*/
=======
	   Verify modules
	 */
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
	for (dsp_row = 0; dsp_row < 4; dsp_row++) {
		row_state = ((ret >> (dsp_row * 7)) & 0x7F);
		if (row_state && (row_state != 0x7F)) {
			for (dsp_index = 0; dsp_index < 7; dsp_index++) {
				if (!(row_state & (1 << dsp_index))) {
					DBG_ERR(("A: MODULE[%d]-DSP[%d] failed",
						 dsp_row + 1,
						 dsp_index + 1))
<<<<<<< HEAD
						}
=======
				}
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
			}
		}
	}

	if (!(ret & 0x10000000)) {
		DBG_ERR(("A: ON BOARD-DSP[1] failed"))
<<<<<<< HEAD
			}
	if (!(ret & 0x20000000)) {
		DBG_ERR(("A: ON BOARD-DSP[2] failed"))
			}

	/*
	  Print module population now
	*/
	DBG_LOG(("+-----------------------+"))
		DBG_LOG(("| DSP MODULE POPULATION |"))
		DBG_LOG(("+-----------------------+"))
		DBG_LOG(("|  1  |  2  |  3  |  4  |"))
		DBG_LOG(("+-----------------------+"))
		DBG_LOG(("|  %s  |  %s  |  %s  |  %s  |",
			 ((ret >> (0 * 7)) & 0x7F) ? "Y" : "N",
			 ((ret >> (1 * 7)) & 0x7F) ? "Y" : "N",
			 ((ret >> (2 * 7)) & 0x7F) ? "Y" : "N",
			 ((ret >> (3 * 7)) & 0x7F) ? "Y" : "N"))
		DBG_LOG(("+-----------------------+"))

		DBG_LOG(("DSP's(present-absent):%08x-%08x", ret,
			 ~ret & 0x3fffffff))

		return (ret);
=======
	}
	if (!(ret & 0x20000000)) {
		DBG_ERR(("A: ON BOARD-DSP[2] failed"))
	}

	/*
	   Print module population now
	 */
	DBG_LOG(("+-----------------------+"))
	DBG_LOG(("| DSP MODULE POPULATION |"))
	DBG_LOG(("+-----------------------+"))
	DBG_LOG(("|  1  |  2  |  3  |  4  |"))
	DBG_LOG(("+-----------------------+"))
	DBG_LOG(("|  %s  |  %s  |  %s  |  %s  |",
		 ((ret >> (0 * 7)) & 0x7F) ? "Y" : "N",
		 ((ret >> (1 * 7)) & 0x7F) ? "Y" : "N",
		 ((ret >> (2 * 7)) & 0x7F) ? "Y" : "N",
		 ((ret >> (3 * 7)) & 0x7F) ? "Y" : "N"))
	DBG_LOG(("+-----------------------+"))

	DBG_LOG(("DSP's(present-absent):%08x-%08x", ret,
		 ~ret & 0x3fffffff))

	return (ret);
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
}
