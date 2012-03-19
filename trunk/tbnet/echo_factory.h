#include "echo_packet.h"

using namespace tbsys;
using namespace tbnet;

class EchoPacketFactory: public IPacketFactory
{
  public:
    Packet* createPacket(int pcode)
    {
      switch (pcode)
      {
        case ECHO_REQUEST_CODE:
          return new EchoRequest();
        case ECHO_RESPONSE_CODE:
          return new EchoResponse();
        default:
          return NULL;
      }
      return NULL;
    }
};


