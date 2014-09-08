
package com.parrot.arsdk.armavlink;

import com.parrot.arsdk.arsal.ARSALPrint;

public class ARMavlinkMissionItemList
{
    private static String TAG = ARMavlinkMissionItemList.class.getSimpleName();

    private native long nativeMissionItemListNew();
    private native void nativeMissionItemListDelete(long nativeList);
    private native int nativeMissionItemListGetSize(long nativeList);
    private native long nativeMissionItemListGet(long nativeList, int index);

    private long nativeMissionItemList = 0;

    /**
     * ARMavlinkMissionItemList constructor
     * Can't be Instantiated by user
     */
    private ARMavlinkMissionItemList ()
    {
        nativeMissionItemList = nativeMissionItemListNew();
    }

    /**
     * ARMavlinkMissionItemList constructor
     * @param itemPtr ARMavlinkMissionItemList native Pointre
     */
    public ARMavlinkMissionItemList (long itemListPtr)
    {
        if(itemListPtr != 0){
            nativeMissionItemList = itemListPtr;
        } 
    }

    /**
     * Get a {@link ARMavlinkMissionItem} in the list according to its index
     * @param index the index of the mission item to return
     * @return {@link ARMavlinkMissionItem} mission item
     */
    public ARMavlinkMissionItem getMissionItem(int index)
    {
        ARMavlinkMissionItem missionItem = null;
        if(nativeMissionItemList != 0){
            long missionItemPtr = nativeMissionItemListGet(nativeMissionItemList, index);
            missionItem = new ARMavlinkMissionItem(missionItemPtr);
            missionItem.updateCommandCode();
        }
        return missionItem;
    }

    /**
     * Get the current size of the list (the number of mission item which are actually in the list)
     * @return the size of the list
     */
    public int getSize(){
        if(nativeMissionItemList != 0){
            return nativeMissionItemListGetSize(nativeMissionItemList);
        }else{
            return -1;
        }
    }

    /**
     * Dispose
     */
    public void dispose()
    {
        //NO dispose, il will be deleted when the file generator was deleted
    }

}
