
#ifndef _COMEDI_FOPS_H
#define _COMEDI_FOPS_H
<<<<<<< HEAD
#include <linux/types.h>

extern struct class *comedi_class;
extern const struct file_operations comedi_fops;
extern bool comedi_autoconfig;
=======

extern struct class *comedi_class;
extern const struct file_operations comedi_fops;
extern int comedi_autoconfig;
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
extern struct comedi_driver *comedi_drivers;

#endif /* _COMEDI_FOPS_H */
