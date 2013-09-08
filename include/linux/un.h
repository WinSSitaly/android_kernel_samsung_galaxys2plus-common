#ifndef _LINUX_UN_H
#define _LINUX_UN_H

<<<<<<< HEAD
#include <linux/socket.h>

#define UNIX_PATH_MAX	108

struct sockaddr_un {
	__kernel_sa_family_t sun_family; /* AF_UNIX */
=======
#define UNIX_PATH_MAX	108

struct sockaddr_un {
	sa_family_t sun_family;	/* AF_UNIX */
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
	char sun_path[UNIX_PATH_MAX];	/* pathname */
};

#endif /* _LINUX_UN_H */
