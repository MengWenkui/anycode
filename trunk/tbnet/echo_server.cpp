#include "echo_factory.h"

using namespace tbsys;
using namespace tbnet;

class EchoServerAdapter: public IServerAdapter
{
  public:
    IPacketHandler::HPRetCode handlePacket(Connection *connection, Packet *packet)
    {
      switch (packet->getPCode())
      {
        case ECHO_REQUEST_CODE:
          return do_echo(connection, packet);
        default:
          fprintf(stderr, "invalid packet\n");
      }
      return IPacketHandler::FREE_CHANNEL;
    }


  private:
    // return the request message and current time to client
    IPacketHandler::HPRetCode do_echo(Connection *connection, Packet *packet)
    {
      EchoRequest* req = (EchoRequest* )packet;
      EchoResponse* resp = new EchoResponse();
      resp->set_message(req->get_message());
      resp->set_time(CTimeUtil::getTime());
      resp->setChannelId(packet->getChannelId());

      connection->postPacket(resp);
      // resp->free();
      // packet->free();
      return IPacketHandler::FREE_CHANNEL;
    }
};

class EchoServer
{
  public:
    void start()
    {
      EchoPacketFactory factory;
      DefaultPacketStreamer streamer(&factory);
      EchoServerAdapter adapter;
      transport_.listen("tcp:127.0.0.1:9527", &streamer, &adapter);
      transport_.start();
      transport_.wait();
    }
    void stop()
    {
      transport_.stop();
    }
  private:
    Transport transport_;
};

int main()
{
  EchoServer echoserver;
  echoserver.start();
  return 0;
}

