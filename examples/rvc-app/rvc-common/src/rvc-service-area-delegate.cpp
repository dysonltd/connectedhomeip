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
#include <rvc-service-area-delegate.h>

using namespace chip;
using namespace chip::app;
using namespace chip::app::Clusters;
using namespace chip::app::Clusters::ServiceArea;


void RvcServiceAreaDelegate::HandleVolatileCurrentLocation(const DataModel::Nullable<uint32_t> prevCurrentLocation)
{
    // TODO IMPLEMENT
};

void RvcServiceAreaDelegate::HandleVolatileEstimatedEndTime(const DataModel::Nullable<uint32_t> prevEstimatedEndTime)
{
    // TODO IMPLEMENT
};

void RvcServiceAreaDelegate::HandleSelectedLocationsChanged()
{
    // TODO IMPLEMENT
};

void RvcServiceAreaDelegate::HandleVolatileProgressList()
{
    // TODO IMPLEMENT
};   

bool RvcServiceAreaDelegate::IsSetSelectedLocationAllowed(std::string & statusText)
{
    return (mSetSelectedLocationAllowedInstance->*mSetSelectedLocationAllowedCallback)(statusText);
};

void RvcServiceAreaDelegate::SetIsSetSelectedLocationCallback(IsSetSelectedLocationAllowedCallback aCallback, RvcDevice * aInstance)
{
    mSetSelectedLocationAllowedCallback = aCallback;
    mSetSelectedLocationAllowedInstance = aInstance;
};

bool RvcServiceAreaDelegate::HandleSetSelectLocations(const std::vector<uint32_t> & newSelectLocations, 
                                            SelectLocationsStatus & locationStatus, std::string & locationStatusText) 
{
    bool ret_value = false;

    ret_value = true; // TODO IMPLEMENT

    return ret_value;
};

bool RvcServiceAreaDelegate::HandleSkipCurrentLocation(std::string & skipStatusText)
{
    bool ret_value = false;

    ret_value = true; // TODO IMPLEMENT

    return ret_value;
};



//*************************************************************************
// Supported Locations accessors

void RvcServiceAreaDelegate::ReloadSupportedLocationsVector()
{
    mSupportedLocationsByIndex.resize(mSupportedLocationsById.size());

    uint32_t locationIndex = 0;
    for (auto & entry : mSupportedLocationsById)
    {
        mSupportedLocationsByIndex[locationIndex++] = &entry.second;
    }
}

size_t RvcServiceAreaDelegate::GetNumberOfSupportedLocations() 
{
    return mSupportedLocationsByIndex.size();
}

bool RvcServiceAreaDelegate::RvcServiceAreaDelegate::GetSupportedLocationByIndex(uint32_t listIndex, const LocationStructureWrapper *& supportedLocation) 
{
    bool ret_value = false;

    if (listIndex < mSupportedLocationsByIndex.size())
    {
        supportedLocation = mSupportedLocationsByIndex[listIndex];
        ret_value = true;
    }

    return ret_value;
};

bool RvcServiceAreaDelegate::GetSupportedLocationById(uint32_t aLocationId, const LocationStructureWrapper *& supportedLocation)
{
    bool ret_value = false;

    auto locationIter = mSupportedLocationsById.find(aLocationId);

    if (locationIter != mSupportedLocationsById.end())
    {
        supportedLocation = &locationIter->second;
        ret_value = true;
    }

    return ret_value;
}

bool RvcServiceAreaDelegate::GetWritableSupportedLocationById(uint32_t aLocationId, LocationStructureWrapper *& supportedLocation)
{
    bool ret_value = false;

    auto locationIter = mSupportedLocationsById.find(aLocationId);

    if (locationIter != mSupportedLocationsById.end())
    {
        supportedLocation = &locationIter->second;
        ret_value = true;
    }

    return ret_value;
}

bool RvcServiceAreaDelegate::IsSupportedLocation(uint32_t aLocationId)
{
    const LocationStructureWrapper *supportedLocation;

    return GetSupportedLocationById(aLocationId, supportedLocation);
}


bool RvcServiceAreaDelegate::AddSupportedLocation(const LocationStructureWrapper & supportedLocation) 
{
    bool ret_value = false;

    auto result = mSupportedLocationsById.insert(SupportedLocationPairType(supportedLocation.locationId, supportedLocation));

    if (result.second)
    {
        // insertion successful - reload the vector aliases
        ReloadSupportedLocationsVector();
        ret_value = true;
    }

    return ret_value;
}

uint32_t RvcServiceAreaDelegate::RemoveSupportedLocationByIndex(uint32_t locationIndex)
{
    if (locationIndex < mSupportedLocationsByIndex.size())
    {
        uint32_t locationId = mSupportedLocationsByIndex[locationIndex]->locationId;

        // erase from the map - remaining references from within the vector are still valid
        mSupportedLocationsById.erase(locationId);

        // erase from vector- incurs vector re-allocate and copy
        mSupportedLocationsByIndex.erase(mSupportedLocationsByIndex.begin() + locationIndex);
    }

    // for this a vector implementation, vector index does not change on delete - now points to next element
    return locationIndex;  
}

bool RvcServiceAreaDelegate::RemoveSupportedLocationById(uint32_t aLocationId)
{
    bool ret_value = false;

    if (mSupportedLocationsById.erase(aLocationId) != 0)
    {
        // insertion successful - reload the vector aliases
        // - incurs vector re-allocate, map iterate, pointer copy
        ReloadSupportedLocationsVector();
        ret_value = true;       
    }

    return ret_value;
}

bool RvcServiceAreaDelegate::ClearSupportedLocations()
{
    bool ret_value = false;

    if (mSupportedLocationsById.size() > 0)
    {
        mSupportedLocationsById.clear();
        mSupportedLocationsByIndex.clear();
        ret_value = true;
    }

    return ret_value;
}
