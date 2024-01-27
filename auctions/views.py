"""
Title: Commerece
Author: Luca Piccone
Description: Auction bidding

Special Thanks to OpenAI's ChatGPT (https://www.openai.com/chatgpt) for insights.
"""
from datetime import datetime
from decimal import Decimal
from django.contrib import messages
from django.contrib.auth import authenticate, login, logout
from django.contrib.auth.decorators import login_required
from django.db import IntegrityError
from django.http import HttpResponse, HttpResponseRedirect
from django.shortcuts import render
from django.urls import reverse, reverse_lazy
from django.views.decorators.http import require_http_methods

from .models import Categorie, User, Listing, Bid, Watchlist, Review
from .forms import CreateLising


def index(request):
    listings = Listing.objects.all()

    for listing in listings:
        # Retrieve the highest bid related to a listing
        highest_bid = listing.Bid.order_by('-amount').first()
        # Create a dynamic attribute and store the highest bid or the starting price
        listing.effective_price = highest_bid.amount if highest_bid else listing.starting_bid_price

    return render(request, "auctions/index.html", {
        "listings": listings
    })


@login_required(login_url=reverse_lazy('login'))
@require_http_methods(["POST"])
def comment(request, listing_id):
    listing = Listing.objects.filter(pk=listing_id).first()
    user = User.objects.filter(username=request.user.username).first()
    comment = request.POST["comment"]
    rating = request.POST['rating']

    try: 
        review = Review(user_id=user, listing_id=listing, content=comment, rating=rating)
        review.save()
    except:
        messages.error(request, "Something went wrong", extra_tags='comment_error')

    return HttpResponseRedirect(reverse('listing', args=[listing_id]))


def categories(request, category=None):
        return render(request, 'auctions/categories.html', {
            'categories': Categorie.objects.all()
        })


def search_by_category(request, category):
    category_to_search = Categorie.objects.filter(name=category).first().id
    listings = Listing.objects.all().filter(category_id=category_to_search)
    
    for listing in listings:
        highest_bid = Bid.objects.filter(listing_id=listing).order_by('-amount').first()
        # Create a dynamic attribute and store highest_bid.amount if highest_bid != None else store the starting_bid_price.
        listing.effective_price = highest_bid.amount if highest_bid else listing.starting_bid_price
        listing.bid_type = 'Highest Bid:' if highest_bid else "Bid Starting at:"

    return render(request, 'auctions/category_search_results.html', {
            'listings': listings,
            'category': category
        })
        

@login_required(login_url=reverse_lazy('login'))
def watchlist(request):
    user = User.objects.filter(username=request.user.username).first()
    watchlist = Watchlist.objects.get(user_id=user)
    if request.method == "GET":
        try:
            listings_in_watchlist = watchlist.listing_id.all()
             # For all the listings associated to a users watchlist 
            for listing in listings_in_watchlist:
                # retrieve the highest bid for each listing else highest_bid = None 
                highest_bid = Bid.objects.filter(listing_id=listing).order_by('-amount').first()
                # Create a dynamic attribute and store highest_bid.amount if highest_bid != None else store the starting_bid_price.
                listing.effective_price = highest_bid.amount if highest_bid else listing.starting_bid_price
                listing.bid_type = 'Highest Bid:' if highest_bid else "Bid Starting at:"

        except:
            watchlist = None

        if watchlist:
            return render(request, 'auctions/watchlist.html', {
                'listings_in_watchlist': listings_in_watchlist
            })
        else:
            messages.error(request, "Your Watchlist is empty")
            return render(request, 'auctions/watchlist.html')
        
    else:
        # Request to remove a listing from Watchlist
        if 'remove_from_watchlist' in request.POST:
            listing_to_remove = Listing.objects.get(pk=request.POST['listing_id'])

            watchlist.listing_id.remove(listing_to_remove)
        
        # Request to add a listing to watchlist 
        elif 'add_to_watchlist' in request.POST:
            listing_to_add = Listing.objects.get(pk=request.POST['listing_id'])

            watchlist.listing_id.add(listing_to_add)

            watchlist.save()
            
        return HttpResponseRedirect(reverse('watchlist'))


