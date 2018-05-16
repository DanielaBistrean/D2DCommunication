

#include "node.h"
#include "data_packet_m.h"
#include "data_packet_types.h"
#include "Register_m.h"
#include "d2dReq_m.h"

#define NONE 0
#define DOWNLOAD 1
#define READY 2

Define_Module(Node);

#include <time.h>

int Node::count = 0;

void Node::initialize()
{
    float r2 = static_cast <float> (rand()) * 2 / (static_cast <float> (RAND_MAX));
    cMessage *msg = new cMessage("message");
    scheduleAt(simTime() + r2, msg); // mesaj propriu -> peste un timp
    status[0] = status[1] = status[2] = NONE;

    D2DCommunication = registerSignal("D2DCommunication");
    D2ICommunication = registerSignal("D2ICommunication");

    this->id = Node::count;
    Node::count ++;

    config = check_and_cast <Configurator*> (Configurator::getConfigurator(this));

    cRNG *random = this->getRNG(0);
    x = random->intRand(100); // x in the range of 0 to 100
    y = random->intRand(100); // y in the range of 0 to 100    getDisplayString()->setTagArg("p", 0, pos.x);

    this->getDisplayString().setTagArg("p", 0, x);
    this->getDisplayString().setTagArg("p", 1, y);

    Register *reg = new Register("Register");
    reg->setX(this->x);
    reg->setY(this->y);
    reg->setSenderId(this->id);

    //send(reg, "register$o");
    sendDirect(reg, config->geteNBControlGate(id));
}

void Node::handleMessage(cMessage *msg)
{
    if (msg->isSelfMessage())
    {
        int fileId = static_cast <int> (rand()) % 3;
        if (status[fileId] == NONE)
        {
            Data_packet *data_packet = new Data_packet("Req");
            data_packet->setIsRequest(true);
            data_packet->setType(FILE_REQUEST);
            data_packet->setSequenceNumber(0);
            data_packet->setSenderID(this->id);
            payload p;
            p.fileId = fileId;
            data_packet->setData(p);
            send(data_packet, "out", 0);

            status[fileId] = DOWNLOAD;
        }

        float r2 = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX));
        scheduleAt((simTime()+r2), msg);
    }
    else if (msg->arrivedOn("register$i"))
    {
        D2dReq *req = static_cast <D2dReq*> (msg);

        int userId = req->getUserId();
        int fileId = req->getFileId();
        int seq = req->getSeq();

        Data_packet *res = createFileResponse(userId, fileId, seq + 1);
        res->setIsD2D(true);

        send(res, "out", userId + 1);

        delete(msg);
    }
    else
    {
        Data_packet *dp = static_cast <Data_packet*> (msg);
        if (dp->getType() == FILE_RESPONSE)
        {
            Data_packet *response = new Data_packet("ACK");
            response->setSenderID(this->id);
            response->setIsRequest(false);
            response->setType(FILE_ACK);
            response->setSize(dp->getSize());
            response->setSequenceNumber(dp->getSequenceNumber()+1);
            payload p;
            p.fileId = dp->getData().fileId;
            response->setData(p);

            bool isD2D = dp->getIsD2D();
            if (isD2D)
            {
                emit(D2DCommunication, dp->getSize());
            }
            else
            {
                emit(D2ICommunication, dp->getSize());
            }

            //send(response, "out");
            send(response, "out", dp->getArrivalGate()->getIndex());
        }
        else if (dp->getType() == FILE_END)
        {
            status[dp->getData().fileId] = READY;
        }
        else if (dp->getType() == FILE_ACK)
        {
            int fileId = dp->getData().fileId;
            int userId = dp->getSenderID();
            int seqNum = dp->getSequenceNumber();
            int size = dp->getSize();
            updateProgress(userId, fileId, size);
            Data_packet *res = createFileResponse(userId, fileId, seqNum);
            res->setIsD2D(true);
            send(res, "out", dp->getArrivalGate()->getIndex());
        }

            delete dp;
    }
}
