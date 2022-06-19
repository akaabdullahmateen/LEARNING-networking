## Internet protocol suite

The internet protocol suite, commonly known as TCP/IP, is the set of communication protocols used in the internet and similar computer networks. The current foundational protocols in the suite are Transmission Control Protocol (TCP) and the Internet Protocol (IP), as well as the User Datagram Protocol (DCP). The internet protocol suite provides end-to-end data communication specifying how data should be packetized, addressed, transmitted, routed, and received. This functionality is organized into four abstraction layers, which classify all related protocols according to each protocol's scope of networking. From lowest to highest, the layers are the link layer, containing communication methods for data that remains within a single networking segment (link); the internet layer, providing internetworking between independent networks; the transport layer, handling host-to-host communication; and the application layer, providing process-to-process data exchange for applications.

The technical standards underlying the internet protocol suite and its constituent protocols are maintained by the Internet Engineering Task Force (IETF). The internet protocol suite predates the OSI model, a more comprehensive reference framework for general networking systems.

### Key architecture principles

The end-to-end principle has evolved over time. Its original expression put the maintainence of state and overall intelligence at the edges, and assumed the internet that connected to edges retained no state and concentrated on speed and simplicity. Real world needs for firewall, network address translators, web content caches and the like have forced changes in this principle.

The robustness principle states: "In general, an implementation must be conservative in its sending behavior, and liberal in its receiving behavior. That is, it must be careful to send well-formed datagrams, but must accept any datagram that it can interpret (e.g., not object to technical errors where the meaning is still clear)". The second part of the principle is almost as important: "software on other hosts may contain deficiencies that make it unwise to exploit legal but obscure protocol features".

Encapsulation is used to provide abstraction of protocols and services. Encapsulation is usually aligned with the division of the protocol suite into layers of general functionality. In general, an application (the highest level of the model) uses a set of protocols to send its data down the layers. The data is further encapsulated at each level.

An early architectural document, RFC 1122, emphasizes architectural principles over layering. RFC 1122, titled *Host Requirements*, is structured in paragraphs referring to layers, but the document refers to many other architectural principles and does not emphasize layering. It loosely defines a four-layer model, with the layers having names, not numbers, as follows:

- The application layer is the scope within which applications, or process, create user data and communicate this data to other applications on another or the same host. The applications make use of the services provided by the underlying lower layers, especially the transport layer which provides reliable or unreliable pipes to other processes. The communications partners are characterized by the application architecture, such as the client-server model and peer-to-peer networking. This is the layer in which all application protocols, such as SMTP, FTP, SSH, HTTP operate. Processes are addressed via ports which essentially represent services.

- The transport layer performs host-to-host communications on either the local network or remote networks separated by routers. It provides a channel for the communication needs of applications. UDP is the basic transport layer protocol, providing an unreliable connectionless datagram service. The transmission control protocol (TCP) provides flow-control, connection establishment, and reliable transmission of data.

- The internet layer exchanges datagrams across network boundaries. It provides a uniform networking interface that hides the actual topology (layout) of the underlying network connections. It is therefore also the layer that establishes internetworking. Indeed, it defines and establishes the internet. This layer defines the addressing and routing strcutures for the TCP/IP protocol suite. The primary protocol in this scope is the internet protocol (IP), which defines IP addresses. Its function in routing is to transport datagrams to the next host, functioning as an IP router, that has the connectivity to a network closer to the final data destination.

- The link layer defines the networking methods within the scope of the local network link on which hosts communicate without interveing routers. This layer includes the protocols used to describe the local network topology and the interfaces needed to affect the transmission of internet layer datagrams to next-neighbour hosts.

## OSI model

The Open System Interconnection model (OSI model) is a conceptual model that describes the universal standard of communication functions of a telecommunication system or computing system, without any regard to the system's underlying internet technology and specific protocol suites. Therefore, the objective is the interoperability of all diverse communication systems containing standard communication protocols, through the encapsulation and de-encapsulation of data, for all networked communication. In the OSI reference model, the communications between a computing system are split into seven different abstraction layers: Physical, Data link, Network, Transport, Session, Presentation, and Application.

