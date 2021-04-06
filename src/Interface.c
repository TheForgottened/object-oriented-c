#include "Interface.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "utils.h"

void defineCommands_Interface(Interface* this) {
    initCommand(&(this->commands[0]), "load", "Loads informations about the world from a file", "<file_name>");
    initCommand(&(this->commands[1]), "create", "Creates n territories of the specified type", "<type> <n>");
    initCommand(&(this->commands[2]), "conquer", "Tries to conquer a territory", "<name>");
    initCommand(&(this->commands[3]), "skip", "Skips the chance to conquest", "");
    initCommand(&(this->commands[4]), "moregold", "Buys 1 gold for the price of 2 products", "");
    initCommand(&(this->commands[5]), "moreprod", "Buys 1 product for the price of 2 golds", "");
    initCommand(&(this->commands[6]), "moremilitary", "Buys 1 military unit for the price of 1 gold and 1 product", "");
    initCommand(&(this->commands[7]), "acquire", "Acquires the specified technology", "<name>");
    initCommand(&(this->commands[8]), "show", "Shows information about the world or a specified territory", "(<name>)");
    initCommand(&(this->commands[9]), "continue", "Continues to the next phase", "");
    initCommand(&(this->commands[10]), "save", "Saves the current game state with the specified name", "<name>");
    initCommand(&(this->commands[11]), "activate", "Loads the save with the specified name", "<name>");
    initCommand(&(this->commands[12]), "delete", "Deletes the save with the specified name", "<name>");
    initCommand(&(this->commands[13]), "info", "Shows instructions of the specified command", "<cmd>");
#if DEBUG
    initCommand(&(this->commands[14]), "take", "(DEBUG) Takes a technology or territory without any restrictions or costs", "<tec/terr> <name>");
    initCommand(&(this->commands[15]), "modify", "(DEBUG) Modifies the empire's safe or the empire's warehouse", "<gold/prod> <n>");
    initCommand(&(this->commands[16]), "fevent", "(DEBUG) Forces the specified event", "<name>");
    initCommand(&(this->commands[17]), "quit", "(DEBUG) Forces the game to finish", "");
#endif
}

void game_Interface(Interface* this) {
    errcode code;

    this->nextPhase = -1;

    while (1) {
        switch (this->nextPhase) {
            case -1:
                code = this->setupPhase(this);
                break;
            
            case 0:
                code = this->conquestPhase(this);
                break;

            case 1:
                code = this->gatheringPhase(this);
                break;

            case 2:
                code = this->shopPhase(this);
                break;

            case 3:
                code = this->eventPhase(this);
                break;

            case 4:
                putchar('\n');
                this->w->infoEndGame(this->w, "");
                putchar('\n');

                while ((code = this->askForCommands(this)) == OK);

                if (code == AVANCA) {
                    putchar('\n');
                    return;
                } else {
                    break;
                }

            default:
                printf("CRITICAL ERROR\n");
                code = UNEXPECTED;
                break;
        }

        if (code == FIM_JOGO) {
            this->nextPhase = 4;
        } else if (code != ATIVA) {
            this->nextPhase = this->nextPhase == 3 ? 0 : this->nextPhase + 1;
        }
    }
}

errcode setupPhase_Interface(Interface* this) {
    errcode code;

    printf("\n-- SETUP PHASE --\n");

    this->changeCMDAvailability(this, "show", true);
    this->changeCMDAvailability(this, "save", true);
    this->changeCMDAvailability(this, "activate", true);
    this->changeCMDAvailability(this, "delete", true);
    this->changeCMDAvailability(this, "info", true);
    this->changeCMDAvailability(this, "continue", true);

#if DEBUG
    this->changeCMDAvailability(this, "quit", true);
    this->changeCMDAvailability(this, "take", true);
    this->changeCMDAvailability(this, "modify", true);
    this->changeCMDAvailability(this, "fevent", true);
#endif

    this->changeCMDAvailability(this, "load", true);
    this->changeCMDAvailability(this, "create", true);

    while ((code = this->askForCommands(this)) == OK);

    this->changeCMDAvailability(this, "load", false);
    this->changeCMDAvailability(this, "create", false);

    return code;
}

