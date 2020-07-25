#pragma once

#include <string>
#include <vrpn_Analog.h>
#include <vrpn_Button.h>
#include <openvr.h>
#include "vrpn_Tracker_OpenVR.h"

class vrpn_Tracker_OpenVR_Controller :
	public vrpn_Tracker_OpenVR,
	public vrpn_Analog,
	public vrpn_Button_Filter
{
public:
	vrpn_Tracker_OpenVR_Controller() = delete;
	vrpn_Tracker_OpenVR_Controller(const std::string& name, vrpn_Connection* connection, vr::IVRSystem * vr, vr::TrackedDeviceIndex_t trackedDeviceIndex);
	void mainloop();
private:
    void updateController();
    vr::VRControllerState_t pControllerState;
};