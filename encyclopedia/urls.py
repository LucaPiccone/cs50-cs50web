from django.urls import path

from . import views

app_name = "encyclopedia"
urlpatterns = [
    path("", views.index, name="index"),
    path("search", views.search, name="search"),
    path("randompage", views.randompage, name="randompage"),
    path("create", views.create, name="create"),
    path("update", views.update, name="update"),
    path("wiki/<str:name>", views.wiki, name="wiki"),
]
