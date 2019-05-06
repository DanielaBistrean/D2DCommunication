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

#ifndef FILETRANSFER_H_
#define FILETRANSFER_H_

#include "data_packet_m.h"

#define NONE 0
#define DOWNLOAD 1
#define READY 2

class FileTransfer {
public:
    FileTransfer();
    virtual ~FileTransfer();
protected:
    virtual Data_packet* createFileResponse(int userId, int fileId, int seqNumber);
    virtual void updateProgress(int userId, int fileId, int bytes_sent);
    virtual int getFileStatus(int userId, int fileId);
//    virtual int getFilesNumber();
private:
    char *files[3];
    int fsize[3];
    int f[3][20] = { {0}, {0}, {0} };
    int progress[3][20] = { {0}, {0}, {0} };

};

#endif /* FILETRANSFER_H_ */
