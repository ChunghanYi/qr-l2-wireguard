// SPDX-License-Identifier: GPL-2.0
/*
 * Copyright (C) 2015-2019 Jason A. Donenfeld <Jason@zx2c4.com>. All Rights Reserved.
 */

#include "version.h"
#include "device.h"
#include "noise.h"
#include "queueing.h"
#include "ratelimiter.h"
#include "netlink.h"

#include <uapi/linux/wireguard.h>

#include <linux/init.h>
#include <linux/module.h>
#include <linux/genetlink.h>
#include <net/rtnetlink.h>

static int __init wg_mod_init(void)
{
	int ret;

	ret = wg_allowedips_slab_init();
	if (ret < 0)
		goto err_allowedips;

#ifdef DEBUG
	ret = -ENOTRECOVERABLE;
	if (!wg_allowedips_selftest() || !wg_packet_counter_selftest() ||
	    !wg_ratelimiter_selftest())
		goto err_peer;
#endif
	wg_noise_init();

	ret = wg_peer_init();
	if (ret < 0)
		goto err_peer;

	ret = wg_device_init();
	if (ret < 0)
		goto err_device;

	ret = wg_genetlink_init();
	if (ret < 0)
		goto err_netlink;

	pr_info("WireGuard " WIREGUARD_VERSION " loaded. See www.wireguard.com for information.\n");
	pr_info("Copyright (C) 2015-2019 Jason A. Donenfeld <Jason@zx2c4.com>. All Rights Reserved.\n");
	/*
	 * L2 WireGuard:
	 *  Original author: fadis@quaternion.sakura.ne.jp
	 *  Ported by: chunghan.yi@gmail.com
	 */
#ifdef L2_WIREGUARD
	pr_info("The L2 WireGuard feature added.\n");
#endif
#ifdef QR_WIREGUARD
	pr_info("PQC KEM Algorithm added inside the WireGuard protocol.\n");
	pr_info("Copyright (C) 2024 Chunghan Yi <chunghan.yi@gmail.com>. All Rights Reserved.\n");
#endif

	return 0;

err_netlink:
	wg_device_uninit();
err_device:
	wg_peer_uninit();
err_peer:
	wg_allowedips_slab_uninit();
err_allowedips:
	return ret;
}

static void __exit wg_mod_exit(void)
{
	wg_genetlink_uninit();
	wg_device_uninit();
	wg_peer_uninit();
	wg_allowedips_slab_uninit();
}

module_init(wg_mod_init);
module_exit(wg_mod_exit);
MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("WireGuard secure network tunnel");
MODULE_AUTHOR("Jason A. Donenfeld <Jason@zx2c4.com>");
MODULE_VERSION(WIREGUARD_VERSION);
MODULE_ALIAS_RTNL_LINK(KBUILD_MODNAME);
MODULE_ALIAS_GENL_FAMILY(WG_GENL_NAME);
