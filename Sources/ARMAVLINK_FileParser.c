/**
 * @file ARMAVLINK_FileParser.c
 * @brief Mavlink File Parser
 * @date 14/05/2014
 * @author djavan.bertrand@parrot.com
 */
#include <stdlib.h>
#include <stdio.h>
#include <libARSAL/ARSAL_Print.h>
#include "ARMAVLINK_FileParser.h"
#include "ARMAVLINK_WaypointUtils.h"
#include <string.h>

/* ***************************************
 *
 *             define :
 *
 *****************************************/
#define ARMAVLINK_FILE_PARSER_TAG                                "ARMAVLINK_FileParser"

#define ARMAVLINK_FILE_PARSER_FILE_HEADER                        "QGC WPL 120"
#define ARMAVLINK_FILE_PARSER_MAX_CHAR_IN_LINE                   255
#define ARMAVLINK_FILE_PARSER_QGC_WORD                           "QGC"
#define ARMAVLINK_FILE_PARSER_WPL_WORD                           "WPL"
/* ***************************************
 *
 *             functions :
 *
 *****************************************/
ARMAVLINK_FileParser_t* ARMAVLINK_FileParser_New(eARMAVLINK_ERROR *error)
{
    ARMAVLINK_FileParser_t *fileParser = NULL;
    eARMAVLINK_ERROR err = ARMAVLINK_OK;
    
    if(err == ARMAVLINK_OK)
    {
        /* Create the file parser */
        fileParser = malloc (sizeof (ARMAVLINK_FileParser_t));
        if (fileParser == NULL)
        {
            err = ARMAVLINK_ERROR_ALLOC;
        }
    }
    
    /* delete the file parser if an error occurred */
    if (err != ARMAVLINK_OK)
    {
        ARSAL_PRINT (ARSAL_PRINT_ERROR, ARMAVLINK_FILE_PARSER_TAG, "error: %s", ARMAVLINK_Error_ToString (err));
        ARMAVLINK_FileParser_Delete (&fileParser);
    }
    
    /* return the error */
    if (error != NULL)
    {
        *error = err;
    }
    
    return fileParser;
}

void ARMAVLINK_FileParser_Delete(ARMAVLINK_FileParser_t **fileParser)
{
    ARMAVLINK_FileParser_t *fileParserPtr = NULL;
    
    if (fileParser)
    {
        fileParserPtr = *fileParser;
        
        // Uninitialize here
        
        if (fileParserPtr)
        {
            free (fileParserPtr);
            fileParserPtr = NULL;
        }
        
        *fileParser = NULL;
    }
}

eARMAVLINK_ERROR ARMAVLINK_FileParser_Parse(ARMAVLINK_FileParser_t *fileParser, const char *const filePath, waypoint_list_t *waypointList)
{
    eARMAVLINK_ERROR error = ARMAVLINK_OK;
    
    FILE *file;
    char line[ARMAVLINK_FILE_PARSER_MAX_CHAR_IN_LINE];
    
    // check params
    if (waypointList == NULL || filePath == NULL)
    {
        error = ARMAVLINK_ERROR_BAD_PARAMETER;
    }
    
    // try to open the file
    if(error == ARMAVLINK_OK)
    {
        file = fopen(filePath,"r");
        if (file == NULL)
        {
            error = ARMAVLINK_ERROR_FILE_PARSER_FILE_NOT_FOUND;
        }
    }
    
    // read the file
    int i = 0;
    while ((ARMAVLINK_OK == error) &&
           (fgets(line, ARMAVLINK_FILE_PARSER_MAX_CHAR_IN_LINE, file) != NULL))
    {
        // the first line is the qgc description
        if (i == 0)
        {
            ARMAVLINK_FileParser_ReadFirstLine(fileParser, line);
        }
        else
        {
            ARMAVLINK_FileParser_ReadMavlinkCommand(fileParser, line, waypointList);
        }
        
        
        i++;
    }    
    return error;
}

eARMAVLINK_ERROR ARMAVLINK_FileParser_ReadFirstLine(ARMAVLINK_FileParser_t *fileParser, char *line)
{
    eARMAVLINK_ERROR error = ARMAVLINK_OK;
    
    char *token;
    
    token = strtok(line, " ");
    if (strcmp(token, ARMAVLINK_FILE_PARSER_QGC_WORD) != 0)
    {
        error = ARMAVLINK_ERROR_FILE_PARSER_WORD_NOT_EXPTECTED;
    }
    
    if (error == ARMAVLINK_OK)
    {
        // use NULL to reuse the last string
        token = strtok(NULL, " ");
        if (strcmp(token, ARMAVLINK_FILE_PARSER_WPL_WORD) != 0)
        {
            error = ARMAVLINK_ERROR_FILE_PARSER_WORD_NOT_EXPTECTED;
        }
    }
    
    if (error == ARMAVLINK_OK)
    {
        token = strtok(line, " ");
        if (token != NULL)
        {
            fileParser->mavlinkVersion = malloc(sizeof(char) * strlen(token));
            strcpy(fileParser->mavlinkVersion, token);
        }
        else
        {
            error = ARMAVLINK_ERROR_FILE_PARSER_WORD_NOT_EXPTECTED;
        }
    }
    
    return error;
}

