/*
 * Copyright (C) 2008-2016 TrinityCore <http://www.trinitycore.org/>
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2 of the License, or (at your
 * option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#include "AuthenticationPackets.h"
#include "HmacHash.h"

WorldPacket const* WorldPackets::Auth::AuthChallenge::Write()
{
    _worldPacket.append(DosChallenge, 8);
    _worldPacket.append(Challenge.data(), Challenge.size());
    _worldPacket << uint8(DosZeroBits);
    return &_worldPacket;
}

void WorldPackets::Auth::AuthSession::Read()
{
    uint32 addonDataSize, realmJoinTicketSize;

    _worldPacket >> Build;
    _worldPacket >> BuildType;
    _worldPacket >> RegionID;
    _worldPacket >> BattlegroupID;
    _worldPacket >> RealmID;
    _worldPacket.read(LocalChallenge.data(), LocalChallenge.size());
    _worldPacket.read(Digest.data(), Digest.size());
    _worldPacket >> DosResponse;
    _worldPacket >> addonDataSize;
    if (addonDataSize)
    {
        AddonInfo.resize(std::min(addonDataSize, uint32(_worldPacket.size() - _worldPacket.rpos())));
        _worldPacket.read(AddonInfo.contents(), AddonInfo.size());
    }

    _worldPacket >> realmJoinTicketSize;
    if (realmJoinTicketSize)
    {
        RealmJoinTicket.resize(std::min(realmJoinTicketSize, uint32(_worldPacket.size() - _worldPacket.rpos())));
        _worldPacket.read(reinterpret_cast<uint8*>(&RealmJoinTicket[0]), RealmJoinTicket.size());
    }

    UseIPv6 = _worldPacket.ReadBit();           // UseIPv6
}

WorldPackets::Auth::AuthResponse::AuthResponse()
    : ServerPacket(SMSG_AUTH_RESPONSE, 132)
{
}

WorldPacket const* WorldPackets::Auth::AuthResponse::Write()
{
    _worldPacket << uint32(Result);
    _worldPacket.WriteBit(SuccessInfo.is_initialized());
    _worldPacket.WriteBit(WaitInfo.is_initialized());
    _worldPacket.FlushBits();

    if (SuccessInfo)
    {
        _worldPacket << uint32(SuccessInfo->VirtualRealmAddress);
        _worldPacket << uint32(SuccessInfo->VirtualRealms.size());
        _worldPacket << uint32(SuccessInfo->TimeRested);
        _worldPacket << uint8(SuccessInfo->ActiveExpansionLevel);
        _worldPacket << uint8(SuccessInfo->AccountExpansionLevel);
        _worldPacket << uint32(SuccessInfo->TimeSecondsUntilPCKick);
        _worldPacket << uint32(SuccessInfo->AvailableRaces->size());
        _worldPacket << uint32(SuccessInfo->AvailableClasses->size());
        _worldPacket << uint32(SuccessInfo->Templates.size());
        _worldPacket << uint32(SuccessInfo->CurrencyID);

        {
            _worldPacket << uint32(SuccessInfo->Billing.BillingPlan);
            _worldPacket << uint32(SuccessInfo->Billing.TimeRemain);
            // 3x same bit is not a mistake - preserves legacy client behavior of BillingPlanFlags::SESSION_IGR
            _worldPacket.WriteBit(SuccessInfo->Billing.InGameRoom); // inGameRoom check in function checking which lua event to fire when remaining time is near end - BILLING_NAG_DIALOG vs IGR_BILLING_NAG_DIALOG
            _worldPacket.WriteBit(SuccessInfo->Billing.InGameRoom); // inGameRoom lua return from Script_GetBillingPlan
            _worldPacket.WriteBit(SuccessInfo->Billing.InGameRoom); // not used anywhere in the client
            _worldPacket.FlushBits();
        }

        for (auto& virtualRealm : SuccessInfo->VirtualRealms)
        {
            _worldPacket << uint32(virtualRealm.RealmAddress);
            _worldPacket.WriteBit(virtualRealm.IsLocal);
            _worldPacket.WriteBit(virtualRealm.IsInternalRealm);
            _worldPacket.WriteBits(virtualRealm.RealmNameActual.length(), 8);
            _worldPacket.WriteBits(virtualRealm.RealmNameNormalized.length(), 8);
            _worldPacket.FlushBits();

            _worldPacket.WriteString(virtualRealm.RealmNameActual);
            _worldPacket.WriteString(virtualRealm.RealmNameNormalized);
        }

        for (auto& race : *SuccessInfo->AvailableRaces)
        {
            _worldPacket << uint8(race.first); /// the current race
            _worldPacket << uint8(race.second); /// the required Expansion
        }

        for (auto& klass : *SuccessInfo->AvailableClasses)
        {
            _worldPacket << uint8(klass.first); /// the current class
            _worldPacket << uint8(klass.second); /// the required Expansion
        }

        for (auto& templat : SuccessInfo->Templates)
        {
            _worldPacket << uint32(templat.TemplateSetId);
            _worldPacket << uint32(templat.Classes.size());
            for (auto& templateClass : templat.Classes)
            {
                _worldPacket << uint8(templateClass.ClassID);
                _worldPacket << uint8(templateClass.FactionGroup);
            }

            _worldPacket.WriteBits(templat.Name.length(), 7);
            _worldPacket.WriteBits(templat.Description.length(), 10);
            _worldPacket.FlushBits();

            _worldPacket.WriteString(templat.Name);
            _worldPacket.WriteString(templat.Description);
        }

        _worldPacket.WriteBit(SuccessInfo->IsExpansionTrial);
        _worldPacket.WriteBit(SuccessInfo->ForceCharacterTemplate);
        _worldPacket.WriteBit(SuccessInfo->NumPlayersHorde.is_initialized());
        _worldPacket.WriteBit(SuccessInfo->NumPlayersAlliance.is_initialized());
        _worldPacket.FlushBits();

        if (SuccessInfo->NumPlayersHorde)
            _worldPacket << uint16(*SuccessInfo->NumPlayersHorde);

        if (SuccessInfo->NumPlayersAlliance)
            _worldPacket << uint16(*SuccessInfo->NumPlayersAlliance);
    }

    if (WaitInfo)
    {
        _worldPacket << uint32(WaitInfo->WaitCount);
        _worldPacket << uint32(WaitInfo->WaitTime);
        _worldPacket.WriteBit(WaitInfo->HasFCM);
        _worldPacket.FlushBits();
    }

    return &_worldPacket;
}

std::string const WorldPackets::Auth::ConnectTo::Haiku("An island of peace\nCorruption is brought ashore\nPandarens will rise\n\0\0", 71);

uint8 const WorldPackets::Auth::ConnectTo::PiDigits[130] =
{
    0x31, 0x41, 0x59, 0x26, 0x53, 0x58, 0x97, 0x93, 0x23, 0x84,
    0x62, 0x64, 0x33, 0x83, 0x27, 0x95, 0x02, 0x88, 0x41, 0x97,
    0x16, 0x93, 0x99, 0x37, 0x51, 0x05, 0x82, 0x09, 0x74, 0x94,
    0x45, 0x92, 0x30, 0x78, 0x16, 0x40, 0x62, 0x86, 0x20, 0x89,
    0x98, 0x62, 0x80, 0x34, 0x82, 0x53, 0x42, 0x11, 0x70, 0x67,
    0x98, 0x21, 0x48, 0x08, 0x65, 0x13, 0x28, 0x23, 0x06, 0x64,
    0x70, 0x93, 0x84, 0x46, 0x09, 0x55, 0x05, 0x82, 0x23, 0x17,
    0x25, 0x35, 0x94, 0x08, 0x12, 0x84, 0x81, 0x11, 0x74, 0x50,
    0x28, 0x41, 0x02, 0x70, 0x19, 0x38, 0x52, 0x11, 0x05, 0x55,
    0x96, 0x44, 0x62, 0x29, 0x48, 0x95, 0x49, 0x30, 0x38, 0x19,
    0x64, 0x42, 0x88, 0x10, 0x97, 0x56, 0x65, 0x93, 0x34, 0x46,
    0x12, 0x84, 0x75, 0x64, 0x82, 0x33, 0x78, 0x67, 0x83, 0x16,
    0x52, 0x71, 0x20, 0x19, 0x09, 0x14, 0x56, 0x48, 0x56, 0x69,
};

/*
RSA key values

uint8 const Modulus[] =
{
    0x5F, 0xD6, 0x80, 0x0B, 0xA7, 0xFF, 0x01, 0x40, 0xC7, 0xBC, 0x8E, 0xF5, 0x6B, 0x27, 0xB0, 0xBF,
    0xF0, 0x1D, 0x1B, 0xFE, 0xDD, 0x0B, 0x1F, 0x3D, 0xB6, 0x6F, 0x1A, 0x48, 0x0D, 0xFB, 0x51, 0x08,
    0x65, 0x58, 0x4F, 0xDB, 0x5C, 0x6E, 0xCF, 0x64, 0xCB, 0xC1, 0x6B, 0x2E, 0xB8, 0x0F, 0x5D, 0x08,
    0x5D, 0x89, 0x06, 0xA9, 0x77, 0x8B, 0x9E, 0xAA, 0x04, 0xB0, 0x83, 0x10, 0xE2, 0x15, 0x4D, 0x08,
    0x77, 0xD4, 0x7A, 0x0E, 0x5A, 0xB0, 0xBB, 0x00, 0x61, 0xD7, 0xA6, 0x75, 0xDF, 0x06, 0x64, 0x88,
    0xBB, 0xB9, 0xCA, 0xB0, 0x18, 0x8B, 0x54, 0x13, 0xE2, 0xCB, 0x33, 0xDF, 0x17, 0xD8, 0xDA, 0xA9,
    0xA5, 0x60, 0xA3, 0x1F, 0x4E, 0x27, 0x05, 0x98, 0x6F, 0xAA, 0xEE, 0x14, 0x3B, 0xF3, 0x97, 0xA8,
    0x12, 0x02, 0x94, 0x0D, 0x84, 0xDC, 0x0E, 0xF1, 0x76, 0x23, 0x95, 0x36, 0x13, 0xF9, 0xA9, 0xC5,
    0x48, 0xDB, 0xDA, 0x86, 0xBE, 0x29, 0x22, 0x54, 0x44, 0x9D, 0x9F, 0x80, 0x7B, 0x07, 0x80, 0x30,
    0xEA, 0xD2, 0x83, 0xCC, 0xCE, 0x37, 0xD1, 0xD1, 0xCF, 0x85, 0xBE, 0x91, 0x25, 0xCE, 0xC0, 0xCC,
    0x55, 0xC8, 0xC0, 0xFB, 0x38, 0xC5, 0x49, 0x03, 0x6A, 0x02, 0xA9, 0x9F, 0x9F, 0x86, 0xFB, 0xC7,
    0xCB, 0xC6, 0xA5, 0x82, 0xA2, 0x30, 0xC2, 0xAC, 0xE6, 0x98, 0xDA, 0x83, 0x64, 0x43, 0x7F, 0x0D,
    0x13, 0x18, 0xEB, 0x90, 0x53, 0x5B, 0x37, 0x6B, 0xE6, 0x0D, 0x80, 0x1E, 0xEF, 0xED, 0xC7, 0xB8,
    0x68, 0x9B, 0x4C, 0x09, 0x7B, 0x60, 0xB2, 0x57, 0xD8, 0x59, 0x8D, 0x7F, 0xEA, 0xCD, 0xEB, 0xC4,
    0x60, 0x9F, 0x45, 0x7A, 0xA9, 0x26, 0x8A, 0x2F, 0x85, 0x0C, 0xF2, 0x19, 0xC6, 0x53, 0x92, 0xF7,
    0xF0, 0xB8, 0x32, 0xCB, 0x5B, 0x66, 0xCE, 0x51, 0x54, 0xB4, 0xC3, 0xD3, 0xD4, 0xDC, 0xB3, 0xEE
};

uint8 const Exponent[] = { 0x01, 0x00, 0x01, 0x00 };

uint8 const D[] =
{
    0x79, 0x16, 0xC0, 0xDB, 0xF2, 0x31, 0xCE, 0xA7, 0xEB, 0xFB, 0x91, 0x1F, 0x1E, 0x72, 0x70, 0x25,
    0x0B, 0xF5, 0x7A, 0xE0, 0x88, 0x0B, 0x79, 0xBD, 0xFF, 0xBA, 0x24, 0x62, 0x5A, 0x08, 0x59, 0x2B,
    0x41, 0x7E, 0x4B, 0xF4, 0x9C, 0x3D, 0x4B, 0x5C, 0xEA, 0x6B, 0x21, 0xB8, 0x6E, 0x1C, 0xD1, 0x30,
    0x3E, 0x7C, 0x9C, 0x74, 0xA9, 0x9F, 0x77, 0x31, 0x28, 0xAE, 0x0C, 0x65, 0x18, 0xFF, 0x32, 0x63,
    0x06, 0xD9, 0x33, 0x03, 0xEA, 0x31, 0x26, 0x06, 0x2E, 0xF9, 0x20, 0x81, 0x07, 0xEB, 0x04, 0x42,
    0x22, 0x31, 0x5C, 0x7D, 0x6E, 0x5B, 0x04, 0xF0, 0xBB, 0x4E, 0xF6, 0xB5, 0x9B, 0x96, 0x56, 0xBD,
    0x4C, 0x0E, 0x79, 0xF4, 0x8F, 0x8F, 0xF1, 0xEA, 0x35, 0x5C, 0x98, 0x23, 0x29, 0xA7, 0x7C, 0xAC,
    0xF5, 0xD3, 0x50, 0x2D, 0xDA, 0xB3, 0x5A, 0x34, 0x33, 0x4D, 0x02, 0x9E, 0x39, 0xAD, 0x52, 0x9B,
    0xCE, 0x78, 0xAD, 0x6F, 0x65, 0xD4, 0x81, 0xA3, 0x64, 0x0D, 0x6B, 0x96, 0x29, 0x1C, 0x6C, 0xE3,
    0x1D, 0xDA, 0x4C, 0x5E, 0xAF, 0xD7, 0x14, 0x2A, 0xC9, 0x07, 0x23, 0x04, 0x2F, 0xC4, 0x73, 0x4B,
    0xDC, 0xCC, 0xEE, 0x94, 0xE8, 0xFE, 0xF3, 0x09, 0x88, 0x8E, 0xF6, 0xF4, 0x31, 0x5D, 0xC1, 0xA4,
    0x3B, 0x54, 0x47, 0x6E, 0x03, 0x91, 0x03, 0x12, 0x16, 0x97, 0xC6, 0xF0, 0xAA, 0x38, 0x7D, 0xB3,
    0x9E, 0xC7, 0x7D, 0x9D, 0xEB, 0xCE, 0x8C, 0x56, 0x0C, 0x8A, 0x77, 0x6C, 0x07, 0x17, 0x02, 0xBD,
    0x8F, 0x00, 0x94, 0x1F, 0xB4, 0x96, 0x72, 0x20, 0xBC, 0x51, 0x43, 0x8F, 0xBC, 0xA8, 0xBC, 0xBA,
    0xAF, 0x4F, 0x3C, 0x9A, 0xA2, 0x45, 0x9A, 0x14, 0x5B, 0x96, 0xDF, 0x55, 0x51, 0xC9, 0x5D, 0x68,
    0xB6, 0x5E, 0xC3, 0xFA, 0x00, 0xE2, 0x2B, 0x37, 0x34, 0x66, 0x07, 0xE0, 0xAF, 0xE6, 0x9A, 0x22
};
*/

