#ifndef HOST_H
#define HOST_H

#include "address.h"
#include "packet.h"
#include "service.h"
#include <vector>
#include <set>
#include <iostream>

class Host : public Node {
  friend class ServiceInstaller;

private:
  // 호스트의 주소
  Address address_;

  // 설치된 서비스 목록
  std::vector<Service *> services_;

public:
  Address address() { return address_; }
  Host(Address address) : address_(address) {}

  // 호스트와 설치된 서비스를 전부 초기화한다.
  void initialize() {}

  // 링크를 랜덤으로 하나 선택하여 패킷을 전송한다.
  void send(Packet *packet) {
    // Host #1: sending packet (from: 0, to: 1, 13 bytes)
    std::cout << "Host #" << id() << ": sending packet (from: " << address_.toString() 
                    << ", to: " << packet->destAddress().toString() << ", " << packet->data().size() << " bytes)" << std::endl;
    getRandomLink()->onReceive(this, packet);
  }

  void onReceive(Packet* packet) override {
    // 포트를 보고 맞는 서비스를 찾기
    // 맞는 서비스에 패킷 전달
    Service *service = nullptr;
    for(size_t i = 0; i < services_.size(); i++) {
      Service* s = services_[i];
      if(s->port() == packet->destPort()) {
        service = s;
        break;
      }
    }

    if(service != nullptr) {
      // Host #0: received packet, destination port: 3000
      std::cout << "Host #" << id() << ": received packet, destination port: " << packet->destPort() << std::endl;
      service->onReceive(packet);
    } else {
      std::cout << "Host #" << id() << ": no service for packet (from: " << packet->srcAddress().toString() 
                    << ", to: " << packet->destAddress().toString() << ", " << packet->data().size() << " bytes)" << std::endl;
    }
  }

  short validPort() {
    short validPort = 1000;
    std::set<short> ports_;
    std::set<short>::iterator iter;
    
    for (size_t i = 0; i < services_.size(); i++) {
     ports_.insert(services_[i]->port()); 
    }

    while (true) {
      iter = ports_.find(validPort);
      if (iter != ports_.end()) {
        validPort++;
      } else {
        break;
      }
    }

    return validPort;
  }
};

#endif