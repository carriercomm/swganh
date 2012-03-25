/*
 This file is part of SWGANH. For more information, visit http://swganh.com
 
 Copyright (c) 2006 - 2012 The SWG:ANH Team

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

#include "sui_service.h"

#include <glog/logging.h>

#include "anh/crc.h"
#include "anh/app/kernel_interface.h"
#include "swganh/object/object.h"
#include "swganh/object/creature/creature.h"
#include "swganh/network/remote_client.h"
#include "anh/service/service_manager.h"
#include "sui_window.h"
#include "form/list_box.h"
#include "form/input_box.h"

#include "swganh/command/command_service.h"
#include "swganh/connection/connection_service.h"
#include "swganh/connection/connection_client.h"

using namespace std;

using namespace swganh::connection;
using namespace swganh::messages;

namespace swganh {
namespace sui {

SuiService::SuiService(anh::app::KernelInterface* kernel)
    : BaseService(kernel)
{
}

SuiService::~SuiService(void)
{
}

anh::service::ServiceDescription SuiService::GetServiceDescription(void)
{
    anh::service::ServiceDescription service_description(
        "SuiService",
        "sui",
        "0.1",
        "127.0.0.1",
        0,
        0,
        0);

    return service_description;
}

void SuiService::onStart(void)
{
	auto command_service_ = kernel()->GetServiceManager()->GetService<swganh::command::CommandService>("CommandService");
    command_service_->SetCommandHandler(anh::memcrc("attack"), boost::bind(&SuiService::HandleCommand, this, _1, _2, _3));

    auto connection_service = std::static_pointer_cast<swganh::connection::ConnectionService>(kernel()->GetServiceManager()->GetService("ConnectionService"));
    connection_service->RegisterMessageHandler<swganh::messages::SuiEventNotification>(
        bind(&SuiService::HandleSuiEventNotification, this, placeholders::_1, placeholders::_2));
}

void SuiService::onStop(void)
{
}

void SuiService::HandleSuiEventNotification(std::shared_ptr<ConnectionClient> client, const swganh::messages::SuiEventNotification& message)
{
	auto iter = windows_.find(message.window_id);
	if(iter != windows_.end())
	{
		if(message.cancel) 
		{
			iter->second.cancel_callback_();
			// Close
		}
		else
		{
			iter->second.success_callback_(sui::ResultSet(message.results));
		}
	}
}

void SuiService::HandleCommand(const std::shared_ptr<swganh::object::creature::Creature>& object, const std::shared_ptr<swganh::object::Object>& target, std::wstring properties)
{
	swganh::sui::form::ListBox listbox(L"Anh Character Services", L"Which service would you like to use?");
	listbox.SetId(1);
	listbox.AddItem(L"0", L"Name Change");

	listbox.SetSuccessCallback([=](sui::ResultSet& result) {
		if(result[0].compare(std::wstring(L"0")) == 0) // Name Change
		{
			auto object2 = object;
			swganh::sui::form::InputBox inputbox(L"Name Change", L"Enter your characters new name.");
			inputbox.SetId(2);
			inputbox.SetSuccessCallback([=](sui::ResultSet& result) {
				object2->SetCustomName(result[0]);
			});

			object->GetController()->GetRemoteClient()->Send(inputbox.onCreate());
			windows_.insert(std::pair<uint32_t, SuiWindow>(inputbox.GetId(), std::move(inputbox)));
		}
	});

	object->GetController()->GetRemoteClient()->Send(listbox.onCreate());
	windows_.insert(std::pair<uint32_t, SuiWindow>(listbox.GetId(), std::move(listbox)));
}

}} // namespace swganh::sui