package app.service;

import app.object.ACParameters;
import app.object.Room;
import app.object.RoomState;
import app.object.RoomServiceListItem;
import app.entity.User;
import app.entity.bill;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.scheduling.annotation.Scheduled;
import org.springframework.stereotype.Component;

import java.time.Duration;
import java.time.LocalDateTime;
import java.util.ArrayList;
import java.util.Collections;
import java.util.List;
import java.util.Random;

@Component
public class Service implements RoomService, ReceptionService{
    private List<RoomServiceListItem> roomServiceListItemList;
    private List<RoomServiceListItem> roomWaitList;
    private List<Room> roomList;
    private List<bill> billList;
    @Autowired
    private ACParameters p;
    @Autowired
    private BillService billService;
    @Autowired
    private RDRService RDRService;
    public void init() {
        roomWaitList = Collections.synchronizedList(new ArrayList<>());
        roomServiceListItemList = Collections.synchronizedList(new ArrayList<>());
        roomList = Collections.synchronizedList(new ArrayList<>());
        billList = Collections.synchronizedList(new ArrayList<>());
        for(int i = 0; i <= 4; i++) {
            roomList.add(new Room());
            billList.add(new bill(i));
        }
    }

    private RoomServiceListItem getRoomService(int id) {
        for (RoomServiceListItem i: roomServiceListItemList) {
            if(i.getRoomId() == id)
                return i;
        }
        for (RoomServiceListItem i: roomWaitList) {
            if(i.getRoomId() == id)
                return i;
        }
        return null;
    }

    private void deleteRoomService(int id) {
        for (RoomServiceListItem i: roomServiceListItemList) {
            if(i.getRoomId() == id) {
                roomServiceListItemList.remove(i);
                return;
            }
        }
        for (RoomServiceListItem i: roomWaitList) {
            if(i.getRoomId() == id) {
                roomWaitList.remove(i);
                return;
            }
        }
    }

    public String initTemp(int roomId, int initTemp) {
        roomList.get(roomId).setInitTemp(initTemp);
        roomList.get(roomId).setNowTemp(initTemp);
        return "success";
    }

    public String requestPowerOn(int roomId) {
        if (roomList.get(roomId).getIsPowerOn()) return "Error: It's already power On.";
        roomList.get(roomId).setPowerOn(true);
        billService.addPOC(billList.get(roomId));
        RoomServiceListItem i = new RoomServiceListItem(roomId, p.getDefaultTargetTemp(), p.getDefaultFanSpeed(), LocalDateTime.now(), p.getDefaultFeeRate());
        roomWaitList.add(i);
        billList.get(roomId).setStarttime(LocalDateTime.now().toString());
        return "success";
    }


    public String requestPowerOff(int roomId) {
        if (roomList.get(roomId).getIsPowerOn()== false) return "Error: It's already power Off.";
        RoomServiceListItem serv = getRoomService(roomId);
        RDRService.addRDR(serv);
        billService.addSC(billList.get(roomId),serv);

        deleteRoomService(roomId);
        roomList.get(roomId).clear();
        return "success";
    }

    public String changeTargetTemp(int roomId, int tarTemp) {
        if (roomList.get(roomId).getIsPowerOn() == false) return "Error: It's already power Off.";
        RoomServiceListItem i = getRoomService(roomId);
        if(i == null) {
            return "Error: Invaild request";
        }
        if (roomServiceListItemList.contains(i)) {
            RDRService.addRDR(i);
            billService.addSC(billList.get(roomId), i);
        }
        billService.addTC(billList.get(roomId));
        i.setStartTime(LocalDateTime.now());
        i.setCurrentFee(0);
        i.setTarTemp(tarTemp);
        return "success";
    }

    public String changeFanSpeed(int roomId, String fanSpeed) {
        if (roomList.get(roomId).getIsPowerOn() == false) return "Error: It's already power Off.";
        RoomServiceListItem i = getRoomService(roomId);
        if(i == null) {
            return "Error: Invaild request";
        }

        if (roomServiceListItemList.contains(i)) {
            RDRService.addRDR(i);
            billService.addSC(billList.get(roomId), i);
        }

        billService.addFC(billList.get(roomId));
        i.setStartTime(LocalDateTime.now());
        i.setFeeRate(p.getFeeRate(fanSpeed));
        i.setFanSpeed(fanSpeed);

        return "success";
    }


    public RoomState checkRoomState(int roomId) {
        RoomServiceListItem i = getRoomService(roomId);
        Room room = roomList.get(roomId);
        bill b = billList.get(roomId);
        RoomState rs = new RoomState();
        if (i != null) {
            rs.setTarTemp(i.getTarTemp());
            rs.setFeeRate(i.getFeeRate());
            rs.setFanSpeed(i.getFanSpeed());
        }
        rs.setInService(room.getIsInService());
        rs.setTotalFee(b.getTotalfee());
        rs.setNowTemp(room.getNowTemp());
        rs.setPowerOn(room.getIsPowerOn());
        rs.setRunningTime(b.getRunningtime());
        return rs;
    }

    private String createRandomNumber(int length) {
        StringBuilder sb=new StringBuilder();
        Random r=new Random();
        for(int i=0;i<length;i++)
            sb.append(r.nextInt(10));
        return sb.toString();
    }

