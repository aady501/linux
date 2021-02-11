#include <linux/kernel.h>
#include <linux/syscalls.h>
SYSCALL_DEFINE1(my_sycall, char *, msg)
{
	  char buf[256];
	  long copied = strncpy_from_user(buf, msg, sizeof(buf));
	  if (copied < 0 || copied == sizeof(buf))
		  return -EFAULT;
	  printk(KERN_INFO "my_syscall called with \"%s\"\n", buf);
	  return 0;
}
