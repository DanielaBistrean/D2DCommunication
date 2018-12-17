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

#ifndef NETWORKABSTRACTION_H_
#define NETWORKABSTRACTION_H_

#include <vector>

#include "node.h"

class NetworkAbstraction
{
public:
    virtual ~NetworkAbstraction();
    static NetworkAbstraction& getInstance();
    NetworkAbstraction(NetworkAbstraction const&) = delete;
    void operator=(NetworkAbstraction const&) = delete;
    void registerUser(Node *user);
    void deregisterUser(Node *user);
    unsigned int broadcast(Node *user, cMessage *msg, unsigned int maxRange = 0);
private:
    NetworkAbstraction();
    std::vector<Node *> m_vUsers;
};

#endif /* NETWORKABSTRACTION_H_ */
