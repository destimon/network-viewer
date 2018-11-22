# network-viewer

## Foreword
Project may have problems with leaks in CLI due to time constraints, but the main
functional implemented and works fine. Daemon memory usage maximum - 0.1%.

Libft - my own C Library. You can see repo in my profile.

## Usage
* Install libpcap, if you don't have already.
`sudo apt-get install libpcap-dev`
* Build project
`make`
* Set rights for socket usage
`sudo chown root:root nviewer; chmod u+s nviewer`
or just run as root
`sudo ./nviewer`

## Task
Create a service that collects statistic about network traffic.

## Requirements
1. A daemon should be implemented that sniffs packets from particular interface. It
saves ip addresses of incoming packets and number of packets from each ip.
2. Time complexity for ip search should be log(N).
3. Statistic should be persistent through reboots.
4. Command line interface (cli) should be implemented - another process that
interacts with the daemon.
5. The cli should support command:
* **start**​ (packets are being sniffed from now on from default iface(eth0))
* **stop**​ (packets are not sniffed)
* **show [ip] count** ​ (print number of packets received from ip address)
* **select iface [iface]** ​ (select interface for sniffing eth0, wlan0, ethN,
wlanN...)
* **stat​ ​ [iface]** ​ show all collected statistics for particular interface, if iface
omitted - for all interfaces.
* ​ **--help** ​ (show usage information)
6. Daemon could be started independently as well as through the cli.
7. Build automation tool should be used (make is preferable).
8. C Programing language is preferable to be used.
9. Would you be so kind as uploading your code on github (or bitbucket). Please, do
not include files for your IDE, etc.
10. It’s up to you to make choice unless otherwise specified.
11. Assessment depends on meeting requirements, clean and safe code and the
faster you finish the better.
