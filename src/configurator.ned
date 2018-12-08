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
// TODO auto-generated module
//
simple Configurator
{
    parameters:
    	int size = default(10);
        
        // new development
        double radius = default(1000);
        double cx = default(radius);
        double cy = default(radius);
        double deltaHeadingMax = default(30);
        double velocityMax = default(15);
        
        double updateInterval = default(1000); //1000ms
}
