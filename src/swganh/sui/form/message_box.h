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

#ifndef SWGANH_SUI_FORM_MESSAGE_BOX_H_
#define SWGANH_SUI_FORM_MESSAGE_BOX_H_

#include "swganh/sui/sui_window.h"

class MessageBox : public swganh::sui::SuiWindow
{
public:
	MessageBox();
	~MessageBox();
};

#endif // SWGANH_SUI_FORM_MESSAGE_BOX_H_