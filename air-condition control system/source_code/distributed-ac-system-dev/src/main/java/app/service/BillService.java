package app.service;

import app.mapper.billMapper;
import app.object.RoomServiceListItem;
import app.entity.*;
import org.springframework.beans.factory.annotation.Autowired;

import java.time.LocalDateTime;
import java.util.List;

@org.springframework.stereotype.Service
public class BillService{
    @Autowired
    private billMapper billmapper;

    public void initBill(bill b, String startTime, User u) {
        b.init();
        b.setRoomid(u.getRoomid());
        b.setUserid(u.getUserid());
        b.setStarttime(startTime);
    }

    public void addBill(bill b) {
        billmapper.insert(b);
    }
    public void addRC(bill b) {
        b.setSchedulecounter(b.getSchedulecounter()+1);
    }
    public void addPOC(bill b){
        b.setPoweroncounter(b.getPoweroncounter()+1);
    }
    public void addSC(bill b, RoomServiceListItem s) {
        b.setTotalfee(b.getTotalfee()+s.getCurrentFee());
        b.setRunningtime(b.getRunningtime()+(int)(java.time.Duration.between(s.getStartTime(), LocalDateTime.now()).getSeconds()));
        b.setDetailedrecordcounter(b.getDetailedrecordcounter()+1);
    }
    public void addTC(bill b) {
        b.setChangetempcounter(b.getChangetempcounter()+1);
    }
    public void addFC(bill b) {
        b.setChangefuncounter(b.getChangefancounter()+1);
    }

    public bill queryBill(int roomId, String startTime, String stopTime) {

        billExample be=new billExample();
        be.createCriteria()
                .andRoomidEqualTo(roomId)
                .andStarttimeBetween(startTime,stopTime)
                .andStoptimeBetween(startTime,stopTime);
        List<bill> bl=
                billmapper.selectByExample(be);
        if (bl.size()>0)
            return bl.get(bl.size()-1);
        return null;
    }

}
