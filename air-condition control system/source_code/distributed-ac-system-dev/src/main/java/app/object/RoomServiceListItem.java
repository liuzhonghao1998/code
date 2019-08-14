package app.object;

import java.time.LocalDateTime;

public class RoomServiceListItem {
    private int roomId;
    private int tarTemp;
    private String fanSpeed;
    private LocalDateTime startTime;
    private double feeRate;
    private double currentFee;

    public RoomServiceListItem(int roomId, int tarTemp, String fanSpeed, LocalDateTime startTime, double feeRate) {
        this.roomId = roomId;

        this.tarTemp = tarTemp;
        this.fanSpeed = fanSpeed;
        this.startTime = startTime;
        this.feeRate = feeRate;
        this.currentFee = 0;
    }

    public int getRoomId() {
        return roomId;
    }

    public void setRoomId(int roomId) {
        this.roomId = roomId;
    }

    public int getTarTemp() {
        return tarTemp;
    }

    public void setTarTemp(int tarTemp) {
        this.tarTemp = tarTemp;
    }

    public String getFanSpeed() {
        return fanSpeed;
    }

    public void setFanSpeed(String fanSpeed) {
        this.fanSpeed = fanSpeed;
    }

    public LocalDateTime getStartTime() {
        return startTime;
    }

    public void setStartTime(LocalDateTime startTime) {
        this.startTime = startTime;
    }

    public double getFeeRate() {
        return feeRate;
    }

    public void setFeeRate(double feeRate) {
        this.feeRate = feeRate;
    }

    public double getCurrentFee() {
        return currentFee;
    }

    public void setCurrentFee(double currentFee) {
        this.currentFee = currentFee;
    }
}
