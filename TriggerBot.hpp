#pragma once
struct TriggerBot {
    ConfigLoader* cl;
    MyDisplay* display;
    LocalPlayer* lp;
    std::vector<Player*>* players;
    const float TB_MAX_RANGE_ZOOMED = util::metersToGameUnits(180);
    const float TB_MAX_RANGE_HIPFRE = util::metersToGameUnits(25);

    TriggerBot(ConfigLoader* configLoada, MyDisplay* myDisplay, LocalPlayer* localPlayer, std::vector<Player*>* all_players) {
        this->cl = configLoada;
        this->display = myDisplay;
        this->lp = localPlayer;
        this->players = all_players;
    }

    void shootAtEnemy(int counter) {
        if (!cl->FEATURE_TRIGGERBOT_ON) return;
        if (!lp->isCombatReady()) return;

        //only these weapons will work with trigger bot
        int weaponId = lp->weaponIndex;
        //printf("Last weapon held: [%s] - id: [%d]- GrenadeID: [%d] - Ammo: [%d]\n", WeaponName(weaponId).c_str(), weaponId, lp->grenadeID, lp->ammoInClip);        
        if (
            weaponId != WEAPON_MOZAMBIQUE &&
            weaponId != WEAPON_EVA8 &&
            weaponId != WEAPON_PEACEKEEPER &&
            weaponId != WEAPON_MASTIFF 
            )return;

        //max range changes based on if we are zoomed in or not
        const float RANGE_MAX = (lp->inZoom) ? TB_MAX_RANGE_ZOOMED : TB_MAX_RANGE_HIPFRE;

        for (int i = 0; i < players->size(); i++) {
            Player* p = players->at(i);
            if (!p->isCombatReady()) continue;
            if (!p->enemy) continue;
            if (!p->aimedAt) continue;
            if (p->distanceToLocalPlayer <= RANGE_MAX ) {
                display->mouseClickLeft();
                break;
            }
        }
    }
};
