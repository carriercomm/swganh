/*
 This file is part of SWGANH. For more information, visit http://swganh.com
 
 Copyright (c) 2006 - 2011 The SWG:ANH Team

 This program is free software; you can redistribute it and/or
 modify it under the terms of the GNU General Public License
 as published by the Free Software Foundation; either version 2
 of the License, or (at your option) any later version.

 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with this program; if not, write to the Free Software
 Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/

#include "building_message_builder.h"

using namespace swganh::object;
using namespace swganh::messages;
using namespace swganh::messages::containers;

namespace swganh {
namespace object {
namespace building {

boost::optional<BaselinesMessage> BuildingMessageBuilder::GetBaseline3(Building* building)
{
    auto message = building->CreateBaselinesMessage(Object::VIEW_3, 5);
    message.data.append(building->BaseTangible::GetBaseline3().get().data);
    return boost::optional<BaselinesMessage>(std::move(message));
}

boost::optional<BaselinesMessage> BuildingMessageBuilder::GetBaseline6(Building* building)
{
    auto message = building->CreateBaselinesMessage(Object::VIEW_6, 5);
    message.data.append(building->BaseTangible::GetBaseline6().get().data);
    return boost::optional<BaselinesMessage>(std::move(message));
}

}}} // namespace swganh::object::building