This program is made for simple serialization practice.
There are server and client. 
Basically, this is simple echo server. When client send message to server, then server toss it back to client.

There's several thing to note.
Client has its client information like name, etc. Client serialize these information with message and send serialized data to server.
Server deserialize these information and print these information with its message and send it back to client.

Server use IOCP.
There is String serialize(...) function. (Function's specs might be change)
There is OriginalClass deserialize(...) function. (Function's specs might be change)



//? UDP�� datagram(packet)�� �ְ� �ް� TCP�� stream�̶����.. serialization�� packet�� ����°� �ƴѰ�..? 
	�׷� TCP���� serialization�� �Ѵٴ� �� ���� ������..?

//? lambda�� ���� ����?

//? functor�� ���� ����?

//? find(..) �Լ��� �۵�����? obj�� ==operator�� �̿��ϳ�?
	>>done

//? enum Vs const int ���� Ȯ�� 
	>>done

//? enum�� class�� �־���ϴ���, namespace�� �־���ϴ���..

//? string���� copiedStr = origStr �� ���� =operation�� shallow copy? deep copy?

version history
0.1.0		basic IOCP server & client
0.2.0		class implementation
