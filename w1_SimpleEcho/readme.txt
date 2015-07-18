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

//? lambda를 쓰는 이유?

//? functor를 쓰는 이유?

//? find(..) 함수의 작동원리? obj의 ==operator를 이용하나?
	>>done

//? enum Vs const int 사용법 확인 
	>>done

//? enum을 class로 넣어야하는지, namespace로 넣어야하는지..

//? string에서 copiedStr = origStr 과 같이 =operation은 shallow copy? deep copy?

version history
0.1.0		basic IOCP server & client
0.2.0		class implementation
