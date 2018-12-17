
#ifndef __D2DCOMMUNICATION_NODE_H_
#define __D2DCOMMUNICATION_NODE_H_

#include <omnetpp.h>
#include <queue>
#include "FileTransfer.h"
#include "configurator.h"
#include "FileCache.h"
#include "FileInfoResponse.h"

using namespace omnetpp;

/**
 * TODO - Generated class
 */
class Node : public cSimpleModule, public FileTransfer
{
public:
    double  getX()   { return m_dPosX; }
    double  getY()   { return m_dPosY; }
    int     getId()  { return id; }
  protected:
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);
    virtual void finish();

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
    FileCache m_cache;
    std::queue<FileInfoMessage> m_currentRequestList;
};

#endif