eARMAVLINK_ERROR ARMAVLINK_FileParser_ReadMavlinkCommand(ARMAVLINK_FileParser_t *fileParser, char *line, waypoint_list_t *waypointList)
{
    char *token;
    
    float param1;
    float param2;
    float param3;
    float param4;
    float longitude;
    float latitude;
    float altitude;
    uint16_t seq;
    uint16_t command;
    uint8_t frame;
    uint8_t current;
    uint8_t autocontinue;
    
    mavlink_mission_item_t waypoint;
    
    eARMAVLINK_ERROR error = ARMAVLINK_OK;
    
    // <INDEX> <CURRENT WP> <COORD FRAME> <COMMAND> <PARAM1> <PARAM2> <PARAM3> <PARAM4> <PARAM5/X/LONGITUDE> <PARAM6/Y/LATITUDE> <PARAM7/Z/ALTITUDE> <AUTOCONTINUE>
    // where each space is a tabulation
    
    // get the index
    token = strtok(line, "\t");
    if (token != NULL)
    {
        seq = atoi(token);
    }
    else
    {
        error = ARMAVLINK_ERROR_FILE_PARSER_WORD_NOT_EXPTECTED;
    }
    
    // get the current
    if (ARMAVLINK_OK == error)
    {
        token = strtok(NULL, "\t");
        if (token != NULL)
        {
            current = atoi(token);
        }
        else
        {
            error = ARMAVLINK_ERROR_FILE_PARSER_WORD_NOT_EXPTECTED;
        }
    }
    
    // get the frame
    if (ARMAVLINK_OK == error)
    {
        token = strtok(NULL, "\t");
        if (token != NULL)
        {
            frame = atoi(token);
        }
        else
        {
            error = ARMAVLINK_ERROR_FILE_PARSER_WORD_NOT_EXPTECTED;
        }
    }
    
    // get the command
    if (ARMAVLINK_OK == error)
    {
        token = strtok(NULL, "\t");
        if (token != NULL)
        {
            command = atoi(token);
        }
        else
        {
            error = ARMAVLINK_ERROR_FILE_PARSER_WORD_NOT_EXPTECTED;
        }
    }
    
    // get the param1
    if (ARMAVLINK_OK == error)
    {
        token = strtok(NULL, "\t");
        if (token != NULL)
        {
            param1 = atof(token);
        }
        else
        {
            error = ARMAVLINK_ERROR_FILE_PARSER_WORD_NOT_EXPTECTED;
        }
    }
    
    // get the param2
    if (ARMAVLINK_OK == error)
    {
        token = strtok(NULL, "\t");
        if (token != NULL)
        {
            param2 = atof(token);
        }
        else
        {
            error = ARMAVLINK_ERROR_FILE_PARSER_WORD_NOT_EXPTECTED;
        }
    }
    
    // get the param3
    if (ARMAVLINK_OK == error)
    {
        token = strtok(NULL, "\t");
        if (token != NULL)
        {
            param3 = atof(token);
        }
        else
        {
            error = ARMAVLINK_ERROR_FILE_PARSER_WORD_NOT_EXPTECTED;
        }
    }
    
    // get the param4
    if (ARMAVLINK_OK == error)
    {
        token = strtok(NULL, "\t");
        if (token != NULL)
        {
            param4 = atof(token);
        }
        else
        {
            error = ARMAVLINK_ERROR_FILE_PARSER_WORD_NOT_EXPTECTED;
        }
    }
    
    // get the longitude
    if (ARMAVLINK_OK == error)
    {
        token = strtok(NULL, "\t");
        if (token != NULL)
        {
            longitude = atof(token);
        }
        else
        {
            error = ARMAVLINK_ERROR_FILE_PARSER_WORD_NOT_EXPTECTED;
        }
    }
    
    // get the latitude
    if (ARMAVLINK_OK == error)
    {
        token = strtok(NULL, "\t");
        if (token != NULL)
        {
            latitude = atof(token);
        }
        else
        {
            error = ARMAVLINK_ERROR_FILE_PARSER_WORD_NOT_EXPTECTED;
        }
    }
    
    // get the altitude
    if (ARMAVLINK_OK == error)
    {
        token = strtok(NULL, "\t");
        if (token != NULL)
        {
            altitude = atof(token);
        }
        else
        {
            error = ARMAVLINK_ERROR_FILE_PARSER_WORD_NOT_EXPTECTED;
        }
    }
    
    // get the autocontinue
    if (ARMAVLINK_OK == error)
    {
        token = strtok(NULL, "\t");
        if (token != NULL)
        {
            autocontinue = atoi(token);
        }
        else
        {
            error = ARMAVLINK_ERROR_FILE_PARSER_WORD_NOT_EXPTECTED;
        }
    }
    
    if (ARMAVLINK_OK == error)
    {
        error = ARMAVLINK_WaypointUtils_CreateMavlinkMissionItemWithAllParams(&waypoint, param1, param2, param3, param4,
                                                                              latitude, longitude, altitude, command,
                                                                              seq, frame, current, autocontinue);
    }
    
    if (ARMAVLINK_OK == error)
    {
        ARMAVLINK_ListUtils_WaypointListAdd(waypointList, &waypoint);
    }
    
    return error;
}

