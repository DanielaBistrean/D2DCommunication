
#include "data_packet_m.h"
#include "enb.h"
#include <string.h>
#include "data_packet_types.h"
#include "Register_m.h"
#include <math.h>
#include "d2dReq_m.h"

Define_Module(Enb);

void Enb::initialize()
{
    files[0] = files[1] = files[2] = 0;


    fsize[0] = 12582912;
    fsize[1] = fsize[2] = 3145728;

    files[0] = (char*) malloc(sizeof(char) * fsize[0]);
    files[1] = (char*) malloc(sizeof(char) * fsize[1]);
    files[2] = (char*) malloc(sizeof(char) * fsize[2]);

    enb_x = 50;
    enb_y = 50;

    this->getDisplayString().setTagArg("p", 0, enb_x);
    this->getDisplayString().setTagArg("p", 1, enb_y);
}

Data_packet* Enb::createFileResponse(int userId, int fileId, int seqNumber)
{
    if (f[fileId][userId] == NONE || f[fileId][userId] == DOWNLOAD)
    {
        int toSend;
        char buff[256];
       // int toSend = (progress[fileId][userId]) >= 0 ? (4096) : (-1);
        sprintf(buff, "res %d", progress[fileId][userId]);
        Data_packet *res = new Data_packet(buff);
        res->setType(FILE_RESPONSE);
        res->setSequenceNumber(seqNumber);
        payload p;
        p.fileId = fileId;
        if ((fsize[fileId] - progress[fileId][userId]) > 4096)
            toSend = 4096;
        else
            toSend = fsize[fileId] - progress[fileId][userId];

        memcpy(p.fileData, files[fileId] + progress[fileId][userId], toSend);
        res->setData(p);
        res->setSize(toSend);

        EV << "Sending " << toSend << " bytes to node " << userId << endl;
        EV << "Node " << userId << " downloaded " << progress[fileId][userId] << " bytes from file " << fileId << endl;

        f[fileId][userId] = DOWNLOAD;
        return res;
    }
    else if (f[fileId][userId] == READY)
    {
        if (progress[fileId][userId] != -1)
        {
            progress[fileId][userId] = -1;
            // send file end
            Data_packet *res = new Data_packet("EndResp");
            res->setType(FILE_END);
            res->setSequenceNumber(seqNumber);
            payload p;
            p.fileId = fileId;
            res->setData(p);

            return res;
        }
        else
            return NULL;
    }
}

void Enb::updateProgress(int userId, int fileId, int bytes_sent)
{
    if (f[fileId][userId] == DOWNLOAD)
    {
        progress[fileId][userId] += bytes_sent;
        if (progress[fileId][userId] >= fsize[fileId])
        {
            f[fileId][userId] = READY;
        }
    }
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
      if (f[fileId][i] == READY && i != userId)
      {
          float dx = (float) user_pos[userId][0] - (float) user_pos[i][0];
          float dy = (float) user_pos[userId][1] - (float) user_pos[i][1];
          distNcN = std::sqrt(dx * dx + dy * dy);
          if (distNcN < min)
          {
              min = distNcN;
              minId = i;
          }

          EV << "Distance from " << " userId " << " to " << i << " is " << distNcN << endl;

          /*EV << "user_pos " << user_pos[userId][0] << endl;
          EV << "user_pos " << user_pos[userId][1] << endl;*/
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

                send(d2d, "register$o", nearest);
            }

        }
        else if (fr->getType() == FILE_ACK)
        {
            updateProgress(userId, fileId, size);
            res = createFileResponse(userId, fileId, seqNum);
        }

        if (res != NULL)
            // send res
            send(res, this->gate("out", fr->getArrivalGate()->getIndex()));
        delete(fr);
    }
}

void Enb::finish()
{
    free(files[0]);
    free(files[1]);
    free(files[2]);
}
