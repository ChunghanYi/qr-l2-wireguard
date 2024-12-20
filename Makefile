ccflags-y := -D'pr_fmt(fmt)=KBUILD_MODNAME ": " fmt'
ccflags-y += -DL2_WIREGUARD
ccflags-y += -I$(srctree)/drivers/net/wireguard/pqc -DQR_WIREGUARD
ccflags-$(CONFIG_WIREGUARD_DEBUG) += -DDEBUG
wireguard-y := main.o
wireguard-y += noise.o
wireguard-y += device.o
wireguard-y += peer.o
wireguard-y += timers.o
wireguard-y += queueing.o
wireguard-y += send.o
wireguard-y += receive.o
wireguard-y += socket.o
wireguard-y += peerlookup.o
wireguard-y += allowedips.o
wireguard-y += ratelimiter.o
wireguard-y += cookie.o
wireguard-y += netlink.o
ccflags-y += -O3 -fvisibility=hidden
ccflags-y += -Wframe-larger-than=2048
wireguard-y += pqc/cbd.o
wireguard-y += pqc/fips202.o
wireguard-y += pqc/indcpa.o
wireguard-y += pqc/kem.o
wireguard-y += pqc/ntt.o
wireguard-y += pqc/poly.o
wireguard-y += pqc/polyvec.o
wireguard-y += pqc/reduce.o
wireguard-y += pqc/symmetric-shake.o
wireguard-y += pqc/verify.o
wireguard-y += pqc/kex.o
obj-$(CONFIG_WIREGUARD) := wireguard.o
