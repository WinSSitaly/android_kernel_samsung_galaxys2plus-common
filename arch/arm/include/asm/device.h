/*
 * Arch specific extensions to struct device
 *
 * This file is released under the GPLv2
 */
#ifndef ASMARM_DEVICE_H
#define ASMARM_DEVICE_H

struct dev_archdata {
#ifdef CONFIG_DMABOUNCE
	struct dmabounce_device_info *dmabounce;
#endif
<<<<<<< HEAD
#ifdef CONFIG_IOMMU_API
	void *iommu; /* private IOMMU data */
#endif
};

struct omap_device;

struct pdev_archdata {
#ifdef CONFIG_ARCH_OMAP
	struct omap_device *od;
#endif
=======
};

struct pdev_archdata {
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
};

#endif
