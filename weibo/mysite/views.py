from django.shortcuts import render
from mysite.models import Weibo
from mysite.models import Topic
from mysite.models import Comment
from mysite.models import mention
from mysite.models import UserProfile
from mysite.models import dianzan
from django.contrib.auth.models import User
from django.contrib import auth
from django.contrib.auth.decorators import login_required
from django.core.paginator import Paginator, EmptyPage, PageNotAnInteger
from django.contrib.auth import authenticate, login, logout
from django.http import JsonResponse
from itertools import chain
from django.core.validators import validate_email
from django.core.exceptions import ValidationError
from django.shortcuts import redirect,HttpResponseRedirect,HttpResponse
import datetime
import json
# Create your views here.
def indexpage(request):
    logininfo = ''
    return render(request, 'mysite/login.html', {'logininfo': logininfo})

def loginf(request):
    if request.method == "POST":
        loginname = request.POST['username']
        loginpassword = request.POST['pwd']
        user = auth.authenticate(username=loginname, password=loginpassword)
        if user is not None:
            login(request, user)
            myup = UserProfile.objects.get(user=user)
            weibos = Weibo.objects.order_by("-Comment_count")
            listweibo = Paginator(weibos, 5)  # 每页5条
            page = 1
            try:
                weibolist = listweibo.page(page)  # contacts为Page对象！
            except PageNotAnInteger:
                # If page is not an integer, deliver first page.
                weibolist = listweibo.page(1)
            except EmptyPage:
                # If page is out of range (e.g. 9999), deliver last page of results.
                weibolist = listweibo.page(listweibo.num_pages)
            return render(request, 'mysite/list.html', {'user': user, 'weibos': weibolist, 'myup': myup})
        else:
            return render(request, 'mysite/login.html', {'wrong': 1})


def registf(request):
    if request.method == 'GET':
        return render(request, 'mysite/regist.html')
    else:
        registname = request.POST['username']
        touxiangimg = request.FILES.get('img')
        todouser = User.objects.filter(username=registname)
        if todouser.exists():
            logininfo = "error"
            return render(request, 'mysite/regist.html', {'logininfo': logininfo})
        else:
            registpassword = request.POST['pwd']
            nicheng = request.POST['nicheng']
            registemail = request.POST['email']
            if (registemail == ""):
                logininfo = "lack"
                return render(request, 'mysite/regist.html', {'logininfo': logininfo})
            else:
                if User.objects.filter(email=registemail):
                    logininfo = "repeate"
                    return render(request, 'mysite/regist.html', {'logininfo': logininfo})
                else:
                    try:
                        validate_email(registemail)
                        todo = User.objects.create_user(registname, registemail, registpassword)
                        todo.save()
                        todom = UserProfile(user=todo, name=nicheng,touxiangimg=touxiangimg)
                        todom.save()
                        logininfo = ''
                        return render(request, 'mysite/login.html', {'logininfo': logininfo})
                    except ValidationError:
                        logininfo='wrong'
                        return render(request, 'mysite/regist.html', {'logininfo': logininfo})


@login_required()
def search(request):
    if request.method=='POST':
        info = request.POST['info']
        contactswlist = Weibo.objects.filter(text__contains=info)
        contactsulist=UserProfile.objects.filter(name__contains=info)
        user=request.user
        return render(request, 'mysite/searchshow.html', {'contactswlist': contactswlist, 'contactsulist': contactsulist, 'user':user ,'info':info})

@login_required()
def deletecomment(request):
    if request.method=='GET':
     commentid= request.GET['commentid']
     thiscomment=Comment.objects.get(id=commentid)
     thisweibo=thiscomment.to_weibo
     thiscomment.delete()
     thisweibo.Comment_count = thisweibo.Comment_count - 1
     thisweibo.save()
     comments = Comment.objects.filter(to_weibo=thisweibo)
     return render(request, 'mysite/weiboconcent.html',
                   {'thisweibo': thisweibo, 'comments': comments, 'user': request.user})

