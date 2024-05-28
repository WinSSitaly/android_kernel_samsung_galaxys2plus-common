/*
 * various internal comedi functions
 */
int do_rangeinfo_ioctl(struct comedi_device *dev,
		       struct comedi_rangeinfo __user *arg);
int insn_inval(struct comedi_device *dev, struct comedi_subdevice *s,
	       struct comedi_insn *insn, unsigned int *data);
int comedi_alloc_board_minor(struct device *hardware_device);
void comedi_free_board_minor(unsigned minor);
<<<<<<< HEAD
int comedi_find_board_minor(struct device *hardware_device);
=======
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
void comedi_reset_async_buf(struct comedi_async *async);
int comedi_buf_alloc(struct comedi_device *dev, struct comedi_subdevice *s,
		     unsigned long new_size);
