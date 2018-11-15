#include <linux/module.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

MODULE_INFO(vermagic, VERMAGIC_STRING);
MODULE_INFO(name, KBUILD_MODNAME);

__visible struct module __this_module
__attribute__((section(".gnu.linkonce.this_module"))) = {
	.name = KBUILD_MODNAME,
	.init = init_module,
#ifdef CONFIG_MODULE_UNLOAD
	.exit = cleanup_module,
#endif
	.arch = MODULE_ARCH_INIT,
};

#ifdef RETPOLINE
MODULE_INFO(retpoline, "Y");
#endif

static const struct modversion_info ____versions[]
__used
__attribute__((section("__versions"))) = {
	{ 0x13e75575, __VMLINUX_SYMBOL_STR(module_layout) },
	{ 0xc1514a3b, __VMLINUX_SYMBOL_STR(free_irq) },
	{ 0xd6b8e852, __VMLINUX_SYMBOL_STR(request_threaded_irq) },
	{ 0xb6c1e257, __VMLINUX_SYMBOL_STR(gpiod_to_irq) },
	{ 0xf64a8ce, __VMLINUX_SYMBOL_STR(gpiod_get_raw_value) },
	{ 0xbaeef7b0, __VMLINUX_SYMBOL_STR(gpio_to_desc) },
	{ 0x403f9529, __VMLINUX_SYMBOL_STR(gpio_request_one) },
	{ 0x5b69f608, __VMLINUX_SYMBOL_STR(__register_chrdev) },
	{ 0x9e52ac12, __VMLINUX_SYMBOL_STR(prepare_to_wait_event) },
	{ 0xfe487975, __VMLINUX_SYMBOL_STR(init_wait_entry) },
	{ 0x1000e51, __VMLINUX_SYMBOL_STR(schedule) },
	{ 0x7435e0e, __VMLINUX_SYMBOL_STR(prepare_to_wait_exclusive) },
	{ 0x4be7fb63, __VMLINUX_SYMBOL_STR(up) },
	{ 0x98dfb43, __VMLINUX_SYMBOL_STR(finish_wait) },
	{ 0xad73041f, __VMLINUX_SYMBOL_STR(autoremove_wake_function) },
	{ 0x1afae5e7, __VMLINUX_SYMBOL_STR(down_interruptible) },
	{ 0xa1c76e0a, __VMLINUX_SYMBOL_STR(_cond_resched) },
	{ 0x4215a929, __VMLINUX_SYMBOL_STR(__wake_up) },
	{ 0x27e1a049, __VMLINUX_SYMBOL_STR(printk) },
	{ 0x2e5810c6, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr1) },
	{ 0xb1ad28e0, __VMLINUX_SYMBOL_STR(__gnu_mcount_nc) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";


MODULE_INFO(srcversion, "03D767D5DA86150A3365E7B");
