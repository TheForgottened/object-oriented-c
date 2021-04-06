#include "World.h"

#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <string.h>

void endGame_World(World* this) {
    int points;
    size_t size = 0, used;
    char* str = NULL;

    if (this->emp.getNTerr(&this->emp) == 0) {
        size = (strlen("The empire's out of territories, you lost everything. Therefore, you end the game with 0 points.")
                + 1) * sizeof(char); // '\0'

        str = malloc(size);
        snprintf(str, size, "The empire's out of territories, you lost everything. Therefore, you end the game with 0 points.");

    } else {
        points = this->emp.getSumPointsTerr(&this->emp) + this->emp.getSumPointsTech(&this->emp);

        size = (strlen("The game ended.\n\nTerritories: + points\nTechnologies: + points\n\nFinal score: ")
                + 21) * sizeof(char); // 2 numbers and '\0'

        if (this->emp.getNTech(&this->emp) >= NR_TECHNOLOGIES) {
            size += (strlen("\nScientific bonus (own all technologies): +1 point")) * sizeof(char);
            points += 1;
        }

        if (this->getNTerr(this) == this->emp.getNTerr(&this->emp)) {
            size += (strlen("\nSupreme Emperor: +3 points")) * sizeof(char);
            points += 3;
        }

        str = malloc(size);

        if (str == NULL) {
            fprintf(stderr, "Error allocating memory for a string.");
            return;
        }

        used = snprintf(str, size, "The game ended.\n\nTerritories: +%i points\nTechnologies: +%i points", this->emp.getSumPointsTerr(&this->emp), this->emp.getSumPointsTech(&this->emp));

        if (this->emp.getNTech(&this->emp) >= NR_TECHNOLOGIES) {
            strcat(str, "\nScientific bonus (own all technologies): +1 point");
        }

        if (this->getNTerr(this) == this->emp.getNTerr(&this->emp)) {
            strcat(str, "\nSupreme Emperor: +3 points");
        }
        printf("\n\nbruh: %s\nacabou\n\n", str);
        snprintf(str + used, size - used, "\n\nFinal score: %i", points);
    }  

    this->infoEndGame(this, str);
    free(str);
}

void abandonedResource_World(World* this) {
    errcode code;

    printf("EVENT: Abandoned Resource\n");
    printf("An abandoned resource was found and it gives the empire one unit of ");

    if (this->round <= 6) { // First year
        printf("product");
        code = this->emp.addProduct(&this->emp, 1);

        if (code == IMP_TOO_MUCH_PROD) {
            printf(", but it was wasted because %s", codeToString(IMP_CANT_TAKE_PROD));
        }

        printf(".");
    } else {
        printf("ouro");
        code = this->emp.addGold(&this->emp, 1);

        if (code == IMP_TOO_MUCH_PROD) {
            printf(", but it was wasted because %s", codeToString(IMP_CANT_TAKE_OURO));
        }

        printf(".");
    }
}

void invasion_World(World* this) {
    int force, resistance, luck;
    Territory* terr = this->emp.getLastConquered(&this->emp);

    printf("EVENT: Invasion\n");
    printf("A foreign empire, with a military force of ");

    if (this->round <= 6) {
        force = 2;
    } else {
        force = 3;
    }

    printf("%i, is trying to conquer ", force);

    resistance = terr->getResistance(terr);
    printf("%s, with a resistance of %i", terr->getName(terr), resistance);
    
    if (this->emp.hasTech(&this->emp, "Territorial Defenses")) {
        printf(" + 1 (Territorial Defenses)");
        resistance++;
    }

    luck = rand() % 6 + 1;
    printf(". In battle, the foreign empire got a luck factor of %i, attacking with a force of %i. ", luck, luck + force);

    if (luck + force < resistance) {
        printf("Because your territory's resistance was superior, the invasion failed.");
    } else {
        this->emp.rmTerrStr(&this->emp, terr->getName(terr));
        printf("Because the attack was stronger than your defense, the invasion was successful was you lost the territory.");
    }
}

void diplomaticAlliance_World(World* this) {
    errcode code;

    printf("EVENT: Diplomatic Alliance\n");
    printf("You signed a truece with a foreign empire. Because of that, your receive 1 military unit");

    code = this->emp.addForce(&this->emp, 1);

    if (code == IMP_TOO_MUCH_FORCA) {
        printf(", but it was wasted because %s", codeToString(IMP_CANT_TAKE_FORCA));
    }

    printf(".");
}

