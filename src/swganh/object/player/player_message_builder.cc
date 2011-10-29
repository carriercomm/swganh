#include "player_message_builder.h"

#include <algorithm>

#include "anh/crc.h"
#include "swganh/messages/deltas_message.h"
#include "swganh/messages/baselines_message.h"
#include "swganh/object/waypoint/waypoint.h"

using namespace std;
using namespace swganh::object;
using namespace player;
using namespace waypoint;
using namespace swganh::messages;

// deltas
void PlayerMessageBuilder::BuildStatusBitmaskDelta(Player* object)
{
    if (object->HasObservers())
    {
        DeltasMessage message = object->CreateDeltasMessage(Object::VIEW_3, 5);

        message.data.write<uint32_t>(object->status_flags_.size());

        for_each(begin(object->status_flags_),
            end(object->status_flags_),
            [&message] (vector<FlagBitmask>::value_type& flag)
        {
            flag.Serialize(message);
        });
        
        object->AddDeltasUpdate(move(message));
    }
}
void PlayerMessageBuilder::BuildProfileBitmaskDelta(Player* object)
{
    if (object->HasObservers())
    {
        DeltasMessage message = object->CreateDeltasMessage(Object::VIEW_3, 6);
        
        message.data.write<uint32_t>(object->profile_flags_.size());

        for_each(begin(object->profile_flags_),
            end(object->profile_flags_),
            [&message] (vector<FlagBitmask>::value_type& flag)
        {
            flag.Serialize(message);
        });

        object->AddDeltasUpdate(move(message));
    }
}
void PlayerMessageBuilder::BuildProfessionTagDelta(Player* object)
{
    if (object->HasObservers())
    {
        DeltasMessage message = object->CreateDeltasMessage(Object::VIEW_3, 7);
        message.data.write(object->GetProfessionTag());

        object->AddDeltasUpdate(move(message));
    }
}
void PlayerMessageBuilder::BuildBornDateDelta(Player* object)
{
     if (object->HasObservers())
    {
        DeltasMessage message = object->CreateDeltasMessage(Object::VIEW_3, 8);
        message.data.write(object->GetBornDate());

        object->AddDeltasUpdate(move(message));
    }
}
void PlayerMessageBuilder::BuildPlayTimeDelta(Player* object)
{
     if (object->HasObservers())
    {
        DeltasMessage message = object->CreateDeltasMessage(Object::VIEW_3, 9);
        message.data.write(object->GetTotalPlayTime());

        object->AddDeltasUpdate(move(message));
    }
}
void PlayerMessageBuilder::BuildRegionIdDelta(Player* object)
{
    if (object->HasObservers())
    {
        DeltasMessage message = object->CreateDeltasMessage(Object::VIEW_6, 0);
        message.data.write(object->GetRegionId());

        object->AddDeltasUpdate(move(message));
    }
}
void PlayerMessageBuilder::BuildAdminTagDelta(Player* object)
{
    if (object->HasObservers())
    {
        DeltasMessage message = object->CreateDeltasMessage(Object::VIEW_6, 1);
        message.data.write<uint8_t>(object->GetAdminTag());
        object->AddDeltasUpdate(std::move(message));
    }
}
void PlayerMessageBuilder::BuildXpDelta(Player* object)
{
    if (object->HasObservers())
    {
        DeltasMessage message = object->CreateDeltasMessage(Object::VIEW_7, 0);
        object->experience_.Serialize(message);
        object->AddDeltasUpdate(move(message));
    }
    else
        object->experience_.ClearDeltas();
}
void PlayerMessageBuilder::BuildWaypointDelta(Player* object)
{
    if (object->HasObservers())
    {
        DeltasMessage message = object->CreateDeltasMessage(Object::VIEW_7, 1);
        object->waypoints_.Serialize(message);
        object->AddDeltasUpdate(move(message));
    }
}
void PlayerMessageBuilder::BuildCurrentForcePowerDelta(Player* object)
{
    if (object->HasObservers())
    {
        DeltasMessage message = object->CreateDeltasMessage(Object::VIEW_8, 2);
        message.data.write(object->GetCurrentForcePower());

        object->AddDeltasUpdate(move(message));
    }
}
void PlayerMessageBuilder::BuildMaxForcePowerDelta(Player* object)
{
    if (object->HasObservers())
    {
        DeltasMessage message = object->CreateDeltasMessage(Object::VIEW_8, 3);
        message.data.write(object->GetMaxForcePower());

        object->AddDeltasUpdate(move(message));
    }
}
void PlayerMessageBuilder::BuildForceSensitiveQuestDelta(Player* object)
{
    if (object->HasObservers())
    {
        DeltasMessage message = object->CreateDeltasMessage(Object::VIEW_8, 4);
        message.data.write(object->GetCurrentForceSensitiveQuests());

        object->AddDeltasUpdate(move(message));
    }
}
void PlayerMessageBuilder::BuildCompletedForceSensitiveQuestDelta(Player* object)
{
    if (object->HasObservers())
    {
        DeltasMessage message = object->CreateDeltasMessage(Object::VIEW_8, 5);
        message.data.write(object->GetCompletedForceSensitiveQuests());

        object->AddDeltasUpdate(move(message));
    }
}
void PlayerMessageBuilder::BuildQuestJournalDelta(Player* object)
{
    if (object->HasObservers())
    {
        DeltasMessage message = object->CreateDeltasMessage(Object::VIEW_8, 6);
        object->quest_journal_.Serialize(message);
        object->AddDeltasUpdate(move(message));
    }
    else
        object->quest_journal_.ClearDeltas();
}
void PlayerMessageBuilder::BuildAbilityDelta(Player* object)
{
    if (object->HasObservers())
    {
        DeltasMessage message = object->CreateDeltasMessage(Object::VIEW_9, 0);
        object->abilities_.Serialize(message);
        object->AddDeltasUpdate(move(message));
    }
    else
        object->abilities_.ClearDeltas();
}

