#!/bin/sh

#
#Configurations for NanoPi R5C : Server side
#

#wg genkey | tee ./privatekey | wg pubkey > ./publickey

ip link add dev wg1 type l2wireguard

wg set wg1 listen-port 51820 private-key ./keys/privatekey peer jkOW74X1CRS8fobzmYYPGDkyVhR5rdEa9uh8QA2O/0k= allowed-ips 0.0.0.0/0 endpoint 192.168.8.182:51820

ip link set dev wg1 address 1E:45:77:76:DE:26
ip link set wg1 up

ifconfig br-lan down
brctl delbr br-lan

ifconfig eth1 0.0.0.0
ifconfig wg1 0.0.0.0

brctl addbr br -lan
brctl addif br-lan eth1
brctl addif br-lan wg1
brctl setfd br-lan 1
brctl stp br-lan 1

#ip link set dev br-lan address 1E:45:77:76:DE:26
ip address add dev br-lan  192.168.3.1/24
ip link set br-lan up

echo 1 > /proc/sys/net/ipv4/conf/br-lan/proxy_arp
