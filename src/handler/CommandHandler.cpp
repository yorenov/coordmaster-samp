#include <sstream>
#include "game/GameUtil.h"
#include "coord/Coord.h"
#include "util/EncodingUtil.h"
#include "CommandHandler.h"
#include "sampapi/CInput.h"
#include "sampapi/CChat.h"

namespace CommandHandler {
    bool parseParams(const char *param, DWORD &delay, DWORD &forceDelay, float &stepMultiplier) {
        std::string str(param);
        std::istringstream iss(str);
        std::string number;
        int i = 0;

        while (std::getline(iss, number, ':')) {
            try {
                if (i < 2) {
                    size_t pos;
                    int value = std::stoi(number, &pos);
                    if (pos < number.length()) {
                        SendClientMessage("Ошибка: Некорректное число");
                        return false;
                    }
                    if (i == 0) delay = value;
                    else forceDelay = value;
                } else {
                    size_t pos;
                    stepMultiplier = std::stof(number, &pos);
                    if (pos < number.length()) {
                        SendClientMessage("Ошибка: Некорректное число");
                        return false;
                    }
                }
            } catch (std::invalid_argument const &e) {
                SendClientMessage("Ошибка: Некорректный ввод. Это не число.");
                return false;
            } catch (std::out_of_range const &e) {
                SendClientMessage("Ошибка: Число вне диапазона допустимых значений.");
                return false;
            }
            ++i;
        }

        if (i != 3) {
            SendClientMessage("Ошибка: Неверное количество чисел.");
            return false;
        }

        return true;
    }

    void OnCommandCord(const char *args) {
        if (Coord::enabled) {
            GameUtil::GetPlayerVehicle()->Teleport(Coord::currentPoint);
            Coord::enabled = false;
            return SendClientMessage("Выключен");
        }
        sampapi::CVector pos(0, 0, 0);
        if (GameUtil::GetMarkerPosition(&pos)) {
            pos.z += 3;
            if (!GameUtil::IsPlayerInVehicle()) return SendClientMessage("Вы должны быть в авто");
            auto pPed = sampapi::v037r3::RefNetGame()->GetPlayerPool()->GetLocalPlayer();
            Coord::endPoint = sampapi::CVector(pos);
            Coord::currentPoint = sampapi::CVector(pPed->m_onfootData.m_position);
            Coord::enabled = true;
            return SendClientMessage("Включен");
        }
        return SendClientMessage("Поставьте метку");
    }

    bool Init() {
        if (sampapi::v037r3::RefInputBox() == nullptr) return false;

        sampapi::v037r3::RefInputBox()->AddCommand("cord", (sampapi::CMDPROC) OnCommandCord);
        sampapi::v037r3::RefInputBox()->AddCommand("cord_set", [](const char *param) {
            if (std::string(param).empty()) {
                SendClientMessage("Укажите параметры в формате /cord_set delay:forceDelay:stepMultiplier");
            } else {
                if (parseParams(param, Coord::delay, Coord::forceDelay, Coord::stepMultiplier)) {
                    int bufferSize = std::snprintf(nullptr, 0,
                                                   "Указаны числа: delay = %lu, forceDelay = %lu, stepMultiplier = %.2f",
                                                   Coord::delay, Coord::forceDelay, Coord::stepMultiplier) +
                                     1;
                    std::string output(bufferSize, '\0');
                    std::snprintf(&output[0], bufferSize,
                                  "Указаны числа: delay = %lu, forceDelay = %lu, stepMultiplier = %.2f", Coord::delay,
                                  Coord::forceDelay, Coord::stepMultiplier);
                    output.pop_back();
                    SendClientMessage(output);
                }
            }
        });
        return true;
    }

    void SendClientMessage(std::string message) {
        message = "{2CB6DD}[CoordMaster]: {FFFFFF}" + EncodingUtil::ConvertUTF8ToCP1251(message);
        sampapi::v037r3::RefChat()->AddMessage(-1, message.c_str());
    }
}