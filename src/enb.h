
#ifndef __D2DCOMMUNICATION_Enb_H_
#define __D2DCOMMUNICATION_Enb_H_

#include <omnetpp.h>

#include "FileTransfer.h"
#include "configurator.h"

using namespace omnetpp;

/**
 * TODO - Generated class
 */
class Enb : public cSimpleModule, public FileTransfer
{
  protected:
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);
    virtual void finish();

  private:
    int user_pos[20][2] = { {0} }; //20 users; 2 - x, y
    double enb_x, enb_y;
    int nearestN(int userId, int fileId);
    Configurator* config;
};

#endif
