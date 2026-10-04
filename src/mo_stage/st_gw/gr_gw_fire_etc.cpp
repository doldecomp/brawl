#include <memory.h>
#include <mt/mt_prng.h>

#include <st_gw/gr_gw_fire_etc.h>

namespace {
struct StageData { // Name unknown
    u8 unk0[0x3C];
    float unk3C;
    u8 unk40[4];
    float unk44;
    float unk48;
    float unk4C;
    float unk50;
};
}

grGWFireEtc::grGWFireEtc(const char* taskName) : grGW(taskName) {
    unk174 = nullptr;
    unk1E4 = nullptr;
    unk1E8 = 1;
    memset(&unk180, 0, sizeof(unk180));
    memset(&unk188, 0, sizeof(unk188));
    unk178 = nullptr;
    unk17C = nullptr;
    unk188.unk58 = 0.0f;
}

grGWFireEtc* grGWFireEtc::create(int modelIndex, const char* nodeName, const char* taskName) {
    grGWFireEtc* ground = new (Heaps::StageInstance) grGWFireEtc(taskName);
    if (ground != nullptr) {
        ground->setMdlIndex(modelIndex);
        ground->setTgtNode(nodeName);
    }
    return ground;
}

grGWFireEtc::~grGWFireEtc() {
    clearVictimAll();
}

void grGWFireEtc::update(float deltaFrame) {
    grGW::update(deltaFrame);
    StageData* data = static_cast<StageData*>(getStageData());
    if (data == nullptr) {
        return;
    }
    unk154 -= deltaFrame;
    if (unk154 < 0.0f) {
        unk154 = 0.0f;
    }
    switch (unk150) {
        case STATE_0:
            setMotion(1, false, true, nullptr);
            setVisibility(false);
            setNodeVisibility(false, 0, unk180, true, true);
            clearVictimAll();
            unk174[0] = MISTAKE_11;
            unk174[1] = MISTAKE_11;
            unk174[2] = MISTAKE_11;
            unk1E8 = 1;
            unk150 = STATE_1;
            break;
        case STATE_1:
            if (*unk158 == unk15C) {
                setVisibility(true);
                unk188.unk58 = data->unk44 + (data->unk48 - data->unk44) * randf();
                unk150 = STATE_3;
            }
            break;
        case STATE_2:
            break;
        case STATE_3:
            if (*unk158 != unk15C) {
                setMotion(0, false, true, &unk164);
                if (m_motionRatio < 0.0f) {
                    m_motionRatio *= -1.0f;
                }
                unk150 = STATE_4;
            } else {
                if (*unk1E4 == 0) {
                    updateVictim(deltaFrame);
                } else if (*unk1E4 != unk1E8) {
                    setNodeVisibility(false, 0, unk180, true, true);
                    clearVictimAll();
                    unk174[0] = MISTAKE_11;
                    unk174[1] = MISTAKE_11;
                    unk174[2] = MISTAKE_11;
                }
                unk1E8 = *unk1E4;
            }
            break;
        case STATE_4:
            if (getMotionFrame(0) >= unk164) {
                unk150 = STATE_0;
            }
            break;
    }
}

void grGWFireEtc::updateVictim(float deltaFrame) {
    StageData* data = static_cast<StageData*>(getStageData());
    if (data == nullptr) {
        return;
    }
    unk188.unk58 -= deltaFrame;
    if (unk188.unk58 < 0.0) {
        unk188.unk58 = 0.0f;
    }
    setNodeVisibility(true, 0, unk184, true, false);
    if (unk188.unk58 == 0.0f) {
        if (randf() < data->unk4C) {
            addVictim();
            setNodeVisibility(true, 0, unk188.unk0[0], true, false);
        }
        unk188.unk58 = data->unk44 + (data->unk48 - data->unk44) * randf();
    }
    if (unk178 != nullptr) {
        unk178[0] = 0;
        unk178[1] = 0;
        unk178[2] = 0;
    }
    u32 removed;
    u32 i;
    u32 count;
    nw4r::ut::LinkList<Victim, 0>::Iterator victim;
    victim = unk1EC.GetBeginIter();
    count = unk1EC.GetSize();
    removed = 0;
    for (i = 0; i != count; ++i, ++victim) {
        victim->unkC -= deltaFrame;
        if (victim->unkC < 0.0f) {
            victim->unkC = 0.0f;
        }
        if (victim->unkC == 0.0f) {
            setNodeVisibility(false, 0, unk188.unk0[victim->unk8], true, false);
            if (victim->unk8 == STEP_END) {
                victim->unk8 = STEP_REMOVED;
                ++removed;
            } else {
                u32 previous = removed;
                switch (victim->unk8) {
                    case STEP_4:
                        if (*unk17C == 2) {
                            unk154 = data->unk3C;
                        } else {
                            unk174[2] = MISTAKE_12;
                            victim->unk8 = STEP_REMOVED;
                            ++removed;
                        }
                        break;
                    case STEP_12:
                        if (*unk17C == 1) {
                            unk154 = data->unk3C;
                        } else {
                            unk174[1] = MISTAKE_12;
                            victim->unk8 = STEP_REMOVED;
                            ++removed;
                        }
                        break;
                    case STEP_18:
                        if (*unk17C == 0) {
                            unk154 = data->unk3C;
                        } else {
                            unk174[0] = MISTAKE_12;
                            victim->unk8 = STEP_REMOVED;
                            ++removed;
                        }
                        break;
                }
                if (removed == previous) {
                    ++victim->unk8;
                    victim->unkC = data->unk50;
                    setNodeVisibility(true, 0, unk188.unk0[victim->unk8], true, false);
                }
            }
            switch (victim->unk8) {
                case STEP_3:
                    unk178[2] = 1;
                    break;
                case STEP_4:
                    unk178[2] = 1;
                    break;
                case STEP_11:
                    unk178[1] = 1;
                    break;
                case STEP_12:
                    unk178[1] = 1;
                    break;
                case STEP_17:
                    unk178[0] = 1;
                    break;
                case STEP_18:
                    unk178[0] = 1;
                    break;
            }
        }
    }
    for (u32 i = 0; i != removed; ++i) {
        clearVictim();
    }
}

