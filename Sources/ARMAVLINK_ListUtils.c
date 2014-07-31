/**
 * @file ARMAVLINK_ListUtils.c
 * @brief ARMavlink library List Utils
 * @date 14/05/2014
 * @author djavan.bertrand@parrot.com
 */
#include <stdlib.h>
#include "ARMAVLINK_ListUtils.h"

/* ****************************************
 *
 *             define :
 *
 **************************************** */
#define ARMAVLINK_LIST_UTILS_TAG                "ARMAVLINK_ListUtils"
#define ARMAVLINK_LIST_UTILS_LIST_SIZE          32
#define ARMAVLINK_LIST_UTILS_LIST_MAX_INDEX     ((uint16_t) -1)

struct mission_item_list_t
{
    int size;
    int alloc_size;
    mavlink_mission_item_t *missionItems;
};

mission_item_list_t* ARMAVLINK_ListUtils_MissionItemListNew(void)
{
    mission_item_list_t *list = (mission_item_list_t *)malloc(sizeof(mission_item_list_t));
    if(list != NULL)
    {
        list->missionItems = (mavlink_mission_item_t *)malloc(sizeof(mavlink_mission_item_t) * ARMAVLINK_LIST_UTILS_LIST_SIZE);
        if(list->missionItems != NULL)
        {
            list->alloc_size = ARMAVLINK_LIST_UTILS_LIST_SIZE;
            list->size = 0;
        }
        else
        {
            free(list);
            list = NULL;
        }
    }
    
    return list;
}

uint16_t ARMAVLINK_ListUtils_MissionItemListAdd(mission_item_list_t *list, const mavlink_mission_item_t *const missionItem)
{
    uint16_t index = ARMAVLINK_LIST_UTILS_LIST_MAX_INDEX;
    
    if(list != NULL && missionItem != NULL)
    {
        if(list->size == list->alloc_size)
        {
            list->alloc_size += ARMAVLINK_LIST_UTILS_LIST_SIZE;
            mavlink_mission_item_t *new_mission_items = (mavlink_mission_item_t *)realloc(list->missionItems, sizeof(mavlink_mission_item_t) * list->alloc_size);
            if(new_mission_items != NULL)
            {
                list->missionItems = new_mission_items;
            }
        }
        
        index = list->size;
        memcpy(&(list->missionItems[index]), missionItem, sizeof(mavlink_mission_item_t));
        list->size++;
    }
    
    return index;
}

mavlink_mission_item_t* ARMAVLINK_ListUtils_MissionItemListGet(const mission_item_list_t *const list, const uint16_t index)
{
    mavlink_mission_item_t *retval = NULL;
    if(list != NULL && index < list->size && index >= 0)
    {
        retval = &list->missionItems[index];
    }
    
    return retval;
}

int ARMAVLINK_ListUtils_MissionItemListGetSize(const mission_item_list_t *const list)
{
    return list->size;
}

eARMAVLINK_ERROR ARMAVLINK_ListUtils_MissionItemListDeleteMissionItem(mission_item_list_t *list, const uint16_t index)
{
    eARMAVLINK_ERROR error = ARMAVLINK_OK;
    
    if ((list != NULL) &&
        (index < list->size) &&
        (index >= 0))
    {
        int nbMissionItemsToCopy = (list->size - index) - 1;
        if (nbMissionItemsToCopy > 0)
        {
            memcpy(&(list->missionItems[index]), &(list->missionItems[index+1]), nbMissionItemsToCopy * sizeof(mavlink_mission_item_t));
        }
        list->size--;
    }
    else
    {
        error = ARMAVLINK_ERROR_BAD_PARAMETER;
    }
    
    return error;
}

eARMAVLINK_ERROR ARMAVLINK_ListUtils_MissionItemListInsertMissionItem(mission_item_list_t *list, const mavlink_mission_item_t *const missionItem, const uint16_t index)
{
    eARMAVLINK_ERROR error = ARMAVLINK_OK;
    
    if ((list != NULL) &&
        (index <= list->size) &&
        (index >= 0) &&
        (missionItem != NULL))
    {
        if(list->size == list->alloc_size)
        {
            list->alloc_size += ARMAVLINK_LIST_UTILS_LIST_SIZE;
            mavlink_mission_item_t *new_mission_items = (mavlink_mission_item_t *)realloc(list->missionItems, sizeof(mavlink_mission_item_t) * list->alloc_size);
            if(new_mission_items != NULL)
            {
                list->missionItems = new_mission_items;
            }
        }
        
        int nbMissionItemsToCopy = (list->size - index);
        if (nbMissionItemsToCopy > 0)
        {
            memcpy(&(list->missionItems[index+1]), &(list->missionItems[index]), nbMissionItemsToCopy * sizeof(mavlink_mission_item_t));
        }
        memcpy(&(list->missionItems[index]), missionItem, sizeof(mavlink_mission_item_t));
        list->size++;
    }
    else
    {
        error = ARMAVLINK_ERROR_BAD_PARAMETER;
    }
    
    return error;

}

eARMAVLINK_ERROR ARMAVLINK_ListUtils_MissionItemListReplaceMissionItem(mission_item_list_t *list, const mavlink_mission_item_t *const missionItem, const uint16_t index)
{
    eARMAVLINK_ERROR error = ARMAVLINK_OK;
    
    if ((list != NULL) &&
        (index <= list->size) &&
        (index >= 0) &&
        (missionItem != NULL))
    {
        memcpy(&(list->missionItems[index]), missionItem, sizeof(mavlink_mission_item_t));
    }
    else
    {
        error = ARMAVLINK_ERROR_BAD_PARAMETER;
    }
    
    return error;
}

void ARMAVLINK_ListUtils_MissionItemListDelete(mission_item_list_t **list)
{
    mission_item_list_t *listPtr = NULL;
    
    if (list)
    {
        listPtr = *list;
        
        if (listPtr)
        {
            if(listPtr->missionItems != NULL)
            {
                free(listPtr->missionItems);
                listPtr->missionItems = NULL;
            }
            
            free (listPtr);
            listPtr = NULL;
        }
        
        *list = NULL;
    }
}

