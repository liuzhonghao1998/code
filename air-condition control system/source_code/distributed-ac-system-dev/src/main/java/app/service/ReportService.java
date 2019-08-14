package app.service;

import app.mapper.billMapper;
import app.object.RoomStatistics;
import app.entity.bill;
import app.entity.billExample;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

import java.util.List;

@Service
public class ReportService {
    @Autowired
    private billMapper bm;

    public RoomStatistics queryRoom(int roomid, String startTime, String stopTime) {
        RoomStatistics rs=new RoomStatistics(roomid);
        billExample be=new billExample();
        billExample.Criteria criteria=be.createCriteria();
        criteria.andRoomidEqualTo(roomid).andStarttimeBetween(startTime,stopTime).andStoptimeBetween(startTime,stopTime);
        List<bill> bl= bm.selectByExample(be);
        for(bill b:bl){
            rs.addBill(b);
        }
        return rs;
    }
}
