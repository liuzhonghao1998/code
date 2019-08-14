package app.controller;

import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.GetMapping;

import java.time.LocalDateTime;

@Controller
public class WelcomeController {
    @GetMapping("/")
    String welcome() {
        LocalDateTime nowtime=LocalDateTime.now();
        System.out.println("New visit time :"+nowtime.toString());
        return "welcome.html";
    }
}
