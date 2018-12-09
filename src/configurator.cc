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

#include "configurator.h"

Define_Module(Configurator);

void Configurator::initialize()
{
    // new development
    double x = par("cx");
    double y = par("cy");
    double dRadius = par("radius");

    this->getDisplayString().setTagArg("p", 0, (int) (x + dRadius));
    this->getDisplayString().setTagArg("p", 1, (int) (y + dRadius));


    int size = par("size");
    enb = this->getParentModule()->getSubmodule("gNB");
    nodes = new cModule* [size];
    for(int i = 0; i < size; i++)
        nodes[i] = this->getParentModule()->getSubmodule("n", i);
}

cModule* Configurator::getConfigurator(cModule *thisModule)
{
    while(thisModule->getParentModule() != nullptr)
    {
        thisModule = thisModule->getParentModule();
    }

    return thisModule->getSubmodule("config");
}

cGate* Configurator::geteNBControlGate(int userId)
{
    return enb->gate("register$i", userId);
}

cGate* Configurator::getNodeControlGate(int userId)
{
    return nodes[userId]->gate("register$i");
}

cGate* Configurator::getNodeGate(int userId, int sid)
{
    return nodes[userId]->gate("in", sid + 1);
}

cGate* Configurator::getENBGate(int userId)
{
    return enb->gate("in", userId);
}

void Configurator::finish()
{
    delete [] nodes;
}
