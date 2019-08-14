from django.db.models.signals import post_save
from django.contrib.auth.models import User
from mysite.models import UserProfile
from django.dispatch import receiver


@receiver(post_save, sender=User)
def creat_user_profile(sender, instance, created, **kwargs):
    print "use signal creat"
    if created:
        UserProfile.objects.create(user=instance)


@receiver(post_save, sender=User)
def save_user_otherstatus(sender, instance, **kwargs):
    print (" use signal save")
    instance.userprofile.save()