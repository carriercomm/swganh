// This file is part of SWGANH which is released under the MIT license.
// See file LICENSE or go to http://swganh.com/LICENSE

#include "installation.h"

using namespace std;
using namespace swganh::object;
using namespace swganh::messages::containers;

Installation::Installation()
	: Tangible()
	, resource_pool_ids_(10)
	, resource_names_(10)
	, resource_types_(10)
	, hopper_(10)
{
}

uint32_t Installation::GetType() const
{ 
    return Installation::type; 
}

bool Installation::IsActive() const
{
    return is_active_;
}

void Installation::Activate()
{
    if (!IsActive())
    {
        ToggleActive();
    }
}

void Installation::Deactivate()
{
    if (IsActive())
    {
        ToggleActive();
    }
}

void Installation::ToggleActive()
{
    is_active_ = !is_active_;
	DISPATCH(Installation, Active);
}

float Installation::GetPowerReserve() const
{
	boost::lock_guard<boost::mutex> lock(object_mutex_);
    return power_reserve_;
}

void Installation::SetPowerReserve(float power_reserve)
{
	{
		boost::lock_guard<boost::mutex> lock(object_mutex_);
		power_reserve_ = power_reserve;
	}
	DISPATCH(Installation, PowerReserve);
}

float Installation::GetPowerCost() const
{
	boost::lock_guard<boost::mutex> lock(object_mutex_);
    return power_cost_;
}

void Installation::SetPowerCost(float power_cost)
{
	{
		boost::lock_guard<boost::mutex> lock(object_mutex_);
		power_cost_ = power_cost;
	}
	DISPATCH(Installation, PowerCost);
}

std::vector<Installation::Resource> Installation::GetAvailableResources()
{
	boost::lock_guard<boost::mutex> lock(object_mutex_);

	std::vector<Installation::Resource> available_resources;
	uint16_t size = resource_pool_ids_.Size();
	for(uint16_t i = 0; i < size; ++i)
	{
		Installation::Resource resource;
		resource.global_id = resource_pool_ids_[i].id;
		resource.resource_name = resource_names_[i].name;
		resource.resource_type = resource_types_[i].name;
		available_resources.push_back(resource);
	}

    return available_resources;
}

void Installation::AddAvailableResource(uint64_t global_id, std::string name, std::string type)
{
	bool send_update = true;

	{
		boost::lock_guard<boost::mutex> lock(object_mutex_);
		uint16_t size = resource_pool_ids_.Size();
		for(uint16_t i = 0; i < size; ++i)
		{
			if(resource_pool_ids_[i] == global_id)
			{
				//We already have it
				send_update = false;
				return;
			}
		}
	
		resource_pool_ids_.Add(global_id);
		resource_names_.Add(name);
		resource_types_.Add(type);
	}

	if(send_update)
	{
		DISPATCH(Installation, AvailableResource);
	}
}

void Installation::RemoveAvailableResourceById(uint64_t global_id)
{
	bool send_update = false;

	{
		boost::lock_guard<boost::mutex> lock(object_mutex_);
		uint16_t size = resource_pool_ids_.Size();
		uint16_t index;
		for(index = 0; index < size; ++index)
		{
			if(resource_pool_ids_[index] == global_id)
			{
				resource_pool_ids_.Remove(index);
				resource_names_.Remove(index);
				resource_types_.Remove(index);
				send_update = true;
				break;
			}
		}
	}

	if(send_update)
	{
		DISPATCH(Installation, AvailableResource);
	}
}

void Installation::UpdateResource(uint64_t global_id, std::string name, std::string type)
{
	bool send_update = false;

	{
		boost::lock_guard<boost::mutex> lock(object_mutex_);
		uint16_t size = resource_pool_ids_.Size();
		uint16_t index;
		for(index = 0; index < size; ++index)
		{
			if(resource_pool_ids_[index] == global_id)
			{
				resource_pool_ids_.Update(index, ResourceId(global_id));
				resource_names_.Update(index, ResourceString(name));
				resource_types_.Update(index, ResourceString(type));
				send_update = true;
				break;
			}
		}
	}

	if(send_update)
	{
		DISPATCH(Installation, AvailableResource);
	}
}

