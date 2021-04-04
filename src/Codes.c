#include "Codes.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define NR_CODES 35

Map codes[NR_CODES] = {   
    {UNEXPECTED, "Unexpected error"},
    {OK, "OK"},
    {NEXT, "Next sub-phase"},
    {AVANCA, "Next phase"},
    {ATIVA, "Load save"},

    {FILE_CANT_OPEN, "File opening failed"},
    {FILE_BAD_FORMAT, "File with wrong format"},
    {FILE_NO_NEW_TERRITORIES, "Information in file doesn't generate territories"},

    {CMD_UNKNOWN, "Unknown command"},
    {CMD_INFO_UNKNOWN, "There's no information about that command"},
    {CMD_INVALID_ARGS, "Wrong command arguments"},
    {CMD_NOT_AVAILABLE, "Command unavailable at the moment"},
    {CMD_DISP_UNCHANGED, "Command availability hasn't been changed"},
    {CMD_NO_NEW_TERRITORIES, "Command doesn't generate territories"},

    {IMP_NOT_ENOUGH_POWER, "Empire isn't strong enough"},
    {IMP_NOT_ENOUGH_LUCK, "Luck generated wasn't enough"},
    {IMP_NOT_ENOUGH_OURO, "Not enough gold"},
    {IMP_NOT_ENOUGH_PROD, "not enough product"},
    {IMP_TOO_MUCH_OURO, "The empire's safe is full therefore some gold was lost"},
    {IMP_TOO_MUCH_PROD, "The empire's warehouse is full therefore some product was lost"},
    {IMP_TOO_MUCH_FORCA, "The empire's military is full therefore some units were lost"},
    {IMP_TOO_MANY_RESOURCES, "Both the empire's safe and warehouse are full therefore some product was lost"},
    {IMP_CANT_TAKE_OURO, "The empire's safe isn't big enough to receive that amount of gold"},
    {IMP_CANT_TAKE_PROD, "The empire's warehouse isn't big enough to receive that amount of gold"},
    {IMP_CANT_TAKE_FORCA, "The military can't go past its limit"},
    {IMP_NO_REQUIRED_TEC, "The empire doesn't have the required technology"},

    {TERR_NOT_FOUND, "Territory not found"},
    {TERR_ALREADY_CONQUERED, "Territory already conquered"},
    {TERR_TYPE_UNKNOWN, "Unknown territory type"},
    
    {TEC_ALREADY_BOUGHT, "This technology was bought previously"},
    {TEC_DOESNT_EXIST, "Nonexistent technology"},

    {EVNT_NOT_FOUND, "Event not found"},

    {SAVE_NOT_FOUND, "Save not found"},
    {SAVE_USER_CANCEL, "Canceled by the user"},

    {FIM_JOGO, "The game reached its end"} 
};

char* codeToString(int key) {
    int i;

    for (i = 0; i < NR_CODES; i++) {
        if (codes[i].key == key) {
            return codes[i].value;
        }
    }

    return NULL;
}