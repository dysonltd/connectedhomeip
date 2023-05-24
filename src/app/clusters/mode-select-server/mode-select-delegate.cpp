/*
*
*    Copyright (c) 2023 Project CHIP Authors
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

#include <app/clusters/mode-select-server/mode-select-server.h>
#include "mode-select-delegate.h"

using namespace std;
using namespace chip;
using namespace chip::app::Clusters;
using namespace chip::app::Clusters::ModeSelect;

using ModeOptionStructType = Structs::ModeOptionStruct::Type;

Status Delegate::HandleChangeToMode(uint8_t mode)
{
    return Status::Success;
}

void Delegate::HandleChangeToModeWitheStatus(uint8_t mode, ModeSelect::Commands::ChangeToModeResponse::Type &response)
{
    response.status = to_underlying(ChangeToModeResponseStatus::kSuccess);
}

uint8_t Delegate::NumberOfModes()
{
    return 0;
}

CharSpan Delegate::getModeLabelByIndex(uint8_t modeIndex, bool &found)
{
    found = false;
    return CharSpan{};
}

uint8_t Delegate::getModeValueByIndex(uint8_t modeIndex, bool &found)
{
    found = false;
    return 0;
}

List<const SemanticTagStructType> Delegate::getModeTagsByIndex(uint8_t modeIndex, bool &found)
{
    found = false;
    return List<const SemanticTagStructType>{};
}

ModeOptionStructType Delegate::getModeByIndex(uint8_t modeIndex, bool &found)
{
    ModeOptionStructType mode;
    if (modeIndex < NumberOfModes())
    {
        mode.label = getModeLabelByIndex(modeIndex, found);
        if (!found) {
            return mode;
        }
        mode.mode = getModeValueByIndex(modeIndex, found);
        if (!found) {
            return mode;
        }
        mode.semanticTags = getModeTagsByIndex(modeIndex, found);
        return mode;
    }
    found = false;
    return mode;
}

bool Delegate::IsSupportedMode(uint8_t modeValue)
{
    bool found = false;
    for (uint8_t i = 0; i < NumberOfModes(); i++) {
        uint8_t val = getModeValueByIndex(i, found);
        if (found) {
            if (val == modeValue) {
                return true;
            }
        } else {
            break;
        }
    }
    ChipLogDetail(Zcl, "Cannot find the mode %u", modeValue);
    return false;
}

ModeOptionStructType Delegate::GetModeByValue(uint16_t modeValue, bool &found)
{
    for (uint8_t i = 0; i < NumberOfModes(); i++) {
        uint8_t val = getModeValueByIndex(i, found);
        if (found) {
            if (val == modeValue) {
                return getModeByIndex(i, found);
            }
        } else {
            break;
        }
    }
    ChipLogDetail(Zcl, "Cannot find the mode %u", modeValue);
    found = false;
    return ModeOptionStructType{};
}
