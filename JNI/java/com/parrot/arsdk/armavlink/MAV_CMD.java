package com.parrot.arsdk.armavlink;

public enum MAV_CMD {
    MAV_CMD_NAV_WAYPOINT(16),
    MAV_CMD_DO_CHANGE_SPEED(178),
    MAV_CMD_SET_VIEW_MODE(50000);

    private final int id;
    MAV_CMD(int id)  { this.id = id; }
    public int getId() { return id; }
}