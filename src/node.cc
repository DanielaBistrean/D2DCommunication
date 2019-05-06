

#include "node.h"
#include "data_packet_m.h"
#include "data_packet_types.h"
#include "Register_m.h"
#include "d2dReq_m.h"
#include "NetworkAbstraction.h"
#include "broadcast_m.h"
#include "FileInfoMessage_m.h"
#include "timeout_m.h"

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

    m_cache.setBlockSize(4096);
    m_cache.setMaxSize(0);

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

    //my modif
//    Register *reg = new Register("Register");
//    reg->setX((int) m_dPosX);
//    reg->setY((int) m_dPosY);
//    reg->setSenderId(this->id);

//    sendDirect(reg, config->geteNBControlGate(id));

    cMessage *update = new cMessage("position");
    double interval = config->par("updateInterval");
    m_dUpdateInterval = (interval / m_dVelocity) / 1000;
    scheduleAt(simTime() + m_dUpdateInterval, update);

    NetworkAbstraction &na = NetworkAbstraction::getInstance();
    na.registerUser(this);
}

bool Node::inDownload()
{
    for(int s : status)
    {
        if(s == DOWNLOAD)
            return true;
    }

    return false;
}

void Node::handleMessage(cMessage *msg)
{
//    if (strcmp(msg->getName(), "HELLO!") == 0)
//    {
//        delete (msg);
//        return;
//    }
//    cMessage *test = new cMessage("HELLO!");
    NetworkAbstraction &na = NetworkAbstraction::getInstance();
//    na.broadcast(this, test, 500);
//    delete test;
    EV << "handleMessage? " << msg->getDisplayString()<< std::endl;

    if (strcmp(msg->getName(), "Broadcast") == 0) // getClassNAme
    {
        FileInfoMessage *fim = new FileInfoMessage("FIM");

        Broadcast *bcast = check_and_cast<Broadcast*> (msg);

        std::vector<int> fimData;
        int fileId = bcast->getBfileId();
        int senderId = bcast->getBuserId();

        EV << "Broadcast?" << std::endl;
        if (m_cache.findFile(fileId))
        {
            FileData &fd = m_cache.getFile(fileId);
            std::vector<Block> &blocks = fd.getBlocks();

            for (int i = 0; i < blocks.size(); i++)
            {
                if (blocks[i].isPresent())
                    fimData.push_back(i);
            }
            fim->setBlocks(fimData);
            fim->setUId(id);
            EV << "Broadcast - findFile()?" << std::endl;

            sendDirect(fim, config->getNodeGate(senderId, id));
//            status[fileId] = DOWNLOAD;
        }

//        Data_packet *bres = createFileResponse(userId, fileId, seq + 1);
//        bres->setIsD2D(true);
//        bres->setSenderID(id);

        delete(msg);
    }

    else if (msg->isSelfMessage())
    {
        EV << "Self message: " << msg->getName() << std::endl;
        if (strcmp(msg->getName(), "position") == 0)
        {
            updatePosition();
            delete(msg);
        }
        else if (strcmp(msg->getName(), "Timeout") == 0)
        {
            Timeout *t = check_and_cast<Timeout*> (msg);
            EV << "Timeout arrived for " << id << std::endl;

//            m_cache.createFile(t->getFileId(), ) // add here the file size.

            bool isComplete = false;
            int fileId = 0;
//                    static_cast <int> (rand()) % 3;

            if (!m_currentRequestList.empty() && !inDownload())
            {
                FileInfoMessage *fim = m_currentRequestList.front();
                m_currentRequestList.pop();

                Data_packet *data_packet = new Data_packet("Req");

                data_packet->setIsRequest(true);
                data_packet->setType(FILE_REQUEST);
                data_packet->setSequenceNumber(0);
                data_packet->setSenderID(this->id);
                payload p;
                p.fileId = fileId;
                data_packet->setData(p);

                EV << "Timeout?" << std::endl;
                sendDirect(data_packet, config->getNodeGate(fim->getUId(), id));
                status[fileId] = DOWNLOAD;

                while(!m_currentRequestList.empty())
                {
                    m_currentRequestList.pop();
                }

//                int numBlocks = fim.getNumBlocks();
//
//                std::vector<int> blockI = fim.getBlocks();
//                for (auto i : blockI)
//                {
//
//                }
            }
            else if (!inDownload())
            {
                int fileId = 0;
//                        static_cast <int> (rand()) % 3;

                Data_packet *data_packet = new Data_packet("Req");

                data_packet->setIsRequest(true);
                data_packet->setType(FILE_REQUEST);
                data_packet->setSequenceNumber(0);
                data_packet->setSenderID(this->id);
                payload p;
                p.fileId = fileId;
                data_packet->setData(p);

                EV << "Req?" << std::endl;

                sendDirect(data_packet, 0.05, 0.01, config->getENBGate(id));
//                sendDirect(data_packet, config->getENBGate(id));
                status[fileId] = DOWNLOAD;
            }
        }
        else
        {
            int fileId = 0;
//                    static_cast <int> (rand()) % 3; // choose a file

            if (/*!m_cache.findFile(fileId) &&*/ !inDownload())
            {
                Broadcast *bMsg = new Broadcast("Broadcast");
                bMsg->setBfileId(fileId);
                bMsg->setBuserId(this->id);

                Timeout *timeout = new Timeout("Timeout");
                timeout->setFileId(fileId);

                na.broadcast(this, bMsg, 500);
                scheduleAt(simTime() + 0.5, timeout);

            }


//            if (status[fileId] == NONE)
//            {
//                Data_packet *data_packet = new Data_packet("Req");
//                data_packet->setIsRequest(true);
//                data_packet->setType(FILE_REQUEST);
//                data_packet->setSequenceNumber(0);
//                data_packet->setSenderID(this->id);
//                payload p;
//                p.fileId = fileId;
//                data_packet->setData(p);
//
//                Broadcast *bMsg = new Broadcast("Broadcast");
//                bMsg->setBfileId(fileId);
//                bMsg->setBuserId(this->id);
//
//                na.broadcast(this, bMsg, 500);
//
//
//                // sent the msg to enb
//                sendDirect(data_packet, config->getENBGate(id));
//
//
//                status[fileId] = DOWNLOAD;
//            }

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

        EV << "register?" << std::endl;

        sendDirect(res, 0.05, 0.01, config->getNodeGate(userId, id));
//        sendDirect(res, config->getNodeGate(userId, id));

        delete(msg);
    }
    else
    {
        Data_packet *dp = nullptr;
        try
        {
            dp = check_and_cast <Data_packet*> (msg);
        }
        catch (...){};

        if (!dp)
        {
            FileInfoMessage *dp = static_cast <FileInfoMessage*> (msg);
            m_currentRequestList.push(dp);
        } else
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
                emit(D2DCommunication, (unsigned long)dp->getSize());
            }
            else
            {
                emit(D2ICommunication, (unsigned long)dp->getSize());
            }

            int sId = dp->getSenderID();
            EV << "sID = " << sId << std::endl;

            if (sId < 0)
                sendDirect(response, 0.05, 0.01, config->getENBGate(id));
//                sendDirect(response, config->getENBGate(id));
            else
                sendDirect(response, 0.05, 0.01, config->getNodeGate(dp->getSenderID(), id));
//                sendDirect(response, config->getNodeGate(dp->getSenderID(), id));
        }
        else if (dp->getType() == FILE_END)
        {
            status[dp->getData().fileId] = READY;
            m_cache.createFile(dp->getData().fileId, 12582);
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
                sendDirect(res, 0.05, 0.01, config->getENBGate(id));
//                sendDirect(res, config->getENBGate(id));
            else
                sendDirect(res, 0.05, 0.01, config->getNodeGate(dp->getSenderID(), id));
//                sendDirect(res, config->getNodeGate(dp->getSenderID(), id));
        }
        else if (dp->getType() == FILE_REQUEST)
        {

            int fileId = dp->getData().fileId;
            int userId = dp->getSenderID();
            int seqNum = dp->getSequenceNumber();

//            if (nearest == -1)
            Data_packet *res = createFileResponse(userId, fileId, seqNum + 1);
//            else
//            {
//                D2dReq *d2d = new D2dReq("D2D");
//                d2d->setUserId(userId);
//                d2d->setFileId(fileId);
//                d2d->setSeq(seqNum);
//
//                sendDirect(d2d, config->getNodeControlGate(nearest));
//            }

             sendDirect(res, 0.05, 0.01, config->getNodeGate(dp->getSenderID(), id));

        }

            delete dp;
    }
}

void
Node::updatePosition()
{
    m_dPosX += m_dVelocity * cos(m_dHeading);
    m_dPosY += m_dVelocity * sin(m_dHeading);

    double dRadius = config->par("radius");
    double dCx = config->par("cx");
    double dCy = config->par("cy");

    double dDist = sqrt((dCx - m_dPosX) * (dCx - m_dPosX) + (dCy - m_dPosY) * (dCy - m_dPosY));
    if (dDist > dRadius)
    {
        // node is outside of radius, replace it at the other side of the circle
        m_dPosX = (2 * dCx) - m_dPosX;
        m_dPosY = (2 * dCy) - m_dPosY;
    }

    this->getDisplayString().setTagArg("p", 0, (long) m_dPosX);
    this->getDisplayString().setTagArg("p", 1, (long) m_dPosY);

    cMessage *update = new cMessage("position");

    scheduleAt(simTime() + m_dUpdateInterval, update);
}

void
Node::finish()
{
    NetworkAbstraction &na = NetworkAbstraction::getInstance();
    na.deregisterUser(this);
}


