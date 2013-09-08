/*
 * videobuf2-dma-contig.c - DMA contig memory allocator for videobuf2
 *
 * Copyright (C) 2010 Samsung Electronics
 *
 * Author: Pawel Osciak <pawel@osciak.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation.
 */

#include <linux/module.h>
#include <linux/slab.h>
#include <linux/dma-mapping.h>

#include <media/videobuf2-core.h>
<<<<<<< HEAD
#include <media/videobuf2-dma-contig.h>
=======
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
#include <media/videobuf2-memops.h>

struct vb2_dc_conf {
	struct device		*dev;
};

struct vb2_dc_buf {
	struct vb2_dc_conf		*conf;
	void				*vaddr;
<<<<<<< HEAD
	dma_addr_t			dma_addr;
=======
	dma_addr_t			paddr;
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
	unsigned long			size;
	struct vm_area_struct		*vma;
	atomic_t			refcount;
	struct vb2_vmarea_handler	handler;
};

static void vb2_dma_contig_put(void *buf_priv);

static void *vb2_dma_contig_alloc(void *alloc_ctx, unsigned long size)
{
	struct vb2_dc_conf *conf = alloc_ctx;
	struct vb2_dc_buf *buf;

	buf = kzalloc(sizeof *buf, GFP_KERNEL);
	if (!buf)
		return ERR_PTR(-ENOMEM);

<<<<<<< HEAD
	buf->vaddr = dma_alloc_coherent(conf->dev, size, &buf->dma_addr,
=======
	buf->vaddr = dma_alloc_coherent(conf->dev, size, &buf->paddr,
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
					GFP_KERNEL);
	if (!buf->vaddr) {
		dev_err(conf->dev, "dma_alloc_coherent of size %ld failed\n",
			size);
		kfree(buf);
		return ERR_PTR(-ENOMEM);
	}

	buf->conf = conf;
	buf->size = size;

	buf->handler.refcount = &buf->refcount;
	buf->handler.put = vb2_dma_contig_put;
	buf->handler.arg = buf;

	atomic_inc(&buf->refcount);

	return buf;
}

static void vb2_dma_contig_put(void *buf_priv)
{
	struct vb2_dc_buf *buf = buf_priv;

	if (atomic_dec_and_test(&buf->refcount)) {
		dma_free_coherent(buf->conf->dev, buf->size, buf->vaddr,
<<<<<<< HEAD
				  buf->dma_addr);
=======
				  buf->paddr);
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
		kfree(buf);
	}
}

static void *vb2_dma_contig_cookie(void *buf_priv)
{
	struct vb2_dc_buf *buf = buf_priv;

<<<<<<< HEAD
	return &buf->dma_addr;
=======
	return &buf->paddr;
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
}

static void *vb2_dma_contig_vaddr(void *buf_priv)
{
	struct vb2_dc_buf *buf = buf_priv;
	if (!buf)
<<<<<<< HEAD
		return NULL;
=======
		return 0;
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip

	return buf->vaddr;
}

static unsigned int vb2_dma_contig_num_users(void *buf_priv)
{
	struct vb2_dc_buf *buf = buf_priv;

	return atomic_read(&buf->refcount);
}

static int vb2_dma_contig_mmap(void *buf_priv, struct vm_area_struct *vma)
{
	struct vb2_dc_buf *buf = buf_priv;

	if (!buf) {
		printk(KERN_ERR "No buffer to map\n");
		return -EINVAL;
	}

<<<<<<< HEAD
	return vb2_mmap_pfn_range(vma, buf->dma_addr, buf->size,
=======
	return vb2_mmap_pfn_range(vma, buf->paddr, buf->size,
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
				  &vb2_common_vm_ops, &buf->handler);
}

static void *vb2_dma_contig_get_userptr(void *alloc_ctx, unsigned long vaddr,
					unsigned long size, int write)
{
	struct vb2_dc_buf *buf;
	struct vm_area_struct *vma;
<<<<<<< HEAD
	dma_addr_t dma_addr = 0;
=======
	dma_addr_t paddr = 0;
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
	int ret;

	buf = kzalloc(sizeof *buf, GFP_KERNEL);
	if (!buf)
		return ERR_PTR(-ENOMEM);

<<<<<<< HEAD
	ret = vb2_get_contig_userptr(vaddr, size, &vma, &dma_addr);
=======
	ret = vb2_get_contig_userptr(vaddr, size, &vma, &paddr);
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
	if (ret) {
		printk(KERN_ERR "Failed acquiring VMA for vaddr 0x%08lx\n",
				vaddr);
		kfree(buf);
		return ERR_PTR(ret);
	}

	buf->size = size;
<<<<<<< HEAD
	buf->dma_addr = dma_addr;
=======
	buf->paddr = paddr;
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
	buf->vma = vma;

	return buf;
}

static void vb2_dma_contig_put_userptr(void *mem_priv)
{
	struct vb2_dc_buf *buf = mem_priv;

	if (!buf)
		return;

	vb2_put_vma(buf->vma);
	kfree(buf);
}

const struct vb2_mem_ops vb2_dma_contig_memops = {
	.alloc		= vb2_dma_contig_alloc,
	.put		= vb2_dma_contig_put,
	.cookie		= vb2_dma_contig_cookie,
	.vaddr		= vb2_dma_contig_vaddr,
	.mmap		= vb2_dma_contig_mmap,
	.get_userptr	= vb2_dma_contig_get_userptr,
	.put_userptr	= vb2_dma_contig_put_userptr,
	.num_users	= vb2_dma_contig_num_users,
};
EXPORT_SYMBOL_GPL(vb2_dma_contig_memops);

void *vb2_dma_contig_init_ctx(struct device *dev)
{
	struct vb2_dc_conf *conf;

	conf = kzalloc(sizeof *conf, GFP_KERNEL);
	if (!conf)
		return ERR_PTR(-ENOMEM);

	conf->dev = dev;

	return conf;
}
EXPORT_SYMBOL_GPL(vb2_dma_contig_init_ctx);

void vb2_dma_contig_cleanup_ctx(void *alloc_ctx)
{
	kfree(alloc_ctx);
}
EXPORT_SYMBOL_GPL(vb2_dma_contig_cleanup_ctx);

MODULE_DESCRIPTION("DMA-contig memory handling routines for videobuf2");
MODULE_AUTHOR("Pawel Osciak <pawel@osciak.com>");
MODULE_LICENSE("GPL");
