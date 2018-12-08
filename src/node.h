
#ifndef __D2DCOMMUNICATION_NODE_H_
#define __D2DCOMMUNICATION_NODE_H_

#include <omnetpp.h>
#include "FileTransfer.h"
#include "configurator.h"

using namespace omnetpp;

/**
 * TODO - Generated class
 */
class Node : public cSimpleModule, public FileTransfer
{
  protected:
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);

  private:
    int status[3];
    static int count;
    int id;
    simsignal_t D2DCommunication;
    simsignal_t D2ICommunication;
    Configurator* config;

    // new development
    double m_dPosX;
    double m_dPosY;
    double m_dVelocity;
    double m_dHeading;
    double m_dUpdateInterval;

    void updatePosition();
};

#endif