void PlayerMessageBuilder::BuildExperimentationFlagDelta(Player* object)
{
    if (object->HasObservers())
    {
        DeltasMessage message = object->CreateDeltasMessage(Object::VIEW_9, 1);
        message.data.write(object->GetExperimentationFlag());            

        object->AddDeltasUpdate(move(message));
    }
}
void PlayerMessageBuilder::BuildCraftingStageDelta(Player* object)
{
    if (object->HasObservers())
    {
        DeltasMessage message = object->CreateDeltasMessage(Object::VIEW_9, 2);
        message.data.write(object->GetCraftingStage());            

        object->AddDeltasUpdate(move(message));
    }
}
void PlayerMessageBuilder::BuildNearestCraftingStationDelta(Player* object)
{
    if (object->HasObservers())
    {
        DeltasMessage message = object->CreateDeltasMessage(Object::VIEW_9, 3);
        message.data.write(object->GetNearestCraftingStation());            

        object->AddDeltasUpdate(move(message));
    }
}
void PlayerMessageBuilder::BuildDraftSchematicDelta(Player* object)
{
    if (object->HasObservers())
    {
        DeltasMessage message = object->CreateDeltasMessage(Object::VIEW_9, 4);
        object->draft_schematics_.Serialize(message);
        object->AddDeltasUpdate(move(message));
    }
    else
        object->draft_schematics_.ClearDeltas();
}

void PlayerMessageBuilder::BuildExperimentationPointsDelta(Player* object)
{
    if (object->HasObservers())
    {
        DeltasMessage message = object->CreateDeltasMessage(Object::VIEW_9, 5);
        message.data.write(object->GetExperimentationPoints());            

        object->AddDeltasUpdate(move(message));
    }
}
void PlayerMessageBuilder::BuildAccomplishmentCounterDelta(Player* object)
{
    if (object->HasObservers())
    {
        DeltasMessage message = object->CreateDeltasMessage(Object::VIEW_9, 6);
        message.data.write(object->GetAccomplishmentCounter());            

        object->AddDeltasUpdate(move(message));
    }
}
void PlayerMessageBuilder::BuildFriendsDelta(Player* object)
{
    if (object->HasObservers())
    {
        DeltasMessage message = object->CreateDeltasMessage(Object::VIEW_9, 7);
        object->friends_.Serialize(message);
        object->AddDeltasUpdate(move(message));
    }
    else
        object->friends_.ClearDeltas();
}
void PlayerMessageBuilder::BuildIgnoredDelta(Player* object)
{
    if (object->HasObservers())
    {
        DeltasMessage message = object->CreateDeltasMessage(Object::VIEW_9, 8);
        object->ignored_players_.Serialize(message);
        object->AddDeltasUpdate(move(message));
    }
    else
        object->ignored_players_.ClearDeltas();
}
void PlayerMessageBuilder::BuildLanguageDelta(Player* object)
{
    if (object->HasObservers())
    {
        DeltasMessage message = object->CreateDeltasMessage(Object::VIEW_9, 9);
        message.data.write(object->GetLanguage());            

        object->AddDeltasUpdate(move(message));
    }
}
void PlayerMessageBuilder::BuildCurrentStomachDelta(Player* object)
{
    if (object->HasObservers())
    {
        DeltasMessage message = object->CreateDeltasMessage(Object::VIEW_9, 10);
        message.data.write(object->GetCurrentStomach());            

        object->AddDeltasUpdate(move(message));
    }
}
void PlayerMessageBuilder::BuildMaxStomachDelta(Player* object)
{
    if (object->HasObservers())
    {
        DeltasMessage message = object->CreateDeltasMessage(Object::VIEW_9, 11);
        message.data.write(object->GetMaxStomach());            

        object->AddDeltasUpdate(move(message));
    }
}
void PlayerMessageBuilder::BuildCurrentDrinkDelta(Player* object)
{
    if (object->HasObservers())
    {
        DeltasMessage message = object->CreateDeltasMessage(Object::VIEW_9, 12);
        message.data.write(object->GetCurrentDrink());            

        object->AddDeltasUpdate(move(message));
    }
}
void PlayerMessageBuilder::BuildMaxDrinkDelta(Player* object)
{
    if (object->HasObservers())
    {
        DeltasMessage message = object->CreateDeltasMessage(Object::VIEW_9, 13);
        message.data.write(object->GetMaxDrink());            

        object->AddDeltasUpdate(move(message));
    }
}
void PlayerMessageBuilder::BuildJediStateDelta(Player* object)
{
    if (object->HasObservers())
    {
        DeltasMessage message = object->CreateDeltasMessage(Object::VIEW_9, 17);
        message.data.write(object->GetExperimentationPoints());            

        object->AddDeltasUpdate(move(message));
    }
}
// baselines
boost::optional<swganh::messages::BaselinesMessage> PlayerMessageBuilder::BuildBaseline3(Player* object)
{
    auto message = object->CreateBaselinesMessage(Object::VIEW_3, 10);
    message.data.append(object->Object::GetBaseline3().get().data);
    message.data.write<uint32_t>(0);                                    // Not Used
    
    message.data.write<uint32_t>(object->status_flags_.size());

    for_each(begin(object->status_flags_),
        end(object->status_flags_),
        [&message] (vector<FlagBitmask>::value_type& flag)
    {
        flag.Serialize(message);
    });

    message.data.write<uint32_t>(object->profile_flags_.size());

    for_each(begin(object->profile_flags_),
        end(object->profile_flags_),
        [&message] (vector<FlagBitmask>::value_type& flag)
    {
        flag.Serialize(message);
    });

    message.data.write<std::string>(object->GetProfessionTag());        // Profession Tag
    message.data.write<uint32_t>(object->GetBornDate());                // Born Date
    message.data.write<uint32_t>(object->GetTotalPlayTime());           // Total Play Time
    return boost::optional<BaselinesMessage>(move(message));
}

