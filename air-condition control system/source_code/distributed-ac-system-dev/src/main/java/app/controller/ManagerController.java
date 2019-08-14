package app.controller;


import app.object.RoomStatistics;
import app.service.ReportService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RestController;

import javax.servlet.http.HttpServletRequest;
import java.util.ArrayList;

@RestController
@RequestMapping("/manager")
public class ManagerController {
    @Autowired
    private ReportService ms;

    @GetMapping("/queryreport")
    public ArrayList<RoomStatistics> QueryReport(HttpServletRequest request) {

        String[] tmp=request.getParameterValues("list_Roomid");
        ArrayList<Integer> roomlist=new ArrayList<>();

        for(String nowStr:tmp) {
            roomlist.add(Integer.parseInt(nowStr));
        }

        ArrayList<RoomStatistics> roomStatisticsList =new ArrayList<RoomStatistics>();
        Integer reportType=Integer.valueOf(request.getParameter("type_Report"));
        String year=request.getParameter("year");
        String month=request.getParameter("month");
        String day=request.getParameter("day");
        String stopTime=year+"-"+month+"-"+day+"T"+"23:59:59";
        String startTime="0000-00-00";
        switch (reportType) {
            case 0:startTime=year+"-"+month+"-"+day+"T"+"00:00:00";break;
            case 1:
                month=String.format("%02d",Integer.valueOf(month));
                startTime=year+"-"+month+"-"+"01"+"T"+"00:00:00";
                stopTime=year+"-"+month+"-"+"31"+"T"+"23:59:59";
                break;
            case 2:
                year=String.format("%04d",Integer.valueOf(year));
                startTime=year+"-"+"01"+"-01"+"T"+"00:00:00";
                stopTime=year+"-"+"12"+"-"+"31"+"T"+"23:59:59";
                break;
        }

        for(int roomid:roomlist) {
            roomStatisticsList.add(ms.queryRoom(roomid,startTime,stopTime));
        }
        return roomStatisticsList;
    }

}