uint8 const P[] =
{
    0x7D, 0xBD, 0xB9, 0xE1, 0x2D, 0xAE, 0x42, 0x56, 0x6E, 0x2B, 0xE2, 0x89, 0xD9, 0xBB, 0x0C, 0x1F,
    0x67, 0x28, 0xC1, 0x4D, 0x91, 0x3C, 0xAD, 0x5F, 0xF0, 0x43, 0x86, 0x5C, 0x27, 0xDC, 0x58, 0xB3,
    0x0E, 0x75, 0x77, 0x78, 0x49, 0x35, 0xE7, 0xE7, 0xDF, 0xFD, 0x74, 0xAB, 0x4E, 0xFE, 0xD3, 0xAB,
    0x6B, 0x96, 0xF7, 0x89, 0xB2, 0x5A, 0x6A, 0x25, 0x03, 0x5A, 0x92, 0x1A, 0xF1, 0xFC, 0x05, 0x4E,
    0xCE, 0xDD, 0x37, 0xA4, 0x02, 0x53, 0x76, 0xCB, 0xC2, 0xD9, 0x63, 0xCB, 0x51, 0x94, 0xEC, 0x5C,
    0x39, 0xCC, 0xB2, 0x17, 0x0C, 0xA3, 0x43, 0x9A, 0xD0, 0x83, 0x27, 0x67, 0x52, 0x64, 0x37, 0x0E,
    0x38, 0xB7, 0x9B, 0xF4, 0x2D, 0xB8, 0x0F, 0x30, 0x72, 0xD3, 0x15, 0xF3, 0x2C, 0x39, 0x55, 0x72,
    0x2C, 0x55, 0x80, 0x63, 0xA0, 0xA1, 0x6F, 0x28, 0xF3, 0xF3, 0x5A, 0x6F, 0x68, 0x59, 0xB3, 0xF3
};

