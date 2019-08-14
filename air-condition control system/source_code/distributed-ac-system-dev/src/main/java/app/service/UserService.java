package app.service;
import app.mapper.UserMapper;
import app.entity.User;
import app.entity.UserExample;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;
import java.util.List;

@Service
public class UserService {
    @Autowired
    private UserMapper usermapper;

    public User getUser(String userName) {
        UserExample ue=new UserExample();
        ue.createCriteria().andUsernameEqualTo(userName);
        List<User> ul=usermapper.selectByExample(ue);
        if (ul.size()==0) return null;
        return ul.get(ul.size()-1);
    }
    public void addUser(User u) {
        usermapper.insert(u);
    }
}