@login_required()
def tomyconcern(request):
    if request.method == 'GET' :
        myuser=request.user
        myup = UserProfile.objects.get(user=myuser)
        myconcernlist = myup.follow_list.all()
        return render(request, 'mysite/myconcern.html', {'myconcernlist': myconcernlist, 'user': myuser})

@login_required()
def addmyconcernmenu(request):
    if request.method == 'GET':
       hisid=request.GET['hisid']
       myuser=request.user
       myup=UserProfile.objects.get(user=myuser)
       hisup=UserProfile.objects.get(id=hisid)
       myup.follow_list.add(hisup)
       myup.concernnum = myup.concernnum+1
       hisup.fannum = hisup.fannum +1
       hisup.save()
       myup.save()
       hisweibolist = Weibo.objects.filter(user=hisup)
       signal = 0
       if myup.follow_list.filter(id=hisid):
           signal = 1
       return render(request, 'mysite/hisweibo.html', {'hisweibolist': hisweibolist, 'signal': signal, 'hisup': hisup})

@login_required()
def deleteconcernmenu(request):
    if request.method== 'GET':
       hisid=request.GET['concernid']
       myuser=request.user
       myup=UserProfile.objects.get(user=myuser)
       hisup=UserProfile.objects.get(id=hisid)
       myup.follow_list.remove(hisup)
       myup.concernnum = myup.concernnum-1
       hisup.fannum = hisup.fannum-1
       hisup.save()
       myup.save()
       hisweibolist = Weibo.objects.filter(user=hisup)
       signal = 0
       if myup.follow_list.filter(id=hisid):
           signal = 1
       return render(request, 'mysite/hisweibo.html', {'hisweibolist': hisweibolist, 'signal': signal, 'hisup': hisup})

@login_required()
def deleteconcernmy(request):
    if request.method== 'GET':
       hisid=request.GET['concernid']
       myuser=request.user
       myup=UserProfile.objects.get(user=myuser)
       hisup=UserProfile.objects.get(id=hisid)
       myup.follow_list.remove(hisup)
       myup.concernnum = myup.concernnum-1
       hisup.fannum = hisup.fannum-1
       hisup.save()
       myup.save()
       myconcernlist = myup.follow_list.all()
       return render(request, 'mysite/myconcern.html', {'myconcernlist': myconcernlist, 'user': myuser})

@login_required()
def tomyfan(request):
    if request.method == 'GET':
        myuser = request.user
        myup = UserProfile.objects.get(user=myuser)
        myfanlist=UserProfile.objects.filter(follow_list=myup)
        return render(request, 'mysite/myfans.html', {'myfanlist': myfanlist, 'user': myuser})

@login_required()
def tomyweibo(request):
    if request.method == 'GET':
        myuser = request.user
        myup = UserProfile.objects.get(user=myuser)
        myweibolist=Weibo.objects.filter(user=myup)
        return render(request, 'mysite/myweibo.html', {'myweibolist': myweibolist, 'user': myuser ,'myup':myup})

@login_required()
def tohisweibo(request):
    if request.method == 'GET':
        hisid = request.GET['hisid']
        hisup= UserProfile.objects.get(id=hisid)
        hisweibolist = Weibo.objects.filter(user=hisup)
        user=request.user
        myup=UserProfile.objects.get(user=user)
        signal=0
        if myup.follow_list.filter(id=hisid):
            signal=1
        return render(request, 'mysite/hisweibo.html', {'hisweibolist':hisweibolist, 'signal':signal ,'hisup':hisup})

@login_required()
def toconcent(request):
    if request.method == 'GET':
        mentionid=request.GET['mentionid']
        thismention=mention.objects.get(id=mentionid)
        if thismention.mention_type == 0:
            thismention.mention_type=1
            thismention.save()
        if thismention.flag == 0:
            thisweibo=thismention.to_weibo
        else:
            thisweibo=thismention.comment.to_weibo
        myuser=request.user
        myup = UserProfile.objects.get(user=myuser)
        myup.messagenum = myup.messagenum-1
        myup.save()
        comments = Comment.objects.filter(to_weibo=thisweibo)
    return render(request, 'mysite/weiboconcent.html',
                  {'thisweibo': thisweibo, 'comments': comments, 'user': myuser})

