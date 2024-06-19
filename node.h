#ifndef NODE_H
#define NODE_H

#include "link.h"
#include "packet.h"
#include <vector>
#include <cstdlib>
#include <ctime>

class Node {
  friend class LinkInstaller;

private:
  int id_;
  static int nextId_;
  std::vector<Link *> links_;

public:
  Node() : id_(nextId_++) {}
  virtual ~Node() {}
  int id() const { return id_; }

  virtual void onReceive(Packet *packet) = 0;
  Link* getRandomLink() { 
    if (links_.size() == 1) {
      return links_[0];
    }
    srand((unsigned int)time(NULL));
    int randomNum = rand() % (links_.size() - 1);
    return links_[randomNum]; 
  }
};

#endif