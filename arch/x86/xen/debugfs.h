#ifndef _XEN_DEBUGFS_H
#define _XEN_DEBUGFS_H

struct dentry * __init xen_init_debugfs(void);

<<<<<<< HEAD
struct dentry *xen_debugfs_create_u32_array(const char *name, umode_t mode,
=======
struct dentry *xen_debugfs_create_u32_array(const char *name, mode_t mode,
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
					    struct dentry *parent,
					    u32 *array, unsigned elements);

#endif /* _XEN_DEBUGFS_H */
