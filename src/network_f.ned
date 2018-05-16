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
        config.size = size;
    submodules:     
        config : Configurator;  
        n[size] : Node
        {
            //@display("p=100,100,ri,100,100");
        };
        enb    : Enb
        {
            //@display("p=200,200");
        };
}

