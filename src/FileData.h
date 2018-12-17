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

#ifndef FILEDATA_H_
#define FILEDATA_H_

#include <vector>
#include "Block.h"

class FileData {
public:
    FileData();
    FileData(int size, int blockSize);

    double getSize()                     { return m_size;      }
    int getNumBlocks()                   { return m_numBlocks; }
    simtime_t getLastUsed()              { return m_lastUsed;  }
    std::vector<Block>& getBlocks()      { return m_blocks;    }
    bool isComplete()                    { return m_complete;  }
    void setComplete(bool value)         { m_complete = value; }

private:
    int m_size;
    int m_numBlocks;
    simtime_t m_lastUsed;
    std::vector<Block> m_blocks;
    bool m_complete;
};

#endif /* FILEDATA_H_ */
