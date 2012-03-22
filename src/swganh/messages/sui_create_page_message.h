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

#ifndef SWGANH_MESSAGE_SUI_CREATE_PAGE_MESSAGE_H_
#define SWGANH_MESSAGE_SUI_CREATE_PAGE_MESSAGE_H_

#include <cstdint>
#include <tuple>
#include <map>
#include <glog/logging.h>

#include "anh/byte_buffer.h"
#include "swganh/messages/base_swg_message.h"

namespace swganh {
namespace messages {

typedef std::tuple<std::string, std::string, std::wstring> PropertyValue;
typedef std::tuple<std::string, std::string, std::wstring> PropertyHeader;
typedef std::pair<std::string, std::string> PropertyResult;

struct SuiCreatePageMessage : public swganh::messages::BaseSwgMessage<SuiCreatePageMessage>
{
	static uint16_t opcount() { return 0x02; }
	static uint32_t opcode() { return 0xD44B7259; }

	uint32_t id;
	std::string ui_script; 
	std::string handler;
	std::vector<std::string> property_containers;
	std::vector<PropertyValue> property_values;
	std::vector<PropertyHeader> property_headers;
	std::vector<PropertyResult> property_results;
	float max_distance;

	void AddPropertyContainer(std::string location)
	{
		property_containers.push_back(location);
	}

	void AddPropertyHeader(std::string object, std::string variable, std::wstring index)
	{
		property_headers.push_back(PropertyHeader(object, variable, index));
	}
	
	void AddPropertyResult(std::string object, std::string variable)
	{
		property_results.push_back(PropertyResult(object, variable));
	}

	void AddPropertyValue(std::string object, std::string variable, std::wstring value)
	{
		property_values.push_back(PropertyValue(object, variable, value));
	}

	void onSerialize(anh::ByteBuffer& buffer) const {
		buffer.write<uint32_t>(id);
		buffer.write<std::string>(ui_script);
		buffer.write<uint32_t>(2 + property_values.size() + property_headers.size());
	
		// Yes, this must be ran twice, we do not know why SOE
		// insisted the headers be defined twice, but that's the way
		// it is.
		for(int x = 0; x < 2; x++)
		{
			buffer.write<uint8_t>(5); // Define Header
			buffer.write<uint32_t>(0);
			buffer.write<uint32_t>(3 + (property_results.size() * 2));
			buffer.write<uint16_t>(0);
			buffer.write<uint16_t>(1);
			buffer.write<uint8_t>(9);
			buffer.write<std::string>(handler);
			std::for_each(property_results.begin(), property_results.end(), [&buffer](const PropertyResult& result_element) {
				buffer.write<std::string>(result_element.first);
				buffer.write<std::string>(result_element.second);
			});
		}

		std::for_each(property_headers.begin(), property_headers.end(), [&buffer](const PropertyHeader& element) {
			buffer.write<uint8_t>(4);
			buffer.write<uint32_t>(1);
			buffer.write<std::wstring>(std::get<2>(element));
			buffer.write<uint32_t>(2);
			buffer.write<std::string>(std::get<0>(element));
			buffer.write<std::string>(std::get<1>(element));
		});

		std::for_each(property_values.begin(), property_values.end(), [&buffer](const PropertyValue& element) {
			buffer.write<uint8_t>(3);
			buffer.write<uint32_t>(1);
			buffer.write<std::wstring>(std::get<2>(element));
			buffer.write<uint32_t>(2);
			buffer.write<std::string>(std::get<0>(element));
			buffer.write<std::string>(std::get<1>(element));
		});

		buffer.write<uint64_t>(0);
		buffer.write<float>(max_distance);
		buffer.write<uint64_t>(0);
	
	}

	void onDeserialize(anh::ByteBuffer buffer) {
	}
};

}} // namespace swganh::messages

#endif // SWGANH_MESSAGE_SUI_CREATE_PAGE_MESSAGE_H_