@login_required()
def toconcent2(request):
    if request.method == 'GET':
        commentid=request.GET['commentid']
        thiscomment=Comment.objects.get(id=commentid)
        if thiscomment.comment_type == 0:
            thiscomment.comment_type=1
            thiscomment.save()
        myuser = request.user
        myup = UserProfile.objects.get(user=myuser)
        myup.messagenum = myup.messagenum - 1
        myup.save()
        thisweibo=thiscomment.to_weibo
        comments = Comment.objects.filter(to_weibo=thisweibo)
    return render(request, 'mysite/weiboconcent.html',
                  {'thisweibo': thisweibo, 'comments': comments, 'user': myuser})

@login_required()
def writing(request):
    if request.method == 'GET':
        return render(request, 'mysite/write.html', {'user': request.user})
    else:
        text = request.POST['userweibo']
        weiboimg=request.FILES.get('img')
        videolink=request.POST['videolink']
        myuser = request.user
        myup = UserProfile.objects.get(user=myuser)
        newweibo=Weibo(user=myup,text=text,weiboimg=weiboimg,videolink=videolink)
        newweibo.save()
        newtext=essaytolink(text,newweibo.id)
        newtext=topictolink(newtext,newweibo.id)
        thisweibo=Weibo.objects.get(id=newweibo.id)
        thisweibo.text=newtext
        thisweibo.save()
        myup.weibonum = myup.weibonum +1
        myup.save()
        print("第二次输出")
        print(newweibo.text)
        weibos = Weibo.objects.order_by("-Comment_count")
        listweibo = Paginator(weibos, 5)  # 每页5条
        page = 1
        try:
            weibolist = listweibo.page(page)  # contacts为Page对象！
        except PageNotAnInteger:
            # If page is not an integer, deliver first page.
            weibolist = listweibo.page(1)
        except EmptyPage:
            # If page is out of range (e.g. 9999), deliver last page of results.
            weibolist = listweibo.page(listweibo.num_pages)
        return render(request, 'mysite/list.html', {'user': myuser, 'weibos' : weibolist,'myup':myup})

@login_required()
def deleteweibo(request):
    if request.method == 'GET':
        weiboid = request.GET['weiboid']
        thisweibo = Weibo.objects.get(id=weiboid)
        thisweibo.delete()
        myuser = request.user
        myup = UserProfile.objects.get(user=myuser)
        myup.weibonum = myup.weibonum -1
        myup.save()
        myweibolist=Weibo.objects.filter(user=myup)
        return render(request, 'mysite/myweibo.html', {'myweibolist': myweibolist, 'user': myuser})

@login_required()
def searchdeleteweibo(request):
    if request.method == 'GET':
        weiboid = request.GET['weiboid']
        info=request.GET['info']
        thisweibo = Weibo.objects.get(id=weiboid)
        thisweibo.delete()
        myuser = request.user
        myup = UserProfile.objects.get(user=myuser)
        myup.weibonum = myup.weibonum -1
        myup.save()
        contactswlist = Weibo.objects.filter( text__contains=info)
        contactsulist=UserProfile.objects.filter(name__contains=info)
        user=request.user
        return render(request, 'mysite/searchshow.html',
                      {'contactswlist': contactswlist, 'contactsulist': contactsulist, 'user': user})

@login_required()
def topicdeleteweibo(request):
    if request.method == 'GET':
        weiboid = request.GET['weiboid']
        topicid = request.GET['topicid']
        thistopic=Topic.objects.get(id=topicid)
        thisweibo = Weibo.objects.get(id=weiboid)
        thisweibo.delete()
        myuser = request.user
        myup = UserProfile.objects.get(user=myuser)
        myup.weibonum = myup.weibonum -1
        myup.save()
        topicweibolist = thistopic.topic_list.all()
        return render(request, 'mysite/topicshow.html',
                      {'topicweibolist': topicweibolist, 'thistopic': thistopic, 'user': request.user})

