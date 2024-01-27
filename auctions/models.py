from django.contrib.auth.models import AbstractUser
from django.core.validators import MinValueValidator, MaxValueValidator
from django.db import models

import os


class User(AbstractUser):
    first_name = models.CharField(max_length=64)
    last_name= models.CharField(max_length=64)
    email = models.CharField(max_length=64)
    birth_date = models.DateField(null=True, blank=True)
    profile_picture = models.ImageField(upload_to=os.path.join('media', 'uploads', 'images'), null=True, blank=True)
    phone_number = models.IntegerField
    address = models.TextField(null=True, blank=True)
    verified = models.BooleanField(default=False)

    def __str__(self):
        return f"{self.first_name} {self.last_name}"


class Categorie(models.Model):
    name = models.CharField(max_length=64)

    def __str__(self):
        return f"{self.name}"


class Brand(models.Model):
    name = models.CharField(max_length=64)

    def __str__(self):
        return f"{self.name}"


class Listing(models.Model):
    user_id = models.ForeignKey(User, on_delete=models.CASCADE, related_name="Listing", null=False)
    title = models.CharField(max_length=255)
    description = models.TextField()
    category_id = models.ManyToManyField(Categorie, related_name="Category")
    brand_id = models.ForeignKey(Brand, on_delete=models.PROTECT, related_name="Brand")
    image = models.URLField(null=True, blank=False)
    # buy_now_price = models.DecimalField(max_digits=10, decimal_places=2)
    starting_bid_price = models.DecimalField(max_digits=10, decimal_places=2)
    # end_time = models.DateTimeField() if we want the auction to expire at a certain time
    auction_ended = models.BooleanField(default=False)
    winner = models.ForeignKey(User, on_delete=models.CASCADE, related_name="Listing_winner", null=True, blank=True)
    timestamp = models.DateTimeField(auto_now_add=True)

    def __str__(self):
        return f"{self.id}: {self.title} ({self.user_id})"


class Review(models.Model):
    user_id = models.ForeignKey(User, on_delete=models.CASCADE, related_name="Review")
    listing_id = models.ForeignKey(Listing, on_delete=models.CASCADE, related_name="Review")
    content = models.TextField()
    rating = models.SmallIntegerField(validators=[MinValueValidator(limit_value=0), MaxValueValidator(limit_value=5)])
    timestamp = models.DateTimeField(auto_now_add=True)

    def __str__(self):
        return f"{self.id}: {self.content}"


class Bid(models.Model):
    user_id = models.ForeignKey(User, on_delete=models.CASCADE, related_name="Bid")
    listing_id = models.ForeignKey(Listing, on_delete=models.CASCADE, related_name="Bid")
    amount = models.DecimalField(max_digits=10, decimal_places=2)
    timestamp = models.DateTimeField(auto_now_add=True)

    def __str__(self):
        return f"{self.user_id}: {self.amount}"


class Purchase(models.Model):
    listing_id = models.ForeignKey(Listing, on_delete=models.CASCADE)
    user_id = models.ForeignKey(User, on_delete=models.CASCADE)
    quantity_purchased = models.IntegerField()
    total_amount = models.DecimalField(max_digits=10, decimal_places=2)
    timestamp = models.DateTimeField(auto_now_add=True)

class Watchlist(models.Model):
    user_id = models.ForeignKey(User, on_delete=models.CASCADE, related_name="watchlist")
    listing_id = models.ManyToManyField(Listing, related_name="watchlist", null=True)

    def __str__(self):
        return f"{self.user_id.first_name} {self.user_id.last_name}'s Watchlist"
