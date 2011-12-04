#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
 
static int  printk_init(void)
{
	printk(KERN_EMERG"emergency\n");
	printk(KERN_ALERT"this is an alert\n");
	printk(KERN_CRIT"critical\n");
	printk(KERN_ERR"error\n");
	printk(KERN_WARNING"warning\n");
	printk(KERN_NOTICE"notice\n");
	printk(KERN_INFO"informationg\n");
	printk(KERN_DEBUG"debuging\n");

	return 0;
}

static void printk_exit(void)
{
	return ;
}

module_init(printk_init);
module_exit(printk_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("ydzhang");
