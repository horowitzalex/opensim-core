#ifndef __ModelScaler_h__
#define __ModelScaler_h__

// ModelScaler.h
// Author: Peter Loan
/*
 * Copyright (c) 2006, Stanford University. All rights reserved. 
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including 
 * without limitation the rights to use, copy, modify, merge, publish, 
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject
 * to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included 
 * in all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
 * CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */


// INCLUDE
#include <iostream>
#include <string>
#include <math.h>
#include "osimToolsDLL.h"
#include "osimToolsDLL.h"
#include <OpenSim/Common/PropertyDblArray.h>
#include <OpenSim/Common/PropertyObj.h>
#include <OpenSim/Common/PropertyBool.h>
#include <OpenSim/Common/PropertyStr.h>
#include <OpenSim/Common/PropertyStrArray.h>
#include <OpenSim/Common/Storage.h>
#include <OpenSim/Common/ScaleSet.h>
#include "MeasurementSet.h"

namespace OpenSim {

class MarkerData;
class Model;

//=============================================================================
//=============================================================================
/**
 * A class for scaling a model. The default method of scaling involves
 * measuring distances between pairs of markers on the model and in a
 * static pose to determine scale factors.
 *
 * @author Peter Loan
 * @version 1.0
 */
class  OSIMTOOLS_API ModelScaler : public Object  
{

//=============================================================================
// DATA
//=============================================================================
private:

protected:
	// order of the two scaling components: measurements and manual scaling
	PropertyStrArray _scalingOrderProp;
	Array<std::string>& _scalingOrder;

	// set of measurements to make on generic model and subject's static pose
	PropertyObj _measurementSetProp;
	MeasurementSet &_measurementSet;

	// set of XYZ scale factors to use for manual scaling
	PropertyObj _scaleSetProp;
	ScaleSet &_scaleSet;

	// name of marker file that contains the static pose
	PropertyStr _markerFileNameProp;
	std::string &_markerFileName;

	// range of frames to average in static pose file, specified by time
	PropertyDblArray _timeRangeProp;
	Array<double> &_timeRange;

	// whether or not to preserve mass distribution in generic model file when scaling
	PropertyBool _preserveMassDistProp;
	bool &_preserveMassDist;

	// name of SIMM joint file to write when done scaling
	PropertyStr _outputJointFileNameProp;
	std::string &_outputJointFileName;

	// name of SIMM muscle file to write when done scaling
	PropertyStr _outputMuscleFileNameProp;
	std::string &_outputMuscleFileName;

	// name of XML model file to write when done scaling
	PropertyStr _outputModelFileNameProp;
	std::string &_outputModelFileName;

	// name of scale file to write when done scaling
	PropertyStr _outputScaleFileNameProp;
	std::string &_outputScaleFileName;

	// amount of allowable motion for each marker when averaging frames of the static trial
	PropertyDbl _maxMarkerMovementProp;
	double &_maxMarkerMovement;

//=============================================================================
// METHODS
//=============================================================================
	//--------------------------------------------------------------------------
	// CONSTRUCTION
	//--------------------------------------------------------------------------
public:
	ModelScaler();
	ModelScaler(const ModelScaler &aModelScaler);
	virtual ~ModelScaler();
	virtual Object* copy() const;

#ifndef SWIG
	ModelScaler& operator=(const ModelScaler &aModelScaler);
#endif
   void copyData(const ModelScaler &aModelScaler);

	bool processModel(Model* aModel, const std::string& aPathToSubject="", double aFinalMass = -1.0);

	/* Register types to be used when reading a ModelScaler object from xml file. */
	static void registerTypes();

	const bool getPreserveMassDist() const
	{
		return _preserveMassDist;
	}

	/**
	 * add a measurement
	 */
	void addMeasurement(Measurement* aMeasurement)
	{
		_measurementSet.append(aMeasurement);
	}
	/**
	 * add a scale factor to current scaleSet
	 */
	void addScale(Scale *aScale)
	{
		_scaleSet.append(aScale);
	}
	//--------------------------------------------------------------------------
	// GET AND SET
	//--------------------------------------------------------------------------

	MeasurementSet& getMeasurementSet() {
		return _measurementSet;
	}

	void setMeasurementSet(MeasurementSet& measurementSet) {
		_measurementSet = measurementSet;
	}

	ScaleSet& getScaleSet() {
		return _scaleSet;
	}

	void setScaleSetFile(const std::string& aScaleSetFilename) {
		_scaleSet = ScaleSet(aScaleSetFilename);
	}

	Array<double> getTimeRange() {
		return _timeRange;
	}

	void setTimeRange(Array<double> timeRange) {
		_timeRange = timeRange;
	}

	void setPreserveMassDist(bool preserveMassDist) {
		_preserveMassDist = preserveMassDist;
	}

	Array<std::string> getScalingOrder() {
		return _scalingOrder;
	}

	void setScalingOrder(Array<std::string>& scalingOrder) {
		_scalingOrder = scalingOrder;
	}

	const std::string& getMarkerFileName() {
		return _markerFileName;
	}

	void setMarkerFileName(const std::string& aMarkerFileName) {
		_markerFileName = aMarkerFileName;
	}

	void setMaxMarkerMovement(const double aMaxMarkerMovement) {
		_maxMarkerMovement = aMaxMarkerMovement;
	}

	double getMaxMarkerMovement() const {
		return _maxMarkerMovement;
	}

	const std::string& getOutputJointFileName() {
		return _outputJointFileName;
	}

	void setOutputJointFileName(const std::string& outputJointFileName) {
		_outputJointFileName = outputJointFileName;
	}

	const std::string& getOutputMuscleFileName() {
		return _outputMuscleFileName;
	}

	void setOutputMuscleFileName(const std::string& aOutputMuscleFileName) {
		_outputMuscleFileName = aOutputMuscleFileName;
	}

	const std::string& getOutputModelFileName() {
		return _outputModelFileName;
	}

	void setOutputModelFileName(const std::string& aOutputModelFileName) {
		_outputModelFileName = aOutputModelFileName;
	}

	const std::string& getOutputScaleFileName() {
		return _outputScaleFileName;
	}

	void setOutputScaleFileName(const std::string& aOutputScaleFileName) {
		_outputScaleFileName = aOutputScaleFileName;
	}

private:
	void setNull();
	void setupProperties();
	double computeMeasurementScaleFactor(const Model& aModel, const MarkerData& aMarkerData, const Measurement& aMeasurement) const;
	double takeModelMeasurement(const Model& aModel, const std::string& aName1, const std::string& aName2, const std::string& aMeasurementName) const;
	double takeExperimentalMarkerMeasurement(const MarkerData& aMarkerData, const std::string& aName1, const std::string& aName2, const std::string& aMeasurementName) const;
//=============================================================================
};	// END of class ModelScaler
//=============================================================================
//=============================================================================

} // end of namespace OpenSim

#endif // __ModelScaler_h__


