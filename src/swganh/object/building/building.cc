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

#include "swganh/object/building/building.h"
#include "swganh/object/building/building_message_builder.h"

using namespace std;
using namespace swganh::object::building;

Building::Building(void)
    : BaseTangible()
{
}

Building::~Building(void)
{
}

boost::optional<swganh::messages::BaselinesMessage> Building::GetBaseline3(void)
{
    return BuildingMessageBuilder::GetBaseline3(this);
}

boost::optional<swganh::messages::BaselinesMessage> Building::GetBaseline6(void)
{
    return BuildingMessageBuilder::GetBaseline6(this);
}

uint32_t Building::GetType() const
{
    return type;
}