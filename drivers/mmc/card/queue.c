/*
 *  linux/drivers/mmc/card/queue.c
 *
 *  Copyright (C) 2003 Russell King, All Rights Reserved.
 *  Copyright 2006-2007 Pierre Ossman
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 */
#include <linux/slab.h>
#include <linux/module.h>
#include <linux/blkdev.h>
#include <linux/freezer.h>
#include <linux/kthread.h>
#include <linux/scatterlist.h>

#include <linux/mmc/card.h>
#include <linux/mmc/host.h>
#include "queue.h"

#define MMC_QUEUE_BOUNCESZ	65536

#define MMC_QUEUE_SUSPENDED	(1 << 0)

/*
 * Prepare a MMC request. This just filters out odd stuff.
 */
static int mmc_prep_request(struct request_queue *q, struct request *req)
{
<<<<<<< HEAD
	struct mmc_queue *mq = q->queuedata;

=======
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
	/*
	 * We only like normal block requests and discards.
	 */
	if (req->cmd_type != REQ_TYPE_FS && !(req->cmd_flags & REQ_DISCARD)) {
		blk_dump_rq_flags(req, "MMC bad request");
		return BLKPREP_KILL;
	}

<<<<<<< HEAD
	if (mq && mmc_card_removed(mq->card))
		return BLKPREP_KILL;

=======
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
	req->cmd_flags |= REQ_DONTPREP;

	return BLKPREP_OK;
}

static int mmc_queue_thread(void *d)
{
	struct mmc_queue *mq = d;
	struct request_queue *q = mq->queue;

	current->flags |= PF_MEMALLOC;

	down(&mq->thread_sem);
	do {
		struct request *req = NULL;
<<<<<<< HEAD
		struct mmc_queue_req *tmp;
=======
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip

		spin_lock_irq(q->queue_lock);
		set_current_state(TASK_INTERRUPTIBLE);
		req = blk_fetch_request(q);
<<<<<<< HEAD
		mq->mqrq_cur->req = req;
		spin_unlock_irq(q->queue_lock);

		if (req || mq->mqrq_prev->req) {
			set_current_state(TASK_RUNNING);
			mq->issue_fn(mq, req);
		} else {
=======
		mq->req = req;
		spin_unlock_irq(q->queue_lock);

		if (!req) {
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
			if (kthread_should_stop()) {
				set_current_state(TASK_RUNNING);
				break;
			}
			up(&mq->thread_sem);
			schedule();
			down(&mq->thread_sem);
<<<<<<< HEAD
		}

		/* Current request becomes previous request and vice versa. */
		mq->mqrq_prev->brq.mrq.data = NULL;
		mq->mqrq_prev->req = NULL;
		tmp = mq->mqrq_prev;
		mq->mqrq_prev = mq->mqrq_cur;
		mq->mqrq_cur = tmp;
=======
			continue;
		}
		set_current_state(TASK_RUNNING);

		mq->issue_fn(mq, req);
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
	} while (1);
	up(&mq->thread_sem);

	return 0;
}

/*
 * Generic MMC request handler.  This is called for any queue on a
 * particular host.  When the host is not busy, we look for a request
 * on any queue on this host, and attempt to issue it.  This may
 * not be the queue we were asked to process.
 */
static void mmc_request(struct request_queue *q)
{
	struct mmc_queue *mq = q->queuedata;
	struct request *req;

	if (!mq) {
		while ((req = blk_fetch_request(q)) != NULL) {
			req->cmd_flags |= REQ_QUIET;
			__blk_end_request_all(req, -EIO);
		}
		return;
	}

<<<<<<< HEAD
	if (!mq->mqrq_cur->req && !mq->mqrq_prev->req)
		wake_up_process(mq->thread);
}

static struct scatterlist *mmc_alloc_sg(int sg_len, int *err)
{
	struct scatterlist *sg;

	sg = kmalloc(sizeof(struct scatterlist)*sg_len, GFP_KERNEL);
	if (!sg)
		*err = -ENOMEM;
	else {
		*err = 0;
		sg_init_table(sg, sg_len);
	}

