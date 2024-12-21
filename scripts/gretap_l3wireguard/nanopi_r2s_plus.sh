#!/bin/sh

#
#Configurations for NanoPi R2S Plus: Client side
#

# wg genkey | tee ./privatekey | wg pubkey > ./publickey

ip link add dev wg0 type wireguard
ip address add dev wg0 10.1.1.1/24
ip link set wg0 mtu 1402 up

wg set wg0 listen-port 51820 private-key ./keys/privatekey peer FppVj8pZvJupnRI9admT8LPiXcwZ4eILHNhfUyU+XWk= allowed-ips 0.0.0.0/0 endpoint 192.168.8.125:51820

ip link add name gretap1 type gretap local 10.1.1.1 remote 10.1.1.2
ip link set gretap1 up

ifconfig br-lan down
brctl delbr br-lan
ifconfig eth1 0.0.0.0

brctl addbr br-lan
brctl addif br -lan eth1
brctl addif br-lan gretap1

brctl setfd br-lan 1
brctl stp br-lan 1
ip link set br-lan up
