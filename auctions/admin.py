from django.contrib import admin

from .models import Bid, Brand, Categorie, Listing, Review, User, Watchlist

class ListingAdmin(admin.ModelAdmin):
    list_display = ("id", "user_id", "title")

class UserAdmin(admin.ModelAdmin):
    list_display = ["username", "first_name", "last_name"]

# Register your models here.
admin.site.register(Bid)
admin.site.register(Brand)
admin.site.register(Categorie)
admin.site.register(Listing, ListingAdmin)
admin.site.register(Review)
admin.site.register(User, UserAdmin)
admin.site.register(Watchlist)