bool grGWFireEtc::setNode() {
    bool result = grGimmick::setNode();
    unk180 = getNodeIndex(0, "_VICTIM");
    unk184 = getNodeIndex(0, "Victim_02");
    unk188.unk0[0] = getNodeIndex(0, "Victim_01");
    unk188.unk0[1] = getNodeIndex(0, "Victim_03");
    unk188.unk0[2] = getNodeIndex(0, "Victim_04");
    unk188.unk0[3] = getNodeIndex(0, "Victim_05");
    unk188.unk0[4] = getNodeIndex(0, "Victim_06");
    unk188.unk0[5] = getNodeIndex(0, "Victim_07");
    unk188.unk0[6] = getNodeIndex(0, "Victim_08");
    unk188.unk0[7] = getNodeIndex(0, "Victim_09");
    unk188.unk0[8] = getNodeIndex(0, "Victim_10");
    unk188.unk0[9] = getNodeIndex(0, "Victim_11");
    unk188.unk0[10] = getNodeIndex(0, "Victim_12");
    unk188.unk0[11] = getNodeIndex(0, "Victim_13");
    unk188.unk0[12] = getNodeIndex(0, "Victim_14");
    unk188.unk0[13] = getNodeIndex(0, "Victim_15");
    unk188.unk0[14] = getNodeIndex(0, "Victim_16");
    unk188.unk0[15] = getNodeIndex(0, "Victim_17");
    unk188.unk0[16] = getNodeIndex(0, "Victim_18");
    unk188.unk0[17] = getNodeIndex(0, "Victim_19");
    unk188.unk0[18] = getNodeIndex(0, "Victim_20");
    unk188.unk0[19] = getNodeIndex(0, "Victim_21");
    unk188.unk0[20] = getNodeIndex(0, "Victim_22");
    unk188.unk0[21] = getNodeIndex(0, "Victim_23");
    return result;
}

void grGWFireEtc::addVictim() {
    StageData* data = static_cast<StageData*>(getStageData());
    if (data == nullptr) {
        return;
    }
    Victim* victim = new (Heaps::StageInstance) Victim;
    if (victim != nullptr) {
        victim->unk8 = 0;
        victim->unkC = data->unk50;
        unk1EC.PushBack(victim);
    }
}

void grGWFireEtc::clearVictim() {
    Victim* victim = getVictim(STEP_REMOVED);
    if (victim != nullptr) {
        unk1EC.Erase(victim);
        delete victim;
    }
}

void grGWFireEtc::clearVictimAll() {
    u32 i = 0;
    u32 count = unk1EC.GetSize();
    for (; i != count; ++i) {
        Victim* victim = &unk1EC.GetFront();
        unk1EC.Erase(unk1EC.GetBeginIter());
        delete victim;
    }
}

grGWFireEtc::Victim* grGWFireEtc::getVictim(u32 index) {
    u32 count = unk1EC.GetSize();
    nw4r::ut::LinkList<Victim, 0>::Iterator victim = unk1EC.GetBeginIter();
    for (u32 i = 0; i != count; ++i, ++victim) {
        if (index == victim->unk8) {
            return &*victim;
        }
    }
    return nullptr;
}

grGWFireFighter::grGWFireFighter(const char* taskName) : grGW(taskName) {
    unk190 = nullptr;
    unk194 = 1;
    memset(&unk174, 0, sizeof(unk174));
    memset(unk178, 0, sizeof(unk178));
    unk184 = nullptr;
    unk188 = nullptr;
    unk18C = nullptr;
}