@login_required()
def writecomment(request):
    if request.method == 'GET':
        weiboid=request.GET['weiboid']
        thisweibo=Weibo.objects.get(id=weiboid)
        comments = Comment.objects.filter(to_weibo=thisweibo)
        return render(request, 'mysite/weiboconcent.html',
                      {'thisweibo': thisweibo, 'comments': comments, 'user': request.user})
    else:
        weiboid = request.POST['weiboid']
        text = request.POST['text']
        thisweibo = Weibo.objects.get(id=weiboid)
        thisuser=UserProfile.objects.get(user=request.user)
        newcomment=Comment(to_weibo=thisweibo,user=thisuser,comment=text)
        newcomment.save()
        atcomment=commenttolink(text,newcomment.id)
        thiscomment=Comment.objects.get(id=newcomment.id)
        thiscomment.comment=atcomment
        thiscomment.save()
        thisweibo = Weibo.objects.get(id=weiboid)
        comments = Comment.objects.filter(to_weibo=thisweibo)
        thisweibo.Comment_count=thisweibo.Comment_count+1
        thisweibo.save()
        thatuser= thisweibo.user
        thatuser.messagenum = thatuser.messagenum + 1
        thatuser.save()
        return render(request, 'mysite/weiboconcent.html',
                      {'thisweibo': thisweibo, 'comments': comments, 'user': request.user})

@login_required()
def writereply(request):
    if request.method == 'POST':
        weiboid = request.POST['weiboid']
        commentid=request.POST['commentid']
        text=request.POST['replytext']
        thisweibo = Weibo.objects.get(id=weiboid)
        thisuser = UserProfile.objects.get(user=request.user)
        thiscomment=Comment.objects.get(id=commentid)
        newreply=Comment(to_weibo=thisweibo,user=thisuser,p_comment=thiscomment,comment=text)
        newreply.save()
        thatuser = thiscomment.user
        thatuser.messagenum = thatuser.messagenum + 1
        thatuser.save()
        atreply=replytolink(text,newreply.id)
        thisreply=Comment.objects.get(id=newreply.id)
        thisreply.comment=atreply
        thisreply.save()
        print(thisreply.id)
        thisweibo = Weibo.objects.get(id=weiboid)
        comments = Comment.objects.filter(to_weibo=thisweibo)
        print(comments.__len__())
        return render(request, 'mysite/weiboconcent.html',
                      {'thisweibo': thisweibo, 'comments': comments, 'user': request.user})

@login_required()
def calculatemention(request):
    if request.method == 'GET':
        thisuser= UserProfile.objects.get(user=request.user)
        mentionlist=mention.objects.filter(user=thisuser,mention_type=0)
        return render(request,'mysite/my@.html',{'mentionlist':mentionlist, 'user':request.user})

@login_required()
def calculatecomment(request):
    if request.method == 'GET':
        thisuser= UserProfile.objects.get(user=request.user)
        print(thisuser.id)
        commentlist=Comment.objects.none()
        commentall=Comment.objects.all()
        for thiscomment in commentall:
            if thiscomment.to_weibo.user == thisuser and thiscomment.comment_type == 0:
                commentsearch=Comment.objects.filter(id=thiscomment.id)
                commentlist=commentlist | commentsearch
        return render(request,'mysite/mycomment.html',{'commentlist':commentlist, 'user':request.user})

@login_required()
def calculatereply(request):
    if request.method == 'GET':
        thisuser= UserProfile.objects.get(user=request.user)
        print(thisuser.id)
        commentlist=Comment.objects.none()
        commentall=Comment.objects.all()
        for thiscomment in commentall :
            if thiscomment.to_weibo.user == thisuser and thiscomment.comment_type == 0:
                commentsearch=Comment.objects.filter(id=thiscomment.id)
                commentlist=commentlist | commentsearch
        return render(request,'mysite/myresponse.html',{'commentlist':commentlist, 'user':request.user})

