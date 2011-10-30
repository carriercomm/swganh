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

#include "factory_crate_message_builder.h"
#include "factory_crate.h"

using namespace swganh::object::factory_crate;
using namespace swganh::messages;

boost::optional<BaselinesMessage> FactoryCrateMessageBuilder::GetBaseline3(FactoryCrate* factory_crate)
{
    auto message = factory_crate->CreateBaselinesMessage(Object::VIEW_3, 11);
    message.data.append(factory_crate->BaseTangible::GetBaseline3().get().data);
    return boost::optional<BaselinesMessage>(std::move(message));
}

boost::optional<BaselinesMessage> FactoryCrateMessageBuilder::GetBaseline6(FactoryCrate* factory_crate)
{
    auto message = factory_crate->CreateBaselinesMessage(Object::VIEW_6, 11);
    message.data.append(factory_crate->BaseTangible::GetBaseline6().get().data);
    return boost::optional<BaselinesMessage>();
}