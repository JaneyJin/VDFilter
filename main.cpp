# pragma comment(lib, "ws2_32.lib")

#include <iostream>
#include "MainVD.h"
#include "Client.h"

int main() {
    MainVD vd;
    Client client;
    int count = 0;
    double ue_X = 0, ue_Y = 0, ue_V = 0;
    double psi = 0;
    libsumo::TraCIPosition sumo_pos;
    double sumo_angle;


    try {
        client.connect("localhost", 24000);

        while (client.simulation.getMinExpectedNumber() > 0) {

            vd.VD_filter(sumo_pos.x, sumo_pos.y, sumo_angle,&psi, &ue_X, &ue_Y, &ue_V);

            count++;
            if(count % 10 == 0){
                client.simulationStep();



                sumo_pos = client.vehicle.getPosition("car0");
                sumo_angle = client.vehicle.getAngle("car0");
                vd.VD_filter(sumo_pos.x, sumo_pos.y, sumo_angle,&psi, &ue_X, &ue_Y, &ue_V);

            }

        }
    }catch (tcpip::SocketException& e) {
        std::cout << "#Error while connecting: " << e.what();
    }



    std::cout << "Hello, World!" << std::endl;
    return 0;
}
