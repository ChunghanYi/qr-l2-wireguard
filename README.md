# qr-l2-wireguard
<span style="color:#d3d3d3">Quantum Resistant L2 WireGuard for Linux kernel</span>

## How to build and run
  You must first replace this folder with drivers/net/wireguard. <br>
  The wireguard build procedure is the same as it was during the linux kernel build. <br>
  The modification code compared to the original wireguard can be searched with L2_WIREGUARD and QR_WIREGUARD. <br>

```
<main features>
 1) Layer 2 wireguard implemented by Fadis.
 2) Quantum resistant wireguard using CRYSTALS Kyber KEM based on PQClean library.
 3) Original wireguard by Jason A. Donenfeld.
```
## My blog posting for this project
  For more information, please read the blog posting below.<br><br>
  https://slowbootkernelhacks.blogspot.com/2024/12/anatomy-of-layer-2-wireguard-vpn.html <br>
  https://slowbootkernelhacks.blogspot.com/2023/02/nanopi-r4s-pq-wireguard-vpn-router-part.html <br>
  https://slowbootkernelhacks.blogspot.com/2020/09/wireguard-vpn.html <br>
  <br>

## Reference codes
```
  a) L2 wireguard:
     https://speakerdeck.com/fadis/l2-wireguard
  b) PQClean library
     https://github.com/PQClean/PQClean
  c) NanoPi R2S Plus (FriendlyWrt 23.05)
     https://wiki.friendlyelec.com/wiki/index.php/NanoPi_R2S_Plus
```
  <br>
  WireGuard is a registered trademark of Jason A. Donenfeld.