def essaytolink(str,weiboid):  # 将@转化为链接
    pos = 0
    aa = '/mysite/tohisweibo/'
    linklen = len(aa)
    thisstr = str
    namelen=0
    while (pos < len(thisstr)):
        if "@" in thisstr[pos:]:
            pos = thisstr[pos:].index("@") + pos
            print(pos)
            if " " in thisstr[pos:]:
                pos1 = thisstr[pos:].index(" ")
            else:
                pos1 = len(thisstr) - pos
                # print(pos1)
            str1 = list(thisstr)
            str11 = str1[pos + 1:pos + pos1]
            print(str11)
            str111 = ''.join(str11)
            names = UserProfile.objects.filter(name=str111)
            if names.exists():
                thisup=UserProfile.objects.get(name=str111)
                hisid=thisup.id
                namelen=len(hisid.__str__())
                print(namelen)
                str1.insert(pos + pos1, '</a>')
                str1.insert(pos, '<a href="/mysite/tohisweibo/?hisid='+hisid.__str__()+'">')
                thisweibo=Weibo.objects.get(id=weiboid)
                for name in names:
                    name.messagenum = name.messagenum + 1
                    name.save()
                    newmention = mention(user=name, to_weibo=thisweibo)
                    newmention.save()
            thisstr = ''.join(str1)
            print(thisstr)
            pos = pos + pos1 + 16 + linklen + namelen + 7
            print(pos)
        else:
            break
    print(thisstr)
    return thisstr

def commenttolink(str,commentid):  # 将@转化为链接
    pos = 0
    aa = '/mysite/tohisweibo/'
    linklen = len(aa)
    thisstr = str
    namelen=0
    while (pos < len(thisstr)):
        if "@" in thisstr[pos:]:
            pos = thisstr[pos:].index("@") + pos
            print(pos)
            if " " in thisstr[pos:]:
                pos1 = thisstr[pos:].index(" ")
            else:
                pos1 = len(thisstr) - pos
                # print(pos1)
            str1 = list(thisstr)
            str11 = str1[pos + 1:pos + pos1]
            print(str11)
            str111 = ''.join(str11)
            names = UserProfile.objects.filter(name=str111)
            if names.exists():
                thisup=UserProfile.objects.get(name=str111)
                hisid=thisup.id
                namelen=len(hisid.__str__())
                str1.insert(pos + pos1, '</a>')
                str1.insert(pos, '<a href="/mysite/tohisweibo/?hisid='+hisid.__str__()+'">')
                thiscomment=Comment.objects.get(id=commentid)
                for name in names:
                    name.messagenum = name.messagenum + 1
                    name.save()
                    newmention=mention(user=name,comment=thiscomment,flag=1)
                    newmention.save()
            thisstr = ''.join(str1)
            print(thisstr)
            pos = pos + pos1 + 16 + linklen+namelen+7
            print(pos)
        else:
            break

    return thisstr

def replytolink(str,commentid):  # 将@转化为链接
    pos = 0
    aa = '/mysite/tohisweibo/'
    linklen = len(aa)
    thisstr = str
    namelen=0
    while (pos < len(thisstr)):
        if "@" in thisstr[pos:]:
            pos = thisstr[pos:].index("@") + pos
            print(pos)
            if " " in thisstr[pos:]:
                pos1 = thisstr[pos:].index(" ")
            else:
                pos1 = len(thisstr) - pos
                # print(pos1)
            str1 = list(thisstr)
            str11 = str1[pos + 1:pos + pos1]
            print(str11)
            str111 = ''.join(str11)
            names = UserProfile.objects.filter(name=str111)
            if names.exists():
                thisup=UserProfile.objects.get(name=str111)
                hisid=thisup.id
                namelen=len(hisid.__str__())
                str1.insert(pos + pos1, '</a>')
                str1.insert(pos, "<a href='/mysite/tohisweibo/?hisid="+hisid.__str__()+"'>")
                thiscomment=Comment.objects.get(id=commentid)
                for name in names:
                    name.messagenum = name.messagenum + 1
                    name.save()
                    newmention=mention(user=name,comment=thiscomment,flag=1)
                    newmention.save()
            thisstr = ''.join(str1)
            print(thisstr)
            pos = pos + pos1 + 16 + linklen+namelen+9
            print(pos)
        else:
            break

    return thisstr

