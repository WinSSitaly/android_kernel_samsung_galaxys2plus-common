/* (C) 1999-2001 Paul `Rusty' Russell
 * (C) 2002-2006 Netfilter Core Team <coreteam@netfilter.org>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#include <linux/types.h>
<<<<<<< HEAD
#include <linux/export.h>
=======
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
#include <linux/init.h>
#include <linux/ip.h>
#include <linux/udp.h>

#include <linux/netfilter.h>
#include <net/netfilter/nf_nat.h>
#include <net/netfilter/nf_nat_core.h>
#include <net/netfilter/nf_nat_rule.h>
#include <net/netfilter/nf_nat_protocol.h>

static u_int16_t udp_port_rover;

static void
udp_unique_tuple(struct nf_conntrack_tuple *tuple,
<<<<<<< HEAD
		 const struct nf_nat_ipv4_range *range,
=======
		 const struct nf_nat_range *range,
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
		 enum nf_nat_manip_type maniptype,
		 const struct nf_conn *ct)
{
	nf_nat_proto_unique_tuple(tuple, range, maniptype, ct, &udp_port_rover);
}

static bool
udp_manip_pkt(struct sk_buff *skb,
	      unsigned int iphdroff,
	      const struct nf_conntrack_tuple *tuple,
	      enum nf_nat_manip_type maniptype)
{
	const struct iphdr *iph = (struct iphdr *)(skb->data + iphdroff);
	struct udphdr *hdr;
	unsigned int hdroff = iphdroff + iph->ihl*4;
	__be32 oldip, newip;
	__be16 *portptr, newport;

	if (!skb_make_writable(skb, hdroff + sizeof(*hdr)))
		return false;

	iph = (struct iphdr *)(skb->data + iphdroff);
	hdr = (struct udphdr *)(skb->data + hdroff);

<<<<<<< HEAD
	if (maniptype == NF_NAT_MANIP_SRC) {
=======
	if (maniptype == IP_NAT_MANIP_SRC) {
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
		/* Get rid of src ip and src pt */
		oldip = iph->saddr;
		newip = tuple->src.u3.ip;
		newport = tuple->src.u.udp.port;
		portptr = &hdr->source;
	} else {
		/* Get rid of dst ip and dst pt */
		oldip = iph->daddr;
		newip = tuple->dst.u3.ip;
		newport = tuple->dst.u.udp.port;
		portptr = &hdr->dest;
	}
	if (hdr->check || skb->ip_summed == CHECKSUM_PARTIAL) {
		inet_proto_csum_replace4(&hdr->check, skb, oldip, newip, 1);
		inet_proto_csum_replace2(&hdr->check, skb, *portptr, newport,
					 0);
		if (!hdr->check)
			hdr->check = CSUM_MANGLED_0;
	}
	*portptr = newport;
	return true;
}

const struct nf_nat_protocol nf_nat_protocol_udp = {
	.protonum		= IPPROTO_UDP,
<<<<<<< HEAD
=======
	.me			= THIS_MODULE,
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
	.manip_pkt		= udp_manip_pkt,
	.in_range		= nf_nat_proto_in_range,
	.unique_tuple		= udp_unique_tuple,
#if defined(CONFIG_NF_CT_NETLINK) || defined(CONFIG_NF_CT_NETLINK_MODULE)
<<<<<<< HEAD
=======
	.range_to_nlattr	= nf_nat_proto_range_to_nlattr,
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
	.nlattr_to_range	= nf_nat_proto_nlattr_to_range,
#endif
};