errcode conquestPhase_Interface(Interface* this) {
    errcode code;

    printf("\n\n");
    this->printInfoPhase(this);
    printf("\n\n-- CONQUEST PHASE --\n");

    this->changeCMDAvailability(this, "conquer", true);
    this->changeCMDAvailability(this, "skip", true);

    while ((code = this->askForCommands(this)) == OK);

    this->changeCMDAvailability(this, "conquer", false);
    this->changeCMDAvailability(this, "skip", false);

    if (code == ATIVA || code == AVANCA) {
        return code;
    }

#if DEBUG
    if (code == FIM_JOGO) {
        return code;
    }
#endif

    while ((code = this->askForCommands(this)) == OK);

    return code;
}

errcode gatheringPhase_Interface(Interface* this) {
    int goldBefore = this->w->getSafeEmp(this->w);
    int prodBefore = this->w->getWarehouseEmp(this->w);

    errcode code = this->w->gather(this->w);

    int currGold = this->w->getSafeEmp(this->w);
    int currProd = this->w->getWarehouseEmp(this->w);

    printf("\n\n-- GATHERING PHASE --\n");

    printf("\nGathered: %i of gold and %i of product.\n", currGold - goldBefore, currProd - prodBefore);
    printf("\nSafe: %i\tWarehouse: %i\n", currGold, currProd);

    if (code != OK) {
        printf("\nINFO: %s.", codeToString(code));
    }

    if (this->w->hasTechTradeEmp(this->w)) {
        this->changeCMDAvailability(this, "moregold", true);
        this->changeCMDAvailability(this, "moreprod", true);

        printf("\nYou have the required technology to make trades.\n");

        while((code = this->askForCommands(this)) == OK);

#if DEBUG
        if (code == FIM_JOGO) {
            return code;
        }
#endif

        this->changeCMDAvailability(this, "moregold", false);
        this->changeCMDAvailability(this, "moreprod", false);
    } else {
        printf("\nYou don't have the required technology to make trades.\n");
    }

    while((code = this->askForCommands(this)) == OK);

    return code;
}

errcode shopPhase_Interface(Interface* this) {
    errcode code;

    printf("\n\n-- SHOP PHASE --\n");

    printf("\nTechnologies available to buy:\n");
    this->w->printAvailableTech(this->w);

    this->changeCMDAvailability(this, "moremilitary", true);
    this->changeCMDAvailability(this, "acquire", true);

    while((code = this->askForCommands(this)) == OK);

    this->changeCMDAvailability(this, "moremilitary", false);
    this->changeCMDAvailability(this, "acquire", false);

    return code;
}

errcode load_Interface(Interface* this, char* fileName) {
    char line[BUFFER_SIZE], **temp;
    bool breakFlag;
    errcode code;
    int initSize, endSize, tempSize;
    FILE *f = NULL;

    f = fopen(fileName, "rt");

    if (f == NULL) {
        return FILE_CANT_OPEN;
    }

    this->changeCMDAvailability(this, "show", false);
    this->changeCMDAvailability(this, "save", false);
    this->changeCMDAvailability(this, "activate", false);
    this->changeCMDAvailability(this, "delete", false);
    this->changeCMDAvailability(this, "info", false);
    this->changeCMDAvailability(this, "continue", false);
#if DEBUG
    this->changeCMDAvailability(this, "quit", false);
    this->changeCMDAvailability(this, "take", false);
    this->changeCMDAvailability(this, "modify", false);
    this->changeCMDAvailability(this, "fevent", false);
#endif

    initSize = this->w->getNTerr(this->w);

    resetString(line);
    code = FILE_BAD_FORMAT;
    breakFlag = true;

    while (breakFlag && (fgets(line, BUFFER_SIZE, f) != NULL)) {
        if (line[strlen(line) - 1] == '\n') {
            line[strlen(line) - 1] = ' ';
        }
        
        temp = splitString(line, " ", &tempSize);
        code = this->run(this, temp, tempSize);

        resetString(line);
        free(temp);

        switch (code) {
            case OK:
                break;

            case TERR_TYPE_UNKNOWN:
            case CMD_NO_NEW_TERRITORIES:
            case CMD_NOT_AVAILABLE:
                printf("\nLine not executed: '%s' (%s)\n", line, codeToString(code));
                code = OK;
                continue;
            
            case CMD_INVALID_ARGS:
            case CMD_UNKNOWN:
                code = FILE_BAD_FORMAT;
                breakFlag = false;
                break;
            
            default:
                code = UNEXPECTED;
                breakFlag = false;
                break;
        }
    }

    endSize = this->w->getNTerr(this->w);

    if (endSize == initSize) {
        printf("\nWARNING: %s\n", codeToString(FILE_NO_NEW_TERRITORIES));
    } else {
        printf("\nCreated %i territories!\n", endSize - initSize);
    }

    this->changeCMDAvailability(this, "show", true);
    this->changeCMDAvailability(this, "save", true);
    this->changeCMDAvailability(this, "activate", true);
    this->changeCMDAvailability(this, "delete", true);
    this->changeCMDAvailability(this, "info", true);
    this->changeCMDAvailability(this, "continue", true);
#if DEBUG
    this->changeCMDAvailability(this, "quit", true);
    this->changeCMDAvailability(this, "take", true);
    this->changeCMDAvailability(this, "modify", true);
    this->changeCMDAvailability(this, "fevent", true);
#endif

    fclose(f);
    return code;
}