def topictolink(str,weiboid):
    pos=0
    aa = '/mysite/topicshow/'
    linklen = len(aa)
    thisstr=str
    topicid = ""
    namelen = 0
    while(pos<len(thisstr)):
        if "#" in thisstr[pos:]:
            pos = thisstr[pos:].index("#") + pos
            print(pos)
            if "#" in thisstr[(pos+1):]:
                pos1 = thisstr[(pos+1):].index("#")
            else:
                break
            str1 = list(thisstr)
            str11 = str1[pos + 1:pos + pos1+1]
            print(str11)
            str111 = ''.join(str11)
            thistopic = Topic.objects.filter(name=str111)
            thisweibo=Weibo.objects.get(id=weiboid)
            if thistopic.exists():
                thistopic = Topic.objects.get(name=str111)
                thistopic.topic_list.add(thisweibo)
                topicid=thistopic.id.__str__()
                thistopic.save()
            else:
                newtopic=Topic(name=str111)
                newtopic.save()
                thetopic=Topic.objects.get(id=newtopic.id)
                thetopic.topic_list.add(thisweibo)
                thetopic.save()
                topicid = thetopic.id.__str__()
            namelen = len(topicid)
            str1.insert(pos + pos1+2, '</a>')
            str1.insert(pos, '<a href="/mysite/topicshow/?topicid='+topicid+'">')
            thisstr = ''.join(str1)
            print(thisstr)
            pos = pos + pos1 + 16 + linklen+ namelen+9
            print(pos)
        else:
            break

    return thisstr

@login_required
def topicshow(request):
    if request.method == 'GET':
      topicid=request.GET['topicid']
      thistopic=Topic.objects.get(id=topicid)
      topicweibolist=thistopic.topic_list.all()
      return render(request, 'mysite/topicshow.html', {'topicweibolist': topicweibolist,'thistopic':thistopic, 'user':request.user})

@login_required
def tolist(request):
    weibos = Weibo.objects.order_by("-Comment_count")
    user=request.user
    myup=UserProfile.objects.get(user=user)
    listweibo = Paginator(weibos, 5)  # 每页5条
    page =  request.GET.get('page', 1)
    try:
        weibolist = listweibo.page(page)  # contacts为Page对象！
    except PageNotAnInteger:
        # If page is not an integer, deliver first page.
        weibolist = listweibo.page(1)
    except EmptyPage:
        # If page is out of range (e.g. 9999), deliver last page of results.
        weibolist = listweibo.page(listweibo.num_pages)
    return render(request, 'mysite/list.html', {'user': request.user, 'weibos': weibolist,'myup':myup})

@login_required
def friendessay(request):
    thisuser=request.user
    myup=UserProfile.objects.get(user=thisuser)
    myconcernlist=myup.follow_list.all()
    thislist = Weibo.objects.none()
    for myconcern in myconcernlist :
      friendweibo= Weibo.objects.filter(user=myconcern)
      thislist=thislist | friendweibo
    listweibo = Paginator(thislist, 5)  # 每页5条
    page =  request.GET.get('page', 1)
    try:
        thislist = listweibo.page(page)  # contacts为Page对象！
    except PageNotAnInteger:
        # If page is not an integer, deliver first page.
        thislist = listweibo.page(1)
    except EmptyPage:
        # If page is out of range (e.g. 9999), deliver last page of results.
        thislist = listweibo.page(listweibo.num_pages)
    return render(request, 'mysite/list.html', {'user': request.user, 'weibos': thislist,'myup':myup})

@login_required
def setdianzan(request):
    id=request.GET['id']
    print("?")
    thisuser=request.user
    thisup=UserProfile.objects.get(user=thisuser)
    thisweibo=Weibo.objects.get(id=id)
    if dianzan.objects.filter(user=thisup, to_weibo=thisweibo).count() == 0:
        newdianzan = dianzan(to_weibo=thisweibo, user=thisup)
        newdianzan.save()
        status=1
    else:
        status=0
        thisdianzan= dianzan.objects.get(user = thisup,to_weibo=thisweibo)
        thisdianzan.delete()
    num = dianzan.objects.filter( to_weibo=thisweibo).count()
    data = {
        'status':status,
        'num':num,
    }
    return HttpResponse(json.dumps(data),content_type = "application/json")