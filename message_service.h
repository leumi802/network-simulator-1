#ifndef MESSAGE_SERVICE_H
#define MESSAGE_SERVICE_H

#include "address.h"
#include "host.h"
#include "service.h"
#include <iostream>

// send 함수를 호출하여 메시지를 전송할 수 있는 서비스
class MessageService : public Service {
  friend class MessageServiceInstaller;

private:
  // 목적지 주소
  Address destAddress_;
  // 목적지 포트
  short destPort_;
  MessageService(Host *host, short port, Address destAddress, short destPort)
      : Service(host, port), destAddress_(destAddress), destPort_(destPort) {}

public:
  // 메시지를 전송한다
  void send(std::string message) {
    // 패킷 만들기
    Packet *packet = new Packet(host_->address(), destAddress_, port_, destPort_, message);
    host_->send(packet);
  }

  void onReceive(Packet *packet) override {
    // MessageService: received "Hello, world!" from 1:3000
    std::cout << "MessageService: received \"" << packet->dataString() << "\" from "
          << packet->srcAddress().toString() << ":" << packet->srcPort() << std::endl;
  }
};

#endif