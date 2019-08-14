from django import template
from mysite.models import dianzan,Weibo,UserProfile
register = template.Library()
@register.simple_tag(takes_context=True)
def get_like_status(context,id):
    user = UserProfile.objects.get(id = context['user'].id)
    if dianzan.objects.filter(user=user,to_weibo = Weibo.objects.get(id=id)).exists():
        return 'active'
    else:
        return ''
@register.simple_tag()
def get_thumbup_num(id):
    return dianzan.objects.filter(to_weibo = Weibo.objects.get(id = id)).count()
@register.simple_tag(takes_context=True)
def get_focus_status(context,myid,id):
    user = UserProfile.objects.get(id=myid)
    thisuser = UserProfile.objects.get(id = id)
    if thisuser in user.follow_list.all():
        print("yes")
        return 'hide'
    else:
        print("no")
        return ''
@register.simple_tag(takes_context=True)
def get_focus_string(context,myid,id):
    myuser = UserProfile.objects.get(id = myid)
    thisuser = UserProfile.objects.get(id = id)
    if thisuser in myuser.follow_list.all():
        return '取消关注'
    else:
        return '关注'