#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/gpio.h>
#include <linux/interrupt.h>
#include <linux/semaphore.h>

#define GPIO_BUTTON 25
#define DEVICE_NAME "mydrv"

static int button_irq = -1;
static unsigned counter = 0;

static struct semaphore sema;

static DECLARE_WAIT_QUEUE_HEAD(wq);
static int flag = 0;

static int MYDRV_MAJOR;

static irqreturn_t button_isr(int irq, void *data)
{
	counter++;
	printk(KERN_INFO "Counter is %d\n", counter);
	return IRQ_HANDLED;
}

static ssize_t sread_read(struct file *file, char *count, size_t size, loff_t *ppos)
{
	wait_event_interruptible(wq, flag !=0);
	if (down_interruptible(&sema)) return -ERESTARTSYS;
	while (flag == 0){
		DEFINE_WAIT(wait);
		up(&sema);
		prepare_to_wait_exclusive(&wq, &wait, TASK_INTERRUPTIBLE);
		if (flag == 0)
			schedule();
		finish_wait(&wq, &wait);
		if (down_interruptible(&sema)) return -ERESTARTSYS;
	}
	flag = 0;
	up(&sema);


	*count = counter;
	return 0;
}

static long sread_ioctl(struct file *file, unsigned int cmd, unsigned long arg)
{
	printk(KERN_INFO "mydrv_ioctl is invoked \n");
	return 0;
}

static int sread_open(struct inode *inode, struct file *file)
{
	if (MAJOR(inode->i_rdev) != MYDRV_MAJOR)
		return -1;
	return 0;
}

static int sread_release(struct inode *inode, struct file *file)
{
	if (MAJOR(inode->i_rdev) != MYDRV_MAJOR)
		return -1;
	return 0;
}

struct file_operations sread_fops =
{
	.owner = THIS_MODULE,
	.read = sread_read,
	.compat_ioctl = sread_ioctl,
	.open = sread_open,
	.release = sread_release,
};

static int __init sread_init(void)
{
	int ret  = 0;

	printk(KERN_INFO "%s\n", __func__);
	sema_init(&sema, 1);

	if (register_chrdev(MYDRV_MAJOR = 243, DEVICE_NAME, &sread_fops) < 0)
	{
		printk(KERN_INFO "can't be registered \n");
		return MYDRV_MAJOR;
	}

	ret = gpio_request_one(GPIO_BUTTON, GPIOF_IN, "BUTTON");
	if(ret) {
		printk(KERN_ERR "Unable to request GPIO for BUTTON: %d\n", ret);
		return ret;
	}
	printk(KERN_INFO "Current button1 value: %d\n", gpio_get_value(GPIO_BUTTON));

	ret = gpio_to_irq(GPIO_BUTTON);
	if(ret < 0) {
		printk(KERN_ERR "Unable to request IRQ: %d\n", ret);
		return ret;
	}
	button_irq = ret;
	printk(KERN_INFO "Successfully requested BUTTON1 IRQ # %d\n", button_irq);

	ret = request_irq(button_irq, button_isr, IRQF_TRIGGER_RISING, "gpiomod#button1", NULL);
	if(ret) {
		printk(KERN_ERR "Unable to request IRQ: %d\n", ret);
		return ret;
	}

	return 0;
}

static void __exit sread_exit(void)
{
	free_irq(button_irq, NULL);
}

module_init(sread_init);
module_exit(sread_exit);

MODULE_LICENSE("GPL");
