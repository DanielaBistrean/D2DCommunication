
#ifndef __D2DCOMMUNICATION_Enb_H_
#define __D2DCOMMUNICATION_Enb_H_

#include <omnetpp.h>

#define NONE 0
#define DOWNLOAD 1
#define READY 2

using namespace omnetpp;

/**
 * TODO - Generated class
 */
class Enb : public cSimpleModule
{
  protected:
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);
    virtual void finish();

  private:
    char *files[3];
    int fsize[3];
    int f[3][20] = { {0}, {0}, {0} };
    int progress[3][20] = { {0}, {0}, {0} };
    Data_packet* createFileResponse(int userId, int fileId, int seqNumber);
    void updateProgress(int userId, int fileId, int bytes_sent);
    int user_pos[20][2] = { {0} }; //20 users; 2 - x, y
    int enb_x, enb_y;
    int nearestN(int userId, int fileId);
};

#endif
