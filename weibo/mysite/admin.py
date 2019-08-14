from django.contrib import admin
from mysite.models import Weibo
from mysite.models import Topic
from mysite.models import Comment
from mysite.models import mention
from mysite.models import UserProfile
# Register your models here.
admin.site.register(Weibo)
admin.site.register(Topic)
admin.site.register(Comment)
admin.site.register(mention)
admin.site.register(UserProfile)