uint8 const Q[] =
{
    0x0B, 0x1A, 0x13, 0x07, 0x12, 0xEF, 0xDD, 0x97, 0x01, 0x9A, 0x21, 0x7D, 0xFA, 0xA3, 0xB7, 0xE2,
    0x39, 0x2E, 0x04, 0x92, 0x96, 0x45, 0x2A, 0xEB, 0x57, 0x03, 0xAC, 0xB1, 0x83, 0xCD, 0x25, 0x4F,
    0x2C, 0xA9, 0xA1, 0x54, 0x26, 0x54, 0xCF, 0xE6, 0x1B, 0x53, 0x51, 0x3A, 0xC1, 0x15, 0xF4, 0x17,
    0xBB, 0x17, 0x1F, 0x37, 0x66, 0x36, 0x1A, 0xD4, 0xB1, 0x5B, 0x49, 0xA8, 0xF1, 0x02, 0xB0, 0x42,
    0xA9, 0x66, 0xA0, 0xE2, 0x52, 0x2C, 0x8C, 0x89, 0xA2, 0xDD, 0xA6, 0xF1, 0xA3, 0xDF, 0xB6, 0x80,
    0x63, 0xB8, 0x10, 0xDA, 0xDE, 0x84, 0x56, 0xFA, 0xFB, 0x72, 0x65, 0x5E, 0xA3, 0x9C, 0x78, 0x65,
    0xD0, 0x73, 0x07, 0x34, 0x1D, 0xE1, 0x4D, 0x77, 0xE8, 0x00, 0x0F, 0x80, 0x1C, 0x5A, 0x21, 0x55,
    0x0A, 0x8C, 0xF4, 0x93, 0xF5, 0xF8, 0x40, 0xF2, 0x40, 0xEA, 0x52, 0x12, 0x40, 0xF0, 0xBF, 0xFA
};

