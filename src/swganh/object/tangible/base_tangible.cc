
#include "swganh/object/tangible/base_tangible.h"

#include "swganh/messages/deltas_message.h"
#include "swganh/object/tangible/tangible_message_builder.h"

using namespace std;
using namespace swganh::object;
using namespace swganh::object::tangible;
using namespace swganh::messages;
using namespace swganh::messages::containers;

BaseTangible::BaseTangible()
    : Object()
    , customization_("")
    , component_customization_list_(NetworkList<ComponentCustomization>())
    , options_bitmask_(0)
    , incap_timer_(0)
    , condition_damage_(0)
    , max_condition_(0)
    , is_static_(false)
    , defender_list_(swganh::messages::containers::NetworkSortedVector<Defender>(3))
{}

BaseTangible::BaseTangible(const std::string& customization, std::vector<uint32_t> component_customization, uint32_t bitmask_options,
        uint32_t incap_timer, uint32_t condition_damage, uint32_t max_condition, bool is_static, std::vector<uint64_t> defenders)
    : Object()
    , customization_(customization)
    , component_customization_list_(NetworkList<ComponentCustomization>())
    , options_bitmask_(bitmask_options)
    , incap_timer_(incap_timer)
    , condition_damage_(condition_damage)
    , max_condition_(max_condition)
    , is_static_(is_static)
    , defender_list_(swganh::messages::containers::NetworkSortedVector<Defender>(3))
{
    std::for_each(defenders.begin(), defenders.end(), [=](const uint64_t& def) {
        defender_list_.Add(Defender(def));
    });

    std::for_each(component_customization.begin(), component_customization.end(), [=](const uint32_t& crc) {
        component_customization_list_.Add(ComponentCustomization(crc));
    });
}

void BaseTangible::AddCustomization(const string& customization)
{
    boost::lock_guard<boost::recursive_mutex> lock(mutex_);
    customization_.append(customization);
    TangibleMessageBuilder::BuildCustomizationDelta(this);
}

std::string BaseTangible::GetCustomization(void)
{
    boost::lock_guard<boost::recursive_mutex> lock(mutex_);
    return customization_;
}

void BaseTangible::SetCustomization(const string& customization)
{
    boost::lock_guard<boost::recursive_mutex> lock(mutex_);
    customization_ = customization;
    TangibleMessageBuilder::BuildCustomizationDelta(this);
}
void BaseTangible::RemoveComponentCustomization(uint32_t customization)
{
    boost::lock_guard<boost::recursive_mutex> lock(mutex_);
    auto iter = std::find_if(component_customization_list_.Begin(), component_customization_list_.End(), [=](ComponentCustomization component) {
        return component.component_customization_crc = customization;
    });

    if(iter != component_customization_list_.End())
    {
        component_customization_list_.Remove(iter);
        TangibleMessageBuilder::BuildComponentCustomizationDelta(this);
    }
}
void BaseTangible::AddComponentCustomization(uint32_t customization)
{
    boost::lock_guard<boost::recursive_mutex> lock(mutex_);
    component_customization_list_.Add(ComponentCustomization(customization));
    TangibleMessageBuilder::BuildComponentCustomizationDelta(this);
}

NetworkList<ComponentCustomization> BaseTangible::GetComponentCustomization(void)
{
    boost::lock_guard<boost::recursive_mutex> lock(mutex_);
    return component_customization_list_;
}

void BaseTangible::ClearComponentCustomization()
{
    boost::lock_guard<boost::recursive_mutex> lock(mutex_);
    component_customization_list_.Clear();
    TangibleMessageBuilder::BuildComponentCustomizationDelta(this);
}

void BaseTangible::SetOptionsMask(uint32_t options_mask)
{
    boost::lock_guard<boost::recursive_mutex> lock(mutex_);
    options_bitmask_ = options_mask;
    TangibleMessageBuilder::BuildOptionsMaskDelta(this);    
}

void BaseTangible::ToggleOption(uint32_t option)
{
	boost::lock_guard<boost::recursive_mutex> lock(mutex_);
	options_bitmask_ ^= option;
	TangibleMessageBuilder::BuildOptionsMaskDelta(this);
}

