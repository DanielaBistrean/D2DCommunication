
#include "data_packet_m.h"
#include "enb.h"
#include <string.h>
#include "data_packet_types.h"

Define_Module(Enb);

void Enb::initialize()
{
    files[0] = files[1] = files[2] = 0;
    files[0] = (char*) malloc(sizeof(char)*12582912);
    files[1] = (char*) malloc(sizeof(char)*3145728);
    files[2] = (char*) malloc(sizeof(char)*3145728);
}

Data_packet* createFileResponse(int userId, int fileId)
{
    if (f[fileId, userID] == NONE)
    {
        int toSend = ( progress[fileID][userId]) >= 0 ? (4096) : (-1)
        Data_packet *res = new Data_packet("Res");
        res->setType(FILE_);
    }
    else
    {
        return NULL;
    }
}

void Enb::handleMessage(cMessage *msg)
{
    int toSend;
    Data_packet *fr = static_cast <Data_packet*> (msg);
    if (fr->getType() == FILE_REQUEST)
    {
        if (f[fr->getData().fileId][fr->getSenderID()] == NONE) //nu are fisierul
        {
            f[fr->getData().fileId][fr->getSenderID()] = DOWNLOAD;
            progress[fr->getData().fileId][fr->getSenderID()] = 0;
            Data_packet *response = new Data_packet("Response");
            response->setType(FILE_RESPONSE);
            response->setSequenceNumber(fr->getSequenceNumber()+1);
            payload p;
            p.fileId = fr->getData().fileId;
            if (progress[fr->getData().fileId][fr->getSenderID()] - 4096) >= 0)
            {
                toSend = 4096;
                memcpy(p.fileData, files[fr->getData().fileId] + progress[fr->getData().fileId][fr->getSenderID()], 4096);
                progress[fr->getData().fileId][fr->getSenderID()] += 4096;
                response->setData(p);
                send(response, this->gate("out", fr->getArrivalGate()->getIndex()));
            }
            else
            {
                progress[fr->getData().fileId][fr->getSenderID()] = -1;
            }
        }
    }
    else if (fr->getType() == FILE_ACK)
    {
        Data_packet *response = new Data_packet("Response");
        response->setType(FILE_RESPONSE);
        response->setSequenceNumber(fr->getSequenceNumber()+1);
        payload p;
        p.fileId = fr->getData().fileId;
        memcpy(p.fileData, files[fr->getData().fileId] + progress[fr->getData().fileId][fr->getSenderID()], 4096);
        progress[fr->getData().fileId][fr->getSenderID()] += 4096;
        response->setData(p);
        send(response, this->gate("out", fr->getArrivalGate()->getIndex()));
    }

    /*if (strcmp(fr->getName(), "file1") == 0)
    {
        cMessage *res = new cMessage("Data");
        send(res, this->gate("out", fr->getArrivalGate()->getIndex()));
    }*/

    delete(fr);
}

void Enb::finish()
{
    free(files[0]);
    free(files[1]);
    free(files[2]);
}