    public User checkIn(String idNumber) {
        LocalDateTime cur=LocalDateTime.now();
        for(int i=1;i<=4;i++) {
            Room nowRoom = roomList.get(i);
            if (!nowRoom.getIsCheckIn()) {
                User u = new User();
                u.setRoomid(i);
                u.setUsername(idNumber);
                Random r=new Random();
                u.setPassword(createRandomNumber(r.nextInt(3)+3));
                nowRoom.init(cur);
                billService.initBill(billList.get(i),cur.toString(),u);
                return u;
            }
        }
        return null;
    }
    public String checkOut(int roomId) {
        Room r=roomList.get(roomId);
        bill b=billList.get(roomId);
        LocalDateTime cur=LocalDateTime.now();

        if (r==null ||!r.getIsCheckIn()) return "Error : Bad request";
        if (r.getIsPowerOn()) {requestPowerOff(roomId); }
        r.setCheckIn(false);
        b.setStoptime(cur.toString());
        billService.addBill(b);
        return "Success";
    }

    @Scheduled(fixedRate = 1000)
    private void billing() {
        if (p.getSystemState()==null) return;
        if (!(p.getSystemState().equals("ON"))) return;
        for(RoomServiceListItem s: roomServiceListItemList) {
            s.setCurrentFee(s.getFeeRate()/60 +s.getCurrentFee());
        }
    }

    private void startService(RoomServiceListItem i) {
        int roomId = i.getRoomId();
        i.setStartTime(LocalDateTime.now());
        roomList.get(roomId).setInService(true);
        roomServiceListItemList.add(i);
    }

    private void stopService(RoomServiceListItem i) {

        int roomId = i.getRoomId();
        RDRService.addRDR(i);
        billService.addRC(billList.get(roomId));
        billService.addSC(billList.get(roomId),i);
        i.setStartTime(LocalDateTime.now());
        i.setCurrentFee(0);
        roomList.get(roomId).setInService(false);
        roomServiceListItemList.remove(i);
        roomWaitList.add(i);
    }

    private String getLowestRunningFanSpeed() {

        for (RoomServiceListItem s: roomServiceListItemList) {
            if(s.getFanSpeed().equals("LOW"))
                return "LOW";
        }
        for (RoomServiceListItem s: roomServiceListItemList) {
            if(s.getFanSpeed().equals("MIDDLE"))
                return "MIDDLE";
        }
        for (RoomServiceListItem s: roomServiceListItemList) {
            if(s.getFanSpeed().equals("HIGH"))
                return "HIGH";
        }
        return "OFF";
    }
    private int getFanSpeedInt(String s){
        int a=0;
        switch (s) {
            case "LOW":a=1;break;
            case "MIDDLE":a=2;break;
            case "HIGH":a=3;break;
        }
        return a;
    }
    private int compareFanSpeed(String a, String b) {
        return getFanSpeedInt(a)-getFanSpeedInt(b);
    }

    private RoomServiceListItem getLongestRunningServiceWithLowestFanSpeed() {
        if (roomServiceListItemList.size()==0) return null;
        RoomServiceListItem i= roomServiceListItemList.get(0);
        for(RoomServiceListItem s: roomServiceListItemList) {
            int delta=compareFanSpeed(s.getFanSpeed(),i.getFanSpeed());
            if (delta==1) continue;
            if (delta==-1) {
                i=s;
            }
            else if (s.getStartTime().isBefore(i.getStartTime()))i = s;
        }
        return i;
    }
    private boolean isWaitingService(int roomID) {
        for (RoomServiceListItem i: roomWaitList)
            if(i.getRoomId() == roomID) return true;
        return false;
    }

    private void ReleaseLongestTime(RoomServiceListItem wi) {
        int interval = (int) Duration.between(wi.getStartTime(), LocalDateTime.now()).getSeconds();
        if (interval >= 120) {
            RoomServiceListItem si = getLongestRunningServiceWithLowestFanSpeed();
            stopService(si);
            startService(wi);
            roomWaitList.remove(wi);

        }
    }
    private void ReleaseSlowestSpeed(RoomServiceListItem wi){
        RoomServiceListItem si = getLongestRunningServiceWithLowestFanSpeed();
        stopService(si);
        startService(wi);
        roomWaitList.remove(wi);
    }

    @Scheduled(fixedRate = 1000)
    private void Schedule() {
        if (p.getSystemState()==null || p.getSystemState().equals("ON")==false) return;
        for (int i = 1; i <= 4; i++) {
            Room r = roomList.get(i);
            if(r.getIsInService()) {
                RoomServiceListItem s = getRoomService(i);
                if (Math.abs(r.getNowTemp() - r.getLastTarTemp()) <0.5) {// arrive target temperature
                    r.setLastFanSpeed(s.getFanSpeed());
                    r.setLastTarTemp(s.getTarTemp());
                    r.setInService(false);
                    roomServiceListItemList.remove(s);
                }
            }
            else {
                if(r.getIsPowerOn() == false||isWaitingService(i)) continue;
                if(Math.abs(r.getNowTemp() - r.getLastTarTemp()) >= 0.8) {
                    RoomServiceListItem si = new RoomServiceListItem(i, r.getLastTarTemp(), r.getLastFanSpeed(), LocalDateTime.now(), p.getFeeRate(r.getLastFanSpeed()));
                    roomWaitList.add(si);
                }
            }
        }
        while(roomWaitList.size() > 0 && roomServiceListItemList.size() < 3) startService(roomWaitList.remove(0));
        for(RoomServiceListItem wi:roomWaitList){
            String LRFanSpeed = getLowestRunningFanSpeed();
            String waitingFanSpeed = wi.getFanSpeed();
            if(compareFanSpeed(waitingFanSpeed, LRFanSpeed) < 0) continue;
            else if(compareFanSpeed(waitingFanSpeed, LRFanSpeed) > 0) {ReleaseSlowestSpeed(wi);return;}
            else { ReleaseLongestTime(wi);return;}
        }
    }
}