	return sg;
}

=======
	if (!mq->req)
		wake_up_process(mq->thread);
}

#ifdef CONFIG_MMC_DISCARD_SUPPORT
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
static void mmc_queue_setup_discard(struct request_queue *q,
				    struct mmc_card *card)
{
	unsigned max_discard;

	max_discard = mmc_calc_max_discard(card);
	if (!max_discard)
		return;

	queue_flag_set_unlocked(QUEUE_FLAG_DISCARD, q);
	q->limits.max_discard_sectors = max_discard;
<<<<<<< HEAD
	if (card->erased_byte == 0 && !mmc_can_discard(card))
=======
	if (card->erased_byte == 0)
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
		q->limits.discard_zeroes_data = 1;
	q->limits.discard_granularity = card->pref_erase << 9;
	/* granularity must not be greater than max. discard */
	if (card->pref_erase > max_discard)
		q->limits.discard_granularity = 0;
	if (mmc_can_secure_erase_trim(card) || mmc_can_sanitize(card))
		queue_flag_set_unlocked(QUEUE_FLAG_SECDISCARD, q);
}
<<<<<<< HEAD
=======
#endif
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip

/**
 * mmc_init_queue - initialise a queue structure.
 * @mq: mmc queue
 * @card: mmc card to attach this queue
 * @lock: queue lock
 * @subname: partition subname
 *
 * Initialise a MMC card request queue.
 */
