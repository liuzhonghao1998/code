package app.service;

import app.entity.RD;
import app.mapper.RDRMapper;
import app.object.RDR;
import app.object.RoomServiceListItem;
import app.entity.RDExample;
import org.springframework.beans.factory.annotation.Autowired;

import java.time.LocalDateTime;
import java.util.List;

@org.springframework.stereotype.Service
public class RDRService{
    @Autowired
    private RDRMapper servicedetailmapper;


    public RD RStoRDR(RoomServiceListItem rs) {
        RD d=new RD();
        d.setFee(rs.getCurrentFee());
        d.setFunspeed(rs.getFanSpeed());
        d.setRoomid(rs.getRoomId());
        d.setStarttime(rs.getStartTime().toString());
        d.setStoptime(LocalDateTime.now().toString() );
        d.setFeerate(rs.getFeeRate());
        d.setServicedetailid(0);
        return d;
    }
    public void addRDR(RoomServiceListItem rs) {
        servicedetailmapper.insert(RStoRDR(rs)
        );
    }

    public RDR queryRDR(int roomId, String startTime, String stopTime) {

        RDExample se=new RDExample();
        se.createCriteria().andRoomidEqualTo(roomId).andStarttimeBetween(startTime,stopTime).andStoptimeBetween(startTime,stopTime);
        List<RD> RDList =
                servicedetailmapper.selectByExample(se);
        RDR r=new RDR();
        for(RD s: RDList) {
            r.addServiceDetail(s);
        }
        if(r.getRDList().size() == 0)
            return null;
        else
            return r;
    }


}