errcode eventPhase_Interface(Interface* this) {
    errcode code;

    printf("\n\n-- SHOP PHASE --\n");

#if DEBUG
    code = this->w->chooseEvent(this->w, "");
#else
    code = this->w->doEvent(this->w, -1);
#endif

    if (code == FIM_JOGO) {
        return code;
    }

    while((code = this->askForCommands(this)) == OK);

    return code;
}

errcode changeCMDAvailability_Interface(Interface* this, char* cmd, bool b) {
    int i;

    for (i = 0; i < NR_COMMANDS; i++) {
        if (strcasecmp(this->commands[i].getName(&(this->commands[i])), cmd) == 0) {
            if (b == this->commands[i].isAvailable(&(this->commands[i]))) {
                return CMD_DISP_UNCHANGED;
            } else {
                this->commands[i].setAvailability(&(this->commands[i]), b);
                return OK;
            }
        }
    }

    return CMD_UNKNOWN;
}

errcode askForCommands_Interface(Interface* this) {
    int i;
    int inputSize = 0;
    char input[BUFFER_SIZE], **temp;
    errcode code;

    while (1) {
        printf("\nAvailable commands:");

        for (i = 0; i < NR_COMMANDS; i++) {
            if (this->commands[i].isAvailable(&(this->commands[i]))) {
                printf(" %s", this->commands[i].getName(&(this->commands[i])));
            }
        }

        printf("\nCMD: ");
        fgets(input, sizeof(input), stdin);
        input[strlen(input) - 1] = '\0';

        if (strlen(input) < 1) {
            fprintf(stderr, "Invalid command! Error: %s\n", codeToString(CMD_UNKNOWN));
            continue;
        }

        temp = splitString(input, " ", &inputSize);
        code = this->run(this, temp, inputSize);
        free(temp);

        if (code == NEXT || code == AVANCA || code == ATIVA) {
            printf("\nCommand executed successfully!\n");
            return code;
        } else if (code == FIM_JOGO) {
            return FIM_JOGO;
        } else if (code != OK) {
            printf("\nCommand failed! Error: %s.\n", codeToString(code));
        } else {
            printf("\nCommand executed successfully!\n");
            return OK;
        }

        if (code == IMP_NOT_ENOUGH_POWER || code == IMP_NOT_ENOUGH_LUCK) {
            return NEXT;
        }
    }
}

