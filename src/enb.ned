
package d2dcommunication;

//
// TODO auto-generated module
//
simple Enb
{
    parameters:
        @display("i=device/antennatower");
    gates:
        input in[20] @loose @directIn;
        output out[20] @loose @directIn;
        inout register[20] @loose @directIn;
}
