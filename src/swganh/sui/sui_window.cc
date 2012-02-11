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

#include "sui_window.h"

#include <glog/logging.h>

#include "anh/crc.h"

namespace swganh {
namespace sui {

SuiWindow::SuiWindow(void)
{
}

SuiWindow::~SuiWindow(void)
{
}

void SuiWindow::AddReturnElement(std::string object, std::string variable)
{
	return_elements_.push_back(ReturnElement(object, variable));
}

void SuiWindow::SetBodyElement(std::string object, std::string variable, std::wstring value)
{
	elements_.push_back(BodyElement(object, variable, value));
}

void SuiWindow::onSerialize(anh::ByteBuffer& message)
{
	message.write<uint16_t>(2); // Update Type
	message.write<uint32_t>(anh::memcrc("SuiCreatePageMessage"));
	message.write<uint32_t>(id_);
	message.write<std::string>(ui_script_);
	message.write<uint32_t>(2 + elements_.size()); // Number of Header and Body elements.

	// Yes, this must be ran twice, we do not know why SOE
	// insisted the headers be defined twice, but that's the way
	// it is.
	for(int x = 0; x < 2; x++)
	{
		message.write<uint8_t>(5);
		message.write<uint32_t>(0);
		message.write<uint32_t>(7);
		message.write<uint16_t>(0);
		message.write<uint16_t>(1);
		message.write<uint8_t>(9);
		message.write<std::string>("");
		std::for_each(return_elements_.begin(), return_elements_.end(), [&message](ReturnElement& element){
			message.write<std::string>(element.first);
			message.write<std::string>(element.second);
		});
	}

	std::for_each(elements_.begin(), elements_.end(), [&message](BodyElement element) {
		message.write<uint8_t>(3);
		message.write<uint32_t>(1);
		message.write<std::wstring>(std::get<2>(element));
		message.write<uint32_t>(2);
		message.write<std::string>(std::get<0>(element));
		message.write<std::string>(std::get<1>(element));
	});

	message.write<uint64_t>(0);
	message.write<uint64_t>(0);
	message.write<uint32_t>(0);
}

}} // swganh::sui