
package d2dcommunication;

//
// TODO auto-generated module
//
simple Enb
{
    parameters:
        @display("i=device/antennatower");
    gates:
        input in[20] @loose;
        output out[20] @loose;
        inout register[20] @loose @directIn;
}
