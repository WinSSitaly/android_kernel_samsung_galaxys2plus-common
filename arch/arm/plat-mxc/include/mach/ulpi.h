#ifndef __MACH_ULPI_H
#define __MACH_ULPI_H

#ifdef CONFIG_USB_ULPI
<<<<<<< HEAD
struct usb_phy *imx_otg_ulpi_create(unsigned int flags);
#else
static inline struct usb_phy *imx_otg_ulpi_create(unsigned int flags)
=======
struct otg_transceiver *imx_otg_ulpi_create(unsigned int flags);
#else
static inline struct otg_transceiver *imx_otg_ulpi_create(unsigned int flags)
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
{
	return NULL;
}
#endif

<<<<<<< HEAD
extern struct usb_phy_io_ops mxc_ulpi_access_ops;
=======
extern struct otg_io_access_ops mxc_ulpi_access_ops;
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip

#endif /* __MACH_ULPI_H */

