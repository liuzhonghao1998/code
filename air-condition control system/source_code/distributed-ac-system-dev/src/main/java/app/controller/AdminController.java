package app.controller;


import app.object.ACParameters;
import app.object.RoomState;
import app.service.Service;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.*;

@RestController
@RequestMapping("/admin")
public class AdminController{
    @Autowired
    ACParameters p;

    @Autowired
    Service s;

    @GetMapping(value = "/powerOn")
    public String powerOn() {
        p.setSystemState("READY");
        return "{ \"statue\" : \""+ p.getSystemState()+"\"}";
    }

    @PostMapping(value = "/setParams")
    public ACParameters setParams(@RequestParam(value="isCooling") boolean isCooling,
                                  @RequestParam(value="tempHighLimit") int tempHighLimit,
                                  @RequestParam(value="tempLowLimit") int tempLowLimit,
                                  @RequestParam(value="defaultTargetTemp") int defaultTargetTemp,
                                  @RequestParam(value="feeRateHigh") double feeRateHigh,
                                  @RequestParam(value="feeRateMiddle") double feeRateMiddle,
                                  @RequestParam(value="feeRateLow") double feeRateLow,
                                  @RequestParam(value="defaultFunSpeed") String defaultFanSpeed) {

        p.setMode(isCooling ? "cool" : "heat");
        p.setTempHighLimit(tempHighLimit);
        p.setTempLowLimit(tempLowLimit);
        p.setDefaultTargetTemp(defaultTargetTemp);
        p.setFeeRateHigh(feeRateHigh);
        p.setFeeRateMiddle(feeRateMiddle);
        p.setFeeRateLow(feeRateLow);
        p.setDefaultFanSpeed(defaultFanSpeed);
        return p;
    }

    @GetMapping(value = "/startup")
    public String startUp() {
        p.setSystemState("ON");
        s.init();
		return "{ \"statue\" : \""+ p.getSystemState()+"\"}";
    }

    @GetMapping(value = "/roomState/{roomID}")
    public RoomState checkRoomState(@PathVariable int roomID) {
        return s.checkRoomState(roomID);
    }

}
