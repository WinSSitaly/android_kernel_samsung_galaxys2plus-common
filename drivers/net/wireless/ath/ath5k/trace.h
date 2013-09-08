#if !defined(__TRACE_ATH5K_H) || defined(TRACE_HEADER_MULTI_READ)
#define __TRACE_ATH5K_H

#include <linux/tracepoint.h>
<<<<<<< HEAD


#if !defined(CONFIG_ATH5K_TRACER) || defined(__CHECKER__)
=======
#include "base.h"

#ifndef CONFIG_ATH5K_TRACER
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
#undef TRACE_EVENT
#define TRACE_EVENT(name, proto, ...) \
static inline void trace_ ## name(proto) {}
#endif

struct sk_buff;
<<<<<<< HEAD
struct ath5k_txq;
struct ath5k_tx_status;
=======

#define PRIV_ENTRY  __field(struct ath5k_softc *, priv)
#define PRIV_ASSIGN __entry->priv = priv
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip

#undef TRACE_SYSTEM
#define TRACE_SYSTEM ath5k

TRACE_EVENT(ath5k_rx,
<<<<<<< HEAD
	TP_PROTO(struct ath5k_hw *priv, struct sk_buff *skb),
	TP_ARGS(priv, skb),
	TP_STRUCT__entry(
		__field(struct ath5k_hw *, priv)
=======
	TP_PROTO(struct ath5k_softc *priv, struct sk_buff *skb),
	TP_ARGS(priv, skb),
	TP_STRUCT__entry(
		PRIV_ENTRY
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
		__field(unsigned long, skbaddr)
		__dynamic_array(u8, frame, skb->len)
	),
	TP_fast_assign(
<<<<<<< HEAD
		__entry->priv = priv;
=======
		PRIV_ASSIGN;
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
		__entry->skbaddr = (unsigned long) skb;
		memcpy(__get_dynamic_array(frame), skb->data, skb->len);
	),
	TP_printk(
		"[%p] RX skb=%lx", __entry->priv, __entry->skbaddr
	)
);

TRACE_EVENT(ath5k_tx,
<<<<<<< HEAD
	TP_PROTO(struct ath5k_hw *priv, struct sk_buff *skb,
=======
	TP_PROTO(struct ath5k_softc *priv, struct sk_buff *skb,
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
		 struct ath5k_txq *q),

	TP_ARGS(priv, skb, q),

	TP_STRUCT__entry(
<<<<<<< HEAD
		__field(struct ath5k_hw *, priv)
=======
		PRIV_ENTRY
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
		__field(unsigned long, skbaddr)
		__field(u8, qnum)
		__dynamic_array(u8, frame, skb->len)
	),

	TP_fast_assign(
<<<<<<< HEAD
		__entry->priv = priv;
=======
		PRIV_ASSIGN;
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
		__entry->skbaddr = (unsigned long) skb;
		__entry->qnum = (u8) q->qnum;
		memcpy(__get_dynamic_array(frame), skb->data, skb->len);
	),

	TP_printk(
		"[%p] TX skb=%lx q=%d", __entry->priv, __entry->skbaddr,
		__entry->qnum
	)
);

TRACE_EVENT(ath5k_tx_complete,
<<<<<<< HEAD
	TP_PROTO(struct ath5k_hw *priv, struct sk_buff *skb,
=======
	TP_PROTO(struct ath5k_softc *priv, struct sk_buff *skb,
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
		 struct ath5k_txq *q, struct ath5k_tx_status *ts),

	TP_ARGS(priv, skb, q, ts),

	TP_STRUCT__entry(
<<<<<<< HEAD
		__field(struct ath5k_hw *, priv)
=======
		PRIV_ENTRY
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
		__field(unsigned long, skbaddr)
		__field(u8, qnum)
		__field(u8, ts_status)
		__field(s8, ts_rssi)
		__field(u8, ts_antenna)
	),

	TP_fast_assign(
<<<<<<< HEAD
		__entry->priv = priv;
=======
		PRIV_ASSIGN;
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
		__entry->skbaddr = (unsigned long) skb;
		__entry->qnum = (u8) q->qnum;
		__entry->ts_status = ts->ts_status;
		__entry->ts_rssi =  ts->ts_rssi;
		__entry->ts_antenna = ts->ts_antenna;
	),

	TP_printk(
		"[%p] TX end skb=%lx q=%d stat=%x rssi=%d ant=%x",
		__entry->priv, __entry->skbaddr, __entry->qnum,
		__entry->ts_status, __entry->ts_rssi, __entry->ts_antenna
	)
);

#endif /* __TRACE_ATH5K_H */

<<<<<<< HEAD
#if defined(CONFIG_ATH5K_TRACER) && !defined(__CHECKER__)
=======
#ifdef CONFIG_ATH5K_TRACER
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip

#undef TRACE_INCLUDE_PATH
#define TRACE_INCLUDE_PATH ../../drivers/net/wireless/ath/ath5k
#undef TRACE_INCLUDE_FILE
#define TRACE_INCLUDE_FILE trace

#include <trace/define_trace.h>

#endif
