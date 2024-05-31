/*
 *
 *    Copyright (c) 2024 Project CHIP Authors
 *    All rights reserved.
 *
 *    Licensed under the Apache License, Version 2.0 (the "License");
 *    you may not use this file except in compliance with the License.
 *    You may obtain a copy of the License at
 *
 *        http://www.apache.org/licenses/LICENSE-2.0
 *
 *    Unless required by applicable law or agreed to in writing, software
 *    distributed under the License is distributed on an "AS IS" BASIS,
 *    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *    See the License for the specific language governing permissions and
 *    limitations under the License.
 */

#pragma once

#include <app-common/zap-generated/cluster-objects.h>
#include <app/clusters/service-area-server/service-area-server.h>
#include <protocols/interaction_model/StatusCode.h>

#include <string>
#include <map>


namespace chip {
namespace app {
namespace Clusters {


class RvcDevice;

typedef void (RvcDevice::*GetRemainingTimeCallback)(DataModel::Nullable<uint32_t> & aRemainineTime);
typedef bool (RvcDevice::*IsSetSelectedLocationAllowedCallback)(std::string & statusText);


namespace ServiceArea {


// This is an application level delegate to handle service area cluster commands and attribute access according to the business logic of the iRobot device.
class RvcServiceAreaDelegate : public ServiceArea::Delegate
{
private:

    RvcDevice * mSetSelectedLocationAllowedInstance;
    IsSetSelectedLocationAllowedCallback mSetSelectedLocationAllowedCallback;

    // containers for array attributes
    std::map<uint32_t, LocationStructureWrapper>       mSupportedLocationsById;     // main storage for supported locations
    std::vector<LocationStructureWrapper*>             mSupportedLocationsByIndex;  // for fast indexed access - mainly for attribute reads and validations.
                                                                                    // puts a O(n) update burden on Add and Delete functions

    // aliases for container types
    using SupportedLocationPairType = decltype(mSupportedLocationsById)::value_type;
    using SupportedLocationType     = decltype(mSupportedLocationsById)::mapped_type;


public:

    void SetIsSetSelectedLocationCallback(IsSetSelectedLocationAllowedCallback aCallback, RvcDevice * aInstance);


protected:

void HandleVolatileCurrentLocation(const DataModel::Nullable<uint32_t> prevCurrentLocation) override;

void HandleVolatileEstimatedEndTime(const DataModel::Nullable<uint32_t> prevEstimatedEndTime) override;

void HandleSelectedLocationsChanged() override;

void HandleVolatileProgressList() override;   

bool IsSetSelectedLocationAllowed(std::string & statusText) override;

bool HandleSetSelectLocations(const std::vector<uint32_t> & newSelectLocations, SelectLocationsStatus & locationStatus, std::string & locationStatusText) override;

bool HandleSkipCurrentLocation(std::string & skipStatusText) override;



//*************************************************************************
// Supported Locations accessors

void ReloadSupportedLocationsVector();

size_t GetNumberOfSupportedLocations() override;

bool GetSupportedLocationByIndex(uint32_t listIndex, const LocationStructureWrapper *& supportedLocation) override;

bool GetSupportedLocationById(uint32_t aLocationId, const LocationStructureWrapper *& supportedLocation) override;

bool GetWritableSupportedLocationById(uint32_t aLocationId, LocationStructureWrapper *& supportedLocation) override;

bool IsSupportedLocation(uint32_t aLocationId) override;

bool AddSupportedLocation(const LocationStructureWrapper & supportedLocation) override;

uint32_t RemoveSupportedLocationByIndex(uint32_t  locationIndex) override;

bool RemoveSupportedLocationById(uint32_t aLocationId) override;

bool ClearSupportedLocations() override;

};


} // namespace Location
} // namespace Clusters
} // namespace app
} // namespace chip