#if DEBUG
void forceEndGame_World(World* this) {
    this->endGame(this);
}

void modifyGoldEmp_World(World* this, int x) {
    this->emp.setGold(&this->emp, x);
}

void modifyProductEmp_World(World* this, int x) {
    this->emp.setProd(&this->emp, x);
}

errcode giveTech_World(World* this, char* t) {
    int i;

    for (i = 0; i < NR_TECHNOLOGIES; i++) {
        if (strcmp(this->technologies[i].getName(&this->technologies[i]), t) == 0) {
            return this->emp.forceAddTech(&this->emp, &this->technologies[i]);
        }
    }

    return TEC_DOESNT_EXIST;
}

errcode giveTerr_World(World* this, char* t) {
    int i;

    for (i = 0; i < this->nrTerritories; i++) {
        if (strcmp(this->territories[i]->getName(this->territories[i]), t) == 0) {
            return this->emp.addTerr(&this->emp, this->territories[i]);
        }
    }

    return TERR_NOT_FOUND;
}

errcode chooseEvent_World(World* this, char* eventName) {
    int i;

    if (strcmp(eventName, "") == 0) {
        return this->doEvent(this, -1);
    } else {
        for (i = 0; i < 4; i++) {
            if (strcmp(this->events[i], eventName) == 0) {
                return this->doEvent(this, i);
            }
        }
    }

    return EVNT_NOT_FOUND;
}

