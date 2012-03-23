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

#ifndef SWGANH_SUI_SUI_WINDOW_H_
#define SWGANH_SUI_SUI_WINDOW_H_

#include <string>
#include <memory>
#include <functional>
#include <tuple>

#include "anh/byte_buffer.h"
#include "swganh/object/object.h"
#include "swganh/messages/sui_create_page_message.h"

namespace swganh {
namespace sui {

typedef std::vector<std::wstring> ResultSet;

class SuiService;
class SuiWindow
{
public:
    SuiWindow(void);
    ~SuiWindow(void);

	messages::SuiCreatePageMessage onCreate(void);
	
    uint32_t GetId() { return id_; }

    std::string GetUiScript() { return ui_script_; }
	void SetUiScript(std::string ui_script) { ui_script_ = ui_script; }

	float GetMaxDistance() { return max_distance_; }
	void SetMaxDistance(float max_distance) { max_distance_ = max_distance; }

	uint64_t GetTargetId() { return target_id_; }
	void SetTargetId(uint64_t target_id) { target_id_ = target_id; }

	void SetCancelCallback(std::function<void()> callback) { cancel_callback_ = callback; }
	void SetSuccessCallback(std::function<void(ResultSet&)> callback) { success_callback_ = callback; }

	void SetHandler(std::string handler) { handler_ = handler; }
	std::string GetHandler(void) { return handler_; }

private:
	friend SuiService;

	void SetId(uint32_t id) { id_ = id; }

    uint32_t id_;
    std::string ui_script_;
	std::string handler_;
    std::shared_ptr<swganh::object::Object> owner_;
    float max_distance_;
	uint64_t target_id_;
	std::function<void(ResultSet&)> success_callback_;
	std::function<void()> cancel_callback_;
};

}} // namespace swganh::sui

#endif // SWGANH_SUI_SUI_WINDOW_H_