uint8 const DP[] =
{
    0xE1, 0xA6, 0x22, 0xAB, 0xFF, 0x57, 0x83, 0x45, 0x3F, 0x93, 0x76, 0xC8, 0xFA, 0xD9, 0x17, 0xE1,
    0x49, 0x73, 0xC2, 0x13, 0x28, 0x0B, 0x1F, 0xE2, 0x9A, 0xF4, 0x7F, 0x7C, 0x37, 0x56, 0xA1, 0xDF,
    0x51, 0x97, 0x2F, 0x15, 0x10, 0x97, 0xCD, 0x2A, 0x40, 0x09, 0xFC, 0x0A, 0xC3, 0x3F, 0x88, 0x86,
    0xA9, 0x51, 0x13, 0xE1, 0x76, 0xCF, 0xA8, 0x37, 0x9A, 0x91, 0x3B, 0xD0, 0x70, 0xA1, 0xD7, 0x03,
    0x71, 0x59, 0x6C, 0xB3, 0x41, 0xB8, 0x32, 0x68, 0x56, 0xC8, 0xB8, 0xD1, 0xF9, 0x1D, 0x04, 0xC5,
    0x13, 0xB5, 0x8E, 0x57, 0x73, 0x02, 0x97, 0x7B, 0x33, 0x60, 0x68, 0xA9, 0xC2, 0x40, 0x96, 0x3C,
    0x57, 0x4E, 0x4F, 0xC0, 0xAB, 0x21, 0x5C, 0xBA, 0x7D, 0x65, 0xAA, 0x1B, 0xD6, 0x43, 0x06, 0xCE,
    0x3E, 0x0C, 0xB9, 0xB2, 0x82, 0xB0, 0xC9, 0x54, 0x59, 0x32, 0xC5, 0x88, 0x08, 0x9C, 0x9B, 0xBF
};

