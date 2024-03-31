# IET
hello not world.
ab -n 1000 -c 100 http://hello/


 not very expert in network security.
But our idea is to implement a model of a system, which consists of 2 esp32 microcontrollers, which basically are small control ic with wifi capabilities.
So in the system  1 esp32 will act as the Programmable logic controller, controlling some actuators simulated in software, the data communication with this plc will be handled by another esp32 ( used as switch) which will be responsible for getting data from servers and sending to plc, we kept both separate because we think keeping it isolated and implementing it as a data diode can be a secure practice, and we will have intrusion detection system in the esp32 acting as switch. So in case of intrusion, the system will detect this, and to avoid catastrophic events the plc will shift to a safe mode, in which it will operate based on some predefined parameters, defined specially for such events of intrusion/failure.

I am still not very knowledgeable or expert in this field or have any real industry experience, but this is a basic idea.

What are your opinions?
Is the idea fine? Will it in anyway comply with industry practices?
Please do let me know if you have experience regarding this!!
Thanks alot for reading!
I hope i communicated the idea properly.
