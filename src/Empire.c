#include "Empire.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

bool canAdd_Empire(Empire* this, int x, int t) {
    int maxResources = this->hasTech(this, "Central Bank") ? 5 : 3;
    int maxForce = this->hasTech(this, "Military Drones") ? 5 : 3;

    switch (t) {
        case 0:
            return x + this->safe > maxResources ? false : true;
            break;

        case 1:
            return x + this->warehouse > maxResources ? false : true;
            break;
        
        case 2:
            return x + this->force > maxForce ? false : true;
            break;

        default:
            return false;
            break;
    }
}

errcode gather_Empire(Empire* this) {
    errcode err1 = this->addGold(this, this->getTotalGoldProd(this));
    errcode err2 = this->addProduct(this, this->getTotalProductProd(this));

    if (err1 == IMP_TOO_MUCH_OURO && err2 == IMP_TOO_MUCH_PROD) {
        return IMP_TOO_MANY_RESOURCES;
    } else if (err1 == IMP_TOO_MUCH_OURO) {
        return IMP_TOO_MUCH_OURO;
    } else if (err2 == IMP_TOO_MUCH_PROD) {
        return IMP_TOO_MUCH_PROD;
    } else if (err1 == OK && err2 == OK) {
        return OK;
    } else {
        return UNEXPECTED;
    }
}

errcode addGold_Empire(Empire* this, int x) {
    if (!this->canAdd(this, x, 0)) {
        this->safe = this->hasTech(this, "Central Bank") ? 5 : 3;
        return IMP_TOO_MUCH_OURO; 
    }

    this->safe += x;
    return OK;
}

errcode addProduct_Empire(Empire* this, int x) {
    if (!this->canAdd(this, x, 1)) {
        this->warehouse = this->hasTech(this, "Central Bank") ? 5 : 3;
        return IMP_TOO_MUCH_OURO; 
    }

    this->warehouse += x;
    return OK;
}

errcode addForce_Empire(Empire* this, int x) {
    if (!this->canAdd(this, x, 2)) {
        this->force = this->hasTech(this, "Military Drones") ? 5 : 3;
        return IMP_TOO_MUCH_OURO; 
    }

    this->force += x;
    return OK;
}

errcode addTech_Empire(Empire* this, Tech* newTech) {
    int i;
    size_t size;
    Tech** temp;

    for (i = 0; i < this->nrTechnologies; i++) {
        if (this->technologies[i] == newTech) {
            return TEC_ALREADY_BOUGHT;
        }
    }

    if (newTech->getCost(newTech) > this->safe) {
        return IMP_NOT_ENOUGH_OURO;
    }

    this->safe -= newTech->getCost(newTech);

    size = (this->nrTechnologies + 1) * sizeof(Tech *);
    temp = realloc(this->technologies, size);

    if (temp == NULL) {
        fprintf(stderr, "Error allocating memory for technologies array.");
        return UNEXPECTED;
    }

    this->technologies = temp;
    this->technologies[(this->nrTechnologies)++] = newTech;
    return OK;
}

#if DEBUG
errcode forceAddTech_Empire(Empire* this, Tech* newTech) {
    int i;
    size_t size;
    Tech** temp;

    for (i = 0; i < this->nrTechnologies; i++) {
        if (this->technologies[i] == newTech) {
            return TEC_ALREADY_BOUGHT;
        }
    }

    size = (this->nrTechnologies + 1) * sizeof(Tech *);
    temp = realloc(this->technologies, size);

    if (temp == NULL) {
        fprintf(stderr, "Error allocating memory for technologies array.");
        return UNEXPECTED;
    }

    this->technologies = temp;
    this->technologies[(this->nrTechnologies)++] = newTech;
    return OK;
}

void setGold_Empire(Empire* this, int x) {
    this->safe = x;
}

void setProd_Empire(Empire* this, int x) {
    this->warehouse = x;
}
#endif

bool hasTech_Empire(Empire* this, char* name) {
    int i;

    for (i = 0; i < this->nrTechnologies; i++) {
        if (strcmp(this->technologies[i]->getName(this->technologies[i]), name)) {
            return true;
        }
    }

    return false;
}