uint8 const DQ[] =
{
    0xE3, 0xB1, 0xED, 0x52, 0xEF, 0xE6, 0x88, 0x40, 0x50, 0x89, 0x4C, 0x99, 0xE5, 0xF7, 0xED, 0x03,
    0x1C, 0x54, 0x11, 0x24, 0x2F, 0x9D, 0xE8, 0xE6, 0x39, 0xFA, 0x19, 0xF4, 0x06, 0x55, 0x0B, 0x8B,
    0x95, 0xC8, 0xB1, 0xE2, 0x7C, 0x75, 0x3B, 0x2A, 0x40, 0xC3, 0xE7, 0xE0, 0x25, 0x18, 0xBF, 0xB5,
    0x03, 0x1B, 0x5A, 0x57, 0x92, 0x3C, 0x85, 0x7D, 0x7F, 0x43, 0x56, 0x1F, 0x1E, 0x80, 0xC3, 0xBA,
    0xF0, 0x53, 0xD7, 0x6A, 0xD0, 0xF2, 0xDD, 0x9C, 0xC6, 0x53, 0xE7, 0xB4, 0xD3, 0x9D, 0xAB, 0xBF,
    0xE0, 0x97, 0x50, 0x92, 0x23, 0xB9, 0xB7, 0xDC, 0xAA, 0xC4, 0x20, 0x93, 0x5A, 0xF5, 0xDE, 0x76,
    0x28, 0x93, 0x91, 0x44, 0x1E, 0x4C, 0x15, 0x2F, 0x7F, 0x45, 0x3C, 0x3B, 0x7D, 0x36, 0x3B, 0x24,
    0xC7, 0x8C, 0x65, 0x43, 0xAE, 0x65, 0x84, 0xBC, 0xF9, 0x76, 0x4E, 0x3C, 0x44, 0x05, 0xBC, 0xFA
};

