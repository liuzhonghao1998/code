package app.controller;

import app.entity.User;
import app.service.UserService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.*;

import javax.servlet.http.HttpServletRequest;


@Controller
public class LoginController {

    @Autowired
    private UserService us;

    @GetMapping("/login")
    public String login(HttpServletRequest request) {
        String username=request.getParameter("username");
        String password=request.getParameter("password");

        User nowUser= us.getUser(username);

        if (nowUser!=null && nowUser.getPassword().equals(password)) {

            if (username.equals("admin")) return "admin.html";
            if (username.equals("manager")) return "manager.html";
            if (username.equals("receptionist")) return "receptionist.html";

            return "redirect:/userView/"+nowUser.getRoomid();
        }
        return "error.html";
    }

    @RequestMapping("/userView/{roomid}")
    public String userLoginView(){

        return "../user.html";
    }

}
