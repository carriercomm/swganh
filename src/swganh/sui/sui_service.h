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

#ifndef SWGANH_SUI_SUI_SERVICE_H_
#define SWGANH_SUI_SUI_SERVICE_H_

#include <cstdint>
#include <map>
#include <memory>
#include <string>

#include "swganh/base/base_service.h"
#include "swganh/messages/sui_event_notification.h"
#include "swganh/sui/sui_window.h"

namespace swganh {
namespace object {

class Object;

}} // namespace swganh::object

namespace swganh {
namespace object {
namespace creature {

class Creature;

}}} // namespace swganh::object::creature

namespace swganh {
namespace connection {

class ConnectionClient;

}} // namespace swganh::connection

namespace swganh {
namespace sui {

class SuiWindow;

class SuiService : public swganh::base::BaseService
{
public:
    explicit SuiService(anh::app::KernelInterface* kernel);
    ~SuiService(void);

    anh::service::ServiceDescription GetServiceDescription();

    void onStart(void);
    void onStop(void);

    // SuiService API Methods
    std::shared_ptr<SuiWindow> GetSuiWindowById(uint64_t id);
    bool ManageWindow(SuiWindow&& window);
    bool DestroyWindow(uint64_t id);
    

private:

    void HandleCommand(
		const std::shared_ptr<swganh::object::creature::Creature>&, 
		const std::shared_ptr<swganh::object::Object>&, 
		std::wstring);

    void HandleSuiEventNotification(std::shared_ptr<swganh::connection::ConnectionClient> client, const swganh::messages::SuiEventNotification& message);

	std::map<uint32_t, SuiWindow> windows_;

};

}} // namespace swganh::sui

#endif // SWGANH_SUI_SUI_SERVICE_H_