uint8 const InverseQ[] =
{
    0x63, 0xC1, 0x14, 0x2B, 0x57, 0x0B, 0x8A, 0x3C, 0x27, 0xDB, 0x96, 0x82, 0x27, 0xEB, 0xF6, 0x45,
    0x6D, 0x07, 0x50, 0xE8, 0x4A, 0xD4, 0xB6, 0x7A, 0x3C, 0x8B, 0x4D, 0x65, 0xF0, 0x50, 0x70, 0x84,
    0x71, 0x2B, 0xC6, 0x6D, 0x28, 0x2D, 0x76, 0x38, 0x73, 0x93, 0xDB, 0x44, 0xD7, 0xC0, 0x7F, 0xD9,
    0x57, 0x18, 0x28, 0x57, 0xF1, 0x13, 0x38, 0xA4, 0x91, 0x67, 0x1E, 0x13, 0x73, 0x55, 0xFC, 0x7B,
    0xAF, 0x50, 0xFA, 0xFD, 0x16, 0x12, 0x6F, 0xA4, 0x95, 0x15, 0x9C, 0x07, 0x18, 0xA6, 0x46, 0xFD,
    0xB3, 0xCF, 0xA5, 0x0E, 0x05, 0x30, 0xEC, 0x2C, 0xCD, 0x62, 0xDD, 0x6F, 0xB1, 0xFE, 0x6C, 0x05,
    0x2F, 0x11, 0xA6, 0xA0, 0x98, 0xAC, 0x9B, 0x15, 0xF0, 0x04, 0xC4, 0x7B, 0x79, 0xAA, 0x51, 0x25,
    0x2A, 0x84, 0x73, 0xE6, 0x77, 0x47, 0xA3, 0xEB, 0xCF, 0x6D, 0xC8, 0x96, 0x3A, 0x1B, 0x02, 0x52
};