The model partitions the flow of data in a communication system into seven abstraction layers, to describe networked communication from the physical implementation of transmitting bits across a communication medium to the highest-level representation of data of a distributed application. Each intermediate layer serves a class of functionality to the layer above it and is served by the layer below it. Classes of functionality are realized in all software development through all and any standardized communication protocols.

Each layer in the OSI model has its own well-defined functions, and the functions of each layer communicate and interact with the layers immediately above and below it, unless the layer does not have layers below or above. In either case, each layer of the OSI model has its own well-defined functions that describe the basic applications for communication of all communication protocols.

The internet protocol suite has a separate model, the layers are mentioned in RFC 1122 and RFC 1123. That model combines the physical and data link layers of OSI model into a single link layer, and has a single application layer for all protocols above the transport layer, as opposed to the separate application, presentation, and session layers of the OSI model.

In comparison, several networking models have sought to create an intellectual framework for clarifying networking concepts and activities, but none has been successful as the OSI reference model is becoming the standard model for discussing, teaching, and learning for the networking procedures in the field of information technology. Additionally, the model allows transparent communication through equivalent exchange of protocol data units (PDUs) between two parties, through what is known as peer-to-peer networking (also known as peer-to-peer communication). As a result, OSI reference model has not only become an important piece among professionals and non-professionals alike, but also in all networking between one or many parties, due in large part to its commonly accepted user-friendly framework.

| **Layer**    | **Protocol data unit** | **Function** |
|--------------|------------------------|--------------|
| Application  | Data                   | High-level APIs, including resource sharing, remote file access |
| Presentation | Data                   | Translation of data between a networking service and an application; including character encoding, data compression, and encryption/decryption |
| Session      | Data                   | Managing communication session, i.e., continuous exchange of information in the form of multiple back-and-forth transmissions between two nodes |
| Transport    | Segment, Datagram      | Reliable transmission of data segments between points on a network, including segmentation, acknowledgement, and multiplexing |
| Network      | Packet                 | Structuring and managin multi-node network, including addressing, routing, and traffic control |
| Data link    | Frame                  | Transmission of data frames between two nodes connected by a physical layer |
| Physical     | Bit, Symbol            | Transmission and reception of raw bit streams over a physical medium |

## Frame

A frame is a digital data transmission unit in computer networking and telecommunication. In packet switched systems, a frame is a simple container for a single network packet. In other telecommunication systems, a frame is a repeating structure supporting time-division multiplexing. A frame typically includes frame synchronization features consisting of a sequence of bits or symbols that indicate to the receiver the beginning and end of the payload data within the stream of symbols or bits it receives. If a receiver is connected to the system during the frame transmission, it ignores the data until it detects a new frame synchronization sequence.

In the OSI model of computer networking, a frame is the protocol data unit at the data link layer. Frames are the result of the final layer of encapsulation before the data is transmitted over the physical layer. A frame is "the unit of transmission in a link layer protocol, and consists of a link layer header followed by a packet". Each frame is separated from the next by an interframe gap. A frame is a series of bits generally composed of frame synchronization bits, the packet payload, and a frame check sequence. Examples are Ethernet frames, Point-to-Point Protocol (PPP) frames, Fibre Channel frames, and V.42 modem frames.

Often frames of several different sizes are nested inside each other. For example, when using Point-to-Point Protocol (PPP) over asynchronuous serial communication, the eight bits of each individual byte are framed by start and stop bits, the payload data bytes in a network packet are framed by the header and footer, and several packets can be framed with frame boundary octets.

## Network protocols

A protocol defines the format and the order of messages exchanged between two or more communicating entities, as well as the actions taken on the transmission and/or receipt of a message or other event. A communication protocol is a system of rules that allows two or more entities in a communication system to transmit information via any kind of variation of a physical quantity. The protocol defines the rules, syntax, semantics, and synchronization of communication and possible error recovery methods. Protocols may be implemented by hardware, software, or a combination of both. Multiple protocols often describe different aspects of a single communication. A group of protocols designed to work together is called a protocol suite; when implemented in software, they are a protocol stack.

