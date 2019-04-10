#include <linux/kernel.h>
#include <linux/linkage.h>
#include <linux/ktime.h>

/* function to get time of day */
/* syscall number 548 */
asmlinkage long sys_get_current_time(struct timespec *tsp){
	getnstimeofday(tsp);
	return 0;
}

/* function to print string to kernel */
/* syscall number 549 */
asmlinkage long sys_print_string(char *s){
	printk("%s", s);
	return 0;
}

