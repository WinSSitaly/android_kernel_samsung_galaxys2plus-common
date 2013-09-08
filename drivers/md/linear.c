/*
   linear.c : Multiple Devices driver for Linux
	      Copyright (C) 1994-96 Marc ZYNGIER
	      <zyngier@ufr-info-p7.ibp.fr> or
	      <maz@gloups.fdn.fr>

   Linear mode management functions.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.
   
   You should have received a copy of the GNU General Public License
   (for example /usr/src/linux/COPYING); if not, write to the Free
   Software Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.  
*/

#include <linux/blkdev.h>
#include <linux/raid/md_u.h>
#include <linux/seq_file.h>
<<<<<<< HEAD
#include <linux/module.h>
=======
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
#include <linux/slab.h>
#include "md.h"
#include "linear.h"

/*
 * find which device holds a particular offset 
 */
<<<<<<< HEAD
static inline struct dev_info *which_dev(struct mddev *mddev, sector_t sector)
{
	int lo, mid, hi;
	struct linear_conf *conf;
=======
static inline dev_info_t *which_dev(mddev_t *mddev, sector_t sector)
{
	int lo, mid, hi;
	linear_conf_t *conf;
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip

	lo = 0;
	hi = mddev->raid_disks - 1;
	conf = rcu_dereference(mddev->private);

	/*
	 * Binary Search
	 */

	while (hi > lo) {

		mid = (hi + lo) / 2;
		if (sector < conf->disks[mid].end_sector)
			hi = mid;
		else
			lo = mid + 1;
	}

	return conf->disks + lo;
}

/**
 *	linear_mergeable_bvec -- tell bio layer if two requests can be merged
 *	@q: request queue
 *	@bvm: properties of new bio
 *	@biovec: the request that could be merged to it.
 *
 *	Return amount of bytes we can take at this offset
 */
static int linear_mergeable_bvec(struct request_queue *q,
				 struct bvec_merge_data *bvm,
				 struct bio_vec *biovec)
{
<<<<<<< HEAD
	struct mddev *mddev = q->queuedata;
	struct dev_info *dev0;
	unsigned long maxsectors, bio_sectors = bvm->bi_size >> 9;
	sector_t sector = bvm->bi_sector + get_start_sect(bvm->bi_bdev);
	int maxbytes = biovec->bv_len;
	struct request_queue *subq;
=======
	mddev_t *mddev = q->queuedata;
	dev_info_t *dev0;
	unsigned long maxsectors, bio_sectors = bvm->bi_size >> 9;
	sector_t sector = bvm->bi_sector + get_start_sect(bvm->bi_bdev);
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip

	rcu_read_lock();
	dev0 = which_dev(mddev, sector);
	maxsectors = dev0->end_sector - sector;
<<<<<<< HEAD
	subq = bdev_get_queue(dev0->rdev->bdev);
	if (subq->merge_bvec_fn) {
		bvm->bi_bdev = dev0->rdev->bdev;
		bvm->bi_sector -= dev0->end_sector - dev0->rdev->sectors;
		maxbytes = min(maxbytes, subq->merge_bvec_fn(subq, bvm,
							     biovec));
	}
=======
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
	rcu_read_unlock();

	if (maxsectors < bio_sectors)
		maxsectors = 0;
	else
		maxsectors -= bio_sectors;

	if (maxsectors <= (PAGE_SIZE >> 9 ) && bio_sectors == 0)
<<<<<<< HEAD
		return maxbytes;

	if (maxsectors > (maxbytes >> 9))
		return maxbytes;
	else
		return maxsectors << 9;
=======
		return biovec->bv_len;
	/* The bytes available at this offset could be really big,
	 * so we cap at 2^31 to avoid overflow */
	if (maxsectors > (1 << (31-9)))
		return 1<<31;
	return maxsectors << 9;
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
}

static int linear_congested(void *data, int bits)
{
<<<<<<< HEAD
	struct mddev *mddev = data;
	struct linear_conf *conf;
=======
	mddev_t *mddev = data;
	linear_conf_t *conf;
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
	int i, ret = 0;

	if (mddev_congested(mddev, bits))
		return 1;

	rcu_read_lock();
	conf = rcu_dereference(mddev->private);

	for (i = 0; i < mddev->raid_disks && !ret ; i++) {
		struct request_queue *q = bdev_get_queue(conf->disks[i].rdev->bdev);
		ret |= bdi_congested(&q->backing_dev_info, bits);
	}

	rcu_read_unlock();
	return ret;
}

<<<<<<< HEAD
static sector_t linear_size(struct mddev *mddev, sector_t sectors, int raid_disks)
{
	struct linear_conf *conf;
=======
static sector_t linear_size(mddev_t *mddev, sector_t sectors, int raid_disks)
{
	linear_conf_t *conf;
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
	sector_t array_sectors;

	rcu_read_lock();
	conf = rcu_dereference(mddev->private);
	WARN_ONCE(sectors || raid_disks,
		  "%s does not support generic reshape\n", __func__);
	array_sectors = conf->array_sectors;
	rcu_read_unlock();

	return array_sectors;
}

<<<<<<< HEAD
static struct linear_conf *linear_conf(struct mddev *mddev, int raid_disks)
{
	struct linear_conf *conf;
	struct md_rdev *rdev;
	int i, cnt;

	conf = kzalloc (sizeof (*conf) + raid_disks*sizeof(struct dev_info),
=======
static linear_conf_t *linear_conf(mddev_t *mddev, int raid_disks)
{
	linear_conf_t *conf;
	mdk_rdev_t *rdev;
	int i, cnt;

	conf = kzalloc (sizeof (*conf) + raid_disks*sizeof(dev_info_t),
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
			GFP_KERNEL);
	if (!conf)
		return NULL;

	cnt = 0;
	conf->array_sectors = 0;

<<<<<<< HEAD
	rdev_for_each(rdev, mddev) {
		int j = rdev->raid_disk;
		struct dev_info *disk = conf->disks + j;
=======
	list_for_each_entry(rdev, &mddev->disks, same_set) {
		int j = rdev->raid_disk;
		dev_info_t *disk = conf->disks + j;
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
		sector_t sectors;

		if (j < 0 || j >= raid_disks || disk->rdev) {
			printk(KERN_ERR "md/linear:%s: disk numbering problem. Aborting!\n",
			       mdname(mddev));
			goto out;
		}

		disk->rdev = rdev;
		if (mddev->chunk_sectors) {
			sectors = rdev->sectors;
			sector_div(sectors, mddev->chunk_sectors);
			rdev->sectors = sectors * mddev->chunk_sectors;
		}

		disk_stack_limits(mddev->gendisk, rdev->bdev,
				  rdev->data_offset << 9);
<<<<<<< HEAD
=======
		/* as we don't honour merge_bvec_fn, we must never risk
		 * violating it, so limit max_segments to 1 lying within
		 * a single page.
		 */
		if (rdev->bdev->bd_disk->queue->merge_bvec_fn) {
			blk_queue_max_segments(mddev->queue, 1);
			blk_queue_segment_boundary(mddev->queue,
						   PAGE_CACHE_SIZE - 1);
		}
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip

		conf->array_sectors += rdev->sectors;
		cnt++;

	}
	if (cnt != raid_disks) {
		printk(KERN_ERR "md/linear:%s: not enough drives present. Aborting!\n",
		       mdname(mddev));
		goto out;
	}

	/*
	 * Here we calculate the device offsets.
	 */
	conf->disks[0].end_sector = conf->disks[0].rdev->sectors;

	for (i = 1; i < raid_disks; i++)
		conf->disks[i].end_sector =
			conf->disks[i-1].end_sector +
			conf->disks[i].rdev->sectors;

	return conf;

out:
	kfree(conf);
	return NULL;
}

<<<<<<< HEAD
static int linear_run (struct mddev *mddev)
{
	struct linear_conf *conf;
	int ret;
=======
static int linear_run (mddev_t *mddev)
{
	linear_conf_t *conf;
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip

	if (md_check_no_bitmap(mddev))
		return -EINVAL;
	conf = linear_conf(mddev, mddev->raid_disks);

	if (!conf)
		return 1;
	mddev->private = conf;
	md_set_array_sectors(mddev, linear_size(mddev, 0, 0));

	blk_queue_merge_bvec(mddev->queue, linear_mergeable_bvec);
	mddev->queue->backing_dev_info.congested_fn = linear_congested;
	mddev->queue->backing_dev_info.congested_data = mddev;
<<<<<<< HEAD

	ret =  md_integrity_register(mddev);
	if (ret) {
		kfree(conf);
		mddev->private = NULL;
	}
	return ret;
}

static int linear_add(struct mddev *mddev, struct md_rdev *rdev)
=======
	return md_integrity_register(mddev);
}

static void free_conf(struct rcu_head *head)
{
	linear_conf_t *conf = container_of(head, linear_conf_t, rcu);
	kfree(conf);
}

static int linear_add(mddev_t *mddev, mdk_rdev_t *rdev)
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
{
	/* Adding a drive to a linear array allows the array to grow.
	 * It is permitted if the new drive has a matching superblock
	 * already on it, with raid_disk equal to raid_disks.
	 * It is achieved by creating a new linear_private_data structure
	 * and swapping it in in-place of the current one.
	 * The current one is never freed until the array is stopped.
	 * This avoids races.
	 */
<<<<<<< HEAD
	struct linear_conf *newconf, *oldconf;
=======
	linear_conf_t *newconf, *oldconf;
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip

	if (rdev->saved_raid_disk != mddev->raid_disks)
		return -EINVAL;

	rdev->raid_disk = rdev->saved_raid_disk;
<<<<<<< HEAD
	rdev->saved_raid_disk = -1;
=======
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip

	newconf = linear_conf(mddev,mddev->raid_disks+1);

	if (!newconf)
		return -ENOMEM;

	oldconf = rcu_dereference(mddev->private);
	mddev->raid_disks++;
	rcu_assign_pointer(mddev->private, newconf);
	md_set_array_sectors(mddev, linear_size(mddev, 0, 0));
	set_capacity(mddev->gendisk, mddev->array_sectors);
	revalidate_disk(mddev->gendisk);
<<<<<<< HEAD
	kfree_rcu(oldconf, rcu);
	return 0;
}

static int linear_stop (struct mddev *mddev)
{
	struct linear_conf *conf = mddev->private;
=======
	call_rcu(&oldconf->rcu, free_conf);
	return 0;
}

static int linear_stop (mddev_t *mddev)
{
	linear_conf_t *conf = mddev->private;
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip

	/*
	 * We do not require rcu protection here since
	 * we hold reconfig_mutex for both linear_add and
	 * linear_stop, so they cannot race.
	 * We should make sure any old 'conf's are properly
	 * freed though.
	 */
	rcu_barrier();
	blk_sync_queue(mddev->queue); /* the unplug fn references 'conf'*/
	kfree(conf);
	mddev->private = NULL;

	return 0;
}

<<<<<<< HEAD
static void linear_make_request(struct mddev *mddev, struct bio *bio)
{
	struct dev_info *tmp_dev;
=======
static int linear_make_request (mddev_t *mddev, struct bio *bio)
{
	dev_info_t *tmp_dev;
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
	sector_t start_sector;

	if (unlikely(bio->bi_rw & REQ_FLUSH)) {
		md_flush_request(mddev, bio);
<<<<<<< HEAD
		return;
=======
		return 0;
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
	}

	rcu_read_lock();
	tmp_dev = which_dev(mddev, bio->bi_sector);
	start_sector = tmp_dev->end_sector - tmp_dev->rdev->sectors;


	if (unlikely(bio->bi_sector >= (tmp_dev->end_sector)
		     || (bio->bi_sector < start_sector))) {
		char b[BDEVNAME_SIZE];

		printk(KERN_ERR
		       "md/linear:%s: make_request: Sector %llu out of bounds on "
		       "dev %s: %llu sectors, offset %llu\n",
		       mdname(mddev),
		       (unsigned long long)bio->bi_sector,
		       bdevname(tmp_dev->rdev->bdev, b),
		       (unsigned long long)tmp_dev->rdev->sectors,
		       (unsigned long long)start_sector);
		rcu_read_unlock();
		bio_io_error(bio);
<<<<<<< HEAD
		return;
=======
		return 0;
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
	}
	if (unlikely(bio->bi_sector + (bio->bi_size >> 9) >
		     tmp_dev->end_sector)) {
		/* This bio crosses a device boundary, so we have to
		 * split it.
		 */
		struct bio_pair *bp;
		sector_t end_sector = tmp_dev->end_sector;

		rcu_read_unlock();

		bp = bio_split(bio, end_sector - bio->bi_sector);

<<<<<<< HEAD
		linear_make_request(mddev, &bp->bio1);
		linear_make_request(mddev, &bp->bio2);
		bio_pair_release(bp);
		return;
=======
		if (linear_make_request(mddev, &bp->bio1))
			generic_make_request(&bp->bio1);
		if (linear_make_request(mddev, &bp->bio2))
			generic_make_request(&bp->bio2);
		bio_pair_release(bp);
		return 0;
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
	}
		    
	bio->bi_bdev = tmp_dev->rdev->bdev;
	bio->bi_sector = bio->bi_sector - start_sector
		+ tmp_dev->rdev->data_offset;
	rcu_read_unlock();
<<<<<<< HEAD
	generic_make_request(bio);
}

static void linear_status (struct seq_file *seq, struct mddev *mddev)
=======

	return 1;
}

static void linear_status (struct seq_file *seq, mddev_t *mddev)
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
{

	seq_printf(seq, " %dk rounding", mddev->chunk_sectors / 2);
}


<<<<<<< HEAD
static struct md_personality linear_personality =
=======
static struct mdk_personality linear_personality =
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
{
	.name		= "linear",
	.level		= LEVEL_LINEAR,
	.owner		= THIS_MODULE,
	.make_request	= linear_make_request,
	.run		= linear_run,
	.stop		= linear_stop,
	.status		= linear_status,
	.hot_add_disk	= linear_add,
	.size		= linear_size,
};

static int __init linear_init (void)
{
	return register_md_personality (&linear_personality);
}

static void linear_exit (void)
{
	unregister_md_personality (&linear_personality);
}


module_init(linear_init);
module_exit(linear_exit);
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Linear device concatenation personality for MD");
MODULE_ALIAS("md-personality-1"); /* LINEAR - deprecated*/
MODULE_ALIAS("md-linear");
MODULE_ALIAS("md-level--1");
