#include <linux/module.h>
#include <linux/init.h>
#include <linux/kernel.h>

#include <linux/fs.h>
#include <linux/mm.h>
#include <linux/kthread.h>
#include <asm/uaccess.h>
#include <linux/wait.h>
#include <linux/signal.h>
#include <linux/syscalls.h>

#define BUFSIZE 4096

char *src = "srcfile";
char *dest = "destfile";

module_param(src, charp, 0644);
MODULE_PARM_DESC(src, "the source file to copy from");
module_param(dest, charp, 0644);
MODULE_PARM_DESC(dest, "the target file to copy to");


wait_queue_head_t wq;

int kernel_cp(char *from, char *to)
{

	struct file * filp_from = NULL;
	struct file * filp_to = NULL;
	char *buf = NULL;
	int retval = 0;
	int filesize = 0;
	int this_cp = 0;
	int this_op = 0;

	mm_segment_t old_fs;

	filp_from = filp_open(from, O_RDONLY, 0);
	if(!filp_from)
	{
		printk("open %s error\n", from);
		retval = -1;
		goto out;
	}

	filp_to = filp_open(to, O_CREAT | O_WRONLY, 0644);
	if(!filp_to)
	{
		printk("open %s error\n", to);
		retval = -1;
		goto out;
	}

	buf = (char*)kmalloc(BUFSIZE, GFP_KERNEL);
	if(!buf)
	{
		printk("kmalloc error\n");
		retval = -2;
		goto out;
	}

	filesize = filp_from->f_dentry->d_inode->i_size;
	
	old_fs = get_fs();
	set_fs(get_ds());

	while(filesize > 0)
	{
		if(filesize > BUFSIZE)
			this_cp = BUFSIZE;
		else 
			this_cp = filesize;

		
		this_op = filp_from->f_op->read(filp_from, buf, this_cp, &filp_from->f_pos);
		if(this_op < this_cp)
		{
			retval = -3;
			printk("read file %s error\n", from);
			goto out;
		}

		this_op = filp_to->f_op->write(filp_to, buf, this_cp, &filp_to->f_pos);
		if(this_op < this_cp)
		{
			retval = -4;
			printk("write file %s error\n", to);
			goto out;
		}

		filesize -= this_cp;
	}

	set_fs(old_fs);


	filp_close(filp_from, NULL);
	filp_close(filp_to, NULL);	

out:
	if(buf)		
		kfree(buf);
	return retval;
}

int thread_fn(void *data)
{
	printk("in kernel thread\n");
	printk("thread id = %d\n", current->pid);

	if(kernel_cp("srcfile", "destfile"))
	{
		printk("copy error\n");
		return -1;
	}

//	wake_up(&wq);

	send_sig(SIGTERM, (struct task_struct *)data, 1);

	return 0;
}

static int __init cpsig_init(void)
{
	struct task_struct *task = current;

	init_waitqueue_head(&wq);


	//run the thread
	kthread_run(thread_fn, (void*)task, "cpsig-thread");

//	kernel_cp(src, dest);
	printk("task pid = %d\n", current->pid);

	//block all the signals except SIGTERM
//	sigfillset(&current->blocked);
//	sigdelset(&current->blocked, SIGTERM);

	interruptible_sleep_on(&wq);

	return 0;
}

static void __exit cpsig_exit(void)
{
	printk("task over\n");
}

MODULE_AUTHOR("ydzhang");
MODULE_LICENSE("GPL");

module_init(cpsig_init);
module_exit(cpsig_exit);

