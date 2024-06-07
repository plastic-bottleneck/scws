# [🌲] SCWS :: Simple C WebServer [🌲]
> Simple C WebServer should be an example for a minimalistic C based WebServer.  
> It's free to use or copy for anyone. It's meant to be forked, optimized, etc..

## 🔧 Install

> To compile scws from source, you'll need the following apckages preinstalled:

### 📌 Debian
-  libmicrohttpd-dev
```bash
sudo apt update && sudo apt-get install libmicrohttpd-dev
```
### 📌 OpenBSD
-  libmicrohttpd
```bash
doas pkg_add libmicrohttpd
```
### 📌 Gentoo
-  libmicrohttpd
```bash
doas emerge net-libs/libmicrohttpd
```
### 📌 Fedora
-  libmicrohttpd
```bash
sudo dnf install libmicrohttpd-devel
```
### 📌 MacOS
-  libmicrohttpd-dev
```bash
brew install libmicrohttpd
```
---  
### 👉 SCWS install:
```bash
git clone https://github.com/plastic-bottleneck/scws && cd scws
```
```bash
make
```

## 🔧 Usage
> It is important to keep your `index.html` and `style.css` files inside of the root folder of the compiled binary file. You can change the location in the `scws.c` file though.
> To run SCWS, do this (You can also leave the `ip` and `port` option empty to default to your local IPv4 and port 8888):
```bash
./scws [ip] [port]
```
> When the server is running, you should get the following output:
```
[!!] Yay! Server is running on 0.0.0.0:8888
```
> Now go to http://0.0.0.0:8888/ and see the following example website:

![plus](https://github.com/plastic-bottleneck/scws/blob/main/scws_example_webpage.png)

---

> 🍪 Made by Paul alias Plastic Bottleneck  
> GitHub: https://github.com/plastic-bottleneck  
> Check out my own Distro at 1.4Mb! https://github.com/plastic-bottleneck/plus-linux