grGWFireFighter* grGWFireFighter::create(int modelIndex, const char* nodeName, const char* taskName) {
    grGWFireFighter* ground = new (Heaps::StageInstance) grGWFireFighter(taskName);
    if (ground != nullptr) {
        ground->setMdlIndex(modelIndex);
        ground->setTgtNode(nodeName);
    }
    return ground;
}

grGWFireFighter::~grGWFireFighter() { }

void grGWFireFighter::update(float deltaFrame) {
    grGW::update(deltaFrame);
    StageData* data = static_cast<StageData*>(getStageData());
    if (data == nullptr) {
        return;
    }
    unk154 -= deltaFrame;
    if (unk154 < 0.0f) {
        unk154 = 0.0f;
    }
    switch (unk150) {
        case STATE_0:
            setMotion(1, false, true, nullptr);
            setVisibility(false);
            setNodeVisibility(false, 0, unk174, true, true);
            unk194 = 1;
            unk150 = STATE_1;
            break;
        case STATE_1:
            if (*unk158 == unk15C) {
                setVisibility(true);
                if (*unk188 == 255) {
                    *unk188 = 0;
                }
                unk154 = data->unk3C;
                unk150 = STATE_3;
            }
            break;
        case STATE_2:
            break;
        case STATE_3:
            if (*unk158 != unk15C) {
                setMotion(0, false, true, &unk164);
                if (m_motionRatio < 0.0f) {
                    m_motionRatio *= -1.0f;
                }
                unk150 = STATE_4;
            } else {
                if (*unk190 == 0) {
                    updateFighter(deltaFrame);
                } else if (*unk190 != unk194) {
                    setNodeVisibility(false, 0, unk174, true, true);
                }
                getNodePosition(unk184, 0, unk178[*unk188]);
                unk194 = *unk190;
            }
            break;
        case STATE_4:
            if (getMotionFrame(0) >= unk164) {
                unk150 = STATE_0;
            }
            break;
    }
}

void grGWFireFighter::updateFighter(float deltaFrame) {
    StageData* data = static_cast<StageData*>(getStageData());
    if (data == nullptr) {
        return;
    }
    unk154 -= deltaFrame;
    if (unk154 < 0.0f) {
        unk154 = 0.0f;
    }
    if (unk154 == 0.0f) {
        float random = randf();
        setNodeVisibility(false, 0, unk178[*unk188], true, false);
        switch (*unk188) {
            case 0:
                if (unk18C[0] == 1) {
                    if (random < 0.8f) {
                        *unk188 = 0;
                    } else {
                        *unk188 = 1;
                    }
                } else if (unk18C[1] == 1) {
                    if (random < 0.8f) {
                        *unk188 = 1;
                    } else {
                        *unk188 = 0;
                    }
                } else {
                    if (random < 0.5f) {
                        *unk188 = 1;
                    } else {
                        *unk188 = 0;
                    }
                }
                break;
            case 1:
                if (unk18C[1] == 1) {
                    if (random < 0.8f) {
                        *unk188 = 1;
                    } else if (random < 0.9f) {
                        *unk188 = 0;
                    } else {
                        *unk188 = 2;
                    }
                } else if (unk18C[0] == 1) {
                    if (random < 0.8f) {
                        *unk188 = 0;
                    } else if (random < 0.9f) {
                        *unk188 = 1;
                    } else {
                        *unk188 = 2;
                    }
                } else if (unk18C[2] == 1) {
                    if (random < 0.8f) {
                        *unk188 = 0;
                    } else if (random < 0.9f) {
                        *unk188 = 1;
                    } else {
                        *unk188 = 2;
                    }
                } else {
                    if (random < 1.0f / 3.0f) {
                        *unk188 = 0;
                    } else if (random < 2.0f / 3.0f) {
                        *unk188 = 2;
                    } else {
                        *unk188 = 1;
                    }
                }
                break;
            case 2:
                if (unk18C[2] == 1) {
                    if (random < 0.8f) {
                        *unk188 = 2;
                    } else {
                        *unk188 = 1;
                    }
                } else if (unk18C[1] == 1) {
                    if (random < 0.8f) {
                        *unk188 = 1;
                    } else {
                        *unk188 = 2;
                    }
                } else {
                    if (random < 0.5f) {
                        *unk188 = 1;
                    } else {
                        *unk188 = 2;
                    }
                }
                break;
        }
        unk154 = data->unk3C;
    }
    setNodeVisibility(true, 0, unk178[*unk188], true, false);
}

bool grGWFireFighter::setNode() {
    bool result = grGimmick::setNode();
    unk174 = getNodeIndex(0, "_FIREFIGHTER");
    unk178[0] = getNodeIndex(0, "Firefighter_01");
    unk178[1] = getNodeIndex(0, "Firefighter_02");
    unk178[2] = getNodeIndex(0, "Firefighter_03");
    return result;
}
