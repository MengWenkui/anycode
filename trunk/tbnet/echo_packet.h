#include <string>
#include <stdint.h>
#include "tbnet.h"

// alloc a packet code for every packet
#define ECHO_REQUEST_CODE 10
#define ECHO_RESPONSE_CODE 11

using namespace tbsys;
using namespace tbnet;

class EchoRequest: public Packet
{
  public:
    EchoRequest()
    {
      setPCode(ECHO_REQUEST_CODE);
    }

    string get_message()
    {
      return msg_;
    }
    void set_message(std::string msg)
    {
      msg_ = msg;
    }

    // how to encode and decode response packet
    bool encode(DataBuffer *output)
    {
      output->writeBytes(msg_.c_str(), msg_.length());
      return true;
    }
    bool decode(DataBuffer *input, PacketHeader *header)
    {
      int len = header->_dataLen;
      char buf[1024]; // max
      input->readBytes(buf, len);
      buf[len] = '\0';
      msg_ = buf;
      return true;
    }

  private:
    std::string msg_;
};

class EchoResponse: public Packet
{
  public:
    EchoResponse()
    {
      setPCode(ECHO_RESPONSE_CODE);
    }

    string get_message()
    {
      return msg_;
    }
    void set_message(std::string msg)
    {
      msg_ = msg;
    }

    int64_t get_time()
    {
      return time_;
    }
    void set_time(uint64_t time)
    {
      time_ = time;
    }

    // how to encode and decode response packet
    bool encode(DataBuffer *output)
    {
      output->writeInt64(time_);
      output->writeBytes(msg_.c_str(), msg_.length());
      return true;
    }
    bool decode(DataBuffer *input, PacketHeader *header)
    {
      int len = header->_dataLen;
      time_=input->readInt64();
      char buf[1024]; // max
      input->readBytes(buf, len - sizeof(int64_t));
      buf[len-sizeof(int64_t)] = '\0';
      msg_ = buf;
      return true;
    }

  private:
    std::string msg_;
    int64_t time_;
};

