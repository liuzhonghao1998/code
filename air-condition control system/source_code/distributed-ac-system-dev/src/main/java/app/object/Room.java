package app.object;

import java.time.LocalDateTime;

public class Room {
    private int initTemp;
    private double nowTemp;
    private int lastTarTemp;
    private String lastFanSpeed;
    private boolean isPowerOn;
    private boolean isInService;
    private boolean isCheckIn;
    private LocalDateTime startTime;

    public Room() {
        this.initTemp = 100;
        this.nowTemp = 100;
        this.lastTarTemp = -1;
        this.isPowerOn = false;
        this.isInService = false;
        this.isCheckIn = false;
        this.lastFanSpeed = "OFF";
        this.startTime = LocalDateTime.now();
    }

    public void clear() {
        this.isPowerOn = false;
        this.isInService = false;
    }

    public void init(LocalDateTime nowtime) {
        this.isPowerOn = false;
        this.isInService = false;
        this.lastFanSpeed = "OFF";
        this.startTime = nowtime;
        this.isCheckIn = true;
    }

    public int getInitTemp() {
        return initTemp;
    }

    public double getNowTemp() {
        return nowTemp;
    }

    public int getLastTarTemp() {
        return lastTarTemp;
    }

    public String getLastFanSpeed() {
        return lastFanSpeed;
    }

    public boolean getIsPowerOn() {
        return isPowerOn;
    }

    public boolean getIsInService() {
        return isInService;
    }

    public boolean getIsCheckIn() {
        return isCheckIn;
    }

    public LocalDateTime getStartTime() {
        return startTime;
    }

    public void setInitTemp(int initTemp) {
        this.initTemp = initTemp;
    }

    public void setNowTemp(double nowTemp) {
        this.nowTemp = nowTemp;
    }

    public void setLastTarTemp(int lastTarTemp) {
        this.lastTarTemp = lastTarTemp;
    }

    public void setLastFanSpeed(String lastFanSpeed) {
        this.lastFanSpeed = lastFanSpeed;
    }

    public void setPowerOn(boolean powerOn) {
        isPowerOn = powerOn;
    }

    public void setInService(boolean inService) {
        isInService = inService;
    }

    public void setCheckIn(boolean checkIn) {
        isCheckIn = checkIn;
    }

    public void setStartTime(LocalDateTime startTime) {
        this.startTime = startTime;
    }
}
