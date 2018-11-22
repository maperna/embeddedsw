/******************************************************************************
*
* Copyright (C) 2018 Xilinx, Inc.  All rights reserved.
*
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in
* all copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
* XILINX  BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
* WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF
* OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
* SOFTWARE.
*
* Except as contained in this notice, the name of the Xilinx shall not be used
* in advertising or otherwise to promote the sale, use or other dealings in
* this Software without prior written authorization from Xilinx.
*
******************************************************************************/

#include "xpm_requirement.h"
#include "xpm_power.h"
#include "xillibpm_api.h"

XStatus XPmRequirement_Init(XPm_Requirement *Reqm,
		XPm_Subsystem *Subsystem, XPm_Device *Device)
{
	/* Prepend to subsystem's device reqm list */
	Reqm->NextDevice = Subsystem->Requirements;
	Subsystem->Requirements = Reqm;
	Reqm->Subsystem = Subsystem;

	/* Prepend to device's subsystem reqm list */
	Reqm->NextSubsystem = Device->Requirements;
	Device->Requirements = Reqm;
	Reqm->Device = Device;

	Reqm->Allocated = 0;
	Reqm->Curr.Capabilities = XPM_MIN_CAPABILITY;
	Reqm->Curr.Latency = XPM_MAX_LATENCY;
	Reqm->Curr.QoS = XPM_MAX_QOS;
	Reqm->Next.Capabilities = XPM_MIN_CAPABILITY;
	Reqm->Next.Latency = XPM_MAX_LATENCY;
	Reqm->Next.QoS = XPM_MAX_QOS;

	return XST_SUCCESS;
}

void XPm_RequiremntUpdate(XPm_Requirement *Reqm)
{
	Reqm->Curr.Capabilities = Reqm->Next.Capabilities;
	Reqm->Curr.Latency = Reqm->Next.Latency;
	Reqm->Curr.QoS = Reqm->Next.QoS;
}