from django.db import models
from django.contrib.auth.models import User
import datetime
import django.utils.timezone as timezone
# Create your models here.

class Weibo(models.Model):
    '''所有微博'''
    user = models.ForeignKey('UserProfile',on_delete=models.CASCADE)
    text = models.CharField(max_length=140)
    weiboimg=models.ImageField(upload_to='img',default="")
    videolink=models.CharField(max_length=140,default="")
    Comment_count = models.IntegerField(default=0)
    date = models.DateTimeField(auto_now_add=True)



class Topic(models.Model):
    '''话题'''
    name = models.CharField(max_length=140)
    date = models.DateTimeField(auto_now_add=True)
    topic_list = models.ManyToManyField('Weibo', blank=True, related_name="topic_Weibo", symmetrical=False )


class Comment(models.Model):
    '''评论'''
    to_weibo = models.ForeignKey('Weibo',on_delete=models.CASCADE)
    p_comment = models.ForeignKey('self',related_name="child_comments",on_delete=models.CASCADE,default="")
    user = models.ForeignKey('UserProfile',on_delete=models.CASCADE)
    comment = models.CharField(max_length=140)
    comment_type = models.IntegerField(default=0)
    date  = models.DateTimeField(auto_now_add=True)

class mention(models.Model):
    '''提及'''
    to_weibo = models.ForeignKey('Weibo',on_delete=models.CASCADE,default="")
    comment = models.ForeignKey('Comment',on_delete=models.CASCADE,default="")
    user = models.ForeignKey('UserProfile',on_delete=models.CASCADE)
    mention_type = models.IntegerField(default=0)
    date = models.DateTimeField(auto_now_add=True)
    flag = models.IntegerField(default=0)
class UserProfile(models.Model):
    '''用户信息'''

    user = models.OneToOneField(User,on_delete=models.CASCADE)
    name = models.CharField(max_length=64)
    email = models.EmailField()
    concernnum = models.IntegerField(default=0)
    fannum = models.IntegerField(default=0)
    weibonum = models.IntegerField(default=0)
    messagenum = models.IntegerField(default=0)
    follow_list = models.ManyToManyField('self',blank=True,related_name="my_followers",symmetrical=False)
    touxiangimg = models.ImageField(upload_to='img', default="")

class dianzan(models.Model):
    to_weibo = models.ForeignKey('Weibo', on_delete=models.CASCADE)
    user = models.ForeignKey('UserProfile', on_delete=models.CASCADE)
    date = models.DateTimeField(auto_now_add=True)