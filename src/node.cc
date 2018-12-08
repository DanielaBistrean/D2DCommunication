

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
    scheduleAt(simTime() + r2, msg);
    status[0] = status[1] = status[2] = NONE;

    D2DCommunication = registerSignal("D2DCommunication");
    D2ICommunication = registerSignal("D2ICommunication");

    this->id = Node::count;
    Node::count ++;

    config = check_and_cast <Configurator*> (Configurator::getConfigurator(this));

    cRNG *random = this->getRNG(0);

    // new development

    double dRadius = config->par("radius");
    double dCx = config->par("cx");
    double dCy = config->par("cy");
    double dDeltaHeadingMax = config->par("deltaHeadingMax");
    double dVelocityMax = config->par("velocityMax");

    // Dir is an angle, distance is between 1 and radius
    double dDir = random->doubleRand() * 2 * PI;
    double dDistance = random->doubleRand() * (dRadius - 1) + 1;

    double dHeadingCenter = PI - dDir;

    m_dPosX = dCx + (dDistance * cos(dDir));
    m_dPosY = dCy + (dDistance * sin(dDir));

    m_dVelocity = random->doubleRand() * (dVelocityMax - 1) + 1;
    m_dHeading = dHeadingCenter + random->doubleRand() * (dDeltaHeadingMax * 2) - dDeltaHeadingMax;


    this->getDisplayString().setTagArg("p", 0, (long) m_dPosX);
    this->getDisplayString().setTagArg("p", 1, (long) m_dPosY);

    Register *reg = new Register("Register");
    reg->setX((int) m_dPosX);
    reg->setY((int) m_dPosY);
    reg->setSenderId(this->id);

    sendDirect(reg, config->geteNBControlGate(id));

    cMessage *update = new cMessage("position");
    double interval = config->par("updateInterval");
    m_dUpdateInterval = (interval / m_dVelocity) / 1000;
    scheduleAt(simTime() + m_dUpdateInterval, update);
}

void Node::handleMessage(cMessage *msg)
{
    if (msg->isSelfMessage())
    {
        if (strcmp(msg->getName(), "position") == 0)
        {
            updatePosition();
            delete(msg);
        }
        else
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

                sendDirect(data_packet, config->getENBGate(id));

                status[fileId] = DOWNLOAD;
            }

            float r2 = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX));
            scheduleAt((simTime()+r2), msg);
        }
    }
    else if (msg->arrivedOn("register$i"))
    {
        D2dReq *req = static_cast <D2dReq*> (msg);

        int userId = req->getUserId();
        int fileId = req->getFileId();
        int seq = req->getSeq();

        Data_packet *res = createFileResponse(userId, fileId, seq + 1);
        res->setIsD2D(true);
        res->setSenderID(id);

        sendDirect(res, config->getNodeGate(userId, id));

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

            int sId = dp->getSenderID();
            if (sId < 0)
                sendDirect(response, config->getENBGate(id));
            else
                sendDirect(response, config->getNodeGate(dp->getSenderID(), id));
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
            res->setSenderID(id);

            int sId = dp->getSenderID();
            if (sId < 0)
                sendDirect(res, config->getENBGate(id));
            else
                sendDirect(res, config->getNodeGate(dp->getSenderID(), id));
        }

            delete dp;
    }
}

void
Node::updatePosition()
{
    m_dPosX += m_dVelocity * cos(m_dHeading);
    m_dPosY += m_dVelocity * sin(m_dHeading);

    this->getDisplayString().setTagArg("p", 0, (long) m_dPosX);
    this->getDisplayString().setTagArg("p", 1, (long) m_dPosY);

    cMessage *update = new cMessage("position");

    scheduleAt(simTime() + m_dUpdateInterval, update);
}

