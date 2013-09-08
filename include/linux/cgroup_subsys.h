/* Add subsystem definitions of the form SUBSYS(<name>) in this
 * file. Surround each one by a line of comment markers so that
 * patches don't collide
 */

/* */

/* */

#ifdef CONFIG_CPUSETS
SUBSYS(cpuset)
#endif

/* */

#ifdef CONFIG_CGROUP_DEBUG
SUBSYS(debug)
#endif

/* */

#ifdef CONFIG_CGROUP_SCHED
SUBSYS(cpu_cgroup)
#endif

/* */

#ifdef CONFIG_CGROUP_CPUACCT
SUBSYS(cpuacct)
#endif

/* */

#ifdef CONFIG_CGROUP_MEM_RES_CTLR
SUBSYS(mem_cgroup)
#endif

/* */

#ifdef CONFIG_CGROUP_DEVICE
SUBSYS(devices)
#endif

/* */

#ifdef CONFIG_CGROUP_FREEZER
SUBSYS(freezer)
#endif

/* */

#ifdef CONFIG_NET_CLS_CGROUP
SUBSYS(net_cls)
#endif

/* */

#ifdef CONFIG_BLK_CGROUP
SUBSYS(blkio)
#endif

<<<<<<< HEAD
/* */

=======
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
#ifdef CONFIG_CGROUP_PERF
SUBSYS(perf)
#endif

/* */
<<<<<<< HEAD

#ifdef CONFIG_NETPRIO_CGROUP
SUBSYS(net_prio)
#endif

/* */
=======
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