def listing(request, listing_id):
    if request.method == "GET":
        try:
            highest_bid = Bid.objects.filter(listing_id=listing_id).order_by('-amount').first().amount
        except:
            highest_bid = None

        user = User.objects.filter(username=request.user.username).first()
        listing = Listing.objects.get(pk=listing_id)
        
        listing.owner = "yes" if user == listing.user_id else 'no'

        user = User.objects.filter(username=request.user.username).first()

        user = User.objects.filter(username=request.user.username).first()
        watchlist = Watchlist.objects.get(user_id=user)
        
        listings_in_watchlist = watchlist.listing_id.all() 
        for watchlist_listing in listings_in_watchlist:
            if watchlist_listing.pk == listing.pk:
                listing.in_watchlist = "Yes"
                break
            else:
                listing.in_watchlist = "No"

        return render(request, 'auctions/listing.html',{
            'listing': listing,
            'highest_bid': highest_bid,
            'bid_count': Bid.objects.filter(listing_id=listing_id).count(),
            'categories': Listing.objects.get(pk=listing_id).category_id.all(),
            "listed_by": Listing.objects.get(pk=listing_id).user_id,
            'user_logged_in': user,
            'reviews': Review.objects.filter(listing_id=listing_id)
        })
    if request.method == 'POST':
        # This is exactly like the remove from watchlist function about but it return a redirect to the same listing page
        if 'remove_from_watchlist' in request.POST:
            listing_to_remove = Listing.objects.get(pk=request.POST['listing_id'])

            Watchlist.objects.get(user_id=User.objects.filter(username=request.user.username).first()).listing_id.remove(listing_to_remove)
        
        return HttpResponseRedirect(reverse('listing', args=[listing_id]))



@login_required(login_url=reverse_lazy('login'))
@require_http_methods(["POST"])
def end_auction(request, listing_id):
    user = User.objects.filter(username=request.user.username).first()
    listing = Listing.objects.get(pk=listing_id)
    if user == listing.user_id:
        try:
            highest_bid = Bid.objects.filter(listing_id=listing).order_by('-amount').first().user_id
        except:
            highest_bid = None

        listing.winner = highest_bid
        listing.auction_ended = True
        listing.save()

    return HttpResponseRedirect(reverse('listing', args=[listing_id]))


@login_required(login_url=reverse_lazy('login'))
@require_http_methods(["POST"])
def bid(request, listing_id):
    if request.method == "POST":
        new_bid = Decimal(request.POST['bid'])
        try:
            highest_bid = Decimal(Bid.objects.filter(listing_id=listing_id).order_by('-amount').first().amount)
        except:
            highest_bid = None
        Starting_price = Decimal(Listing.objects.filter(id=listing_id).first().starting_bid_price)

        # if highestbid is none, or new bid > highest bid and new_bid > starting bid evaulate to true 
        if not highest_bid or new_bid > highest_bid and new_bid >= Starting_price:
            bid_instance = Bid(
                user_id = User.objects.filter(username=request.user.username).first(),
                listing_id = Listing.objects.filter(pk=listing_id).first(),
                amount = new_bid
            )
            bid_instance.save()

            return HttpResponseRedirect(reverse('listing', args=[listing_id]))
        
        messages.error(request, "Your bid is to low", extra_tags="invalid_bid")
        return HttpResponseRedirect(reverse('listing', args=[listing_id]))
    

@login_required(login_url=reverse_lazy('login'))
def create(request):
    if request.method == "POST":
        form = CreateLising(request.POST)
        if form.is_valid():        
            form.cleaned_data
            instance = form.save(commit=False)
            instance.user_id = User.objects.filter(username=request.user.username).first()
            instance.save()
            form.save_m2m()

        return HttpResponseRedirect(reverse("listing", args=[instance.pk]))
        
    else:
        create_listing_form = CreateLising
        return render(request, "auctions/create.html", {
            'form': create_listing_form
        })    


def login_view(request):
    if request.method == "POST":

        # Attempt to sign user in
        username = request.POST["username"]
        password = request.POST["password"]
        user = authenticate(request, username=username, password=password)

        # Check if authentication successful
        if user is not None:
            login(request, user)
            return HttpResponseRedirect(reverse("index"))
        else:
            return render(request, "auctions/login.html", {
                "message": "Invalid username and/or password."
            })
    else:
        return render(request, "auctions/login.html")


def logout_view(request):
    logout(request)
    return HttpResponseRedirect(reverse("index"))


def register(request):
    if request.method == "POST":
        username = request.POST["username"]
        email = request.POST["email"]
        first_name = request.POST["first_name"]
        last_name = request.POST["last_name"]

        # Ensure password matches confirmation
        password = request.POST["password"]
        confirmation = request.POST["confirmation"]
        if password != confirmation:
            return render(request, "auctions/register.html", {
                "message": "Passwords must match."
            })

        # Attempt to create new user
        try:
            user = User.objects.create_user(username, email, password, first_name=first_name, last_name=last_name)
            user.save()

            new_watchlist = Watchlist.objects.create(user_id=User.objects.get(pk=user.pk))
        except IntegrityError:
            return render(request, "auctions/register.html", {
                "message": "Username already taken."
            })
        login(request, user)
        return HttpResponseRedirect(reverse("index"))
    else:
        return render(request, "auctions/register.html")