errcode run_Interface(Interface* this, char** input, int sizeInput) {
    size_t size;
    int i;
    int cmd, luck, attackMilitaryForce, phase;
    char c;
    Save* tempSave;
    char* str = NULL;
    errcode code;

    for (cmd = 0; cmd < NR_COMMANDS; cmd++) {
        if (strcmp(this->commands[cmd].getName(&this->commands[cmd]), input[0]) == 0) {
            if (this->commands[cmd].isAvailable(&this->commands[cmd])) {
                break;
            } else {
                return CMD_NOT_AVAILABLE;
            }
        }
    }

    if (cmd == NR_COMMANDS) {
        return CMD_UNKNOWN;
    }

    switch (cmd) {
        case 0: // load
            if (sizeInput != 2) {
                printf("\nInstructions: %s %s\n", this->commands[cmd].getName(&this->commands[cmd]), this->commands[cmd].getArgs(&this->commands[cmd]));
                return CMD_INVALID_ARGS;
            }

            return this->load(this, input[1]);
            break;

        case 1: // create
            if (sizeInput != 3) {
                printf("\nInstructions: %s %s\n", this->commands[cmd].getName(&this->commands[cmd]), this->commands[cmd].getArgs(&this->commands[cmd]));
                return CMD_INVALID_ARGS;
            }

            for (i = 0; i < strlen(input[2]); i++) {
                if (!isdigit(input[2][i])) {
                    printf("\nInstructions: %s %s\n", this->commands[cmd].getName(&this->commands[cmd]), this->commands[cmd].getArgs(&this->commands[cmd]));
                    return CMD_INVALID_ARGS;
                }
            }

            return this->w->create(this->w, input[1], atoi(input[2]));
            break;

        case 2: // conquer
            if (sizeInput != 2) {
                printf("\nInstructions: %s %s\n", this->commands[cmd].getName(&this->commands[cmd]), this->commands[cmd].getArgs(&this->commands[cmd]));
                return CMD_INVALID_ARGS;;
            }

            attackMilitaryForce = this->w->getForceEmp(this->w);
            // input[1] is the territory name (suposedly) 
            code = this->w->conquer(this->w, input[1], &luck); 
            if (code == IMP_NOT_ENOUGH_LUCK || code == IMP_NOT_ENOUGH_POWER) {
                putchar('\n');
                this->w->printTerrInfo(this->w, input[1]);
                printf("\n\nAttack's military force: %i", attackMilitaryForce);
                printf("\nLuck on battle: %i", i);
                printf("\nTotal force: %i\n", attackMilitaryForce + luck);

                if (attackMilitaryForce != this->w->getForceEmp(this->w)) {
                    printf("\nYou lost a military unit.\n New military force: %i\n", this->w->getForceEmp(this->w));
                } else {
                    printf("\nYou didn't lose a military unit because it's already at 0.\n");
                }

                return code;
            } else if (code != OK) {
                return code;
            } else {
                putchar('\n');
                this->w->printTerrInfo(this->w, input[1]);
                printf("\n\nTerritory %s conquered, with luck of %i.\n", input[i], luck);
                return NEXT;
            }
            break;

        case 3: // skip
            if (sizeInput != 1) {
                printf("\nInstructions: %s %s\n", this->commands[cmd].getName(&this->commands[cmd]), this->commands[cmd].getArgs(&this->commands[cmd]));
                return CMD_INVALID_ARGS;
            }

            return NEXT;
            break;

        case 4: // moregold
            if (sizeInput != 1) {
                printf("\nInstructions: %s %s\n", this->commands[cmd].getName(&this->commands[cmd]), this->commands[cmd].getArgs(&this->commands[cmd]));
                return CMD_INVALID_ARGS;
            }

            return this->w->tradeGoldEmp(this->w);
            break;

        case 5: // moreprod
            if (sizeInput != 1) {
                printf("\nInstructions: %s %s\n", this->commands[cmd].getName(&this->commands[cmd]), this->commands[cmd].getArgs(&this->commands[cmd]));
                return CMD_INVALID_ARGS;
            }

            return this->w->tradeProdEmp(this->w);
            break;

        case 6: // moremilitary
            if (sizeInput != 1) {
                printf("\nInstructions: %s %s\n", this->commands[cmd].getName(&this->commands[cmd]), this->commands[cmd].getArgs(&this->commands[cmd]));
                return CMD_INVALID_ARGS;
            }

            return this->w->tradeMilitaryEmp(this->w);
            break;

        case 7: // acquire
            if (sizeInput <= 1) {
                printf("\nInstructions: %s %s\n", this->commands[cmd].getName(&this->commands[cmd]), this->commands[cmd].getArgs(&this->commands[cmd]));
                return CMD_INVALID_ARGS;
            }
            
            for (i = 1, size = 0; i < sizeInput; i++) {
                size += strlen(input[i]);
            }

            size += sizeInput - 2;
            size *= sizeof(char);

            str = malloc(size);
            
            if (str == NULL) {
                fprintf(stderr, "Error allocating memory for string.\n");
                return UNEXPECTED;
            }

            resetString(str);
            strncpy(str, input[1], size);

            for (i = 2; i < sizeInput; i++) {
                strncat(str, input[i], size - (strlen(str) * sizeof(char)));
            }

            code = this->w->acquire(this->w, str);
            free(str);
            return code;
            break;

        case 8: // show
            if (sizeInput == 1) {
                printf("\n\n");
                this->printInfoPhase(this);
                printf("\n\nWorld: \n");
                this->w->print(this->w);
                putchar('\n');

                if (this->nrSaves > 0) {
                    printf("\nAvailable saves: ");

                    for (i = 0; i < this->nrSaves; i++) {
                        printf("%s ", this->saves[i].getName(&this->saves[i]));
                    }
                    putchar('\n');
                }

                return OK;
            } else if (sizeInput == 2) {
                code = this->w->printTerrInfo(this->w, input[1]);

                return code;
            } else {
                printf("\nInstructions: %s %s\n", this->commands[cmd].getName(&this->commands[cmd]), this->commands[cmd].getArgs(&this->commands[cmd]));
                return CMD_INVALID_ARGS;
            }

            break;

        case 9: // continue
            if (sizeInput != 1) {
                printf("\nInstructions: %s %s\n", this->commands[cmd].getName(&this->commands[cmd]), this->commands[cmd].getArgs(&this->commands[cmd]));
                return CMD_INVALID_ARGS;
            }
            
            return AVANCA;
            break;

        case 10: // save
            if (sizeInput != 2) {
                printf("\nInstructions: %s %s\n", this->commands[cmd].getName(&this->commands[cmd]), this->commands[cmd].getArgs(&this->commands[cmd]));
                return CMD_INVALID_ARGS;
            }

            for (i = 0; i < this->nrSaves; i++) {
                if (strcmp(this->saves[i].getName(&this->saves[i]), input[1]) == 0) {
                    printf("\nAre you sure you want to replace the existing save (Y/N)? ");

                    while (1) {
                        scanf("%c", &c);
                        c = toupper(c);

                        if (c != 'Y' && c != 'N') {
                            printf("Invalid option! Please choole a valid option (Y/N): ");
                        } else {
                            break;
                        }
                    }

                    if (c == 'Y') {
                        printf("\nSave: %s replaced.\n", input[0]);

                        if (this->nextPhase == 3) {
                            phase = 0;
                        } else if (this->nextPhase == -1) {
                            phase = -1;
                        } else {
                            phase = this->nextPhase + 1;
                        }

                        disposeSave(&this->saves[i]);
                        initSave(&this->saves[i], input[1], this->w, phase);

                        return OK;
                    } else {
                        printf("\nSave: %s not replaced.\n", input[1]);
                        return SAVE_USER_CANCEL;
                    }
                }
            }

            if (this->nextPhase == 3) {
                phase = 0;
            } else if (this->nextPhase == -1) {
                phase = -1;
            } else {
                phase = this->nextPhase + 1;
            }

            tempSave = NULL;
            size = (this->nrSaves + 1) * sizeof(Save);
            tempSave = realloc(this->saves, size);

            if (tempSave == NULL) {
                fprintf(stderr, "Error allocating memory for an array.\n");
                return UNEXPECTED;
            }

            this->saves = tempSave;

            initSave(&this->saves[(this->nrSaves)++], input[1], this->w, phase);

            return OK;
            break;

        case 11: // activate
            if (sizeInput != 2) {
                printf("\nInstructions: %s %s\n", this->commands[cmd].getName(&this->commands[cmd]), this->commands[cmd].getArgs(&this->commands[cmd]));
                return CMD_INVALID_ARGS;
            }

            for (i = 0; i < this->nrSaves; i++) {
                if (strcmp(this->saves[i].getName(&this->saves[i]), input[1]) == 0) {
                    printf("\nAre you sure you want to load the save %s? You'll lose every unsaved progress! (Y/N) ", input[1]);
                
                    while(1) {
                        scanf("%c", &c);
                        c = toupper(c);

                        if (c != 'Y' && c != 'N') {
                            printf("Invalid option! Please choose a valid option (Y/N): ");
                        } else {
                            break;
                        }
                    }    

                    if (c == 'Y') {
                        printf("\nSave: %s loaded.\n", input[0]);

                        disposeWorld(this->w);
                        copyWorld(this->w, this->saves[i].getWorld(&this->saves[i]));
                        this->nextPhase = this->saves[i].getPhase(&this->saves[i]);

                        return ATIVA;
                    } else {
                        printf("\nSave: %s not loaded.\n", input[1]);
                        return SAVE_USER_CANCEL;
                    }
                }
            }
            
            return SAVE_NOT_FOUND;
            break;

        case 12: // delete
            if (sizeInput != 2) {
                printf("\nInstructions: %s %s\n", this->commands[cmd].getName(&this->commands[cmd]), this->commands[cmd].getArgs(&this->commands[cmd]));
                return CMD_INVALID_ARGS;
            }

            for (i = 0; i < this->nrSaves; i++) {
                if (strcmp(this->saves[i].getName(&this->saves[i]), input[1]) == 0) {
                    printf("\nAre you sure you want to delete the save %s (Y/N)? ", input[1]);
                
                    while (1) {
                        scanf("%c", &c);
                        c = toupper(c);

                        if (c != 'Y' && c != 'N') {
                            printf("Invalid option! Please choose a valid option (Y/N): ");
                        } else {
                            break;
                        }
                    }    

                    if (c == 'Y') {
                        printf("\nSave: %s deleted.\n", input[0]);

                        tempSave = NULL;
                        size = (this->nrSaves - 1) * sizeof(Save);
                        tempSave = realloc(this->saves, size);

                        if (tempSave == NULL && size != 0) {
                            fprintf(stderr, "Error allocating memory for saves array.");
                            return UNEXPECTED;
                        }

                        tempSave[i] = this->saves[--(this->nrSaves)];
                        this->saves = tempSave;

                        return ATIVA;
                    } else {
                        printf("\nSave: %s not deleted.\n", input[1]);
                        return SAVE_USER_CANCEL;
                    }
                }
            }
            break;

        case 13: // info
            if (sizeInput != 2) {
                printf("\nInstructions: %s %s\n", this->commands[cmd].getName(&this->commands[cmd]), this->commands[cmd].getArgs(&this->commands[cmd]));
                return CMD_INVALID_ARGS;
            }

            for (i = 0; i < NR_COMMANDS; i++) {
                if (strcmp(this->commands[i].getName(&this->commands[i]), input[1]) == 0) {
                    putchar('\n');
                    this->commands[i].print(&this->commands[i]);
                    return OK;
                }
            }
            break;
        
#if DEBUG
        case 14: // take
            if (sizeInput < 3 || (strcmp("tech", input[1]) != 0 && strcmp("terr", input[1]) != 0)) {
                printf("\nInstructions: %s %s\n", this->commands[cmd].getName(&this->commands[cmd]), this->commands[cmd].getArgs(&this->commands[cmd]));
                return CMD_INVALID_ARGS;
            }

            if (strcmp("tech", input[1]) == 0) {
                for (i = 2, size = 0; i < sizeInput; i++) {
                    size += strlen(input[i]) + 1; // space between words
                }

                size += 1;
                size *= sizeof(char);

                str = malloc(size);

                if (str == NULL) {
                    fprintf(stderr, "Error allocating memory for string.\n");
                    return UNEXPECTED;
                }

                resetString(str);

                for (i = 2; i < sizeInput; i++) {
                    strcat(str, input[i]);
                    strcat(str, " ");
                }

                str[strlen(str) - 1] = '\0';

                code = this->w->giveTech(this->w, str);
                free(str);
            } else {
                code = this->w->giveTerr(this->w, input[2]);
            }

            return code;
            break;

        case 15: // modify
            if (sizeInput != 2 || (strcmp("gold", input[1]) != 0 && strcmp("prod", input[1]) != 0)) {
                printf("\nInstructions: %s %s\n", this->commands[cmd].getName(&this->commands[cmd]), this->commands[cmd].getArgs(&this->commands[cmd]));
                return CMD_INVALID_ARGS;
            }

            for (i = 0; i < strlen(input[2]); i++) {
                if (!isdigit(input[2][i])) {
                    printf("\nInstructions: %s %s\n", this->commands[i].getName(&this->commands[i]), this->commands[i].getArgs(&this->commands[i]));
                    return CMD_INVALID_ARGS;
                }
            }

            if (strcmp("gold", input[1]) == 0) {
                this->w->modifyGoldEmp(this->w, atoi(input[2]));
            } else {
                this->w->modifyProductEmp(this->w, atoi(input[2]));
            }

            return OK;
            break;

        case 16: // fevent
            if (sizeInput < 2) {
                printf("\nInstructions: %s %s\n", this->commands[cmd].getName(&this->commands[cmd]), this->commands[cmd].getArgs(&this->commands[cmd]));
                return CMD_INVALID_ARGS;
            }

            for (i = 2, size = 0; i < sizeInput; i++) {
                size += strlen(input[i]) + 1; // space between words
            }

            size += 1;
            size *= sizeof(char);

            str = malloc(size);

            if (str == NULL) {
                fprintf(stderr, "Error allocating memory for string.\n");
                return UNEXPECTED;
            }

            resetString(str);

            for (i = 2; i < sizeInput; i++) {
                strcat(str, input[i]);
                strcat(str, " ");
            }

            str[strlen(str) - 1] = '\0';

            code = this->w->chooseEvent(this->w, str);
            free(str);

            if (code == OK || code == FIM_JOGO) {
                return OK;
            }

            return code;
            break;

        case 17: // quit
            if (sizeInput != 1) {
                printf("\nInstructions: %s %s\n", this->commands[cmd].getName(&this->commands[cmd]), this->commands[cmd].getArgs(&this->commands[cmd]));
                return CMD_INVALID_ARGS;
            }

            this->w->forceEndGame(this->w);
            return FIM_JOGO;
            break;
#endif

        default:
            return CMD_UNKNOWN;
    }

    return UNEXPECTED;
} 

