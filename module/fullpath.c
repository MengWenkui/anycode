#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/namei.h>
#include <linux/dcache.h>
#include <linux/string.h>
#include <linux/slab.h>
#include <linux/mount.h>
#include <linux/sched.h>


#define TEST_PATH "/mnt/ext2/home/ydzhang/proc"
#define MAX_ENTRY_LEN  256
#define MAX_ENTRY_DEPTH 10 

static int get_path(struct dentry *dentry, struct vfsmount *mnt, 
		char *full_path)
{
	struct dentry *tmp_dentry = dentry;
	struct vfsmount *tmp_mnt = mnt;
	char tmp_path[MAX_ENTRY_LEN];
	tmp_path[MAX_ENTRY_LEN-1] = '\0';
        char *path_ptr = tmp_path + MAX_ENTRY_LEN - 1;

        int is_top = 0;
	int only_root = 1;

	while(1)
	{
		//if tmp_dentry is the root of fs
		if(tmp_dentry == current->fs->root
				&& tmp_mnt == current->fs->rootmnt)
         	{
			is_top = 1; //can't go up
		}
		//if tmp_dentry is the root of fs
		else if(tmp_dentry == tmp_mnt->mnt_root)
		{
			//if it's mounted by
			if(tmp_mnt != tmp_mnt->mnt_parent)
			{
                              tmp_dentry = mnt->mnt_mountpoint;
			      tmp_mnt = mnt->mnt_parent;
			      only_root = 0;
			}
			else 
			{
				is_top = 1; //can't go up
			}
		}
		else
		{
			path_ptr -= strlen(tmp_dentry->d_name.name);
			strncpy(path_ptr, tmp_dentry->d_name.name, 
					strlen(tmp_dentry->d_name.name));

			//add a "/" separator
			path_ptr -= 1;
                        strncpy(path_ptr, "/", 1);

			tmp_dentry = tmp_dentry->d_parent;

			only_root = 0;
		}

		if(only_root)  //only a slash
		{
			path_ptr -= 1;
			strncpy(path_ptr, "/", 1);
		}
		if(is_top) //toppest
		{
			break;
		}
	}
	strcpy(full_path, path_ptr);
	return 0;
}

//return negative value will lead to insmod fail
static int dentry_init(vstoid)
{
    struct nameidata namei;
    int err = path_lookup(TEST_PATH, LOOKUP_FOLLOW, &namei);
    if(err)
    {
	    printk("path_lookup error\n");
	    return 0;
    }

    /*  here nd stores the lookup result */

    char *full_path = (char*)kmalloc(MAX_ENTRY_LEN * MAX_ENTRY_DEPTH, GFP_KERNEL);
    get_path(namei.dentry, namei.mnt, full_path); 
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


