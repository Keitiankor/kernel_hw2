#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/gpio.h>
#include <linux/interrupt.h>

#define GPIO_BUTTON 25

static int button_irq = -1;
static unsigned counter = 0;

static irqreturn_t button_isr(int irq, void *data)
{
	counter++;
	printk(KERN_INFO "Counter is %d\n", counter);
	return IRQ_HANDLED;
}

static int __init sread_init(void)
{
	int ret  = 0;

	printk(KERN_INFO "%s\n", __func__);

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
