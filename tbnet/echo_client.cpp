#include "echo_factory.h"

using namespace tbsys;
using namespace tbnet;

class EchoPacketHandler: public IPacketHandler
{
  public:
    HPRetCode handlePacket(Packet *packet, void *args)
    {
      switch (packet->getPCode())
      {
        case ECHO_RESPONSE_CODE:
          return do_echo(packet, args);
        default:
          fprintf(stderr, "invalid packet\n");
      }
      return IPacketHandler::FREE_CHANNEL;
    }
  private:
    HPRetCode do_echo(Packet *packet, void *args)
    {
      EchoResponse* resp = (EchoResponse* )packet;
      printf("channel id  : %d\n", resp->getChannelId());
      printf("reply code  : %d\n", resp->getPCode());
      printf("echo message: %s\n", resp->get_message().c_str());
      printf("echo time   : %ld\n", resp->get_time());
      printf("extra args  : %s\n", (char* )args);
      delete packet;
      return IPacketHandler::FREE_CHANNEL;
    }
};

class EchoClient
{
  public:
    void start()
    {
      EchoPacketFactory factory;
      DefaultPacketStreamer streamer(&factory);
      EchoPacketHandler handler;

      transport_.start();

      EchoRequest *request = new EchoRequest();
      request->set_message("hello world for tbnet!");
      printf("%d\n", request->getPCode());

      Connection* conn = transport_.connect("tcp:127.0.0.1:9527", &streamer);
      // we can also set default handler for this conn by setDefaultPacketHandler
      conn->postPacket(request, &handler, (void*)"i am argument");

      transport_.wait();
      delete conn;
    }
  private:
    Transport transport_;
};

int main()
{
  EchoClient echo_client;
  echo_client.start();
  return 0;
}


