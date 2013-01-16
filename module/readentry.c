//#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/namei.h>
#include <linux/dcache.h>
#include <linux/list.h>


#define TEST_PATH "/home/ydzhang/"

static int dentry_init(void)
{
    struct nameidata namei;
    int err = path_lookup(TEST_PATH, LOOKUP_FOLLOW, &namei);
    if(err)
    {
	    printk("path_lookup error\n");
    }
    struct list_head *head = &namei.dentry->d_subdirs;
    struct list_head *pos = head->next;
    
    for(; pos != head; pos = pos->next)
    {
	    struct dentry *tmp_dentry = list_entry(pos, 
			    struct dentry, d_u.d_child);
	    printk("%s\n", tmp_dentry->d_name.name);
    }

    return 0;
}

static void dentry_exit(void)
{
    return;
}

module_init(dentry_init);
module_exit(dentry_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("ydzhang");


