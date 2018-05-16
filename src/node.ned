 
package d2dcommunication;

//
// TODO auto-generated module
//

simple Node
{
    parameters:
        @display("i=device/cellphone");
        int size = default(10);
        @signal[D2DCommunication](type=unsigned long);
        @signal[D2ICommunication](type=unsigned long);
        @statistic[D2DCommunication](record = vector);
        @statistic[D2ICommunication](record = vector);
    gates:
        input in[size];
        output out[size];
        inout register;
}