boost::optional<swganh::messages::BaselinesMessage> PlayerMessageBuilder::BuildBaseline6(Player* object)
{
    auto message = object->CreateBaselinesMessage(Object::VIEW_6, 2);
    message.data.write<uint32_t>(object->GetRegionId());    // Region Id
    message.data.write<uint8_t>(object->GetAdminTag());     // Admin Tag
    return boost::optional<BaselinesMessage>(move(message));
}

boost::optional<swganh::messages::BaselinesMessage> PlayerMessageBuilder::BuildBaseline8(Player* object)
{
    auto message = object->CreateBaselinesMessage(Object::VIEW_8, 7);
    object->experience_.Serialize(message);
    object->waypoints_.Serialize(message);
    
    message.data.write<uint32_t>(object->GetCurrentForcePower());
    message.data.write<uint32_t>(object->GetMaxForcePower());
    
    message.data.write<uint32_t>(0); // Force Sensetive Quest List Soze
    message.data.write<uint32_t>(0); // Force Sensetive Quest List Counter
    
    message.data.write<uint32_t>(0); // Completed Force Sensetive Quest List Size
    message.data.write<uint32_t>(0); // Completed Force Sensetive Quest List Counter
    
    object->quest_journal_.Serialize(message);
    
    return boost::optional<BaselinesMessage>(std::move(message));
}

boost::optional<swganh::messages::BaselinesMessage> PlayerMessageBuilder::BuildBaseline9(Player* object)
{
    auto message = object->CreateBaselinesMessage(Object::VIEW_9, 17);
    
    object->abilities_.Serialize(message);
    message.data.write<uint32_t>(object->GetExperimentationFlag());
    message.data.write<uint32_t>(object->GetCraftingStage());
    message.data.write<uint64_t>(object->GetNearestCraftingStation());
    
    object->draft_schematics_.Serialize(message);
    
    
    message.data.write<uint32_t>(object->GetExperimentationPoints());
    message.data.write<uint32_t>(object->GetAccomplishmentCounter());
    
    object->friends_.Serialize(message);
    
    object->ignored_players_.Serialize(message);
    
    message.data.write<uint32_t>(object->GetLanguage());
    message.data.write<uint32_t>(object->GetCurrentStomach());
    message.data.write<uint32_t>(object->GetMaxStomach());
    message.data.write<uint32_t>(object->GetCurrentDrink());
    message.data.write<uint32_t>(object->GetMaxDrink());
    message.data.write<uint32_t>(0); // Unused
    message.data.write<uint32_t>(0); // Unused
    message.data.write<uint32_t>(0); // Unused
    message.data.write<uint32_t>(0); // Unused
    message.data.write<uint32_t>(object->GetJediState()); // Jedi State
    
    return boost::optional<BaselinesMessage>(std::move(message));
}