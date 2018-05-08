
#ifndef __D2DCOMMUNICATION_NODE_H_
#define __D2DCOMMUNICATION_NODE_H_

#include <omnetpp.h>

using namespace omnetpp;

/**
 * TODO - Generated class
 */
class Node : public cSimpleModule
{
  protected:
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);

  private:
    int status[3];
    static int count;
    int id;
    int x, y;
};

#endif
