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

#ifndef FILECACHE_H_
#define FILECACHE_H_

#include <map>
#include "FileData.h"

class FileCache {
public:
    FileCache();

    void setBlockSize(int blockSize)     { m_dblockSize = blockSize; }
    void setMaxSize(int maxSize)         { m_dmaxSize   = maxSize;   }
    int getBlockSize()                   { return m_dblockSize; }
    int getMaxSize()                     { return m_dmaxSize;   }
    FileData& getFile(int fileName);
    bool findFile(int fileName);
    FileData& createFile(int fileName, int FileS);

private:
    int m_dblockSize;
    int m_dmaxSize;
    std::map<int, FileData> m_files;
};

#endif /* FILECACHE_H_ */
