#!/bin/sh
#
#Configurations for NanoPi R2S Plus: Client side
#

#wg genkey | tee ./privatekey | wg pubkey > ./publickey

ip link add dev wg1 type l2wireguard
wg set wg1 listen-port 51820 private-key ./keys/privatekey peer FppVj8pZvJupnRI9admT8LPiXcwZ4eILHNhfUyU+XWk= allowed-ips 0.0.0.0/0 endpoint 192.168.8.125:51820

ip link set dev wg1 address 56:97:4A:F7:7B:2E
ip link set wg1 up

ifconfig br-lan down
brctl delbr br-lan

ifconfig eth1 0.0.0.0
ifconfig wg1 0.0.0.0

brctl addbr br-lan
brctl addif br -lan eth1
brctl addif br-lan wg1
brctl setfd br-lan 1
brctl stp br-lan 1

ip link set dev br-lan address 56:97:4A:F7:7B:2E
ip link set br-lan up
