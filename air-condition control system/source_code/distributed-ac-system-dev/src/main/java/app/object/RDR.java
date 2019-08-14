package app.object;


import app.entity.RD;

import java.util.ArrayList;


public class RDR {
    private ArrayList<RD> RDList =new ArrayList<RD>() {
    };

    public void addServiceDetail(RD sd) {
        RDList.add(sd);
    }

    public ArrayList<RD> getRDList() {
        return RDList;
    }

    public void setRDList(ArrayList<RD> RDList) {
        this.RDList = RDList;
    }
}