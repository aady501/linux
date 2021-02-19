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
    /* Move pointer to end of string
     * -1 is added as strnlen_user returns length with \0*/
    buf = buf + (len_str - 1);
    for (i = 0; i < len_str - 1; i++) {
      buf--;
      *(buf) = * (buf) + num;
    }
    printk("ENCRYPTED STRING: %s\n", buf);
    kfree(buf);
    return 0;
  } else {
    printk(KERN_ERR "Key out of range, valid range(1-5): %d\n", num);
    return -EINVAL;
  }
}