errcode trade_Empire(Empire* this, int t) {
    switch (t) {
        case 0: // more gold
            if (this->warehouse < 2) {
                return IMP_NOT_ENOUGH_PROD;
            }

            if (this->addGold(this, 1) != OK) {
                return IMP_CANT_TAKE_OURO;
            }

            this->warehouse -= 2;

            return NEXT;
            break;

        case 1: // more product
            if (this->safe < 2) {
                return IMP_NOT_ENOUGH_OURO;
            }

            if (this->addProduct(this, 1) != OK) {
                return IMP_CANT_TAKE_PROD;
            }

            this->safe -= 2;

            return NEXT;
            break;

        case 2: // more military
            if (this->safe < 1) {
                return IMP_NOT_ENOUGH_OURO;
            }

            if (this->warehouse < 1) {
                return IMP_NOT_ENOUGH_PROD;
            }

            if (this->addForce(this, 1) != OK) {
                return IMP_CANT_TAKE_FORCA;
            }

            this->warehouse -= 1;
            this->safe -= 1;

            return OK;
            break;

        default:
            return UNEXPECTED;
            break;
    }
}

errcode addTerr_Empire(Empire* this, Territory* newTerr) {
    int i;
    size_t size;
    Territory** temp;

    for (i = 0; i < this->nrTerritories; i++) {
        if (this->territories[i] == newTerr) {
            return TERR_ALREADY_CONQUERED;
        }
    }

    size = (this->nrTerritories + 1) * sizeof(Territory *);
    temp = realloc(this->territories, size);

    if (temp == NULL) {
        fprintf(stderr, "Error allocating memory for territories array.");
        return UNEXPECTED;
    }

    this->territories = temp;
    this->territories[(this->nrTerritories)++] = newTerr;
    return OK;
}

errcode rmTerrStr_Empire(Empire* this, char* t) {
    int i;
    size_t size;
    Territory** temp;

    for (i = 0; i < this->nrTerritories; i++) {
        if (strcmp(this->territories[i]->getName(this->territories[i]), t) == 0) {
            size = (this->nrTerritories - 1) * sizeof(Territory *);
            temp = realloc(this->territories, size);

            if (temp == NULL) {
                fprintf(stderr, "Error allocating memory for territories array.");
                return UNEXPECTED;
            }

            temp[i] = this->territories[--(this->nrTerritories)];
            this->territories = temp;
            return OK;
        }
    }

    return TERR_NOT_FOUND;
}

errcode rmTerrPtr_Empire(Empire* this, Territory* t) {
    int i;
    size_t size;
    Territory** temp;

    for (i = 0; i < this->nrTerritories; i++) {
        if (this->territories[i] == t) {
            size = (this->nrTerritories - 1) * sizeof(Territory *);
            temp = realloc(this->territories, size);

            if (temp == NULL) {
                fprintf(stderr, "Error allocating memory for territories array.");
                return UNEXPECTED;
            }

            temp[i] = this->territories[--(this->nrTerritories)];
            this->territories = temp;
            return OK;
        }
    }

    return TERR_NOT_FOUND;
}

int getTotalGoldProd_Empire(Empire* this) {
    int rtrnValue = 0, i;

    for (i = 0; i < this->nrTerritories; i++) {
        rtrnValue += this->territories[i]->getGold(this->territories[i]);
    }

    return rtrnValue;
}

int getTotalProductProd_Empire(Empire* this) {
    int rtrnValue = 0, i;

    for (i = 0; i < this->nrTerritories; i++) {
        rtrnValue += this->territories[i]->getProduct(this->territories[i]);
    }

    return rtrnValue;
}

int getSumPointsTerr_Empire(Empire* this) {
    int rtrnValue = 0, i;

    for (i = 0; i < this->nrTerritories; i++) {
        rtrnValue += this->territories[i]->getPoints(this->territories[i]);
    }

    return rtrnValue;
}

int getNTech_Empire(Empire* this) {
    return this->nrTechnologies;
}

int getSumPointsTech_Empire(Empire* this) {
    return this->getNTech(this);
}

void loseForce_Empire(Empire* this) {
    if (this->force > 0) {
        (this->force)--;
    }
}

int getNTerr_Empire(Empire* this) {
    return this->nrTerritories;
}

Territory* getLastConquered_Empire(Empire* this) {
    return this->territories[this->nrTerritories - 1];
}

