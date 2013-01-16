//#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/namei.h>
#include <linux/dcache.h>
#include <linux/string.h>
#include <linux/slab.h>


#define TEST_PATH "/home/ydzhang"
#define MAX_PATH  256

static int get_path(struct dentry *dentry, char attr, char *full_path)
{
	struct dentry *tmp_dentry = dentry;
	char tmp_path[MAX_PATH];
	tmp_path[MAX_PATH-1] = '\0';
        char *path_ptr = tmp_path + MAX_PATH - 1;

	while(1)
	{
		if(!strcmp(tmp_dentry->d_name.name, "/"))
		{
			path_ptr -= 1;
			strncpy(path_ptr, "/", 1);
			break;
		}
		else
		{
			path_ptr -= strlen(tmp_dentry->d_name.name);
			strncpy(path_ptr, tmp_dentry->d_name.name, 
					strlen(tmp_dentry->d_name.name));
                        path_ptr -= 1;
			strncpy(path_ptr, "/", 1);
			/*
			 strcat(full_path, tmp_dentry->d_name.name);
			 strcat(full_path, "/");
			*/
			tmp_dentry = tmp_dentry->d_parent;
		}
	}
	strcpy(full_path, path_ptr);
	return 0;
}


static int dentry_init(void)
{
    struct nameidata namei;
    int err = path_lookup(TEST_PATH, LOOKUP_FOLLOW, &namei);
    if(err)
    {
	    printk("path_lookup error\n");
    }
    printk("dentry result = %s\n", namei.dentry->d_name.name);   

    char *full_path = (char*)kmalloc(MAX_PATH, GFP_KERNEL);
    get_path(namei.dentry, 'f', full_path); 
    printk(KERN_WARNING"full path = %s\n", full_path);
    kfree(full_path);

    return 0;
}

static void dentry_exit(void)
{
    return ;
}

module_init(dentry_init);
module_exit(dentry_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("ydzhang");


