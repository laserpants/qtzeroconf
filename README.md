# QtZeroConf

A high-level Zeroconf interface for Qt-based client-server applications. 

(c) 2012 Johannes Hild&eacute;n   
https://github.com/johanneshilden/qtzeroconf  
http://atomic.batcave.net/qtzeroconf/doxygen/

## About zero configuration networking

Zeroconf simplifies the task of finding and connecting to services on a local area network. There are normally three steps involved in this process:

1. registering a service,
2. browsing for available services, and
3. resolving a service to an actual IP address and port.

The first step concerns the server, which could be a hardware device or an application that advertises its service on the network (e.g., a chat or file sharing software). The other two steps enable a client to search for a service of some type and connect to it without having to know the host machine's IP address and port number.

### About Avahi

QtZeroConf uses the Avahi library, which implements the Apple Zeroconf specification to facilitate service discovery on a local network via the mDNS/DNS-SD protocol suite. http://avahi.org/

## QtZeroConf consists of:

### ZConfService

Allows server applications built using Qt's event loop system to announce a Zeroconf service on the local area network.

### ZConfServiceBrowser

This class can be used to handle Zeroconf service discovery in Qt-based client applications. ZConfServiceBrowser uses Qt's signals/slots mechanism to browse asynchronously for available services on the network.

The *browse()* function call is non-blocking and ZConfServiceBrowser will emit *serviceEntryAdded()* when a new service is discovered and *serviceEntryRemoved()* when a service is removed from the network.

### ZConfBrowserWidget

QTreeWidget-based widget that uses ZConfServiceBrowser internally to browse for and display Zeroconf services available on the local network.

### ZConfServiceEntry

This struct is returned by ZConfServiceBrowser and contains details about a particular Zeroconf service on the local network.
