#include <linux/build-salt.h>
#include <linux/module.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

BUILD_SALT;

MODULE_INFO(vermagic, VERMAGIC_STRING);
MODULE_INFO(name, KBUILD_MODNAME);

__visible struct module __this_module
__section(.gnu.linkonce.this_module) = {
	.name = KBUILD_MODNAME,
	.init = init_module,
#ifdef CONFIG_MODULE_UNLOAD
	.exit = cleanup_module,
#endif
	.arch = MODULE_ARCH_INIT,
};

#ifdef CONFIG_RETPOLINE
MODULE_INFO(retpoline, "Y");
#endif

static const struct modversion_info ____versions[]
__used __section(__versions) = {
	{ 0xdd8f8694, "module_layout" },
	{ 0x12bae5b3, "class_unregister" },
	{ 0x5e04e317, "device_destroy" },
	{ 0x999e8297, "vfree" },
	{ 0xb65e5a32, "class_destroy" },
	{ 0xebaeddf7, "device_create" },
	{ 0x6bc3fbc0, "__unregister_chrdev" },
	{ 0x2871e975, "__class_create" },
	{ 0x9a19ed29, "__register_chrdev" },
	{ 0xb44ad4b3, "_copy_to_user" },
	{ 0x88db9f48, "__check_object_size" },
	{ 0x754d539c, "strlen" },
	{ 0x362ef408, "_copy_from_user" },
	{ 0xd6ee688f, "vmalloc" },
	{ 0xc5850110, "printk" },
	{ 0xbdfb6dbb, "__fentry__" },
};

MODULE_INFO(depends, "");


MODULE_INFO(srcversion, "789FA711FBD477F512EC323");
