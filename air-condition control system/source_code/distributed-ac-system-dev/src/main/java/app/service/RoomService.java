package app.service;

interface RoomService {
    public String requestPowerOn(int roomId);
    public String requestPowerOff(int roomId);
    public String changeTargetTemp(int roomId, int tarTemp);
    public String changeFanSpeed(int roomId, String fanSpeed);
}