void Installation::ResetAvailableResources(std::vector<Installation::Resource> available_resource_pool)
{
	{
		boost::lock_guard<boost::mutex> lock(object_mutex_);
		//Clean out the lists
		resource_pool_ids_.Clear();
		resource_names_.Clear();
		resource_types_.Clear();
    
		//Put the new values in
		for(auto& resource : available_resource_pool)
		{
			resource_pool_ids_.Add(resource.global_id);
			resource_names_.Add(resource.resource_name);
			resource_types_.Add(resource.resource_type);
		}
	
		//Clear Deltas and Reinstall
		resource_pool_ids_.ClearDeltas();
		resource_names_.ClearDeltas();
		resource_types_.ClearDeltas();

		resource_pool_ids_.Reinstall();
		resource_names_.Reinstall();
		resource_types_.Reinstall();
	}
	DISPATCH(Installation, AvailableResource);
}

void Installation::ClearAllAvailableResources()
{
	{
		boost::lock_guard<boost::mutex> lock(object_mutex_);
		resource_pool_ids_.Clear();
		resource_names_.Clear();
		resource_types_.Clear();
	}
	DISPATCH(Installation, AvailableResource);
}

void Installation::SetDisplayedMaxExtractionRate(uint32_t extraction_rate)
{
	displayed_max_extraction_rate_ = extraction_rate;
	DISPATCH(Installation, DisplayedMaxExtraction);
}
    
uint32_t Installation::GetDisplayedMaxExtractionRate() const
{
	return displayed_max_extraction_rate_;
}

float Installation::GetMaxExtractionRate() const
{
	boost::lock_guard<boost::mutex> lock(object_mutex_);
    return max_extraction_rate_;
}

void Installation::SetMaxExtractionRate(float extraction_rate)
{
	{
		boost::lock_guard<boost::mutex> lock(object_mutex_);
		max_extraction_rate_ = extraction_rate;
	}
	DISPATCH(Installation, MaxExtraction);
}

float Installation::GetCurrentExtractionRate() const
{
	boost::lock_guard<boost::mutex> lock(object_mutex_);
    return current_extraction_rate_;
}

void Installation::SetCurrentExtractionRate(float extraction_rate)
{
	{
		boost::lock_guard<boost::mutex> lock(object_mutex_);
		current_extraction_rate_ = extraction_rate;
	}
	DISPATCH(Installation, CurrentExtraction);
}

float Installation::GetCurrentHopperSize() const
{
	boost::lock_guard<boost::mutex> lock(object_mutex_);
    return current_hopper_size_;
}

void Installation::SetCurrentHopperSize(float hopper_size)
{
	{
		boost::lock_guard<boost::mutex> lock(object_mutex_);
		current_hopper_size_ = hopper_size;
	}
	DISPATCH(Installation, CurrentHopperSize);
}

uint32_t Installation::GetMaxHopperSize() const
{
    return max_hopper_size_;
}

void Installation::SetMaxHopperSize(uint32_t hopper_size)
{
	max_hopper_size_ = hopper_size;
	DISPATCH(Installation, MaxHopperSize);
}

bool Installation::IsUpdating() const
{
    return is_updating_;
}

void Installation::StartUpdating()
{
    if (!IsUpdating())
    {
        ToggleUpdating();
    }
}

void Installation::StopUpdating()
{
    if (IsUpdating())
    {
        ToggleUpdating();
    }
}

void Installation::ToggleUpdating()
{
    is_updating_ = !is_updating_;
	DISPATCH(Installation, IsUpdating);
}

NetworkSortedVector<Installation::HopperItem>& Installation::GetHopperContents()
{
	boost::lock_guard<boost::mutex> lock(object_mutex_);
    return hopper_;
}

