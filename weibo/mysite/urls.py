from django.conf.urls import url
from . import views
from django.contrib.auth import views as auth_views
from django.contrib.staticfiles.urls import staticfiles_urlpatterns

from django.contrib import staticfiles
urlpatterns=[
   url(r'^mysite/$', views.indexpage, name='indexpage'),
   url(r'^mysite/loginf/$', views.loginf, name='loginf'),
   url(r'^mysite/registf/$', views.registf, name='registf'),
   url(r'^mysite/search/$', views.search, name='search'),
   url(r'^mysite/addmyconcernmenu/$', views.addmyconcernmenu, name='addmyconcernmenu'),
   url(r'^mysite/writing/$', views.writing, name='writing'),
   url(r'^mysite/writecomment/$', views.writecomment, name='writecomment'),
   url(r'^mysite/writereply/$', views.writereply, name='writereply'),
   url(r'^mysite/calculatemention/$', views.calculatemention, name='calculatemention'),
   url(r'^mysite/calculatecomment/$', views.calculatecomment, name='calculatecomment'),
   url(r'^mysite/calculatereply/$', views.calculatereply, name='calculatereply'),
   url(r'^mysite/toconcent/$', views.toconcent, name='toconcent'),
   url(r'^mysite/toconcent2/$', views.toconcent2, name='toconcent2'),
   url(r'^mysite/tomyconcern/$', views.tomyconcern, name='tomyconcern'),
   url(r'^mysite/deleteconcernmenu/$', views.deleteconcernmenu, name='deleteconcernmenu'),
   url(r'^mysite/deleteconcernmy/$', views.deleteconcernmy, name='deleteconcernmy'),
   url(r'^mysite/tomyfan/$', views.tomyfan, name='tomyfan'),
   url(r'^mysite/tomyweibo/$', views.tomyweibo, name='tomyweibo'),
   url(r'^mysite/tohisweibo/$', views.tohisweibo, name='tohisweibo'),
   url(r'^mysite/deleteweibo/$', views.deleteweibo, name='deleteweibo'),
   url(r'^mysite/searchdeleteweibo/$', views.searchdeleteweibo, name='searchdeleteweibo'),
   url(r'^mysite/topicdeleteweibo/$', views.topicdeleteweibo, name='topicdeleteweibo'),
   url(r'^mysite/tolist/$', views.tolist, name='tolist'),
   url(r'^mysite/topicshow/$', views.topicshow, name='topicshow'),
   url(r'^mysite/deletecomment/$', views.deletecomment, name='deletecomment'),
   url(r'^mysite/friendessay/$', views.friendessay, name='friendessay'),
   url(r'^mysite/password_reset/$', auth_views.PasswordResetView.as_view(template_name="mysite/password_reset.html"),
       name="password_reset"),
   url(r'^mysite/password_reset_done/$',
       auth_views.PasswordResetDoneView.as_view(template_name="mysite/password_reset_done.html"),
       name="password_reset_done"),
   url(r'^mysite/password_reset_confirm/(?P<uidb64>[-\w]+)/(?P<token>[-\w]+)/$',
       auth_views.PasswordResetConfirmView.as_view(template_name="mysite/password_reset_confirm.html"),
       name="password_reset_confirm"),
   url(r'^mysite/password_reset_complete/$',
       auth_views.PasswordResetCompleteView.as_view(template_name="mysite/password_reset_complete.html"),
       name="password_reset_complete"),
   url(r'^thumb_up/', views.setdianzan,name='setdianzan'),
]

urlpatterns += staticfiles_urlpatterns()