uint32_t BaseTangible::GetOptionsMask(void)
{
    boost::lock_guard<boost::recursive_mutex> lock(mutex_);
    return options_bitmask_;
}

void BaseTangible::SetIncapTimer(uint32_t incap_timer)
{
    boost::lock_guard<boost::recursive_mutex> lock(mutex_);
    incap_timer_ = incap_timer;
    TangibleMessageBuilder::BuildIncapTimerDelta(this);
}

uint32_t BaseTangible::GetIncapTimer(void)
{
    boost::lock_guard<boost::recursive_mutex> lock(mutex_);
    return incap_timer_;
}

void BaseTangible::SetConditionDamage(uint32_t damage)
{
    boost::lock_guard<boost::recursive_mutex> lock(mutex_);
    condition_damage_ = damage;
    TangibleMessageBuilder::BuildConditionDamageDelta(this);
}

uint32_t BaseTangible::GetCondition(void)
{
    boost::lock_guard<boost::recursive_mutex> lock(mutex_);
    return condition_damage_;
}

void BaseTangible::SetMaxCondition(uint32_t max_condition)
{
    boost::lock_guard<boost::recursive_mutex> lock(mutex_);
    max_condition_ = max_condition;
    TangibleMessageBuilder::BuildMaxConditionDelta(this);
}

uint32_t BaseTangible::GetMaxCondition(void)
{
    boost::lock_guard<boost::recursive_mutex> lock(mutex_);
    return max_condition_;
}

void BaseTangible::SetStatic(bool is_static)
{
    boost::lock_guard<boost::recursive_mutex> lock(mutex_);
    is_static_ = is_static;
    TangibleMessageBuilder::BuildStaticDelta(this);
}

bool BaseTangible::IsStatic(void)
{
    boost::lock_guard<boost::recursive_mutex> lock(mutex_);
    return is_static_;
}

bool BaseTangible::IsDefending(uint64_t defender)
{
    boost::lock_guard<boost::recursive_mutex> lock(mutex_);
    auto iter = std::find_if(defender_list_.Begin(), defender_list_.End(), [=](const Defender& x)->bool {
        return (x.object_id == defender);
    });

    if(iter != defender_list_.End())
        return true;
    else
        return false;
}
void BaseTangible::AddDefender(uint64_t defender)
{
    boost::lock_guard<boost::recursive_mutex> lock(mutex_);
    defender_list_.Add(Defender(defender));
    TangibleMessageBuilder::BuildDefendersDelta(this);
}
void BaseTangible::RemoveDefender(uint64_t defender)
{
    boost::lock_guard<boost::recursive_mutex> lock(mutex_);
    auto iter = std::find_if(defender_list_.Begin(), defender_list_.End(), [=](const Defender& x)->bool {
        return (x.object_id == defender);
    });

    if(iter != defender_list_.End())
    {
        defender_list_.Remove(iter);
        TangibleMessageBuilder::BuildDefendersDelta(this);
    }
}
void BaseTangible::ResetDefenders(std::vector<uint64_t> defenders)
{
    boost::lock_guard<boost::recursive_mutex> lock(mutex_);
    defender_list_.Clear();
    std::for_each(defenders.begin(), defenders.end(), [=](const uint64_t& x) {
        defender_list_.Insert(Defender(x));
    });
    defender_list_.Reinstall();
    TangibleMessageBuilder::BuildDefendersDelta(this);
}

NetworkSortedVector<Defender> BaseTangible::GetDefenders()
{
    boost::lock_guard<boost::recursive_mutex> lock(mutex_);
    return defender_list_;
}

void BaseTangible::ClearDefenders()
{
    boost::lock_guard<boost::recursive_mutex> lock(mutex_);
    defender_list_.Clear();
    TangibleMessageBuilder::BuildDefendersDelta(this);
}

boost::optional<BaselinesMessage> BaseTangible::GetBaseline3()
{
    return move(TangibleMessageBuilder::BuildBaseline3(this));
}
boost::optional<BaselinesMessage> BaseTangible::GetBaseline6()
{
    return move(TangibleMessageBuilder::BuildBaseline6(this));
}
boost::optional<BaselinesMessage> BaseTangible::GetBaseline7()
{
    return move(TangibleMessageBuilder::BuildBaseline7(this));
}