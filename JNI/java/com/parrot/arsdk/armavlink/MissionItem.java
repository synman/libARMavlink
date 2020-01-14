package com.parrot.arsdk.armavlink;

public class MissionItem {

//    private float param1; //< PARAM1 / For NAV command MISSIONs: Radius in which the MISSION is accepted as reached, in meters
//    private float param2; //< PARAM2 / For NAV command MISSIONs: Time that the MAV should stay inside the PARAM1 radius before advancing, in milliseconds
    private float param3; //< PARAM3 / For LOITER command MISSIONs: Orbit to circle around the MISSION, in meters. If positive the orbit direction should be clockwise, if negative the orbit direction should be counter-clockwise.
//    private float param4; //< PARAM4 / For NAV and LOITER command MISSIONs: Yaw orientation in degrees, [0..360] 0 = NORTH
//    private float x; //< PARAM5 / local: x position, global: latitude
//    private float y; //< PARAM6 / y position: global: longitude
//    private float z; //< PARAM7 / z position: global: altitude
//    private int seq; //< Sequence
    private int command; //< The scheduled action for the MISSION. see MAV_CMD in common.xml MAVLink specs
//    private int target_system; //< System ID
//    private int target_component; //< Component ID
//    private int frame; //< The coordinate system of the MISSION. see MAV_FRAME in mavlink_types.h
//    private int autocontinue; //< autocontinue to next wp

    private int id;

    public MissionItem(int id, ARMavlinkMissionItem item) {
//        param1 = item.getParam1();
//        param2 = item.getParam2();
        param3 = item.getParam3();
//        param4 = item.getParam4();
//        x = item.getX();
//        y = item.getY();
//        z = item.getZ();
//        seq = item.getSeq();
        command = item.getCommand();
//        target_system = item.getTargetSystem();
//        target_component = item.getTargetComponent();
//        frame = item.getFrame();
//        autocontinue = item.getAutocontinue();

        this.id = id;
    }

//    public float getParam1() {
//        return param1;
//    }
//
//    public float getParam2() {
//        return param2;
//    }

    public float getParam3() {
        return param3;
    }

//    public float getParam4() {
//        return param4;
//    }
//
//    public float getX() {
//        return x;
//    }
//
//    public float getY() {
//        return y;
//    }
//
//    public float getZ() {
//        return z;
//    }
//
//    public int getSeq() {
//        return seq;
//    }

    public int getCommand() {
        return command;
    }

//    public int getTarget_system() {
//        return target_system;
//    }
//
//    public int getTarget_component() {
//        return target_component;
//    }
//
//    public int getFrame() {
//        return frame;
//    }
//
//    public int getAutocontinue() {
//        return autocontinue;
//    }

    public int getId() {
        return id;
    }
}
