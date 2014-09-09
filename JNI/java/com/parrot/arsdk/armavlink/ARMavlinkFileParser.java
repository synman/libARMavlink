
package com.parrot.arsdk.armavlink;

import com.parrot.arsdk.arsal.ARSALPrint;

public class ARMavlinkFileParser
{
    private static String TAG = ARMavlinkFileGenerator.class.getSimpleName();

    private native long nativeNew() throws ARMavlinkException;
    private native void nativeDelete(long nativeFileParser);
    private native void nativeParse(long nativeFileParser, String filePath, long nativeMissionList);

    private long nativeFileParser = 0;

    /**
     * ARMavlinkFileGenerator constructor
     */
    public ARMavlinkFileParser () throws ARMavlinkException
    {
        nativeFileParser = nativeNew();
    }

    /**
     * Parse a Mavlink file and store it in a list
     * @param filePath the path of the file to parse
     * @return missionItemList a list of all mission items
     */
    public ARMavlinkMissionItemList parseFile(String filePath) throws ARMavlinkException
    {
        ARMavlinkMissionItemList missionList = new ARMavlinkMissionItemList();
        nativeParse(nativeFileParser, filePath, missionList.getNativePointre());
        return missionList;
    }

    /**
     * Dispose ARMavlinkFileGenerator
     */
    public void dispose() 
    {
        if(nativeFileParser != 0) {
            nativeDelete(nativeFileParser);
            nativeFileParser = 0;
        }
    }

    /**
     * Destructor
     */
    public void finalize () throws Throwable 
    {
        try {
            dispose ();
        } finally {
            super.finalize ();
        }
    }

}
