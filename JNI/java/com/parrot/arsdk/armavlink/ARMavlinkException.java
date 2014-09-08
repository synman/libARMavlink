
package com.parrot.arsdk.armavlink;


public class ARMavlinkException extends Exception
{	
    private ARMAVLINK_ERROR_ENUM error;
    
    /**
     * ARMavlinkException constructor
     * @return void
     */
    public ARMavlinkException()
    {
        error = ARMAVLINK_ERROR_ENUM.ARMAVLINK_ERROR;
    }
    
    /**
     * ARMavlinkException constructor
     * @param error ARMAVLINK_ERROR_ENUM error code
     * @return void
     */
    public ARMavlinkException(ARMAVLINK_ERROR_ENUM error) 
    {
        this.error = error;
    }
    
    /**
     * ARMavlinkException constructor
     * @param error int error code
     * @return void
     */
    public ARMavlinkException(int error) 
    {
        this.error = ARMAVLINK_ERROR_ENUM.getFromValue(error);
    }
    
    /**
     * Gets ARUpdater ERROR code
     * @return {@link ARMAVLINK_ERROR_ENUM} error code
     */
    public ARMAVLINK_ERROR_ENUM getError()
    {
        return error;
    }
    
    /**
     * Sets ARUpdater ERROR code
     * @param error {@link ARMAVLINK_ERROR_ENUM} error code     
     * @return void
     */
    public void setError(ARMAVLINK_ERROR_ENUM error)
    {
        this.error = error;
    }
    
    /**
     * Gets ARMavlinkException string representation
     * @return String Exception representation
     */
    public String toString ()
    {
        String str;
        
        if (null != error)
        {
            str = "ARMavlinkException [" + error.toString() + "]";
        }
        else
        {
            str = super.toString();
        }
        
        return str;
    }
}