uint8 const WherePacketHmac[] =
{
    0x2C, 0x1F, 0x1D, 0x80, 0xC3, 0x8C, 0x23, 0x64, 0xDA, 0x90, 0xCA, 0x8E, 0x2C, 0xFC, 0x0C, 0xCE,
    0x09, 0xD3, 0x62, 0xF9, 0xF3, 0x8B, 0xBE, 0x9F, 0x19, 0xEF, 0x58, 0xA1, 0x1C, 0x34, 0x14, 0x41,
    0x3F, 0x23, 0xFD, 0xD3, 0xE8, 0x14, 0xEC, 0x2A, 0xFD, 0x4F, 0x95, 0xBA, 0x30, 0x7E, 0x56, 0x5D,
    0x83, 0x95, 0x81, 0x69, 0xB0, 0x5A, 0xB4, 0x9D, 0xA8, 0x55, 0xFF, 0xFC, 0xEE, 0x58, 0x0A, 0x2F
};

WorldPackets::Auth::ConnectTo::ConnectTo() : ServerPacket(SMSG_CONNECT_TO, 8 + 4 + 256 + 1)
{
    HexStrToByteArray("F41DCB2D728CF3337A4FF338FA89DB01BBBE9C3B65E9DA96268687353E48B94C", Payload.PanamaKey);
    Payload.Adler32 = 0xA0A66C10;

    p.SetBinary(P, 128);
    q.SetBinary(Q, 128);
    dmp1.SetBinary(DP, 128);
    dmq1.SetBinary(DQ, 128);
    iqmp.SetBinary(InverseQ, 128);
}

WorldPacket const* WorldPackets::Auth::ConnectTo::Write()
{
    ByteBuffer payload;
    uint16 port = Payload.Where.port();
    uint8 address[16] = { 0 };
    uint8 addressType = 3;
    if (Payload.Where.address().is_v4())
    {
        memcpy(address, Payload.Where.address().to_v4().to_bytes().data(), 4);
        addressType = 1;
    }
    else
    {
        memcpy(address, Payload.Where.address().to_v6().to_bytes().data(), 16);
        addressType = 2;
    }

    HmacSha1 hmacHash(64, WherePacketHmac);
    hmacHash.UpdateData(address, 16);
    hmacHash.UpdateData(&addressType, 1);
    hmacHash.UpdateData((uint8* const)&port, 2);
    hmacHash.UpdateData((uint8* const)Haiku.c_str(), 71);
    hmacHash.UpdateData(Payload.PanamaKey, 32);
    hmacHash.UpdateData(PiDigits, 108);
    hmacHash.UpdateData(&Payload.XorMagic, 1);
    hmacHash.Finalize();

    payload << uint32(Payload.Adler32);
    payload << uint8(addressType);
    payload.append(address, 16);
    payload << uint16(port);
    payload.append(Haiku.data(), 71);
    payload.append(Payload.PanamaKey, 32);
    payload.append(PiDigits, 108);
    payload << uint8(Payload.XorMagic);
    payload.append(hmacHash.GetDigest(), hmacHash.GetLength());

    BigNumber bnData;
    bnData.SetBinary(payload.contents(), payload.size());

    BigNumber m1 = (bnData % p).ModExp(dmp1, p);
    BigNumber m2 = (bnData % q).ModExp(dmq1, q);
    BigNumber h = (iqmp * (m1 - m2)) % p;
    // Be sure to use the positive remainder
    if (h.IsNegative())
        h += p;

    BigNumber m = m2 + h * q;

    _worldPacket << uint64(Key);
    _worldPacket << uint32(Serial);
    _worldPacket.append(m.AsByteArray(256).get(), 256);
    _worldPacket << uint8(Con);
    return &_worldPacket;
}

void WorldPackets::Auth::AuthContinuedSession::Read()
{
    _worldPacket >> DosResponse;
    _worldPacket >> Key;
    _worldPacket.read(LocalChallenge.data(), LocalChallenge.size());
    _worldPacket.read(Digest.data(), Digest.size());
}

void WorldPackets::Auth::ConnectToFailed::Read()
{
    Serial = _worldPacket.read<ConnectToSerial>();
    _worldPacket >> Con;
}
