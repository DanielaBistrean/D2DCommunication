
package d2dcommunication;

network net
{
    submodules:
        n1 : Node;
        n2 : Node;
        enb : Enb;
        
    connections:
        n1.out --> { delay = uniform(10ms, 100ms); } --> enb.in[1];
        n1.in  <-- { delay = uniform(10ms, 100ms); } <-- enb.out[1];
        n2.out --> { delay = uniform(10ms, 100ms); } --> enb.in[2];
        n2.in  <-- { delay = uniform(10ms, 100ms); } <-- enb.out[2];
}