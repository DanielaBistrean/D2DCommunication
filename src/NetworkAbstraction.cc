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

#include "NetworkAbstraction.h"
#include <algorithm>

NetworkAbstraction::NetworkAbstraction() {
    // TODO Auto-generated constructor stub
}

NetworkAbstraction::~NetworkAbstraction() {
    // TODO Auto-generated destructor stub
}

NetworkAbstraction&
NetworkAbstraction::getInstance()
{
   static NetworkAbstraction n;

   return n;
}

void
NetworkAbstraction::registerUser(Node *user)
{
    m_vUsers.push_back(user);
    EV << "User " << user->getFullName() << " registered\n";
}

void
NetworkAbstraction::deregisterUser(Node *user)
{
    auto pos = std::find(m_vUsers.begin(), m_vUsers.end(), user);
    if (pos != m_vUsers.end())
    {
        m_vUsers.erase(pos);
    }
    EV << "User " << user->getFullName() << " was erased\n";
}

/*
 * purpose: provides a way for nodes to broadcast a message
 *          to every other node in a given area around the
 *          sender.
 *
 * inputs:  the sender node
 *          the message to be sent
 *          the range (defaults to simulation default)
 *
 * execution: the function iterates through the list of nodes
 *          and checks if the distance from the sender to
 *          another nodes is smaller than the range. If this
 *          is true, then the function sends the message to
 *          that node with a latency proportional to the distance.
 *
 * return:  the number of nodes to which the message has been
 *          sent.
 *
 */

unsigned int
NetworkAbstraction::broadcast(Node *sender, cMessage *msg, unsigned int maxRange)
{
    unsigned int count = 0;

    if (maxRange == 0)
    {
       maxRange = 100; //ToDo: make config singleton
    }

    for (const auto &node : m_vUsers)
    {
        if (node != sender)
        {
            double dist = sqrt((node->getX() - sender->getX()) * (node->getX() - sender->getX()) + (node->getY() - sender->getY()) * (node->getY() - sender->getY()));
            if (dist < maxRange)
            {
                cMessage *copy = msg->dup();
                sender->sendDirect(copy, dist/10000, 0, node->gate("in", sender->getId() + 1));
                count++;
            }
        }
    }

    return count;
}
