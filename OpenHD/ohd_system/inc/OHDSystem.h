//
// Created by consti10 on 02.05.22.
//

#ifndef OPENHD_OHDSYSTEM_H
#define OPENHD_OHDSYSTEM_H


class OHDSystem {
public:
    /**
     * Writes all the system information into json files.
     * Needs to be run on every startup of OpenHD air or ground unit.
     * NOTE: Since Stephen had his microservice approach, looking at this as a whole
     * doesn't really make sense (writing json first, then reading it) but for now it will stay this way.
     */
    static void runOnceOnStartup();
};


#endif //OPENHD_OHDSYSTEM_H
