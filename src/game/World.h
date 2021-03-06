/*
 * This file is part of the CMaNGOS Project. See AUTHORS file for Copyright information
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

/// \addtogroup world The World
/// @{
/// \file

#ifndef __WORLD_H
#define __WORLD_H

#include "Common.h"
#include "Timer.h"
#include "Policies/Singleton.h"
#include "SharedDefines.h"

#include <map>
#include <set>
#include <list>

class Object;
class ObjectGuid;
class WorldPacket;
class WorldSession;
class Player;
class SqlResultQueue;
class QueryResult;
class WorldSocket;

// ServerMessages.dbc
enum ServerMessageType
{
    SERVER_MSG_SHUTDOWN_TIME          = 1,
    SERVER_MSG_RESTART_TIME           = 2,
    SERVER_MSG_CUSTOM                 = 3,
    SERVER_MSG_SHUTDOWN_CANCELLED     = 4,
    SERVER_MSG_RESTART_CANCELLED      = 5,
};

enum ShutdownMask
{
    SHUTDOWN_MASK_RESTART = 1,
    SHUTDOWN_MASK_IDLE    = 2,
};

enum ShutdownExitCode
{
    SHUTDOWN_EXIT_CODE = 0,
    ERROR_EXIT_CODE    = 1,
    RESTART_EXIT_CODE  = 2,
};

/// Timers for different object refresh rates
enum WorldTimers
{
    WUPDATE_AUCTIONS    = 0,
    WUPDATE_UPTIME      = 1,
    WUPDATE_CORPSES     = 2,
    WUPDATE_EVENTS      = 3,
    WUPDATE_DELETECHARS = 4,
    WUPDATE_AHBOT       = 5,
	WUPDATE_AUTOBROADCAST = 6,
    WUPDATE_COUNT       = 7
};

/// Configuration elements
enum eConfigUInt32Values
{
    CONFIG_UINT32_COMPRESSION = 0,
    CONFIG_UINT32_INTERVAL_SAVE,
    CONFIG_UINT32_INTERVAL_GRIDCLEAN,
    CONFIG_UINT32_INTERVAL_MAPUPDATE,
    CONFIG_UINT32_INTERVAL_CHANGEWEATHER,
    CONFIG_UINT32_PORT_WORLD,
    CONFIG_UINT32_GAME_TYPE,
    CONFIG_UINT32_REALM_ZONE,
    CONFIG_UINT32_STRICT_PLAYER_NAMES,
    CONFIG_UINT32_STRICT_CHARTER_NAMES,
    CONFIG_UINT32_STRICT_PET_NAMES,
    CONFIG_UINT32_MIN_PLAYER_NAME,
    CONFIG_UINT32_MIN_CHARTER_NAME,
    CONFIG_UINT32_MIN_PET_NAME,
    CONFIG_UINT32_CHARACTERS_CREATING_DISABLED,
    CONFIG_UINT32_CHARACTERS_PER_ACCOUNT,
    CONFIG_UINT32_CHARACTERS_PER_REALM,
    CONFIG_UINT32_SKIP_CINEMATICS,
    CONFIG_UINT32_MAX_PLAYER_LEVEL,
    CONFIG_UINT32_START_PLAYER_LEVEL,
    CONFIG_UINT32_START_PLAYER_MONEY,
    CONFIG_UINT32_MAX_HONOR_POINTS,
    CONFIG_UINT32_START_HONOR_POINTS,
    CONFIG_UINT32_MIN_HONOR_KILLS,
    CONFIG_UINT32_INSTANCE_RESET_TIME_HOUR,
    CONFIG_UINT32_INSTANCE_UNLOAD_DELAY,
    CONFIG_UINT32_MAX_SPELL_CASTS_IN_CHAIN,
    CONFIG_UINT32_RABBIT_DAY,
    CONFIG_UINT32_MAX_PRIMARY_TRADE_SKILL,
    CONFIG_UINT32_TRADE_SKILL_GMIGNORE_MAX_PRIMARY_COUNT,
    CONFIG_UINT32_TRADE_SKILL_GMIGNORE_LEVEL,
    CONFIG_UINT32_TRADE_SKILL_GMIGNORE_SKILL,
    CONFIG_UINT32_MIN_PETITION_SIGNS,
    CONFIG_UINT32_GM_LOGIN_STATE,
    CONFIG_UINT32_GM_VISIBLE_STATE,
    CONFIG_UINT32_GM_ACCEPT_TICKETS,
    CONFIG_UINT32_GM_CHAT,
    CONFIG_UINT32_GM_WISPERING_TO,
    CONFIG_UINT32_GM_LEVEL_IN_GM_LIST,
    CONFIG_UINT32_GM_LEVEL_IN_WHO_LIST,
    CONFIG_UINT32_START_GM_LEVEL,
    CONFIG_UINT32_GM_INVISIBLE_AURA,
    CONFIG_UINT32_GROUP_VISIBILITY,
    CONFIG_UINT32_MAIL_DELIVERY_DELAY,
    CONFIG_UINT32_MASS_MAILER_SEND_PER_TICK,
    CONFIG_UINT32_UPTIME_UPDATE,
    CONFIG_UINT32_AUCTION_DEPOSIT_MIN,
    CONFIG_UINT32_SKILL_CHANCE_ORANGE,
    CONFIG_UINT32_SKILL_CHANCE_YELLOW,
    CONFIG_UINT32_SKILL_CHANCE_GREEN,
    CONFIG_UINT32_SKILL_CHANCE_GREY,
    CONFIG_UINT32_SKILL_CHANCE_MINING_STEPS,
    CONFIG_UINT32_SKILL_CHANCE_SKINNING_STEPS,
    CONFIG_UINT32_SKILL_GAIN_CRAFTING,
    CONFIG_UINT32_SKILL_GAIN_DEFENSE,
    CONFIG_UINT32_SKILL_GAIN_GATHERING,
    CONFIG_UINT32_SKILL_GAIN_WEAPON,
    CONFIG_UINT32_MAX_OVERSPEED_PINGS,
    CONFIG_UINT32_CHATFLOOD_MESSAGE_COUNT,
    CONFIG_UINT32_CHATFLOOD_MESSAGE_DELAY,
    CONFIG_UINT32_CHATFLOOD_MUTE_TIME,
	CONFIG_UINT32_CHATFLOOD_MESSAGE_COUNT_A,
	CONFIG_UINT32_CHATFLOOD_MESSAGE_DELAY_A,
	CONFIG_UINT32_CHATFLOOD_MUTE_TIME_A,
    CONFIG_UINT32_CREATURE_FAMILY_ASSISTANCE_DELAY,
    CONFIG_UINT32_CREATURE_FAMILY_FLEE_DELAY,
    CONFIG_UINT32_WORLD_BOSS_LEVEL_DIFF,
    CONFIG_UINT32_CHAT_STRICT_LINK_CHECKING_SEVERITY,
    CONFIG_UINT32_CHAT_STRICT_LINK_CHECKING_KICK,
    CONFIG_UINT32_CORPSE_DECAY_NORMAL,
    CONFIG_UINT32_CORPSE_DECAY_RARE,
    CONFIG_UINT32_CORPSE_DECAY_ELITE,
    CONFIG_UINT32_CORPSE_DECAY_RAREELITE,
    CONFIG_UINT32_CORPSE_DECAY_WORLDBOSS,
    CONFIG_UINT32_INSTANT_LOGOUT,
	CONFIG_UINT32_GROUPLEADER_RECONNECT_PERIOD,
    CONFIG_UINT32_BATTLEGROUND_INVITATION_TYPE,
    CONFIG_UINT32_BATTLEGROUND_PREMATURE_FINISH_TIMER,
    CONFIG_UINT32_BATTLEGROUND_PREMADE_GROUP_WAIT_FOR_MATCH,
    CONFIG_UINT32_BATTLEGROUND_QUEUE_ANNOUNCER_JOIN,
    CONFIG_UINT32_GUILD_EVENT_LOG_COUNT,
    CONFIG_UINT32_TIMERBAR_FATIGUE_GMLEVEL,
    CONFIG_UINT32_TIMERBAR_FATIGUE_MAX,
    CONFIG_UINT32_TIMERBAR_BREATH_GMLEVEL,
    CONFIG_UINT32_TIMERBAR_BREATH_MAX,
    CONFIG_UINT32_TIMERBAR_FIRE_GMLEVEL,
    CONFIG_UINT32_TIMERBAR_FIRE_MAX,
    CONFIG_UINT32_MIN_LEVEL_STAT_SAVE,
    CONFIG_UINT32_MAINTENANCE_DAY,
	CONFIG_UINT32_MAINTENANCE_DAY_XP1,
	CONFIG_UINT32_MAINTENANCE_DAY_XP2,
    CONFIG_UINT32_CHARDELETE_KEEP_DAYS,
    CONFIG_UINT32_CHARDELETE_METHOD,
    CONFIG_UINT32_CHARDELETE_MIN_LEVEL,
    CONFIG_UINT32_GUID_RESERVE_SIZE_CREATURE,
    CONFIG_UINT32_GUID_RESERVE_SIZE_GAMEOBJECT,
    CONFIG_UINT32_CREATURE_RESPAWN_AGGRO_DELAY,
	CONFIG_UINT32_HONORAD_TIME_START_1,
	CONFIG_UINT32_HONORAD_TIME_END_1,
	CONFIG_UINT32_HONORAD_TIME_START_2,
	CONFIG_UINT32_HONORAD_TIME_END_2,
	CONFIG_UINT32_HONORAD_TIME_START1_1,
	CONFIG_UINT32_HONORAD_TIME_END1_1,
	CONFIG_UINT32_HONORAD_TIME_START2_2,
	CONFIG_UINT32_HONORAD_TIME_END2_2,
	CONFIG_UINT32_BATTLEGROUND_TIME,
	CONFIG_UINT32_BATTLEGROUND_PLAYER_MINDAMAGE,
	CONFIG_UINT32_BATTLEGROUND_PLAYER_MINHEALINGDONE,
	CONFIG_UINT32_PLAYER_INSTANCES_PER_HOUR,
	CONFIG_UINT32_BATTLEGROUND_IP_PLAYERCONT,
	CONFIG_UINT32_BATTLEGROUND_PLAYERCONT_WINNER,
	CONFIG_UINT32_BATTLEGROUND_PLAYERCONT_LOSER,
	CONFIG_UINT32_NUMTHREADS,
	CONFIG_UINT32_VMSS_MAXTHREADBREAKS, 
    CONFIG_UINT32_VMSS_TBREMTIME, 
    CONFIG_UINT32_VMSS_MAPFREEMETHOD, 
    CONFIG_UINT32_VMSS_FREEZECHECKPERIOD, 
    CONFIG_UINT32_VMSS_FREEZEDETECTTIME,
	CONFIG_UINT32_VMSS_FORCEUNLOADDELAY,
	CONFIG_UINT32_CREATURE_ELITE_NORMAL,
	CREATURE_ELITE_ELITE_ELITE,
	CREATURE_ELITE_RAREELITE_RAREELITE,
	CREATURE_ELITE_WORLDBOSS_WORLDBOSS,
	CREATURE_ELITE_RARE_RARE,
    CONFIG_UINT32_VALUE_COUNT
};

/// Configuration elements
enum eConfigInt32Values
{
    CONFIG_INT32_DEATH_SICKNESS_LEVEL = 0,
    CONFIG_INT32_QUEST_LOW_LEVEL_HIDE_DIFF,
    CONFIG_INT32_QUEST_HIGH_LEVEL_HIDE_DIFF,
    CONFIG_INT32_VALUE_COUNT
};

/// Server config
enum eConfigFloatValues
{
    CONFIG_FLOAT_RATE_HEALTH = 0,
    CONFIG_FLOAT_RATE_POWER_MANA,
    CONFIG_FLOAT_RATE_POWER_RAGE_INCOME,
    CONFIG_FLOAT_RATE_POWER_RAGE_LOSS,
    CONFIG_FLOAT_RATE_POWER_FOCUS,
    CONFIG_FLOAT_RATE_POWER_ENERGY,
    CONFIG_FLOAT_RATE_SKILL_DISCOVERY,
    CONFIG_FLOAT_RATE_DROP_ITEM_POOR,
    CONFIG_FLOAT_RATE_DROP_ITEM_NORMAL,
    CONFIG_FLOAT_RATE_DROP_ITEM_UNCOMMON,
    CONFIG_FLOAT_RATE_DROP_ITEM_RARE,
    CONFIG_FLOAT_RATE_DROP_ITEM_EPIC,
    CONFIG_FLOAT_RATE_DROP_ITEM_LEGENDARY,
    CONFIG_FLOAT_RATE_DROP_ITEM_ARTIFACT,
    CONFIG_FLOAT_RATE_DROP_ITEM_REFERENCED,
	CONFIG_FLOAT_RATE_DROP_ITEM_QUEST,
    CONFIG_FLOAT_RATE_DROP_MONEY,
	CONFIG_FLOAT_RATE_PET_XP_KILL,
    CONFIG_FLOAT_RATE_XP_KILL_LM,
	CONFIG_FLOAT_RATE_XP_KILL_BL,
    CONFIG_FLOAT_RATE_XP_QUEST_LM,
	CONFIG_FLOAT_RATE_XP_QUEST_BL,
    CONFIG_FLOAT_RATE_XP_EXPLORE,
    CONFIG_FLOAT_RATE_REPUTATION_GAIN,
    CONFIG_FLOAT_RATE_REPUTATION_LOWLEVEL_KILL,
    CONFIG_FLOAT_RATE_REPUTATION_LOWLEVEL_QUEST,
	CONFIG_FLOAT_RATE_CREATURE_NORMAL_HP,
	CONFIG_FLOAT_RATE_CREATURE_ELITE_ELITE_HP,
	CONFIG_FLOAT_RATE_CREATURE_ELITE_RAREELITE_HP,
	CONFIG_FLOAT_RATE_CREATURE_ELITE_WORLDBOSS_HP,
	CONFIG_FLOAT_RATE_CREATURE_ELITE_RARE_HP,
	CONFIG_FLOAT_RATE_CREATURE_NORMAL_HP_ZUG,
	CONFIG_FLOAT_RATE_CREATURE_ELITE_ELITE_HP_ZUG,
	CONFIG_FLOAT_RATE_CREATURE_ELITE_RAREELITE_HP_ZUG,
	CONFIG_FLOAT_RATE_CREATURE_ELITE_WORLDBOSS_HP_ZUG,
	CONFIG_FLOAT_RATE_CREATURE_ELITE_RARE_HP_ZUG,
	CONFIG_FLOAT_RATE_CREATURE_NORMAL_HP_FX,
	CONFIG_FLOAT_RATE_CREATURE_ELITE_ELITE_HP_FX,
	CONFIG_FLOAT_RATE_CREATURE_ELITE_RAREELITE_HP_FX,
	CONFIG_FLOAT_RATE_CREATURE_ELITE_WORLDBOSS_HP_FX,
	CONFIG_FLOAT_RATE_CREATURE_ELITE_RARE_HP_FX,
	CONFIG_FLOAT_RATE_CREATURE_NORMAL_HP_MC,
	CONFIG_FLOAT_RATE_CREATURE_ELITE_ELITE_HP_MC,
	CONFIG_FLOAT_RATE_CREATURE_ELITE_RAREELITE_HP_MC,
	CONFIG_FLOAT_RATE_CREATURE_ELITE_WORLDBOSS_HP_MC,
	CONFIG_FLOAT_RATE_CREATURE_ELITE_RARE_HP_MC,
	CONFIG_FLOAT_RATE_CREATURE_NORMAL_HP_HL,
	CONFIG_FLOAT_RATE_CREATURE_ELITE_ELITE_HP_HL,
	CONFIG_FLOAT_RATE_CREATURE_ELITE_RAREELITE_HP_HL,
	CONFIG_FLOAT_RATE_CREATURE_ELITE_WORLDBOSS_HP_HL,
	CONFIG_FLOAT_RATE_CREATURE_ELITE_RARE_HP_HL,
	CONFIG_FLOAT_RATE_CREATURE_NORMAL_HP_BWL,
	CONFIG_FLOAT_RATE_CREATURE_ELITE_ELITE_HP_BWL,
	CONFIG_FLOAT_RATE_CREATURE_ELITE_RAREELITE_HP_BWL,
	CONFIG_FLOAT_RATE_CREATURE_ELITE_WORLDBOSS_HP_BWL,
	CONFIG_FLOAT_RATE_CREATURE_ELITE_RARE_HP_BWL,
	CONFIG_FLOAT_RATE_CREATURE_NORMAL_HP_TAQ,
	CONFIG_FLOAT_RATE_CREATURE_ELITE_ELITE_HP_TAQ,
	CONFIG_FLOAT_RATE_CREATURE_ELITE_RAREELITE_HP_TAQ,
	CONFIG_FLOAT_RATE_CREATURE_ELITE_WORLDBOSS_HP_TAQ,
	CONFIG_FLOAT_RATE_CREATURE_ELITE_RARE_HP_TAQ,
	CONFIG_FLOAT_RATE_CREATURE_NORMAL_HP_NAXX,
	CONFIG_FLOAT_RATE_CREATURE_ELITE_ELITE_HP_NAXX,
	CONFIG_FLOAT_RATE_CREATURE_ELITE_RAREELITE_HP_NAXX,
	CONFIG_FLOAT_RATE_CREATURE_ELITE_WORLDBOSS_HP_NAXX,
	CONFIG_FLOAT_RATE_CREATURE_ELITE_RARE_HP_NAXX,
	CONFIG_FLOAT_RATE_CREATURE_NORMAL_HP_AS,
	CONFIG_FLOAT_RATE_CREATURE_ELITE_ELITE_HP_AS,
	CONFIG_FLOAT_RATE_CREATURE_ELITE_RAREELITE_HP_AS,
	CONFIG_FLOAT_RATE_CREATURE_ELITE_WORLDBOSS_HP_AS,
	CONFIG_FLOAT_RATE_CREATURE_ELITE_RARE_HP_AS,
	CONFIG_FLOAT_RATE_CREATURE_NORMAL_DAMAGE,
	CONFIG_FLOAT_RATE_CREATURE_ELITE_ELITE_DAMAGE,
	CONFIG_FLOAT_RATE_CREATURE_ELITE_RAREELITE_DAMAGE,
	CONFIG_FLOAT_RATE_CREATURE_ELITE_WORLDBOSS_DAMAGE,
	CONFIG_FLOAT_RATE_CREATURE_ELITE_RARE_DAMAGE,
	CONFIG_FLOAT_RATE_CREATURE_NORMAL_DAMAGE_ZUG,
	CONFIG_FLOAT_RATE_CREATURE_ELITE_ELITE_DAMAGE_ZUG,
	CONFIG_FLOAT_RATE_CREATURE_ELITE_RAREELITE_DAMAGE_ZUG,
	CONFIG_FLOAT_RATE_CREATURE_ELITE_WORLDBOSS_DAMAGE_ZUG,
	CONFIG_FLOAT_RATE_CREATURE_ELITE_RARE_DAMAGE_ZUG,
	CONFIG_FLOAT_RATE_CREATURE_NORMAL_DAMAGE_FX,
	CONFIG_FLOAT_RATE_CREATURE_ELITE_ELITE_DAMAGE_FX,
	CONFIG_FLOAT_RATE_CREATURE_ELITE_RAREELITE_DAMAGE_FX,
	CONFIG_FLOAT_RATE_CREATURE_ELITE_WORLDBOSS_DAMAGE_FX,
	CONFIG_FLOAT_RATE_CREATURE_ELITE_RARE_DAMAGE_FX,
	CONFIG_FLOAT_RATE_CREATURE_NORMAL_DAMAGE_MC,
	CONFIG_FLOAT_RATE_CREATURE_ELITE_ELITE_DAMAGE_MC,
	CONFIG_FLOAT_RATE_CREATURE_ELITE_RAREELITE_DAMAGE_MC,
	CONFIG_FLOAT_RATE_CREATURE_ELITE_WORLDBOSS_DAMAGE_MC,
	CONFIG_FLOAT_RATE_CREATURE_ELITE_RARE_DAMAGE_MC,
	CONFIG_FLOAT_RATE_CREATURE_NORMAL_DAMAGE_HL,
	CONFIG_FLOAT_RATE_CREATURE_ELITE_ELITE_DAMAGE_HL,
	CONFIG_FLOAT_RATE_CREATURE_ELITE_RAREELITE_DAMAGE_HL,
	CONFIG_FLOAT_RATE_CREATURE_ELITE_WORLDBOSS_DAMAGE_HL,
	CONFIG_FLOAT_RATE_CREATURE_ELITE_RARE_DAMAGE_HL,
	CONFIG_FLOAT_RATE_CREATURE_NORMAL_DAMAGE_BWL,
	CONFIG_FLOAT_RATE_CREATURE_ELITE_ELITE_DAMAGE_BWL,
	CONFIG_FLOAT_RATE_CREATURE_ELITE_RAREELITE_DAMAGE_BWL,
	CONFIG_FLOAT_RATE_CREATURE_ELITE_WORLDBOSS_DAMAGE_BWL,
	CONFIG_FLOAT_RATE_CREATURE_ELITE_RARE_DAMAGE_BWL,
	CONFIG_FLOAT_RATE_CREATURE_NORMAL_DAMAGE_TAQ,
	CONFIG_FLOAT_RATE_CREATURE_ELITE_ELITE_DAMAGE_TAQ,
	CONFIG_FLOAT_RATE_CREATURE_ELITE_RAREELITE_DAMAGE_TAQ,
	CONFIG_FLOAT_RATE_CREATURE_ELITE_WORLDBOSS_DAMAGE_TAQ,
	CONFIG_FLOAT_RATE_CREATURE_ELITE_RARE_DAMAGE_TAQ,
	CONFIG_FLOAT_RATE_CREATURE_NORMAL_DAMAGE_NAXX,
	CONFIG_FLOAT_RATE_CREATURE_ELITE_ELITE_DAMAGE_NAXX,
	CONFIG_FLOAT_RATE_CREATURE_ELITE_RAREELITE_DAMAGE_NAXX,
	CONFIG_FLOAT_RATE_CREATURE_ELITE_WORLDBOSS_DAMAGE_NAXX,
	CONFIG_FLOAT_RATE_CREATURE_ELITE_RARE_DAMAGE_NAXX,
	CONFIG_FLOAT_RATE_CREATURE_NORMAL_DAMAGE_AS,
	CONFIG_FLOAT_RATE_CREATURE_ELITE_ELITE_DAMAGE_AS,
	CONFIG_FLOAT_RATE_CREATURE_ELITE_RAREELITE_DAMAGE_AS,
	CONFIG_FLOAT_RATE_CREATURE_ELITE_WORLDBOSS_DAMAGE_AS,
	CONFIG_FLOAT_RATE_CREATURE_ELITE_RARE_DAMAGE_AS,
	CONFIG_FLOAT_RATE_CREATURE_NORMAL_SPELLDAMAGE,
	CONFIG_FLOAT_RATE_CREATURE_ELITE_ELITE_SPELLDAMAGE,
	CONFIG_FLOAT_RATE_CREATURE_ELITE_RAREELITE_SPELLDAMAGE,
	CONFIG_FLOAT_RATE_CREATURE_ELITE_WORLDBOSS_SPELLDAMAGE,
	CONFIG_FLOAT_RATE_CREATURE_ELITE_RARE_SPELLDAMAGE,
	CONFIG_FLOAT_RATE_CREATURE_NORMAL_SPELLDAMAGE_ZUG,
	CONFIG_FLOAT_RATE_CREATURE_ELITE_ELITE_SPELLDAMAGE_ZUG,
	CONFIG_FLOAT_RATE_CREATURE_ELITE_RAREELITE_SPELLDAMAGE_ZUG,
	CONFIG_FLOAT_RATE_CREATURE_ELITE_WORLDBOSS_SPELLDAMAGE_ZUG,
	CONFIG_FLOAT_RATE_CREATURE_ELITE_RARE_SPELLDAMAGE_ZUG,
	CONFIG_FLOAT_RATE_CREATURE_NORMAL_SPELLDAMAGE_FX,
	CONFIG_FLOAT_RATE_CREATURE_ELITE_ELITE_SPELLDAMAGE_FX,
	CONFIG_FLOAT_RATE_CREATURE_ELITE_RAREELITE_SPELLDAMAGE_FX,
	CONFIG_FLOAT_RATE_CREATURE_ELITE_WORLDBOSS_SPELLDAMAGE_FX,
	CONFIG_FLOAT_RATE_CREATURE_ELITE_RARE_SPELLDAMAGE_FX,
	CONFIG_FLOAT_RATE_CREATURE_NORMAL_SPELLDAMAGE_MC,
	CONFIG_FLOAT_RATE_CREATURE_ELITE_ELITE_SPELLDAMAGE_MC,
	CONFIG_FLOAT_RATE_CREATURE_ELITE_RAREELITE_SPELLDAMAGE_MC,
	CONFIG_FLOAT_RATE_CREATURE_ELITE_WORLDBOSS_SPELLDAMAGE_MC,
	CONFIG_FLOAT_RATE_CREATURE_ELITE_RARE_SPELLDAMAGE_MC,
	CONFIG_FLOAT_RATE_CREATURE_NORMAL_SPELLDAMAGE_HL,
	CONFIG_FLOAT_RATE_CREATURE_ELITE_ELITE_SPELLDAMAGE_HL,
	CONFIG_FLOAT_RATE_CREATURE_ELITE_RAREELITE_SPELLDAMAGE_HL,
	CONFIG_FLOAT_RATE_CREATURE_ELITE_WORLDBOSS_SPELLDAMAGE_HL,
	CONFIG_FLOAT_RATE_CREATURE_ELITE_RARE_SPELLDAMAGE_HL,
	CONFIG_FLOAT_RATE_CREATURE_NORMAL_SPELLDAMAGE_BWL,
	CONFIG_FLOAT_RATE_CREATURE_ELITE_ELITE_SPELLDAMAGE_BWL,
	CONFIG_FLOAT_RATE_CREATURE_ELITE_RAREELITE_SPELLDAMAGE_BWL,
	CONFIG_FLOAT_RATE_CREATURE_ELITE_WORLDBOSS_SPELLDAMAGE_BWL,
	CONFIG_FLOAT_RATE_CREATURE_ELITE_RARE_SPELLDAMAGE_BWL,
	CONFIG_FLOAT_RATE_CREATURE_NORMAL_SPELLDAMAGE_TAQ,
	CONFIG_FLOAT_RATE_CREATURE_ELITE_ELITE_SPELLDAMAGE_TAQ,
	CONFIG_FLOAT_RATE_CREATURE_ELITE_RAREELITE_SPELLDAMAGE_TAQ,
	CONFIG_FLOAT_RATE_CREATURE_ELITE_WORLDBOSS_SPELLDAMAGE_TAQ,
	CONFIG_FLOAT_RATE_CREATURE_ELITE_RARE_SPELLDAMAGE_TAQ,
	CONFIG_FLOAT_RATE_CREATURE_NORMAL_SPELLDAMAGE_NAXX,
	CONFIG_FLOAT_RATE_CREATURE_ELITE_ELITE_SPELLDAMAGE_NAXX,
	CONFIG_FLOAT_RATE_CREATURE_ELITE_RAREELITE_SPELLDAMAGE_NAXX,
	CONFIG_FLOAT_RATE_CREATURE_ELITE_WORLDBOSS_SPELLDAMAGE_NAXX,
	CONFIG_FLOAT_RATE_CREATURE_ELITE_RARE_SPELLDAMAGE_NAXX,
	CONFIG_FLOAT_RATE_CREATURE_NORMAL_SPELLDAMAGE_AS,
	CONFIG_FLOAT_RATE_CREATURE_ELITE_ELITE_SPELLDAMAGE_AS,
	CONFIG_FLOAT_RATE_CREATURE_ELITE_RAREELITE_SPELLDAMAGE_AS,
	CONFIG_FLOAT_RATE_CREATURE_ELITE_WORLDBOSS_SPELLDAMAGE_AS,
	CONFIG_FLOAT_RATE_CREATURE_ELITE_RARE_SPELLDAMAGE_AS,
    CONFIG_FLOAT_RATE_CREATURE_AGGRO,
    CONFIG_FLOAT_RATE_REST_INGAME,
    CONFIG_FLOAT_RATE_REST_OFFLINE_IN_TAVERN_OR_CITY,
    CONFIG_FLOAT_RATE_REST_OFFLINE_IN_WILDERNESS,
    CONFIG_FLOAT_RATE_DAMAGE_FALL,
    CONFIG_FLOAT_RATE_AUCTION_TIME,
    CONFIG_FLOAT_RATE_AUCTION_DEPOSIT,
    CONFIG_FLOAT_RATE_AUCTION_CUT,
    CONFIG_FLOAT_RATE_HONOR,
    CONFIG_FLOAT_RATE_MINING_AMOUNT,
    CONFIG_FLOAT_RATE_MINING_NEXT,
    CONFIG_FLOAT_RATE_TALENT,
    CONFIG_FLOAT_RATE_LOYALTY,
    CONFIG_FLOAT_RATE_CORPSE_DECAY_LOOTED,
    CONFIG_FLOAT_RATE_INSTANCE_RESET_TIME,
    CONFIG_FLOAT_RATE_TARGET_POS_RECALCULATION_RANGE,
    CONFIG_FLOAT_RATE_DURABILITY_LOSS_DAMAGE,
    CONFIG_FLOAT_RATE_DURABILITY_LOSS_PARRY,
    CONFIG_FLOAT_RATE_DURABILITY_LOSS_ABSORB,
    CONFIG_FLOAT_RATE_DURABILITY_LOSS_BLOCK,
    CONFIG_FLOAT_SIGHT_GUARDER,
    CONFIG_FLOAT_SIGHT_MONSTER,
    CONFIG_FLOAT_LISTEN_RANGE_SAY,
    CONFIG_FLOAT_LISTEN_RANGE_YELL,
    CONFIG_FLOAT_LISTEN_RANGE_TEXTEMOTE,
    CONFIG_FLOAT_CREATURE_FAMILY_FLEE_ASSISTANCE_RADIUS,
    CONFIG_FLOAT_CREATURE_FAMILY_ASSISTANCE_RADIUS,
    CONFIG_FLOAT_GROUP_XP_DISTANCE,
    CONFIG_FLOAT_THREAT_RADIUS,
    CONFIG_FLOAT_GHOST_RUN_SPEED_WORLD,
    CONFIG_FLOAT_GHOST_RUN_SPEED_BG,
	CONFIG_FLOAT_XIOULIFEI,
	CONFIG_FLOAT_HONOR_PLAYER_MAX,
	CONFIG_FLOAT_LOADBALANCE_HIGHVALUE, 
    CONFIG_FLOAT_LOADBALANCE_LOWVALUE,
    CONFIG_FLOAT_VALUE_COUNT
};

/// Configuration elements
enum eConfigBoolValues
{
    CONFIG_BOOL_GRID_UNLOAD = 0,
    CONFIG_BOOL_SAVE_RESPAWN_TIME_IMMEDIATELY,
    CONFIG_BOOL_ALLOW_TWO_SIDE_ACCOUNTS,
    CONFIG_BOOL_ALLOW_TWO_SIDE_INTERACTION_CHAT,
    CONFIG_BOOL_ALLOW_TWO_SIDE_INTERACTION_CHANNEL,
    CONFIG_BOOL_ALLOW_TWO_SIDE_INTERACTION_GROUP,
    CONFIG_BOOL_ALLOW_TWO_SIDE_INTERACTION_GUILD,
    CONFIG_BOOL_ALLOW_TWO_SIDE_INTERACTION_TRADE,
    CONFIG_BOOL_ALLOW_TWO_SIDE_INTERACTION_AUCTION,
    CONFIG_BOOL_ALLOW_TWO_SIDE_INTERACTION_MAIL,
    CONFIG_BOOL_ALLOW_TWO_SIDE_WHO_LIST,
    CONFIG_BOOL_ALLOW_TWO_SIDE_ADD_FRIEND,
    CONFIG_BOOL_INSTANCE_IGNORE_LEVEL,
    CONFIG_BOOL_INSTANCE_IGNORE_RAID,
    CONFIG_BOOL_CAST_UNSTUCK,
    CONFIG_BOOL_GM_LOG_TRADE,
    CONFIG_BOOL_GM_LOWER_SECURITY,
    CONFIG_BOOL_ALWAYS_MAX_SKILL_FOR_LEVEL,
    CONFIG_BOOL_WEATHER,
    CONFIG_BOOL_EVENT_ANNOUNCE,
    CONFIG_BOOL_QUEST_IGNORE_RAID,
    CONFIG_BOOL_DETECT_POS_COLLISION,
    CONFIG_BOOL_RESTRICTED_LFG_CHANNEL,
    CONFIG_BOOL_SILENTLY_GM_JOIN_TO_CHANNEL,
    CONFIG_BOOL_CHAT_FAKE_MESSAGE_PREVENTING,
    CONFIG_BOOL_CHAT_STRICT_LINK_CHECKING_SEVERITY,
    CONFIG_BOOL_CHAT_STRICT_LINK_CHECKING_KICK,
    CONFIG_BOOL_ADDON_CHANNEL,
    CONFIG_BOOL_CORPSE_EMPTY_LOOT_SHOW,
    CONFIG_BOOL_DEATH_CORPSE_RECLAIM_DELAY_PVP,
    CONFIG_BOOL_DEATH_CORPSE_RECLAIM_DELAY_PVE,
    CONFIG_BOOL_DEATH_BONES_WORLD,
    CONFIG_BOOL_DEATH_BONES_BG,
    CONFIG_BOOL_ALL_TAXI_PATHS,
	CONFIG_BOOL_ALL_EXPLORED,
    CONFIG_BOOL_SKILL_FAIL_LOOT_FISHING,
    CONFIG_BOOL_SKILL_FAIL_GAIN_FISHING,
    CONFIG_BOOL_SKILL_FAIL_POSSIBLE_FISHINGPOOL,
    CONFIG_BOOL_BATTLEGROUND_CAST_DESERTER,
    CONFIG_BOOL_BATTLEGROUND_QUEUE_ANNOUNCER_START,
    CONFIG_BOOL_BATTLEGROUND_SCORE_STATISTICS,
    CONFIG_BOOL_OUTDOORPVP_SI_ENABLED,
    CONFIG_BOOL_OUTDOORPVP_EP_ENABLED,
    CONFIG_BOOL_KICK_PLAYER_ON_BAD_PACKET,
    CONFIG_BOOL_STATS_SAVE_ONLY_ON_LOGOUT,
    CONFIG_BOOL_CLEAN_CHARACTER_DB,
    CONFIG_BOOL_VMAP_INDOOR_CHECK,
    CONFIG_BOOL_PET_UNSUMMON_AT_MOUNT,
    CONFIG_BOOL_MMAP_ENABLED,
	CONFIG_BOOL_WORLD_LOGN_ON,
	CONFIG_BOOL_WORLD_AH_ON,
	CONFIG_BOOL_WORLD_PVP_ON,
	CONFIG_BOOL_BATTLEGROUND_CFBG,
    CONFIG_BOOL_PLAYER_COMMANDS,
	CONFIG_BOOL_SAFE_LOCK,
	CONFIG_BOOL_OUTDOORPVP_TS_ENABLED,
	CONFIG_BOOL_OUTDOORPVP_ZG_ENABLED,
	CONFIG_BOOL_OUTDOORPVP_FX_ENABLED,
	CONFIG_BOOL_OUTDOORPVP_EY_ENABLED,
	CONFIG_BOOL_FEIJI_SHUNFEI,
	CONFIG_BOOL_TAQ_KAIENRENWU,
	CONFIG_BOOL_BATTLEGROUND_JIANCE,
	CONFIG_BOOL_BATTLEGROUND_REPUTATION_AV,
	CONFIG_BOOL_BATTLEGROUND_REPUTATION_WS,
	CONFIG_BOOL_BATTLEGROUND_REPUTATION_AB,
	CONFIG_BOOL_PLAYER_INSTANCES_PER_HOUR_DAKAI,
	CONFIG_BOOL_BATTLEGROUND_MAIL,
	CONFIG_BOOL_THREADS_DYNAMIC,
	CONFIG_BOOL_VMSS_ENABLE,
	CONFIG_BOOL_VMSS_TRYSKIPFIRST,
    CONFIG_BOOL_VALUE_COUNT
};

/// Type of server
enum RealmType
{
    REALM_TYPE_NORMAL = 0,
    REALM_TYPE_PVP = 1,
    REALM_TYPE_NORMAL2 = 4,
    REALM_TYPE_RP = 6,
    REALM_TYPE_RPPVP = 8,
    REALM_TYPE_FFA_PVP = 16                                 // custom, free for all pvp mode like arena PvP in all zones except rest activated places and sanctuaries
                         // replaced by REALM_PVP in realm list
};

// [-ZERO] Need drop not existed cases
enum RealmZone
{
    REALM_ZONE_UNKNOWN       = 0,                           // any language
    REALM_ZONE_DEVELOPMENT   = 1,                           // any language
    REALM_ZONE_UNITED_STATES = 2,                           // extended-Latin
    REALM_ZONE_OCEANIC       = 3,                           // extended-Latin
    REALM_ZONE_LATIN_AMERICA = 4,                           // extended-Latin
    REALM_ZONE_TOURNAMENT_5  = 5,                           // basic-Latin at create, any at login
    REALM_ZONE_KOREA         = 6,                           // East-Asian
    REALM_ZONE_TOURNAMENT_7  = 7,                           // basic-Latin at create, any at login
    REALM_ZONE_ENGLISH       = 8,                           // extended-Latin
    REALM_ZONE_GERMAN        = 9,                           // extended-Latin
    REALM_ZONE_FRENCH        = 10,                          // extended-Latin
    REALM_ZONE_SPANISH       = 11,                          // extended-Latin
    REALM_ZONE_RUSSIAN       = 12,                          // Cyrillic
    REALM_ZONE_TOURNAMENT_13 = 13,                          // basic-Latin at create, any at login
    REALM_ZONE_TAIWAN        = 14,                          // East-Asian
    REALM_ZONE_TOURNAMENT_15 = 15,                          // basic-Latin at create, any at login
    REALM_ZONE_CHINA         = 16,                          // East-Asian
    REALM_ZONE_CN1           = 17,                          // basic-Latin at create, any at login
    REALM_ZONE_CN2           = 18,                          // basic-Latin at create, any at login
    REALM_ZONE_CN3           = 19,                          // basic-Latin at create, any at login
    REALM_ZONE_CN4           = 20,                          // basic-Latin at create, any at login
    REALM_ZONE_CN5           = 21,                          // basic-Latin at create, any at login
    REALM_ZONE_CN6           = 22,                          // basic-Latin at create, any at login
    REALM_ZONE_CN7           = 23,                          // basic-Latin at create, any at login
    REALM_ZONE_CN8           = 24,                          // basic-Latin at create, any at login
    REALM_ZONE_TOURNAMENT_25 = 25,                          // basic-Latin at create, any at login
    REALM_ZONE_TEST_SERVER   = 26,                          // any language
    REALM_ZONE_TOURNAMENT_27 = 27,                          // basic-Latin at create, any at login
    REALM_ZONE_QA_SERVER     = 28,                          // any language
    REALM_ZONE_CN9           = 29                           // basic-Latin at create, any at login
};

typedef std::pair<uint32, uint32> ItemPair;
typedef std::list< ItemPair > ItemPairs;

/// Storage class for commands issued for delayed execution
struct CliCommandHolder
{
    typedef void Print(void*, const char*);
    typedef void CommandFinished(void*, bool success);

    uint32 m_cliAccountId;                                  // 0 for console and real account id for RA/soap
    AccountTypes m_cliAccessLevel;
    void* m_callbackArg;
    char* m_command;
    Print* m_print;
    CommandFinished* m_commandFinished;

    CliCommandHolder(uint32 accountId, AccountTypes cliAccessLevel, void* callbackArg, const char* command, Print* zprint, CommandFinished* commandFinished)
        : m_cliAccountId(accountId), m_cliAccessLevel(cliAccessLevel), m_callbackArg(callbackArg), m_print(zprint), m_commandFinished(commandFinished)
    {
        size_t len = strlen(command) + 1;
        m_command = new char[len];
        memcpy(m_command, command, len);
    }

    ~CliCommandHolder() { delete[] m_command; }
};

/// The World
class World
{
    public:
		static ACE_Atomic_Op<ACE_Thread_Mutex, uint32> m_worldLoopCounter;

        World();
        ~World();

        void CleanupsBeforeStop();

        WorldSession* FindSession(uint32 id) const;
        void AddSession(WorldSession* s);
		void SendBroadcast();
        bool RemoveSession(uint32 id);
		void RewardItemid(Player* plr, uint32 item_id, uint32 count);
        /// Get the number of current active sessions
        void UpdateMaxSessionCounters();
        uint32 GetActiveAndQueuedSessionCount() const { return m_sessions.size(); }
        uint32 GetActiveSessionCount() const { return m_sessions.size() - m_QueuedSessions.size(); }
        uint32 GetQueuedSessionCount() const { return m_QueuedSessions.size(); }
        /// Get the maximum number of parallel sessions on the server since last reboot
        uint32 GetMaxQueuedSessionCount() const { return m_maxQueuedSessionCount; }
        uint32 GetMaxActiveSessionCount() const { return m_maxActiveSessionCount; }

        /// Get the active session server limit (or security level limitations)
        uint32 GetPlayerAmountLimit() const { return m_playerLimit >= 0 ? m_playerLimit : 0; }
        AccountTypes GetPlayerSecurityLimit() const { return m_playerLimit <= 0 ? AccountTypes(-m_playerLimit) : SEC_PLAYER; }

        /// Set the active session server limit (or security level limitation)
        void SetPlayerLimit(int32 limit, bool needUpdate = false);

        // player Queue
        typedef std::list<WorldSession*> Queue;
        void AddQueuedSession(WorldSession*);
        bool RemoveQueuedSession(WorldSession* session);
        int32 GetQueuedSessionPos(WorldSession*);

        /// \todo Actions on m_allowMovement still to be implemented
        /// Is movement allowed?
        bool getAllowMovement() const { return m_allowMovement; }
        /// Allow/Disallow object movements
        void SetAllowMovement(bool allow) { m_allowMovement = allow; }

        /// Set a new Message of the Day
        void SetMotd(const std::string& motd) { m_motd = motd; }
        /// Get the current Message of the Day
        const char* GetMotd() const { return m_motd.c_str(); }

        LocaleConstant GetDefaultDbcLocale() const { return m_defaultDbcLocale; }

        /// Get the path where data (dbc, maps) are stored on disk
        std::string GetDataPath() const { return m_dataPath; }

        /// When server started?
        time_t const& GetStartTime() const { return m_startTime; }
        /// What time is it?
        time_t const& GetGameTime() const { return m_gameTime; }
        /// Uptime (in secs)
        uint32 GetUptime() const { return uint32(m_gameTime - m_startTime); }

        tm* GetLocalTimeByTime(time_t now) const { return localtime(&now); }
        uint32 GetDateByLocalTime(tm* now) const { return ((uint32)(now->tm_year << 16) | (uint32)(now->tm_yday)); }
        uint32 GetDateToday() const {   return GetDateByLocalTime(GetLocalTimeByTime(m_gameTime)); }
        uint32 GetDateThisWeekBegin() const {   return GetDateToday() - GetLocalTimeByTime(m_gameTime)->tm_wday; }
        uint32 GetDateLastMaintenanceDay() const
        {
            uint32 today = GetDateToday();
            uint32 mDay  = getConfig(CONFIG_UINT32_MAINTENANCE_DAY);
            tm* date     = GetLocalTimeByTime(m_gameTime);
            // formula to find last mDay of gregorian calendary
            return today - ((date->tm_wday - mDay  + 7) % 7);
        }

		uint32 GetDateLastMaintenanceDayXp1() const
		{
			uint32 today = GetDateToday();
			uint32 mDay = getConfig(CONFIG_UINT32_MAINTENANCE_DAY_XP1);
			tm* date = GetLocalTimeByTime(m_gameTime);
			// formula to find last mDay of gregorian calendary
			return today - ((date->tm_wday - mDay + 7) % 7);
		}

		uint32 GetDateLastMaintenanceDayXp2() const
		{
			uint32 today = GetDateToday();
			uint32 mDay = getConfig(CONFIG_UINT32_MAINTENANCE_DAY_XP2);
			tm* date = GetLocalTimeByTime(m_gameTime);
			// formula to find last mDay of gregorian calendary
			return today - ((date->tm_wday - mDay + 7) % 7);
		}

        /// Get the maximum skill level a player can reach
        uint16 GetConfigMaxSkillValue() const
        {
            uint32 lvl = getConfig(CONFIG_UINT32_MAX_PLAYER_LEVEL);
            return lvl > 60 ? 300 + ((lvl - 60) * 75) / 10 : lvl * 5;
        }

        void SetInitialWorldSettings();
        void LoadConfigSettings(bool reload = false);
		void SendWorldTeam(int32 team, int32 string_id, ...);
        void SendWorldText(int32 string_id, ...);
		void SendWorldTeamText(Player* pPlayer, int32 string_id, ...);
        void SendGlobalMessage(WorldPacket* packet);
        void SendServerMessage(ServerMessageType type, const char* text = "", Player* player = NULL);
        void SendZoneUnderAttackMessage(uint32 zoneId, Team team);
        void SendDefenseMessage(uint32 zoneId, int32 textId);

        /// Are we in the middle of a shutdown?
        bool IsShutdowning() const { return m_ShutdownTimer > 0; }
        void ShutdownServ(uint32 time, uint32 options, uint8 exitcode);
        void ShutdownCancel();
        void ShutdownMsg(bool show = false, Player* player = NULL);
        static uint8 GetExitCode() { return m_ExitCode; }
        static void StopNow(uint8 exitcode) { m_stopEvent = true; m_ExitCode = exitcode; }
        static bool IsStopped() { return m_stopEvent; }

        void Update(uint32 diff);

        void UpdateSessions(uint32 diff);

        /// Get a server configuration element (see #eConfigFloatValues)
        void setConfig(eConfigFloatValues index, float value) { m_configFloatValues[index] = value; }
        /// Get a server configuration element (see #eConfigFloatValues)
        float getConfig(eConfigFloatValues rate) const { return m_configFloatValues[rate]; }

        /// Set a server configuration element (see #eConfigUInt32Values)
        void setConfig(eConfigUInt32Values index, uint32 value) { m_configUint32Values[index] = value; }
        /// Get a server configuration element (see #eConfigUInt32Values)
        uint32 getConfig(eConfigUInt32Values index) const { return m_configUint32Values[index]; }

        /// Set a server configuration element (see #eConfigInt32Values)
        void setConfig(eConfigInt32Values index, int32 value) { m_configInt32Values[index] = value; }
        /// Get a server configuration element (see #eConfigInt32Values)
        int32 getConfig(eConfigInt32Values index) const { return m_configInt32Values[index]; }

        /// Set a server configuration element (see #eConfigBoolValues)
        void setConfig(eConfigBoolValues index, bool value) { m_configBoolValues[index] = value; }
        /// Get a server configuration element (see #eConfigBoolValues)
        bool getConfig(eConfigBoolValues index) const { return m_configBoolValues[index]; }

        /// Get configuration about force-loaded maps
        std::set<uint32>* getConfigForceLoadMapIds() const { return m_configForceLoadMapIds; }

        /// Are we on a "Player versus Player" server?
        bool IsPvPRealm() { return (getConfig(CONFIG_UINT32_GAME_TYPE) == REALM_TYPE_PVP || getConfig(CONFIG_UINT32_GAME_TYPE) == REALM_TYPE_RPPVP || getConfig(CONFIG_UINT32_GAME_TYPE) == REALM_TYPE_FFA_PVP); }
        bool IsFFAPvPRealm() { return getConfig(CONFIG_UINT32_GAME_TYPE) == REALM_TYPE_FFA_PVP; }

        void KickAll();
        void KickAllLess(AccountTypes sec);
        BanReturn BanAccount(BanMode mode, std::string nameOrIP, uint32 duration_secs, std::string reason, const std::string& author);
        bool RemoveBanAccount(BanMode mode, std::string nameOrIP);

        // for max speed access
        static float GetMaxVisibleDistanceOnContinents()    { return m_MaxVisibleDistanceOnContinents; }
        static float GetMaxVisibleDistanceInInstances()     { return m_MaxVisibleDistanceInInstances;  }
        static float GetMaxVisibleDistanceInBG()            { return m_MaxVisibleDistanceInBG;         }

        static float GetMaxVisibleDistanceInFlight()        { return m_MaxVisibleDistanceInFlight;    }
        static float GetVisibleUnitGreyDistance()           { return m_VisibleUnitGreyDistance;       }
        static float GetVisibleObjectGreyDistance()         { return m_VisibleObjectGreyDistance;     }

		//movement anticheat enable flag
        inline bool GetMvAnticheatEnable()             {return m_MvAnticheatEnable;}
        inline bool GetMvAnticheatKick()               {return m_MvAnticheatKick;}
        inline uint32 GetMvAnticheatAlarmCount()       {return m_MvAnticheatAlarmCount;}
        inline uint32 GetMvAnticheatAlarmPeriod()      {return m_MvAnticheatAlarmPeriod;}
        inline unsigned char GetMvAnticheatBan()       {return m_MvAntiCheatBan;}
        inline uint32 GetMvAnticheatBanTime()     {return m_MvAnticheatBanTime;}
        inline unsigned char GetMvAnticheatGmLevel()   {return m_MvAnticheatGmLevel;}
        inline bool GetMvAnticheatKill()               {return m_MvAnticheatKill;}
        inline float GetMvAnticheatMaxXYT()            {return m_MvAnticheatMaxXYT;}
		inline float GetMvAnticheatMaxXGJZQ()            {return m_MvAnticheatMaxXGJZQ;}
		inline float GetMvAnticheatMaxXPTGH()            {return m_MvAnticheatMaxXPTGH;}
		inline float GetMvAnticheatMaxXPTZQ()            {return m_MvAnticheatMaxXPTZQ;}
		inline float GetMvAnticheatMaxXGJGH()            {return m_MvAnticheatMaxXGJGH;}
		inline float GetMvAnticheatMaxXGJYY()            {return m_MvAnticheatMaxXGJYY;}
		inline float GetMvAnticheatMaxXDBX()             {return m_MvAnticheatMaxXDBX; }
        inline uint16 GetMvAnticheatIgnoreAfterTeleport()   {return m_MvAnticheatIgnoreAfterTeleport;}

        static float GetRelocationLowerLimitSq()            { return m_relocation_lower_limit_sq; }
        static uint32 GetRelocationAINotifyDelay()          { return m_relocation_ai_notify_delay; }

        void InitServerMaintenanceCheck();
        void ServerMaintenanceStart();

		void PlayerWorldMailGuid(ItemPairs items, Player* pPlayer, std::string msgSubject, std::string msgText);

		uint32 battleground_kaiguan;
		uint32 battleground_time_Start1;
		uint32 battleground_time_End1;
		uint32 battleground_time_Start2;
		uint32 battleground_time_End2;
		uint32 GetBattleGroundTime(uint32 id, uint32 canshu);

        void ProcessCliCommands();
        void QueueCliCommand(CliCommandHolder* commandHolder) { cliCmdQueue.add(commandHolder); }

        void UpdateResultQueue();
        void InitResultQueue();

        void UpdateRealmCharCount(uint32 accid);

        LocaleConstant GetAvailableDbcLocale(LocaleConstant locale) const { if (m_availableDbcLocaleMask & (1 << locale)) return locale; else return m_defaultDbcLocale; }

        // used World DB version
        void LoadDBVersion();
        char const* GetDBVersion() { return m_DBVersion.c_str(); }
        char const* GetCreatureEventAIVersion() { return m_CreatureEventAIVersion.c_str(); }

		void SetHuoLia(time_t t, time_t now, time_t nextWeek, time_t today, uint32 period, uint32 diff);
		void SetHuoLib(uint64 next_reset);
		bool BattleGroundWeek();
		void SetTaqWuZhi(uint32 id, uint32 cont);
		uint32 GetTaqWuZhi(uint32 id, uint32 canshu);
		uint32 ChaXunBossFdId();
		bool WorldBossId(uint32 Entry);
		void SetBossId(uint32 Entry);
		bool ChaXunGuild_IdBossFd(uint32 Entry);
		bool ChaXunTeam_IdBossFd(uint32 Entry, uint32 Team_Id);
		void SetBossFd(uint32 Entry, uint32 guildid, uint32 world_fd, uint32 lm_fd, uint32 bl_fd, uint32 team);
        /**
        * \brief: force all client to request player data
        * \param: ObjectGuid guid : guid of the specified player
        * \returns: void
        *
        * Description: InvalidatePlayerDataToAllClient force all connected clients to clear specified player cache
        * FullName: World::InvalidatePlayerDataToAllClient
        * Access: public
        **/
        void InvalidatePlayerDataToAllClient(ObjectGuid guid);

		bool Worldsdebug;

    protected:
        void _UpdateGameTime();
        // callback for UpdateRealmCharacters
        void _UpdateRealmCharCount(QueryResult* resultCharCount, uint32 accountId);

    private:
        void setConfig(eConfigUInt32Values index, char const* fieldname, uint32 defvalue);
        void setConfig(eConfigInt32Values index, char const* fieldname, int32 defvalue);
        void setConfig(eConfigFloatValues index, char const* fieldname, float defvalue);
        void setConfig(eConfigBoolValues index, char const* fieldname, bool defvalue);
        void setConfigPos(eConfigFloatValues index, char const* fieldname, float defvalue);
        void setConfigMin(eConfigUInt32Values index, char const* fieldname, uint32 defvalue, uint32 minvalue);
        void setConfigMin(eConfigInt32Values index, char const* fieldname, int32 defvalue, int32 minvalue);
        void setConfigMin(eConfigFloatValues index, char const* fieldname, float defvalue, float minvalue);
        void setConfigMinMax(eConfigUInt32Values index, char const* fieldname, uint32 defvalue, uint32 minvalue, uint32 maxvalue);
        void setConfigMinMax(eConfigInt32Values index, char const* fieldname, int32 defvalue, int32 minvalue, int32 maxvalue);
        void setConfigMinMax(eConfigFloatValues index, char const* fieldname, float defvalue, float minvalue, float maxvalue);
        bool configNoReload(bool reload, eConfigUInt32Values index, char const* fieldname, uint32 defvalue);
        bool configNoReload(bool reload, eConfigInt32Values index, char const* fieldname, int32 defvalue);
        bool configNoReload(bool reload, eConfigFloatValues index, char const* fieldname, float defvalue);
        bool configNoReload(bool reload, eConfigBoolValues index, char const* fieldname, bool defvalue);

        static volatile bool m_stopEvent;
        static uint8 m_ExitCode;
        uint32 m_ShutdownTimer;
        uint32 m_ShutdownMask;

        uint32 m_NextMaintenanceDate;
        uint32 m_MaintenanceTimeChecker;

        time_t m_startTime;
        time_t m_gameTime;
        IntervalTimer m_timers[WUPDATE_COUNT];
        uint32 mail_timer;
        uint32 mail_timer_expires;

        typedef UNORDERED_MAP<uint32, WorldSession*> SessionMap;
        SessionMap m_sessions;
        uint32 m_maxActiveSessionCount;
        uint32 m_maxQueuedSessionCount;

        uint32 m_configUint32Values[CONFIG_UINT32_VALUE_COUNT];
        int32 m_configInt32Values[CONFIG_INT32_VALUE_COUNT];
        float m_configFloatValues[CONFIG_FLOAT_VALUE_COUNT];
        bool m_configBoolValues[CONFIG_BOOL_VALUE_COUNT];

        int32 m_playerLimit;
        LocaleConstant m_defaultDbcLocale;                  // from config for one from loaded DBC locales
        uint32 m_availableDbcLocaleMask;                    // by loaded DBC
        void DetectDBCLang();
        bool m_allowMovement;
        std::string m_motd;
        std::string m_dataPath;

        // for max speed access
        static float m_MaxVisibleDistanceOnContinents;
        static float m_MaxVisibleDistanceInInstances;
        static float m_MaxVisibleDistanceInBG;

        static float m_MaxVisibleDistanceInFlight;
        static float m_VisibleUnitGreyDistance;
        static float m_VisibleObjectGreyDistance;

		//movement anticheat enable flag
        bool m_MvAnticheatEnable;
        bool m_MvAnticheatKick;
        uint32 m_MvAnticheatAlarmCount;
        uint32 m_MvAnticheatAlarmPeriod;
        unsigned char m_MvAntiCheatBan;
        uint32 m_MvAnticheatBanTime;
        unsigned char m_MvAnticheatGmLevel;
        bool m_MvAnticheatKill;
        float m_MvAnticheatMaxXYT;
		float m_MvAnticheatMaxXGJZQ;
		float m_MvAnticheatMaxXPTGH;
		float m_MvAnticheatMaxXPTZQ;
		float m_MvAnticheatMaxXGJGH;
		float m_MvAnticheatMaxXGJYY;
		float m_MvAnticheatMaxXDBX;
        uint16 m_MvAnticheatIgnoreAfterTeleport;

        static float  m_relocation_lower_limit_sq;
        static uint32 m_relocation_ai_notify_delay;

        // CLI command holder to be thread safe
        ACE_Based::LockedQueue<CliCommandHolder*, ACE_Thread_Mutex> cliCmdQueue;

        // Player Queue
        Queue m_QueuedSessions;

        // sessions that are added async
        void AddSession_(WorldSession* s);
        ACE_Based::LockedQueue<WorldSession*, ACE_Thread_Mutex> addSessQueue;

        // used versions
        std::string m_DBVersion;
        std::string m_CreatureEventAIVersion;

        // List of Maps that should be force-loaded on startup
        std::set<uint32>* m_configForceLoadMapIds;
};

extern uint32 realmID;

#define sWorld MaNGOS::Singleton<World>::Instance()
#endif
/// @}
