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
#include "swganh/network/remote_client.h"
#include "anh/service/service_manager.h"

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
    command_service_ = kernel->GetServiceManager()->GetService<swganh::command::CommandService>("CommandService");
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
    command_service_->SetCommandHandler(anh::memcrc("attack"), boost::bind(&SuiService::HandleCommand, this, _1, _2, _3, _4));

    auto connection_service = std::static_pointer_cast<swganh::connection::ConnectionService>(kernel()->GetServiceManager()->GetService("ConnectionService"));
    connection_service->RegisterMessageHandler<swganh::messages::SuiEventNotification>(
        bind(&SuiService::HandleSuiEventNotification, this, placeholders::_1, placeholders::_2));
}

void SuiService::onStop(void)
{
}

void SuiService::HandleSuiEventNotification(std::shared_ptr<ConnectionClient> client, const swganh::messages::SuiEventNotification& message)
{
    LOG(ERROR) << "SuiEventNotification";
}

void SuiService::HandleCommand(std::shared_ptr<swganh::object::Object> object, uint64_t object_id, uint64_t target_it, std::wstring properties)
{
    LOG(ERROR) << "Sending...";

    anh::ByteBuffer window;
    window.write<uint16_t>(2); // World Update
    window.write<uint32_t>(anh::memcrc("SuiCreatePageMessage")); // CRC
    window.write<uint32_t>(rand()); // Window Id
    window.write<std::string>("Script.listBox");
    window.write<uint32_t>(11); // Element List Size

    window.write<uint8_t>(5);
    window.write<uint32_t>(0);
    window.write<uint32_t>(7);
    window.write<uint16_t>(0);
    window.write<uint16_t>(1);
    window.write<uint8_t>(9);
    window.write<std::string>("onGuildSponsoredOptionsResponse");
    window.write<std::string>("List.lstList");
    window.write<std::string>("SelectedRow");
    window.write<std::string>("bg.caption.lblTitle");
    window.write<std::string>("Text");

    window.write<uint8_t>(5);
    window.write<uint32_t>(0);
    window.write<uint32_t>(7);
    window.write<uint16_t>(0);
    window.write<uint16_t>(1);
    window.write<uint8_t>(9);
    window.write<std::string>("onGuildSponsoredOptionsResponse");
    window.write<std::string>("List.lstList");
    window.write<std::string>("SelectedRow");
    window.write<std::string>("bg.caption.lblTitle");
    window.write<std::string>("Text");
    
    window.write<uint8_t>(3);
    window.write<uint32_t>(1);
    window.write<std::wstring>(L"@guild:sponsored_options_title");
    window.write<uint32_t>(2);
    window.write<std::string>("bg.caption.lblTitle");
    window.write<std::string>("Text");
    
    window.write<uint8_t>(3);
    window.write<uint32_t>(1);
    window.write<std::wstring>(L"Sponsored for membership:\nRokig\nDaela\nYou may accept them into the guild. Decline their membership or cancel to leave them unchanged for now.");
    window.write<uint32_t>(2);
    window.write<std::string>("Prompt.lblPrompt");
    window.write<std::string>("Text");    

    window.write<uint8_t>(3);
    window.write<uint32_t>(1);
    window.write<std::wstring>(L"@cancel");
    window.write<uint32_t>(2);
    window.write<std::string>("btnCancel");
    window.write<std::string>("Text");

    window.write<uint8_t>(3);
    window.write<uint32_t>(1);
    window.write<std::wstring>(L"@ok");
    window.write<uint32_t>(2);
    window.write<std::string>("btnOk");
    window.write<std::string>("Text");
    
    
    window.write<uint8_t>(1);
    window.write<uint32_t>(0);
    window.write<uint32_t>(1);
    window.write<std::string>("List.dataList");
    
    window.write<uint8_t>(4);
    window.write<uint32_t>(1);
    window.write<std::wstring>(L"0");
    window.write<uint32_t>(2);
    window.write<std::string>("List.dataList");
    window.write<std::string>("Name");

    window.write<uint8_t>(3);
    window.write<uint32_t>(1);
    window.write<std::wstring>(L"@guild:accept");
    window.write<uint32_t>(2);
    window.write<std::string>("List.dataList.0");
    window.write<std::string>("Text");

    window.write<uint8_t>(4);
    window.write<uint32_t>(1);
    window.write<std::wstring>(L"1");
    window.write<uint32_t>(2);
    window.write<std::string>("List.dataList");
    window.write<std::string>("Name");

    window.write<uint8_t>(3);
    window.write<uint32_t>(1);
    window.write<std::wstring>(L"@guild:decline");
    window.write<uint32_t>(2);
    window.write<std::string>("List.dataList.1");
    window.write<std::string>("Text");

    window.write<uint64_t>(0);
    window.write<uint64_t>(0);
    window.write<uint32_t>(0);
    object->GetController()->GetRemoteClient()->GetSession()->SendMessage(window);
}

}} // namespace swganh::sui