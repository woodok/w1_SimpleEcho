This program is made for simple serialization practice.
There are server and client. 
Basically, this is simple echo server. When client send message to server, then server toss it back to client.

There's several thing to note.
Client has its client information like name, etc. Client serialize these information with message and send serialized data to server.
Server deserialize these information and print these information with its message and send it back to client.

Server use IOCP.
There is String serialize(...) function. (Function's specs might be change)
There is OriginalClass deserialize(...) function. (Function's specs might be change)



//? UDP는 datagram(packet)을 주고 받고 TCP는 stream이라던데.. serialization은 packet을 만드는거 아닌가..? 
	그럼 TCP에서 serialization을 한다는 건 무슨 뜻인지..?

version history
0.1.0		basic IOCP server & client
0.2.0		class implementation