void Installation::AddToHopper(uint64_t global_id, float quantity)
{
	{
		boost::lock_guard<boost::mutex> lock(object_mutex_);
		HopperItem item;
		item.global_id = global_id;
		item.quantity = quantity;
		hopper_.Add(move(item));
	}
	DISPATCH(Installation, Hopper);
}

void Installation::RemoveHopperItem(uint64_t global_id)
{
	bool send_update = false;
	{
		boost::lock_guard<boost::mutex> lock(object_mutex_);
		for(uint16_t i=0; i < hopper_.Size(); ++i)
		{
			if(hopper_[i].global_id == global_id)
			{
				hopper_.Remove(i);
				send_update = true;
				break;
			}
		}
	}

	if(send_update)
	{
		DISPATCH(Installation, Hopper);
	}
}

void Installation::UpdateHopperItem(uint64_t global_id, float quantity)
{
    bool send_update = false;
	{
		boost::lock_guard<boost::mutex> lock(object_mutex_);
		for(uint16_t i=0; i < hopper_.Size(); ++i)
		{
			if(hopper_[i].global_id == global_id)
			{
				HopperItem new_item;
				new_item.global_id = global_id;
				new_item.quantity = quantity;
				hopper_.Update(i, new_item);

				send_update = true;
				break;
			}
		}
	}

	if(send_update)
	{
		DISPATCH(Installation, Hopper);
	}
}

void Installation::ResetContents(std::vector<Installation::HopperItem> hopper)
{
	{
		boost::lock_guard<boost::mutex> lock(object_mutex_);
		hopper_.Clear();

		for(auto& item : hopper)
		{
			hopper_.Add(item);
		}

		hopper_.ClearDeltas();
		hopper_.Reinstall();
	}
	DISPATCH(Installation, Hopper);
}

void Installation::ClearAllHopperContents()
{
	{
		boost::lock_guard<boost::mutex> lock(object_mutex_);
		hopper_.Clear();
	}
	DISPATCH(Installation, Hopper);
}

uint8_t Installation::GetConditionPercentage() const
{
    return condition_percent_;
}

void Installation::SetConditionPercentage(uint8_t condition)
{
	condition = (condition > 100) ? 100 : condition;
	condition_percent_ = condition;
	DISPATCH(Installation, ConditionPercent);
}

NetworkSortedVector<ResourceId>& Installation::GetResourceIds_()
{
	boost::lock_guard<boost::mutex> lock(object_mutex_);
	return resource_pool_ids_;
}

NetworkSortedVector<ResourceString>& Installation::GetResourceNames_()
{
	boost::lock_guard<boost::mutex> lock(object_mutex_);
	return resource_names_;
}

NetworkSortedVector<ResourceString>& Installation::GetResourceTypes_()
{
	boost::lock_guard<boost::mutex> lock(object_mutex_);
	return resource_types_;
}

uint64_t Installation::GetSelectedResourceId()
{
	return selected_resource_;
}

void Installation::SetSelectedResourceId(uint64_t new_id)
{
	selected_resource_ = new_id;
	DISPATCH(Installation, SelectedResource);
}

std::shared_ptr<Object> Installation::Clone()
{
	boost::lock_guard<boost::mutex> lock(object_mutex_);
	auto other = make_shared<Installation>();
	Clone(other);
	return other;
}

void Installation::Clone(std::shared_ptr<Installation> other)
{
	other->is_active_.store(is_active_);
	other->power_reserve_ = power_reserve_;
	other->power_cost_ = power_cost_;
	other->resource_pool_ids_ = resource_pool_ids_;
	other->resource_names_ = resource_names_;
	other->resource_types_ = resource_types_;
	other->selected_resource_.store(selected_resource_);
	other->displayed_max_extraction_rate_.store(displayed_max_extraction_rate_);
	other->max_extraction_rate_ = max_extraction_rate_;
	other->current_extraction_rate_ = current_extraction_rate_;
	other->current_hopper_size_ = current_hopper_size_;
	other->max_hopper_size_.store(max_hopper_size_);
	other->is_updating_.store(is_updating_);
	other->hopper_ = hopper_;
	other->condition_percent_.store(condition_percent_);
}