errcode doEvent_World(World* this, int e) {
    int rnd;

    if (e == -1) {
        rnd = rand() % 4;
    } else {
        rnd = e;
    }
#else
errcode doEvent_World(World* this, int e) {
    int rnd = rand() % 4;
#endif
    switch (rnd) {
        case 0: // No Event
            printf("Nothing special happened. Everyone can sleep peacefully.");
            break;

        case 1: // Abandoned Resource
            this->abandonedResource(this);
            break;

        case 2: // Invasion
            this->invasion(this);

            if (this->emp.getNTerr(&this->emp) == 0) {
                this->endGame(this);
                return FIM_JOGO;
            }
            break;

        case 3: // Diplomatic Alliance
            this->diplomaticAlliance(this);
            break;

        default:
            return UNEXPECTED;
    }

    return OK;
}

int getRound_World(World* this) {
    return this->round;
}

errcode nextRound_World(World* this) {
    int i;

    (this->round)++;

    if (this->round >= 13) {
        this->endGame(this);
        return FIM_JOGO;
    }

    for (i = 0; i < this->nrTerritories; i++) {
        this->territories[i]->refresh(this->territories[i], this->round);
    }

    return OK;
}

void infoEndGame_World(World* this, char* str) {
    size_t size;
    static char* info = NULL;

    if (info == NULL) {
        size = (strlen(str)
                + 1) * sizeof(char); // '\0'

        info = NULL;
        info = malloc(size);

        if (info == NULL) {
            fprintf(stderr, "Error allocating memory for a string.");
            return;
        }

        strcpy(info, str);
        return;
    }

    printf("%s", info);
}

errcode conquer_World(World* this, char* tName, int* luck) {
    int i;

    for (i = 0; i < this->nrTerritories; i++) {
        if(strcmp(this->territories[i]->getName(this->territories[i]), tName) == 0) {
            if (this->territories[i]->getPoints(this->territories[i]) == 3 && !this->emp.hasTech(&this->emp, "Teleguided Missiles")) {
                return IMP_NO_REQUIRED_TEC;
            }

            *luck = rand() % 6 + 1;

            if (this->territories[i]->getResistance(this->territories[i]) <= this->emp.getForce(&this->emp) + *luck) {
                this->emp.addTerr(&this->emp, this->territories[i]);
                return OK;
            } else if (this->territories[i]->getResistance(this->territories[i]) <=this->emp.getForce(&this->emp) + 6) {
                this->emp.loseForce(&this->emp);
                return IMP_NOT_ENOUGH_LUCK;
            } else {
                this->emp.loseForce(&this->emp);
                return IMP_NOT_ENOUGH_POWER;
            }
        }
    }

    return TERR_NOT_FOUND;
}

errcode create_World(World* this, char* t, int n) {
    int i;
    Territory** temp = NULL;

    if (n == 0) {
        return CMD_NO_NEW_TERRITORIES;
    }

    temp = realloc(this->territories, (this->nrTerritories + n) * sizeof(Territory *));

    if (temp == NULL) {
        fprintf(stderr, "Error allocating memory for territories* array.");
        return UNEXPECTED;
    }

    this->territories = temp;

    for (i = 0; i < n; i++) {
        if (strcmp(t, "castle") == 0) {
            this->territories[(this->nrTerritories)++] = newCastle();
        } else if (strcmp(t, "dune") == 0) {
            this->territories[(this->nrTerritories)++] = newDune();
        } else if (strcmp(t, "fort") == 0) {
            this->territories[(this->nrTerritories)++] = newFort();
        } else if (strcmp(t, "mine") == 0) {
            this->territories[(this->nrTerritories)++] = newMine();
        } else if (strcmp(t, "mountain") == 0) {
            this->territories[(this->nrTerritories)++] = newMountain();
        } else if (strcmp(t, "fishery") == 0) {
            this->territories[(this->nrTerritories)++] = newFishery();
        } else if (strcmp(t, "plain") == 0) {
            this->territories[(this->nrTerritories)++] = newPlain();
        } else if (strcmp(t, "refuge") == 0) {
            this->territories[(this->nrTerritories)++] = newRefuge();
        } else if (strcmp(t, "initialterr") == 0) {
            this->territories[(this->nrTerritories)++] = newInitialTerr();
        } else {
            return TERR_TYPE_UNKNOWN;
        }
    }

    return OK;
}

errcode acquire_World(World* this, char* tech) {
    int i;

    for (i = 0; i < NR_TECHNOLOGIES; i++) {
        if (strcmp(this->technologies[i].getName(&this->technologies[i]), tech) == 0) {
            return this->emp.addTech(&this->emp, &this->technologies[i]);
        }
    }

    return TEC_DOESNT_EXIST;
}

errcode gather_World(World* this) {
    return this->emp.gather(&this->emp);
}

bool hasTechTradeEmp_World(World* this) {
    return this->emp.hasTech(&this->emp, "Stock Exchange");
}

errcode tradeGoldEmp_World(World* this) {
    return this->emp.trade(&this->emp, 0);
}

errcode tradeProdEmp_World(World* this) {
    return this->emp.trade(&this->emp, 1);
}

errcode tradeMilitaryEmp_World(World* this) {
    return this->emp.trade(&this->emp, 2);
}

int getNTerr_World(World* this) {
    return this->nrTerritories;
}

int getForceEmp_World(World* this) {
    return this->emp.getForce(&this->emp);
}

int getSafeEmp_World(World* this) {
    return this->emp.getSafe(&this->emp);
}

int getWarehouseEmp_World(World* this) {
    return this->emp.getWarehouse(&this->emp);
}

errcode printTerrInfo_World(World* this, char* tName) {
    int i;

    for (i = 0; i < this->nrTerritories; i++) {
        if (strcmp(this->territories[i]->getName(this->territories[i]), tName)) {
            this->territories[i]->print(this->territories[i]);
            return OK;
        }
    }

    printf("%s", codeToString(TERR_NOT_FOUND));
    return TERR_NOT_FOUND;
}

void printFreeTerr_World(World* this) {
    int i;
    
    for (i = 0; i < this->nrTerritories; i++) {
        if (this->territories[i]->isConquered(this->territories[i]) == false) {
            putchar('\n');
            this->territories[i]->print(this->territories[i]);
        }
    }
}

void printAvailableTech_World(World* this) {
    int i;

    for (i = 0; i < NR_TECHNOLOGIES; i++) {
        if (!this->emp.hasTech(&this->emp, this->technologies[i].getName(&this->technologies[i]))) {
            putchar('\n');
            this->technologies[i].print(&this->technologies[i]);
            putchar('\n');
        }
    }
}

void print_World(World* this) {
    printf("Unconquered territories: %i", this->nrTerritories - this->emp.getNTerr(&this->emp));
    this->printFreeTerr(this);
    putchar('\n');
    printf("\nEmpire: \n");
    this->emp.print(&this->emp);
}

void defineMethods_World(World* this) {
    this->endGame = endGame_World;
    this->abandonedResource = abandonedResource_World;
    this->invasion = invasion_World;
    this->diplomaticAlliance = diplomaticAlliance_World;
#if DEBUG
    this->forceEndGame = forceEndGame_World;
    this->modifyGoldEmp = modifyGoldEmp_World;
    this->modifyProductEmp = modifyProductEmp_World;
    this->giveTech = giveTech_World;
    this->giveTerr = giveTerr_World;
    this->chooseEvent = chooseEvent_World;
#endif
    this->doEvent = doEvent_World;
    this->nextRound = nextRound_World;
    this->getRound = getRound_World;
    this->infoEndGame = infoEndGame_World;
    this->gather = gather_World;
    this->conquer = conquer_World;
    this->create = create_World;
    this->acquire = acquire_World;
    this->hasTechTradeEmp = hasTechTradeEmp_World;
    this->tradeGoldEmp = tradeGoldEmp_World;
    this->tradeProdEmp = tradeProdEmp_World;
    this->tradeMilitaryEmp = tradeMilitaryEmp_World;
    this->getNTerr = getNTerr_World;
    this->getForceEmp = getForceEmp_World;
    this->getSafeEmp = getSafeEmp_World;
    this->getWarehouseEmp = getWarehouseEmp_World;
    this->printTerrInfo = printTerrInfo_World;
    this->printFreeTerr = printFreeTerr_World;
    this->printAvailableTech = printAvailableTech_World;
    this->print = print_World;
}

void defineEvents_World(World* this) {
    strncpy(this->events[0], "No Event", 24);
    strncpy(this->events[1], "Abandoned Resource", 24);
    strncpy(this->events[2], "Invasion", 24);
    strncpy(this->events[3], "Diplomatic Aliance", 24);
}

void defineTech_World(World* this) {
    initTech(&this->technologies[0], "Military Drones", 3, "Increases the maximum number of military force to 5.");
    initTech(&this->technologies[1], "Teleguided Missiles", 4, "Allows the conquest of islands.");
    initTech(&this->technologies[2], "Territorial Defenses", 4, "Increases the resistance of an invaded territory by 1.");
    initTech(&this->technologies[3], "Stock Exchange", 2, "Allows for trades between product and gold on the gathering phase.");
    initTech(&this->technologies[4], "Central Bank", 3, "Increases the empire's safe's and warehouse's capacity to 5.");
}

void initWorld(World* this) {
    srand(time(NULL));

    defineMethods_World(this);
    defineEvents_World(this);
    defineTech_World(this);
    
    initEmpire(&this->emp);

    this->territories = NULL;
    this->nrTerritories = 0;

    this->create(this, "initialterr", 1);
    this->emp.addTerr(&this->emp, this->territories[0]);

    this->round = 1;
}

void copyWorld(World* dest, World* src) {
    Territory** temp = NULL;
    int i;
    size_t size;

    defineMethods_World(dest);
    defineEvents_World(dest);
    defineTech_World(dest);

    dest->nrTerritories = src->nrTerritories;
    dest->round = src->round;

    copyEmpire(&dest->emp, &src->emp);

    size = dest->nrTerritories * sizeof(Territory*);
    temp = malloc(size);

    if (temp == NULL) {
        fprintf(stderr, "Error allocating memory for territories* array.");
        return;
    }

    dest->territories = temp;

    for (i = 0; i < dest->nrTerritories; i++) {
        dest->territories[i] = src->territories[i]->clone(src->territories[i]);

        if (dest->territories[i]->isConquered(dest->territories[i])) {
            dest->emp.rmTerrPtr(&dest->emp, src->territories[i]);
            dest->emp.addTerr(&dest->emp, dest->territories[i]);
        }
    }
}

void disposeWorld(World* this) {
    int i;

    if (this->territories != NULL) {
        for (i = 0; i < this->nrTerritories; i++) {
            disposeTerritory(this->territories[i]);
            free(this->territories[i]);
        }

        free(this->territories);
    }

    disposeEmpire(&this->emp);

    for (i = 0; i < NR_TECHNOLOGIES; i++) {
        disposeTech(&this->technologies[i]);
    }
}