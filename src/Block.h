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

#ifndef BLOCK_H_
#define BLOCK_H_

#include <omnetpp.h>

using namespace omnetpp;

class Block {
public:
    Block();

    bool isPresent()        { return m_isPresent; }
    simtime_t getLastUsed() { return m_lastUsed; }

private:
    bool m_isPresent;
    simtime_t m_lastUsed;
};

#endif /* BLOCK_H_ */
