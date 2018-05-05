

#include "node.h"
#include "data_packet_m.h"
#include "data_packet_types.h"

Define_Module(Node);

void Node::initialize()
{
    cMessage *msg = new cMessage("message");
    scheduleAt(simTime(), msg); // mesaj propriu -> peste un timp
}

void Node::handleMessage(cMessage *msg)
{
    if (msg->isSelfMessage())
    {
        Data_packet *data_packet = new Data_packet("Req");
        data_packet->setIsRequest(true);
        data_packet->setType(FILE_REQUEST);
        data_packet->setSequenceNumber(0);
        data_packet->setSenderID(0);
        payload p;
        p.fileId = 1;
        data_packet->setData(p);
        send(data_packet, "out");
        cMessage *msg = new cMessage("message");

        float r2 = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX));
        scheduleAt((simTime()+r2), msg);
    }
    else
    {
        Data_packet *dp = static_cast <Data_packet*> (msg);
        if (dp->getType() == FILE_RESPONSE)
        {
            Data_packet *response = new Data_packet("ACK");
            response->setSenderID(0);
            response->setIsRequest(false);
            response->setType(FILE_ACK);
            response->setSequenceNumber(dp->getSequenceNumber()+1);
            payload p;
            p.fileId = dp->getData().fileId;
            response->setData(p);
            //send(response, "out");
            send(response, "out");
        }

            delete dp;
    }
}
