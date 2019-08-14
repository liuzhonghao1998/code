package app.controller;


import app.object.RDR;
import app.entity.User;
import app.entity.bill;
import app.service.*;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.*;

@RestController
@RequestMapping("/receptionist")
public class ReceptionistController {

    @Autowired
    private Service s;
    @Autowired
    private RDRService sds;
    @Autowired
    private BillService bs;
    @Autowired
    private UserService us;

    @PostMapping("/adduser")

    public User checkInCustomer(@RequestParam(value="idnumber") String id) {

        User u= s.checkIn(id);
        if (u!=null) us.addUser(u);
        else {
            u=new User();
            u.setUserid(-1);
        }
        return u;
    }

    @PostMapping("/checkout")


    public String checkOutCustomer(@RequestParam(value="roomid") int roomid) {
        return "{ \"statue\" : \""+ s.checkOut(roomid)+"\"}";
    }


    @GetMapping("/createrdr")
    public RDR createRDR(@RequestParam(value="roomid") int roomId,
                         @RequestParam(value="starttime") String startTime,
                         @RequestParam(value="stoptime") String stopTime) {
        return sds.
                queryRDR(roomId,startTime,stopTime);
    }


    @GetMapping("/createinvoice")
    public bill CreateInvoice(@RequestParam(value="roomid") int roomId,
                              @RequestParam(value="starttime") String startTime,
                              @RequestParam(value="stoptime") String stopTime) {

        return bs.queryBill(roomId,startTime,stopTime);
    }

}
