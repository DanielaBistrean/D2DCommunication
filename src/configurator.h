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

#ifndef __D2DCOMMUNICATION_CONFIGURATOR_H_
#define __D2DCOMMUNICATION_CONFIGURATOR_H_

#include <omnetpp.h>

using namespace omnetpp;

/**
 * TODO - Generated class
 */
class Configurator : public cSimpleModule
{
  protected:
    virtual void initialize();
    virtual void finish();

  private:
    cModule* enb;
    cModule** nodes;

  public:
    static cModule* getConfigurator(cModule *thisModule);
    cGate* geteNBControlGate(int userId); // userId because control gate is a vector at eNB
    cGate* getNodeControlGate(int userId);// userId because there is a vector of users
    cGate* getNodeGate(int userId, int sid);
    cGate* getENBGate(int userId);
};

#endif
