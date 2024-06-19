#include "link.h"
#include "node.h"

void Link::onReceive(Node* sender, Packet* packet) {
    Node* receiver = other(sender);
    // Link: forwarding packet from node #1, to node #5
    std::cout << "Link: forwarding packet from node #" << sender->id() << ", to node #" << receiver->id() << std::endl;
    receiver->onReceive(packet);
}