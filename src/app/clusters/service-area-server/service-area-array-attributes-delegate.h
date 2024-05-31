/*
 *
 *    Copyright (c) 2024 Project CHIP Authors
 *    All rights reserved.
 *
 *    Licensed under the Apache License, Version 2.0 (the "License");
 *    you may not use this file except in compliance with the License.
 *    You may obtain a copy of the License at
 *
 *      
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 *    Unless required by applicable law or agreed to in writing, software
 *    distributed under the License is distributed on an "AS IS" BASIS,
 *    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *    See the License for the specific language governing permissions and
 *    limitations under the License.
 */

#pragma once


#include "service-area-cluster-objects.h"


namespace chip {
namespace app {
namespace Clusters {
namespace ServiceArea {



/**
 * A class which wraps a Service Area Cluster LocStruct instance, adding string storage and string utility functions.
 */
class ServiceAreaArrayAttributeDelegate
{
private:  // temporary

    LocationStructureWrapper  mSupportedLocation {  777, 
                                                    DataModel::Nullable<uint_fast8_t>(),
                                                    CharSpan::fromCharString("My Location D"),
                                                    DataModel::Nullable<int16_t>( 1),
                                                    DataModel::Nullable<ServiceArea::AreaTypeTag>(),
                                                    DataModel::Nullable<ServiceArea::LandmarkTag>(ServiceArea::LandmarkTag::kCouch),
                                                    DataModel::Nullable<ServiceArea::PositionTag>(ServiceArea::PositionTag::kNextTo),
                                                    DataModel::Nullable<ServiceArea::FloorSurfaceTag>(ServiceArea::FloorSurfaceTag::kHardwood) };
protected:
    ServiceAreaArrayAttributeDelegate() {}
    ~ServiceAreaArrayAttributeDelegate() = default;

private:
    ServiceAreaArrayAttributeDelegate(const ServiceAreaArrayAttributeDelegate &)             = delete;
    ServiceAreaArrayAttributeDelegate & operator=(const ServiceAreaArrayAttributeDelegate &) = delete;


public:

//*************************************************************************
// Supported Locations accessors

virtual size_t GetNumberOfSupportedLocations() = 0;

virtual bool GetSupportedLocationByIndex(uint32_t listIndex, const LocationStructureWrapper *& supportedLocation) = 0;

virtual bool GetSupportedLocationById(uint32_t aLocationId, const LocationStructureWrapper *& supportedLocation) = 0;

virtual bool GetWritableSupportedLocationById(uint32_t aLocationId, LocationStructureWrapper *& supportedLocation) = 0;

virtual bool IsSupportedLocation(uint32_t aLocationId) = 0;

virtual bool AddSupportedLocation(const LocationStructureWrapper & supportedLocation) = 0;

virtual uint32_t RemoveSupportedLocationByIndex(uint32_t locationIndex) = 0;

virtual bool RemoveSupportedLocationById(uint32_t aLocationId) = 0;

virtual bool ClearSupportedLocations() = 0;

};




} // namespace ServiceArea
} // namespace Clusters
} // namespace app
} // namespace chip
