// This file is part of SWGANH which is released under the MIT license.
// See file LICENSE or go to http://swganh.com/LICENSE
#pragma once

#include "swganh_core/object/object_factory.h"

namespace swganh {
namespace object {


    class ShipFactory : public swganh::object::ObjectFactory
	{
    public:
        virtual uint32_t PersistObject(const std::shared_ptr<swganh::object::Object>& object, bool persist_inherited = false);
		virtual void PersistChangedObjects(){}
        void DeleteObjectFromStorage(const std::shared_ptr<swganh::object::Object>& object);

        std::shared_ptr<swganh::object::Object> CreateObjectFromStorage(uint64_t object_id);

        std::shared_ptr<swganh::object::Object> CreateObject();
    };

}}  // namespace swganh::object
