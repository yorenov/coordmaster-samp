#include "dllmain.h"
#include "coord/Coord.h"
#include "PackerHandler.h"
#include "sampapi/Synchronization.h"

namespace PacketHandler {

	inline bool OnOutcomingPacket(RakNet::BitStream* bs, PacketPriority& priority, PacketReliability& reliability, char& orderingChanel) {
		
		uint8_t packetId;

		bs->ResetReadPointer();
		bs->Read(packetId);
		if (Coord::enabled) {
			
			switch (packetId) {
				case 200: {
					sampapi::v037r3::Synchronization::IncarData data;
					memset(&data, 0, sizeof(sampapi::v037r3::Synchronization::IncarData));
					bs->Read((PCHAR)&data, sizeof(sampapi::v037r3::Synchronization::IncarData));
					data.m_position = Coord::currentPoint;
					data.m_speed = sampapi::CVector(Coord::speed[0], Coord::speed[1], Coord::speed[2]);
                    //тут немного криво сделано Coord::speed[2]. Там надо короче если ниже мы конечной метки то 0.1f, если выше то -0.1f
					bs->ResetWritePointer();
					bs->Write(packetId);
					bs->Write((PCHAR)&data, sizeof(sampapi::v037r3::Synchronization::IncarData));
					break;
				}
				case 209: {
					sampapi::v037r3::Synchronization::UnoccupiedData data;
					memset(&data, 0, sizeof(sampapi::v037r3::Synchronization::UnoccupiedData));
					bs->Read((PCHAR)&data, sizeof(sampapi::v037r3::Synchronization::UnoccupiedData));
					data.m_position = Coord::currentPoint;
					bs->ResetWritePointer();
					bs->Write(packetId);
					bs->Write((PCHAR)&data, sizeof(sampapi::v037r3::Synchronization::UnoccupiedData));
					break;
				}
				case 211: {
					sampapi::v037r3::Synchronization::PassengerData data;
					memset(&data, 0, sizeof(sampapi::v037r3::Synchronization::PassengerData));
					bs->Read((PCHAR)&data, sizeof(sampapi::v037r3::Synchronization::PassengerData));
					data.m_position = Coord::currentPoint;
					bs->ResetWritePointer();
					bs->Write(packetId);
					bs->Write((PCHAR)&data, sizeof(sampapi::v037r3::Synchronization::PassengerData));
					break;
				}
                default: break;
			}
		}

		bs->ResetReadPointer();

		return true;
	}

	bool Init() {
		if (!rakhook::initialize())
			return false;
		rakhook::on_send_packet += OnOutcomingPacket;
		return true;
	}

}