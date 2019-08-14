package app.controller;

import app.object.ACParameters;
import app.object.RoomState;
import app.service.Service;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.*;

@RestController
@RequestMapping("/customer")
public class CustomerController {

    @Autowired
    Service s;

    @Autowired
    ACParameters p;

    @PostMapping("/setInitTemp")
    public String setInitTemp(@RequestParam(value="roomID") int roomID,
                              @RequestParam(value="initTemp") int initTemp) {

        return "{ \"statue\" : \""+s.initTemp(roomID, initTemp)+"\"}";
    }

    @PostMapping("/requestOn")
    public String requestOn(@RequestParam(value="roomID") int roomID) {

        return "{ \"statue\" : \""+s.requestPowerOn(roomID)+"\"," +
                "\"tempLowLimit\": " + p.getTempLowLimit() +","+
                "\"tempHighLimit\":" + p.getTempHighLimit() + "}";
    }

    @PostMapping("/requestOff")
    public String requestOff(@RequestParam(value="roomID") int roomID) {

        return "{ \"statue\" : \""+s.requestPowerOff(roomID)+"\"}";
    }

    @GetMapping("/requestRoomState")
    public RoomState requestRoomState(@RequestParam(value="roomID") int roomID) {

        return s.checkRoomState(roomID);
    }

    @PostMapping("/changeTargetTemp")
    public void changeTargetTemp(@RequestParam(value="roomID") int roomID, @RequestParam(value="targetTemp") int targetTemp) {

        s.changeTargetTemp(roomID, targetTemp);
    }

    @PostMapping("/changeFanSpeed")
    public void changeTargetFunSpeed(@RequestParam(value="roomID") int roomID, @RequestParam(value="targetFanSpeed") String targetFanSpeed) {

        s.changeFanSpeed(roomID, targetFanSpeed);
    }
}