
#include "enb.h"
#include <string.h>
#include "data_packet_types.h"
#include "Register_m.h"
#include <math.h>
#include "d2dReq_m.h"

Define_Module(Enb);
#define RMAX 40

void Enb::initialize()
{
    config = check_and_cast <Configurator*> (Configurator::getConfigurator(this));

    // new development
    enb_x = config->par("cx");
    enb_y = config->par("cy");
    double dRadius = config->par("radius");

    EV << "enb at pos " << enb_x << "," << enb_y;

    this->getDisplayString().setTagArg("p", 0, (int) enb_x);
    this->getDisplayString().setTagArg("p", 1, (int) enb_y);

    this->getDisplayString().setTagArg("r", 0, (int) dRadius);
}



int Enb::nearestN(int userId, int fileId)
{
    float min = 25000.0f;
    float distNcN;
    float distNcE;
    int minId;
    int i;

    for(i = 0; i < 10; i++)
    {
      if (getFileStatus(i, fileId) == READY && i != userId)
      {
          float dx = (float) user_pos[userId][0] - (float) user_pos[i][0];
          float dy = (float) user_pos[userId][1] - (float) user_pos[i][1];
          distNcN = std::sqrt(dx * dx + dy * dy);
          if ((distNcN < min) && (distNcN < RMAX))
          {
              min = distNcN;
              minId = i;
          }

          EV << "Distance from " << " userId " << " to " << i << " is " << distNcN << endl;

      }
    }

    distNcE = sqrt(pow(user_pos[userId][0] - enb_x, 2) + pow(user_pos[userId][1] - enb_y, 2));
    if (distNcE < min)
        return -1;
    else
        return minId;
}

void Enb::handleMessage(cMessage *msg)
{
    if (msg->arrivedOn("register$i"))
    {
        Register *m_reg = static_cast <Register*> (msg);
        int x = m_reg->getX();
        int y = m_reg->getY();
        int userId = m_reg->getSenderId();

        user_pos[userId][0] = x;
        user_pos[userId][1] = y;

        delete(m_reg);
    }
    else
    {
        int toSend;
        Data_packet *fr = static_cast <Data_packet*> (msg);

        int userId = fr->getSenderID();
        int fileId = fr->getData().fileId;
        int seqNum = fr->getSequenceNumber();
        int size = fr->getSize();
        Data_packet *res = NULL;

        if (fr->getType() == FILE_REQUEST)
        {
            int nearest = nearestN(userId, fileId);
            EV << "Nearest for user " << userId << " file " << fileId << " is" << nearest << endl;
            if (nearest == -1)
                res = createFileResponse(userId, fileId, seqNum + 1);
            else
            {
                D2dReq *d2d = new D2dReq("D2D");
                d2d->setUserId(userId);
                d2d->setFileId(fileId);
                d2d->setSeq(seqNum);

                sendDirect(d2d, config->getNodeControlGate(nearest));
            }

        }
        else if (fr->getType() == FILE_ACK)
        {
            updateProgress(userId, fileId, size);
            res = createFileResponse(userId, fileId, seqNum);
        }

        if (res != NULL)
        {
            res->setIsD2D(false);
            res->setSenderID(-1);

            sendDirect(res, config->getNodeGate(userId, -1));
        }
        delete(fr);
    }
}

void Enb::finish()
{

}