int mmc_init_queue(struct mmc_queue *mq, struct mmc_card *card,
		   spinlock_t *lock, const char *subname)
{
	struct mmc_host *host = card->host;
	u64 limit = BLK_BOUNCE_HIGH;
	int ret;
<<<<<<< HEAD
	struct mmc_queue_req *mqrq_cur = &mq->mqrq[0];
	struct mmc_queue_req *mqrq_prev = &mq->mqrq[1];
=======
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip

	if (mmc_dev(host)->dma_mask && *mmc_dev(host)->dma_mask)
		limit = *mmc_dev(host)->dma_mask;

	mq->card = card;
	mq->queue = blk_init_queue(mmc_request, lock);
	if (!mq->queue)
		return -ENOMEM;

<<<<<<< HEAD
	memset(&mq->mqrq_cur, 0, sizeof(mq->mqrq_cur));
	memset(&mq->mqrq_prev, 0, sizeof(mq->mqrq_prev));
	mq->mqrq_cur = mqrq_cur;
	mq->mqrq_prev = mqrq_prev;
	mq->queue->queuedata = mq;

	blk_queue_prep_rq(mq->queue, mmc_prep_request);
	queue_flag_set_unlocked(QUEUE_FLAG_NONROT, mq->queue);
	if (mmc_can_erase(card))
		mmc_queue_setup_discard(mq->queue, card);
=======
	mq->queue->queuedata = mq;
	mq->req = NULL;

	blk_queue_prep_rq(mq->queue, mmc_prep_request);
	queue_flag_set_unlocked(QUEUE_FLAG_NONROT, mq->queue);

	if (mmc_can_erase(card)) {
#ifdef CONFIG_MMC_DISCARD_SUPPORT
		if (mmc_can_discard(card)) {
			mmc_queue_setup_discard(mq->queue, card);
		} else {
#endif
			queue_flag_set_unlocked(QUEUE_FLAG_DISCARD, mq->queue);
			mq->queue->limits.max_discard_sectors = UINT_MAX;
			if (card->erased_byte == 0)
				mq->queue->limits.discard_zeroes_data = 1;
			mq->queue->limits.discard_granularity = card->pref_erase << 9;
			if (mmc_can_secure_erase_trim(card))
				queue_flag_set_unlocked(QUEUE_FLAG_SECDISCARD,
							mq->queue);
#ifdef CONFIG_MMC_DISCARD_SUPPORT
		}
#endif
	}
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip

#ifdef CONFIG_MMC_BLOCK_BOUNCE
	if (host->max_segs == 1) {
		unsigned int bouncesz;

		bouncesz = MMC_QUEUE_BOUNCESZ;

		if (bouncesz > host->max_req_size)
			bouncesz = host->max_req_size;
		if (bouncesz > host->max_seg_size)
			bouncesz = host->max_seg_size;
		if (bouncesz > (host->max_blk_count * 512))
			bouncesz = host->max_blk_count * 512;

		if (bouncesz > 512) {
<<<<<<< HEAD
			mqrq_cur->bounce_buf = kmalloc(bouncesz, GFP_KERNEL);
			if (!mqrq_cur->bounce_buf) {
				pr_warning("%s: unable to "
					"allocate bounce cur buffer\n",
					mmc_card_name(card));
			}
			mqrq_prev->bounce_buf = kmalloc(bouncesz, GFP_KERNEL);
			if (!mqrq_prev->bounce_buf) {
				pr_warning("%s: unable to "
					"allocate bounce prev buffer\n",
					mmc_card_name(card));
				kfree(mqrq_cur->bounce_buf);
				mqrq_cur->bounce_buf = NULL;
			}
		}

		if (mqrq_cur->bounce_buf && mqrq_prev->bounce_buf) {
=======
			mq->bounce_buf = kmalloc(bouncesz, GFP_KERNEL);
			if (!mq->bounce_buf) {
				printk(KERN_WARNING "%s: unable to "
					"allocate bounce buffer\n",
					mmc_card_name(card));
			}
		}

		if (mq->bounce_buf) {
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
			blk_queue_bounce_limit(mq->queue, BLK_BOUNCE_ANY);
			blk_queue_max_hw_sectors(mq->queue, bouncesz / 512);
			blk_queue_max_segments(mq->queue, bouncesz / 512);
			blk_queue_max_segment_size(mq->queue, bouncesz);

<<<<<<< HEAD
			mqrq_cur->sg = mmc_alloc_sg(1, &ret);
			if (ret)
				goto cleanup_queue;

			mqrq_cur->bounce_sg =
				mmc_alloc_sg(bouncesz / 512, &ret);
			if (ret)
				goto cleanup_queue;

			mqrq_prev->sg = mmc_alloc_sg(1, &ret);
			if (ret)
				goto cleanup_queue;

			mqrq_prev->bounce_sg =
				mmc_alloc_sg(bouncesz / 512, &ret);
			if (ret)
				goto cleanup_queue;
=======
			mq->sg = kmalloc(sizeof(struct scatterlist),
				GFP_KERNEL);
			if (!mq->sg) {
				ret = -ENOMEM;
				goto cleanup_queue;
			}
			sg_init_table(mq->sg, 1);

			mq->bounce_sg = kmalloc(sizeof(struct scatterlist) *
				bouncesz / 512, GFP_KERNEL);
			if (!mq->bounce_sg) {
				ret = -ENOMEM;
				goto cleanup_queue;
			}
			sg_init_table(mq->bounce_sg, bouncesz / 512);
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
		}
	}
#endif

<<<<<<< HEAD
	if (!mqrq_cur->bounce_buf && !mqrq_prev->bounce_buf) {
=======
	if (!mq->bounce_buf) {
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
		blk_queue_bounce_limit(mq->queue, limit);
		blk_queue_max_hw_sectors(mq->queue,
			min(host->max_blk_count, host->max_req_size / 512));
		blk_queue_max_segments(mq->queue, host->max_segs);
		blk_queue_max_segment_size(mq->queue, host->max_seg_size);

<<<<<<< HEAD
		mqrq_cur->sg = mmc_alloc_sg(host->max_segs, &ret);
		if (ret)
			goto cleanup_queue;


		mqrq_prev->sg = mmc_alloc_sg(host->max_segs, &ret);
		if (ret)
			goto cleanup_queue;
=======
		mq->sg = kmalloc(sizeof(struct scatterlist) *
			host->max_segs, GFP_KERNEL);
		if (!mq->sg) {
			ret = -ENOMEM;
			goto cleanup_queue;
		}
		sg_init_table(mq->sg, host->max_segs);
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
	}

	sema_init(&mq->thread_sem, 1);

	mq->thread = kthread_run(mmc_queue_thread, mq, "mmcqd/%d%s",
		host->index, subname ? subname : "");

	if (IS_ERR(mq->thread)) {
		ret = PTR_ERR(mq->thread);
		goto free_bounce_sg;
	}

	return 0;
 free_bounce_sg:
<<<<<<< HEAD
	kfree(mqrq_cur->bounce_sg);
	mqrq_cur->bounce_sg = NULL;
	kfree(mqrq_prev->bounce_sg);
	mqrq_prev->bounce_sg = NULL;

 cleanup_queue:
	kfree(mqrq_cur->sg);
	mqrq_cur->sg = NULL;
	kfree(mqrq_cur->bounce_buf);
	mqrq_cur->bounce_buf = NULL;

	kfree(mqrq_prev->sg);
	mqrq_prev->sg = NULL;
	kfree(mqrq_prev->bounce_buf);
	mqrq_prev->bounce_buf = NULL;

=======
 	if (mq->bounce_sg)
 		kfree(mq->bounce_sg);
 	mq->bounce_sg = NULL;
 cleanup_queue:
 	if (mq->sg)
		kfree(mq->sg);
	mq->sg = NULL;
	if (mq->bounce_buf)
		kfree(mq->bounce_buf);
	mq->bounce_buf = NULL;
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
	blk_cleanup_queue(mq->queue);
	return ret;
}

void mmc_cleanup_queue(struct mmc_queue *mq)
{
	struct request_queue *q = mq->queue;
	unsigned long flags;
<<<<<<< HEAD
	struct mmc_queue_req *mqrq_cur = mq->mqrq_cur;
	struct mmc_queue_req *mqrq_prev = mq->mqrq_prev;
=======
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip

	/* Make sure the queue isn't suspended, as that will deadlock */
	mmc_queue_resume(mq);

	/* Then terminate our worker thread */
	kthread_stop(mq->thread);

	/* Empty the queue */
	spin_lock_irqsave(q->queue_lock, flags);
	q->queuedata = NULL;
	blk_start_queue(q);
	spin_unlock_irqrestore(q->queue_lock, flags);

<<<<<<< HEAD
	kfree(mqrq_cur->bounce_sg);
	mqrq_cur->bounce_sg = NULL;

	kfree(mqrq_cur->sg);
	mqrq_cur->sg = NULL;

	kfree(mqrq_cur->bounce_buf);
	mqrq_cur->bounce_buf = NULL;

	kfree(mqrq_prev->bounce_sg);
	mqrq_prev->bounce_sg = NULL;

	kfree(mqrq_prev->sg);
	mqrq_prev->sg = NULL;

	kfree(mqrq_prev->bounce_buf);
	mqrq_prev->bounce_buf = NULL;
=======
 	if (mq->bounce_sg)
 		kfree(mq->bounce_sg);
 	mq->bounce_sg = NULL;

	kfree(mq->sg);
	mq->sg = NULL;

	if (mq->bounce_buf)
		kfree(mq->bounce_buf);
	mq->bounce_buf = NULL;
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip

	mq->card = NULL;
}
EXPORT_SYMBOL(mmc_cleanup_queue);

/**
 * mmc_queue_suspend - suspend a MMC request queue
 * @mq: MMC queue to suspend
 *
 * Stop the block request queue, and wait for our thread to
 * complete any outstanding requests.  This ensures that we
 * won't suspend while a request is being processed.
 */
void mmc_queue_suspend(struct mmc_queue *mq)
{
	struct request_queue *q = mq->queue;
	unsigned long flags;

	if (!(mq->flags & MMC_QUEUE_SUSPENDED)) {
		mq->flags |= MMC_QUEUE_SUSPENDED;

		spin_lock_irqsave(q->queue_lock, flags);
		blk_stop_queue(q);
		spin_unlock_irqrestore(q->queue_lock, flags);

		down(&mq->thread_sem);
	}
}

/**
 * mmc_queue_resume - resume a previously suspended MMC request queue
 * @mq: MMC queue to resume
 */
void mmc_queue_resume(struct mmc_queue *mq)
{
	struct request_queue *q = mq->queue;
	unsigned long flags;

	if (mq->flags & MMC_QUEUE_SUSPENDED) {
		mq->flags &= ~MMC_QUEUE_SUSPENDED;

		up(&mq->thread_sem);

		spin_lock_irqsave(q->queue_lock, flags);
		blk_start_queue(q);
		spin_unlock_irqrestore(q->queue_lock, flags);
	}
}

/*
 * Prepare the sg list(s) to be handed of to the host driver
 */
<<<<<<< HEAD
unsigned int mmc_queue_map_sg(struct mmc_queue *mq, struct mmc_queue_req *mqrq)
=======
unsigned int mmc_queue_map_sg(struct mmc_queue *mq)
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
{
	unsigned int sg_len;
	size_t buflen;
	struct scatterlist *sg;
	int i;

<<<<<<< HEAD
	if (!mqrq->bounce_buf)
		return blk_rq_map_sg(mq->queue, mqrq->req, mqrq->sg);

	BUG_ON(!mqrq->bounce_sg);

	sg_len = blk_rq_map_sg(mq->queue, mqrq->req, mqrq->bounce_sg);

	mqrq->bounce_sg_len = sg_len;

	buflen = 0;
	for_each_sg(mqrq->bounce_sg, sg, sg_len, i)
		buflen += sg->length;

	sg_init_one(mqrq->sg, mqrq->bounce_buf, buflen);
=======
	if (!mq->bounce_buf)
		return blk_rq_map_sg(mq->queue, mq->req, mq->sg);

	BUG_ON(!mq->bounce_sg);

	sg_len = blk_rq_map_sg(mq->queue, mq->req, mq->bounce_sg);

	mq->bounce_sg_len = sg_len;

	buflen = 0;
	for_each_sg(mq->bounce_sg, sg, sg_len, i)
		buflen += sg->length;

	sg_init_one(mq->sg, mq->bounce_buf, buflen);
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip

	return 1;
}

/*
 * If writing, bounce the data to the buffer before the request
 * is sent to the host driver
 */
<<<<<<< HEAD
void mmc_queue_bounce_pre(struct mmc_queue_req *mqrq)
{
	if (!mqrq->bounce_buf)
		return;

	if (rq_data_dir(mqrq->req) != WRITE)
		return;

	sg_copy_to_buffer(mqrq->bounce_sg, mqrq->bounce_sg_len,
		mqrq->bounce_buf, mqrq->sg[0].length);
=======
void mmc_queue_bounce_pre(struct mmc_queue *mq)
{
	if (!mq->bounce_buf)
		return;

	if (rq_data_dir(mq->req) != WRITE)
		return;

	sg_copy_to_buffer(mq->bounce_sg, mq->bounce_sg_len,
		mq->bounce_buf, mq->sg[0].length);
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
}

/*
 * If reading, bounce the data from the buffer after the request
 * has been handled by the host driver
 */
<<<<<<< HEAD
void mmc_queue_bounce_post(struct mmc_queue_req *mqrq)
{
	if (!mqrq->bounce_buf)
		return;

	if (rq_data_dir(mqrq->req) != READ)
		return;

	sg_copy_from_buffer(mqrq->bounce_sg, mqrq->bounce_sg_len,
		mqrq->bounce_buf, mqrq->sg[0].length);
}
=======
void mmc_queue_bounce_post(struct mmc_queue *mq)
{
	if (!mq->bounce_buf)
		return;

	if (rq_data_dir(mq->req) != READ)
		return;

	sg_copy_from_buffer(mq->bounce_sg, mq->bounce_sg_len,
		mq->bounce_buf, mq->sg[0].length);
}

>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
