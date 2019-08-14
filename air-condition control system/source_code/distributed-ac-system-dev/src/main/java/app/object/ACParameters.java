package app.object;

import org.springframework.stereotype.Component;

@Component
public class ACParameters {
    private String mode;
    private int tempHighLimit;
    private int tempLowLimit;
    private int defaultTargetTemp;
    private double feeRateHigh;
    private double feeRateMiddle;
    private double feeRateLow;
    private String defaultFanSpeed;
    private String systemState;


    public double getDefaultFeeRate() {
        switch (defaultFanSpeed) {
            case "LOW":
                return feeRateLow;
            case "MIDDLE":
                return feeRateMiddle;
            case "HIGH":
                return feeRateHigh;
        }
        return -1;
    }

    public double getFeeRate(String fanSpeed) {
        switch (fanSpeed) {
            case "LOW":
                return feeRateLow;
            case "MIDDLE":
                return feeRateMiddle;
            case "HIGH":
                return feeRateHigh;
        }
        return -1;
    }

    public String getMode() {
        return mode;
    }

    public int getTempHighLimit() {
        return tempHighLimit;
    }

    public int getTempLowLimit() {
        return tempLowLimit;
    }

    public int getDefaultTargetTemp() {
        return defaultTargetTemp;
    }

    public double getFeeRateHigh() {
        return feeRateHigh;
    }

    public double getFeeRateMiddle() {
        return feeRateMiddle;
    }

    public double getFeeRateLow() {
        return feeRateLow;
    }

    public String getDefaultFanSpeed() {
        return defaultFanSpeed;
    }

    public String getSystemState() {
        return systemState;
    }

    public void setMode(String mode) {
        this.mode = mode;
    }

    public void setTempHighLimit(int tempHighLimit) {
        this.tempHighLimit = tempHighLimit;
    }

    public void setTempLowLimit(int tempLowLimit) {
        this.tempLowLimit = tempLowLimit;
    }

    public void setDefaultTargetTemp(int defaultTargetTemp) {
        this.defaultTargetTemp = defaultTargetTemp;
    }

    public void setFeeRateHigh(double feeRateHigh) {
        this.feeRateHigh = feeRateHigh;
    }

    public void setFeeRateMiddle(double feeRateMiddle) {
        this.feeRateMiddle = feeRateMiddle;
    }

    public void setFeeRateLow(double feeRateLow) {
        this.feeRateLow = feeRateLow;
    }

    public void setDefaultFanSpeed(String defaultFanSpeed) {
        this.defaultFanSpeed = defaultFanSpeed;
    }

    public void setSystemState(String systemState) {
        this.systemState = systemState;
    }
}
