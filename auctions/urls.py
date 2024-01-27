from django.urls import path

from . import views

urlpatterns = [
    path("", views.index, name="index"),
    path("sell", views.create, name="create"),
    path("<int:listing_id>", views.listing, name="listing"),
    path("bid/<int:listing_id>", views.bid, name="bid"),
    path("categories", views.categories, name="categories"),
    path("comment/<int:listing_id>", views.comment, name="comment"),
    path("search/<str:category>", views.search_by_category, name="search_by_category"),
    path("end_auction/<int:listing_id>", views.end_auction, name="end_auction"),
    path("watchlist", views.watchlist, name="watchlist"),
    path("login", views.login_view, name="login"),
    path("logout", views.logout_view, name="logout"),
    path("register", views.register, name="register")
]
