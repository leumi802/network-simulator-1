#ifndef ROUTER_H
#define ROUTER_H

#include "node.h"
#include <iostream>

struct RoutingEntry {
public:
  Address destination;
  Link *nextLink;
  RoutingEntry(Address dest, Link *next): destination(dest), nextLink(next) {}
};

class Router : public Node {
protected:
  std::vector<RoutingEntry> routingTable_;

  void onReceive(Packet* packet) override {
    for (size_t i = 0; i < routingTable_.size(); i++) {
      RoutingEntry entry = routingTable_[i];
      if (entry.destination == packet->destAddress()) {
        // Router #2: forwarding packet (from: 1, to: 0, 13 bytes)
        std::cout << "Router #" << id() << ": forwarding packet (from: " << packet->srcAddress().toString() 
                    << ", to: " << packet->destAddress().toString() << ", " << packet->data().size() << " bytes)" << std::endl;
        entry.nextLink->onReceive(this, packet);
        return;
      }
    }
    // Router #6: no route for packet (from: 456, to: 0, 7 bytes)
    std::cout << "Router #" << id() << ": no route for packet (from: " << packet->srcAddress().toString() 
                    << ", to: " << packet->destAddress().toString() << ", " << packet->data().size() << " bytes)" << std::endl;
  }
};

#endif