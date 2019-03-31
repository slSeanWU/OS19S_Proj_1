#include <linux/kernel.h>
#include <linux/linkage.h>
#include <linux/ktime.h>

/* function to get time of day */
/* syscall number 548 */
asmlinkage struct timespec sys_get_current_time(void){
	struct timespec t;
	getnstimeofday(&t);
	return t;
}

/* function to print string to kernel */
/* syscall number 549 */
asmlinkage void sys_print_string(char s[256]){
	printk("%s", s);
	return;
}

