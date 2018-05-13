//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
// 

#include "FileTransfer.h"

#include <omnetpp.h>
#include "data_packet_types.h"

using namespace omnetpp;

FileTransfer::FileTransfer() {
    files[0] = files[1] = files[2] = 0;


    fsize[0] = 12582912;
    fsize[1] = fsize[2] = 3145728;

    files[0] = (char*) malloc(sizeof(char) * fsize[0]);
    files[1] = (char*) malloc(sizeof(char) * fsize[1]);
    files[2] = (char*) malloc(sizeof(char) * fsize[2]);

}

Data_packet* FileTransfer::createFileResponse(int userId, int fileId, int seqNumber)
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

void FileTransfer::updateProgress(int userId, int fileId, int bytes_sent)
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

int FileTransfer::getFileStatus(int userId, int fileId)
{
    return f[fileId][userId];
}

FileTransfer::~FileTransfer() {
    free(files[0]);
    free(files[1]);
    free(files[2]);
}

