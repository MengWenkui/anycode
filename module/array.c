#include <linux/module.h>
#include <linux/moduleparam.h>    /* Optional, to include module_param() macros */
#include <linux/kernel.h>    /* Optional, to include prink() prototype */
#include <linux/init.h>        /* Optional, to include module_init() macros */
#include <linux/stat.h>        /* Optional, to include S_IRUSR ... */

static int myint = -99;
static char *mystring = "i'm hungry";

static int myintary[]= {1,2,3,4};
static char *mystrary[] = {"apple", "orange", "banana"};
static int nstrs = 3;

module_param(myint, int, S_IRUSR|S_IWUSR);
MODULE_PARM_DESC(myint, "A trial integer");

module_param(mystring, charp, 0);
module_param_array(myintary, int, NULL, 0444);
module_param_array(mystrary, charp, &nstrs, 0664);

static int __init hello_init(void)
{
    int i;

    printk(KERN_INFO "myint is %d\n", myint);
    printk(KERN_INFO "mystring is %s\n", mystring);

    printk(KERN_INFO "myintary are");
    for(i = 0; i < sizeof(myintary)/sizeof(int); i++)
        printk(" %d", myintary[i]);
    printk("\n");

    printk(KERN_INFO "mystrary are");
    for(i=0; i < nstrs; i++)
        printk(" %s", mystrary[i]);
    printk("\n");

    return 0;
}

static void __exit hello_exit(void)
{
}

module_init(hello_init);
module_exit(hello_exit);

