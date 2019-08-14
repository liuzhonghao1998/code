package app.service;

import app.entity.User;
import app.entity.bill;
import app.object.RDR;

interface ReceptionService {
    public User checkIn(String idNumber);
    public String checkOut(int roomId);

}