void printInfoPhase_Interface(Interface* this) {
    int temp = this->w->getRound(this->w);

    printf("|* PHASE %i (YEAR %i PHASE %i) *|", temp, temp == 0 ? 0 : temp / 7 + 1, temp >= 7 ? temp % 7 + 1 : temp % 7);
}

void initInterface(Interface* this, World* w) {
    // Functions
    this->printInfoPhase = printInfoPhase_Interface;
    this->askForCommands = askForCommands_Interface;
    this->game = game_Interface;
    this->setupPhase = setupPhase_Interface;
    this->conquestPhase = conquestPhase_Interface;
    this->gatheringPhase = gatheringPhase_Interface;
    this->shopPhase = shopPhase_Interface;
    this->eventPhase = eventPhase_Interface;
    this->load = load_Interface;
    this->run = run_Interface;
    this->changeCMDAvailability = changeCMDAvailability_Interface;

    this->w = w;
    this->saves = NULL;
    this->nrSaves = 0;

    defineCommands_Interface(this);

    printf("\n|+ ISEC: Total War +|\n");
    this->game(this);
}

void disposeInterface(Interface* this) {
    int i;

    if (this->saves != NULL) {
        for (i = 0; i < this->nrSaves; i++) {
            disposeSave(&this->saves[i]);
        }

        free(this->saves);
    }

    for (i = 0; i < NR_COMMANDS; i++) {
        disposeCommand(&this->commands[i]);
    }
}