#ifndef OPENSIM_SLIDER_JOINT_H_
#define OPENSIM_SLIDER_JOINT_H_
/* -------------------------------------------------------------------------- *
 *                          OpenSim:  SliderJoint.h                           *
 * -------------------------------------------------------------------------- *
 * The OpenSim API is a toolkit for musculoskeletal modeling and simulation.  *
 * See http://opensim.stanford.edu and the NOTICE file for more information.  *
 * OpenSim is developed at Stanford University and supported by the US        *
 * National Institutes of Health (U54 GM072970, R24 HD065690) and by DARPA    *
 * through the Warrior Web program.                                           *
 *                                                                            *
 * Copyright (c) 2005-2012 Stanford University and the Authors                *
 * Author(s): Ajay Seth                                                       *
 *                                                                            *
 * Licensed under the Apache License, Version 2.0 (the "License"); you may    *
 * not use this file except in compliance with the License. You may obtain a  *
 * copy of the License at http://www.apache.org/licenses/LICENSE-2.0.         *
 *                                                                            *
 * Unless required by applicable law or agreed to in writing, software        *
 * distributed under the License is distributed on an "AS IS" BASIS,          *
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.   *
 * See the License for the specific language governing permissions and        *
 * limitations under the License.                                             *
 * -------------------------------------------------------------------------- */

// INCLUDE
#include <OpenSim/Simulation/osimSimulationDLL.h>
#include "Joint.h"

namespace OpenSim {

//=============================================================================
//=============================================================================
/**
A class implementing a Slider joint.  A class implementing a Slider joint.  The
underlying implementation in Simbody is a SimTK::MobilizedBody::Slider.
Slider provides a single mobility along the common X-axis of the joint frames
(not body) in the parent and body.

\image html sliderJoint.gif

@author Ajay Seth
*/


class OSIMSIMULATION_API SliderJoint : public Joint {
OpenSim_DECLARE_CONCRETE_OBJECT(SliderJoint, Joint);
//=============================================================================
// METHODS
//=============================================================================
public:
    /** Use Joint's constructors. @see Joint */
    using Joint::Joint;

    virtual ~SliderJoint() {}

    int numCoordinates() const { return _numMobilities; }

protected:
    void extendFinalizeFromProperties() override;
    void extendAddToSystem(SimTK::MultibodySystem& system) const override;

private:
    static const int _numMobilities = 1;

//=============================================================================
};  // END of class SliderJoint
//=============================================================================
//=============================================================================

} // end of namespace OpenSim

#endif // OPENSIM_SLIDER_JOINT_H_