int getForce_Empire(Empire* this) {
    return this->force;
}

int getSafe_Empire(Empire* this) {
    return this->safe;
}

int getWarehouse_Empire(Empire* this) {
    return this->warehouse;
}

void printTerritories_Empire(Empire* this) {
    int i;

    for (i = 0; i < this->nrTerritories; i++) {
        putchar('\n');
        this->territories[i]->print(this->territories[i]);
    }
}

void printNameTech_Empire(Empire* this) {
    int i;

    for (i = 0; i < this->nrTechnologies; i++) {
        printf("%s     ", this->technologies[i]->getName(this->technologies[i]));
    }
}

void print_Empire(Empire* this) {
    int maxResources = this->hasTech(this, "Central Bank") ? 5 : 3;
    int maxForce = this->hasTech(this, "Military Drones") ? 5 : 3;

    printf("Force %i/%i   |   Safe: %i/%i (+%i)   |   Warehouse: %i/%i (+%i)\n",
    this->force, maxForce, this->safe, maxResources, this->getTotalGoldProd(this), this->warehouse, maxResources, this->getTotalProductProd(this));

    if (this->nrTechnologies > 0) {
        printf("Acquired technologies: ");
        this->printNameTech(this);
        putchar('\n');
    }

    printf("Territories: %i", this->nrTerritories);
    this->printTerritories(this);
}

void initEmpire(Empire* this) {
    // Functions
    this->canAdd = canAdd_Empire;
    this->loseForce = loseForce_Empire;
    this->gather = gather_Empire;
    this->addGold = addGold_Empire;
    this->addProduct = addProduct_Empire;
    this->addForce = addForce_Empire;
    this->addTech = addTech_Empire;
#if DEBUG
    this->forceAddTech = forceAddTech_Empire;
    this->setGold = setGold_Empire;
    this->setProd = setProd_Empire;
#endif
    this->hasTech = hasTech_Empire;
    this->addTerr = addTerr_Empire;
    this->rmTerrStr = rmTerrStr_Empire;
    this->rmTerrPtr = rmTerrPtr_Empire;
    this->getNTerr = getNTerr_Empire;
    this->getLastConquered = getLastConquered_Empire;
    this->getForce = getForce_Empire;
    this->getSafe = getSafe_Empire;
    this->getWarehouse = getWarehouse_Empire;
    this->getTotalGoldProd = getTotalGoldProd_Empire;
    this->getTotalProductProd = getTotalProductProd_Empire;
    this->getSumPointsTerr = getSumPointsTerr_Empire;
    this->getNTech = getNTech_Empire;
    this->getSumPointsTech = getSumPointsTech_Empire;
    this->printTerritories = printTerritories_Empire;
    this->printNameTech = printNameTech_Empire;
    this->print = print_Empire;
    // End Functions

    this->territories = NULL;
    this->nrTerritories = 0;

    this->technologies = NULL;
    this->nrTechnologies = 0;

    this->safe = 0;
    this->warehouse = 0;
    this->force = 0;
}

void copyEmpire(Empire* dest, Empire* src) {
    Territory** tempTerr = NULL;
    Tech** tempTech = NULL;
    size_t size;
    int i;

    initEmpire(dest);

    dest->nrTerritories = src->nrTerritories;
    dest->nrTechnologies = src->nrTechnologies;

    dest->safe = src->safe;
    dest->warehouse = src->warehouse;
    dest->force = src->force;

    size = dest->nrTerritories * sizeof(Territory*);
    tempTerr = malloc(size);

    if (tempTerr == NULL) {
        fprintf(stderr, "Error allocating memory for territories* array.");
        return;
    }

    dest->territories = tempTerr;

    for (i = 0; i < dest->nrTerritories; i++) {
        dest->territories[i] = src->territories[i];
    }

    size = dest->nrTechnologies * sizeof(Tech*);
    tempTech = malloc(size);

    if (tempTech == NULL) {
        fprintf(stderr, "Error allocating memory for technologies* array.");
        return;
    }

    dest->technologies = tempTech;

    for (i = 0; i < dest->nrTechnologies; i++) {
        dest->technologies[i] = src->technologies[i];
    }
}

void disposeEmpire(Empire* this) {
    free(this->territories);
    free(this->technologies);
}