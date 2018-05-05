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
    submodules:       
        n[20] : Node
        {
            @display("p=100,100,ri,100,100");
        };
        enb    : Enb
        {
            @display("p=200,200");
        };
        
    connections:
        for i = 0..19
        {
            n[i].in  <-- { delay = uniform(10ms, 100ms); } <-- enb.out[i];
        	n[i].out --> { delay = uniform(10ms, 100ms); } --> enb.in[i];
        }
        
}