Operating systems usually contains a set of cooperating processes that manipulate shared data to communicate with each other. This communication is governed by well-understood protocols, which can be embedded in the process code itself. In contrast, because there is no shared memory, communication systems have to communicate with each other using a shared transmission medium. Transmission is not necessarily reliable, and individual systems may use different hardware or operating systems.

To implement a networking protocol, the protocol software modules are interfaced with a framework implemented on the machine's operating system. This framework implements the networking functionality of the operating system. When protocol algorithms are expressed in a portable programming language and the protocol software may be made operating system independent. The best known frameworks are the TCP/IP model and the OSI model.

At the time the internet was developed, abstraction layering had proven to be a successful design approach for both compilers and operating system design and, given the similarities between programming languages and communication protocols, the originally monolothic networking prorgrams were decomposed into cooperating protocols. This gave rise to the concept of layered protocols which nowadays forms the basis of protocol design.

Systems typically do not use a single protocol to handle a transmission. Instead they use a set of cooperating protocols, sometimes called a protocol suite. Some of the best known protocol suites are TCP/IP, IPX/SPX, AX.25, and AppleTalk.

The protocols can be arranged based on functionality in groups, for instance, there is a group of transport protocols. The functionalities are mapped onto the layers, each layer solving a distinct class of problems relating to, for instance: application-, transport-, internet-, and network interface-functions. To transmit a message, a protocol has to be selected from each layer. The selection of the next protocol is accomplished by extending the message with a protocol selector for each layer.

## Types of protocols

There are two types of communication protocols, based on their representation of the content being carried: text-based and binary.

### Text-based protocol

A text-based protocol or plain text protocol represents its content in human-readable format, often in plain text. The immediate human readability stands in contrast to binary protocols which have inherent benefits for use in a computer environment (such as ease of mechanical parsing and improved bandwidth utilization).

Network applications have various methods of encapsulating data. One method very common with internet protocols is a text oriented representation that transmits requests and responses as lines of ASCII text, terminated by a newline character (and usually a carriage return character). Examples of protocols that use plain, human-readbale text for its commands are File Transfer Protocol (FTP), Simple Mail Transfer Protocol (SMTP), and the finger protocol.

Text-based protocols are typically optimized for human parsing and interpretation, and are therefore suitable whenever human inspection of protocol contents is required, such as during debugging and during early protocol development design phases. To be clear, all digital communication is fundamentally binary. The "text" based protocols mentioned here use only binary content, which is made "human readable" by a text editor (or other such software).

### Binary protocol

A binary protocol utilizes all values of a byte, as opposed to a text-based approach which only uses values corresponding to human-readable characters in ASCII encoding. Binary protocols are intended to be read by a machine, rather than a human. Binary protocols have the advantage of terseness, which translates into speed of transmission and interpretation. Binary have been used in the normative documents describing modern standards like EbXML, HTTP/2, HTTP/3, and EDOC. An interface in UML may also be considered a binary protocol.




# Temporary

One of the important concepts developed in the 1960s was the idea of packet switching. In packet switching, chunks (or packets) of digital information comprising some number of bytes are carried through the network somewhat independently. Packets coming from different sources or senders can be mixed together and pulled apart later, which is called multiplexing. The packets can be moved around from one switch to another on their way to a destination, and the path might be subject to change. This has two potential advantages: the network can be more resilient (the designers were worried about the network being physically attacked), and there can be better utilization of the network links and switches because of statistical multiplexing.

When packets are received at a packet switch, they are ordinarily stored in buffer memory or queue and processed in a first-come-first-served (FCFS) fashion. This is the simplest method for scheduling the way packets are processed and is also called first-in-first-out (FIFO). FIFO buffer management and on-demand scheduling are easily combined to implement statistical multiplexing, which is the primary method used to intermix traffic from different sources on the internet. In statistical multiplexing, traffic is mixed together based on the arrival statistics or timing pattern of the t