# Acronyms in Computer Networks

## Overview

- RFC: Request for Comments
- IETF: Internet Engineering Task Force
- ITU: International Telecommunication Union
- IEEE: Institute of Electrical and Electronics Engineers

- FDM: Frequency-Division Multiplexing
- STDM: Statistical Time-Division Multiplexing

- ADSL: Asymmetric Digital Subscriber Line
  - DSLAM: Digital Subscriber Line Access Multiplexer
  - CO: Central Office
- HFC: Hybrid Fiber Coax
- Modem: Modulator-Demodulator
  - CMTS: Cable Modem Termination System
- FTTH: Fiber to the Home

- ISP: Internet Service Provider
- ICP: Internet Content Provider
  - DC: Data Center
- IXP: Internet Exchange Point
- PoP: Point of Presence

- SAP: Service Access Point
- IDU: Interface Data Unit
- SDU: Service Data Unit
- PDU: Protocol Data Unit
- ICI: Interface Control Information

## Application Layer

- HTTP: Hypertext Transfer Protocol 
  - TCP port 80
  - Methods: GET, POST, PUT, DELETE
  - Status codes:
    - 200: OK
    - 301: Moved Permanently
    - 304: Not Modified
    - 400: Bad Request
    - 404: Not Found
    - 505: HTTP Version Not Supported
- FTP: File Transfer Protocol
  - TCP port 20, 21
- Telnet: Teletype Network Protocol
- SSH: Secure Shell Protocol
- SMTP: Simple Mail Transfer Protocol
  - TCP port 25
  - MIME: Multipurpose Internet Mail Extensions
- POP3: Post Office Protocol 3
- IMAP: Internet Message Access Protocol
- BGP: TCP port 179

- DNS: Domain Name System
  - UDP port 53
  - TLD: Top-Level Domain
  - RR: Resource Record
    - (Name, TTL, Class, Type, Value)
    - Types:
      - A: Address
      - AAAA: IPv6 Address
      - NS: Name Server
      - MX: Mail Exchange
      - CNAME: Canonical Name
      - TXT: Text
      - HINFO: Host Information
- SNMP: Simple Network Management Protocol
  - UDP port 161, 162
- DHCP: UDP port 67, 68
- RIP: UDP port 520

- CDN: Content Delivery Network
- DASH: Dynamic Adaptive Streaming over HTTP

- TLS: Transport Layer Security
- SSL: Secure Sockets Layer

## Transport Layer

- TCP: Transmission Control Protocol
  - RDT: Reliable Data Transfer
    - GBN: Go-Back-N
    - SR: Selective Repeat
  - MSS: Maximum Segment Size
  - RTT: Round-Trip Time
    - $EstimatedRTT = (1 - \alpha) * EstimatedRTT + \alpha * SampleRTT$, where $\alpha = 0.125$
    - $DevRTT = (1 - \beta) * DevRTT + \beta * |SampleRTT - EstimatedRTT|$, where $\beta = 0.25$
    - $TimeoutInterval = EstimatedRTT + 4 * DevRTT$
  - AIMD: Additive Increase, Multiplicative Decrease
    - SS: Slow Start
    - CA: Congestion Avoidance
    - FR: Fast Recovery

- UDP: User Datagram Protocol
  - UDT: Unreliable Data Transfer
  - EDC: Error Detection and Correction

## Network Layer

- TCAM: Ternary Content Addressable Memory

- HOL: Head-of-Line Blocking

- RR: Round-Robin Scheduling
- WFQ: Weighted Fair Queuing

- IP: Internet Protocol
  - MTU: Maximum Transmission Unit
  - Class A: 1.0.0.0 ~ 127.255.255.255
    - Mask: 255.0.0.0
    - Private: 10.0.0.0 ~ 10.255.255.255
  - Class B: 128.0.0.0 ~ 191.255.255.255
    - Mask: 255.255.0.0
    - Private: 172.16.0.0 ~ 172.31.255.255
  - Class C: 192.0.0.0 ~ 223.255.255.255
    - Mask: 255.255.255.0
    - Private: 192.168.0.0 ~ 192.168.255.255
  - Class D: 224.0.0.0 ~ 239.255.255.255
  - Class E: 240.0.0.0 ~ 247.255.255.255
  - CIDR: Classless Inter-Domain Routing
  - ICANN: Internet Corporation for Assigned Names and Numbers
  - NAT: Network Address Translation
- DHCP: Dynamic Host Configuration Protocol

- LS: Link State Routing
  - Dijkstra's Algorithm
  - OSPF: Open Shortest Path First
  - IS-IS: Intermediate System to Intermediate System
- DS: Distance Vector Routing
  - Bellman-Ford Algorithm
  - RIP: Routing Information Protocol
  - BGP: Border Gateway Protocol
  
- AS: Autonomous System
  - IGP: Interior Gateway Protocol
    - Intra-AS Routing: RIP, OSPF, IGRP
  - EGP: Exterior Gateway Protocol
    - Inter-AS Routing: BGP
  
- ICMP: Internet Control Message Protocol
  
- SDN: Software-Defined Networking

## Link Layer

- NIC: Network Interface Card

- ATM: Asynchronous Transfer Mode

- CRC: Cyclic Redundancy Check

- PPP: Point-to-Point Protocol
- MAC: Media Access Control
- MAP: Multiple Access Protocol
  - TDMA: Time-Division Multiple Access
  - FDMA: Frequency-Division Multiple Access
  - RAP: Random Access Protocol
    - Slotted ALOHA, Pure ALOHA
    - CSMA/CD: Carrier Sense Multiple Access with Collision Detection
      - BEB: Binary Exponential Backoff
    - CSMA/CA: Carrier Sense Multiple Access with Collision Avoidance
  
- ARP: Address Resolution Protocol
  - (IP address, MAC address, TTL)

- MPLS: Multi-Protocol Label Switching