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

package d2dcommunication;
//
// TODO documentation
//
network final_net
{
    parameters:
        int size = default(10);
        n[*].size = size;
    submodules:       
        n[size] : Node
        {
            //@display("p=100,100,ri,100,100");
        };
        enb    : Enb
        {
            //@display("p=200,200");
        };
        //ac : Node;
        
    connections:
        for i = 0..(size - 1)
        {
            n[i].in[0]  <-- { delay = uniform(10us, 100us); } <-- enb.out[i];
        	n[i].out[0] --> { delay = uniform(10us, 100us); } --> enb.in[i];
        	n[i].register <--> enb.register[i];
        }
        
        for i = 0..(size - 1), for j = 0..(size - 1), if i != j
        {
            n[i].in++ <-- { delay = uniform(10us, 100us); } <-- n[j].out++;
            n[i].out++ --> { delay = uniform(10us, 100us); } --> n[j].in++;
        }
        
}

