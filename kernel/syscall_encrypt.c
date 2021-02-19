#include <linux/kernel.h>

#include <linux/syscalls.h>

SYSCALL_DEFINE2(s2_encrypt, char * , msg, int, num) {
  if ((num >= 1) && (num <= 5)) {
    char * buf;
    long copied;
    int i = 0;
    int len_str = strnlen_user(msg, 32767);
    if ((buf = (char * ) kmalloc(len_str * sizeof (char), GFP_KERNEL)) == NULL) {
      printk(KERN_ERR "kmalloc failed");
      kfree(buf);
      return -ENOMEM;
    }
    copied = strncpy_from_user(buf, msg, sizeof(buf));
    if (copied < 0) {
      printk(KERN_ERR "Copy failed using strncpy_from_user\n");
      kfree(buf);
      return -EINVAL;
    }
    printk("original string: %s\n", buf);
    while(*(buf + i) != '\0' ){
    	*(buf + i) = *(buf + i) + 1;
	i++;
    }
    printk("encrypted string: %s\n", buf);
    kfree(buf);
    return 0;
  } else {
    printk(KERN_ERR "Key out of range, valid range(1-5): %d\n", num);
    return -EINVAL;
  }
}
